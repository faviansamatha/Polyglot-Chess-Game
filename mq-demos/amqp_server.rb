# ruby amqp_server.rb
# based on https://www.rabbitmq.com/tutorials/tutorial-six-ruby.html

require 'bunny'
require 'json'

class RpcServer
  def initialize
    @connection = Bunny.new
    @connection.start
    @channel = @connection.create_channel
  end

  def start(queue_name)
    @queue = channel.queue(queue_name)
    @exchange = channel.default_exchange
    subscribe_to_queue
  end

  def stop
    channel.close
    connection.close
  end

  def loop_forever
    # This loop only exists to keep the main thread
    # alive. Many real world apps won't need this.
    loop { sleep 5 }
  end

  private

  attr_reader :channel, :exchange, :queue, :connection

  def subscribe_to_queue
    queue.subscribe do |_delivery_info, properties, payload|
      request = JSON.parse(payload.encode('utf-8'))
      puts request
      result = get_length request

      exchange.publish(
        JSON.generate(result).encode('utf-8'),
        routing_key: properties.reply_to,
        correlation_id: properties.correlation_id
      )
    end
  end

  def get_length(request)
    length = request['string'].length
    {:length => length}
  end
end

begin
  server = RpcServer.new

  puts 'Awaiting RPC requests'
  server.start('rpc_queue')
  server.loop_forever
rescue Interrupt => _
  server.stop
end