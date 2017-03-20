#ifndef NETWORKINFORMATION_H
#define NETWORKINFORMATION_H

#include <QWidget>
#include <QtGui>
#include <QtNetwork>
#include <Qstring>
#include <QList>
#include <winsock2.h>
#include <QNetworkInterface>
#include <iphlpapi.h>

class NetworkInformation : public QWidget
{
    Q_OBJECT

public:
    explicit NetworkInformation(QWidget *parent = 0);
    ~NetworkInformation();

private:
    QLabel *LabelLocalHostName;
    QLineEdit *LineEditLocalHostName;
    QLabel *LabelIPAddress;
    QLineEdit *LineEditIPAddress;
    QLabel *LabelGateway;
    QLineEdit *LineEditGateway;
    QPushButton *PushButtonDetail;
    QPushButton *PushButtonInfo;
    QHBoxLayout *hbLayout1;
    QHBoxLayout *hbLayout2;
    QHBoxLayout *hbLayout3;
    QHBoxLayout *hbLayout4;
    QVBoxLayout *vbLayout;

    QTextEdit *textEdit;

public slots:
    void slotDetail();
    void slotInfo();
};

#endif // NETWORKINFORMATION_H
