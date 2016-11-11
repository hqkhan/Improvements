import xmlrpclib
from SimpleXMLRPCServer import SimpleXMLRPCServer

def sample_add(var1,var2):
	int_value = 7
	double_value = 2.79
	string_value = "hello_world"
	return_list = [int_value,double_value,string_value];	
	return return_list

server = SimpleXMLRPCServer(("localhost", 8080))
print "Listening on port 8080..."
server.register_function(sample_add, "sample.add")
server.serve_forever()
