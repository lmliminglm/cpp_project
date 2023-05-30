#include "abup_rpc_service.h"
#include "adm_rpc_service.h"
#include <string>



D32S abup_rpc_init(void* pPriv)
{
    return adm_rpc_init(pPriv);
}

D32S abup_rpc_start(void* pPriv)
{
    return adm_rpc_start(pPriv);
}

D32S abup_rpc_stop(void* pPriv)
{
    return adm_rpc_stop(pPriv);
}


D32S callback(const std::string& strReqData, const D32U uiReqDataSize, std::string& strRespData, D32U* puiRespDataSize)
{
    
}

void abup_rpc_registerServMethodHandler(
    D16U usInstanceId, 
    D16U usServiceId, 
    D16U usMethodId, 
    ABUP_RPC_METHOD_CALLBACK_F methodHandler)
{

    




    return adm_rpc_registerServMethodHandler(usInstanceId, usServiceId, usMethodId, );
}