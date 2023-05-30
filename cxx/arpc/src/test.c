#include "adm_typedefs.h"


// vector<byte>
typedef D32S (*ADM_RPC_METHOD_CALLBACK_F)(const std::string& strReqData, const D32U uiReqDataSize, std::string& strRespData, D32U* puiRespDataSize);

// vector<byte>
typedef D32S (*ABUP_RPC_METHOD_CALLBACK_F)(const DCHAR* strReqData, const D32U uiReqDataSize, const DCHAR* strRespData, D32U* puiRespDataSize);

/**
 * @brief   提供服务方法, 注册该方法对应的处理函数
 * 
 * @param instanceId        [IN]   	D16U  instanceId 
 * @param serviceId         [IN]   	D16U  serviceId
 * @param methodId          [IN]   	D16U  methodId 
 * @param methodHandler     [IN]   	ADM_RPC_METHOD_CALLBACK_F 
*/
void adm_rpc_registerServMethodHandler(D16U usInstanceId, D16U usServiceId, D16U usMethodId, ADM_RPC_METHOD_CALLBACK_F methodHandler);

/**
 * @brief 封装adm_rpc_registerServMethodHandler接口
 * 
 */
void abup_rpc_registerServMethodHandler(D16U usInstanceId, D16U usServiceId, D16U usMethodId, ABUP_RPC_METHOD_CALLBACK_F methodHandler)
{
    ADM_RPC_METHOD_CALLBACK_F tmp = (ADM_RPC_METHOD_CALLBACK_F)methodHandler;
    
    adm_rpc_registerServMethodHandler(usInstanceId, usServiceId, usMethodId, tmp);
}
    




int add(int a, int b)
{
    int sum = 0;

    sum = a+b;
    return sum;
}

int main()
{
    int sumtmp = 0;

    sumtmp = add(10,20);

    if(sumtmp>10)
    {
        sumtmp = 33;
    }

    return 0;

}

