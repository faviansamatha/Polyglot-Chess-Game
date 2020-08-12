// cargo run --bin zmq_request 

#[macro_use]
extern crate json;

fn main() {
    let ctx = zmq::Context::new();

    let requester = ctx.socket(zmq::REQ).unwrap();
    requester.connect("tcp://127.0.0.1:5555").unwrap();
    
    let arg = "message";
    let data = object!{
       "string": arg
    };
    requester.send(json::stringify(data).as_bytes(), 0).unwrap();
    let response_message = requester.recv_msg(0).unwrap();
    let response = json::parse(response_message.as_str().unwrap()).unwrap();
    println!("{}", response);
}
