#include "widget.h"
#include "ui_widget.h"


Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->initUi();
    this->connect(ui->scanBtn,SIGNAL(clicked()),this,SLOT(scanBtnPushed()));
    mySocket = new QUdpSocket(this);
    mySocket->bind(QHostAddress::Any,10000);
    connect(mySocket,SIGNAL(readyRead()),this,SLOT(readSearchData()));

    connect(ui->brightnessSlider,SIGNAL(valueChanged(int)),this,SLOT(brightnessSliderMoved(int)));
    connect(ui->redSlider,SIGNAL(valueChanged(int)),this,SLOT(redSliderMoved(int)));
    connect(ui->greenSlider,SIGNAL(valueChanged(int)),this,SLOT(greenSliderMoved(int)));
    connect(ui->blueSlider,SIGNAL(valueChanged(int)),this,SLOT(blueSliderMoved(int)));

    connect(ui->brightnessSpinBox,SIGNAL(valueChanged(int)),this,SLOT(brightnessSpinBoxValueChanged(int)));
    connect(ui->redSpinBox,SIGNAL(valueChanged(int)),this,SLOT(redSpinBoxValueChanged(int)));
    connect(ui->greenSpinBox,SIGNAL(valueChanged(int)),this,SLOT(greenSpinBoxValueChanged(int)));
    connect(ui->blueSpinBox,SIGNAL(valueChanged(int)),this,SLOT(blueSpinBoxValueChanged(int)));

    connect (ui->scanResultListWidget,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(itemDoubleClicked()));

    myTcpSocket = new QTcpSocket(this);
    connect(myTcpSocket,SIGNAL(readyRead()),this,SLOT(readTempHumData()));
}

Widget::~Widget()
{
    delete ui;
}


void Widget::initUi()
{
    this->setWindowTitle(QString("iBaby Air Tools ")+VERSION + QString("        本机IP: ")+this->getHostIp());
    this->setWindowFlags(Qt:: WindowMinimizeButtonHint|Qt::WindowCloseButtonHint);

    ui->deviceNumLabel->setText("共搜索到 0 台设备");

    ui->scanBtn->setMinimumSize(80,50);
    ui->LEDBtn->setMinimumSize(80,50);
    ui->speakeBtn->setMinimumSize(80,50);
    ui->listenBtn->setMinimumSize(80,50);
    ui->setBtn->setMinimumSize(80,50);
    this->setUiDisable();
}

void Widget::setUiDisable()
{
    ui->LEDBtn->setDisabled(true);
    ui->speakeBtn->setDisabled(true);
    ui->setBtn->setDisabled(true);
    ui->listenBtn->setDisabled(true);

    ui->brightnessSlider->setDisabled(true);
    ui->redSlider->setDisabled(true);
    ui->greenSlider->setDisabled(true);
    ui->blueSlider->setDisabled(true);

    ui->brightnessSpinBox->setDisabled(true);
    ui->redSpinBox->setDisabled(true);
    ui->greenSpinBox->setDisabled(true);
    ui->blueSpinBox->setDisabled(true);

    ui->connectionStuteLabel->setText("连接状态：\t");
    ui->tempLabel->setText("温    度：   ℃");
    ui->humLabel->setText("湿    度：   %");
    ui->workModeLabel->setText("工作模式：\t");
}

void Widget::setUiEnable()
{
    ui->LEDBtn->setDisabled(false);
    ui->speakeBtn->setDisabled(false);
    ui->setBtn->setDisabled(false);
    ui->listenBtn->setDisabled(false);

    ui->LEDBtn->setStyleSheet("background-color:green");
    ui->speakeBtn->setStyleSheet("background-color:green");
    ui->setBtn->setStyleSheet("background-color:green");
    ui->listenBtn->setStyleSheet("background-color:green");

    ui->brightnessSlider->setDisabled(false);

    ui->redSlider->setDisabled(false);
    ui->greenSlider->setDisabled(false);
    ui->blueSlider->setDisabled(false);


    ui->brightnessSpinBox->setDisabled(false);
    ui->redSpinBox->setDisabled(false);
    ui->greenSpinBox->setDisabled(false);
    ui->blueSpinBox->setDisabled(false);


    ui->connectionStuteLabel->setText("连接状态:\t");
    ui->tempLabel->setText("温    度：   ℃");
    ui->humLabel->setText("湿    度：   %");
    ui->workModeLabel->setText("工作模式：用户态");


}
//搜索按钮点击开始广播
void Widget::scanBtnPushed()
{
    this->setWindowTitle(QString("iBaby Air Tools ")+VERSION + QString("        本机IP: ")+this->getHostIp());
    this->setUiEnable();

    searchBrodcastHeader search;
    memset(&search,0,sizeof(search));
    search.protocolHeader[0] = 'M';
    search.protocolHeader[1] = 'O';
    search.protocolHeader[2] = '_';
    search.protocolHeader[3] = 'I';
    search.controlMask = CONTROLLCODE_SEARCH_BROADCAST_REQUEST;
    search.contentLength = 27;

    QByteArray datagram = QByteArray((char *)&search, sizeof(search));
    mySocket->writeDatagram(datagram.data(),sizeof(search), QHostAddress::Broadcast,10000);
}

