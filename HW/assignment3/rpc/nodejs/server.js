var xmlrpc = require('xmlrpc')

// Creates an XML-RPC server to listen to XML-RPC method calls
var server = xmlrpc.createServer({ host: 'localhost', port: 8080, path: '/RPC2'})
// Handle methods not found
server.on('NotFound', function(method, params) {
  console.log('Method ' + method + ' does not exist');
})
// Handle method calls by listening for events with the method call name
server.on('sample.add', function (err, params, callback) {
  console.log('Method call params for sample.add: ' + params);  
  
  // Send a method response with a value
  callback(null, [7,2.78,'hello world']);
})
console.log('XML-RPC server listening on port 8080')
