const express = require("express");
const { ApolloClient, ApolloRequest } = require("./ApolloClient");
const path = require("path")
const app = express();

app.use(express.urlencoded({ extended: true }));

const client = new ApolloClient();

app.get("/", (req, res) => {
    res.sendFile(path.join(__dirname, '/index.html'))
    client.connect(5000, '127.0.0.1')
    // const request = new ApolloRequest('P', 'Apollo://127.0.0.1', "{\"hello\": \"hello 123\"}");
    // client.sendRequest(request)
})

app.post('/form', (req, res) => {
    const body = req.body
    const data = JSON.stringify(body)
    const request = new ApolloRequest('P', 'Apollo://127.0.0.1', data);
    client.sendRequest(request)
    res.redirect("/")
})

app.listen(3000, () => console.log("server started"))