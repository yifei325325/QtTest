#ifndef IBABYDEFINE_H
#define IBABYDEFINE_H

#endif // IBABYDEFINE_H
#define Big2Little16(A)  ((((unsigned short)(A) & 0xff00) >> 8) | \
(((unsigned short)(A) & 0x00ff) << 8))
#define Big2Little32(A)  ((((unsigned int)(A) & 0xff000000) >> 24) | \
(((unsigned int)(A) & 0x00ff0000) >> 8) | \
(((unsigned int)(A) & 0x0000ff00) << 8) | \
(((unsigned int)(A) & 0x000000ff) << 24))

typedef short INT16;

const INT16    CONTROLLCODE_LOGINREQUEST                =0;    //登陆请求操作码  (操作命令)
const INT16    CONTROLLCODE_LOGINREPLY                  =1;    //登陆回应操作码  (操作命令)
const INT16    CONTROLLCODE_VERIFIYREQUEST              =2;    //验证请求操作码  (操作命令)
const INT16    CONTROLLCODE_VERIFIYREPLY                =3;    //验证回应操作码  (操作命令)
const INT16    CONTROLLCODE_VIDEOTRANSLATION_REQUEST    =4;    //视频请求操作码  (操作命令)
const INT16    CONTROLLCODE_VIDEOTRANSLATION_REPLY      =5;    //视频回应操作码  (操作命令)
const INT16    CONTROLLCODE_VIDEOTRANSLATION_STOP       =6;    //视频停止操作码  (操作命令)

const INT16    CONTROLLCODE_LISTENSTART_COMMAND         =8;    //开始监听操作码  (操作命令)
const INT16    CONTROLLCODE_LISTENSTART_REPLY           =9;    //监听回应操作码  (操作命令)
const INT16    CONTROLLCODE_LISTENSTOP_COMMAND          =10;   //停止监听操作码  (操作命令)

const INT16    CONTROLLCODE_TALKSTART_COMMAND           =11;    //开始对讲操作码  (操作命令)
const INT16    CONTROLLCODE_TALKSTART_REPLY             =12;    //对讲回应操作码  (操作命令)
const INT16    CONTROLLCODE_TALKSTOP_COMMAND            =13;   //停止对讲操作码   (操作命令)

const INT16    CONTROLLCODE_SEARCH_BROADCAST_REQUEST    =0;   //广播请求操作码
const INT16    CONTROLLCODE_SEARCH_BROADCAST_REPLY      =1;   //广播回应操作码

const INT16    CONTROLLCODE_DECODER_CONTROLL            =14;   //解码器控制操作码  (操作命令)
const INT16    CONTROLLCODE_REPLY_ALARM                 =25;   //报警操作码       (操作命令)
const INT16    CONTROLLCODE_MULTIVIDEOINFOREPLY         =28;   //多路信息操作码    (操作命令)

const INT16    CONTROLLCODE_VIDEOTRANSPORTCOMMD         =0;   //视频传输请求操作码   (传输命令)
const INT16    CONTROLLCODE_VIDEOTRANSPORTREPLY         =1;   //视频传输回应操作码   (传输命令)
const INT16    CONTROLLCODE_LISTENTRANSPORTREPLY        =2;   //监听回应操作码      (传输命令)
const INT16    CONTROLLCODE_TALKTRANSPORTREPLY          =3;   //对讲回应操作码      (传输命令)

const INT16    CONTROLLCODE_KEEPALIVECOMMAND            =255;

const INT16     CONTROLLCODE_SEARCHWIFI_REQ             =30;  //搜索Wi-Fi请求命令
const INT16     CONTROLLCODE_SEARCHWIFI_REPLY           =31;  //搜索wifi回复

const INT16     CONTROLLCODE_TEMP_HUM_REQ               =32;  //温湿度请求命令
const INT16     CONTROLLCODE_TEMP_HUM_REPLY             =33;  //温湿度回复

const INT16     CONTROLLCODE_LASER_CTRL_REQ             =34;
const INT16     CONTROLLCODE_LASER_CTRL_REPLY           =35;

const INT16     CONTROLLCODE_AIR_QUALITY_REQ            =36;
const INT16     CONTROLLCODE_AIR_QUALITY_REPLY          =37;

