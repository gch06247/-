//#include <Servo.h>
int Left_motor_back = 8; //Left_motor_back(IN1)
int Left_motor_go = 9; //Left_motor_go(IN2)
int Right_motor_go = 10; //Right_motor_go(IN3)
int Right_motor_back = 11; //Right_motor_back(IN4)

int Echo = A1;
int Trig = A0;
int Front_Distance = 0;
int Left_Distance = 0;
int Right_Distance = 0;
int servopin = 2;
int myangle;
int pulsewidth;
int val;

const int SensorRight = 3; //(P3.2 OUT1)
const int SensorLeft = 4; //(P3.3 OUT2)
int SL; //SensorLeft
int SR; //SensorRight

const int SensorRight_2 = 5; //(P3.2 OUT1)
const int SensorLeft_2 = 6; //(P3.3 OUT2)
int SL_2; //SensorLeftc
int SR_2; //SensorRight

void setup()
{
  pinMode(SensorRight, INPUT);
  pinMode(SensorLeft, INPUT);
  pinMode(SensorRight_2, INPUT);
  pinMode(SensorLeft_2, INPUT);

  pinMode(Echo, INPUT);
  pinMode(Trig, OUTPUT);
  pinMode(servopin, OUTPUT);

  pinMode(Left_motor_go, OUTPUT);
  pinMode(Left_motor_back, OUTPUT);
  pinMode(Right_motor_go, OUTPUT);
  pinMode(Right_motor_back, OUTPUT);
  Serial.begin(9600);

}

void run(int time) //전진
{
  digitalWrite(Right_motor_go, HIGH);
  digitalWrite(Right_motor_back, LOW);
  analogWrite(Right_motor_go, 85); //PWM은 0~255속도조절, 좌우 차이가 증감
  analogWrite(Right_motor_back, 0);
  digitalWrite(Left_motor_go, HIGH);
  digitalWrite(Left_motor_back, LOW);
  analogWrite(Left_motor_go, 85); //PWM은 0~255속도조절， 좌우 차이가 증감
  analogWrite(Left_motor_back, 0);
  delay(time * 20);
}
void brake(int time) //브레이크
{
  digitalWrite(Right_motor_go, LOW); //Right, Left 모두 LOW
  digitalWrite(Right_motor_back, LOW);
  digitalWrite(Left_motor_go, LOW);
  digitalWrite(Left_motor_back, LOW);
  delay(time * 2);
}
void left(int time) //좌회전(오른쪽 바퀴 회전식으로)
{
  digitalWrite(Right_motor_go, HIGH); // Right_motor_go가 HIGH
  digitalWrite(Right_motor_back, LOW); // Right_motor_back이 LOW
  analogWrite(Right_motor_go, 100); // Right_motor_go의 속도 200
  analogWrite(Right_motor_back, 0); //PWM0~255속도조절
  digitalWrite(Left_motor_go, LOW); //Left는 LOW
  digitalWrite(Left_motor_back, LOW); //Left는 LOW
  analogWrite(Left_motor_go, 0); // Left_motor_go의 속도 0
  analogWrite(Left_motor_back, 0); //PWM0~255 속도조절
  delay(time * 50);
}
void spin_left(int time) //좌회전(Spin)
{
  digitalWrite(Right_motor_go, HIGH);
  digitalWrite(Right_motor_back, LOW);
  analogWrite(Right_motor_go, 200); // Right_motor_go의 속도 200
  analogWrite(Right_motor_back, 0);
  
  digitalWrite(Left_motor_go, LOW);
  digitalWrite(Left_motor_back, HIGH);
  analogWrite(Left_motor_go, 0);
  analogWrite(Left_motor_back, 140); // Left_motor_back의 속도 200
  delay(time * 2);
}
void right(int time) //우회전(왼쪽 바퀴 회전식으로)
{
  digitalWrite(Right_motor_go, LOW); // Right_motor_go가 LOW
  digitalWrite(Right_motor_back, LOW); // Right_motor_back이 LOW
  analogWrite(Right_motor_go, 0); // Right_motor_go의 속도 0
  analogWrite(Right_motor_back, 0); //PWM0~255속도조절
  digitalWrite(Left_motor_go, HIGH); // Left_motor_go HIGH
  digitalWrite(Left_motor_back, LOW); // Left_motor_go LOW
  analogWrite(Left_motor_go, 100); // Left_motor_go의 속도 200
  analogWrite(Left_motor_back, 0); //PWM0~255속도조절
  delay(time * 50);
}
void spin_right(int time) //우회전(Spin)
{
  digitalWrite(Right_motor_go, LOW);
  digitalWrite(Right_motor_back, HIGH);
  analogWrite(Right_motor_go, 0);
  analogWrite(Right_motor_back, 100); // Right_motor_go의 속도 200
  digitalWrite(Left_motor_go, HIGH);
  digitalWrite(Left_motor_back, LOW);
  analogWrite(Left_motor_go, 100);
  analogWrite(Left_motor_back, 0); // Left_motor_back의 속도 0
  delay(time * 2);
}
void back(int time) //후진
{
  digitalWrite(Right_motor_go, LOW); //오른쪽 바퀴 뒤로
  digitalWrite(Right_motor_back, HIGH);
  analogWrite(Right_motor_go, 0);
  analogWrite(Right_motor_back, 80); //속도 150
  digitalWrite(Left_motor_go, LOW); //왼쪽 바퀴 뒤로
  digitalWrite(Left_motor_back, HIGH);
  analogWrite(Left_motor_go, 0);
  analogWrite(Left_motor_back, 80); //속도 150
  delay(time * 2);
}

