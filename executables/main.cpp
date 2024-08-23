#include "../xwsclient/hyperliquid/hlclient.hpp" 

using namespace lm; 

int main() {
    const std::string host = "api.hyperliquid.xyz"; 

    try {
        std::cout << "Setting up..." << "\n"; 
        asio::io_context ioc;
        std::make_shared<HlClient>(ioc, host, "fjskdqyfgyqfgqdgfbiyq", "SOL")->run();
        ioc.run();
    }
    catch (std::exception const& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}