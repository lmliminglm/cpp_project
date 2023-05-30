#include "adm_rpc_service.h"
#include <iostream>
#include <chrono>
#include <thread>
#include <iomanip>

static char *cfg = "./client.ini";

D32S reqHandler1(const std::string& reqData, const D32U reqDataSize, std::string& respData, D32U* respDataSize)
{
    std::cout << "app begin reqHandler1" << '\n';

    std::cout << "app recv req data: " << reqData.c_str() << ", size: " << reqDataSize << '\n';

	respData = "serv:1,1,1";
	*respDataSize = 11;

    std::cout << "app end reqHandler1\n";

	return 0;
}

D32S notifyHandler(D16U usInstanceId, const std::string& strData, const D32U uiDataSize)
{
    std::cout << "app begin notifyHandler\n";

    std::cout << "app recv notify, instanceId: " << usInstanceId 
        << ", " << strData.c_str() << ", size: " << uiDataSize << '\n';

    std::cout << "app end notifyHandler\n";

    return 0;
}

D32S sysiOnlinehandler(D16U instanceId)
{
    int ret = -1;

    std::cout << "sysiOnlinehandler "<< std::showbase << std::hex << instanceId <<" is online\n";

	// 注册由服务端通知的事件
    ret = adm_rpc_subscriberEvent(0x101, 0x02, 0x01, notifyHandler);
    if (0 != ret)
    {
        std::cout << "subscribe event failed: " << ret << '\n';
        return -1;
    }

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

    // 注册上线回调
    adm_rpc_registerInstanceOnlineCb(0x101, sysiOnlinehandler);

    ret = adm_rpc_start(nullptr);
    if (0 != ret)
    {
        std::cout << "start failed: " << ret << '\n';
        return -1;
    }

    std::this_thread::sleep_for(std::chrono::seconds(5));

    // 向服务端发送数据
    std::string resp;
	D32U respSize = 0;
    ret = adm_rpc_request_service(0x101, 0x01, 0x01, 5, "how are you?", 13, resp, &respSize);
    if (0 != ret)
    {
        std::cout << "request service failed: " << ret << '\n';
        return -1;
    }

    std::cout << "resp: " << resp << ", respSize: " << respSize << '\n';
    
    while(1)
    {
        std::this_thread::sleep_for(std::chrono::seconds(5));
        std::cout << "/\\/\\/\\/\\/\\/\\/\\" << std::endl;
    }
    return 0;
}