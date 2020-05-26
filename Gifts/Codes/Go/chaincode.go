package main

import (
	"bytes"
	"encoding/json"
	"fmt"
	"strconv"
	"time"

	"github.com/hyperledger/fabric/core/chaincode/shim"
	pb "github.com/hyperledger/fabric/protos/peer"
)

type SupplyChain struct {
}

//
type Orders struct {
	OrderId     string `json:"orderid"`
	TruckId     string `json:"truckid"`
	GpscordsX   string `json:"gpscordsx"`
	GpscordsY   string `json:"gpscordsy"`
	OrderInfos   []string `json:"orderinfo"`
}
type OrderInfo struct {
	OrderInfoId string `json:"OrderInfoId"`
	L1000TxDes  string `json:"L1000_TxDes"`
	L1100Status string `json:"L1100_Status"`
	L1200Part   string `json:"L1200_Part"`
	L1300Weight string `json:"L1300_Weight"`
}
func constructOrderKey (orderId string) string{
	return fmt.Sprintf("order_%s",orderId)
}

func constructOrderInfoKey (orderInfoId string) string{
	return fmt.Sprintf("orderInfo_%s", orderInfoId)
}

func (c *SupplyChain) Init(stub shim.ChaincodeStubInterface) pb.Response{
	return shim.Success(nil)
}

func (c *SupplyChain) Invoke(stub shim.ChaincodeStubInterface) pb.Response{
	funcName, args := stub.GetFunctionAndParameters()
	switch funcName {
	case "ordersRegister":
		return c.ordersRegister (stub, args)
	case "gpsChange":
		return c.gpsChange (stub, args)
	case "queryOrders":
		return c.queryOrders (stub, args)
	case "queryOrdersHistory":
		return c.queryOrdersHistory (stub, args)
	case "gpsChangeBaseTruck":
		return c.gpsChangeBaseTruck (stub,args)
	case "orderInfoEnroll":
		return c.orderInfoEnroll (stub,args)
	case "orderInfoChange":
		return c.orderInfoChange(stub,args)
	case "queryOrderInfoHistory":
		return c.queryOrderInfoHistory(stub,args)
	case "queryOrdersInfo":
		return c.queryOrdersInfo(stub,args)



	default:
		return shim.Error(fmt.Sprintf("unsupported function: %s",funcName))
	}
}

