#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

const int motorPin1 = A0;
const int motorPin2 = A1;
const int enablePin = 6;

const int switchPin1 = 7;
const int switchPin2 = 8;
const int switchPin3 = 13;

const int piezoPin = 10;

bool stopped;

void setup()
{
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);

  pinMode(switchPin1, INPUT);
  pinMode(switchPin2, INPUT);
  pinMode(switchPin3, INPUT);

  pinMode(piezoPin, OUTPUT);

  digitalWrite(enablePin, HIGH);;

  lcd.begin(16, 2);
  lcd.print("Drawing Machine");

  //Before we start, we play a tune to indicate that the
  //machine had been powered on
  //The tune is the "5 tones" tune from the Close Encounters of the Third Kind move
  tone(piezoPin, 587, 500);
  delay(500);
  tone(piezoPin, 659, 500);
  delay(500);
  tone(piezoPin, 523, 500);
  delay(1000);
  tone(piezoPin, 294, 500);
  delay(500);
  tone(piezoPin, 330, 500);
  delay(500);
  
  stopped = true;
}

void loop()
{
  //if the motor is moving, play a random note every 300 milliseconds
  if (!stopped && (millis() % 300 == 0))
  {
    tone(piezoPin, random(440, 1000), 300);
  }
  
  int switchPinState1 = digitalRead(switchPin1);
  int switchPinState2 = digitalRead(switchPin2);
  int switchPinState3 = digitalRead(switchPin3);

  //controlling the motors based on button presses
  //and updating lcd based on motor status
  if ((switchPinState1 == HIGH) && (switchPinState2 == LOW) && (switchPinState3 == LOW))
  {
    lcd.setCursor(0, 1);
    lcd.print("Direction 1");
    digitalWrite(motorPin1, LOW);
    digitalWrite(motorPin2, HIGH);
    stopped = false;
  }
  else if ((switchPinState1 == LOW) && (switchPinState2 == HIGH) && (switchPinState3 == LOW))
  {
    lcd.setCursor(0, 1);
    lcd.print("Direction 2");
    digitalWrite(motorPin1, HIGH);
    digitalWrite(motorPin2, LOW);
    stopped = false;
  }
  else if ((switchPinState1 == LOW) && (switchPinState2 == LOW) && (switchPinState3 == HIGH))
  {
    lcd.setCursor(0, 1);
    lcd.print("Stopped    ");
    digitalWrite(motorPin1, LOW);
    digitalWrite(motorPin2, LOW);    
    stopped = true;
  }
}
