
#include <M5Stack.h>
#include <Arduino.h>
#include <DacTone.h> // this is the DAC audio library

#define SQUARE_PIN 26 // Pin for square wave

int freq = 4000;     // Frequency in Hz
int resolution = 8;  // PWM resolution
int duty_cycle = 50; // Duty Ccyle
int i;

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

int blank[19]; // We keep all the strings pixel lengths to optimize the speed
               // of the top line blanking

void setup()
{

    int duty_cycle = 128;
    //  setup freq, resolution and dutycycle
    ledcSetup(0, freq, resolution);
    ledcAttachPin(SQUARE_PIN, 0);
    ledcWrite(0, duty_cycle); // 50% duty cycle

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

void loop()
{
    M5.update();

    if (M5.BtnA.wasPressed())
    {
        M5.Lcd.setCursor(10, 20);
        M5.Lcd.printf("                ");
        M5.Lcd.setCursor(10, 20);
        Serial.println(duty_cycle);
        M5.Lcd.printf("duty cycle= %d", duty_cycle);

        M5.Lcd.setCursor(10, 30);
        M5.Lcd.printf("                ");
        M5.Lcd.setCursor(10, 30);
        Serial.println(freq);
        M5.Lcd.printf("Frequency= %d", freq);

        M5.Lcd.setCursor(10, 40);
        M5.Lcd.printf("                ");
        M5.Lcd.setCursor(10, 40);
        Serial.println(freq);
        M5.Lcd.printf("resolution is = %d", resolution);

        ledcWrite(0, duty_cycle);
        ledcSetup(0, freq, resolution);
    }

    if (M5.BtnB.wasPressed())
    {
        M5.Lcd.setCursor(10, 20);
        M5.Lcd.printf("                ");
        M5.Lcd.setCursor(10, 20);
        Serial.println(duty_cycle);
        M5.Lcd.printf("duty cycle= %d", duty_cycle);

        M5.Lcd.setCursor(10, 30);
        M5.Lcd.printf("                ");
        M5.Lcd.setCursor(10, 30);
        Serial.println(freq);
        M5.Lcd.printf("Frequency= %d", freq);

        M5.Lcd.setCursor(10, 40);
        M5.Lcd.printf("                ");
        M5.Lcd.setCursor(10, 40);
        Serial.println(freq);
        M5.Lcd.printf("resolution is = %d", resolution);

        ledcWrite(0, duty_cycle);
        ledcSetup(0, freq, resolution);
    }

    if (M5.BtnC.wasPressed())
    {
        M5.Lcd.setCursor(10, 20);
        M5.Lcd.printf("                ");
        M5.Lcd.setCursor(10, 20);
        Serial.println(duty_cycle);
        M5.Lcd.printf("duty cycle= %d", duty_cycle);

        M5.Lcd.setCursor(10, 30);
        M5.Lcd.printf("                ");
        M5.Lcd.setCursor(10, 30);
        Serial.println(freq);
        M5.Lcd.printf("Frequency= %d", freq);

        M5.Lcd.setCursor(10, 40);
        M5.Lcd.printf("                ");
        M5.Lcd.setCursor(10, 40);
        Serial.println(freq);
        M5.Lcd.printf("resolution is = %d", resolution);

        ledcWrite(0, duty_cycle);
        ledcSetup(0, freq, resolution);
    }
}
