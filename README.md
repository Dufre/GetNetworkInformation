# GetNetworkInformation
qt下获取主机名，IP地址、网关地址
程序是从网上下的，稍作改动，还有很多不完善的地方，自己也是刚开始学qt，欢迎大神来指导.

20170320更新
IPHLPAPI.LIB在.pro工程文件下添加

LIBS += -LE:/A_WC/qt/NetworkInformation/ -lIPHLPAPI
把   E:/A_WC/qt/NetworkInformation/  替换为文件所在路径
