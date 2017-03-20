#include "networkinformation.h"

NetworkInformation::NetworkInformation(QWidget *parent) :
QWidget(parent)
{
    /******************设置标题*******************/
    setWindowTitle(tr("Network Infomation:"));

    /******************设置控件*******************/
    LabelLocalHostName = new QLabel;
    LabelLocalHostName->setText(tr("LocalHostname:"));
    LineEditLocalHostName = new QLineEdit;

    LabelIPAddress = new QLabel;
    LabelIPAddress->setText(tr("IPAddress:"));
    LineEditIPAddress = new QLineEdit;

    LabelGateway = new QLabel;
    LabelGateway->setText(tr("Gateway:"));
    LineEditGateway = new QLineEdit;

    PushButtonInfo = new QPushButton;
    PushButtonInfo->setText(tr( "Info" ));

    PushButtonDetail = new QPushButton;
    PushButtonDetail->setText(tr( "Detail" ));

    /******************设置布局*******************/
    hbLayout1 = new QHBoxLayout;
    hbLayout1->addWidget(LabelLocalHostName);
    hbLayout1->addWidget(LineEditLocalHostName);

    hbLayout2 = new QHBoxLayout;
    hbLayout2->addWidget(LabelIPAddress);
    hbLayout2->addWidget(LineEditIPAddress);

    hbLayout3 = new QHBoxLayout;
    hbLayout3->addWidget(LabelGateway);
    hbLayout3->addWidget(LineEditGateway);

    hbLayout4 = new QHBoxLayout;
    hbLayout4->addWidget(PushButtonInfo);
    hbLayout4->addWidget(PushButtonDetail);

    vbLayout = new QVBoxLayout(this);//this
    vbLayout->addLayout( hbLayout1 );
    vbLayout->addLayout( hbLayout2 );
    vbLayout->addLayout( hbLayout3 );
    vbLayout->addLayout( hbLayout4 );
    //vbLayout->addWidget( PushButtonDetail );

    /******************连接设置*******************/
    connect(PushButtonInfo, SIGNAL(clicked()), this, SLOT(slotInfo()));
    connect(PushButtonDetail, SIGNAL(clicked()), this, SLOT(slotDetail()));

}

NetworkInformation::~NetworkInformation()
{

}


    /******************获取详细之机信息*******************/
/*
void NetworkInformation::slotDetail()
{
    textEdit = new QTextEdit;
    textEdit->setWindowTitle(tr("HostInformation"));
    textEdit->setMinimumSize(600,600);

    QList<QNetworkInterface> list=QNetworkInterface::allInterfaces ();
    for(int i=0;i<list.count();i++)
    {
            QNetworkInterface interface=list.at(i);
            //textEdit->setText(tr("Device:")+interface.name());
            textEdit->insertPlainText(tr("Device:")+interface.name()+"\n");
            QString hardwareAddress=interface.hardwareAddress();
            //textEdit->setText(tr("HardwareAddress:")+interface.hardwareAddress()+"\n");
            textEdit->insertPlainText(tr("HardwareAddress:")+interface.hardwareAddress()+"\n");
            QList<QNetworkAddressEntry> entryList=interface.addressEntries();
            for(int j=0;j<entryList.count();j++)
            {
                    QNetworkAddressEntry entry=entryList.at(j);

                    textEdit->insertPlainText(tr("IP Address:")+entry.ip().toString()+"\n");
                    textEdit->insertPlainText(tr("Netmask:")+entry.netmask().toString()+"\n");
                    textEdit->insertPlainText(tr("Broadcast:")+entry.broadcast().toString()+"\n");
            }
            textEdit->insertPlainText(tr("************************************************")+"\n\n\n");
    }

    textEdit->show();
}
*/

static QString getHostIpByWinSock()
{
    QString IP;
    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
    for (int i = 0; i < ipAddressesList.size(); ++i)
    {
        if (ipAddressesList.at(i) != QHostAddress::LocalHost &&
        ipAddressesList.at(i).toIPv4Address())
        {
            // 如果这个地址不是127.0.0.1，并且是IPv4的地址，就将其赋值给IP，并结束for循环
            IP = ipAddressesList.at(i).toString();
            break;
        }
    }
    // 如果IP为空，则将其赋值为127.0.0.1
    if (IP.isEmpty())
        IP = QHostAddress(QHostAddress::LocalHost).toString();
    return IP;
}


static QString getGateway()
{
    PIP_ADAPTER_INFO pIpAdapterInfo = new IP_ADAPTER_INFO();
    unsigned long stSize = sizeof(IP_ADAPTER_INFO);
    int nRel = GetAdaptersInfo(pIpAdapterInfo,&stSize);
    if (ERROR_BUFFER_OVERFLOW == nRel){
        // ERROR_BUFFER_OVERFLOW：内存空间不够
        // 释放原来的内存空间
        delete pIpAdapterInfo;
        // 重新申请内存空间用来存储所有网卡信息
        pIpAdapterInfo = (PIP_ADAPTER_INFO)new BYTE[stSize];
        // 再次调用GetAdaptersInfo
        nRel=GetAdaptersInfo(pIpAdapterInfo,&stSize);
    }
    if (ERROR_SUCCESS == nRel){
        while (pIpAdapterInfo){
            switch(pIpAdapterInfo->Type){
            case MIB_IF_TYPE_OTHER:
                break;
            case MIB_IF_TYPE_ETHERNET:
                break;
            case MIB_IF_TYPE_TOKENRING:
                break;
            case MIB_IF_TYPE_FDDI:
                break;
            case MIB_IF_TYPE_PPP:
                break;
            case MIB_IF_TYPE_LOOPBACK:
                break;
            case MIB_IF_TYPE_SLIP:
                break;
            default:
                break;
            }
            for (DWORD i = 0; i < pIpAdapterInfo->AddressLength; i++)
                if (i < pIpAdapterInfo->AddressLength-1){
                }
                else{
                }
                // 多个网卡、多个IP
                IP_ADDR_STRING *pIpAddrString =&(pIpAdapterInfo->IpAddressList);
                do{
                    if(QString(pIpAddrString->IpAddress.String) == getHostIpByWinSock()){
                        return QString(pIpAdapterInfo->GatewayList.IpAddress.String);
                    }
                    pIpAddrString=pIpAddrString->Next;
                } while (pIpAddrString);
                pIpAdapterInfo = pIpAdapterInfo->Next;
        }

    }
    //释放内存空间
    if (pIpAdapterInfo){
        delete pIpAdapterInfo;
    }

    return "0.0.0.0";
}

    /******************获取主机名和IP和网关*******************/
void NetworkInformation::slotInfo()
{
    QString localHostName=QHostInfo::localHostName();//获得主机名
    LineEditLocalHostName->setText(localHostName);
    LineEditIPAddress->setText(getHostIpByWinSock());
    LineEditGateway->setText(getGateway());

/*
    QHostInfo hostInfo = QHostInfo::fromName(localHostName);
    QList<QHostAddress> listAddress = hostInfo.addresses();
    if(!listAddress.isEmpty())
    {
         //列表不为空时使用第一个IP地址
         LineEditAddress->setText(listAddress.first().toString());
    }
*/
}



