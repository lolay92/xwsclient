add_library(hlclient STATIC common/ws_common.cpp hyperliquid/hlclient.cpp)
target_link_libraries(hlclient PRIVATE cxx_setup)