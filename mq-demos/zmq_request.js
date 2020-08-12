// node zmq_request.js
const zmq = require("zeromq");

// UTF-8 handing from https://stackoverflow.com/a/13691499
function encode_utf8(s) {
  return unescape(encodeURIComponent(s));
}
function decode_utf8(s) {
  return decodeURIComponent(escape(s));
}

// adapted from https://github.com/zeromq/zeromq.js/#reqrep
async function run() {
  const sock = new zmq.Request;
  sock.connect("tcp://127.0.0.1:5555");
  
  const arg = "message";
  const request = encode_utf8(JSON.stringify({"string": arg}));
  await sock.send(request)

  const [response_bytes] = await sock.receive()
  const response = JSON.parse(decode_utf8(response_bytes));
  console.log(response);
}

run()