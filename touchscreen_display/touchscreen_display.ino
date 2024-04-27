// Portable Automated Microgreen Farm - Touch Screen Display Interface using UART
// Created by Ruopu Dong and Faizan Darsot

#include <SPI.h>
#include <string.h>
#include "Adafruit_GFX.h"
#include "Adafruit_HX8357.h"
#include "TouchScreen.h"

#define TFT_CS 10
#define TFT_DC 9
#define TFT_RST -1 // RST can be set to -1 if you tie it to Arduino's reset

#define YP A2  // must be an analog pin, use "An" notation!
#define XM A3  // must be an analog pin, use "An" notation!
#define YM 7   // can be a digital pin
#define XP 8   // can be a digital pin

// This is calibration data for the raw touch data to the screen coordinates
#define TS_MINX 110
#define TS_MINY 80
#define TS_MAXX 900
#define TS_MAXY 940

#define MINPRESSURE 10
#define MAXPRESSURE 1000

#define BOXSIZE 350

// Use hardware SPI (on Uno, #13, #12, #11) and the above for CS/DC
Adafruit_HX8357 tft = Adafruit_HX8357(TFT_CS, TFT_DC, TFT_RST);
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  //Serial.println("HX8357D Test!"); 
  tft.begin();
  tft.fillScreen(HX8357_GREEN);
  tft.setCursor(0, 0);
  tft.setTextColor(HX8357_BLACK);  
  tft.setRotation(3);
  tft.setTextSize(4);
  tft.println("Hello\nEatclusive!");
  String temp = Serial.readStringUntil('\n');
  while(temp == ""){
    temp = Serial.readStringUntil('\n');
  }
  Serial.flush();
  tft.println("Program\nStarted!");
  delay(5000);

  temp = "";
  while(temp == ""){
    temp = Serial.readStringUntil('\n');
  }
  Serial.flush();
  tft.fillScreen(HX8357_GREEN);
  tft.setCursor(0, 0);
  tft.println("Maintenance\nStarted!");
  delay(1000);

  tft.setCursor(0, 100);
  tft.println("\n Touch the screen to end maintenance \n");
}

void loop() {
  // put your main code here, to run repeatedly:
  while(1){
    //tft.drawRect(0, 0, 500, 130, HX8357_BLACK);
    //tft.fillRect(0, 0, 500, 130, HX8357_BLACK);
    tft.fillScreen(HX8357_GREEN);
    tft.setTextColor(HX8357_BLACK);
    tft.setCursor(0, 0);
    String tempM = Serial.readString();
    tft.println(tempM);
    tft.println("\n Touch the screen to end maintenance \n");
    delay(2500);
    Serial.flush();
    
    TSPoint p = ts.getPoint();
    // we have some minimum pressure we consider 'valid'
    // pressure of 0 means no pressing!
    if (p.z < MINPRESSURE || p.z > MAXPRESSURE) {
       return;
    }
    else{
      Serial.print("end");
      break;
    }
  }
  tft.fillScreen(HX8357_GREEN);

  tft.setCursor(0, 0);
  tft.println("Maintenance ended\n Harvest began");
  Serial.flush();

  delay(20000);
  tft.fillScreen(HX8357_GREEN);
  tft.setCursor(0, 0);
  tft.println("Harvest ended");
  while(1);
}
