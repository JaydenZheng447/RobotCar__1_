
#include <SoftwareSerial.h>
//  check this link for more: https://docs.arduino.cc/learn/built-in-libraries/software-serial/

// i'm making these comments for future reference
//when motors are Blue-Red IO 1 it spinss CCW, IO2 makes it spin CW
//when motors are White-Black IO 1 it spinss CCW, IO2 makes it also spin CW

//motor 2 needs to be input 2 for CW and motor 4 needs to be input 3 for CW
//motor 1 needs to be input 2 to be CW and motpr 3 needs to be input 2 to be CW
//just use the other input for each motor if you want to reverse directionality
//for this i will put motor 1 and 3 (front left and back right) in CCW and motors 2 and 4 (front right and back left) in CW

//top motor driver IO 1 and 2 refer to motor 2
//top motor driver IO 3 and 4 refer to motor 1
//bottom motor driver IO 1 and 2 refer to motor 3
//bottom motor driver IO 3 and 4 refer to motor 4

char command;
int drain = 2; // red blue motor 1
int gate = 3;
int MOSFET_DRAIN = 4; // red blue motor 2
int MOSFET_GATE = 5;
int MOSFET_BW_GATE_1 = 6; // black white motor 1
int MOSFET_BW_DRAIN_1 = 7;
int MOSFET_BW_GATE_2 = 8; // black white motor 2
int MOSFET_BW_DRAIN_2 = 9;

int PWM_Speed = 200; // medium speed (int currentSpeed = 2)
int currentSpeed = 2;
// 2 stands for medium(200), 1 stands for slow(160), 3 stands for fast (255)

SoftwareSerial btSerial(12, 13); // SoftwareSerial objectname(the wire that goes into HC05 TXD pin, the wire that goes into HC05 RXD pin)
// btSerial is the object name for this

void setup()
{

  pinMode(drain, OUTPUT);
  pinMode(gate, OUTPUT);
  pinMode(MOSFET_DRAIN, OUTPUT);
  pinMode(MOSFET_GATE, OUTPUT);
  pinMode(MOSFET_BW_GATE_1, OUTPUT);
  pinMode(MOSFET_BW_DRAIN_2, OUTPUT);
  pinMode(MOSFET_BW_DRAIN_1, OUTPUT);
  pinMode(MOSFET_BW_GATE_2, OUTPUT);
  Serial.begin(9600);

  Serial.println("Setup...");
  btSerial.begin(9600);
  btSerial.print("command");
}

void loop()
{

  if (btSerial.available() > 0)
  {
    command = btSerial.read();
    Serial.println(command);

    btSerial.print(command);

    if (command == 'F')
    {
      forward();
    }
    else if (command == 'L')
    {
      left();
    }
    else if (command == 'R')
    {
      right();
    }
    else if (command == 'B')
    {
      backward();
    }
    else if (command == 'Q')
    {
      fast();
    }
    else if (command == 'W')
    {
      medium();
    }
    else if (command == 'E')
    {
      slow();
    }
    else if (command == 'S')
    {
      stop();
    }
    else
    {
      // stop();
    }
  }
}

void forward()
{

  Serial.println("forward");

  digitalWrite(gate, HIGH);
  digitalWrite(drain, HIGH);
  digitalWrite(MOSFET_DRAIN, HIGH);
  digitalWrite(MOSFET_GATE, HIGH);
  digitalWrite(MOSFET_BW_GATE_2, HIGH);
  digitalWrite(MOSFET_BW_GATE_1, HIGH);
  digitalWrite(MOSFET_BW_DRAIN_1, HIGH);
  digitalWrite(MOSFET_BW_DRAIN_2, HIGH);

  delay(10);
}

void backward()
{
  Serial.println("backward");

  digitalWrite(gate, HIGH);
  analogWrite(drain, PWM_Speed);
  digitalWrite(MOSFET_GATE, HIGH);
  analogWrite(MOSFET_DRAIN, PWM_Speed); // motor speed seems to dependent on the voltage in both the drain and gate pin

  digitalWrite(MOSFET_BW_GATE_1, HIGH);
  digitalWrite(MOSFET_BW_GATE_2, HIGH);
  analogWrite(MOSFET_BW_DRAIN_1, PWM_Speed);
  analogWrite(MOSFET_BW_DRAIN_2, PWM_Speed);

  delay(10);
}

void left()
{
  Serial.println("left");

  delay(10);
  analogWrite(gate, PWM_Speed);
  analogWrite(drain, PWM_Speed);
  analogWrite(MOSFET_GATE, PWM_Speed);
  analogWrite(MOSFET_DRAIN, PWM_Speed);
  analogWrite(MOSFET_BW_DRAIN_1, PWM_Speed);
  analogWrite(MOSFET_BW_GATE_1, PWM_Speed);
  analogWrite(MOSFET_BW_DRAIN_2, PWM_Speed);
  analogWrite(MOSFET_BW_GATE_2, PWM_Speed);
}

void right()
{
  Serial.println("right");

  analogWrite(gate, PWM_Speed);
  digitalWrite(drain, HIGH);
  digitalWrite(MOSFET_DRAIN, HIGH);
  analogWrite(MOSFET_GATE, PWM_Speed);
  analogWrite(MOSFET_BW_GATE_1, PWM_Speed);
  analogWrite(MOSFET_BW_GATE_2, PWM_Speed);
  digitalWrite(MOSFET_BW_DRAIN_1, HIGH);
  digitalWrite(MOSFET_BW_DRAIN_2, HIGH);
  delay(10);
}

void stop()
{
  Serial.println("stop");
  digitalWrite(gate, LOW);
  digitalWrite(drain, LOW);
  digitalWrite(MOSFET_DRAIN, LOW);
  digitalWrite(MOSFET_GATE, LOW);
  digitalWrite(MOSFET_BW_GATE_2, LOW);
  digitalWrite(MOSFET_BW_GATE_1, LOW);
  digitalWrite(MOSFET_BW_DRAIN_1, LOW);
  digitalWrite(MOSFET_BW_DRAIN_2, LOW);
}

// slow = 160 mediu = 200 fast=255
void fast()
{
  Serial.println(PWM_Speed);
  if (currentSpeed == 2) // medium
  {
    delay(500);
    PWM_Speed = 220;
    delay(1000);
    PWM_Speed = 255;
  }
  else if (currentSpeed == 1) // slow
  {
    delay(500);
    PWM_Speed = 200;
    delay(1000);
    PWM_Speed = 220;
    delay(1000);
    PWM_Speed = 255;
  }
  Serial.println(PWM_Speed);
  currentSpeed = 3;
  Serial.println("CurrSpeedType: " + currentSpeed);
}
void medium()
{
  Serial.println(PWM_Speed);
  if (currentSpeed == 3) // fast
  {
    delay(500);
    PWM_Speed = 220;
    delay(500);
    PWM_Speed = 200;
  }
  else if (currentSpeed == 1) // slow
  {
    delay(500);
    PWM_Speed = 200;
  }
  Serial.println(PWM_Speed);
  currentSpeed = 2;
  Serial.println("CurrSpeedType: " + currentSpeed);
}
void slow()
{
  Serial.println(PWM_Speed);
  if (currentSpeed == 2) // medium
  {
    delay(500);
    PWM_Speed = 160;
  }
  else if (currentSpeed == 3) // fast
  {
    delay(500);
    PWM_Speed = 220;
    delay(1000);
    PWM_Speed = 190;
    delay(1000);
    PWM_Speed = 160;
  }
  Serial.println(PWM_Speed);
  currentSpeed = 1;
  Serial.println("CurrSpeedType: " + currentSpeed);
}