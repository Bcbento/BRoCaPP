#include <SPI.h>
#include <PixyI2C.h>
#include <ESP32Servo.h>
#include "BluetoothSerial.h"

// init Class:
BluetoothSerial ESP_BT;
int modo;

int LEDR = 32;
int LEDG = 13;
int LEDB = 12;

int servo_base_pin = 27;
int servo_meio_pin = 26;
int servo_topo_pin = 25;
int servo_garra_pin = 33;

int rottopo = 0;
int rotmeio = 0;
int rotbase = 0;
int rotgarra = 0;


PixySPI_SS pixy;
Servo servo_base, servo_meio, servo_topo, servo_garra;

void setup() {

  Serial.begin(9600);
  ESP_BT.begin("BRoCaPP");  //Name of your Bluetooth interface
  pixy.init();
  delay(1000);
  lcd.clear();

  servo_base.attach(servo_base_pin);
  servo_topo.attach(servo_topo_pin);
  servo_meio.attach(servo_meio_pin);
  servo_garra.attach(servo_garra_pin);

  pinMode(LEDR, OUTPUT);
  pinMode(LEDG, OUTPUT);
  pinMode(LEDB, OUTPUT);
}

void loop() {

  ///////////////////////////////////////////////////////////////////////////
  //imprime no serial monitor consoante o comando dado na app e move garra//

  if (ESP_BT.available() == 0) {
    return;
  }

  else {
    //////////////////////////////MODO ATOMATICO//////////////////////////////
    if (/*strign enviada pela app quando modo automático*/) {  
      //led verde aka modo automatico on
      digitalWrite(LEDG, HIGH);
      digitalWrite(LEDR, LOW);
      digitalWrite(LEDB, LOW);
      uint16_t blocks = pixy.getBlocks();
      if (blocks) {
        for (int j = 0; j < blocks; j++) {
          // Get the signature for the detected block
          uint8_t color = pixy.blocks[j].signature;

          lcd.clear();

          switch (color) {
            case 1:
              lcd.print("Color Detected: Red");
              break;
            case 2:
              lcd.print("Color Detected: Dark Blue");
              break;
            case 3:
              lcd.print("Color Detected: Yellow");
              break;
            // Add more cases as needed for other signatures
            default:
              lcd.print("Color Detected: Unknown");
          }
          delay(1000);  // Pause for 1 second to let the user read the output
          if(color == 1 && /* string recebida da app quando vermelho*/){
            for (rotgarra = 0; rotgarra < 80; rotgarra += 5) {
              servo_garra.write(rotgarra);
            }

            /////testar posição dos restantes servos/////

            for (rotgarra = 80; rotgarra > 0; rotgarra -= 5) {
              servo_garra.write(rotgarra);
            }


          }
          if(color == 2 && /* string recebida da app quando azul*/){
            for (rotgarra = 0; rotgarra < 80; rotgarra += 5) {
              servo_garra.write(rotgarra);
            }

            /////testar posição dos restantes servos/////

            for (rotgarra = 80; rotgarra > 0; rotgarra -= 5) {
              servo_garra.write(rotgarra);
            }
            
            
          }
          if(color == 3 && /* string recebida da app quando amarelo*/){
            for (rotgarra = 0; rotgarra < 80; rotgarra += 5) {
              servo_garra.write(rotgarra);
            }
            /////testar posição dos restantes servos/////

            for (rotgarra = 80; rotgarra > 0; rotgarra -= 5) {
              servo_garra.write(rotgarra);
            }


          }
        }
        //////////////////////////////MODO CONTROLADO//////////////////////////////
        else {
          ////////////cor modo controlado - roxo
          digitalWrite(LEDG, LOW);
          digitalWrite(LEDB, HIGH);
          digitalWrite(LEDR, HIGH);

          String Direction = ESP_BT.readString();

          if (Direction == "T") {
            modo = 1;
            Serial.print("T");
          }

          if (Direction == "M") {
            modo = 2;
            Serial.print("M");
          }
          if (Direction == "K") {
            modo = 3;
            Serial.print("K");
          }



          switch (modo) {
            case 1:


              if (Direction == "C") {
                rottopo += 20;
                Serial.print("C");  //codigo de subir
              }

              if (Direction == "B") {
                rottopo -= 20;
                Serial.print("B");  //codigo de descer
              }

              if (Direction == "G") {
                Serial.print("G");  //garra
                if (rotgarra == 0) {
                  for (rotgarra = 0; rotgarra < 80; rotgarra += 5) {
                    servo_garra.write(rotgarra);
                  }
                } else {
                  for (rotgarra = 80; rotgarra > 0; rotgarra -= 5) {
                    servo_garra.write(rotgarra);
                  }
                }
              }

              servo_topo.write(rottopo);

              break;

            case 2:


              if (Direction == "C") {
                rotmeio -= 20;
                Serial.print("C");  //codigo de subir
              }

              if (Direction == "B") {
                rotmeio += 20;
                Serial.print("B");  //codigo de descer
              }

              if (Direction == "G") {
                Serial.print("G");  //garra
                if (rotgarra == 0) {
                  for (rotgarra = 0; rotgarra < 80; rotgarra += 5) {
                    servo_garra.write(rotgarra);
                  }
                } else {
                  for (rotgarra = 80; rotgarra > 0; rotgarra -= 5) {
                    servo_garra.write(rotgarra);
                  }
                }
              }

              servo_meio.write(rotmeio);

              break;


            case 3:

              if (Direction == "E") {
                rotbase += 20;

                Serial.print("E");  //codigo de esquerda
              }

              if (Direction == "D") {
                rotbase -= 20;
                Serial.print("D");  //codigo de direita
              }

              if (Direction == "G") {
                Serial.print("G");  //garra
                if (rotgarra == 0) {
                  for (rotgarra = 0; rotgarra < 80; rotgarra += 5) {
                    servo_garra.write(rotgarra);
                  }
                } else {
                  for (rotgarra = 80; rotgarra > 0; rotgarra -= 5) {
                    servo_garra.write(rotgarra);
                  }
                }
              }
              //} (acho que é inutil mas se der erro n é)
              servo_base.write(rotbase);
              break;
            default:
              break;
          }
        }
      }
    }
