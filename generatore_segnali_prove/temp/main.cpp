
#include <M5Stack.h>
// #include <Arduino.h>
// #include <DacTone.h>         // this is the DAC audio library


#define SQUARE_PIN 26 // Pin for square wave


//  triangular  GPIO25
//  sinusoidal  GPIO26
//  square      GPIO26


// DacTone audio;                 // create audio object

const int freq = 5000; // Frequency in Hz
const int resolution = 8; // PWM resolution

// enum WaveType {
//   SINE_WAVE,              // max 5 kHz
//   SQUARE_WAVE,            // max 300 kHz
//   TRIANGLE_WAVE           // max 300 Hz
// };

// WaveType waveType = SQUARE_WAVE; // SINE_WAVE, SQUARE_WAVE, TRIANGLE_WAVE


// void generateTriangleWave(int freq);

void setup() {
  Serial.begin(115200);
  delay(1000);

  // if(waveType != SINE_WAVE) {
    // Square wave configuration
    ledcSetup(0, freq, resolution);
    ledcAttachPin(SQUARE_PIN, 0);
    ledcWrite(0, 128); // 50% duty cycle
  // }
 Serial.print(" Setup done");
}

void loop() {
  //   switch (waveType) {
  //     case SINE_WAVE:
  //       audio.tone(freq);
  //       break;
  //     case SQUARE_WAVE:
  //       break;
  //     case TRIANGLE_WAVE:
  //       generateTriangleWave(freq);
  //       break;
  // }
}

void generateTriangleWave(int frequency) {
  // ledcWrite(0, 0); // Turn off LEDC for DAC operation
  // dac_output_enable(DAC_CHANNEL_1); // Enable DAC

  // const int samples = 500; // Increase the number of samples per cycle to improve resolution
  // int value = 0;
  // int increment = 256 / (samples / 2);

  // for (int i = 0; i < samples; ++i) {
  //   dac_output_voltage(DAC_CHANNEL_1, value);
  //   value += increment;
  //   if (value >= 256) {
  //     increment = -increment;
  //     value = 256 + increment;
  //   } else if (value <= 0) {
  //     increment = -increment;
  //     value = 0 + increment;
  //   }

  //   delayMicroseconds((1000000 / frequency) / samples);
  // }
}


