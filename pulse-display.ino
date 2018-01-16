#include<LiquidCrystal.h>

int CONTRAST           = 90;
int BACKLIGHT          = 20;
int i                  = 0;
//defining lcd pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

//  Variables
int PulseSensorPurplePin = 0;        // Pulse Sensor PURPLE WIRE connected to ANALOG PIN 0
int LED13 = 13;   //  The on-board Arduion LED


int Signal;                // holds the incoming raw data. Signal value can range from 0-1024
int Threshold = 550;            // Determine which Signal to "count as a beat", and which to ingore.

int max = 0;

void setup() {

  //Display setup
  analogWrite(6, CONTRAST);
  analogWrite(9, BACKLIGHT);
  Serial.begin(9600);
  Serial.setTimeout(50);
  lcd.begin(16,2);
  lcd.print("Pulse Value");

  //Pulse SetUp
  pinMode(LED13,OUTPUT);         // pin that will blink to your heartbeat!

}
void loop() {
  Signal = analogRead(PulseSensorPurplePin);  // Read the PulseSensor's value.
                                              // Assign this value to the "Signal" variable.
  Serial.println(Signal);                    // Send the Signal value to Serial Plotter.

  if(Signal > Threshold){                          // If the signal is above "550", then "turn-on" Arduino's on-Board LED.
     digitalWrite(LED13,HIGH);
   } else {
     digitalWrite(LED13,LOW);                //  Else, the sigal must be below "550", so "turn-off" this LED.
   }

   //Logic for displaying pulse value on lcd
   if (Signal > max) {
     max = Signal;
   } else {
     if (Signal < max) {
       lcd.setCursor(0, 1);
       lcd.print(max);
       max = Signal;
       delay(1000);
     }
   }

    delay(10);
}
