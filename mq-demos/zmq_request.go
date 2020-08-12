// go run zmq_request.go
package main

import (
	"encoding/json"
	"fmt"
	zmq "github.com/pebbe/zmq4"
)

func main() {
	requester, _ := zmq.NewSocket(zmq.REQ)
	defer requester.Close()
	requester.Connect("tcp://localhost:5555")

	arg := "message"
	request, _ := json.Marshal(map[string]string{"string": arg})
	requester.SendBytes(request, 0)
	reply, _ := requester.RecvBytes(0)
	var response map[string]int
	json.Unmarshal(reply, &response)
	fmt.Printf("%v\n", response)
}
