#include <M5Stack.h>

const uint8_t nBits_forPWM = 8; // Number of bits used for PWM n=1 to 16[bit]
const double PWM_Frequency = 2000.0; // PWM frequency Maxfreq=80000000.0/2^n[Hz]

const uint8_t PWM_CH = 2; // PWM channel
const uint8_t PWM_PIN = 2; // GPIO PIN number used for PWM output

const int PWM_Values[] = {0, 1, 10, 64, 128, 192, 255, 256};
const int nValues = sizeof(PWM_Values)/sizeof(int);

int ValueIndex = 0;

void setup() {
  M5.begin();
  M5.Power.begin();
  M5.Lcd.setTextSize(2);
  M5.Lcd.print("PWM Test");

  //Put the PWM signal generating pin into output mode.
  pinMode(PWM_PIN, OUTPUT); 

  //Set the channel and frequency resolution.
  ledcSetup(PWM_CH, PWM_Frequency, nBits_forPWM);
  //Set the PWM output pin and channel.
  ledcAttachPin(PWM_PIN, PWM_CH);

  M5.Lcd.setCursor(10, 20);
  M5.Lcd.printf("duty ratio = %d/256 ", PWM_Values[ValueIndex]);
  //Start PWM signal generation.
  ledcWrite(PWM_CH, PWM_Values[ValueIndex]);
}

void loop() {
  M5.update();

  if (M5.BtnA.wasPressed()) {
    ValueIndex++;
    if (nValues<=ValueIndex) ValueIndex = 0;
    M5.Speaker.tone(880, 200); //Peett
    M5.Lcd.setCursor(10, 20);
    M5.Lcd.printf("duty ratio = %d/256 ", PWM_Values[ValueIndex]);
    ledcWrite(PWM_CH, PWM_Values[ValueIndex]);
  }
}