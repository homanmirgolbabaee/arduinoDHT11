#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>


// OLED Screen
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define OLED_DC 8
#define OLED_CS 10
#define OLED_REST 9

Adafruit_SSD1306 display(SCREEN_WIDTH,SCREEN_HEIGHT,
                        &SPI,OLED_DC,OLED_REST,OLED_CS);




void setup() {
  Serial.begin(9600);
  if(!display.begin(SSD1306_SWITCHCAPVCC)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  display.display();
  delay(2000);
  display.clearDisplay();
}

void loop() {
    display.clearDisplay();
    display.setCursor(0 , 20);
    display.setTextColor(SSD1306_WHITE); 
    display.setTextSize(1);
    display.println("Hello World !");
    display.display();
    
}
