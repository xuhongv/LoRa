#ifndef __MODBUS_H
#define __MODBUS_H

/*网络相关宏定义*/
#define NET_ADDR           0xA5    //网络地址
#define SLAVE1_ADDR        0x01    //子设备1地址
#define BROADCAST_ADDR     0xFF    //广播地址

/*操作码相关宏定义*/
#define OP_W_COILS         0x02    //写继电器状态
#define OP_R_SENSOR        0x01    //读传感器数据

/*参数相关宏定义*/
#define PRAM_R_TEMPERATURE 0x01    //只读取温度
#define PRAM_R_HUMIDITY    0x02    //只读取湿度
#define PRAM_R_LUX         0x04    //只读取光线强度
#define PRAM_R_ALL         0x07    //读取所有传感器

#define PRAM_W_RELAY1      0x01    //吸合继电器1,如果想断开按位取反即可
#define PRAM_W_RELAY2      0x02    //吸合继电器2,如果想断开按位取反即可

typedef enum
{
    FRAME_OK = 0x00,               //数据帧正确
    FRAME_NETADDR_ERR = 0x01,      //网络地址错误
    FRAME_SLAVEADDR_ERR = 0x02,    //从机地址错误
    FRAME_CRC_ERR = 0x03,          //CRC校验错误
    FRAME_EMPTY = 0xFF             //数据为空，此时没接到数据
}FrameStatus;

typedef struct 
{
    /**
     * 对于主机端来说，还可以在最前面添加各个从机的运行状态
     * 如：unsigned char SlaveStatus[256];
     * 每个数组成员都对应一个从机的状态，比如电量不足、通信异常等等
     * 这里没有添加
     * */  
    unsigned char Coils;        //线圈状态,Bit0对应继电器1,Bit1对应继电器2
    unsigned char Temperature;  //环境温度
    unsigned char Humidity;     //环境湿度
    unsigned short int Lux;     //环境光照强度
    /*可继续添加其他传感器、被控单元和系统参数*/
}DeviceBlock;

void sendMasterAsk(unsigned char slave_addr,unsigned char op_code,unsigned char pram);
FrameStatus receiveSlaveAck(unsigned char slave_addr,unsigned char op_code,unsigned char pram,DeviceBlock * pdevblock);
FrameStatus processMasterAsk(DeviceBlock * pdevblock);

#endif