func (c *SupplyChain)ordersRegister(stub shim.ChaincodeStubInterface, args []string) pb.Response {
	//检查参数个数 
	if len(args)!= 4 {
		return shim.Error("not enough args")
	}
	objectid := args[0]
	truckid := args[1]
	gpscordsx := args[2]
	gpscordsy := args[3]
	//检查参数正确性  
	if objectid == "" || truckid == "" {
		return shim.Error("invalid args")
	}

	if userBytes, err :=stub.GetState(constructOrderKey(objectid)); err ==nil && len(userBytes) !=0 {
		return shim.Error("order already exist")
	}

	orders := &Orders{
		OrderId:    objectid,
		TruckId:    truckid,
		GpscordsX:  gpscordsx,
		GpscordsY:  gpscordsy,
		OrderInfos: make([]string,0),
	}

	userBytes, err := json.Marshal(orders)
	if err != nil{
		return shim.Error(fmt.Sprintf("marshal order error %s",err))
	}
	err = stub.PutState(constructOrderKey(objectid),userBytes)
	if err != nil{
		return shim.Error(fmt.Sprintf("put order error %s",err))
	}
	return shim.Success(nil)
}
func (c *SupplyChain)orderInfoEnroll(stub shim.ChaincodeStubInterface, args []string) pb.Response {
	/*OrderInfoId string `json:"OrderInfoId"`
	L1000TxDes  string `json:"L1000_TxDes"`
	L1100Status string `json:"L1100_Status"`
	L1200Part   string `json:"L1200_Part"`
	L1300Weight string `json:"L1300_Weight"`*/
	//检查参数个数 
	if len(args)!=6{
		return shim.Error("not enough args")
	}
	orderinfoid :=args[0]
	txdes       :=args[1]
	status      :=args[2]
	part        :=args[3]
	weight      :=args[4]
	orderid     :=args[5]
	//检查参数正确性  
	if orderinfoid == "" || orderid == ""{
		return shim.Error("invalid args")
	}
	orderBytes, err := stub.GetState(constructOrderKey(orderid))
	if err != nil ||len(orderBytes) == 0{
		return shim.Error("order not find")
	}

	if orderInfoBytes ,err := stub.GetState(constructOrderInfoKey(orderinfoid));err == nil && len(orderInfoBytes) != 0{
		return  shim.Error("order info already exist")
	}

	orderinfo := &OrderInfo{
		OrderInfoId: orderinfoid,
		L1000TxDes:  txdes,
		L1100Status: status,
		L1200Part:   part,
		L1300Weight: weight,
	}
	orderinfoBytes ,err := json.Marshal(orderinfo)
	if err != nil{
		return  shim.Error(fmt.Sprintf("marshal order info error: %s",err))
	}
	if err := stub.PutState(constructOrderInfoKey(orderinfoid),orderinfoBytes);err != nil{
		return  shim.Error(fmt.Sprintf("save order info error: %s",err))
	}
	//将orderinfoid插入到Order的OrderInfos   []string里面
	order := new(Orders)
	if err := json.Unmarshal(orderBytes, order); err != nil{
		return shim.Error(fmt.Sprintf("unmarshal user error: %s",err))
	}
	order.OrderInfos = append(order.OrderInfos,orderinfoid)
	orderBytes,err = json.Marshal(order)
	if err != nil{
		return shim.Error(fmt.Sprintf("marshal order error: %s",err))
	}
	if err := stub.PutState(constructOrderKey(order.OrderId),orderBytes);err != nil{
		return shim.Error(fmt.Sprintf("update order error:%s",err))
	}
	return shim.Success(nil)
}
func (c *SupplyChain) orderInfoChange(stub shim.ChaincodeStubInterface, args []string) pb.Response {
	//检查参数个数 
	if len(args) !=3{
		return shim.Error("not enough args")
	}
	orderinfoid :=args[0]
	newtxdes    :=args[1]
	newstatus   :=args[2]
	//检查参数正确性  
	if orderinfoid == "" {
		return shim.Error("invalid args")
	}
	orderinfoBytes ,err := stub.GetState(constructOrderInfoKey(orderinfoid))
	if err !=nil || len(orderinfoBytes) == 0{
		return shim.Error("order not found")
	}
	orderinfotochange := OrderInfo{}
	err =json.Unmarshal(orderinfoBytes,&orderinfotochange)
	if err != nil{
		return shim.Error("Unmarshal not success")
	}
	orderinfotochange.L1000TxDes = newtxdes
	orderinfotochange.L1100Status = newstatus
	infoJsonToChange, err := json.Marshal(orderinfotochange)
	if err != nil{
		return shim.Error(fmt.Sprintf("marshal order error %s",err))
	}
	err = stub.PutState(constructOrderInfoKey(orderinfoid),infoJsonToChange)
	if err != nil{
		return shim.Error(fmt.Sprintf("put order error %s",err))
	}
	return shim.Success(nil)
}

func (c *SupplyChain) gpsChange(stub shim.ChaincodeStubInterface, args []string) pb.Response {
	//检查参数个数 
	if len(args) != 3{
		return shim.Error("not enough args")
	}
	//检查参数正确性  
	objectid := args[0]
	newgpscordsx := args[1]
	newgpscordsy := args[2]
	if objectid == "" || newgpscordsx == "" ||newgpscordsy == ""{
		return shim.Error("invalid args")
	}
	fmt.Println("- start change gps ", objectid, newgpscordsx,newgpscordsy)

	orderBytes ,err := stub.GetState (constructOrderKey(objectid))
	if err !=nil || len(orderBytes) == 0{
		return shim.Error("order not found")
	}

	gpstochange := Orders{}
	err = json.Unmarshal(orderBytes,&gpstochange)
	if err !=nil{
		return shim.Error("Unmarshal not success")
	}
	gpstochange.GpscordsX = newgpscordsx
	gpstochange.GpscordsY = newgpscordsy

	gpsJsonToChange, err := json.Marshal(gpstochange)
	if err != nil{
		return shim.Error(fmt.Sprintf("marshal order error %s",err))
	}
	err = stub.PutState(constructOrderKey(objectid),gpsJsonToChange)
	if err != nil{
		return shim.Error(fmt.Sprintf("put order error %s",err))
	}
	return shim.Success(nil)
}

func (c *SupplyChain) queryOrders(stub shim.ChaincodeStubInterface, args []string) pb.Response{
	//检查参数个数 
	if len(args) !=1{
		return shim.Error("not enough args")
	}
	//检查参数正确性  
	objecrId := args[0]
	if objecrId == ""{
		return shim.Error("invalid args")
	}

	orderBytes ,err := stub.GetState (constructOrderKey(objecrId))
	if err !=nil || len(orderBytes) == 0{
		return shim.Error("order not found")
	}
	return shim.Success(orderBytes)
}

