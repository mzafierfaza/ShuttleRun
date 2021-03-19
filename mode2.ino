
void mode2(String gender) {
  while (1) {
    bacaTombol();
    dataStream = 0;
    ibzr = 0;
    if (gender == "putra") {
      lcd.setCursor(0, 0); lcd.print("Ready");
      lcd.setCursor(5, 0); lcd.print(" | ");
      lcd.setCursor(8, 0); lcd.print("MODE_2-Putra");
      lcd.setCursor(0, 1); lcd.print("--------------------");
      lcd.setCursor(1, 2); lcd.print("Harap tekan tombol");
      lcd.setCursor(3, 3); lcd.print("Untuk memulai");
    }
    else if (gender == "putri") {
      lcd.setCursor(0, 0); lcd.print("Ready");
      lcd.setCursor(5, 0); lcd.print(" | ");
      lcd.setCursor(8, 0); lcd.print("MODE_2-Putri");
      lcd.setCursor(0, 1); lcd.print("--------------------");
      lcd.setCursor(1, 2); lcd.print("Harap tekan tombol");
      lcd.setCursor(3, 3); lcd.print("Untuk memulai");
    }
    digitalWrite(buzzer, LOW);       // buzzer LOW
    lastMillis1 = millis();
    if (!btn && !hitung_ms05) {
      hitung_ms05 = true;
      lcd.clear();
    }
    while (hitung_ms05 == true) {
      sonic3();
      lastMillis05 = millis();
      while (distance3 < jarakTrigger) {
        for (ibzr; ibzr < 1; ibzr++) {
          digitalWrite(buzzer, HIGH);    // buzzer LOW
          delay(500);
          digitalWrite(buzzer, LOW);    // buzzer LOW
        }
        sonic3();
        lastMillis1 = millis();
        //        Serial.print("lastMls05 = "); Serial.print(lastMillis05); Serial.print(" | ");
        //        Serial.print("prvsMls05 = "); Serial.print(previousMillis05); Serial.print(" | ");
        //        Serial.print("3 = "); Serial.print(distance3); Serial.println(" | ");
        kunci_start = true;
        digitalWrite(buzzer, LOW);    // buzzer LOW
      }
      if (kunci_start == true) {
        hitung_ms1 = true;
        hitung_ms05 = false;
      }
    }
    while (hitung_ms1 == true) {    // ============== LAP 1 =================
      do {
        previousMillis1 = millis();
        sonic1();
        //        Serial.print("lastMls1 = "); Serial.print(lastMillis1); Serial.print(" | ");
        //        Serial.print("prvsMls1 = "); Serial.print(previousMillis1); Serial.print(" | ");
        //        Serial.print("1 = "); Serial.print(distance1); Serial.println(" | ");

        if (previousMillis1 - lastMillis1 >= waktuBuzzer) {
          digitalWrite(buzzer, LOW);    // buzzer LOW
        }
      } while (distance1 > jarakTrigger);
      hitung_lap1 = true;
      if (hitung_lap1 == true) {
        digitalWrite(buzzer, HIGH);       // buzzer tiittttttt
        waktu_1 = (previousMillis1 - lastMillis1); // ini kan masih milidetik
        waktu_1 = waktu_1 / 1000;
        //        kecepatan1 = jarak2 / waktu_1; // satuannya mm/ms.
        //        Serial.print("Kec 1 = "); Serial.print(kecepatan1, 3); Serial.println(" | ");
        hitung_ms2 = true;
        hitung_ms1 = false;
      }
      break;
    }
    lastMillis2 = millis();
    while (hitung_ms2 == true) {     // ============== LAP 2 =================
      do {
        previousMillis2 = millis();
        sonic3();
        //        Serial.print("lastMls2 = "); Serial.print(lastMillis2); Serial.print(" | ");
        //        Serial.print("prvsMls2 = "); Serial.print(previousMillis2); Serial.print(" | ");
        //        Serial.print("2 = "); Serial.print(distance2); Serial.println(" | ");

        if (previousMillis2 - lastMillis2 >= waktuBuzzer) {
          digitalWrite(buzzer, LOW);    // buzzer LOW
        }
      } while (distance3 > jarakTrigger);
      hitung_lap2 = true;
      if (hitung_lap2 == true) {
        digitalWrite(buzzer, HIGH);       // buzzer tiittttttt
        waktu_2 = (previousMillis2 - lastMillis2); // ini kan masih milidetik
        waktu_2 = waktu_2 / 1000;   // dakjadi pake kecepatan , jadinyo ambek waktu nyo bae
        //        kecepatan2 = jarak2 / waktu_2; // satuannya mm/ms.
        //        Serial.print("Kec 1 = "); Serial.print(kecepatan1, 3); Serial.print(" | ");
        //        Serial.print("Kec 2 = "); Serial.print(kecepatan2, 3); Serial.println(" | ");
        hasil = true;
        hitung_ms2 = false;
      }
      break;
    }
    while (hasil == true) {
      bacaTombol();
      total = (waktu_1 + waktu_2);
      if (gender == "putra") {
        cekNilai(total, "male");
      }
      else if (gender == "putri") {
        cekNilai(total, "female");
      }

      // ------------- Serial to Excel ---------------------
      for (dataStream; dataStream < 1; dataStream++) {
        digitalWrite(buzzer, HIGH);    // buzzer tiittttt
        delay(1000);
        digitalWrite(buzzer, LOW);       // buzzer LOW
        lcd.setCursor(0, 0); lcd.print("1: ");
        lcd.setCursor(3, 0); lcd.print(waktu_1);
        lcd.setCursor(9, 0); lcd.print("|");
        lcd.setCursor(0, 1); lcd.print("2: ");
        lcd.setCursor(3, 1); lcd.print(waktu_2);
        lcd.setCursor(9, 1); lcd.print("|");
        lcd.setCursor(11, 1); lcd.print("T: ");
        lcd.setCursor(14, 1); lcd.print(total); // rata2
        lcd.setCursor(0, 2); lcd.print("--------------------");
        lcd.setCursor(0, 3); lcd.print("Rate: ");
        lcd.setCursor(5, 3); lcd.print(nilai);
        Serial.print("DATA,");
        Serial.print("2,");   // MODE
        Serial.print(waktu_1);   // Lap 1
        Serial.print(" s,");
        Serial.print(kecepatan2);   // Lap 2
        Serial.print(" s,");
        Serial.print("0 ");   // Lap 3
        Serial.print(" s,");
        Serial.print(total);    // Total
        Serial.print(" s,");
        Serial.print(nilai);    // String Nilai
        Serial.print(",");    //
        Serial.println(gender);    // String gender
      }
      if (!mode) {  // tombol reset maka dia reset
        lcd.clear();
        delay(200);
        hasil = false;
        break;
      }
    }
    break;
  }
}
