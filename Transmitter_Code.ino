#include <VirtualWire.h> // VirtualWire Kütüphanesi
 
int pwm1;
int pwm2;
int TX_PIN = 12;// Arduino'ya bağlanan verici data pini. !!PWM pini olmak zorundadır
int TX_ID = 3; // Verici ID'si. Alıcı tarafından tanınması için
 
typedef struct veriler// Structure tanımlanmıştır. Burada gönderilecek veriler tanımlanmıştır
{
int    TX_ID;     
int    PWM1Data;
int    PWM2Data;
};
 
void setup() {
 
  pinMode(6,INPUT); //Analog giriş pinleri tanımlanmıştır
  pinMode(8,INPUT);
 
  vw_setup(4000);//Haberleşme için kurulum yapılır ve haberleşme başlar. Maksimum 4000kbps olarak ayarlanabilir.
  vw_set_tx_pin(TX_PIN);// data bacağının nereye bağlı olduğu tanımlanır
 
              }
void loop()
{
  pwm1=digitalRead(6); // A3 pininden analog okuma yapılır
 
  pwm2=digitalRead(8); // A4 pininden analog okuma yapılır
  
  struct veriler payload;// Göndermek istenilen veri tanımlanmıştır
  
  
  payload.TX_ID = 3; // ID değeri belirlenir
  payload.PWM1Data =pwm1; //PWM1 değeri payload yapısına yüklenir
  payload.PWM2Data =pwm2; // PWM2 değeri payload yapısına yüklenir
 
  vw_send((uint8_t *)&payload, sizeof(payload)); // Payload verisi gönderilir. Yani içinde bulunan ID, PWM1 ve PWM2 değerleri gönderilmiştir.
  vw_wait_tx();// Bütün datanın gönderilmesi beklenir 
}
