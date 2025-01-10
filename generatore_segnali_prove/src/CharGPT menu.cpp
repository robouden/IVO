#include <M5Stack.h>

// Pin for square wave
#define SQUARE_PIN 26

// Parameters for PWM control
int duty_cycle = 128;    // Duty cycle (0-255)
int freq = 100000;       // Frequency (Hz)
int resolution = 8;      // Resolution (8-bit PWM)

// Define menu options
enum MenuOption
{
    DUTY_CYCLE,
    FREQUENCY,
    RESOLUTION
};
MenuOption current_option = DUTY_CYCLE;

// Declare function prototypes
void displayMenu(); // Declare displayMenu before setup and loop
void adjustParameter(int delta);

void setup()
{
    M5.begin();
    Serial.begin(115200);

    ledcSetup(0, freq, resolution);
    ledcAttachPin(SQUARE_PIN, 0);
    ledcWrite(0, 128); // 50% duty cycle

    // Check if the LCD is initialized properly
    M5.Lcd.fillScreen(BLACK);
    M5.Lcd.setTextColor(WHITE);
    M5.Lcd.setTextSize(2); // Set larger text size (2x larger than default)
    M5.Lcd.setCursor(10, 20);
    M5.Lcd.printf("Square wave gen V0.9");

    delay(1000); // Show this message for 2 seconds to check if the display works
    M5.Lcd.fillScreen(BLACK);
    displayMenu();
}

void loop()
{
    M5.update(); // Update M5Stack state

    // Button A: Select menu option (cycle through DUTY_CYCLE, FREQUENCY, RESOLUTION)
    if (M5.BtnA.wasPressed())
    {
        current_option = static_cast<MenuOption>((current_option + 1) % 3);
        displayMenu();
    }

    // Button B: Increment the selected parameter (Duty Cycle by 10%, Frequency by 100)
    if (M5.BtnB.wasPressed())
    {
        adjustParameter(1);
        displayMenu();
    }

    // Button C: Decrement the selected parameter (Duty Cycle by 10%, Frequency by 100)
    if (M5.BtnC.wasPressed())
    {
        adjustParameter(-1);
        displayMenu();
    }

    // Long press handling for Button B: continuously adjust frequency when held down, only in FREQUENCY mode
    if (M5.BtnB.isPressed() && current_option == FREQUENCY)
    {
        delay(100); // Add delay to prevent excessive button presses
        adjustParameter(1);
        displayMenu();
    }

    // Long press handling for Button C: continuously adjust frequency when held down, only in FREQUENCY mode
    if (M5.BtnC.isPressed() && current_option == FREQUENCY)
    {
        delay(100); // Add delay to prevent excessive button presses
        adjustParameter(-1);
        displayMenu();
    }
}


// Display the current menu based on the selected option
void displayMenu()
{
    // Clear the entire screen to avoid overlapping old menu and indicator
    M5.Lcd.fillScreen(BLACK);

    // Convert duty cycle to percentage (256 is 100%)
    int duty_cycle_percent = (duty_cycle * 100) / 255; // (0 to 100%)

    // Display menu options
    M5.Lcd.setTextColor(WHITE);

    // Duty Cycle option
    if (current_option == DUTY_CYCLE)
    {
        M5.Lcd.setCursor(10, 20);
        M5.Lcd.printf("Duty Cycle: %d%%  <---", duty_cycle_percent); // Display duty cycle as a percentage
    }
    else
    {
        M5.Lcd.setCursor(10, 20);
        M5.Lcd.printf("Duty Cycle: %d%%       ", duty_cycle_percent); // Display duty cycle as a percentage
    }

    // Frequency option
    if (current_option == FREQUENCY)
    {
        M5.Lcd.setCursor(10, 50);
        M5.Lcd.printf("Frequency: %d  <---", freq);
    }
    else
    {
        M5.Lcd.setCursor(10, 50);
        M5.Lcd.printf("Frequency: %d             ", freq);
    }

    // Debug output
    Serial.printf("Duty Cycle: %d%%, Frequency: %d, Resolution: %d\n", duty_cycle_percent, freq, resolution);
}

// Adjust the selected parameter
void adjustParameter(int delta)
{
    switch (current_option)
    {
    case DUTY_CYCLE:
        // Adjust duty cycle by 10% of the full range (255)
        duty_cycle = constrain(duty_cycle + delta * 25, 0, 255); // 10% of 255 = 25 units
        ledcWrite(0, duty_cycle);                                // Update PWM with new duty cycle
        break;
    case FREQUENCY:
        // Adjust frequency by 100 each time
        freq = constrain(freq + delta * 100, 100, 300000); // Limit frequency range
        ledcSetup(0, freq, resolution);                    // Update frequency
        break;
    }
}
