#include <MsTimer2.h>  // 引入定时器库文件
#include <Servo.h>      //引入舵机库文件
Servo myservo;
void ggyy() {           //中断处理函数  改变led的状态
   static int gy = 0;
   gy = 1- gy; 
   digitalWrite(13, gy);
}
int times=0;
int buttom=6;
int pos=0;
int bos=0;
int interval=900;
void setup() {       // 初始化
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  myservo.attach(9);
  myservo.write(0); 
}
void loop() {
  int  state=digitalRead(buttom);
  if(state==1)                     // 判断按钮是否被按下
  {  ++times;                      // 记录按钮按下的次数
     Serial.println(times);
     delay(200);                   // 消除抖动
    if(pos>=0&&pos<180){            //在舵机没到180之前，按一次增加10度
	  pos=pos+10;
      Serial.println(pos);
      myservo.write(pos);
      MsTimer2::set(interval, ggyy);// 改变led的闪烁频率
      MsTimer2::start();
      interval=interval-50;
           if(pos==180){
	           pos=180;
               bos=pos;}
     }  
     if(bos>0&&bos<=180){        //在舵机没有回到0度之前，按一次减10度
	  bos=bos-10;
      Serial.println(bos);
      myservo.write(bos); 
      MsTimer2::set(interval, ggyy);
      MsTimer2::start();
      interval=interval+50;
           if(bos==0){
			 bos=0;
             pos=bos;}
                        } 
  }           
}