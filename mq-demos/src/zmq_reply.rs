// cargo run --bin zmq_reply

#[macro_use]
extern crate json;

fn main() {
    let context = zmq::Context::new();
    let responder = context.socket(zmq::REP).unwrap();

    assert!(responder.bind("tcp://*:5555").is_ok());

    let mut msg = zmq::Message::new();
    loop {
        responder.recv(&mut msg, 0).unwrap();
        let request = json::parse(msg.as_str().unwrap()).unwrap();
        let length = request["string"].as_str().unwrap().len();
        let response = object!{
            "length": length
        };
        responder.send(json::stringify(response).as_bytes(), 0).unwrap();
    }
}
