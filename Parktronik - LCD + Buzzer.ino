/*
  Ping))) Sensor

  This sketch reads a PING))) ultrasonic
  rangefinder and returns the distance to the
  closest object in range. To do this, it sends a
  pulse to the sensor to initiate a reading, then
  listens for a pulse to return.  The length of
  the returning pulse is proportional to the
  distance of the object from the sensor.

  The circuit:
   * +V connection of the PING))) attached to +5V
   * GND connection attached to ground
   * SIG connection attached to digital pin 7

  http://www.arduino.cc/en/Tutorial/Ping

  This example code is in the public domain.
*/
#include <Wire.h>
#include<LCD.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd1(0x3F,2,1,0,4,5,6,7,3,POSITIVE);
//LiquidCrystal_I2C lcd1(0x3F, 16,2);

int cmFront = 0;
int cmBack = 0;

long readUltrasonicDistance(int triggerPin, int echoPin)
{
  pinMode(triggerPin, OUTPUT);  // Clear the trigger
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  // Sets the trigger pin to HIGH state for 10 microseconds
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  pinMode(echoPin, INPUT);
  // Reads the echo pin, and returns the sound wave travel time in microseconds
  return pulseIn(echoPin, HIGH);
}



 // LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup()
{
  Serial.begin(9600);
  lcd1.begin(16,2);
  lcd1.backlight();
  
//  lcd.begin(16, 2);
 // lcd.print(cm);
  
  pinMode(6, OUTPUT);
  pinMode(5, OUTPUT);
}

void loop()
{
  // measure the ping time in cm
  cmFront = (0.01723 * readUltrasonicDistance(6, 7)) - 10;
  cmBack = (0.01723 * readUltrasonicDistance(8,9 )) - 20;
 
  lcd1.setCursor(0,0);
  lcd1.print("Front: ");
  lcd1.print(cmFront); 
  lcd1.print("            ");

  lcd1.setCursor(0,1);
  lcd1.print("Back: ");
  lcd1.print(cmBack); 
  lcd1.print("            ");

  if(cmFront > 50 && cmBack > 50)
  {
      noTone(5);
      Serial.print(cmFront);
      Serial.print(" - ");
      Serial.println(cmBack);
  }
  else
  {
    if((cmFront > 20 && cmFront<=50)|| (cmBack > 20 && cmBack<=50))
    {
      tone(5, 300, 70);
    }
    if(cmFront < 20 || cmBack < 20)
    {
      tone(5, 600, 30);
    } 
  }


  /*
  
 
*/
  //  lcd.print(cm);
    
  
  delay(100);
 // lcd.clear();
}
