This is the template for CMPT 383 projects, providing some basics to get started with various languages in a a consistent environment.


## Starting the VM

This repository is designed to deploy itself into a virtual machine, managed by [Vagrant](https://www.vagrantup.com/downloads.html) and [VirtualBox](https://www.virtualbox.org/wiki/Downloads). You should be able to change into the repository directory and type:
```sh
vagrant up
```
&hellip; to bring up a virtual machine. As part of creating the VM, Vagrant will run the Chef cookbook provided (described below).

Once you have the VM up, you can SSH into it and start running commands (and press ctrl-D to exit):
```sh
vagrant ssh
```

If you'd like to shut down or destroy the VM, you can do it with these commands:
```sh
vagrant halt
vagrant destroy
```


## The Cookbook

The [Chef cookbook](https://docs.chef.io/cookbooks/) that is provided in `cookbooks/polyglot/recipes/default.rb` and can be edited as necessary.

Most of the recipe is commented out: you can un-comment parts as necessary to install language tools or libraries as described there. If you need other libraries (e.g. Ruby on Rails, a Go package for some numeric computation), hopefully you can do it by analogy with the commented code in the recipe.

If you would like to re-run the recipe, you can ask Vagrant to do that:
```sh
vagrant provision
```

## Hello Worlds

In `hello-world/`, there are &ldquo;hello world&rdquo; programs for all of the languages that the Chef recipe can install. At the top of each program is a comment indicating how to run it.

Hopefully this will at least get things started running code in various languages in this context.


## Messaging Demo Code

In `mq-demos/`, you will find several examples of working with message queues. All of the programs start with a comment that indicates the command to run them.

All of the RPC examples do the same basic operation: do a remote procedure call by passing a [JSON](https://en.wikipedia.org/wiki/JSON) string. For each demo, the request includes a string; we ask the remote code to calculate its length, and return the result as a JSON response. These should be easily extensible to have whatever information is needed in the request/response messages, and whatever logic in between.


### ZeroMQ Demo Code

The `zmq_*` programs are examples of an RPC call using [ZeroMQ](https://zeromq.org/). In each case, the same operation is done: the `zmq_request.*` programs create a request consisting of a single argument (called `"string"`), encode it as JSON, make a ZeroMQ request to localhost port 5555, get the JSON response, decode the JSON, and print the result.

The `zmq_reply.*` programs start a server listening on port 5555. When a request comes in, they decode the JSON, extract the argument (`"string"`), calculate the length of the string, create a response (containing the `"length"`), encode it as JSON, and send it back to the requester.

All of these programs can interact with each other: you can start any of the `zmq_reply.*` programs, and run any of the `zmq_request.*` programs to ask it to calculate a string length.


### RabbitMQ Demo Code

Similarly, the `amqp_*` programs are examples of an RPC call using [RabbitMQ](https://www.rabbitmq.com/) (using its underlying [AMQP](https://en.wikipedia.org/wiki/Advanced_Message_Queuing_Protocol) protocol). All of these require the RabbitMQ server (Ubuntu package `rabbitmq-server`) installed, and assume they can connect with no username/password (which is the default).

The `amqp_client.*` programs create a request consisting of a single argument (called `"string"`), encode it as JSON, make a request through RabbitMQ in the `rpc_queue` queue, get the JSON response, decode the JSON, and print the result.

The `amqp_server.*` programs all listen on the `rpc_queue` queue. When a request comes in, they decode the JSON, extract the argument (`"string"`), calculate the length of the string, create a response (containing the `"length"`), encode it as JSON, and send it back to the requester.

All of these programs can interact with each other: you can start any of the `amqp_server.*` programs, and run any of the `amqp_client.*` programs to ask it to calculate a string length.


## SWIG Example

The `swig-demo/` directory contains an example of using [SWIG](http://www.swig.org/) to call a C function from another language. The README file in that directory gives details on how to build and run the code.