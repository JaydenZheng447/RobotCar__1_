
#include <SoftwareSerial.h>

// // ok
int motA_pin1 = 11;
int motA_pin2 = 11;
int motB_pin1 = 11;
int motB_pin2 = 11;
char command;
int drain = 3;
int gate = 2;
int PWM_Speed = 200; // medium speed (currentSpeed = 2)
int currentSpeed = 2;
// 2 stands for medium(123), 1 stands for slow(61), 3 stands for fast (255)

// int MOSFET_UL_GATE = 13; // mosfet upper right gate terminal
// int MOSFET_LL_GATE = 2;
// int MOSFET_UR_GATE = 12;
// int MOSFET_LR_GATE = 3;
int MOSFET_DRAIN = 4;
int MOSFET_GATE = 6;

SoftwareSerial btSerial(12, 13);

void setup()
{

  pinMode(motA_pin1, OUTPUT);
  pinMode(motA_pin2, OUTPUT);
  pinMode(motB_pin1, OUTPUT);
  pinMode(motB_pin2, OUTPUT);

  // temp
  pinMode(drain, OUTPUT);
  pinMode(gate, OUTPUT);
  pinMode(MOSFET_DRAIN, OUTPUT);
  pinMode(MOSFET_GATE, OUTPUT);
  // pinMode(MOSFET_LL_GATE, OUTPUT);
  // pinMode(MOSFET_LR_GATE, OUTPUT);
  // pinMode(MOSFET_UL_GATE, OUTPUT);
  // pinMode(MOSFET_UR_GATE, OUTPUT);
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
  // digitalWrite(motA_pin1, HIGH);
  // digitalWrite(motA_pin2, LOW);

  // digitalWrite(motB_pin1, HIGH);
  // digitalWrite(motB_pin2, LOW);
  digitalWrite(gate, HIGH);
  digitalWrite(drain, HIGH);
  digitalWrite(MOSFET_DRAIN, HIGH);
  digitalWrite(MOSFET_GATE, HIGH);
  // digitalWrite(MOSFET_UR_GATE, HIGH);
  // digitalWrite(MOSFET_LL_GATE, HIGH);
  // digitalWrite(MOSFET_UR_DRAIN, HIGH);
  delay(10);
}

void backward()
{
  Serial.println("backward");
  digitalWrite(motA_pin1, LOW);
  digitalWrite(motA_pin2, HIGH);

  digitalWrite(motB_pin1, LOW);
  digitalWrite(motB_pin2, HIGH);

  digitalWrite(gate, HIGH);
  analogWrite(drain, PWM_Speed);
  digitalWrite(MOSFET_GATE, HIGH);
  analogWrite(MOSFET_DRAIN, PWM_Speed);

  // digitalWrite(MOSFET_UL_GATE, HIGH);
  // digitalWrite(MOSFET_LR_GATE, HIGH);
  // digitalWrite(MOSFET_UL_DRAIN, HIGH);
  delay(10);
}

void left()
{
  Serial.println("left");
  digitalWrite(motA_pin1, LOW);  // left mot REV
  digitalWrite(motA_pin2, LOW);  // left mot rev
  digitalWrite(motB_pin1, HIGH); // right mot front
  digitalWrite(motB_pin2, LOW);  // right mot front
  delay(10);
  analogWrite(gate, PWM_Speed);
  analogWrite(drain, PWM_Speed);
  analogWrite(MOSFET_GATE, PWM_Speed);
  analogWrite(MOSFET_DRAIN, PWM_Speed);
}

void right()
{
  Serial.println("right");
  digitalWrite(motA_pin1, HIGH);
  digitalWrite(motA_pin2, LOW);
  digitalWrite(motB_pin1, LOW);
  digitalWrite(motB_pin2, LOW);
  analogWrite(gate, PWM_Speed);
  digitalWrite(drain, HIGH);
  digitalWrite(MOSFET_DRAIN, HIGH);
  analogWrite(MOSFET_GATE, PWM_Speed);
  delay(10);
}

void stop()
{
  Serial.println("stop");
  digitalWrite(motA_pin1, LOW);
  digitalWrite(motA_pin2, LOW);
  digitalWrite(motB_pin1, LOW);
  digitalWrite(motB_pin2, LOW);
  digitalWrite(gate, LOW);
  digitalWrite(drain, LOW);
  digitalWrite(MOSFET_DRAIN, LOW);
  digitalWrite(MOSFET_GATE, LOW);
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
    PWM_Speed = 100;
  }
  else if (currentSpeed == 3) // fast
  {
    delay(500);
    PWM_Speed = 220;
    delay(1000);
    PWM_Speed = 190;
    delay(1000);
    PWM_Speed = 100;
  }
  Serial.println(PWM_Speed);
  currentSpeed = 1;
  Serial.println("CurrSpeedType: " + currentSpeed);
}