/*
 * L298N Motor Driver — Basic Demo
 * --------------------------------
 * Drives two DC motors through an L298N H-bridge module.
 * Cycles through forward, backward, and stop on both motors.
 * Uses only built-in Arduino functions — no external library required.
 *
 * Target board: Arduino Uno (or any 5V Arduino with PWM pins)
 * Wiring (L298N module):
 *   L298N IN1  -> Arduino D5    (motor A direction)
 *   L298N IN2  -> Arduino D6    (motor A direction)
 *   L298N ENA  -> Arduino D9    (motor A speed, PWM)
 *   L298N IN3  -> Arduino D7    (motor B direction)
 *   L298N IN4  -> Arduino D8    (motor B direction)
 *   L298N ENB  -> Arduino D10   (motor B speed, PWM)
 *   L298N GND  -> Arduino GND   (must share GND)
 *
 *   L298N +12V -> external motor power supply (4.5–35 V)
 *   L298N +5V  -> can power the Arduino if the on-board 5 V regulator
 *                 jumper is enabled and motor supply is <= 12 V. For
 *                 supplies above 12 V, REMOVE the jumper and power
 *                 the Arduino separately.
 *
 * (c) 2026 Circuitrocks. Released under the MIT License.
 * https://github.com/circuitrocks
 */

const uint8_t IN1 = 5;
const uint8_t IN2 = 6;
const uint8_t ENA = 9;
const uint8_t IN3 = 7;
const uint8_t IN4 = 8;
const uint8_t ENB = 10;

void motorA(int speed) {
  // speed: -255 (full reverse) to +255 (full forward), 0 = stop
  if (speed > 0) {
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    analogWrite(ENA, speed);
  } else if (speed < 0) {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    analogWrite(ENA, -speed);
  } else {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    analogWrite(ENA, 0);
  }
}

void motorB(int speed) {
  if (speed > 0) {
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    analogWrite(ENB, speed);
  } else if (speed < 0) {
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    analogWrite(ENB, -speed);
  } else {
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
    analogWrite(ENB, 0);
  }
}

void setup() {
  Serial.begin(9600);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);
  motorA(0);
  motorB(0);
  Serial.println(F("L298N demo: forward, reverse, stop, repeat."));
}

void loop() {
  Serial.println(F("Forward, half speed"));
  motorA(128);
  motorB(128);
  delay(2000);

  Serial.println(F("Stop"));
  motorA(0);
  motorB(0);
  delay(500);

  Serial.println(F("Reverse, half speed"));
  motorA(-128);
  motorB(-128);
  delay(2000);

  Serial.println(F("Stop"));
  motorA(0);
  motorB(0);
  delay(500);

  Serial.println(F("Spin in place (A forward, B reverse), full speed"));
  motorA(255);
  motorB(-255);
  delay(2000);

  Serial.println(F("Stop"));
  motorA(0);
  motorB(0);
  delay(2000);
}
