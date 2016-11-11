#include <cstdlib>
#include <string>
#include <iostream>
#include <xmlrpc-c/girerr.hpp>
#include <xmlrpc-c/base.hpp>
#include <xmlrpc-c/client_simple.hpp>

using namespace std;

int
main(int argc, char **) {

    if (argc-1 > 0) {
        cerr << "This program has no arguments" << endl;
        exit(1);
    }

    try {
        xmlrpc_c::clientSimple myClient;
        xmlrpc_c::value result;
        string const serverUrl("http://localhost:8080/RPC2");
        string const methodName("sample.add");

        myClient.call(serverUrl, methodName, "ii", &result, 5, 7);
        
        xmlrpc_c::value_array array1(result);
        vector<xmlrpc_c::value> const param1Value(array1.vectorValueValue());
        int const int_value = xmlrpc_c::value_int(param1Value[0]);
	double const double_value = xmlrpc_c::value_double(param1Value[1]);  
	string const string_value = xmlrpc_c::value_string(param1Value[2]);

	cout << "The first array value is " << int_value << " the second array value is " << double_value << " and the third array value is " << string_value << endl;

    } catch (exception const& e) {
        cerr << "Client threw error: " << e.what() << endl;
    } catch (...) {
        cerr << "Client threw unexpected error." << endl;
    }

    return 0;
}
