int servo_base_pin = 27;
int servo_meio_pin = 26;
int servo_topo_pin = 25;

#include <ESP32Servo.h>

Servo servo_base, servo_meio;

void setup() {
  servo_base.attach(servo_base_pin);
  servo_topo.attach(servo_topo_pin);
  servo_meio.attach(servo_meio_pin);
  servo_meio.write(180);
}

void loop() {

  for(int i = 0;i<180;i++){
      servo_base.write(i);
      delay(5);
  }

  for(int i =180;i>0;i--){
    servo_base.write(i);
    delay(5);
  }

}
