// include the neo pixel library
#include <Adafruit_NeoPixel.h>

// The number of LEDs being driven. This dictates how much data is expected in each frame read from the serial port.
static const int NUM_LEDS = 256;

// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_RGB     Pixels are wired for RGB bitstream
//   NEO_GRB     Pixels are wired for GRB bitstream
//   NEO_KHZ400  400 KHz bitstream (e.g. FLORA pixels)
//   NEO_KHZ800  800 KHz bitstream (e.g. High Density LED strip)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(
  NUM_LEDS,             // Number of pixels in strip
  6,                   // Pin number (most are valid)
  NEO_GRB + NEO_KHZ800  //  pixel type flags, add together as needed:
                        //   NEO_RGB     Pixels are wired for RGB bitstream
                        //   NEO_GRB     Pixels are wired for GRB bitstream
                        //   NEO_KHZ400  400 KHz bitstream (e.g. Old FLORA pixels)
                        //   NEO_KHZ800  800 KHz bitstream (e.g. New FLORA pixels and most WS2811 strips)
);

// Buffer used to read LED data from Serial.
// TODO: Direct access to the Adafruit_NeoPixel buffer would cut memory usage in half
char colorValues[NUM_LEDS*3];

void setup() {
  // Init the NeoPixel library and turn off all the LEDs
  strip.begin();
  strip.show();
  
  // Do a quick test/demo to show that things are working
  for (int i=0; i<60; i++) { flashAll(strip.Color((i%20)*2,i%30,i%60)); delay(10); }

  // Initialize the buffer to all black
  memset(colorValues, 0, sizeof(colorValues));

  // Initialize serial and wait for port to open:
  Serial.begin(115200);
  while (!Serial) {
    ; // wait for port to be ready
  }
  
  // Tell the computer that we're ready for data
  Serial.println("READY");
}


void loop() {
  while (true) {
    int bufferPos = 0;
    
    // Read the data for each pixel
    while (bufferPos < NUM_LEDS*3) {
      int color = Serial.read();
      if (color >= 0) {
        colorValues[bufferPos++] = color;
      }
    }
    
    // Feed the data to the NeoPixel library
    for(int i=0; i<NUM_LEDS; i++) {
      int d = i*3;
      uint32_t c = strip.Color(colorValues[d], colorValues[d+1], colorValues[d+2]);
      strip.setPixelColor(i, c);
    }
    
    // update the strip
    strip.show();
    
    // Clear up the serial buffer
    while (Serial.available() > 0) Serial.read();
    
    // Let the sender know we're ready for more data
    Serial.println("READY");
  }
}

void flashAll(uint32_t color) {
  // Do a quick test/demo to show that things are working
  for (int i=0; i < NUM_LEDS; i++) {
    strip.setPixelColor(i, color);
  }
  strip.show();
}
