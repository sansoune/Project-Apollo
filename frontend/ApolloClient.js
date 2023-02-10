const net = require('net');

const PORT = 5000;
const BUFFER_SIZE = 1024;

class ApolloRequest {
  constructor(type, resource, data) {
    this.type = type;
    this.resource = resource;
    this.data = data;
  }
}

class ApolloResponse {
  constructor(status, size, data, code) {
    this.status = status;
    this.size = size;
    this.data = data;
    this.code = code;
  }
}
class ApolloClient {
  constructor() {
    this.client = new net.Socket();
  }


  connect(port, host) {
    this.client.connect(port, host, () => console.log("connected to server"))
    this.client.on('data', (data) => {
      const response = new ApolloResponse();
      response.status = data.toString('utf8', 0, 1);
      response.size = data.readUInt32BE(1);
      response.data = data.toString('utf8', 5, 19);
      response.code = data.readInt32BE(16);
      console.log(`${response.status} ${response.size} ${response.data} ${response.code}`);
      console.log(data.toJSON());
    });
    this.client.on('close', () => {
      console.log('Connection closed');
    });
  }

  sendRequest(request) {
    const requestBuffer = Buffer.alloc(BUFFER_SIZE);
    requestBuffer.write(request.type);
    requestBuffer.write(request.resource, 1);
    requestBuffer.write(request.data, 21);
    this.client.write(requestBuffer);
  }

}

module.exports = { ApolloClient, ApolloRequest }