//接收搜索广播后的返回结果
void Widget::readSearchData()
{
    ui->scanResultListWidget->clear();

    while (mySocket->hasPendingDatagrams())
    {
        MJPEG_searchCommandContentReply searchReply;
        memset(&searchReply,0,sizeof(searchReply));

        mySocket->readDatagram((char *)&searchReply,sizeof(searchReply));

        if(searchReply.header.controlMask == 1)
        {
            QString camid = searchReply.camID;
            QString camName = searchReply.camName;
            QString camType = searchReply.camtype;
            int workState = (int)searchReply.workState;
            int p2pType = (int)searchReply.p2pType;

            struct in_addr temp_in_addr;
            memset(&temp_in_addr,0,sizeof(temp_in_addr));
            memcpy(&temp_in_addr.S_un,&searchReply.IP,sizeof(searchReply.IP));

            QString ip= QString(QLatin1String(inet_ntoa(temp_in_addr)));
            QString sysVersion = QString("%1.%2.%3").arg((int)searchReply.sysVersion[0]).arg((int)searchReply.sysVersion[1]).arg((int)searchReply.sysVersion[2]);

            QString camInfo = "camID:\t"+ camid
                    + "\nIP:\t" + ip
                    + "\ncamType:\t" + camType
                    + "\nVerison:\t" + sysVersion
                    + "\nP2P type:\t"+ QString::number(p2pType,10)
                    + "\nworkState:\t" + QString::number(workState,10)
                    + "\nUID:\t" + camName
                    +"\n##########################";

            ui->scanResultListWidget->addItem(camInfo);
        }
    }
    int num = ui->scanResultListWidget->count();
    qDebug()<<"num = "<<num;
    ui->deviceNumLabel->setText(QString("共搜索到 %1 台设备").arg(num));
}

//获取主机ip地址
QString Widget::getHostIp()
{
    QHostInfo info = QHostInfo::fromName(QHostInfo::localHostName());
    foreach(QHostAddress address,info.addresses())
    {
         if(address.protocol() == QAbstractSocket::IPv4Protocol)
         {
             return address.toString();
         }
    }
}
//关联的亮度调节槽函数
void Widget::brightnessSliderMoved(int value)
{
    ui->brightnessSpinBox->setValue(ui->brightnessSlider->value());
}

void Widget::redSliderMoved(int value)
{
    ui->redSpinBox->setValue(ui->redSlider->value());
}

void Widget::greenSliderMoved(int value)
{
    ui->greenSpinBox->setValue(ui->greenSlider->value());
}

void Widget::blueSliderMoved(int value)
{
    ui->blueSpinBox->setValue(ui->blueSlider->value());
}

void Widget::brightnessSpinBoxValueChanged(int value)
{
    ui->brightnessSlider->setValue(ui->brightnessSpinBox->value());
}

void Widget::redSpinBoxValueChanged(int value)
{
    ui->redSlider->setValue(ui->redSpinBox->value());
}

void Widget::greenSpinBoxValueChanged(int value)
{
    ui->greenSlider->setValue(ui->greenSpinBox->value());
}

void Widget::blueSpinBoxValueChanged(int value)
{
    ui->blueSlider->setValue(ui->blueSpinBox->value());
}

