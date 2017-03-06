
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

#include <Bounce2.h>

#define PIN            8
#define BUTTON1_PIN    2
#define BUTTON2_PIN    3

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      4

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRBW + NEO_KHZ800);


//State and Debounch Constants and Variables
int state = 0;
static const int debounceTime = 5;
Bounce debouncer1 = Bounce(); 
Bounce debouncer2 = Bounce(); 

//Tail Light Flash Constants and Variables
static const uint32_t tailLightColor = pixels.Color(255,0,0,0);
unsigned long lastTimeTailLight = 0;

//Indicator Constants and Variables
static const uint32_t indicatorColor = pixels.Color(255,82,0,0);
static const short indicatorDelay = 300;
unsigned long lastTimeIndicator = 0;
int lastColoredPixel = 0;
int pixelToColor = 0;
uint32_t oldColor = 0;


void setup() {
  
  pinMode(BUTTON1_PIN, INPUT_PULLUP);
  debouncer1.attach(BUTTON1_PIN);
  debouncer1.interval(debounceTime); 
  pinMode(BUTTON2_PIN, INPUT_PULLUP);
  debouncer2.attach(BUTTON2_PIN);
  debouncer2.interval(debounceTime); 

  
    pixels.begin(); // This initializes the NeoPixel library.
    pixels.show(); // sets all off
  }

  void loop() {
    debouncer1.update();
    debouncer2.update();
    int button1 = !debouncer1.read();
    int button2 = !debouncer2.read();
    
    
    if (button1) state++;
    else if (button2) state--;
    
    for(int i=0;i<NUMPIXELS;i++){
            pixels.setPixelColor(i, pixels.Color(0,0,0,0));
          }

    for(int i=0;i<state;i++){
            pixels.setPixelColor(i, pixels.Color(0,255,0,0));
          }


    pixels.show(); // This sends the updated pixel color to the hardware.
    
  }


