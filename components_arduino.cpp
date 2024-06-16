//including libraries that are going to be used to work with LCD and servo motors
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <Servo.h>


LiquidCrystal_I2C lcd(0x27, 16, 2); // Adjust the address if necessary

Servo servoMotor1; // Create the first servo object to control the first servo
Servo servoMotor2; // Create the second servo object to control the second servo

int startB = 1; //start button , pin 1
int cur_start = 0;
int cur_state = 0; //cur_state
int endB = 13; //end button , pin 13
int Pir2Pin = 16; //PIR sensor in the first part of the machine

int pir2State = LOW; //State of the PIR motion sensor
int Pir2val = 0;
int counter = 0; //counter for given bottles
String op;
int cm; //distance for the sensor in the first part
int c = 1; //distance for the sensor in the second part
int triggerPin = 9; //for the ultrasonic distance sensor which checks is it full
int echoPin = 8; //for the ultrasonic distance sensor which checks is it full
int trigger = 4;//for the ultrasonic distance sensor which checks is bottle included
int echo = 5;//for the ultrasonic distance sensor which checks is bottle included
int triggerC = 11; //for the ultrasonic distance sensor which works as a counter
int echoC = 12;  //for the ultrasonic distance sensor which works as a counter
int full; //state of the fullness of the machine
int c_count; ////distance for the sensor which works as a counter

void setup() {

  servoMotor1.attach(7); // Attaches the first servo on pin 9 to the servo object
  servoMotor2.attach(6); // Attaches the second servo on pin 10 to the servo object
  servoMotor2.write(35);
//Setup all devices -> Input, Output and Pins
  pinMode(startB, INPUT);
  pinMode(endB, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(Pir2Pin, INPUT);
  lcd.begin(16, 2);
  lcd.init();
  lcd.backlight();
  Serial.begin(9600);
}

//for the ultrasonic distance sensor which checks is it full
long readUltrasonicDistance() {
  pinMode(triggerPin, OUTPUT);
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  pinMode(echoPin, INPUT);
  return pulseIn(echoPin, HIGH);
}

//for the ultrasonic distance sensor which checks is bottle included
long readUltrasonic() {
  pinMode(trigger, OUTPUT);
  digitalWrite(trigger, LOW);
  delayMicroseconds(2);
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger, LOW);
  pinMode(echo, INPUT);
  return pulseIn(echo, HIGH);
}

 //for the ultrasonic distance sensor which works as a counter
long readUltra() {
  pinMode(triggerC, OUTPUT);
  digitalWrite(triggerC, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerC, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerC, LOW);
  pinMode(echo, INPUT);
  return pulseIn(echoC, HIGH);
}

void loop() {
//States of the start and end buttons
  int startState = digitalRead(startB); // Corrected variable name
  int endState = digitalRead(endB); // Corrected variable name

//Start the program, if the start button pressed
  if ((startState == LOW && cur_state == 0)) {
	cur_state = 1;
	lcd.clear();
	servoMotor2.write(35);
  }
  cm = 0.01723 * readUltrasonicDistance();
  c = 0.01723 * readUltrasonic();

  if (cur_state == 0) {
	counter = 0;
  }
//Debugging
  Serial.print("Print cm: ");
  Serial.println(cm);

  if (c != 0) {
//End program, if end button pressed
	if ((endState == LOW && cur_state == 1)) {
  	cur_state = 0;
//if at least one bottle was given to the machine, then show the promocode
  	if (counter > 0) {
    	Promo(counter);
  	}
	}
//If machine is full and prof=gram is started
	if ((cm <= 8 && cur_state == 1)) {
//show that the machine is full

  	lcd.clear();
  	lcd.setCursor(0, 0);
  	lcd.print("Machine is full");
//And show promocode if at least one bottle was given to the machine, then show the promocode
  	if (cm <= 8) {
    	Promo(counter);
    	cur_state = 0;
  	}
	}

	cm = 0.01723 * readUltrasonicDistance();

//if the distance between sensor and the bottles is less then  machine full state is on
	if (cm <= 8) {
  	full = 1;
	} 
//else it is off
else {
  	full = 0;
	}
//if full is on, check the full state as long as it is not full again -> it means that other part of code (other devices) would not work
	while (full && cur_state == 0) {
  	lcd.setCursor(0, 0);
//Show that the machine is full
  	lcd.print("Machine is Full ");
  	Serial.println(cm);
  	delay(500);
  	delay(1000);
  	cm = 0.01723 * readUltrasonicDistance();
  	if (cm <= 8) {
    	full = 1;
  	} else {
    	full = 0;
    	lcd.clear();
  	}
	}

//if machine is on, other sensors could start their work
	if (cur_state == 1) {
  	c = 0.01723 * readUltrasonic();
  	Serial.print("Print c: ");
  	Serial.println(c);
  	delay(750);
  	int motionDetected = digitalRead(15); // Read the PIR sensor
//if bottle is given
  	if (motionDetected == HIGH && c <= 8) {
//motors open the door, and bottle falls down
    	servoMotor1.write(0); // Rotate first servo to 90 degrees
    	servoMotor2.write(120); // Rotate second servo to 90 degree
    	delay(500); // Wait for 3 seconds before moving back

    	c_count = 0.01723 * readUltra();
    	Serial.print("Print c-count: ");
    	Serial.println(c_count);
//every time when bottle falls down, counter in LCD increase and printed
    	if (c_count <= 12 && c_count != 0) {
      	counter = counter + 1;
      	lcd.setCursor(0, 0);
      	lcd.print("Count: ");
      	lcd.print(counter);
      	delay(10);
    	}
    	Serial.println(counter);
    	delay(1000);
//after  second motors close the doors
     servoMotor1.write(90); // Rotate first servo to 90 degrees
    	servoMotor2.write(30);
    	delay(500); // Short delay before turning off the LED and proceeding
    	Serial.println("Motor babe!");
    	digitalWrite(13, LOW); // Turn off the LED
  	}
	}
	if (cur_state == 0) {
  	counter = 0;
  	lcd.setCursor(0, 0);
  	lcd.print("Press start!");
  	delay(2000);
	} else {
  	lcd.setCursor(0, 0);
  	lcd.print("Count: ");
  	lcd.print(counter);
  	delay(10);
	}
  }
}

//Function to print different promocode for different cases of the counter
void Promo(int counter) {
  if (counter > 0) {
	lcd.setCursor(0, 1);
	lcd.print("Wait for promo..");
	delay(2000);
	lcd.clear();
	lcd.clear();
	lcd.setCursor(0, 0);
	lcd.print("Promocode:");
	
	lcd.setCursor(0, 1);
	if (counter <= 3) {
  	lcd.print("choco");
	} else if (counter > 3 && counter < 8) {
  	lcd.print("tea");
	} else if (counter >= 8) {
  	lcd.print("coffee");
	}

	delay(5000);
	lcd.clear();
  }
}