const INT16     CONTROLLCODE_WRITE_UID_REQ              =38;
const INT16     CONTROLLCODE_WRITE_UID_REPLY            =39;

const INT16     CONTROLLCODE_SET_WIFI_REQ               =40;
const INT16     CONTROLLCODE_SET_WIFI_REPLY             =41;

const INT16     CONTROLLCODE_GET_SD_REQ                 =42;
const INT16     CONTROLLCODE_GET_SD_REPLY               =43;

const INT16     CONTROLLCODE_ION_CTRL_REQ               =44;  //iON开关
const INT16     CONTROLLCODE_ION_CTRL_REPLY             =45;

const INT16     CONTROLLCODE_LED_CTRL_REQ               =46;  //LED开关
const INT16     CONTROLLCODE_LED_CTRL_REPLY             =47;

//固件工作状态 0： 用户态，1：工装态。
const INT16   CONTROLLCODE_WORKSTATE_CTRL_REQ          =48;
const INT16   CONTROLLCODE_WORKSTATE_CTRL_REPLY        =49;

const INT16    LOGINREQUESTREPLYVALUE_OK                =0;
const INT16    LOGINREQUESTREPLYVALUE_BADACCESS         =1;


const INT16     VERIFYREPLYRETURNVALUE_OK               =0;   //较验正确
const INT16     VERIFYREPLYRETURNVALUE_USER_ERROR       =1;   //用户名出错
const INT16     VERIFYREPLYRETURNVALUE_PASS_ERROR       =5;   //密码出错


const INT16     VIDEOIREQUESTREPLY_OK                   =0;   //同意连接
const INT16     VIDEOIREQUESTREPLY_USERFULL             =2;   //用户已经满
const INT16     VIDEOIREQUESTREPLY_FORBIDEN             =8;   //禁止连接

#pragma pack(push,1)
typedef struct searchBrodcastHeader
{
    char            protocolHeader[4];   //协议头
    short           controlMask;         //操作码
    char            reserved;            //保留
    char            reserved2[8];        //保留
    int             contentLength;       //正文长度
    int             reserved3;           //保留

}MJPEG_searchBrodcastHeader;

typedef struct searchCommandContent
{
    char            reserved0;
    char            reserved1;
    char            reserved2;
    char            reserved3;

}MJPEG_searchCommandContent;

typedef struct searchCommandContentReply
{
    MJPEG_searchBrodcastHeader  header; //头部
    char            camID[13];          //摄像头ID
    char            camName[21];        //摄像头名称,p2p
    unsigned int    IP;                 //IP; 大端
    unsigned int    netMask;            //掩码  大端
    unsigned int    getwayIP;           //网关IP;  大端
    unsigned int    DNS;                //DNS;  大端
    char p2pType;
    char workState;          //工装状态
    char            reserved[2];        //保留
    char            sysVersion[4];      //系统版本
    char            camtype[4];       //App software 版本 修改为 设备类型
    unsigned short  port;       //端口 大端
    char            dhcpEnabled;        //DHCP状态

}MJPEG_searchCommandContentReply;


//--------------------------------------tcp
//协议头文件.
typedef struct MJPEG_MessageHeader
{
    unsigned char           messageHeader[4];    //协议头  摄像头操作协议: "MO_O" 摄像头传输协议 "MO_V"  搜索协议头： MO_I
    short                   controlMask;         //操作码，区分同一协议中不同命令.
    unsigned char           reserved0;            //保留，默认=0;
    unsigned char           reserved1[8];           //保留
    int                     commandLength;        //命令中正文的长度
    int                     reserved2;            //保留

}MJPEG_MsgHeader;

//网络连接信息结构体
typedef struct NetConnectInfomation
{
    char server_ip[64];   //camIP
    int  port;            //端口
    char user_name[13];	  //用户名
    char pass_word[13];	  //密码

}MJPEG_NetConnectInfo;


//登陆响应结构体
typedef struct LoginRequestReply
{
    short           result;   //返回 0 OK,2 已经达到最大连接许可，连接将断开.
    unsigned char   devID[13];  //返回设备id.
    unsigned char   reserved0[4];  //保留
    unsigned char   reserved1[4];  //保留
    unsigned char   devVersion[4];  //摄像头系统固件版本.

}MJPEG_LoginRequestReply;



