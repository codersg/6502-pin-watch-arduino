#include <Arduino.h>

// The 16 address input pins.
const uint8_t ADDRESS_INPUTS[16] = {23,25,27,29,31,33,35,37,39,41,43,45,47,49,51,53};

// the 8 data pins
const uint8_t DATA_INPUTS[8] = {22,24,26,28,30,32,34,38};

// Clock signalinput pin.
#define CLOCK_INPUT 19

// Read/Write input pin
#define READWRITE_INPUT 18

// Reset input pin
#define RESET_INPUT 17

// The Values
uint8_t ADDRESS_VALUES[16];
uint8_t DATA_VALUES[8];
uint8_t READWRITE_VALUE;
uint8_t RESET_VALUE;

// "I'm Alive!" LED Indicator blink time (in milliseconds)
#define ImAliveLedBlinkSpeed 1000

// Reads the values of the A0-A15 pins (the Address Bus), D0-D7 (Data Bus), RWB (Read/Write for the Data Bus) and RST (Reset)
void measure()
{

  RESET_VALUE = digitalRead(RESET_INPUT);

  // If we are resetting (RESET is LOW) then no point in reading the values.
  if (RESET_VALUE == 1)
  {
    // Read all the values
    for (byte i = 0; i < 16; ++i)
    {
      ADDRESS_VALUES[i] = digitalRead(ADDRESS_INPUTS[i]);
    } 
    for (byte i = 0; i < 8; ++i)
    {
      DATA_VALUES[i] = digitalRead(ADDRESS_INPUTS[i]);
    }
    READWRITE_VALUE = digitalRead(READWRITE_INPUT);
  }
}

// Sends the values of the Address Bus, Data Bus and Read/Write stata to the Serial connection.
void outputMeasurements()
{
  // RESET value of LOW (0) means the 6502 is being reset
  if (RESET_VALUE == 0)
  {
    Serial.println("--RESET--");
  }
  else
  {
    uint16_t addressValue = 0;
    uint8_t dataValue = 0;

    // Calculate the 16-bit unsigned int value from the Address Bus values
    for (byte i = 0; i < 16; i++)
    {
      addressValue |= (ADDRESS_VALUES[i] << i);
    }

    // Calculate the 8-bit unsigned int value from the Data Bus values
    for (byte i = 0; i < 8; i++)
    {
      dataValue |= (DATA_VALUES[i] << i);
    }

    // Send a formatted string via the Serial connection.
    char output[20];
    sprintf(output, "[%c] ADR: %04x  DATA: %02x (%u)", (READWRITE_VALUE)? 'R' : 'W', addressValue, dataValue, dataValue);
    Serial.println(output);
  }
}

// Measures the outputs and sends a summary via the serial connection.
void onClockTicked()
{
  measure();
  outputMeasurements();
}

// Initialise the pins and set the Serial connection.
void setup() {
  // Setup the pins
  for(byte i=0; i<16; ++i)
  {
    pinMode(ADDRESS_INPUTS[i], INPUT);
  }

  pinMode(READWRITE_INPUT, INPUT);
  pinMode(CLOCK_INPUT, INPUT);

  // Set the serial output
  Serial.begin(115200);

  // Setup an interrupt for the Clock.
  attachInterrupt(digitalPinToInterrupt(CLOCK_INPUT), onClockTicked, RISING);
}


// Used to toggle on and off the built-in LED, just to let us know it's alive.
uint8_t builtinLedState = HIGH;

// Does nothing but blink the built-in LED to let us know it's alive.
void loop() {
  builtinLedState = (builtinLedState == HIGH)?    builtinLedState = LOW :  builtinLedState = HIGH;
  digitalWrite(LED_BUILTIN, builtinLedState);
  delay(ImAliveLedBlinkSpeed);
}