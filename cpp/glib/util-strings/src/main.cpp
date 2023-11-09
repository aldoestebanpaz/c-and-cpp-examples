#include <iostream>
#include <glib.h>


void sample_split() {
    std::cout << "[+] Example of split functions" << std::endl;
    
    gchar** fields = g_strsplit (":a:bc::d:", ":", -1);

    std::cout << "Items: " << std::endl;
    for(char** f = fields; *f; ++f) {
        std::cout << "'" << *f << "' " << std::endl;
    }

    g_strfreev (fields);
}


int main() {

    sample_split();

    return 0;
}
