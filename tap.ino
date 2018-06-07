#include <Arduino.h>
#include <SPI.h>
#include "Adafruit_BLE.h"
#include "Adafruit_BluefruitLE_SPI.h"
#include "Adafruit_BluefruitLE_UART.h"

#include "BluefruitConfig.h"

//#if SOFTWARE_SERIAL_AVAILABLE
//  #include <SoftwareSerial.h>
//#endif

Adafruit_BluefruitLE_SPI ble(BLUEFRUIT_SPI_CS, BLUEFRUIT_SPI_IRQ, BLUEFRUIT_SPI_RST);

#define LED_PIN 6
#define BUTTON_PIN 5

// button state
int state = 0;
int last_state = 1;

void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  ble.begin(VERBOSE_MODE);
  ble.echo(false);
  ble.sendCommandCheckOK(F( "AT+GAPDEVNAME=Cole's VIM Clutch" ));
  ble.reset();
}

void loop() {
  // grab the current state of the button.
  // we have to flip the logic because we are
  // using INPUT_PULLUP.
  
  if(digitalRead(BUTTON_PIN) == LOW)
  {
        state = 1;
        digitalWrite(LED_PIN, state);
        if (state not_eq last_state) {
              ble.print("AT+BleKeyboard=");
              ble.println("i");
              last_state = 1;
        };
        
  }
  else
  {
        state = 0;
        digitalWrite(LED_PIN, state);
        if (state not_eq last_state) {
              ble.print("AT+BleKeyboard=");
              ble.println("\033");
              last_state = 0;
       };
  };

}
