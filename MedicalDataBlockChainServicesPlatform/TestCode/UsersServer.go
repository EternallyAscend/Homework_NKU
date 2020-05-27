package main
// You need to check the ip of the server and change it in line.
import (
	"fmt"
	"net"
	"os"
)

//// ------------------------------------ Request ------------------------------------

type request struct{
	front *request
	next *request
	ip string // Here using ipv4 with port.
	command byte
	authorID string
	parameter string
}

func (re *request)init(message string) bool{
	re.front=nil
	re.next=nil
	re.ip=message[0:20]
	switch message[20:26] {
	case "Query ":
		re.command=1
		break
	case "Write ":
		re.command=2
		break
	case "Verify":
		re.command=3
		break
	default:
		return false
	}
	re.authorID=message[26:30]
	re.parameter=message[30:len(message)]
	return true
} // This deal string.

//// ------------------------------------ Request Queue ------------------------------------

type requestQueue struct{
	empty bool
	size uint64
	head *request
	tail *request
}

func (rq *requestQueue)init(){
	rq.empty=true
	rq.size=0
	rq.head=nil
	rq.tail=nil
}

func (rq *requestQueue)insert(re *request){
	if rq.empty{
		rq.empty=false
		rq.head=re
		rq.head.front=nil
	}else{
		rq.tail.next=re
		re.front=rq.tail
	}
	rq.tail=re
	rq.tail.next=nil
	rq.size++
}

func (rq *requestQueue)pop() *request{
	if rq.empty{
		return nil
	}
	re:=rq.head
	if rq.size>1 {
		rq.head=rq.head.next
		rq.head.front=nil
	}else{
		rq.empty=true
		rq.head=nil
		rq.tail=nil
	}
	rq.size--
	re.next=nil
	return re
}

//// ------------------------------------ Deal Queue ------------------------------------

type dealQueue struct{
	empty bool
	size uint64
	head *request
	tail *request
}

func (rq *dealQueue)init(){
	rq.empty=true
	rq.size=0
	rq.head=nil
	rq.tail=nil
}

func (rq *dealQueue)insert(re *request){
	if rq.empty{
		rq.empty=false
		rq.head=re
		rq.head.front=nil
	}else{
		rq.tail.next=re
		re.front=rq.tail
	}
	rq.tail=re
	rq.tail.next=nil
	rq.size++
}

func (rq *dealQueue)pop() *request{
	if rq.empty{
		return nil
	}
	re:=rq.head
	if rq.size>1 {
		rq.head=rq.head.next
		rq.head.front=nil
	}else{
		rq.empty=true
		rq.head=nil
		rq.tail=nil
	}
	rq.size--
	re.next=nil
	return re
}

//// ------------------------------------ Result ------------------------------------

type result struct{
	front *result
	next *result
	ip string
	data string
}

func (re *result)init(ip string,data string){
	re.front=nil
	re.next=nil
	re.ip=ip
	re.data=data
}

//// ------------------------------------ Result Queue ------------------------------------

type resultQueue struct{
	empty bool
	size uint64
	head *result
	tail *result
}

func (rq *resultQueue)init(){
	rq.empty=true
	rq.size=0
	rq.head=nil
	rq.tail=nil
}

func (rq *resultQueue)insert(re *result){
	if rq.empty{
		rq.empty=false
		rq.head=re
		rq.head.front=nil
	}else{
		rq.tail.next=re
		re.front=rq.tail
	}
	rq.tail=re
	rq.tail.next=nil
	rq.size++
}

func (rq *resultQueue)pop() *result{
	if rq.empty{
		return nil
	}
	re:=rq.head
	if rq.size>1 {
		rq.head=rq.head.next
		rq.head.front=nil
	}else{
		rq.empty=true
		rq.head=nil
		rq.tail=nil
	}
	rq.size--
	re.next=nil
	return re
}

//// ------------------------------------ User Server ------------------------------------

type userServer struct{
	request_queue *requestQueue
	deal_queue *dealQueue
	result_queue *resultQueue
	// Maybe here will add some ip and port list for easy start.
	receiving bool
	running bool
	sending bool
}

