#include <Wire.h>
#include <OzOLED.h>
#include <SPI.h>
#include <Arduino.h>
#include "U8glib.h"
#include "max6675.h"
#include <RGB.h>

int ktcSO = 8;
int ktcCS = 9;
int ktcCLK = 10;
int far;
int maxT =0;
char temp[10];

MAX6675 ktc(ktcCLK, ktcCS, ktcSO);
RGB led;

void setup() {
    OzOled.init();                 // initialze SDD1306 OLED display
//  OzOled.sendCommand(0x8d);        // Set displays inbuilt inverter on
//  OzOled.sendCommand(0x14);          
//  OzOled.setBrightness(0xFF);      // ... and brightness to max
//  OzOled.clearDisplay();           // Clear the screen
//        // Set display to Normal mode


  OzOled.sendCommand(0x8d); // charge pump regulator
  OzOled.sendCommand(0x14); // VCC
  OzOled.sendCommand(0xA0 | 0x1); //
  OzOled.sendCommand(0xC8);
  OzOled.clearDisplay();
}

void loop() {
  
  OzOled.setNormalDisplay(); 
  returnTemp();
  delay(500); 
  
  
}  
 void returnTemp(){
  
  far = ktc.readFahrenheit();
  if(maxT <= far){
    maxT = far;
  }
  far = 251;
  itoa(far,temp,10);
  OzOled.sendCommand(0x14); 
  OzOled.printString("Max temp:",0,0);     
  OzOled.printNumber ((long)maxT,9,0);
  OzOled.printString("o",10,3); 
  OzOled.printString("F",11,4);  
  OzOled.printBigNumber (temp, 0,3);
  
  if(far <=  145){
    led.red(); 
  }
  if(far >= 145 & far <= 250){
    led.blue(); 
  }
  if(far >= 251){
    led.green();
  }
  
 }

