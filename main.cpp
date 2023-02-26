#include "fasty/formats/json/Json.h"
#include "fasty/net/http/AsyncHttpSession.h"
#include "fasty/net/http/HttpServer.h"
#include "fasty/protocol/http/HttpApi.h"
#include "fasty/net/tcp/TcpConnect.h"
#include "fasty/protocol/http/HttpApiRequest.h"
#include "fasty/protocol/http/HttpRequest.h"
#include "fasty/protocol/http/HttpResponse.h"
#include "fasty/protocol/http/HttpRouter.h"
#include "fasty/protocol/http/HttpRouterClouser.h"
#include "fasty/sync/Channel.h"
#include "fasty/sync/IO.h"
#include <chrono>
#include <filesystem>
#include <fstream>
#include <istream>
#include <memory>
#include <ostream>
#include <string_view>
#include <thread>
#include "fasty/protocol/http/HttpApi.h"
#include <iostream>

int main () {

    fasty::IO io(6);

    auto [socket, error] = fasty::tcpConnect(io.context(), "10.56.77.157", 8080);

    if (error) {
        return 0;
    }

    std::make_shared<fasty::HttpApi>(std::move(socket))
    -> use([](fasty::HttpApiRequest& request){
        std::cout << request << std::endl;
    })
    -> send({
        .method = "GET",
        .route = "/hi",
        .queries = {
            {"user", "Vasiliy"},
            {"lang", "ru"}
        },
        .headers = {
            {"Content-Type", "application/json"},
            {"XXX-KEY", "XXXXXXX"}
        },
        .content = fasty::toJson("HI"),
    }, 
    [](fasty::HttpApiResponse& response) {
        std::cout << response << std::endl;
    });
    
   while(true) {
    std::this_thread::yield();
   }
 return 0;
}