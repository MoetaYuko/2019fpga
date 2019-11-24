#include <IRremote.h> 
#include <Servo.h>
#include <Wire.h> 

int MotorRight1=4;
int MotorRight2=5;
int MotorLeft1=6;
int MotorLeft2=7;
int MotorRight3=8;
int MotorRight4=9;
int MotorLeft3=10;
int MotorLeft4=11;
int judge=12;

int counter=0;
int irReceiverPin = 3; //紅外線接收器 OUTPUT 訊號接在 pin 3

int Trig=A2;
int Echo=A3;
int f=A0;
int d=A1;
//int M1=A2;
//int M2=A3;
//int M3=A4;
//int M4=A5;

long IRfront= 0x00FF629D; //前進碼
long IRback=0x00FFA857; //後退
long IRleft=0x00FF22DD; //左平移
long IRright= 0x00FFC23D; //右平移
long IRstop=0x00FF02FD; //停止
long IRAutorun=0x00FF6897; //超音波自走模式
long IRturnsmallleft= 0x00FFB04F; 
long IRturnleft=0x00FFA25D; //左转弯
long IRturnright= 0x00FFE21D; //右转弯
long IRallfront= 0x00FF9867; //全速


int delay_time = 250; // 伺服馬達轉向後的穩定時間
int Fd,Dd,J,i,distance;

Servo myservo; // 設 myservo
IRrecv irrecv(irReceiverPin); // 定義 IRrecv 物件來接收紅外線訊號
decode_results results; 

