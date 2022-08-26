#include <SoftwareSerial.h>

#define RxD 1

#define TxD 0

const int motor1 = 5; //velocidade motor 1 - de 0 a 255
const int motor2 = 6; //velocidade motor 2 - de 0 a 255
const int dir1 = 7; //direcao do motor 1 - HIGH ou LOW
const int dir2 = 8; //direcao do motor 2 - HIGH ou LOW

SoftwareSerial HM10(RxD, TxD);
char c;

void setup() {
  HM10.begin(9600);
  pinMode(motor1, OUTPUT);
  pinMode(motor2, OUTPUT);
  pinMode(dir1, OUTPUT);
  pinMode(dir2, OUTPUT);
  pinMode(RxD, INPUT);
  pinMode(TxD, OUTPUT);
  Serial.begin(9600);//inicia a porta serial
}

void loop() {

  {
    HM10.listen();
    while (HM10.available() > 0)
    {
      c = HM10.read();
      Serial.write(c);
    }

    if (Serial.available())
    {
      c = Serial.read();     
      delay(10);
      Serial.println(c);     
      HM10.write(Serial.read());
    }


    if (c == '3') { //comando vindo do APP Que faz o carrinho se mover para frente
      digitalWrite(dir1, HIGH); //SENTIDO DE ROTACAO
      digitalWrite(dir2, HIGH);
      analogWrite(motor1, 200); //VELOCIDADE
      analogWrite(motor2, 200);


    }
    if (c == '2') { //comando vindo do APP Que faz o carrinho se mover para trás
      digitalWrite(dir1, LOW); //SENTIDO DE ROTACAO
      digitalWrite(dir2, LOW);
      analogWrite(motor1, 200); //VELOCIDADE
      analogWrite(motor2, 200);


    }
    if (c == '5') { //comando vindo do APP Que faz o carrinho dar curva
      digitalWrite(motor1, 0);
      digitalWrite(dir1, HIGH);
      digitalWrite(motor2, 200);
      digitalWrite(dir2, LOW);

    }
    if (c == '4') { //comando vindo do APP Que faz o carrinho dar curva
      digitalWrite(motor2, 0);
      digitalWrite(dir2, HIGH);
      digitalWrite(motor1, 200);
      digitalWrite(dir1, LOW);

    }
    if (c == '6') { //comando vindo do APP Que faz o carrinho frear
      digitalWrite(motor1, 0);
      digitalWrite(dir1, LOW);
      digitalWrite(motor2, 0);
      digitalWrite(dir2, LOW);
    }

  }
}