//较验请求正文结构体
typedef struct VerifyRequestCommContent
{
    //协议正文
    MJPEG_MsgHeader msgHeader;
    unsigned char   userName[13];      //用户名
    unsigned char   password[13];      //密码

}MJPEG_VerifyRequestCommContent;



//较验响应结构体
typedef struct verifyRequestReply
{
    MJPEG_MsgHeader msgHeader;
    short           result; //0 较验正确 1 用户名出错 2 密码出错.
    char            reserved;    //保留


}MJPEG_VerifyRequestReply;


//视频传输正文
typedef struct videoTranslationRequest
{
     MJPEG_MsgHeader msgHeader;
    char          reserved;   //保留

}MJPEG_videoTranslationRequest;


//视频响应.
typedef struct videoTranslationRequestReply
{
    short           result;   //0: 同意 2 超过最大连接数被拒绝.
    unsigned int    videoID;  //当Result=0 并且之前没有进行因视频传输时，本字段才存在.用来标识数据连接的ID.

}MJPEG_videoTranslationRequestReply;





typedef struct signalDeviceInfo
{
    char  msid[13];
    char  alias[21];

    char  host[65];
    short port;

    char  user[13];
    char  pwd[13];

    char  mode;

}SignalDeviceInfo;





//报警信息正文
typedef struct replyDeviceAlarm
{
    char              alarmType;   //报警类型 0 停止 1 移动检测 2 外部报警
    short             reserved0;
    short             reserved1;
    short             reserved2;
    short             reserved3;

}MJPEG_replyDeviceAlarm;



//发送视频数据请求
typedef struct videoTranslationRequestID
{
    MJPEG_MsgHeader    msgHeader;
    int                videoID;

}MJPEG_videoTranslationRequestID;



//视频正文结构体
typedef struct videoDataContent
{
    unsigned int             timeStamp; //时间戳
    unsigned int             frameTime; //帧采集时间
    unsigned char            reserved;  //保留
    unsigned int             pictureLength;  //图片长度

}MJPEG_videoDataContent;

//监听音频正文结构体
typedef struct listeningDataContent
{
    unsigned int             timeStamp;//时间戳
    unsigned int             packageNumber; //包序号
    unsigned int             collectionTime; //采集时间
    char                     audioFormat;    //音频格式
    unsigned int             dataLength;     //数据长度

}MJPEG_listeningDataContent;

//对讲正文结构体
typedef struct talkingDataContent
{
    MJPEG_MsgHeader          msgHeader;
    unsigned int             timeStamp;//时间戳
    unsigned int             packageNumber; //包序号
    unsigned int             collectionTime; //采集时间
    char                     audioFormat;    //音频格式
    unsigned int             dataLength;     //数据长度

}MJPEG_talkingDataContent;



//监听请求结构体
typedef struct audioRequestCommand
{
    MJPEG_MsgHeader msgHeader;
    char            reserved;    //保留
}MJPEG_audioRequestCommand;



//监听接收响应正文
typedef struct audioRequestCommandReply
{

    short           result; //0：同意 2:超过最大连接数拒绝 7: 机器不支持此功能
    int             audioID; //数据连接ID.
}MJPEG_audioRequestCommandReply;



//对讲请求结构体
typedef struct talkRequestCommand
{
    MJPEG_MsgHeader msgHeader;
    char            playdelayBuffTime; //音频播放缓冲时间 >=1;
}MJPEG_talkRequestCommand;



//对讲接受响应正文
typedef struct talkRequestCommandReply
{
    short            result; //0: 同意,2:超过最大连接数拒绝 7: 不支持改功能
    //int              talkID; //数据连接ID;
}MJPEG_talkRequestCommandReply;


//wifi 搜索
typedef struct wifiRequestCommand
{
    MJPEG_MsgHeader msgHeader;
    char            reserved;
}MJPEG_wifiRequestCommand;

typedef struct wifiCfg
{
    char 	ssid[32];
    char	signal;//0-100代表%0-%100
}MJPEG_wifiCfg;


typedef struct wifiRequestCommandReply
{
    MJPEG_MsgHeader msgHeader;
    char            num;
    MJPEG_wifiCfg	wifiCfg[0];

}MJPEG_wifiRequestCommandReply;


