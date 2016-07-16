                                                                                                                                                                                                                                                                                                                                            #ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTcpSocket>
#include <QDebug>
#include <QString>
#include <QTextCodec>
#include <QUdpSocket>
#include <QTcpSocket>
#include "ibabydefine.h"
#include <QStringList>
#include <winsock.h>
#include <QHostAddress>
#include <QHostInfo>
#include "winsock2.h"



#define      VERSION    "V1.0"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    void initUi();
    void setUiDisable();
    void setUiEnable();
    QString getHostIp();
    QUdpSocket *mySocket;
    QTcpSocket *myTcpSocket;
    QStringList list;


private slots:
    void scanBtnPushed();
    void readSearchData();

    void brightnessSliderMoved(int);
    void redSliderMoved(int);
    void greenSliderMoved(int);
    void blueSliderMoved(int);

    void brightnessSpinBoxValueChanged(int);
    void redSpinBoxValueChanged(int);
    void greenSpinBoxValueChanged(int);
    void blueSpinBoxValueChanged(int);

    void itemDoubleClicked();

    void hostConnected();
    void readTempHumData();







private:
    Ui::Widget *ui;

};

#endif // WIDGET_H
