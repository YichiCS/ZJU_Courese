//============================亚博智能========================================
//  智能小车蓝牙遥控实验
//=============================================================================

#include <SoftwareSerial.h>
SoftwareSerial BT(0,1);
char command;

#define run_car     '1'//按键前
#define back_car    '2'//按键后
#define left_car    '3'//按键左
#define right_car   '4'//按键右
#define stop_car    '0'//按键停
#define left_turn   0x06//按键左旋转
#define right_turn  0x07//按键右旋转
/*小车运行状态枚举*/
enum{
  enSTOP = 0,
  enRUN,
  enBACK,
  enLEFT,
  enRIGHT,
  enTRACE,
  enAVOID
}enCarState;
//==============================
//
//车速控制量 control
#define level1  0x08//速度控制标志位1
#define level2  0x09//速度控制标志位2
#define level3  0x0A//速度控制标志位3
#define level4  0x0B//速度控制标志位4
#define level5  0x0C//速度控制标志位5
#define level6  0x0D//速度控制标志位6
#define level7  0x0E//速度控制标志位7
#define level8  0x0F//速度控制标志位8
//==============================
//==============================
int Left_motor_back = 9;     //左电机后退(IN1)
int Left_motor_go = 5;     //左电机前进(IN2)
int Right_motor_go = 10;    // 右电机前进(IN3)
int Right_motor_back = 6;    // 右电机后退(IN4)

const int SensorRight = 3;   	//右循迹红外传感器(P3.2 OUT1)
const int SensorLeft = 4;     	//左循迹红外传感器(P3.3 OUT2)

int SL;    //左循迹红外传感器状态
int SR;    //右循迹红外传感器状态
int control = 100;//PWM控制量
int control0 = 80;
int incomingByte = 0;          // 接收到的 data byte
String inputString = "";         // 用来储存接收到的内容
boolean newLineReceived = false; // 前一次数据结束标志
boolean startBit  = false;  //协议开始标志
int g_carstate = enSTOP; //  1前2后3左4右0停止
/*超声波*/
int Echo = A5;  // Echo回声脚(P2.0)
int Trig = A4;  //  Trig 触发脚(P2.1)


int Front_Distance = 0;
int Left_Distance = 0;
int Right_Distance = 0;

/*舵机*/
int servopin = 2;  //设置舵机驱动脚到数字口2
int myangle;//定义角度变量
int pulsewidth;//定义脉宽变量
int val;

void setup()
{
  //初始化电机驱动IO为输出方式
  BT.begin(9600);
  pinMode(Left_motor_go, OUTPUT); // PIN 5 (PWM)
  pinMode(Left_motor_back, OUTPUT); // PIN 9 (PWM)
  pinMode(Right_motor_go, OUTPUT); // PIN 6 (PWM)
  pinMode(Right_motor_back, OUTPUT); // PIN 10 (PWM)
  pinMode(Echo, INPUT);    // 定义超声波输入脚
  pinMode(Trig, OUTPUT);   // 定义超声波输出脚
  pinMode(servopin,OUTPUT);      //设定舵机接口为输出接口

  
}

float Distance_test()   // 量出前方距离 
{
  digitalWrite(Trig, LOW);   // 给触发脚低电平2μs
  delayMicroseconds(2);
  digitalWrite(Trig, HIGH);  // 给触发脚高电平10μs，这里至少是10μs
  delayMicroseconds(10);
  digitalWrite(Trig, LOW);    // 持续给触发脚低电
  float Fdistance = pulseIn(Echo, HIGH);  // 读取高电平时间(单位：微秒)
  Fdistance= Fdistance/58;       //为什么除以58等于厘米，  Y米=（X秒*344）/2
  return Fdistance;
}  

void run()     // 前进
{
   digitalWrite(Right_motor_back,LOW);        
   digitalWrite(Left_motor_back,LOW);
   digitalWrite(Right_motor_go,HIGH);  // 右电机前进
   digitalWrite(Left_motor_go,HIGH);  // 左电机前进
  
  analogWrite(Right_motor_go,control);//PWM比例0~255调速，左右轮差异略增减
  analogWrite(Left_motor_go,control);//PWM比例0~255调速，左右轮差异略增减
  //delay(time * 100);   //执行时间，可以调整
}

void brake()         //刹车，停车
{
  digitalWrite(Left_motor_back, LOW);
  digitalWrite(Left_motor_go, LOW);
  digitalWrite(Right_motor_go, LOW);
  digitalWrite(Right_motor_back, LOW);
  //delay(time * 100);//执行时间，可以调整
}

void left()         //左转(左轮不动，右轮前进)
{
  digitalWrite(Right_motor_go, HIGH);	// 右电机前进
  digitalWrite(Right_motor_back, LOW);
  analogWrite(Right_motor_go, control0);//control);
  //analogWrite(Right_motor_back,0);//PWM比例0~255调速
  digitalWrite(Left_motor_go, LOW);  //左轮不动
  digitalWrite(Left_motor_back, LOW);
  //analogWrite(Left_motor_go,0);
  //analogWrite(Left_motor_back,0);//PWM比例0~255调速
 //delay(100);	//执行时间，可以调整
  //digitalWrite(Right_motor_go, LOW);	//全部停止
  //delay(100);	//执行时间，可以调整
}

