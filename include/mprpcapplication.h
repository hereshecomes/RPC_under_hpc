#ifndef rpc_APPLICATION_H
#define rpc_APPLICATION_H

#include "rpcconfig.h"
#include "rpcchannel.h"
#include "rpccontroller.h"

// rpc 框架基础类，类对象只需要实例化一次，故设计为单例
class rpcApplication {
public:
  // 获取单例对象
  static rpcApplication &getInstance();

  static void Init(int argc, char **argv);

  static rpcConfig &GetConfig();

private:
  rpcApplication() {}
  rpcApplication(const rpcApplication &) = delete;
  rpcApplication(rpcApplication &&) = delete;
  bool operator=(const rpcApplication &) = delete;
  bool operator=(rpcApplication &&) = delete;

  static rpcConfig config_;
  static bool isInit_;  // 记录框架是否初始化
};




#endif