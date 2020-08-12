# python3 zmq_reply.py 

import json
import zmq

context = zmq.Context()
socket = context.socket(zmq.REP)
socket.bind("tcp://*:5555")

while True:
    request = json.loads(socket.recv().decode('utf-8'))
    length = len(request['string'])
    response = {'length': length}
    socket.send(json.dumps(response).encode('utf-8'))