#include "networkinformation.h"

NetworkInformation::NetworkInformation(QWidget *parent) :
QWidget(parent)
{
    /******************���ñ���*******************/
    setWindowTitle(tr("Network Infomation:"));

    /******************���ÿؼ�*******************/
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

    /******************���ò���*******************/
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

    /******************��������*******************/
    connect(PushButtonInfo, SIGNAL(clicked()), this, SLOT(slotInfo()));
    connect(PushButtonDetail, SIGNAL(clicked()), this, SLOT(slotDetail()));

}

NetworkInformation::~NetworkInformation()
{

}


    /******************��ȡ��ϸ֮����Ϣ*******************/
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
            // ��������ַ����127.0.0.1��������IPv4�ĵ�ַ���ͽ��丳ֵ��IP��������forѭ��
            IP = ipAddressesList.at(i).toString();
            break;
        }
    }
    // ���IPΪ�գ����丳ֵΪ127.0.0.1
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
        // ERROR_BUFFER_OVERFLOW���ڴ�ռ䲻��
        // �ͷ�ԭ�����ڴ�ռ�
        delete pIpAdapterInfo;
        // ���������ڴ�ռ������洢����������Ϣ
        pIpAdapterInfo = (PIP_ADAPTER_INFO)new BYTE[stSize];
        // �ٴε���GetAdaptersInfo
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
                // ������������IP
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
    //�ͷ��ڴ�ռ�
    if (pIpAdapterInfo){
        delete pIpAdapterInfo;
    }

    return "0.0.0.0";
}

    /******************��ȡ��������IP������*******************/
void NetworkInformation::slotInfo()
{
    QString localHostName=QHostInfo::localHostName();//���������
    LineEditLocalHostName->setText(localHostName);
    LineEditIPAddress->setText(getHostIpByWinSock());
    LineEditGateway->setText(getGateway());

/*
    QHostInfo hostInfo = QHostInfo::fromName(localHostName);
    QList<QHostAddress> listAddress = hostInfo.addresses();
    if(!listAddress.isEmpty())
    {
         //�б�Ϊ��ʱʹ�õ�һ��IP��ַ
         LineEditAddress->setText(listAddress.first().toString());
    }
*/
}



