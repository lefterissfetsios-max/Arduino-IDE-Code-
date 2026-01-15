
 
#include <Servo.h> //SERVO MOTOR LIBRARY INCLUDED 
Servo myservo;
byte servostart = 105; //SET INITIAL SERVO POSITION 
int distanceleft = 0;
int distanceright = 0;
long t, cm; //VARIABLES FOR DISTANCE READING 

//DEFINE MOTOR AND SENSOR PINS 
//MOTOR 1
#define IN1 4             
#define IN2 3

//MOTOR 2 
#define IN3 1
#define IN4 2


//SENSOR 
#define Trig 7
#define Echo 6



void setup() {
  myservo.attach(5); //INCLUDE SERVO MOTOR PIN 
//MOTOR PINS SET AS OUTPUT 
  //MOTOR 1 
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  
//MOTOR 2 
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
//SENSOR PIN TRIG SET AS OUTPUT AND ECHO PIN SET AS INPUT 
//SENSOR 
  pinMode(Trig, OUTPUT);
  pinMode(Echo, INPUT);
 //SERIAL MONITOR BEGIN 
  Serial.begin(9600);
 //THE ROBOT START FUNCTION
  start();
}
void loop() {
//THE LOOP MAKES THE CODE RUN AGAIN AND AGAIN 
 //GETS THE DISTANCE VALUE 
  getdistance();
  Serial.println(cm);
  int leftdistance = 0;
  int rightdistance = 0;
 //THE VALUES ARE CHECKED WITH THE IF CONDITION 
//IF THE DISTANCE IS EQUAL OR SMALLER THAN 2O.THE ROBOT STOPS
  if (cm <= 20) {
    Stop();
    delay(200);
   //THE SERVO MOTOR ROTATES LEFT AND TAKES THE DISTANCE USING THE ULTRASONIC SENSOR
    leftdistance = leftsee();
   //THE SERVO MOTOR ROTATES RIGHT AND TAKES THE DISTANCE USING THE ULTRASONIC SENSOR
    rightdistance = rightsee();
//IF THE DISTANCE LEFT IS GREATER TO THE DISTANCE TO THE RIGHT. THE ROBOT TURNS LEFT
    if (leftdistance >= rightdistance) {
      turnleft();
      delay(200);
      Stop();
     //IF THE DISTANCE TO THE RIGHT IS GREATER THAN TO THE LEFT. THE ROBOT TURNS RIGHT 
    } else {
      turnright();
      delay(200);
      Stop();
    }
   //ELSE THE ROBOT MOVES FOWARD 
  } else {
    forward();
    Serial.println("forward");
  }
}
//MOTOR ROTATION FUNCTIONS 
//FOR THE ROBOT TO MOVE FOWARD 
void forward() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH); //LEFT MOTOR FOWARD
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW); //RIGHT MOTOR BACKWARD 
}
//FOR THE ROBOT TO MOVE RIGHT 
void turnright() {
  digitalWrite(IN1, HIGH); //LEFT MOTOR BACKWARD
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH); //RIGHT MOTOR FOWARD
  digitalWrite(IN4, LOW);
}
//FOR THE ROBOT TO MOVE LEFT 
void turnleft() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH); //LEFT MOTOR FOWARD
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH); //RIGHT MOTOR BACKWARD 
}
//FOR THE ROBOT TO STOP 
void Stop() {
  digitalWrite(IN1, LOW); //NO PIN SET TO HIGH, THE MOTORS DONT MOVE SO THE ROBOT STOPS 
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
//THE ROBOT START FUNCTION 
//LOOP RUNS 4 TIMES AND GOES TO 3 DIFFERENT POSITION 105 , 40 AND 90 TO SHOW SERVO IS WORKING AND THE ROBOT IS POWERED ON 
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
//THE SERVO MOTOR TURN LEFT FUNCTION
int leftsee() {
  myservo.write(servostart); //CENTER
  delay(1000);
  myservo.write(175); //FULLY LEFT
  delay(1000);
  distanceleft = getdistance();
  myservo.write(servostart);
  return distanceleft;
}
//THE SERVO MOTOR TURN RIGHT FUNCTION
int rightsee() {
  myservo.write(servostart); //CENTER
  delay(1000);
  myservo.write(5); //FULLY RIGHT 
  delay(1000);
  distanceright = getdistance();
  myservo.write(servostart);
  return distanceright;
}
//THE ULTRASONIC FUNCTION 
int getdistance() {
  digitalWrite(Trig, LOW); //TRIG IS LOW 
  delayMicroseconds(4);
  digitalWrite(Trig, HIGH); //TRIG IS HIGH
  delayMicroseconds(10);
  digitalWrite(Trig, LOW); //TRIG IS LOW 
  t = pulseIn(Echo, HIGH); //MEASURE ECHO PULSE TIME 
  cm = t / 29 / 2; //29 MICROSECONDS FOR THE SPEED OF SOUND TO TRAVEL 1 CM AND DIVIDE BY 2 TO CALCULATE THE 1 WAY DISTANCE 
  return cm;
}

      

