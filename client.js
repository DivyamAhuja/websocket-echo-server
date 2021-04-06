const prompt = require('prompt-sync')({sigint: true});

const ws = require('ws');



let client = new ws("ws+unix:///tmp/meow.sock", "ws_echo", {perMessageDeflate: false});
client.onopen = () => {
    client.onmessage = (msg) => {
        console.log(`message received: ${msg}`);
    }

    while (true) {
        let input = prompt('Enter message to send: ');
        console.log(`Sending message: ${input}`);
        client.send(input);
    }
    client.close()
}
