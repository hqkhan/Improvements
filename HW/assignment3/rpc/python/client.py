import xmlrpclib

proxy = xmlrpclib.ServerProxy("http://localhost:8080/RPC2")
return_list = proxy.sample.add(5,7)
print "The first array value is",return_list[0],"the second array value is",return_list[1],"and the third array value is",return_list[2] 