void setup() 
{
  Serial.begin(9600);
  pinMode(MotorRight1, OUTPUT); // 腳位 4 (PWM)
  pinMode(MotorRight2, OUTPUT); // 腳位 5 (PWM)
  pinMode(MotorLeft1, OUTPUT); // 腳位 6 (PWM) 
  pinMode(MotorLeft2, OUTPUT); // 腳位 7 (PWM)
  pinMode(MotorRight3, OUTPUT); // 腳位 8 (PWM)
  pinMode(MotorRight4, OUTPUT); // 腳位 9 (PWM)
  pinMode(MotorLeft3, OUTPUT); // 腳位 10 (PWM) 
  pinMode(MotorLeft4, OUTPUT); // 腳位 11 (PWM)
  
  pinMode(Echo, INPUT);
  pinMode(Trig, OUTPUT);
  pinMode(f, INPUT);
  pinMode(d, INPUT);
//  pinMode(M1, OUTPUT);
//  pinMode(M2, OUTPUT);
//  pinMode(M3, OUTPUT);
//  pinMode(M4, OUTPUT);
  
  pinMode(judge, INPUT);
  irrecv.enableIRIn(); // 啟動紅外線解碼
  myservo.attach(2);
  // put your setup code here, to run once:

  // put your setup code here, to run once:

}
/////////////////////////////////////////////////
void back(int a) // 後退 
{
  digitalWrite(MotorRight1,LOW);
  digitalWrite(MotorRight2,HIGH);
  digitalWrite(MotorLeft1,LOW);
  digitalWrite(MotorLeft2,HIGH);
  digitalWrite(MotorRight3,LOW);
  digitalWrite(MotorRight4,HIGH);
  digitalWrite(MotorLeft3,LOW);
  digitalWrite(MotorLeft4,HIGH);
//  setspeed(128);
  delay(a * 10); 
}
void Turnleft(int b) //左轉(转弯)
{
  digitalWrite(MotorRight1,HIGH);
  digitalWrite(MotorRight2,LOW);
  digitalWrite(MotorLeft1,LOW);
  digitalWrite(MotorLeft2,HIGH);
  digitalWrite(MotorRight3,HIGH);
  digitalWrite(MotorRight4,LOW);
  digitalWrite(MotorLeft3,LOW);
  digitalWrite(MotorLeft4,HIGH);
//  setspeed(128);
  delay(b * 10);
}
void Turnright(int c) //右轉(转弯)
{
  digitalWrite(MotorRight1,LOW);
  digitalWrite(MotorRight2,HIGH);
  digitalWrite(MotorLeft1,HIGH);
  digitalWrite(MotorLeft2,LOW);
  digitalWrite(MotorRight3,LOW);
  digitalWrite(MotorRight4,HIGH);
  digitalWrite(MotorLeft3,HIGH);
  digitalWrite(MotorLeft4,LOW);
//  setspeed(128);
  delay(c * 10);
}
void left(int d) //左轉(平移)
{
  digitalWrite(MotorRight1,HIGH);
  digitalWrite(MotorRight2,LOW);
  digitalWrite(MotorLeft1,LOW);
  digitalWrite(MotorLeft2,HIGH);
  digitalWrite(MotorRight3,LOW);
  digitalWrite(MotorRight4,HIGH);
  digitalWrite(MotorLeft3,HIGH);
  digitalWrite(MotorLeft4,LOW);
//  setspeed(128);
  delay(d * 10);
}
void right(int e) //右轉(平移)
{
  digitalWrite(MotorRight1,LOW);
  digitalWrite(MotorRight2,HIGH);
  digitalWrite(MotorLeft1,HIGH);
  digitalWrite(MotorLeft2,LOW);
  digitalWrite(MotorRight3,HIGH);
  digitalWrite(MotorRight4,LOW);
  digitalWrite(MotorLeft3,LOW);
  digitalWrite(MotorLeft4,HIGH);
//  setspeed(128);
  delay(e * 10);
}  
void stopp(int f) //停止
{
  digitalWrite(MotorRight1,LOW);
  digitalWrite(MotorRight2,LOW);
  digitalWrite(MotorLeft1,LOW);
  digitalWrite(MotorLeft2,LOW);
  digitalWrite(MotorRight3,LOW);
  digitalWrite(MotorRight4,LOW);
  digitalWrite(MotorLeft3,LOW);
  digitalWrite(MotorLeft4,LOW); 
  delay(f * 100);
}
void fulladvance(int j) //前進 
{
  digitalWrite(MotorRight1,HIGH);
  digitalWrite(MotorRight2,LOW);
  digitalWrite(MotorLeft1,HIGH);
  digitalWrite(MotorLeft2,LOW);
  digitalWrite(MotorRight3,HIGH);
  digitalWrite(MotorRight4,LOW);
  digitalWrite(MotorLeft3,HIGH);
  digitalWrite(MotorLeft4,LOW);
//  setspeed(256);
  delay(j * 100); 
}
void advance(int g) //前進 
{
  digitalWrite(MotorRight1,HIGH);
  digitalWrite(MotorRight2,LOW);
  digitalWrite(MotorLeft1,HIGH);
  digitalWrite(MotorLeft2,LOW);
  digitalWrite(MotorRight3,HIGH);
  digitalWrite(MotorRight4,LOW);
  digitalWrite(MotorLeft3,HIGH);
  digitalWrite(MotorLeft4,LOW);
//  setspeed(128);
  delay(g * 10); 
}
/*
void setspeed(int h)
{
  analogWrite(M1,h);
  analogWrite(M2,h);
  analogWrite(M3,h);
  analogWrite(M4,h);
}*/
////////////////////////////////////////////
void measure()
{
  digitalWrite(Trig, LOW); 
  delayMicroseconds(2);
  digitalWrite(Trig, HIGH);
  delayMicroseconds(10); 
  digitalWrite(Trig, LOW);
  distance = pulseIn(Echo, HIGH);
  distance = distance/5.88;
  if(distance<0)
  {
    return measure();
  }
  Serial.println(distance);
//  return distance;
}