//温湿度
typedef struct temperaterHumlityRequest
{
    MJPEG_MsgHeader msgHeader;
    char            reserved;
}MJPEG_temperaterHumlityRequest;

typedef struct temperaterHumlityReply
{
    double			temperature;
    double			wetness;
}MJPEG_temperaterHumlityReply;


//镭射
typedef struct laserCtrlRequestCommand
{
    MJPEG_MsgHeader msgHeader;
    int laser_stast;// 1:开2:关
}MJPEG_laserCtrlRequestCommand;

typedef struct laserCtrlRequestCommandReply
{
    short result;
}MJPEG_laserCtrlRequestCommandReply;


//iON 开关
typedef struct iONCtrlRequestCommand
{
    MJPEG_MsgHeader msgHeader;
    int ion_stast;// 1:开2:关
}MJPEG_iONCtrlRequestCommand;

typedef struct iONCtrlRequestCommandReply
{
    short result;
}MJPEG_iONCtrlRequestCommandReply;


//LED 开关
typedef struct lEDCtrlRequestCommand
{
    MJPEG_MsgHeader msgHeader;
    int led_stast;// 1:开2:关
}MJPEG_lEDCtrlRequestCommand;

typedef struct lEDCtrlRequestCommandReply
{
    short result;
}MJPEG_lEDCtrlRequestCommandReply;

//空气质量
typedef struct airQualityRequestCommand
{
    MJPEG_MsgHeader msgHeader;
    char reserved;
}MJPEG_airQualityRequestCommand;

typedef struct airQualityRequestCommandReply
{
    int airQualityLevel;//1234
}MJPEG_airQualityRequestCommandReply;

//写老化的P2P UID
typedef struct writeUIDRequestCommand
{
    MJPEG_MsgHeader msgHeader;
    unsigned char cUID[21];
}MJPEG_writeUIDRequestCommand;

typedef struct writeUIDRequestCommandReply
{
    short result;
}MJPEG_writeUIDRequestCommandReply;

//设置wifi
typedef struct setWifiRequestCommand
{
    MJPEG_MsgHeader msgHeader;
    unsigned char ssid[33];
    unsigned char password[65];
}MJPEG_setWifiRequestCommand;

typedef struct setWifiRequestCommandReply
{
    short result;

}MJPEG_setWifiRequestCommandReply;


typedef struct getSDRequestCommand
{
    MJPEG_MsgHeader msgHeader;
    char reserved;
}MJPEG_GetSDRequestCommand;

typedef struct GetSDRequestCommandReply
{
    int total;//0:NO sd card , >0: MB
    int used;//>0: MB

}MJPEG_GetSDRequestCommandReply;


//
typedef struct  WorkStateCtrlRequestCommand
{
    MJPEG_MsgHeader msgHeader;
    int workstate;// 1:用户态2:工装态
}MJPEG_WorkStateCtrlRequestCommand;

typedef struct WorkStateCtrlRequestCommandReply
{
    short result; // 1:用户态2:工装态
}MJPEG_WorkStateCtrlRequestCommandReply;

#pragma pack(pop)
//076b7e
enum MJ_FUNCTION_RETURN_ERROR_VALUE
{
    RECV_READHEADERERROR=0,
    SEND_LOGINCOMMAND_REPLY_ERROR,      //登陆回应出错

    SEND_VIDEOTRANSLATION_REQUEST_FAILED, //视频传输请求失败
    SEND_VIDEOTRANSLATION_REPLY_ACCESS,//同意连接
    SEND_VIDEOTRANSLATION_REPLY_USERFULL,//用户满
    SEND_VIDEOTRANSLATION_REPLY_FPRBIDEN, //拒绝连接

    SEND_VERIFYREQUEST_FAILED,   //发送较验命令失败.
    SEND_VERIFYREQUEST_NO_REPLY, //较验请求无回应
    SEND_VERIFYREQUEST_REPLY_ERROR, //较验响应出错
    SEND_VIDEOTRANSLATION_REPLY_FAILED,//视频传输读取头部出错
    SEND_VIDEOTRANSLATION_REQUEST_ERROR, //视频传输请求错误

    MULTIVIDEOINFO_REPLY_ERROR, //视频传输请求错误

};





