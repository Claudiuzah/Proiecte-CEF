
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define IR_SENSOR_PIN 2
#define RESET_BUTTON_PIN 3

Adafruit_SSD1306 display (128, 32, &Wire, -1);

volatile int counter = 0;

bool lastState = true; // Starea anterioară a senzorului, inițializată la "HIGH"

void setup() {
  pinMode(IR_SENSOR_PIN, INPUT);
  pinMode(RESET_BUTTON_PIN, INPUT_PULLUP); // Activarea rezistenței pull-up internă pentru buton
  Serial.begin(9600);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.display();
  delay(2000);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor (SSD1306_WHITE);
}
void loop() {
  bool currentState = digitalRead(IR_SENSOR_PIN);

  if (currentState == LOW && lastState == HIGH) {
     // Senzorul a trecut de la HIGH la LOW incrementCounter();
    incrementCounter();
    Serial.println("Obiect detectat!");}

  // Verificare buton de reset
  if (digitalRead(RESET_BUTTON_PIN) == LOW) {
  // Butonul de reset este apăsat, resetați contorul 
  resetCounter();
  Serial.println("Contor resetat!");
  }
  lastState = currentState;

  display.clearDisplay();
  display.setCursor(0, 0);
  display.print("Obiecte: ");
  display.print(counter);
  display.display();
  }

  void incrementCounter(){
    counter++;
  }

  void resetCounter(){
    counter = 0;
  }