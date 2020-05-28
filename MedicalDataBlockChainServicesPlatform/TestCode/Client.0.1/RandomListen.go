package main

import (
	"fmt"
	"net"
)

func main(){
	//freePort,freePortError:=net.Listen("tcp",":0")
	//if freePortError!=nil{
	//	fmt.Println("Init Error.")
	//	return
	//}
	//getPort:=strconv.Itoa(freePort.Addr().(*net.TCPAddr).Port)
	//freePort.Close()
	//fmt.Println(getPort)
	getPort:="58400"
	tcpReceive,receiveError:=net.Listen("tcp","60.24.251.228:"+getPort)
	if receiveError!=nil{
		fmt.Println(receiveError)
		fmt.Println("Tcp Receive Create Failed.")
		return
	}

	tcpSend,sendError:=net.Dial("tcp","101.200.155.187:9000")
	if sendError!=nil{
		fmt.Println("Cannot Connect to Server.")
		return
	}
	defer tcpSend.Close()
	fmt.Println("Connect to Server.")


	var message string
	fmt.Scan(&message)
	tcpSend.Write([]byte(getPort+";"+message))

	statusByte:=make([]byte,255)
	statusRead,statusError:=tcpSend.Read(statusByte)
	if statusRead==0||statusError!=nil{
		fmt.Println("Receive Error.")
		return
	}
	statusString:=string(statusByte[0:statusRead])
	fmt.Println("Status:")
	fmt.Println(statusString)
	//tcpSend.Close()

	fmt.Println("Before")
	tcpReturn,returnError:=tcpReceive.Accept()
	if returnError!=nil{
		fmt.Println("Listening Start Error.")
	}
	defer tcpReturn.Close()
	fmt.Println("Waiting return...")

	returnByte:=make([]byte,255)
	returnRead,readError:=tcpReturn.Read(returnByte)
	if returnRead==0||readError!=nil{
		fmt.Println("Error Occur when Read.")
	}
	returnString:=string(returnByte[0:returnRead])
	fmt.Println(returnString)

	// tcpReceive.Close()

	//listen_socket,error:=net.Listen("tcp",":0")
	//if listen_socket!=nil{
	//	defer listen_socket.Close()
	//}
	//if error!=nil{
	//	fmt.Println(error)
	//	fmt.Printf("Socket Running Error.\n")
	//	return
	//}
	//fmt.Printf("Running listener at %s,\n",strconv.Itoa(listen_socket.Addr().(*net.TCPAddr).Port))
	//connectR,errorR:=listen_socket.Accept()
	//fmt.Println("Waiting...")
	//if errorR!=nil{
	//	fmt.Println("Return Connect Error.")
	//	return
	//}
	//defer connectR.Close()
	//data_return := make([]byte, 255)
	//msg_read_return, err_return := connectR.Read(data_return)
	//if err_return!=nil{
	//	fmt.Println("Return receive wrong.")
	//	return
	//}
	//fmt.Println(msg_read_return)
}