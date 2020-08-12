# python3 zmq_request.py 

import json
import zmq

context = zmq.Context()
socket = context.socket(zmq.REQ)
socket.connect("tcp://localhost:5555")

arg = 'message'
request = json.dumps({'string': arg}).encode('utf8')
socket.send(request)
response_bytes = socket.recv()
response = json.loads(response_bytes.decode('utf-8'))
print(response)
