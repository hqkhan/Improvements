#include <cassert>
#include <stdexcept>
#include <iostream>
#include <unistd.h>

#include "xmlrpc-c/base.hpp"
#include "xmlrpc-c/registry.hpp"
#include "xmlrpc-c/server_abyss.hpp"

using namespace std;

#define SLEEP(seconds) sleep(seconds);


class sampleAddMethod : public xmlrpc_c::method {
public:
    sampleAddMethod() {
        // signature and help strings are documentation -- the client
        // can query this information with a system.methodSignature and
        // system.methodHelp RPC.
        this->_signature = "A:ii";
            // method's result and two arguments are integers
        this->_help = "This method adds two integers together";
    }
    void
    execute(xmlrpc_c::paramList const& paramList,
            xmlrpc_c::value *   const  retvalP) {
        
        int const addend(paramList.getInt(0));
        int const adder(paramList.getInt(1));

        paramList.verifyEnd(2);

        vector<xmlrpc_c::value> arrayData;
        arrayData.push_back(xmlrpc_c::value_int(7));
        arrayData.push_back(xmlrpc_c::value_double(2.78));
        arrayData.push_back(xmlrpc_c::value_string("hello world"));
        
        // Make an XML-RPC array out of it
        xmlrpc_c::value_array array1(arrayData);
        
        *retvalP = array1;

        // Sometimes, make it look hard (so client can see what it's like
        // to do an RPC that takes a while).
        if (adder == 1)
            SLEEP(2);
    }
};



int 
main(int           const, 
     const char ** const) {

    try {
        xmlrpc_c::registry myRegistry;

        xmlrpc_c::methodPtr const sampleAddMethodP(new sampleAddMethod);

        myRegistry.addMethod("sample.add", sampleAddMethodP);
        
        xmlrpc_c::serverAbyss myAbyssServer(
            xmlrpc_c::serverAbyss::constrOpt()
            .registryP(&myRegistry)
            .portNumber(8080));
        
        myAbyssServer.run();
        // xmlrpc_c::serverAbyss.run() never returns
        assert(false);
    } catch (exception const& e) {
        cerr << "Something failed.  " << e.what() << endl;
    }
    return 0;
}
