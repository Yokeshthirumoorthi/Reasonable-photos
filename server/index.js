const express = require('express')
const app = express()
const port = 3001

const fetchThingAlbumsListResponse = require('./data/fetchThingAlbumsListResponse.json')

app.get('/', (req, res) => {
    res.send('Hello World')
})
app.get('/api/albums/thing/list/', (req, res) => {
    res.send(fetchThingAlbumsListResponse)
})

app.listen(port, () => {
    console.log(`Example app listening at http://localhost:${port}`)
})