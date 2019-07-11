#include <Adafruit_NeoPixel.h>  
#define PIN 6 // the pin your strip is connected to 
#define COUNT 36 // how many led's are on that strip  
Adafruit_NeoPixel strip = Adafruit_NeoPixel(COUNT, PIN, NEO_GRB + NEO_KHZ800); //defines the strips properties  
int R; 
int G; 
int B;  
void setColor(int Pixel, int R2, int G2, int B2) {
uint32_t color = strip.Color(R2, G2, B2); // make a color   
strip.setPixelColor(Pixel, color); //set a single pixel color   
strip.show(); //update the colors
}   

void setup() {
strip.begin(); // start the strip
strip.show(); // set the strip to black (because we havent told it to do anything yet)
Serial.begin(9600);
Serial.println("ready to change color"); 
}
void loop() {
if (Serial.available() > 0)
{ // if bytes are available through the serial port     
char c = Serial.read(); //read the first byte
if (c == 'R') {
R = Serial.parseInt(); //get the INT     
}
if (c == 'G') {
G = Serial.parseInt(); //get the INT     
}
if (c == 'B') {
B = Serial.parseInt(); //get the INT     
}
if (c == 'P') {
setColor(Serial.parseInt(), R, G, B);
}
}
}
