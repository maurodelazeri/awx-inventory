#include <iostream>
#include "src/inventory.h"

using namespace std;

int main(int argc, char **argv, char **envp) {

    std::cout << "\n"
                 "██╗███████╗██████╗ ██████╗ ██╗███╗   ███╗███████╗     █████╗ ██╗    ██╗██╗  ██╗\n"
                 "██║██╔════╝██╔══██╗██╔══██╗██║████╗ ████║██╔════╝    ██╔══██╗██║    ██║╚██╗██╔╝\n"
                 "██║███████╗██████╔╝██████╔╝██║██╔████╔██║█████╗      ███████║██║ █╗ ██║ ╚███╔╝ \n"
                 "██║╚════██║██╔═══╝ ██╔══██╗██║██║╚██╔╝██║██╔══╝      ██╔══██║██║███╗██║ ██╔██╗ \n"
                 "██║███████║██║     ██║  ██║██║██║ ╚═╝ ██║███████╗    ██║  ██║╚███╔███╔╝██╔╝ ██╗\n"
                 "╚═╝╚══════╝╚═╝     ╚═╝  ╚═╝╚═╝╚═╝     ╚═╝╚══════╝    ╚═╝  ╚═╝ ╚══╝╚══╝ ╚═╝  ╚═╝\n"
                 "                                                                               " << std::endl;

    std::cout << "Build generated: " __DATE__ << " " << __TIME__ << endl;

    // Check the number of parameters
    if (argc < 5) {
        // Tell the user how to run the program
        std::cerr << "Usage: " << argv[0] << " 'XXXXX' '/api/v2/device?filters[label]=i-clf1-rmg0&pagination[perPage]=10&pagination[page]=1' '/tmp/host' 120" << std::endl;
        return 1;
    }
    std::istringstream iss( argv[4] );
    int timeout;
    if (iss >> timeout) {
        std::unique_ptr<Inventory> inventory_ = std::make_unique<Inventory>(timeout,argv[1]);
        std::string query = argv[2];
        std::string path =  argv[3];
        inventory_->buildInventory(query,path);
    }else{
        cerr << "Timeout is not a valid number" << endl;
        std::cerr << "Usage: " << argv[0] << " 'XXXXX' '/api/v2/device?filters[label]=i-clf1-rmg0&pagination[perPage]=10&pagination[page]=1' '/tmp/host' 120" << std::endl;
    }

    return 0;
}