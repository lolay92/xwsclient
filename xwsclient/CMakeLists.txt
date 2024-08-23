add_library(hlclient STATIC common/ws_common.cpp hyperliquid/hlclient.cpp)
target_include_directories(hlclient PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(hlclient PUBLIC cxx_setup)