//*********__MODULE DEPENDENCIES__**************
var express         = require('express'),
    http            = require('http')

//-//__Express Stuff
var app = express();
require('./config/express')(app)

//-//__Start the server
var server  = http.createServer(app)
server.listen(3000)

//-//__Router Config
require('./config/routes')(app);

console.log('listening on port 3000')

//EXPOSE APPLICATION
exports = module.exports = app