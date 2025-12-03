
 
#include <Servo.h>
Servo myservo;
byte servostart = 105;
int distanceleft = 0;
int distanceright = 0;
long t, cm;



#define IN1 4
#define IN2 3


#define IN3 1
#define IN4 2



#define Trig 7
#define Echo 6



void setup() {
  myservo.attach(5);

  
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  

  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  //Sensor
  pinMode(Trig, OUTPUT);
  pinMode(Echo, INPUT);
  Serial.begin(9600);
  start();
}
void loop() {
  getdistance();
  Serial.println(cm);
  int leftdistance = 0;
  int rightdistance = 0;

  if (cm <= 20) {
    Stop();
    delay(200);
    leftdistance = leftsee();
    rightdistance = rightsee();

    if (leftdistance >= rightdistance) {
      turnleft();
      delay(200);
      Stop();
    } else {
      turnright();
      delay(200);
      Stop();
    }
  } else {
    forward();
    Serial.println("forward");
  }
}

void forward() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void turnright() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}
void turnleft() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}
void Stop() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void start() {
  delay(3000);
  for (int a = 0; a < 4; a++) {
    myservo.write(servostart);
    delay(50);
    myservo.write(40);
    delay(50);
    myservo.write(90);
    delay(50);
    myservo.write(servostart);
  }
}

int leftsee() {
  myservo.write(servostart);
  delay(1000);
  myservo.write(175);
  delay(1000);
  distanceleft = getdistance();
  myservo.write(servostart);
  return distanceleft;
}
int rightsee() {
  myservo.write(servostart);
  delay(1000);
  myservo.write(5);
  delay(1000);
  distanceright = getdistance();
  myservo.write(servostart);
  return distanceright;
}
int getdistance() {
  digitalWrite(Trig, LOW);
  delayMicroseconds(4);
  digitalWrite(Trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trig, LOW);
  t = pulseIn(Echo, HIGH);
  cm = t / 29 / 2;
  return cm;
}

      

