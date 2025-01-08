
#include <M5Stack.h>
#include "DacTone.h"           // this is the DAC audio library


#define SQUARE_PIN 26 // Pin for square wave


//  triangular  GPIO25
//  sinusoidal  GPIO26
//  square      GPIO26


DacTone audio;                 // create audio object

const int freq = 4000; // Frequency in Hz
const int resolution = 8; // PWM resolution

enum WaveType {
  SINE_WAVE,              // max 5 kHz
  SQUARE_WAVE,            // max 300 kHz
  TRIANGLE_WAVE           // max 300 Hz
};

WaveType waveType = SQUARE_WAVE; // SINE_WAVE, SQUARE_WAVE, TRIANGLE_WAVE


void generateTriangleWave(int freq);
  
// The scrolling area must be a integral multiple of TEXT_HEIGHT
#define TEXT_HEIGHT 16 // Height of text to be printed and scrolled
#define TOP_FIXED_AREA \
    14 // Number of lines in top fixed area (lines counted from top of screen)
#define BOT_FIXED_AREA \
    0            // Number of lines in bottom fixed area (lines counted from bottom of
                 // screen)
#define YMAX 240 // Bottom of screen area

// The initial y coordinate of the top of the scrolling area
uint16_t yStart = 0;
// yArea must be a integral multiple of TEXT_HEIGHT
uint16_t yArea = YMAX - TOP_FIXED_AREA - BOT_FIXED_AREA;
// The initial y coordinate of the top of the bottom text line
// uint16_t yDraw = YMAX - BOT_FIXED_AREA - TEXT_HEIGHT;
uint16_t yDraw = 0;

// Keep track of the drawing x coordinate
uint16_t xPos = 0;

// For the byte we read from the serial port
byte data = 0;

// A few test variables used during debugging
boolean change_colour = 1;
boolean selected = 1;





// Some extra variables.:

// const uint8_t nBits_forPWM = 8; // Number of bits used for PWM n=1 to 16[bit]
// const double PWM_Frequency = 2000.0; // PWM frequency Maxfreq=80000000.0/2^n[Hz]

// const uint8_t PWM_CH = 2; // PWM channel
// const uint8_t PWM_PIN = 2; // GPIO PIN number used for PWM output


int ValueIndex = 0; 


int blank[19]; // We keep all the strings pixel lengths to optimize the speed
               // of the top line blanking



void setup()
{

      if(waveType != SINE_WAVE) {
    // Square wave configuration
    ledcSetup(0, freq, resolution);
    ledcAttachPin(SQUARE_PIN, 0);
    ledcWrite(0, 64); // 50% duty cycle
  }
    // Setup the TFT display
    M5.begin();
    M5.Power.begin();
    M5.Lcd.fillScreen(TFT_BLACK);

    // Setup baud rate and draw top banner
    Serial.begin(115200);
    Serial.print(" ZPE pulse generator - 115200 baud ");
    M5.Lcd.setTextColor(TFT_WHITE, TFT_DARKGREY);
    M5.Lcd.fillRect(0, 0, 320, TEXT_HEIGHT, TFT_DARKGREY);
    M5.Lcd.drawCentreString(" ZPE pulse generator - 115200 baud ", 320 / 2, 0, 2);

    // Change colour for scrolling zone text
    M5.Lcd.setTextColor(TFT_WHITE, TFT_BLACK);
}


void loop() {
  M5.update();

  if (M5.BtnA.wasPressed()) {
    ValueIndex++;
    M5.Lcd.setCursor(10, 20);
    M5.Lcd.printf("duty ratio = %d/256 ", freq, ValueIndex);
    // ledcWrite(PWM_CH, PWM_Values[ValueIndex]);
  }
}


void generateTriangleWave(int frequency) {
  ledcWrite(0, 0); // Turn off LEDC for DAC operation
  dac_output_enable(DAC_CHANNEL_1); // Enable DAC

  const int samples = 500; // Increase the number of samples per cycle to improve resolution
  int value = 0;
  int increment = 256 / (samples / 2);

  for (int i = 0; i < samples; ++i) {
    dac_output_voltage(DAC_CHANNEL_1, value);
    value += increment;
    if (value >= 256) {
      increment = -increment;
      value = 256 + increment;
    } else if (value <= 0) {
      increment = -increment;
      value = 0 + increment;
    }

    delayMicroseconds((1000000 / frequency) / samples);
  }
}