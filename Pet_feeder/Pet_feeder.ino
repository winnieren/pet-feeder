#include <Servo.h>
Servo fwServo; // create servo object to control servo for food and water
Servo doorServo; // servo object for door opening and closing
int pos = 0; // variable to store servo position
int hours, minutes, seconds = 0;
const int trigPin = 6;
const int echoPin = 7;

void setup() {

  Serial.begin(9600);
  TCNT1 = 0;
//  attachInterrupt(digitalPinToInterrupt(//Set interrupt to send time when food is consumed
  fwServo.attach(9); // attaches servo on pin 9 to food and water servo
  pinMode (trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

}

void loop() {
  long duration, inches;
  digitalWrite(trigPin, LOW);
  delay(2);
  digitalWrite(trigPin, HIGH);
  delay(10);
  digitalWrite(trigPin, LOW);
   
   // Read the signal from the sensor: a HIGH pulse whose
   
   // duration is the time (in microseconds) from the sending
   
   // of the ping to the reception of its echo off of an object.
   duration = pulseIn(echoPin, HIGH);
   inches = microsecondsToInches(duration);
   // turns the servo to dispense food if sensor is >6 inches away from food
   if (inches >= 6) {
    turn();
    Serial.println("Turning");
    }
   // Re-check position if the sensor is <6 inches away (no need to refill food)
   
   else if (inches < 6) {
    fwServo.write(pos); 
    Serial.println("Measure");
   }
   
   // Tell the Arduino to wait 1 seconds before pinging the Ultrasonic Sensor again.
   delay(1000);
   Serial.println(inches); //used for testing and checking how far food is from sensor

}

long microsecondsToInches(long microseconds){
  return microseconds / 74 / 2;
}
 
//turns the servo 180 degrees and back
void turn() {
  for (pos = 0; pos < 180; pos += 1){ // 0 to 180 degrees 
    fwServo.write(pos); //servo goes to position for pos
    delay(5);
//  int time = millis() - startTime;
//  Serial.print(time);
  }

  delay(1000);
  
  for(pos = 180; pos >=1; pos-=1){
    fwServo.write(pos);
    delay(5);
    }
}




void getTime(){
  //minutes = (millis()-start_time)/60000;
  hours = minutes/60;
  minutes = minutes - hours*60;
}

void motor(int n){
  //code to turn motor 1 (food bowl), motor 2 (water bowl), motor 3(door)
}


void foodBottleEmpty(){
  getTime();
  Serial.println("food bottle empty at " + String(hours) + "H " + String(minutes) +"M.");
}

void waterBottleEmpty(){
  getTime();
  Serial.println("water bottle empty at " + String(hours) + "H " + String(minutes) +"M.");
}

void foodBowlEmpty(){
  getTime();
  Serial.println("food bowl empty at " + String(hours) + "H " + String(minutes) +"M.");
  motor(1);
}

void waterBowlEmpty(){
  getTime();
  Serial.println("water bowl empty at " + String(hours) + "H " + String(minutes) +"M.");
  motor(2);
}

void door(){
  getTime();
  Serial.println("pet doored at" + String(hours) + "H " + String(minutes) +"M.");
  motor(3);
}



