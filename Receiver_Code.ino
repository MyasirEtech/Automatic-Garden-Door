#include <VirtualWire.h>  //VirtualWire Kütüphanesi
int RX_PIN = 6;// Alıcının data pininin hangi pine bağlandığı gösterilmiştir. PWM pini olması zorunludur
int RX_ID = 3;// Recever ID address
int TX_ID;


int redledPin = 24; //Ledin bağlı olduğu arduino
int greenledPin = 26; 
int blueledPin = 28; 
int whiteledPin = 30;
int redledPin2 = 25;
int greenledPin2 = 27;
int blueledPin2 = 29;
int whiteledPin2 = 31;
/*
  int blueledPin = 4; //Ledin bağlı olduğu arduino pini
  int greenledPin = 3; //Ledin bağlı olduğu arduino
  int redledPin = 2; //Ledin bağlı olduğu arduino
  //int whiteledPin = 30;
  int redledPin2 = 10;
  int greenledPin2 = 11;
  int blueledPin2 = 12;
  //int whiteledPin2 = 31;
*/
int calismalambasi = 48;
int buyukkapiacikendstop = 2;
int buyukkapikapaliendstop = 3;
int kucukkapiacikendstop = 14;
int kucukkapikapaliendstop = 15;
int lazersensor = 20;
int tekkapiacmabutonu = 8;
int ciftkapiacmabutonu = 9;
int motorrole_1 = 40;
int motorrole_2 = 41;
int motorrole_3 = 42;
int motorrole_4 = 43; // ilkdört role büyük kapı motorunu
int motorrole_5 = 44;
int motorrole_6 = 45;
int motorrole_7 = 46;
int motorrole_8 = 47; // son dört role ise küçük kapı motorunu

typedef struct veriler //Alınan veriler için Data Structure oluşturulmuştur
{
  int    TX_ID;      // ID verisi tanımlanmıştır
  int    PWM1Data;// PWM1 verisi tanımlanmıştır
  int    PWM2Data;// PWM2 verisi tanımlanmıştır


};

void setup() {
  pinMode(motorrole_1, OUTPUT);
  pinMode(motorrole_2, OUTPUT);
  pinMode(motorrole_3, OUTPUT);
  pinMode(motorrole_4, OUTPUT);
  pinMode(motorrole_5, OUTPUT);
  pinMode(motorrole_6, OUTPUT);
  pinMode(motorrole_7, OUTPUT);
  pinMode(motorrole_8, OUTPUT);
  digitalWrite(motorrole_1, HIGH);
  digitalWrite(motorrole_2, HIGH);
  digitalWrite(motorrole_3, HIGH);
  digitalWrite(motorrole_4, HIGH);
  digitalWrite(motorrole_5, HIGH);
  digitalWrite(motorrole_6, HIGH);
  digitalWrite(motorrole_7, HIGH);
  digitalWrite(motorrole_8, HIGH);
  pinMode(calismalambasi, OUTPUT);
  //digitalWrite(calismalambasi, HIGH); //role takılı ise
  digitalWrite(calismalambasi, LOW); //5v luk lamba takılı ise
  pinMode(blueledPin, OUTPUT);
  pinMode(greenledPin, OUTPUT);
  pinMode(redledPin, OUTPUT);
  pinMode(whiteledPin, OUTPUT);
  pinMode(blueledPin2, OUTPUT);
  pinMode(greenledPin2, OUTPUT);
  pinMode(redledPin2, OUTPUT);
  pinMode(whiteledPin2, OUTPUT);
  pinMode(buyukkapiacikendstop, INPUT);
  pinMode(buyukkapikapaliendstop, INPUT);
  pinMode(kucukkapiacikendstop, INPUT);
  pinMode(kucukkapikapaliendstop, INPUT);
  pinMode(lazersensor, INPUT);
  pinMode(tekkapiacmabutonu, INPUT);
  pinMode(ciftkapiacmabutonu, INPUT);
  Serial.begin(9600);

  vw_setup(4000);// Haberleşme için kurulum yapılır ve haberleşme başlar. Maksimum 4000kbps olarak ayarlanabilir.
  vw_set_rx_pin(RX_PIN);// Alıcı pini belirlenir
  vw_rx_start(); //alıcı modunda tarama başlar

}
void loop() {
  struct veriler alinan_veri; //alınacak veriler için atama yapılır
  uint8_t data_boyutu = sizeof(alinan_veri);//Alınacak verinin boyutu belirlenin
  vw_wait_rx();// data okuması başlar

  if (vw_get_message((uint8_t *)&alinan_veri, &data_boyutu)) // verinin mevcut olup olmaması kontrol edilir
  {
    if (alinan_veri.TX_ID == RX_ID) //eğer veri mevcutsa ID eşleşmesi kontrol edilir
    {
      if (alinan_veri.PWM1Data == 1) { //6.pinden gelen veri
        Serial.println("buyuk kapi aciliyor");
        buyukkapiacma();
      }
      if (alinan_veri.PWM2Data == 1) { //8. pinden gelen veri
        //buyukkapiacma();
        //kucukkapiacma();
        Serial.println("cift kapi aciliyor");
        ciftkapiacma();
      }
      //digitalWrite(2, alinan_veri.PWM1Data); // 2 numaralı pine okunan değer PWM olarak verilir
      //digitalWrite(3, alinan_veri.PWM2Data); // 3 numaralı pine okunan değer PWM olarak verilir
    }
  }
  if (digitalRead(tekkapiacmabutonu) == 1) {
    Serial.println("buyuk kapi aciliyor");
    buyukkapiacma();
  }
  if (digitalRead(ciftkapiacmabutonu) == 1) {
    Serial.println("cift kapi aciliyor");
    ciftkapiacma();
  }
}

