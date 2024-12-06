#include <SPI.h>
#include <Pixy.h>
#include <ESP32Servo.h>
#include "BluetoothSerial.h"
#include <LiquidCrystal.h>

// init Class:
BluetoothSerial ESP_BT;
int modo;
int manual;

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

int sigRed = 1;   // signature 1 is red objects
int sigBlue = 2;  //signature 2 is blue
int sigYellow = 3;
int i;

const int rs = 15, en = 2, d4 = 0, d5 = 4, d6 = 21, d7 = 22;

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
Pixy pixy;
Servo servo_base, servo_meio, servo_topo, servo_garra;

void setup() {

  Serial.begin(9600);
  ESP_BT.begin("BRoCaPP");  //Name of your Bluetooth interface
  pixy.init();
  delay(1000);


  lcd.begin(16, 2);

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
    String Direction = ESP_BT.readString();
    //////////////////////////////MODO ATOMATICO//////////////////////////////
    if (Direction == "X") {
      manual = 1;
      Serial.print("automatico");
    }
    if (Direction == "W") {
      manual = 2;
      Serial.print("manual");
    }


    if (manual == 1) {
      //led verde aka modo automatico on
      digitalWrite(LEDG, HIGH);
      digitalWrite(LEDR, LOW);
      digitalWrite(LEDB, LOW);
      uint16_t blocks;
      while (manual == 1) {
        blocks = pixy.getBlocks();
        if (blocks) {
          if (pixy.blocks[i].signature == sigRed) {
            Serial.println("vermelho");
            lcd.print("Color Detected");
            lcd.setCursor(0, 1);
            lcd.print("RED             ");
            delay(3000);
          } else if (pixy.blocks[i].signature == sigBlue) {
            Serial.println("azul");
            lcd.print("Color Detected:");
            lcd.setCursor(0, 1);
            lcd.print("BLUE             ");
            delay(3000);
          } else if (pixy.blocks[i].signature == sigYellow) {
            Serial.println("amarelo");
            lcd.print("Color Detected:");
            lcd.setCursor(0, 1);
            lcd.print("YELLOW          ");
            delay(3000);
          } 

          // Pause for 1 second to let the user read the output
          if (pixy.blocks[i].signature == sigRed && Direction == "R") {
            servo_garra.write(0);
            servo_meio.write(0);
            servo_base.write(0);
            servo_topo.write(0);
            delay(500);
            rotgarra = 60;
            servo_garra.write(rotgarra);
            for (rotmeio = 0; rotmeio < 40; rotmeio += 5) {
              servo_meio.write(rotmeio);
              delay(100);
            }
            delay(1000);
            rotgarra = 0;
            servo_garra.write(rotgarra);
            delay(1000);
            rotmeio = 0;
            rotbase = 40;
            servo_meio.write(rotmeio);
            servo_base.write(rotbase);
            delay(1000);

            for (rotmeio = 0; rotmeio < 40; rotmeio += 5) {
              servo_meio.write(rotmeio);
              delay(100);
            }
            delay(1000);
            rotgarra = 60;
            servo_garra.write(rotgarra);
            delay(1000);
            servo_meio.write(0);
            delay(1000);
            servo_garra.write(0);
            delay(1000);
          }


          if (pixy.blocks[i].signature == sigBlue && Direction == "Z") {
            servo_garra.write(0);
            servo_meio.write(0);
            servo_base.write(0);
            servo_topo.write(0);
            delay(500);
            rotgarra = 60;
            servo_garra.write(rotgarra);
            for (rotmeio = 0; rotmeio < 40; rotmeio += 5) {
              servo_meio.write(rotmeio);
              delay(100);
            }
            delay(1000);
            rotgarra = 0;
            servo_garra.write(rotgarra);
            delay(1000);
            rotmeio = 0;
            rotbase = 40;
            servo_meio.write(rotmeio);
            servo_base.write(rotbase);
            delay(1000);

            for (rotmeio = 0; rotmeio < 40; rotmeio += 5) {
              servo_meio.write(rotmeio);
              delay(100);
            }
            delay(1000);
            rotgarra = 60;
            servo_garra.write(rotgarra);
            delay(1000);
            servo_meio.write(0);
            delay(1000);
            servo_garra.write(0);
            delay(1000);
          }
          if (pixy.blocks[i].signature == sigYellow && Direction == "Y") {
            servo_garra.write(0);
            servo_meio.write(0);
            servo_base.write(0);
            servo_topo.write(0);
            delay(500);
            rotgarra = 60;
            servo_garra.write(rotgarra);
            for (rotmeio = 0; rotmeio < 40; rotmeio += 5) {
              servo_meio.write(rotmeio);
              delay(100);
            }
            delay(1000);
            rotgarra = 0;
            servo_garra.write(rotgarra);
            delay(1000);
            rotmeio = 0;
            rotbase = 40;
            servo_meio.write(rotmeio);
            servo_base.write(rotbase);
            delay(1000);

            for (rotmeio = 0; rotmeio < 40; rotmeio += 5) {
              servo_meio.write(rotmeio);
              delay(100);
            }
            delay(1000);
            rotgarra = 60;
            servo_garra.write(rotgarra);
            delay(1000);
            servo_meio.write(0);
            delay(1000);
            servo_garra.write(0);
            delay(1000);
          }
          Direction = ESP_BT.readString();
        }
      
      delay(1000);
      Direction = ESP_BT.readString();
      if (Direction == "W") {
        manual = 2;
        Serial.print("manual");
      }
    }
  }


    //////////////////////////////MODO CONTROLADO//////////////////////////////
    if (manual == 2) {
      lcd.clear();
      ////////////cor modo controlado - roxo
      digitalWrite(LEDG, LOW);
      digitalWrite(LEDB, HIGH);
      digitalWrite(LEDR, HIGH);



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
            if (rotgarra < 50) {
              rotgarra = 50;
              servo_garra.write(rotgarra);
            } else {
              rotgarra = 0;
              servo_garra.write(rotgarra);
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
            if (rotgarra < 50) {
              rotgarra = 50;
              servo_garra.write(rotgarra);
            } else {
              rotgarra = 0;
              servo_garra.write(rotgarra);
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
            if (rotgarra < 50) {
              rotgarra = 50;
              servo_garra.write(rotgarra);
            } else {
              rotgarra = 0;
              servo_garra.write(rotgarra);
            }
          }

          servo_base.write(rotbase);

          break;

        default:

          break;
      }
    }
  }
}
