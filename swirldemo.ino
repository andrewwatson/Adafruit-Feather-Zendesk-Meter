#include "config.h"
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_IS31FL3731.h>

// If you're using the full breakout...
//Adafruit_IS31FL3731 ledmatrix = Adafruit_IS31FL3731();
// If you're using the FeatherWing version
Adafruit_IS31FL3731_Wing ledmatrix = Adafruit_IS31FL3731_Wing();

#define WING_WIDTH 7
#define WING_HEIGHT 15

#define DEFAULT_BRIGHTNESS 80

// The lookup table to make the brightness changes be more visible
uint8_t sweep[] = {1, 2, 3, 4, 6, 8, 10, 15, 20, 20, 80, 120, 120, 80, 20, 20, 15, 10, 8, 6, 4, 3, 2, 1};

#define MODE_DARK 0
#define MODE_SWISH 1
#define MODE_FILL 2

#define IO_LOOP_DELAY 5000

uint8_t currentMode = MODE_DARK;
int loop_count = 0;
unsigned long lastUpdate;
uint8_t fill_level = 0;

// set up the 'servo' feed
AdafruitIO_Feed *commandfeed = io.feed("swisher");

void setup() {
  Serial.begin(115200);
  Serial.println("ISSI swirl test");

  if (! ledmatrix.begin()) {
    Serial.println("IS31 not found");
    while (1);
  }
  Serial.println("IS31 found!");


  Serial.println("Connecting to Adafruit IO");
  io.connect();

  commandfeed->onMessage(handleMessage);

  // wait for a connection
  while(io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("");

  // Because Adafruit IO doesn't support the MQTT retain flag, we can use the
  // get() function to ask IO to resend the last value for this feed to just
  // this MQTT client after the io client is connected.
  commandfeed->get();

  Serial.println();
  Serial.println(io.statusText());
  
  pinMode(STATUS_LED, OUTPUT);

  fill(WING_HEIGHT, DEFAULT_BRIGHTNESS);
  fill(0, DEFAULT_BRIGHTNESS);
  
}

void loop() {
  io.run();

  if (currentMode == MODE_SWISH) {
    // animate over all the pixels, and set the brightness from the sweep table
    swish();  
  }
  if (currentMode == MODE_DARK) {
    dark();
  }

  delay(20);
}

void handleMessage(AdafruitIO_Data *data) {
  Serial.printf("Incoming Feed Message: %s\n", data->value());
 
  if (data->toInt() >= 0 && data->toInt() <= WING_HEIGHT) {    
    fill(data->toInt(), DEFAULT_BRIGHTNESS);
    currentMode = MODE_FILL;
  }

  if (data->toString() == "dark") {
    currentMode = MODE_DARK;
  }

  if (data->toString() == "swish") {
    currentMode = MODE_SWISH;    
  }  
}

void fill(uint8_t lines, uint8_t brightness) {

  if (lines < fill_level) {
    Serial.printf("filling down from %d to %d\n", fill_level, lines);
    for (int x = fill_level; x >= lines; x--) {
      Serial.printf("x %d\n", x);
      ledmatrix.fillRect(x, 0, WING_HEIGHT, WING_WIDTH, 0);
//      ledmatrix.fillRect(0, 0, x, WING_WIDTH, brightness);
      delay(50);
    }    
  } else {
    Serial.printf("filling up from %d to %d\n", fill_level, lines);
    for (int x = fill_level; x <= lines; x++) {
      Serial.printf("x %d\n", x);
      ledmatrix.fillRect(0, 0, x, WING_WIDTH, brightness);
      delay(50);
    }    
  }
  fill_level = lines;  
}

void dark() {
    for (uint8_t x = 0; x < 16; x++)
      for (uint8_t y = 0; y < 9; y++) {
        ledmatrix.drawPixel(x, y, 0);
        delay(1);
      }
        
}

void swish() {

  for (uint8_t incr = 0; incr < 24; incr++)
    for (uint8_t x = 0; x < 16; x++)
      for (uint8_t y = 0; y < 9; y++)
        ledmatrix.drawPixel(x, y, sweep[(x+y+incr)%24]);  

}

void flashLED(uint8_t pin) {
  digitalWrite(pin, HIGH);
  delay(500);
  digitalWrite(pin, LOW);
}
