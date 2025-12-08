#include <Wire.h>
#include <VL6180X.h>
#include "Servo.h"


Servo servo1;
Servo servo2;
int phi; // переменная для угла поворота серво для основной крышки
int psi;
const int ir = A3;
VL6180X sensor;



void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  servo1.attach(9);
  servo2.attach(7);
  pinMode(5, OUTPUT);
  Wire.begin();

  servo1.write(0);
  servo2.write(0);
  
  sensor.init();
  sensor.configureDefault();
  sensor.setTimeout(500);

}

void loop() {
  int r = analogRead(ir); // r в диапазоне от 0 до 1023
  Serial.println(r);
  if (r < 100) { // т.к. используется аналоговый пин Arduino
    for (phi = 0; phi <= 90; phi++) {
    servo1.write(phi); // сообщаем серво угол поворота
    delay(20); // ждем 20 мс
  }

  tone(5, 20); // включаем на пьезодинамик 900 Гц
  delay(1000); // ждем 1 секунду
  noTone(5); // отключаем пьезодинамик на пин 11
  delay(1000); // ждем 1 секунду
  
  // цикл для поворота от 90 до 0 градусов
  for (phi = 90; phi >= 0; phi--) {
    servo1.write(phi); // сообщаем серво угол поворота
    delay(20); // ждем 20 мс
  }
  }
  delay(100);

  Serial.println(sensor.readRangeSingleMillimeters());

  if (sensor.readRangeSingleMillimeters() > 200){
    servo2.write(0);
  }

  if (sensor.readRangeSingleMillimeters() < 200 and sensor.readRangeSingleMillimeters() > 150){
    servo2.write(30);
  }

  if (sensor.readRangeSingleMillimeters() < 150 and sensor.readRangeSingleMillimeters() > 100){
    servo2.write(45);
  }

  if (sensor.readRangeSingleMillimeters() < 100 and sensor.readRangeSingleMillimeters() > 50){
    servo2.write(60);
  }

  if (sensor.readRangeSingleMillimeters() < 50){
    servo2.write(90);
  }

  delay(200); // Задержка перед следующим измерением

}
