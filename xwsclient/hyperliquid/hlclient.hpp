#ifndef HLCLIENT_HPP
#define HLCLIENT_HPP

#include "../common/ws_common.hpp"
#include <nlohmann/json.hpp>

namespace lm {

using json = nlohmann::json; 

enum class SubscriptionType {
    ALLMIDS,
    NOTIFICATION,
    WEBDATA2,
    L2BOOK,
    TRADES,
    CANDLE,
    ORDERUPDATES,
    USEREVENTS,
    USERFILLS,
    USERFUNDINGS
};

class HlClient : public IClient {

    protected:
        std::string m_user_address, m_coin_symbol;
        void subscribe() override; 
        void onWrite(const boost::system::error_code& ec, [[maybe_unused]] std::size_t bytes_transferred) override;
        void onRead(const boost::system::error_code& ec, [[maybe_unused]] std::size_t bytes_transferred) override;
    
    public:
        explicit HlClient(asio::io_context& ioc, const std::string& host,
            const std::string& user_address, const std::string& coin_symbol);
        
        template<typename... Args>
        static json subMessageFactory(const std::string& method, Args&&... args) {
            return {
                {"method", method},
                {"subscription", {std::forward<Args>(args)...} }
            }; 
        }

        json createSubMessage(const SubscriptionType& subscription_typ) {
            switch(subscription_typ){
                case SubscriptionType::ALLMIDS:
                    return subMessageFactory("subscribe",
                    std::make_pair("type", "allMids"));

                case SubscriptionType::NOTIFICATION:
                    return subMessageFactory("subscribe",
                    std::make_pair("type", "notification"),
                    std::make_pair("user", m_user_address));

                case SubscriptionType::WEBDATA2:
                    return subMessageFactory("subscribe",
                    std::make_pair("type", "webData2"),
                    std::make_pair("user", m_user_address));

                case SubscriptionType::L2BOOK:
                    return subMessageFactory("subscribe",
                    std::make_pair("type", "l2Book"),
                    std::make_pair("coin", m_coin_symbol));

                case SubscriptionType::TRADES:
                    return subMessageFactory("subscribe",
                    std::make_pair("type", "trades"),
                    std::make_pair("coin", m_coin_symbol));

                case SubscriptionType::CANDLE:
                    return subMessageFactory("subscribe",
                    std::make_pair("type", "candle"),
                    std::make_pair("coin", m_coin_symbol),
                    std::make_pair("interval", "1m"));

                case SubscriptionType::ORDERUPDATES:
                    return subMessageFactory("subscribe",
                    std::make_pair("type", "orderUpdates"),
                    std::make_pair("user", m_user_address));

                case SubscriptionType::USEREVENTS:
                    return subMessageFactory("subscribe",
                    std::make_pair("type", "userEvents"),
                    std::make_pair("user", m_user_address));

                case SubscriptionType::USERFILLS:
                    return subMessageFactory("subscribe",
                    std::make_pair("type", "userFills"),
                    std::make_pair("user", m_user_address));

                case SubscriptionType::USERFUNDINGS:
                    return subMessageFactory("subscribe",
                    std::make_pair("type", "userFundings"),
                    std::make_pair("user", m_user_address));

                default:
                    std::cerr << "Subscription Type error\n"; 
            }
        }
};

} // namespace lm

#endif