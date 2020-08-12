# ruby zmq_reply.rb
require 'ezmq'
require 'json'

server = EZMQ::Server.new
server.listen do |message|
  request = JSON.parse(message.encode('utf-8'))
  length = request['string'].length
  response = {:length => length}
  JSON.generate(response).encode('utf-8')
end
