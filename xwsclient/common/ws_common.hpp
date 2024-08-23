#ifndef WS_COMMON_HPP
#define WS_COMMON_HPP


#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/bind.hpp>
#include <iostream>
#include <string>

namespace lm {

namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace ws = beast::websocket;        // from <boost/beast/websocket.hpp>
namespace asio = boost::asio;            // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>

using error_code = boost::system::error_code; 


/**
 * @brief Generic IClient class base to implement ApiClient from different providers 
 * 
 * Override the "subscribe_()" private method according to the provider subscribe message structure
 * 
 * run --> resolve dns --> connect --> handshake --> write/subscribe --> read
 * 
 * @todo Maybe think of a shared state that will handle the subscribe / unsubscribe ticker 
 */
class IClient : public std::enable_shared_from_this<IClient> {
    protected:
        ws::stream<beast::tcp_stream> m_ws;
        tcp::resolver m_resolver; 
        std::string m_host;
        beast::flat_buffer m_buffer; 

        void onResolve(const error_code&, tcp::resolver::results_type); 
        void onConnect(const error_code&, tcp::resolver::results_type::endpoint_type); 
        void onHandshake(const error_code&);

        virtual void subscribe() = 0;  
        virtual void onWrite(const error_code&, [[maybe_unused]] std::size_t bytes_transferred) = 0; 
        virtual void onRead(const error_code&, [[maybe_unused]] std::size_t bytes_transferred) = 0; 

    public:
        explicit IClient(asio::io_context& ioc, const std::string& host); 
        void fail(const error_code& ec, const std::string& failure_location);
        void run(); 
        virtual ~IClient() = default; 
};

} // namespace lm

#endif