float Distance_test()
{
  digitalWrite(Trig, LOW);
  delayMicroseconds(2);
  digitalWrite(Trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trig, LOW);
  float Fdistance = pulseIn(Echo,HIGH);
  Fdistance = Fdistance / 58;
 return Fdistance;
}
//void Distance_display(int Distance)
//{
//if((2<Distance)&(Distance<400))
//{ lcd.home();
//lcd.print(" Distance: ");
//lcd.setCursor(6,2);
//lcd.print(Distance);
//lcd.print("cm"); }
//else { lcd.home();
//lcd.print("!!! Out of range");
//}
//delay(250);
//lcd.clear();
//}
void servopulse(int servopin, int myangle)
{
  pulsewidth = (myangle * 11) + 500;     //500~2480
  digitalWrite(servopin, HIGH);
  delayMicroseconds(pulsewidth);
  digitalWrite(servopin, LOW);
  delay(20 - pulsewidth / 1000);
}
void front_detection()
{
  for (int i = 0; i <= 15; i++) //PWM
  {
    servopulse(servopin, 60);
  }
  Front_Distance = Distance_test();
}

void left_detection()
{
  for (int i = 0; i <= 15; i++)
  {
    servopulse(servopin, 130);
  }
  Left_Distance = Distance_test();
}
void right_detection()
{
  for (int i = 0; i <= 15; i++)
  {
    servopulse(servopin, 20);
  }
 Right_Distance = Distance_test();
}



void loop()
{
  
  while (1)
  {
 SR = digitalRead(SensorRight);
 SL = digitalRead(SensorLeft);



  if (SL == LOW && SR == LOW)
  {
    run(1);
  }
  else if (SL == HIGH & SR == LOW)
  {
    left(1);
  }
  else if (SR == HIGH & SL == LOW)
  {
    right(1);
  }
  else if (SL == HIGH && SR == HIGH )
  {
    brake(10);
    left_detection();
    delay(500);
    front_detection();
    
delay(500);
    
    right_detection();
   
    
    //Serial.print("Left_Distance is ");
   // Serial.println(Left_Distance);
   // right_detection();
   // Serial.print("Right_Distance is ");
   // Serial.println(Right_Distance);
  //  front_detection();
   // Serial.print("Front_Distance is ");
   // Serial.println(Front_Distance);
    brake(100);
    //if (Left_Distance < 50)
    //{
     // left(17);
    //}
   //else if ( Right_Distance < 50)
    //{
      //right(17);
    //}
    //else if (( Front_Distance < 50 ))
    //{ 
    //spin_left(500);
    //} 
   //else if (( Right_Distance > 50) && ( Left_Distance > 50))
    //{
      //run(5);
    //}
    if (( Right_Distance > 60) && ( Left_Distance > 60) && ( Front_Distance > 60))
    {
    run(2);
    }
    else if (( Front_Distance < Right_Distance )&&( Front_Distance < Left_Distance ))
    {
      spin_left(170);
      brake(200);
    }
   else if (( Right_Distance < Front_Distance )&&( Right_Distance < Left_Distance ))
    {
      right(17);
      brake(150);
     
    }
    else if (( Left_Distance < Right_Distance )&&( Left_Distance < Front_Distance ))
    { 
    left(18);
    brake(150);
    } 

    
}
}
}