void buyukkapiacma() {
  digitalWrite(redledPin, LOW);
  digitalWrite(greenledPin, LOW);
  digitalWrite(blueledPin, HIGH);
  digitalWrite(whiteledPin, LOW);
  //digitalWrite(calismalambasi, LOW);
  digitalWrite(calismalambasi, HIGH);
  digitalWrite(motorrole_1, LOW);
  digitalWrite(motorrole_2, HIGH);
  digitalWrite(motorrole_3, HIGH);
  digitalWrite(motorrole_4, LOW);
  //attachInterrupt(5, acik_kapibekleme, LOW); //18 numaralı pin LOW olduğunda
  if (digitalRead(buyukkapiacikendstop) == 0) {
    buyukkapiacikbekleme();
  }
  else {
    buyukkapiacma();
  }
}

void buyukkapikapatma() {
  digitalWrite(redledPin, HIGH);
  digitalWrite(greenledPin, LOW);
  digitalWrite(blueledPin, LOW);
  digitalWrite(whiteledPin, LOW);

  digitalWrite(motorrole_1, HIGH);
  digitalWrite(motorrole_2, LOW);
  digitalWrite(motorrole_3, LOW);
  digitalWrite(motorrole_4, HIGH);
  //attachInterrupt(4, kapali_kapibekleme, LOW);   //19 numaralı pin LOW olduğunda
  if (digitalRead(buyukkapikapaliendstop) == 0) {
    buyukkapikapalibekleme();
  }
  else {
    buyukkapikapatma();
  }
}

void buyukkapiacikbekleme() {
  digitalWrite(redledPin, LOW);
  digitalWrite(greenledPin, HIGH);
  digitalWrite(blueledPin, LOW);
  digitalWrite(whiteledPin, LOW);

  digitalWrite(motorrole_1, HIGH);
  digitalWrite(motorrole_2, HIGH);
  digitalWrite(motorrole_3, HIGH);
  digitalWrite(motorrole_4, HIGH);
  sure_15sn_buyukkapi();

}

void sure_15sn_buyukkapi () {
  delay(5000);
  //delay(5000);
  //delay(5000);
  if (digitalRead(lazersensor) == 0) {
    sure_15sn_buyukkapi();
  }
  else {
    buyukkapikapatma();
  }
}

