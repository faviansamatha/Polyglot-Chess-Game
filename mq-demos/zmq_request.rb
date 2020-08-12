# ruby zmq_request.rb
require 'ezmq'
require 'json'

client = EZMQ::Client.new

arg = 'message'
request = JSON.generate({'string': arg}).encode('utf-8')
response_bytes = client.request request
response = response_bytes.encode('utf-8')
puts response