void spin_left()         //左转(左轮后退，右轮前进)
{
  digitalWrite(Right_motor_go, HIGH);	// 右电机前进
  digitalWrite(Right_motor_back, LOW);
  //analogWrite(Right_motor_go,control);
  analogWrite(Right_motor_back,0);//PWM比例0~255调速
  digitalWrite(Left_motor_go, LOW);  //左轮后退
  digitalWrite(Left_motor_back, HIGH);
  //analogWrite(Left_motor_go,0);
  analogWrite(Left_motor_back,control);//PWM比例0~255调速
  //delay(time * 100);	//执行时间，可以调整
}

void right()        //右转(右轮不动，左轮前进)
{
  digitalWrite(Right_motor_go, LOW);  //右电机不动
  digitalWrite(Right_motor_back, LOW);
  //analogWrite(Right_motor_go,0);
  //analogWrite(Right_motor_back,0);//PWM比例0~255调速
  digitalWrite(Left_motor_go, HIGH); //左电机前进
  digitalWrite(Left_motor_back, LOW);
  analogWrite(Left_motor_go,control0);  //control);
  //delay(100);	//执行时间，可以调整
  //digitalWrite(Left_motor_go, LOW);	//全部停止
  //delay(100);	//执行时间，可以调整
}

void spin_right()        //右转(右轮后退，左轮前进)
{
  digitalWrite(Right_motor_go, LOW);  //右电机后退
  digitalWrite(Right_motor_back, HIGH);
  //analogWrite(Right_motor_go,0);
  analogWrite(Right_motor_back,control);//PWM比例0~255调速
  digitalWrite(Left_motor_go, HIGH); //左电机前进
  digitalWrite(Left_motor_back, LOW);
  //analogWrite(Left_motor_go,200);
  analogWrite(Left_motor_go,control);//PWM比例0~255调速
  //delay(time * 100);	//执行时间，可以调整
}

void back()          //后退
{
  digitalWrite(Right_motor_back, HIGH);
  digitalWrite(Left_motor_back, HIGH);
  digitalWrite(Right_motor_go, LOW); //右轮后退
  digitalWrite(Left_motor_go, LOW); //左轮后退

  analogWrite(Right_motor_back,control);//PWM比例0~255调速
  analogWrite(Left_motor_back,control);//PWM比例0~255调速
  //delay(time * 100);     //执行时间，可以调整
}

/*舵机控制*/
void servopulse(int servopin,int myangle)/*定义一个脉冲函数，用来模拟方式产生PWM值*/
{
  pulsewidth=(myangle*11)+500;//将角度转化为500-2480 的脉宽值
  digitalWrite(servopin,HIGH);//将舵机接口电平置高
  delayMicroseconds(pulsewidth);//延时脉宽值的微秒数
  digitalWrite(servopin,LOW);//将舵机接口电平置低
  delay(20-pulsewidth/1000);//延时周期内剩余时间
}
void front_detection()
{
  //此处循环次数减少，为了增加小车遇到障碍物的反应速度
  for(int i=0;i<=5;i++) //产生PWM个数，等效延时以保证能转到响应角度
  {
    servopulse(servopin,90);//模拟产生PWM
  }
  Front_Distance = Distance_test();
}

void left_detection()
{
  for(int i=0;i<=15;i++) //产生PWM个数，等效延时以保证能转到响应角度
  {
    servopulse(servopin,175);//模拟产生PWM
  }
  Left_Distance = Distance_test();
}

void right_detection()
{
  for(int i=0;i<=15;i++) //产生PWM个数，等效延时以保证能转到响应角度
  {
    servopulse(servopin,5);//模拟产生PWM
  }
  Right_Distance = Distance_test();
}

void trace(){
  while(1)
  {
    //有信号为LOW  没有信号为HIGH
    SR = digitalRead(SensorRight);//有信号表明在白色区域，车子底板上L3亮；没信号表明压在黑线上，车子底板上L3灭
    SL = digitalRead(SensorLeft);//有信号表明在白色区域，车子底板上L2亮；没信号表明压在黑线上，车子底板上L2灭
    if (SL == HIGH&&SR==HIGH)
      run();   //调用前进函数
    else if (SL == HIGH & SR == LOW)// 左循迹红外传感器,检测到信号，车子向右偏离轨道，向左转 
      left();
    else if (SR == HIGH & SL == LOW) // 右循迹红外传感器,检测到信号，车子向左偏离轨道，向右转  
      right();
    else // 都是白色, 停止
    brake();
    
    if(BT.available()){
      command = BT.read();
      if (command == 'p') break;
    }
  }
}
void brake0(int time)  //刹车，停车
{
  digitalWrite(Right_motor_go,LOW);
  digitalWrite(Right_motor_back,LOW);
  digitalWrite(Left_motor_go,LOW);
  digitalWrite(Left_motor_back,LOW);
  delay(time * 100);//执行时间，可以调整  
}
void left0(int time)         //左转(左轮不动，右轮前进)
{
  digitalWrite(Right_motor_go,HIGH);	// 右电机前进
  digitalWrite(Right_motor_back,LOW);
  analogWrite(Right_motor_go,200); 
  analogWrite(Right_motor_back,0);//PWM比例0~255调速
  digitalWrite(Left_motor_go,LOW);   //左轮后退
  digitalWrite(Left_motor_back,LOW);
  analogWrite(Left_motor_go,0); 
  analogWrite(Left_motor_back,0);//PWM比例0~255调速
  delay(time * 100);	//执行时间，可以调整  
}

