#include <Adafruit_NeoPixel.h>
#include <VescUart.h>

// LED related
#define PIN     A5
#define PIXEL   18

Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXEL, PIN, NEO_GRB + NEO_KHZ800);
int ledState = LOW;             // ledState used to set the LED
unsigned long previousLedMillis = 0;        // will store last time LED was updated
const long interval = 1000;           // interval at which to blink (milliseconds)

// VESC related
VescUart UART;

//Setup---------------------------------------------------------------------------------------------------------------------
void setup()
{
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  strip.setBrightness(50);
  showBlue();

  Serial.begin(115200);
  while (!Serial) {;}
  UART.setSerialPort(&Serial);
  showBlack();
}

void reportError()
{
  unsigned long currentLedMillis = millis();

  if (currentLedMillis - previousLedMillis >= interval) {
    // save the last time you blinked the LED
    previousLedMillis = currentLedMillis;
    uint32_t color;

    // if the LED is off turn it on and vice-versa:
    if (ledState == LOW) {
      ledState = HIGH;
      showRed();
    } else {
      ledState = LOW;
      showBlack();
    }
  }
}

void showBlack()
{
    uint32_t color;
    color = strip.Color(0,   0,   0);
    for(int i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, color);
    }
    strip.show();
}

void showWhite()
{
    uint32_t color;
    color = strip.Color(255,   255,   255);
    for(int i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, color);
    }
    strip.show();
}

void showRed()
{
    uint32_t color;
    color = strip.Color(255,   0,   0);
    for(int i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, color);
    }
    strip.show();
}

void showGreen()
{
    uint32_t color;
    color = strip.Color(0,   255,   0);
    for(int i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, color);
    }
    strip.show();
}

void showBlue()
{
    uint32_t color;
    color = strip.Color(0,   0,   255);
    for(int i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, color);
    }
    strip.show();
}

void showForwardDrivingLights()
{
    uint32_t color;
    color = strip.Color(255, 255, 255);
    for(int i=0; i<(strip.numPixels() / 2); i++) {
      strip.setPixelColor(i, color);
    }

    color = strip.Color(255, 0, 0);
    for(int i=(strip.numPixels() / 2); i<strip.numPixels(); i++) {
      strip.setPixelColor(i, color);
    }

    strip.show();
}

void showBackwardDrivingLights()
{
    uint32_t color;
    color = strip.Color(255, 0, 0);
    for(int i=0; i<(strip.numPixels() / 2); i++) {
      strip.setPixelColor(i, color);
    }

    color = strip.Color(255, 255, 255);
    for(int i=(strip.numPixels() / 2); i<strip.numPixels(); i++) {
      strip.setPixelColor(i, color);
    }

    strip.show();
}

void loop()
{
    if ( UART.getVescValues() ) {
      if(UART.data.rpm < -10) {
        showForwardDrivingLights();
      }

      if(UART.data.rpm > 10) {
        showBackwardDrivingLights();
      }
      
/*  Available data.
      data.tempMotor
      data.avgMotorCurrent
      data.avgInputCurrent
      data.rpm
      data.inpVoltage
      data.watt_hours
      data.watt_hours_charged
      data.fault
*/
    }
    else
    {
      // Blink red lights.
      reportError();
    }
}