void buyukkapikapalibekleme() {
  digitalWrite(redledPin, LOW);
  digitalWrite(greenledPin, LOW);
  digitalWrite(blueledPin, LOW);
  digitalWrite(whiteledPin, HIGH);
  digitalWrite(motorrole_1, HIGH);
  digitalWrite(motorrole_2, HIGH);
  digitalWrite(motorrole_3, HIGH);
  digitalWrite(motorrole_4, HIGH);
  //digitalWrite(calismalambasi, HIGH); 
  digitalWrite(calismalambasi, LOW);
}
/*
  void kucukkapiacma() {
  digitalWrite(redledPin2, LOW);
  digitalWrite(greenledPin2, LOW);
  digitalWrite(blueledPin2, HIGH);
  //attachInterrupt(5, acik_kapibekleme, LOW); //18 numaralı pin LOW olduğunda
  if (digitalRead(kucukkapiacikendstop) == 0) {
    kucukkapiacikbekleme();
  }
  else {
    kucukkapiacma();
  }

  }

  void kucukkapikapatma() {
  digitalWrite(redledPin2, HIGH);
  digitalWrite(greenledPin2, LOW);
  digitalWrite(blueledPin2, LOW);
  //attachInterrupt(4, kapali_kapibekleme, LOW);   //19 numaralı pin LOW olduğunda
  if (digitalRead(kucukkapikapaliendstop) == 0) {
    kucukkapikapalibekleme();
  }
  else {
    kucukkapikapatma();
  }
  }

  void kucukkapiacikbekleme() {
  digitalWrite(redledPin2, LOW);
  digitalWrite(greenledPin2, HIGH);
  digitalWrite(blueledPin2, LOW);
  sure_15sn();
  if (digitalRead(lazersensor) == 0) {
    sure_15sn();
  }
  else {
    kucukkapikapatma();
  }
  }

  void kucukkapikapalibekleme() {
  digitalWrite(redledPin2, HIGH);
  digitalWrite(greenledPin2, HIGH);
  digitalWrite(blueledPin2, HIGH);
  }
*/
void ciftkapiacikendstopkontrol() {
  if (digitalRead(buyukkapiacikendstop) == 0) {
    digitalWrite(redledPin, LOW);
    digitalWrite(greenledPin, HIGH);
    digitalWrite(blueledPin, LOW);
    digitalWrite(whiteledPin, LOW);

    digitalWrite(motorrole_1, HIGH);
    digitalWrite(motorrole_2, HIGH);
    digitalWrite(motorrole_3, HIGH);
    digitalWrite(motorrole_4, HIGH);
  }
  if (digitalRead(kucukkapiacikendstop) == 0) {
    digitalWrite(redledPin2, LOW);
    digitalWrite(greenledPin2, HIGH);
    digitalWrite(blueledPin2, LOW);
    digitalWrite(whiteledPin2, LOW);

    digitalWrite(motorrole_5, HIGH);
    digitalWrite(motorrole_6, HIGH);
    digitalWrite(motorrole_7, HIGH);
    digitalWrite(motorrole_8, HIGH);
  }
  if (digitalRead(buyukkapiacikendstop) == 0 && digitalRead(kucukkapiacikendstop) == 0) {
    ciftkapiacikbekleme();
  }
  else {
    ciftkapiacikendstopkontrol();
  }
}
void ciftkapiacma() {
  digitalWrite(redledPin2, LOW);
  digitalWrite(greenledPin2, LOW);
  digitalWrite(blueledPin2, HIGH);
  digitalWrite(whiteledPin2, LOW);
  digitalWrite(redledPin, LOW);
  digitalWrite(greenledPin, LOW);
  digitalWrite(blueledPin, HIGH);
  digitalWrite(whiteledPin, LOW);
  //digitalWrite(calismalambasi, LOW);
  digitalWrite(calismalambasi, HIGH);

  digitalWrite(motorrole_1, LOW);
  digitalWrite(motorrole_2, HIGH);
  digitalWrite(motorrole_3, HIGH);
  digitalWrite(motorrole_4, LOW);
  digitalWrite(motorrole_5, LOW);
  digitalWrite(motorrole_6, HIGH);
  digitalWrite(motorrole_7, HIGH);
  digitalWrite(motorrole_8, LOW);
  //attachInterrupt(5, acik_kapibekleme, LOW); //18 numaralı pin LOW olduğunda
  /*if (digitalRead(buyukkapiacikendstop) == 0) {
    digitalWrite(redledPin, LOW);
    digitalWrite(greenledPin, LOW);
    digitalWrite(blueledPin, LOW);
    }
    if (digitalRead(kucukkapiacikendstop) == 0) {
    digitalWrite(redledPin2, LOW);
    digitalWrite(greenledPin2, HIGH);
    digitalWrite(blueledPin2, LOW);
    }
    if (buyukkapiacikendstop && kucukkapiacikendstop == 0){
    ciftkapiacikbekleme();
    }
    else {
    ciftkapiacma();
    }*/
  ciftkapiacikendstopkontrol();
}
void ciftkapikapaliendstopcontrol() {
  if (digitalRead(buyukkapikapaliendstop) == 0) {
    digitalWrite(redledPin, LOW);
    digitalWrite(greenledPin, LOW);
    digitalWrite(blueledPin, LOW);
    digitalWrite(whiteledPin, HIGH);

    digitalWrite(motorrole_1, HIGH);
    digitalWrite(motorrole_2, HIGH);
    digitalWrite(motorrole_3, HIGH);
    digitalWrite(motorrole_4, HIGH);
  }
  if (digitalRead(kucukkapikapaliendstop) == 0) {
    digitalWrite(redledPin2, LOW);
    digitalWrite(greenledPin2, LOW);
    digitalWrite(blueledPin2, LOW);
    digitalWrite(whiteledPin2, HIGH);

    digitalWrite(motorrole_5, HIGH);
    digitalWrite(motorrole_6, HIGH);
    digitalWrite(motorrole_7, HIGH);
    digitalWrite(motorrole_8, HIGH);
  }
  if (digitalRead(buyukkapikapaliendstop) == 0 && digitalRead(kucukkapikapaliendstop) == 0) {
    ciftkapikapalibekleme();
  }
  else {
    ciftkapikapaliendstopcontrol();
  }
}
void ciftkapikapatma() {
  digitalWrite(redledPin, HIGH);
  digitalWrite(greenledPin, LOW);
  digitalWrite(blueledPin, LOW);
  digitalWrite(whiteledPin, LOW);
  digitalWrite(redledPin2, HIGH);
  digitalWrite(greenledPin2, LOW);
  digitalWrite(blueledPin2, LOW);
  digitalWrite(whiteledPin2, LOW);

  digitalWrite(motorrole_1, HIGH);
  digitalWrite(motorrole_2, LOW);
  digitalWrite(motorrole_3, LOW);
  digitalWrite(motorrole_4, HIGH);
  digitalWrite(motorrole_5, HIGH);
  digitalWrite(motorrole_6, LOW);
  digitalWrite(motorrole_7, LOW);
  digitalWrite(motorrole_8, HIGH);
  //attachInterrupt(4, kapali_kapibekleme, LOW);   //19 numaralı pin LOW olduğunda
  /*if (digitalRead(buyukkapikapaliendstop) == 0) {
    digitalWrite(redledPin, HIGH);
    digitalWrite(greenledPin, HIGH);
    digitalWrite(blueledPin, HIGH);
    }
    if (digitalRead(kucukkapikapaliendstop) == 0) {
    digitalWrite(redledPin2, HIGH);
    digitalWrite(greenledPin2, HIGH);
    digitalWrite(blueledPin2, HIGH);
    }
    if (buyukkapikapaliendstop && kucukkapikapaliendstop == 0){
    ciftkapikapalibekleme();
    }
    else {
    ciftkapikapatma();
    }*/
  ciftkapikapaliendstopcontrol();
}

