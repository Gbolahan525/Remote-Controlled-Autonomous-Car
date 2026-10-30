#include <Servo.h>
#include <IRremote.hpp>

//Remote 
unsigned long buttonCode;
int remote_pin=11;
String condition="OFF"; 



//SERVO
Servo Servo_var;
int pin9=9;


//DC_MOTOR
int ENA=5;
int ENB=6;
int IN1=7;
int IN2=3;
int IN3=4;
int IN4=2;
int speed=200;  


//ULTRASONIC SENSOR
int trigPin=8;
int echoPin=10;
unsigned long time;
int distance;
int front_Distance;
int left_Distance;
int right_Distance;


void setup() {
  // put your setup code here, to run once:

  //REMOTE
  IrReceiver.begin(remote_pin);

  //SERVO
  Servo_var.attach(pin9);
  Servo_var.write(90);
  
  //MOTOR
      pinMode(IN1,OUTPUT);
      pinMode(IN2,OUTPUT);
      pinMode(IN3,OUTPUT);
      pinMode(IN4,OUTPUT);
      pinMode(ENA,OUTPUT);
      pinMode(ENB,OUTPUT);

  //ULTRASONIC SENSOR
      pinMode(trigPin,OUTPUT);
      pinMode(echoPin,INPUT);
      Serial.begin(9600);


      stopCar();
      delay(300);

  }

void loop() {

  // put your main code here, to run repeatedly:
   if (IrReceiver.decode()){
     buttonCode=IrReceiver.decodedIRData.decodedRawData;
     IrReceiver.resume();
    }

  Serial.println(buttonCode);

  if (buttonCode==104450040){ 
    condition="ON";
  }

  if (buttonCode==121161720){
    condition="OFF";
  }

  if (buttonCode==238143480){
    condition="turnLeft";
  }

  if (buttonCode==171296760){
    condition="turnRight";
  }

  if (buttonCode==154585080){
    condition="moveFront";
  }

  if (buttonCode==204720120){
    condition="moveBack";
  }



  if (condition=="turnRight"){
    turnRight();
    delay(200);
    stopCar();
    Serial.println("TURN-Right");
    condition="OFF";
    buttonCode=0;
  }

  if (condition=="turnLeft"){
    turnLeft();
    delay(200);
    stopCar();
    Serial.println("TURN-LEFT");
    condition="OFF";
    buttonCode=0;
  }

  if (condition=="moveFront"){
    moveFront();
    delay(200);
    stopCar();
    Serial.println("TURN-LEFT");
    condition="OFF";
    buttonCode=0;
  }

  if (condition=="moveBack"){
    moveBack();
    delay(200);
    stopCar();
    Serial.println("Move-Back");
    condition="OFF";
    buttonCode=0;
  }






  if (condition=="OFF"){
    stopCar();
  }

  

  if (condition=="ON"){
    
      Serial.println("AUTONOMOUS BUTTON DETECTED");

      //ULTRASONIC SENSOR
      digitalWrite(trigPin,LOW);
      delayMicroseconds(10);
      digitalWrite(trigPin,HIGH);
      delayMicroseconds(10);
      digitalWrite(trigPin,LOW);
      time=pulseIn(echoPin,HIGH,25000);
      distance=time*(0.0343/2);
      delay(100);

      if (time==0){
          front_Distance=100;
          }
      
      else {
          front_Distance=distance;
        }
      


        if (front_Distance>35){
          moveFront();
          Serial.print("FRONT-DISTANCE = ");
          Serial.print(front_Distance);

          }



        else {
          Serial.print("FRONT-DISTANCE IS LESSER= ");
          Serial.print(front_Distance);



          stopCar();
          delay(100);

          moveBack();
          delay(500);

          stopCar();
          delay(100);
        

        //LEFT Distance

          Servo_var.write(180);
          delay(700);
          digitalWrite(trigPin,LOW);
          delayMicroseconds(2);
          digitalWrite(trigPin,HIGH);
          delayMicroseconds(10);
          digitalWrite(trigPin,LOW);
          time=pulseIn(echoPin,HIGH,25000);
          left_Distance=time*(0.0343/2);
          
          Serial.println(left_Distance);


          // RIGHT DISTANCE

          Servo_var.write(90);
          delay(300);
          Servo_var.write(0);
          delay(700);
          digitalWrite(trigPin,LOW);
          delayMicroseconds(10);
          digitalWrite(trigPin,HIGH);
          delayMicroseconds(10);
          digitalWrite(trigPin,LOW);
          time=pulseIn(echoPin,HIGH,25000);
          right_Distance=time*(0.0343/2);


          Servo_var.write(90);
          delay(300);


          if (right_Distance>left_Distance){
            turnRight();
            delay(500);
              }
          else {
            turnLeft();
            delay(500);
            }

          stopCar();
          delay(100);       
    }
  }
}

   
     







void  turnLeft(){
        digitalWrite(IN1,HIGH);
        digitalWrite(IN2,LOW);
        analogWrite(ENA,speed);
        digitalWrite(IN3,HIGH);
        digitalWrite(IN4,LOW);
        analogWrite(ENB,speed);

      }

void turnRight(){

        digitalWrite(IN1,LOW);
        digitalWrite(IN2,HIGH);
        analogWrite(ENA,speed);
        digitalWrite(IN3,LOW);
        digitalWrite(IN4,HIGH);
        analogWrite(ENB,speed);
      
      }
      

void moveFront(){

      digitalWrite(IN1,HIGH);
      digitalWrite(IN2,LOW);
      analogWrite(ENA,speed);
      digitalWrite(IN3,LOW);
      digitalWrite(IN4,HIGH);
      analogWrite(ENB,speed);
     
      }


void moveBack(){

      digitalWrite(IN1,LOW);
      digitalWrite(IN2,HIGH);
      analogWrite(ENA,speed);
      digitalWrite(IN3,HIGH);
      digitalWrite(IN4,LOW);
      analogWrite(ENB,speed);
     
      }


void stopCar(){
    digitalWrite(IN1,LOW);
    digitalWrite(IN2,LOW);
    digitalWrite(IN3,LOW);
    digitalWrite(IN4,LOW);
    digitalWrite(ENA,0);
    digitalWrite(ENB,0);
}
