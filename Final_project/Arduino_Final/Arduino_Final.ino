#include <Stepper.h>
#include <Bounce2.h>
#define stepsPerRevolution 2048
#include <TimedAction.h>

/* Wiring: Ultrasonic Sensor -> Arduino:
  - VCC  -> 5VDC
  - TRIG -> Pin 7
  - ECHO -> Pin 6
  - GND  -> GND
  - // Wiring:Stepper Motor
  // Pin 8 to IN1 on the ULN2003 driver
  // Pin 9 to IN2 on the ULN2003 driver
  // Pin 10 to IN3 on the ULN2003 driver
  // Pin 11 to IN4 on the ULN2003 driver*/

Stepper myStepper = Stepper(stepsPerRevolution, 8, 10, 9, 11);
int spincount = 0;
int rainbowcount = 0;
const int SW = 2;
int check = 0;
int count = 0;
int r = 0;
int g = 0;
int b = 0;
int red;
int green;
int blue;
int trigPin = 7;    // TRIG pin
int echoPin = 6;    // ECHO pin
int redPin = 5;     // RGB red pin
int greenPin = 3;   // RGB green pin
int bluePin = 4;    // RGB blue pin

float duration_us, distance_cm;

void setup() {
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(SW, INPUT_PULLUP);
  myStepper.setSpeed(15);
  Serial.begin (9600);

  // configure the trigger pin to output mode
  pinMode(trigPin, OUTPUT);
  // configure the echo pin to input mode
  pinMode(echoPin, INPUT);
}


void motorCW()
{
  // Step one revolution in one direction:
  //Serial.println("clockwise");
  myStepper.setSpeed(15);
  myStepper.step(1000);
}

void motorACW()
{
  // Step one revolution in the other direction:
  //Serial.println("counterclockwise");
  myStepper.setSpeed(15);
  myStepper.step(-1000);
}

void rainbowlight() {
  if (rainbowcount ==0){
  analogWrite(redPin, 255);
  analogWrite(greenPin, 0);
  analogWrite(bluePin, 0);
  rainbowcount ++;
  }
  else if (rainbowcount ==1){
  analogWrite(redPin, 255);
  analogWrite(greenPin, 60);
  analogWrite(bluePin, 0);
  rainbowcount ++;
  }
   else if (rainbowcount ==2){
  analogWrite(redPin, 255);
  analogWrite(greenPin, 120);
  analogWrite(bluePin, 0);
    rainbowcount ++;
  }
  else if (rainbowcount ==3){
  analogWrite(redPin, 0);
  analogWrite(greenPin, 200);
  analogWrite(bluePin, 0);
  rainbowcount ++;
  }
  else if (rainbowcount ==4){
  analogWrite(redPin, 110);
  analogWrite(greenPin, 255);
  analogWrite(bluePin, 200);
  rainbowcount ++;
  }
  else if (rainbowcount ==5){
  analogWrite(redPin, 0);
  analogWrite(greenPin, 255);
  analogWrite(bluePin, 255);
  rainbowcount ++;
  }
  else if (rainbowcount ==6){
  analogWrite(redPin, 0);
  analogWrite(greenPin, 0);
  analogWrite(bluePin, 255);
  rainbowcount ++;
  }
  else if (rainbowcount ==7){
  analogWrite(redPin, 75);
  analogWrite(greenPin, 0);
  analogWrite(bluePin, 130);
  rainbowcount ++;
  }
  else if (rainbowcount ==8){
  analogWrite(redPin, 138);
  analogWrite(greenPin, 43);
  analogWrite(bluePin, 226);
  rainbowcount ++;
  }
  else if (rainbowcount ==9){
  analogWrite(redPin, 148);
  analogWrite(greenPin, 0);
  analogWrite(bluePin, 211);
  rainbowcount ++;
  }
  else if (rainbowcount ==10){
  analogWrite(redPin, 255);
  analogWrite(greenPin, 0);
  analogWrite(bluePin, 255);
  rainbowcount = 0;
  }
}

void warmlight() {
  analogWrite(redPin, 255);
  analogWrite(greenPin, random(0, 70));
  analogWrite(bluePin, 0);
}

void coollight() {
  analogWrite(redPin, random(0, 255));
  analogWrite(greenPin, 255);
  analogWrite(bluePin, random(0, 255));
}
void _setColor() {
  analogWrite(redPin, r);
  analogWrite(greenPin, g);
  analogWrite(bluePin, b);
}

TimedAction motorcwthread = TimedAction(0,motorCW);
TimedAction motoracwthread = TimedAction(0,motorACW);
TimedAction rainbowthread = TimedAction(3000,rainbowlight);
TimedAction warmlightthread = TimedAction(3000,warmlight);
TimedAction coollightthread = TimedAction(3000,coollight);

void loop() {
    digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // measure duration of pulse from ECHO pin
  duration_us = pulseIn(echoPin, HIGH);

  // calculate the distance
  distance_cm = 0.017 * duration_us;
  // print the value to Serial Monitor
  Serial.print("distance: ");
  Serial.print(distance_cm);
  Serial.println(" cm");
  
  if (distance_cm >= 40)
  {
    check++;
    if (check >=8 && count==1 )
    {
      digitalWrite(redPin, LOW);
      digitalWrite(greenPin, LOW);
      digitalWrite(bluePin, LOW);
      myStepper.setSpeed(0);
      check =0;
    }
    if (check >= 8 && count==2)
    {
      digitalWrite(redPin, LOW);
      digitalWrite(greenPin, LOW);
      digitalWrite(bluePin, LOW);
      myStepper.setSpeed(0);
      check =0;
    }
    if (check >= 8 && count==3)
    {
      digitalWrite(redPin, LOW);
      digitalWrite(greenPin, LOW);
      digitalWrite(bluePin, LOW);
      myStepper.setSpeed(0);
      check =0;
    }
  }
  else
  {
    check = 0;
    int status = digitalRead(SW);
    if (status == LOW)
    {
      count++;
      delay(1000);
      if (count > 3){
        count = 1;

      }
    }
  }
  Serial.println(check);
  Serial.println(count);
  
  switch (count)
    {
      case 1:
          if (spincount <=5){
          rainbowthread.check();
          motorcwthread.check();
          
          }
          else{
          rainbowthread.check();
          motoracwthread.check();
          if (spincount ==10)
          spincount = 0;
          }
          spincount++;
          break;
      case 2:
          if (spincount <=5){
          warmlightthread.check();
          motorcwthread.check();
          }
          else{
          warmlightthread.check();
          motoracwthread.check();
          if (spincount ==10)
          spincount = 0;
          }
          spincount++;
          break;

      case 3:

           if (spincount <=5){
           coollightthread.check();
          motorcwthread.check();
          }
          else{
          coollightthread.check();
          motoracwthread.check();
          if (spincount ==10)
          spincount = 0;
          }
          spincount++;
          break;
        
    }
}