void ciftkapiacikbekleme() {
  digitalWrite(redledPin, LOW);
  digitalWrite(greenledPin, HIGH);
  digitalWrite(blueledPin, LOW);
  digitalWrite(whiteledPin, LOW);
  digitalWrite(redledPin2, LOW);
  digitalWrite(greenledPin2, HIGH);
  digitalWrite(blueledPin2, LOW);
  digitalWrite(whiteledPin2, LOW);

  digitalWrite(motorrole_1, HIGH);
  digitalWrite(motorrole_2, HIGH);
  digitalWrite(motorrole_3, HIGH);
  digitalWrite(motorrole_4, HIGH);
  digitalWrite(motorrole_5, HIGH);
  digitalWrite(motorrole_6, HIGH);
  digitalWrite(motorrole_7, HIGH);
  digitalWrite(motorrole_8, HIGH);
  sure_15sn_ciftkapi();

}

void ciftkapikapalibekleme() {
  digitalWrite(redledPin, LOW);
  digitalWrite(greenledPin, LOW);
  digitalWrite(blueledPin, LOW);
  digitalWrite(whiteledPin, HIGH);
  digitalWrite(redledPin2, LOW);
  digitalWrite(greenledPin2, LOW);
  digitalWrite(blueledPin2, LOW);
  digitalWrite(whiteledPin2, HIGH);

  digitalWrite(motorrole_1, HIGH);
  digitalWrite(motorrole_2, HIGH);
  digitalWrite(motorrole_3, HIGH);
  digitalWrite(motorrole_4, HIGH);
  digitalWrite(motorrole_5, HIGH);
  digitalWrite(motorrole_6, HIGH);
  digitalWrite(motorrole_7, HIGH);
  digitalWrite(motorrole_8, HIGH);
  //digitalWrite(calismalambasi, HIGH);
  digitalWrite(calismalambasi, LOW);
}
void sure_15sn_ciftkapi() {
  delay(5000);
  //delay(5000);
  //delay(5000);
  if (digitalRead(lazersensor) == 0) {
    sure_15sn_ciftkapi();
  }
  else {
    ciftkapikapatma();
  }
}












