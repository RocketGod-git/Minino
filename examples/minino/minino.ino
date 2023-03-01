#include "enum.h"

#include <Wire.h>
#include <SPI.h>
#include <ArduinoBLE.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>


Adafruit_SH1106G display = Adafruit_SH1106G(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);



void setup() {
  pinMode(5, INPUT_PULLUP);
  pinMode(6, INPUT_PULLUP);
  pinMode(9, INPUT_PULLUP);
  pinMode(10,INPUT_PULLUP);

  Serial.begin(9600);

  // Begin initialization

  if (!display.begin(SCREEN_ADDRESS)) {
    //Serial.println(F("SH110X allocation failed"));
    for (;;); // Don't proceed, loop forever
  }
  display.clearDisplay(); 
  display.setTextSize(1);
  display.setTextColor(SH110X_WHITE);
  display.setCursor(0,0);
  display.println("BIENVENIDO");
  display.display();


  display.drawLine(0, 10, 128, 10, SH110X_WHITE);
  display.display();
  display.drawBitmap( (display.width() - LOGO_WIDTH ) / 2,((display.height()- LOGO_HEIGHT) / 2 )+4, logo, LOGO_WIDTH, LOGO_HEIGHT, SH110X_WHITE);
  display.display();
  delay(2000); 
  if (!BLE.begin()) {
   while (1);
  }
    BLE.scan();

}
  
void loop() {
  displayMenu();
   
}

void displayMenu() {

  int down = digitalRead(5);
  int up = digitalRead(6);
  int enter = digitalRead(9);
  int back = digitalRead(10);

  if (up == LOW && down == LOW) {
  };
  if (up == LOW) {
    selected++;
    delay(200);
  }
   if(selected==4){
        selected=0;}
  if (down == LOW) {
    selected--;
    delay(200);
  }
  if(selected==-1){
        selected=3;
      };
  if (enter == LOW) {
    Layer = selected;
  };
  if (back == LOW) {
    Layer = -1;
  };
  const char *options[4] = {
    " 1.-SCAN",
    " 2.-SPOOF",
    " 3.-DETECT",
    " 4.-SOUND "
  };

  if (Layer == -1) {                       
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SH110X_WHITE);
    display.setCursor(0, 0);
    display.println(F("MAIN MENU"));
    //display.print(selected);
    display.println("");
    for (int i = 0; i < 4; i++) {
      if (i == selected) {
        display.setTextColor(SH110X_BLACK, SH110X_WHITE);
        display.println(options[i]);
      } 
      else if (i != selected) {
        display.setTextColor(SH110X_WHITE);
        display.println(options[i]);
      }
    }
  } 
  if (Layer == 0) {
    Scanner();
    //llamar funcion de scan 
    //una vrez presionado back sale de funcion
  } 
  if (Layer ==1) {
   
    //spoofDevice();
  }
   if (Layer == 2) {
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SH110X_WHITE);
    display.setCursor(0, 0);
    display.println(F("Detect"));
    display.println("configuration");
    display.setTextColor(SH110X_WHITE);
    display.setTextSize(2);
    display.println("Detecting...");
  } 
   if (Layer == 3) {
   soundDevice();
  } 
   

 display.display();
}

//--------------------------------Init sound device Function------------------------------------//
//una vez presionado back sale de funcion
void Scanner(){
  
    display.println("BLE scan - filtering AirTags");
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SH110X_WHITE);
    display.setCursor(0, 0);
    display.println(F("Scan Function"));
    delay(1000);
  // Start scanning for peripheral
BLEDevice peripheral = BLE.available(); 
  
  if (peripheral){
    
    int adLength = peripheral.advertisementData(advertisement,31);
    if (advertisement[0] == 0x1e && advertisement[2] == 0x4c && advertisement[3] == 0x00){ //Check if it is an Apple AirTag

    display.setTextSize(1);
    display.setTextColor(SH110X_WHITE);    
    display.println(F("Detected AirTag!! -"));
         delay(2000);

      display.println("-------"); 
      
      display.setTextSize(1);
      display.setTextColor(SH110X_WHITE);
      
      display.print("Detected AirTag!! - ");
      delay(2000);
      
      if (advertisement[4] == 0x12 && advertisement[6] == 0x10){
    
       display.setTextSize(1);
       display.setTextColor(SH110X_WHITE);
       display.println("Registered and active device");
       delay(2000);
      }
      else if(advertisement[4] == 0x07 && advertisement[6] == 0x05){
       // Serial.print("Unregister device");
      }
  
      
      display.print("Address: "); display.println(peripheral.address());
      display.print("Advertising data: ");
      for (int x = 0; x < 31; x++) {
        display.print(advertisement[x],HEX); display.print(" ");
      }
      //Serial.println("");
      //Serial.println("-------"); 
      
      //Serial.print("RSSI: ");
      //Serial.println(peripheral.rssi());
    }
    else {
      
      display.setTextSize(1);
      display.setTextColor(SH110X_WHITE);
      display.println("Found device, but ");
      display.println("it is not an AirTag");
      display.println("Address:"); display.println(peripheral.address()); display.println(peripheral.deviceName());
          delay(1000);

    }
  }
}

