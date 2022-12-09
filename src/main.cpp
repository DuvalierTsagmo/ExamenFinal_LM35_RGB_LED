

#include <Arduino.h>
#include "WIFI_NINA_Connector.h"
#include "MQTTConnector.h"
#include <Adafruit_NeoPixel.h>

uint16_t val;
double dat;

int bouton1 = 4;
int bouton2 = 5;
int Allume = 255;

#define PIN_LED 2     // Control signal, connect to DI of the LED
#define NUM_LED 1     // Number of LEDs in a strip

// Custom colour1: Yellow
#define RED_VAL_1       255
#define GREEN_VAL_1     255
#define BLUE_VAL_1      0

// Custom colour2: Purple
#define RED_VAL_2       255
#define GREEN_VAL_2     0
#define BLUE_VAL_2      255

// Custom colour3: Cyan
#define RED_VAL_3       0
#define GREEN_VAL_3     255
#define BLUE_VAL_3      255

// Custom colour4: White
#define RED_VAL_4       255
#define GREEN_VAL_4     255
#define BLUE_VAL_4      255

Adafruit_NeoPixel RGB_Strip = Adafruit_NeoPixel(NUM_LED, PIN_LED, NEO_GRB + NEO_KHZ800);

void setup()
{
    Serial.begin(9600);
    wifiConnect(); // Branchement au réseau WIFI
    MQTTConnect(); // Branchement au broker MQTT
     RGB_Strip.begin();
     RGB_Strip.show();
     RGB_Strip.setBrightness(128); 
}

void loop()
{
  
    val = analogRead(A2); // Connect LM35 on Analog 0
    dat = (double)val * (5 / 10.24);
    Serial.print("Tep:"); // Display the temperature on Serial monitor
    Serial.print(dat);
    Serial.println("C");
    delay(5000);
    if (Droit == LOW && Gauche == LOW)
    {
        analogWrite(bouton1, 0);
        analogWrite(bouton2, 0);
    }

    else if (Droit == true && Gauche == false)
    {
        analogWrite(bouton2, 0);
        analogWrite(bouton1, Allume);
    }
    appendPayload("Tep", val);
    appendPayload("bouton1", Droit);
    sendPayload();

}