void Widget::itemDoubleClicked()
{
    myTcpSocket->abort();
    QString ip;
    //返回双击的item上面的文字
    QString str = ui->scanResultListWidget->currentItem()->text();
    QString tmp = str.section("\n",1,1);
    ip = tmp.split("IP:",QString::SkipEmptyParts).at(0).trimmed();

    qDebug()<<"ip = "<<ip;
    myTcpSocket->connectToHost(QHostAddress(ip), 80);
    connect(myTcpSocket,SIGNAL(connected()),this,SLOT(hostConnected()));

}
void Widget::hostConnected()
{
    qDebug()<<"connected!";
    MJPEG_MessageHeader login;
    memset(&login,0,sizeof(login));
    login.messageHeader[0] = 'M';
    login.messageHeader[1] = 'O';
    login.messageHeader[2] = '_';
    login.messageHeader[3] = 'O';
    login.controlMask = CONTROLLCODE_LOGINREQUEST;

    unsigned long loginMsgLength=(unsigned long)sizeof(login);
    myTcpSocket->write((char *) &login,loginMsgLength);
}

void Widget::readTempHumData()
{
    qDebug()<<"ready to read!";
    //缓冲区没有数据，直接无视
      if( tcpData->bytesAvailable() <= 0 )
      {
          return;
      }

    //读取头信息
    MJPEG_MsgHeader msgDataHeader;

    memset(&msgDataHeader,0,sizeof(msgDataHeader));
    mySocket->read((char *)&msgDataHeader,sizeof(msgDataHeader)); //读取

    QString hStr=QString::fromUtf8((char*)(msgDataHeader.messageHeader));

    switch(msgDataHeader.controlMask){
//      case CONTROLLCODE_VIDEOTRANSPORTREPLY: //video 数据
//        {
//             MJPEG_videoDataContent  videoDataContent;
//             memset(&videoDataContent, 0, sizeof(videoDataContent));
//              tcpData->read((char *)&videoDataContent,sizeof(videoDataContent));
//                {
//                       unsigned char pictureData[204800];
//                       memset(pictureData, 0, sizeof(pictureData));

//                       unsigned int pictureLength=videoDataContent.pictureLength;

//                      tcpData->read((char *)pictureData , pictureLength);
//                       {

//                          // [self updateAVData:pictureLength withAVBuffer:pictureData];
//                       }

//                   }

//        }
//        break;

       case CONTROLLCODE_TEMP_HUM_REPLY:
        {//音频数据
          MJPEG_listeningDataContent   listenDataContent;
          memset(&listenDataContent, 0, sizeof(listenDataContent));

          tcpData->read((char *)&listenDataContent , sizeof(listenDataContent));
            {

              unsigned char listenData[160];
              memset(listenData, 0, sizeof(listenData));

              unsigned int listenDataLength=listenDataContent.dataLength;

               tcpData->read((char *)listenData , listenDataLength);
                  {
                   //printf("接收到音频数据  更新音频数据-------------------------->%d\n",listenDataContent.dataLength);

                          //解码 & update音频
                          //[self decodeADPCM2LinearPCM:(unsigned char*)listenData withLength:listenDataLength];
                          if(listenDataLength>640){
                             // return -1;
                          }
                        //  [self decodeG711_2_PCM:listenData withLength:listenDataLength];

                      }

                  }

         }
        break;
//    case CONTROLLCODE_LISTENTRANSPORTREPLY:
//    {//音频数据
//        MJPEG_listeningDataContent   listenDataContent;
//        memset(&listenDataContent, 0, sizeof(listenDataContent));

//        tcpData->read((char *)&listenDataContent , sizeof(listenDataContent));
//        {

//            unsigned char listenData[160];
//            memset(listenData, 0, sizeof(listenData));

//            unsigned int listenDataLength=listenDataContent.dataLength;

//            tcpData->read((char *)listenData , listenDataLength);
//            {
//                //printf("接收到音频数据  更新音频数据-------------------------->%d\n",listenDataContent.dataLength);

//                //解码 & update音频
//                //[self decodeADPCM2LinearPCM:(unsigned char*)listenData withLength:listenDataLength];
//                if(listenDataLength>640){
//                    // return -1;
//                }
//                //  [self decodeG711_2_PCM:listenData withLength:listenDataLength];

//            }

//        }

//    }
//        break;
    default:
        break;


    }

}


