#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Setting Up Fonts 
#include <Fonts/FreeSansBoldOblique12pt7b.h>
#include <Fonts/FreeMono9pt7b.h>
#include <Fonts/Tiny3x3a2pt7b.h>
#include <Fonts/TomThumb.h>

#include <DHT.h>

// OLED Screen
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define OLED_DC 8
#define OLED_CS 10
#define OLED_REST 9

Adafruit_SSD1306 display(SCREEN_WIDTH,SCREEN_HEIGHT,
                        &SPI,OLED_DC,OLED_REST,OLED_CS);

// DHT 11
#define DHTPIN 2
#define DHTTYPE DHT11 
DHT dht(DHTPIN,DHTTYPE);


void setup() {
  Serial.begin(9600);
  
  // Setting Up Display
  if(!display.begin(SSD1306_SWITCHCAPVCC)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE); 
  display.setTextSize(2);
  display.setFont(&TomThumb);  
  Serial.println("OELD Initiliazed ....");

  // Setting Up DHT11
  dht.begin();
  Serial.println("DHT Initialized ....");

}



void loop() {
  display.setCursor(0,30);
  display.print("Temp: ");
  display.setCursor(0,50);
  display.print("Humidity: ");
  display.display();
  DHT11_SENSOR_DETECTION();

}

void DHT11_SENSOR_DETECTION(){
  delay(2000);
  display.clearDisplay();
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
  float hif = dht.computeHeatIndex(f, h);
  float hic = dht.computeHeatIndex(t, h, false);
  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("C "));
  Serial.print(f);
  Serial.print(F("F  Heat index: "));
  Serial.print(hic);
  Serial.print(F("C "));
  Serial.print(hif);
  Serial.println(F("F"));
  //Interfacing to OLED 
  display.setCursor(80,30);
  display.print(t);
  display.setCursor(69,50);  
  display.print("%");
  display.setCursor(80,50);  
  display.print(h);
  display.display();
}



