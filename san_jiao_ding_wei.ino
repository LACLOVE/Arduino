//可见光室内定位-三角定位
#include "OneButton.h"
#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2); 
double   d1, d2, d3, xa=0, ya=40, za=80, xb=-40, yb=0, zb=80, xc=40, yc=-40, zc=80 ; //定义距离，x,y,z的坐标
double   a, b, c, d, e, f;
double    x, y, x1, y1, x2, y2;          //所求平面坐标
double    r1, r2, r3;    //三个返回值变量
float    k1=35, k2=10, k3=20;    //光强换算距离的比例系数
float num[5]={0};
int flag=0;
OneButton button(8, true); 
void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.print("hello, world!");
  button.attachDoubleClick(doubleclick);
}
void loop() {
  r1=voltage1();
  r2=voltage2();
  r3=voltage3();

  float a = r1*r1 - r2*r2 + xb*xb - xa*xa - ya*ya;
  float b = r1*r1 - r3*r3 + xc*xc + yc*yc - xa*xa - ya*ya;
  float c = 2 * (xb - xa);
  float d = 2 * (yb - ya);
  float e = 2*(xc-xa);
  float f = 2 * (yc-ya);
  float x = (a - b*c / e) / (d - f*c / e);
  float y = (a-c*x)/d;
  int   k = y/x;
  int x1=(int)x*10;
  float x2=x1/10;
  int y1=(int)y*10;
  float y2=y1/10;
  
  button.tick();  //按钮确定
  if(flag==1){
  lcd.clear();//LCD清屏
  // 定位光标在LCD第0行、第0列
  lcd.setCursor(0, 0);
  lcd.print("x:");
  lcd.setCursor(0, 1);
  lcd.print("y:");
  lcd.setCursor(2, 0);
  lcd.print(x2);
  lcd.setCursor(2, 1);
  lcd.print(y2);
  Serial.println(x);
  Serial.println("\n");
  Serial.println(y);
  flag=0;
  }
  
  if(y>=20&&k>1)    //区分B区域
  { lcd.setCursor(9, 0);
    lcd.print("D:");
    lcd.setCursor(11, 0);
    lcd.print("up");
    }
   if(y<=-20&&k>1)  //区分D区域
  { lcd.setCursor(9, 0);
    lcd.print("D:");
    lcd.setCursor(11, 1);
    lcd.print("down");
    }
   if(x>=20&&k<-1)    //区分C区域
  { lcd.setCursor(9, 0);
    lcd.print("D:");
    lcd.setCursor(11, 0);
    lcd.print("right");
    }
   if(y<=-20&&k<-1)  //区分E区域
  { lcd.setCursor(9, 0);
    lcd.print("D:");
    lcd.setCursor(11, 1);
    lcd.print("left");
    }
  delay(100);
}
double voltage1()    //AD转换成电压值
{
  double   d1;
  int sensorValue1 = analogRead(A0);  //读取电压值
  for(int i=0;i<5;i++){
    float sensorValue1=num[i]+sensorValue1;
  }
  float sensorValue11=sensorValue1/5;
  float voltage1 = sensorValue11 * (5.0 / 1023.0);
  d1=voltage1*k1;
  //Serial.println(voltage1);
  return(d1);
  }
double voltage2()    //AD转换成电压值
{
  double   d2;
  int sensorValue2 = analogRead(A1);  //读取电压值
  for(int i=0;i<5;i++){
    float sensorValue2=num[i]+sensorValue2;
  }
  float sensorValue22=sensorValue2/5;
  float voltage2 = sensorValue22 * (5.0 / 1023.0);
  d2=voltage2*k2;
  //Serial.println(voltage2);
  return(d2);
  }
double voltage3()    //AD转换成电压值
{
  double   d3;
  int sensorValue3 = analogRead(A3);  //读取电压值
  for(int i=0;i<5;i++){
    float sensorValue3=num[i]+sensorValue3;
  }
  float sensorValue33=sensorValue3/5;
  float voltage3 = sensorValue33 * (5.0 / 1023.0);
  d3=voltage3*k3;
  //Serial.println(voltage3);
  return(d3);
  }
void doubleclick() {
  flag=1;
}

