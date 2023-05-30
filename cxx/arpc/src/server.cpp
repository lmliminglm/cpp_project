#include "adm_rpc_service.h"
#include "abup_rpc_service.h"
#include <iostream>
#include <chrono>
#include <thread>

static char *cfg = "./server.ini";

D32S reqHandler1(const std::string& reqData, const D32U reqDataSize, std::string& respData, D32U* respDataSize)
{
    std::cout << "app begin reqHandler1" << '\n';

	//sleep(7);

    std::cout << "app recv req data: " << reqData.c_str() << ", size: " << reqDataSize << '\n';

	respData = "fine, thanks";
	*respDataSize = 13;

    std::cout << "app end reqHandler1\n";

	return 0;
}

D32S reqHandler12(const DCHAR* reqData, const D32U reqDataSize, DCHAR* respData, D32U* respDataSize)
{ 
  return 0;
}

int main()
{
    int ret = -1;

    ret = adm_rpc_init(cfg);
    if (0 != ret)
    {
        std::cout << "init failed: " << ret << '\n'; 
        return -1;
    }

    // 注册来自客户端的请求
    adm_rpc_registerServMethodHandler(0x101, 0x01, 0x01, reqHandler1);

    //注册来自客户端的请求
    abup_rpc_registerServMethodHandler(0x101, 0x01, 0x01, reqHandler12);


    // 提供事件供客户端注册
    adm_rpc_offerEvent(0x101, 0x02, 0x01);

    ret = adm_rpc_start(nullptr);
    if (0 != ret)
    {
        std::cout << "start failed: " << ret << '\n';
        return -1;
    }

    std::this_thread::sleep_for(std::chrono::seconds(5));

    // 向客户端推送消息
    
    int len = 100;
    char *buff = (char *)malloc(len);
    if (nullptr == buff)
    {
        std::cerr << "malloc failed\n";
        return -1;
    }
    snprintf(buff, len, "%s", "Happy Every Day!");
    std::cout << "begin notify: " << buff <<  '\n';
    adm_rpc_notifyEvent(0x101, 0x02, 0x01, buff, len);
    std::cout << "end notify " <<  '\n';
    free(buff);

    while(1)
    {
        std::this_thread::sleep_for(std::chrono::seconds(5));
        std::cout << "/\\/\\/\\/\\/\\/\\/\\" << std::endl;
    }
    return 0;
}