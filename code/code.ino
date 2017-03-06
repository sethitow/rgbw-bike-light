
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

#define LED_PIN        8
#define BUTTON1_PIN    2
#define BUTTON2_PIN    3

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      4

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, LED_PIN, NEO_GRBW + NEO_KHZ800);


//State and Debounce Constants and Variables
int state = 0;
static const int debounceTime = 10;

//Tail Light Flash Constants and Variables
static const uint32_t tailLightColor = pixels.Color(255,0,0,0);
unsigned long lastTimeTailLight = 0;

//Indicator Constants and Variables
static const uint32_t indicatorColor = pixels.Color(255,82,0,0);
static const short indicatorDelay = 200;
unsigned long lastTimeIndicator = 0;
int lastColoredPixel = 0;
int pixelToColor = 0;
uint32_t oldColor = 0;


void setup() {
  
  pinMode(BUTTON1_PIN, INPUT_PULLUP);
  pinMode(BUTTON2_PIN, INPUT_PULLUP);
  
    pixels.begin(); // This initializes the NeoPixel library.
    pixels.show(); // sets all off
  }

  void loop() {

    int button1 = !digitalRead(BUTTON1_PIN);
    int button2 = !digitalRead(BUTTON2_PIN);
    
    if (button1 && button2) state = 0;
    else if (button1) state = 3;
    else if (button2) state = 2;
    
    switch (state) {
      case 0:
      for(int i=0;i<NUMPIXELS;i++){
        pixels.setPixelColor(i, pixels.Color(0,0,0,0));
      }
      break;

      
      case 1:
          //Flash Red
      if(millis() > (lastTimeTailLight + 500)) {
        for(int i=0;i<NUMPIXELS;i++){
        // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
          pixels.setPixelColor(i, tailLightColor);
        }
        lastTimeTailLight = millis();}

        else if(millis() > (lastTimeTailLight + 400)){
          for(int i=0;i<NUMPIXELS;i++){
        // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
            pixels.setPixelColor(i, pixels.Color(0,0,0,0));
          }}

          else if(millis() > (lastTimeTailLight + 200)){
            for(int i=0;i<NUMPIXELS;i++){
        // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
              pixels.setPixelColor(i, tailLightColor);
            }}
            
            else if(millis() > (lastTimeTailLight + 100)){
              for(int i=0;i<NUMPIXELS;i++){
                pixels.setPixelColor(i, pixels.Color(0,0,0,0));
              }}

              break;

      case 2:
      for(int i=0;i<NUMPIXELS;i++){
       pixels.setPixelColor(i, pixels.Color(255,255,255,255));
         }

        break;
             
      case 3:
  
       if (millis() > (lastTimeIndicator + indicatorDelay)){
        pixelToColor = (lastColoredPixel + 1 >= NUMPIXELS) ? 0 : lastColoredPixel + 1;
  
        oldColor = pixels.getPixelColor(pixelToColor);
        pixels.setPixelColor(pixelToColor,indicatorColor);
        pixels.setPixelColor(lastColoredPixel,oldColor);
        
        lastColoredPixel = pixelToColor;
        lastTimeIndicator = millis();
      }

            pixels.show();
            
            break;
            
            default:
            for(int i=0;i<NUMPIXELS;i++){
        // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
              pixels.setPixelColor(i, pixels.Color(0,0,0,0));
            }
            break;
          }


    pixels.show(); // This sends the updated pixel color to the hardware.
    
  }


