#include "../common/ws_common.hpp"

namespace lm {


class HlClient : public IClient {

    protected:
        void subscribe() override; 
        void onWrite(const boost::system::error_code& ec, [[maybe_unused]] std::size_t bytes_transferred) override;
        void onRead(const boost::system::error_code& ec, [[maybe_unused]] std::size_t bytes_transferred) override;
    
    public:
        explicit HlClient(asio::io_context& ioc, const std::string& host);
};

} // namespace lm