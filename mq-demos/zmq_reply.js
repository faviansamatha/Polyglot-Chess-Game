// node zmq_reply.js
const zmq = require("zeromq")

// UTF-8 handing from https://stackoverflow.com/a/13691499
function encode_utf8(s) {
  return unescape(encodeURIComponent(s));
}
function decode_utf8(s) {
  return decodeURIComponent(escape(s));
}

// adapted from https://github.com/zeromq/zeromq.js/#reqrep
async function run() {
  const rep = new zmq.Reply

  await rep.bind("tcp://127.0.0.1:5555")

  for await (const [msg] of rep) {
    const request = JSON.parse(decode_utf8(msg));
    
    const len = request.string.length;
    const response = {'length': len};
    
    const resp_bytes = encode_utf8(JSON.stringify(response));
    await rep.send(resp_bytes);
  }
}

run();