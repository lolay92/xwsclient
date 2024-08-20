#include "ws_common.hpp"

namespace lm {


IClient::IClient(asio::io_context& ioc, const std::string& host):
    m_resolver(ioc),
    m_ws(ioc),
    m_host(std::move(host)) { }

void IClient::fail(const boost::system::error_code& ec, const std::string& failure_location) {
    std::cerr << failure_location << ": " << ec.message() << "\n"; 
}

void IClient::run() {
        std::cout << "Hello from run..." << std::endl; 

        m_resolver.async_resolve(m_host, "80", 
            [self=shared_from_this()](const boost::system::error_code& ec, tcp::resolver::results_type endpoints){
                self->onResolve(ec, endpoints); 
            }); 
}

void IClient::onResolve(const boost::system::error_code& ec, tcp::resolver::results_type endpoints) {
    if (ec) return fail(ec, "DNS resolving error"); 

    beast::get_lowest_layer(m_ws).async_connect(endpoints, 
    [self = shared_from_this()](const boost::system::error_code& ec, tcp::resolver::results_type::endpoint_type endpoint_iter){
        self->onConnect(ec, endpoint_iter); 
    });
}

void IClient::onConnect(const boost::system::error_code& ec, tcp::resolver::results_type::endpoint_type endpoint_iter){
    if (ec) return fail(ec, "Connection error");

    std::cout << "Hello from onConnect..." << std::endl; 

    m_ws.async_handshake(m_host, "/ws",
    [self = shared_from_this()](const boost::system::error_code& ec){
        self->onHandshake(ec);
    });
}

void IClient::onHandshake(const boost::system::error_code& ec) {
    std::cout << "Hello from onHandshake..." << std::endl; 

    if(ec) return fail(ec, "Handshake error");
    subscribe(); 
}


} //namespace lm