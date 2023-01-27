#include <SPI.h>
#include <KeyboardFR.h>
#include <RFID.h>

#define SS_PIN 10
#define RST_PIN 9

RFID rfid(SS_PIN, RST_PIN); 

const String VALID_CARD_NUMBER = "10220********";
const String BACKUP_CARD_NUMBER = "10220********";

const String PASSWORD = "YOUR_PASSWORD";

void setup() { 
  Keyboard.begin();
  SPI.begin(); 
  rfid.init();
}

void loop() {
  if (rfid.isCard()) {
    if (rfid.readCardSerial()) {
      String card_number = "";
  
      for(int i=0; i<5; i++){
        card_number += rfid.serNum[i];
      }

      if(card_number == VALID_CARD_NUMBER || card_number == BACKUP_CARD_NUMBER){
        Keyboard.println(PASSWORD);
        delay(3000);
      }else{
        Keyboard.println(card_number);
        delay(800);
      }
      
    }
  }

  rfid.halt();
}
