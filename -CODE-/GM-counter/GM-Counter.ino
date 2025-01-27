#include "Arduino_SensorKit.h"

#define GEIGER 2 // Cteni impulzu z obvodu
#define refreshRate 500 
#define pocet_snimani 30

 /* Globalne */
unsigned long pulzy_celkove = 0;
unsigned long pulzy_za_minutu = 0;
int data_pulzu[poccet_snimani];

void setup() {
 /* Nastavení displeje */
  Oled.begin(); 
  Oled.setFlipMode(false); 

 /* Serial */
  Serial.begin(9600);

 /* Pin Modes, Interupty */
  pinMode(GEIGER, INPUT_PULLUP); // musí být pull-up, jinak by nastal floating stav a zaznamenávaly by se falešné pulzy. lze resit tez jako digitalWrite(GEIGER, 1); // pripadne donastavuje pull-up na pinu 2
  attachInterrupt(digitalPinToInterrupt(GEIGER), geiger_pulzy, RISING); // Interupt na cteni pulzu
}
 
void loop() {
/* TESTY */
   





/* ------ */

  unsigned long radiace = analogRead(A0);
  unsigned long cas = millis();
  static unsigned long cas_pred = millis();
  unsigned long cas_prevod = cas / 1000;
  static int radiace_nachytana = 50;
  static int CPM = pulzy_za_minutu;
  

 if((cas - cas_pred) >= refreshRate) { // OLED DISPLAY
    cas_pred = cas;
    Oled.setFont(u8x8_font_chroma48medium8_r);  

    Oled.setCursor(1, 1);    // UI
    Oled.print("---Dozimetr--- ");

    Oled.setCursor(0, 3);   // Radiace aktualne - podle CPM
    Oled.print("Ted: ");
    Oled.print(radiace);   
    Oled.print("uSv/h");

    Oled.setCursor(9, 5);    // CPM (counts per minute)
    Oled.print(CPM); 
    Oled.print("CPM");

    Oled.setCursor(0, 6);    // cas zapnuti 
    Oled.print("Cas: ");
    Oled.print(cas_prevod);
    Oled.print("s");

    Oled.setCursor(0, 7);    // celkova radiace txt
    Oled.print("Celkove: ");
    Oled.print(radiace_nachytana);
    Oled.print("uSv");

    Oled.refreshDisplay();    // refresh displaye
 }


}

void geiger_pulzy() {
  pulzy_celkove++;
  pulzy_za_minutu++;
  Serial.println(pulzy_celkove); // check v serial monitoru
}