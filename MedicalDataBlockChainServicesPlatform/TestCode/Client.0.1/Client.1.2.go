package main

import (
	"fmt"
	"net"
	"strconv"
)

func main() {

	listens_socket,errors:=net.Listen("tcp",":0")
	if errors!=nil{
		fmt.Println(errors)
		fmt.Printf("Socket Running Error.\n")
		return
	}
	port:=strconv.Itoa(listens_socket.Addr().(*net.TCPAddr).Port)
	listens_socket.Close()
	fmt.Printf("Running listener at %s,\n",port)
	listen_socket,error:=net.Listen("tcp",port)
	if error!=nil{
		fmt.Println("Lunching error.")
		return
	}
	defer listen_socket.Close()
	connect,err:=net.Dial("tcp","101.200.155.187:9000")
	if err != nil {
		fmt.Println("Connect to server failed.")
		return
	}
	defer connect.Close()
	fmt.Println("Connect sever completed.")
	var msg string
	message:=strconv.Itoa(listen_socket.Addr().(*net.TCPAddr).Port)
	fmt.Scan(&msg)
	message+=";"
	message+=msg
	connect.Write([]byte(message))

	data := make([]byte, 255)
	msg_read,err:=connect.Read(data)
	if msg_read==0 || err!=nil {
		fmt.Println("Receive Error.")
		return
	}
	connectR,errorR:=listen_socket.Accept()
	fmt.Println("Waiting...")
	if errorR!=nil{
		fmt.Println("Return Connect Error.")
		return
	}
	defer connectR.Close()
	data_return := make([]byte, 255)
	msg_read_return, err_return := connectR.Read(data_return)


	msg_read_str := string(data[0:msg_read])
	fmt.Println("Result: ", msg_read_str)
	connect.Close()

	if msg_read_str=="Error - Wrong Message."||msg_read_str==""{
		fmt.Println(msg_read_str)
		return
	}
	// var message string

	if msg_read_return == 0 || err_return != nil {
		fmt.Println("Read error.")
		return
	}else{
		message=string(data[0:msg_read])
		fmt.Printf("Return: %s.\n",message)
		return
	}


	//var pos int
	//for pos=0;pos<len(msg_read_str);pos++{
	//	if msg_read_str[pos]==':'{
	//		break
	//	}
	//}
	//fmt.Println(msg_read_str[pos:len(msg_read_str)])
	//for{
	//	fmt.Println("Waiting...")
	//
	//}

}

// Verify000000000000000000000000000000000000000000000000000000000000000012345678901234567890123456789