void spin_left0(int time)         //左转(左轮后退，右轮前进)
{
  digitalWrite(Right_motor_go,HIGH);	// 右电机前进
  digitalWrite(Right_motor_back,LOW);
  analogWrite(Right_motor_go,150); 
  analogWrite(Right_motor_back,0);//PWM比例0~255调速
  digitalWrite(Left_motor_go,LOW);   //左轮后退
  digitalWrite(Left_motor_back,HIGH);
  analogWrite(Left_motor_go,0); 
  analogWrite(Left_motor_back,150);//PWM比例0~255调速
  delay(time * 100);	//执行时间，可以调整  
}

void right0(int time)
//void right()        //右转(右轮不动，左轮前进)
{
  digitalWrite(Right_motor_go,LOW);   //右电机后退
  digitalWrite(Right_motor_back,LOW);
  analogWrite(Right_motor_go,0); 
  analogWrite(Right_motor_back,0);//PWM比例0~255调速
  digitalWrite(Left_motor_go,HIGH);//左电机前进
  digitalWrite(Left_motor_back,LOW);
  analogWrite(Left_motor_go,200); 
  analogWrite(Left_motor_back,0);//PWM比例0~255调速
  delay(time * 100);	//执行时间，可以调整  
}
void back0(int time)          //后退
{
  digitalWrite(Right_motor_go,LOW);  //右轮后退
  digitalWrite(Right_motor_back,HIGH);
  analogWrite(Right_motor_go,0);
  analogWrite(Right_motor_back,200);//PWM比例0~255调速
  digitalWrite(Left_motor_go,LOW);  //左轮后退
  digitalWrite(Left_motor_back,HIGH);
  analogWrite(Left_motor_go,0);
  analogWrite(Left_motor_back,200);//PWM比例0~255调速
  delay(time * 100);     //执行时间，可以调整  
}
void avoid(){
  while(1)
  {
    front_detection();//测量前方距离
    if(Front_Distance < 32)//当遇到障碍物时
    {
      back0(2);//后退减速
      brake0(2);//停下来做测距
      left_detection();//测量左边距障碍物距离
      right_detection();//测量右边距障碍物距离
      if((Left_Distance < 35 ) &&( Right_Distance < 35 ))//当左右两侧均有障碍物靠得比较近
        spin_left0(0.7);//旋转掉头
      else if(Left_Distance > Right_Distance)//左边比右边空旷
      {      
        left0(3);//左转
        brake0(1);//刹车，稳定方向
      }
      else//右边比左边空旷
      {
        right0(3);//右转
        brake0(1);//刹车，稳定方向
      }
    }
    else{
      run(); //无障碍物，直行     
    }

    if(BT.available()){
      command = BT.read();
      if (command == 'l') break;
    }
  } 
}

6{  
    SR = digitalRead(SensorRight);//有信号表明在白色区域，车子底板上L3亮；没信号表明压在黑线上，车子底板上L3灭
    SL = digitalRead(SensorLeft);//有信号表明在白色区域，车子底板上L2亮；没信号表明压在黑线上，车子底板上L2灭
  
   if(BT.available()){
      command = BT.read();
      switch(command){
        case 'w': g_carstate = enRUN; Serial.print("run\r\n"); break;
        case 'a': g_carstate = enLEFT; Serial.print("left\r\n"); break;
        case 's': g_carstate = enSTOP; Serial.print("stop\r\n"); break;
        case 'd': g_carstate = enRIGHT; Serial.print("right\r\n"); break;
        case 'x': g_carstate = enBACK; Serial.print("back\r\n"); break;
        case 't': g_carstate = enTRACE; Serial.print("trace\r\n"); break;
        case 'k': g_carstate = enAVOID; Serial.print("avoid\r\n"); break;
        
        default:g_carstate = enSTOP;break;
      }

      switch(g_carstate)
    {
      case enSTOP: brake();break;
      case enRUN:run();break;
      case enLEFT:left();break;
      case enRIGHT:right();break;
      case enBACK:back();break;
      case enTRACE:trace();break;
      case enAVOID:avoid();break;
      default:brake();break;
    }
   }
}




