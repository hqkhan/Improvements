var xmlrpc = require('xmlrpc')

// Creates an XML-RPC client. Passes the host information on where to
// make the XML-RPC calls.
var client = xmlrpc.createClient({ host: 'localhost', port: 8080, path: '/RPC2'})

// Sends a method call to the XML-RPC server
client.methodCall('sample.add', [5,7], function (error, value) {
   // Results of the method response
   console.log('The first array value is ' + value[0] + ' the second array value is ' + value[1] + ' and the third array value is ' + value[2])
})



//},1)
