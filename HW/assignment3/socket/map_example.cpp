#include <iostream>
#include <unordered_map>
#include <string>
using namespace std;

int main() {
    unordered_map <string, int> socket_descriptor_table;
    int socket_descriptor = 77;
    socket_descriptor_table["username"] = socket_descriptor;
    cout << socket_descriptor_table["username"] << endl;
}