func (user_server *userServer)init(){
	user_server.request_queue=&requestQueue{
		empty: true,
		size:  0,
		head:  nil,
		tail:  nil,
	}
	user_server.deal_queue=&dealQueue{
		empty: true,
		size:  0,
		head:  nil,
		tail:  nil,
	}
	user_server.result_queue=&resultQueue{
		empty: true,
		size:  0,
		head:  nil,
		tail:  nil,
	}
	//user_server.request_queue.init()
	//user_server.deal_queue.init()
	//user_server.request_queue.init()

	user_server.receiving=false
	user_server.running=false
	user_server.sending=false
}

func (us *userServer)start(ip string,port string){
	listen_socket,error:=net.Listen("tcp",port)
	defer listen_socket.Close()
	defer us.close(ip,port)
	if error!=nil{
		fmt.Println("Socket Running Error.")
	}else {
		us.receiving=true
	}
	for us.receiving{
		message:=""
		connect,err:=listen_socket.Accept()
		defer connect.Close()
		if err!=nil{
			fmt.Println("Connect Error.")
			continue
		}
		data := make([]byte, 255)
		msg_read, err := connect.Read(data)
		if msg_read == 0 || err != nil {
			fmt.Println("Read error.")
		}else{
			message=string(data[0:msg_read])
		}

		if message==""{
			continue
		}
		re:=&request{
			front:     nil,
			next:      nil,
			ip:        "",
			command:   0,
			authorID:  "",
			parameter: "",
		}
		re.init(message)
		// us.request_queue.insert(re)
		go us.deal(re)
	}
}

func (us *userServer)close(ip string,port string){
	us.receiving=false
}

func (us *userServer)deal(re *request){
	data:=""
	switch re.command {
	case 1:
		data+="Query "
		break
	case 2:
		data+="Write "
		break
	case 3:
		data+="Verify"
		break
	default:
		break
	}
	go us.returnResult(re.ip,data)
}

func (us *userServer)returnResult(ip string,data string){
	//for !us.result_queue.empty{
	//	re:=us.result_queue.pop()
	//	fmt.Println(re.data)
	//	// Return data here.
	//}
	connect,err:=net.Dial("tcp",ip)
	defer connect.Close()
	if err!=nil{
		fmt.Printf("Return failed to ip %s.",ip)
		return
	}
	connect.Write([]byte(data))
	connect.Close()
}

//// ------------------------------------ Main Function ------------------------------------


//// ------------------------------------ Main Function ------------------------------------
func main(){
	var userServer userServer
	userServer.init()

	addrs, err := net.InterfaceAddrs()
	if err != nil {
		fmt.Println(err)
		os.Exit(1)
	}
	for _, address := range addrs {

		// 检查ip地址判断是否回环地址
		if ipnet, ok := address.(*net.IPNet); ok && !ipnet.IP.IsLoopback() {
			if ipnet.IP.To4() != nil {
				fmt.Println(ipnet.IP.String())
			}

		}
	}

	rq:=userServer.request_queue
	//rq:=&requestQueue{
	//	empty: true,
	//	size:  0,
	//	head:  nil,
	//	tail:  nil,
	//}
	for i:=0;i<100;i++{
		temp:=&request{
			front:     nil,
			next:      nil,
			ip:        "",
			command:   byte(i),
			authorID:  "",
			parameter: "",
		}
		rq.insert(temp)
	}
	for i:=0;i<100;i++{
		re:=rq.pop()
		fmt.Println(re.command)
	}
	//interface_list, err := net.Interfaces()
	//if err != nil {
	//	fmt.Println(err)
	//	return
	//}
	//var byName *net.Interface
	//var addrList []net.Addr
	//var oneAddrs []string
	//for _, i := range interface_list {
	//	byName, err = net.InterfaceByName(i.Name)
	//	if err != nil {
	//		fmt.Println(err)
	//		return
	//	}
	//	addrList, err = byName.Addrs()
	//	if err != nil {
	//		fmt.Println(err)
	//		return
	//	}
	//	for _, oneAddr := range addrList {
	//		oneAddrs = strings.SplitN(oneAddr.String(), "/", 2)
	//		fmt.Println(i.Name, "-", oneAddrs[0])
	//	}
	//}
	userServer.start("101.200.155.187",":9000")
}

//101.200.155.187:8000Verify12345IDID