void loop() 
{

  if (irrecv.decode(&results)) 
    
  { // 解碼成功，收到一組紅外線訊號
////////////////////////////////////////////////////
    if (results.value == IRfront)//前進 
    {
      advance(100);//前進
    }

    if (results.value == IRback)//後退 
    {
      back(10);//後退
    }

    if (results.value == IRright)//右平移
    {
      right(10); // 右轉 
    }

    if (results.value == IRleft)//左平移 
    {
      left(10); // 左轉);
    }
    if (results.value == IRturnright)//右轉 
    {
      Turnright(10); // 右轉 
    }

    if (results.value == IRturnleft)//左轉 
    {
      Turnleft(10); // 左轉);
    }
    
    if (results.value == IRallfront)//全速 
    {
      fulladvance(100); // 左轉);
    }
    
    if (results.value == IRstop)//停止
    {
      stopp(5);
    }
/////////////////////////////////////////////////////////    
    if (results.value == IRstop)//停止
    {
      stopp(5);
    }
    if (results.value == IRAutorun)//自动
    {
      while(IRAutorun)
      {
        myservo.write(90);
        Serial.println("前方");
        delay(1000);
        J=digitalRead(judge);
        Serial.println(J);
        if(J==1)//存在球
        {     
          Dd=digitalRead(d);
          Fd=digitalRead(f);
          Serial.println(Dd);
          Serial.println(Fd);
          if(Dd==1&&Fd==0)//偏左
          {
            myservo.write(177);
            Serial.println("左方");
            measure();
            if(distance>2000)//左距离够
            {
              for(i=0;i<20;i++)
              {
                left(1);
                Fd=digitalRead(f);//读取前进指令
                if (irrecv.decode(&results))
                {
                  irrecv.resume(); 
                  Serial.println(results.value,HEX);
                  if(results.value ==IRstop)
                  { 
                    stopp(5);
                    break;
                  }
                }
                if(Fd==1)//球偏差允许范围内
                {
                  for(i=0;i<20;i++)//前进
                  {
                    myservo.write(90);
                    measure();
                    fulladvance(1);
                    if (irrecv.decode(&results))//手动停
                    {
                      irrecv.resume(); 
                      Serial.println(results.value,HEX);
                      if(results.value ==IRstop)
                      { 
                        stopp(5);
                        break;
                      }
                    }
                    if(distance<3000)//前方距离过小
                    {
                      back(20);
                      break;
                    }
                  }
                }
              }

            }
            else
            {
              right(5);             
            }
          }
          else if(Dd==0&&Fd==0)//偏右
          {
            myservo.write(5);
            Serial.println("右方");
            measure();
            if(distance>2000)//右距离够
            {
              for(i=0;i<20;i++)
              {
                right(1);
                Fd=digitalRead(f);//读取前进指令
                if (irrecv.decode(&results))
                {
                  irrecv.resume(); 
                  Serial.println(results.value,HEX);
                  if(results.value ==IRstop)
                  { 
                    stopp(5);
                    break;
                  }
                }
                if(Fd==1)//球偏差允许范围内
                {
                  for(i=0;i<20;i++)//前进
                  {
                    myservo.write(90);
                    measure();
                    fulladvance(1);
                    if (irrecv.decode(&results))//手动停
                    {
                      irrecv.resume(); 
                      Serial.println(results.value,HEX);
                      if(results.value ==IRstop)
                      { 
                        stopp(5);
                        break;
                      }
                    }
                    if(distance<3000)//前方距离过小
                    {
                      back(20);
                      break;
                    }
                  }
                }
              }
            }
            else
            {
              left(5);             
            }
          }
          else if(Fd==1)
          {
            for(i=0;i<50;i++)//前进
            {
              myservo.write(90);
              measure();
              fulladvance(5);
              if (irrecv.decode(&results))
              {
                irrecv.resume(); 
                Serial.println(results.value,HEX);
                if(results.value ==IRstop)
                { 
                  stopp(5);
                  break;
                }
              }
              if(distance<3000)//前方距离过小
              {
                back(20);
                break;
              }
            }
          }
        }
        else
        {
          stopp(5);
        }
      }
    }
    
    else
    {
      stopp(5);
    }
    Serial.println(results.value, HEX);
    irrecv.resume(); // 繼續收下一組紅外線訊號
  } 
}