//--------------------------------Init spoof device Function------------------------------------//


void spoofDevice(){ //Spoof advertising data
   display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SH110X_WHITE);
    display.setCursor(0, 0);
    display.println("Spoof Function");
    
  uint8_t adv[27];
  for (int x = 4; x < 31; x++) {
    adv[x-4] = (byte)advertisement[x];
  }

  uint16_t idm = 0x004c; //Apple ID
  //setAdvertisingData(BLEAdvertisingData& advertisingData)

  BLE.setManufacturerData(idm, adv, sizeof(adv));
  BLE.advertise();
  
  while (1){}
}


//--------------------------------Init sound device Function------------------------------------//


void checkTimeout() {
    unsigned long nowTime = millis() - delayStart[positiona];
  if (nowTime >= DELAY_TIME) {
    //delayStart[positiona] += DELAY_TIME;         // This prevents drift in the delays
    actives[positiona] = true;
    //Serial.println("Timeout!!");
  }
  else{
    actives[positiona] = false;
  }
}
bool conec (BLEDevice peripheral){                //Establish the BLE connection to the AirTag
  bool cn = false;
  BLE.stopScan();
  
  if (peripheral.connect()) {
    Serial.println("Connected");
    cn = true;
    
    Serial.println("Discovering attributes...");
    if (peripheral.discoverAttributes() ) {
      Serial.println("Attributes discovered");
    }
    else {
      Serial.println("Attribute discovery failed!");
      peripheral.disconnect();
      cn = false;
    }
  }
  else {
    Serial.println("Failed to connect!");
  }
  
  return cn;
}
void wcharc(BLEDevice peripheral){ //Play a sound
  BLECharacteristic nCharac = peripheral.characteristic("7dfc9001-7d1c-4951-86aa-8d9728f8d66c");
  if (nCharac) {
   Serial.print("Found characteristic! Writing..."); 
   Serial.println(nCharac.writeValue((byte)0x01));
  } else {
    Serial.println("Peripheral does NOT have that characteristic");
  }
}
void soundDevice(){
     display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SH110X_WHITE);
    display.setCursor(0, 0);
    display.println("Sound Function");
    delay(1000);
  BLEDevice peripheral = BLE.available(); 
 // check if a peripheral has been discovered
  
  bool chkc = false, rtag = false;
  
  if (peripheral){
    int adLength = peripheral.advertisementData(advertisement,31);
    
    if (advertisement[0] == 0x1e && advertisement[2] == 0x4c && advertisement[3] == 0x00){ //Check if it is an Apple AirTag
      // print address
      Serial.println("-------"); 
      Serial.print("Detected AirTag!! - ");
      if (advertisement[4] == 0x12 && advertisement[6] == 0x10){
        Serial.print("Registered and active device");
        rtag = true;
      }
      else if(advertisement[4] == 0x07 && advertisement[6] == 0x05){
        Serial.print("Unregister device");
      }
      
      Serial.print(" - Address: "); Serial.println(peripheral.address());
      Serial.print("Advertising data: ");
      for (int x = 0; x < 31; x++) {
        Serial.print(advertisement[x],HEX); Serial.print(" ");
      }
      Serial.println("");
        
      if(rtag == true) {
        checkTimeout();      
        for (uint8_t i = 0; i < limitDevices; i++){ //Save the AirTag in the array
          if (!mairtags[i].equals(peripheral.address())){
            if (mairtags[i].equals("")){
  
              chkc = conec(peripheral);
              if (chkc) {
                
                mairtags[i] = peripheral.address(); 
                Serial.print("Saved in memory "); Serial.println(mairtags[i]);Serial.print(" - Position: "); Serial.println(i);
              
                delayStart[i] = millis();
                positiona = i;
                delayRunning = 1;
                memcpy(&advertags[i][0], advertisement, sizeof(advertisement));
              }
              BLE.scan();
              delay(50);
              break;
            }
          }
          else {
            display.println("This AirTag is alredy in memory...");
            positiona = i;
            break;
          }
        }
      }          
      
      if (actives[positiona] || playSoundm){
        chkc = conec(peripheral);
        if (chkc){
          wcharc(peripheral);
        }
        BLE.scan();
        delay(50);
      }
      Serial.println("-------");
    }
    else {
      display.println("Found device, but");
      display.println("it is not an AirTag");
      display.println("Address:"); display.println(peripheral.address()); display.println(peripheral.deviceName());
      delay(1000);
    }
  }
}
