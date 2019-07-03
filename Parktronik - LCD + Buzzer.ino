/*
  LiquidCrystal Library - Hello World

 Demonstrates the use a 16x2 LCD display.  The LiquidCrystal
 library works with all LCD displays that are compatible with the
 Hitachi HD44780 driver. There are many of them out there, and you
 can usually tell them by the 16-pin interface.

 This sketch prints "Hello World!" to the LCD
 and shows the time.

  The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)

 Library originally added 18 Apr 2008
 by David A. Mellis
 library modified 5 Jul 2009
 by Limor Fried (http://www.ladyada.net)
 example added 9 Jul 2009
 by Tom Igoe
 modified 22 Nov 2010
 by Tom Igoe

 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/LiquidCrystal
 */

// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
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

void setup()
{
  Serial.begin(9600);
  lcd.begin(16,2);
  pinMode(6, OUTPUT);
  pinMode(5, OUTPUT);
}

void loop()
{
  // measure the ping time in cm
  cmFront = (0.01723 * readUltrasonicDistance(6, 7)) - 10;// It is minus 10 cm because the front end of the prototype is 10 cm in front of the ultrasonic sensor.
  cmBack = (0.01723 * readUltrasonicDistance(8,9 )) - 15;// Its is minus 15 cm because the back end of the prototype is 10 cm behind the ultrasonic sensor.
 
  // setting up the display setings.
  lcd.setCursor(0,0);
  lcd.print("Front:");
  lcd.print(cmFront); 
  lcd.print("              ");

  lcd.setCursor(0,1);
  lcd.print("Back:");
  lcd.print(cmBack);
  lcd.print("              ");

  // checks if you are far from an object on the both sides.
  if(cmFront > 50 && cmBack > 50)
  {
      noTone(10);
      Serial.print(cmFront);
      Serial.print(" - ");
      Serial.println(cmBack);
  }
  else
  {
    if(cmFront >= 20 && cmFront <=50)   // checks if you are closer to an object in front.
    {
      lcd.setCursor(8,0);
      lcd.print("Caution!");    // a message that should grab your attention because you are not so far from an object.
      tone(10, 300, 100);   // sound that should orientate you about the distance between the  prototype and an object if you havent or are unable to see the display.
    }
    if(cmBack >= 20 && cmBack <= 50)  // checks if you are closer to an object behind.
    {
      lcd.setCursor(8,1);
      lcd.print("Caution!");    // a message that should grab your attention because you are not so far from an object.
      tone(10, 300, 100);   // sound that should orientate you about the distance between the  prototype and an object if you havent or are unable to see the display.
    }
    if(cmFront < 20)  // checks if you are way too close to an object in front.
    {
      lcd.setCursor(8,0);   // sets where the message should be displayed on the lcd.
      lcd.print("! STOP !");    // writes the message to let you know that you are too close.
      tone(10, 600, 10);    // this is the annoying sound that should let you know that you are too close if you havent seen the display.
    }
    if(cmBack < 20) // checks if you are way too close to an object behind.
    {
      lcd.setCursor(8,1);   // sets where the message should be displayed on the lcd.
      lcd.print("! STOP !");    // writes the message to let you know that you are too close.
      tone(10, 600, 10);    // this is the annoying sound that should let you know that you are too close if you havent seen the display.
    } 
  }
  delay(250);
}
