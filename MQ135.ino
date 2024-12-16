#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <MQ135.h>

#define OLED_WIDTH 128
#define OLED_HEIGHT 64
#define OLED_ADDR   0x3C
#define PIN_MQ135 A0
MQ135 mq135_sensor(PIN_MQ135);

Adafruit_SSD1306 display(OLED_WIDTH, OLED_HEIGHT);
float temperature = 21.0; 
float humidity = 25.0; 
float rzero;
float correctedRZero;
float resistance;
float ppm;
float correctedPPM;

void setup() {
  Serial.begin(115200);
  display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
  display.clearDisplay(); 
  
  delay(1000);
}

void readMQ135()
{
  rzero = mq135_sensor.getRZero();
  correctedRZero = mq135_sensor.getCorrectedRZero(temperature, humidity);
  resistance = mq135_sensor.getResistance();
  ppm = mq135_sensor.getPPM();
  correctedPPM = mq135_sensor.getCorrectedPPM(temperature, humidity);
  
  Serial.print("MQ135 RZero: ");
  Serial.print(rzero);
  Serial.print("\t Corrected RZero: ");
  Serial.print(correctedRZero);
  Serial.print("\t Resistance: ");
  Serial.print(resistance);
  Serial.print("\t PPM: ");
  Serial.print(ppm);
  Serial.print("\t Corrected PPM: ");
  Serial.print(correctedPPM);
  Serial.println("ppm");
}

void loop() { 
  readMQ135();
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.print("~ MQ135 ~"); 
  display.display();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,22);
  display.print("PPM:");
  display.print(correctedPPM);  
  display.display(); 
  delay(2000);
}
