// NeoPixel test program showing use of the WHITE channel for RGBW
// pixels only (won't look correct on regular RGB NeoPixel strips).
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

#define LED_PIN     6


#define LED_COUNT  150


#define BRIGHTNESS 255 

int R2; 
int G2; 
int B2;  //<== All values From 0 to 255 in order of R0G0B0L0D0P
int L2;
int D2;



Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRBW + NEO_KHZ800);



 void setColor(int P, int R2, int G2, int B2, int L2, int D2 )
 {
 uint32_t color = strip.Color(R2, G2, B2);
 strip.fill(color , 0 , LED_COUNT);  
 strip.setBrightness(D2); 
 //strip.show(); //update the color
 }   



void setup() {
 
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif

strip.begin(); // start the strip
strip.show(); // set the strip to black (because we havent told it to do anything yet)
Serial.begin(9600);
Serial.println("ready to change color"); 
}

void loop()

{
chase(strip.Color(R2, G2, B2));
strip.show();
}
 
static void chase(uint32_t c) {
  for(uint16_t i=0; i<strip.numPixels()+L2; i++) {
      strip.setPixelColor(i , c); // Draw new pixel
      strip.setPixelColor(i-L2, 0); // Erase pixel a few steps back
     // strip.show();
  }
if (Serial.available() > 0)
{ // if bytes are available through the serial port     
char c = Serial.read(); //read the first byte
if (c == 'R') {
R2 = Serial.parseInt(); //get the INT     
}
if (c == 'G') {
G2 = Serial.parseInt(); //get the INT     
}
if (c == 'B') {
B2 = Serial.parseInt(); //get the INT     
}
if (c == 'L')
{
L2 = Serial.parseInt(); //get the INT     
}
if (c == 'D')
{
D2 = Serial.parseInt(); //get the INT     
}
if (c == 'P')
{
setColor(Serial.parseInt(), R2, G2, B2, L2, D2);
}
}
}
