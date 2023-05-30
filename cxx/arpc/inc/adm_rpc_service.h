#ifndef ADM_RPC_SERVICE_H
#define ADM_RPC_SERVICE_H

#include "adm_typedefs.h"
#include <string>
#ifdef __cplusplus
extern "C" {
#endif

// vector<byte>
typedef D32S (*ADM_RPC_METHOD_CALLBACK_F)(const std::string& strReqData, const D32U uiReqDataSize, std::string& strRespData, D32U* puiRespDataSize);

typedef D32S (*ADM_RPC_EVENT_CALLBACK_F)(D16U usInstanceId, const std::string& strData, const D32U uiDataSize);

typedef D32S (*ADM_RPC_INSTANCE_STATUS_CALLBACK_F)(D16U usInstanceId);

///< publilc -------

/**
 * @brief 初始化rpc, 初始化OTA配置文件
 * 
 * @param filename [in]     配置文件的绝对路径
 * @return D32S     0:Successed, None-0:Failed
 */
D32S adm_rpc_init(void* pPriv);

/**
 * @brief 启动rpc服务
 * 
 * @param priv     [in] 	目前没用
 * @return D32S    0:Successed, None-0:Failed
 */
D32S adm_rpc_start(void* pPriv); 

/**
 * @brief 停止rpc服务
 * 
 * @param priv     [in] 	目前没用
 * @return D32S    0:Successed, None-0:Failed
 */
D32S adm_rpc_stop(void* pPriv);

///< ------for server begin--------

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
 * @brief   提供事件, 提供后客户端可订阅该事件
 * 
 * @param instanceId        [IN]   	D16U  instanceId 
 * @param serviceId         [IN]   	D16U  serviceId
 * @param methodId          [IN]   	D16U  eventId 
*/
void adm_rpc_offerEvent(D16U usInstanceId, D16U usServiceId, D16U usEventId); 

/**
 * @brief   事件通知
 * 
 * @param instanceId        [IN]   	D16U  instanceId 
 * @param serviceId         [IN]   	D16U  serviceId
 * @param methodId          [IN]   	D16U  eventId 
 * @param data          	[IN]   	const DCHAR*  notify data 
 * @param dataSize          [IN]   	D32U  notify dataSize 
*/
void adm_rpc_notifyEvent(D16U usInstanceId,D16U usServiceId, D16U usEventId, const std::string& strData, D32U uiDataSize); 

///< ---------for server end-------

///< ---------for client begin--------
/**
 * @brief   订阅服务端提供的事件, 注册该事件对应的处理函数
 * 
 * @param instanceId       [IN]   	D16U  instanceId 
 * @param serviceId        [IN]   	D16U  serviceId
 * @param eventId          [IN]   	D16U  eventId 
 /// ADM_RPC_EVENT_CALLBACK_F
*/
D32S adm_rpc_subscriberEvent(D16U usInstanceId, D16U usServiceId, D16U usEventId, ADM_RPC_EVENT_CALLBACK_F eventHandler);

/**
 * @brief   服务请求, 同步接口
 * @note    注意 !!!, respData rpc 申请内存, 应用层释放, 释放函数adm_free
 * 
 * @param instanceId        [IN]   	D16U  instanceId 
 * @param serviceId         [IN]   	D16U  serviceId
 * @param methodId          [IN]   	D16U  methodId 
 * @param timeOut      		[IN]   	D16U  timeOut, The unit is the second
 * @param reqData        	[IN]   	const DCHAR* reqData 
 * @param reqDataSize       [IN]   	D32U reqDataSize
 * @param respData         	[OUT]  	DCHAR* respData. attention !!!,  app malloc, app delete
 * @param respDataSize      [OUT]   D32U* respDataSize
 * @return D32S             [OUT]  	D32S returncode
 									0  			///< 成功;
 									2001		///< 实例不在线;
 									2002		///< 实例在线,服务不在线;
 									2003		///< 请求服务超时;
*/
D32S adm_rpc_request_service(D16U usInstanceId, D16U usServiceId, D16U usMethodId, D16U usTimeOut, 
										const std::string& strReqData, const D32U uiReqDataSize, std::string& strRespData, D32U* puiRespDataSize);

///< ----------for client end------------

///< 扩展接口
/**
 * @brief   关键事件, 检查期待的客户端是否已订阅
 * 
 * @param instanceId        [IN]    D16U  instanceId
 * @param serviceId         [IN]    D16U  serviceId
 * @param messageId         [IN]    D16U  eventid
 * @param instanceId      	[IN]    D16U  checked instanceId
 * @return D32S             [OUT]   1:subed, 0:not sub
 */
D32S adm_rpc_checkIfClientSubedEvent(D16U usInstanceId, D16U usServiceId, D16U usEventId, D16U usClientId);

/**
 * @brief   对于关注的实例上下线行为, 注册回调处理函数
 * 
 * @param instanceId        [IN]    D16U  instanceId
 * @param ADM_RPC_INSTANCE_BEHAVIOR_CALLBACK_F         [IN]    D16U  serviceId
 * @return D32S             [OUT]   1:ok, 0:fail
 */
D32S adm_rpc_registerInstanceOnlineCb(D16U usInstanceId, ADM_RPC_INSTANCE_STATUS_CALLBACK_F instanceOnlineHandler);

D32S adm_rpc_registerInstanceOfflineCb(D16U usInstanceId, ADM_RPC_INSTANCE_STATUS_CALLBACK_F instanceOfflineHandler);


/**
 * @brief 使用SSL连接时，配置PKCS-8证书私钥的加密口令
 * @note  当SSL使用PCKS-8加密私钥时，通过该接口配置加密口令
 *
 * @param password    [In] DHCAR *     PKCS-8 私钥的加密口令
 */
void adm_rpc_setSSLKeyPasswd(DCHAR* pcPassword);

#define ADM_RPC_DEFAULT_SDK_VERSION      "tools_default_version_1.1.0"       //!< 定义默认的软件版本号

/*!
 *******************************************************************************
 * rpc get software version number
 * \return	version format: ${PROJECT_NAME}_${ENV_PLATFORM}_${ADM_SDK_VERSION}_${COMPILE_DATE}_${GIT_COMMITID})
 *******************************************************************************
 */
DCHAR* adm_rpc_getSdkVersion(void);

#ifdef __cplusplus
}
#endif


#endif // ADM_RPC_SERVICE_H