func (c *SupplyChain) queryOrdersInfo(stub shim.ChaincodeStubInterface, args []string) pb.Response{
	//检查参数个数 
	if len(args) !=1{
		return shim.Error("not enough args")
	}
	//检查参数正确性  
	orderinfoid := args[0]
	if orderinfoid == ""{
		return shim.Error("invalid args")
	}

	orderBytes ,err := stub.GetState (constructOrderInfoKey(orderinfoid))
	if err !=nil || len(orderBytes) == 0{
		return shim.Error("order not found")
	}
	return shim.Success(orderBytes)
}

func (c *SupplyChain) queryOrdersinfoHistory(stub shim.ChaincodeStubInterface, args []string) pb.Response{
	//检查参数个数 
	if len(args) !=1{
		return shim.Error("not enough args")
	}
	//检查参数正确性  
	orderinfoid :=args[0]
	if orderinfoid == ""{
		return shim.Error("invalid args")
	}
	resultIterator,err := stub.GetHistoryForKey(constructOrderInfoKey(orderinfoid))
	if err != nil {
		return shim.Error("order not found")
	}
	defer resultIterator.Close()
	var buffer bytes.Buffer
	buffer.WriteString("[")

	isWrited := false
	for resultIterator.HasNext(){
		queryResponse, err :=resultIterator.Next()
		if err != nil{
			return shim.Error(err.Error())
		}
		if isWrited ==true{
			buffer.WriteString(",")
		}
		buffer.WriteString("{\"TxId\":")
		buffer.WriteString("\"")
		buffer.WriteString(queryResponse.TxId)
		buffer.WriteString("\"")

		buffer.WriteString(",\"Value\":")
		if queryResponse.IsDelete{
			buffer.WriteString("null")
		}else {
			buffer.WriteString(string(queryResponse.Value))
		}

		buffer.WriteString(",\"Timestamp\":")
		buffer.WriteString("\"")
		buffer.WriteString(time.Unix(queryResponse.Timestamp.Seconds,int64(queryResponse.Timestamp.Nanos)).String())
		buffer.WriteString("\"")

		buffer.WriteString(",\"IsDelete\":")
		buffer.WriteString("\"")
		buffer.WriteString(strconv.FormatBool(queryResponse.IsDelete))
		buffer.WriteString("\"")

		buffer.WriteString("}")
		isWrited = true
	}
	buffer.WriteString("}")
	fmt.Printf("getHistoruForOrders result : \n%s\n", buffer.String())
	fmt.Println("end getHistoryforOrders")

	return shim.Success(buffer.Bytes())
}

func (c *SupplyChain) queryOrderHistory(stub shim.ChaincodeStubInterface, args []string) pb.Response{
	//检查参数个数 
	if len(args) !=1{
		return shim.Error("not enough args")
	}
	//检查参数正确性  
	objectID :=args[0]
	if objectID == ""{
		return shim.Error("invalid args")
	}
	resultIterator,err := stub.GetHistoryForKey(constructOrderKey(objectID))
	if err != nil {
		return shim.Error("order not found")
	}
	defer resultIterator.Close()
	var buffer bytes.Buffer
	buffer.WriteString("[")

	isWrited := false
	for resultIterator.HasNext(){
		queryResponse, err :=resultIterator.Next()
		if err != nil{
			return shim.Error(err.Error())
		}
		if isWrited ==true{
			buffer.WriteString(",")
		}
		buffer.WriteString("{\"TxId\":")
		buffer.WriteString("\"")
		buffer.WriteString(queryResponse.TxId)
		buffer.WriteString("\"")

		buffer.WriteString(",\"Value\":")
		if queryResponse.IsDelete{
			buffer.WriteString("null")
		}else {
			buffer.WriteString(string(queryResponse.Value))
		}

		buffer.WriteString(",\"Timestamp\":")
		buffer.WriteString("\"")
		buffer.WriteString(time.Unix(queryResponse.Timestamp.Seconds,int64(queryResponse.Timestamp.Nanos)).String())
		buffer.WriteString("\"")

		buffer.WriteString(",\"IsDelete\":")
		buffer.WriteString("\"")
		buffer.WriteString(strconv.FormatBool(queryResponse.IsDelete))
		buffer.WriteString("\"")

		buffer.WriteString("}")
		isWrited = true
	}
	buffer.WriteString("}")
	fmt.Printf("getHistoruForOrders result : \n%s\n", buffer.String())
	fmt.Println("end getHistoryforOrders")

	return shim.Success(buffer.Bytes())
}
func main(){
	err := shim.Start(new(SupplyChain))
	if err != nil {
		fmt.Printf("Error starting SupllyChain chaincode: %s",err)
	}
}
