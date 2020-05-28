package main

import (
	"fmt"
	"net"
)

func main(){



	ip:="52513"
	connect,err:=net.Dial("tcp","localhost:"+ip)
	//connect,err:=net.Dial("tcp","60.24.251.228:"+ip)
	//connect,err:=net.Dial("tcp","101.200.155.187:"+ip)
	if err != nil {
		fmt.Println("Connect to server failed.")
		return
	}
	defer connect.Close()
	fmt.Println("Connect sever completed.")
	var msg string
	fmt.Scan(&msg)
	connect.Write([]byte(msg))
}
