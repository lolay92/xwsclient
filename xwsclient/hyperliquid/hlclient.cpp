#include "hlclient.hpp"

namespace lm {

/**
 * @brief Concrete Hyperliquid client based on the generic IClient interface class.
 * 
 * @todo
 * - Handle the interval case parameter
 * - Add a unsunscribe method to gracefully close the socket
 */
HlClient::HlClient(asio::io_context& ioc, const std::string& host,
            const std::string& user_address, const std::string& coin_symbol): 
            IClient(ioc, host), 
            m_user_address(user_address),
            m_coin_symbol(coin_symbol) {}

void HlClient::subscribe() {
    // Hyperliquid subscribe Msg structure

    json subscription_msg = {
        {"method", "subscribe"},
        {"subscription", {
            {"type", "candle"},
            {"coin", "SOL"},
            {"interval", "1m"}
        }}
    };

    // asio::buffer is constructible with string data parameter
    // Since I want onWrite callable to stay a protected member
    // using a lambda func and calling the "onWrite" method from the object pointer 
    // does not work. 

    m_ws.async_write(asio::buffer(subscription_msg.dump()), 
        boost::bind(&HlClient::onWrite, 
                    std::static_pointer_cast<HlClient>(shared_from_this()),
                    boost::placeholders::_1,
                    boost::placeholders::_2));
}

void HlClient::onWrite(const boost::system::error_code& ec, [[maybe_unused]] std::size_t bytes) {
    if (ec) return fail(ec, "Writing the subscription message failed");

    m_ws.async_read(m_buffer,
        boost::bind(&HlClient::onRead,
                    std::static_pointer_cast<HlClient>(shared_from_this()),
                    boost::placeholders::_1,
                    boost::placeholders::_2)); 
}

void HlClient::onRead(const boost::system::error_code& ec, [[maybe_unused]] std::size_t bytes) {
    if (ec) return fail(ec, "Reading the response failed");

    std::cout << beast::buffers_to_string(m_buffer.data()) << "\n";
    m_buffer.consume(m_buffer.size()); 

    m_ws.async_read(m_buffer,
        boost::bind(&HlClient::onRead,
                    std::static_pointer_cast<HlClient>(shared_from_this()),
                    boost::placeholders::_1,
                    boost::placeholders::_2)); 
}

} // namespace lm