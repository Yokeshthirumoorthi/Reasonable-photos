const express = require('express')
const app = express()
const port = 3001

const fetchThingAlbumsListResponse = require('./data/fetchThingAlbumsListResponse.json')
const loginResponse = require('./data/loginResponse.json')

app.get('/', (req, res) => {
    res.send('Hello World')
})
app.get('/api/albums/thing/list/', (req, res) => {
    res.send(fetchThingAlbumsListResponse)
})

app.post('/api/auth/token/obtain/', (req, res) => {
    res.send(loginResponse)
})

app.get('/api/auth/token/obtain/', (req, res) => {
    res.send(loginResponse)
})

app.listen(port, () => {
    console.log(`Example app listening at http://localhost:${port}`)
})