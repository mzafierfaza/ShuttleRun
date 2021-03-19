#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 20, 4);
float kecepatan1, kecepatan2, kecepatan3, total;
float jarak1 = 5000;  // jarak 5 meter
float jarak2 = 10000; // jarak 10 meter
float jarak3 = 5000;  // jarak 5 meter
int distance1, distance2, distance3;
int jarakTrigger = 30;
int waktuBuzzer = 500;
float waktu_1, waktu_2, waktu_3;
int mode_no;
const int TRIG_PIN_1 = 2;
const int ECHO_PIN_1 = 3;
const int TRIG_PIN_2 = 4;
const int ECHO_PIN_2 = 5;
const int TRIG_PIN_3 = A1;
const int ECHO_PIN_3 = A2;
const int btnPin = 12;
const int btnOk = 11;
const int btnMode = 9;
const int buzzer = 7;
const int pinLedKuning = 10;
const int pinLedBiru = 8;
int btn, ok, mode;
bool kunci_start = false;
bool hasil = false;
bool hitung_ms1, hitung_ms2, hitung_ms3,hitung_ms05 = false;
bool hitung_lap1, hitung_lap2, hitung_lap3 = false;
const long interval = 1;
unsigned long lastMillis1, lastMillis2, lastMillis3, lastMillis05 = 0;
unsigned long previousMillis1, previousMillis2, previousMillis3, previousMillis05 = 0; // millis() returns an unsigned long.
String nilai;
int dataStream, ibzr = 0;
void setup() {
  lcd.init();
  lcd.backlight();
  Serial.begin(9600);
  pinMode(btnPin, INPUT_PULLUP);
  pinMode(btnOk, INPUT_PULLUP);
  pinMode(btnMode, INPUT_PULLUP);
  pinMode(pinLedKuning, OUTPUT);
  pinMode(pinLedBiru, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(TRIG_PIN_1, OUTPUT);
  pinMode(ECHO_PIN_1, INPUT);
  pinMode(TRIG_PIN_2, OUTPUT);
  pinMode(ECHO_PIN_2, INPUT);
  pinMode(TRIG_PIN_3, OUTPUT);
  pinMode(ECHO_PIN_3, INPUT);
  lcd.setCursor(0, 0); lcd.print("====================");
  lcd.setCursor(4, 1); lcd.print("Shuttle Run");
  lcd.setCursor(0, 2); lcd.print("====================");
  Serial.println("CLEARSHEET");
  Serial.println("LABEL,Mode,Lap 1,Lap 2,Lap 3, Total, Keterangan, Kategori");
  delay(500);
  lcd.clear();
}

void loop() {
  homescreen();
}


void homescreen() {
  while (1) {
    bacaTombol();
    if (!mode) {
      if (++mode_no == 5) mode_no = 0;
      delay(200);
    }
    switch (mode_no) {
      case 0:
        mode1("putra");
        break;
      case 1:
        mode2("putra");
        break;
      case 2:
        mode1("putri");
        break;
      case 3:
        mode2("putri");
        break;
      case 4:
        lcd.setCursor(0, 0); lcd.print("Ready");
        lcd.setCursor(5, 0); lcd.print(" | ");
        lcd.setCursor(8, 0); lcd.print("CekSensor    ");
        lcd.setCursor(0, 1); lcd.print("--------------------");
        lcd.setCursor(1, 2); lcd.print("Harap tekan tombol");
        lcd.setCursor(3, 3); lcd.print("Untuk memulai");
        if (!btn) bacaSensor();
        break;
    }
  }
}


void bacaTombol() {
  btn = digitalRead(btnPin);
  ok = digitalRead(btnOk);
  mode = digitalRead(btnMode);
}


void bacaSensor() {
  lcd.clear();
  while (1) {
    bacaTombol();
    sonic1();
    sonic2();
    sonic3();
    lcd.setCursor(0, 0); lcd.print("Sensor 1 = ");
    lcd.setCursor(11, 0); lcd.print(distance1); lcd.print("   ");
    lcd.setCursor(15, 0); lcd.print("CM");
    lcd.setCursor(0, 1); lcd.print("Sensor 2 = ");
    lcd.setCursor(11, 1); lcd.print(distance2); lcd.print("   ");
    lcd.setCursor(15, 1); lcd.print("CM");
    lcd.setCursor(0, 2); lcd.print("Sensor 3 = ");
    lcd.setCursor(11, 2); lcd.print(distance3); lcd.print("   ");
    lcd.setCursor(15, 2); lcd.print("CM");
    lcd.setCursor(0, 3); lcd.print("Mode untuk kembali");
    if (!mode) break;
  }
  lcd.clear();
  delay(200);
}


void cekNilai(float total, String gender) {
  if (gender == "female") {
    if (total <= 12.42) {
      nilai = "(A) Sangat Baik";
    }
    else if (total >= 12.43 && total < 14.10) {
      nilai = "(B) Baik" ;
    }
    else if (total >= 14.10 && total < 15.75) {
      nilai = "(C) Cukup" ;
    }
    else if (total >= 15.75 && total < 17.40) {
      nilai = "(D) Kurang" ;
    }
    else if (total >= 17.40) {
      nilai = "(E) Sangat Kurang" ;
    }
  }
  else if (gender == "male") {
    if (total <= 12.10) {
      nilai = "(A) Sangat Baik";
    }
    else if (total >= 12.11 && total < 13.54) {
      nilai = "(B) Baik" ;
    }
    else if (total >= 13.54 && total < 14.97) {
      nilai = "(C) Cukup" ;
    }
    else if (total >= 14.97 && total < 16.4) {
      nilai = "(D) Kurang" ;
    }
    else if (total >= 16.4) {
      nilai = "(E) Sangat Kurang" ;
    }
  }
}

int sonic1() {
  digitalWrite(TRIG_PIN_1, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN_1, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN_1, LOW);
  const unsigned long duration1 = pulseIn(ECHO_PIN_1, HIGH);
  distance1 = duration1 / 29 / 2;
  return distance1;
}


int sonic2() {
  digitalWrite(TRIG_PIN_2, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN_2, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN_2, LOW);
  const unsigned long duration2 = pulseIn(ECHO_PIN_2, HIGH);
  distance2 = duration2 / 29 / 2;
  return distance2;
}


int sonic3() {
  digitalWrite(TRIG_PIN_3, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN_3, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN_3, LOW);
  const unsigned long duration3 = pulseIn(ECHO_PIN_3, HIGH);
  distance3 = duration3 / 29 / 2;
  return distance3;
}
