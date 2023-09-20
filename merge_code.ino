//Viral Science
//RFID
//solinoid added with the led pin
#include <Wire.h>
#include <SPI.h>
#include <MFRC522.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
LiquidCrystal_I2C lcd(0x27,16,2);

const byte ROWS = 4; //four rows
const byte COLS = 3; //three columns
int ledPin = A0;
char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};

char key_code[3];
char password[3]={'3','2','1'};
int lock =A0;

const int ledp =  A3;
const int ledn =  A2;
const int buzzp =  A1;
const int buzzn =  A0;

unsigned int k=0;
byte rowPins[ROWS] = {8, 7, 6, 5}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {4, 3, 2}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
int i=0;
 
#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.

 
void setup() 
{
  Serial.begin(9600);   // Initiate a serial communication
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522 rfid
 
  
 Serial.begin(9600);
  pinMode(lock, OUTPUT);
  pinMode(ledp, OUTPUT);
  pinMode(ledn, OUTPUT);
  pinMode(buzzp, OUTPUT);
  pinMode(buzzn, OUTPUT);
  digitalWrite(lock, HIGH); 
  pinMode(ledPin, OUTPUT);
  SPI.begin(); // Init SPI bus
  Serial.println("Put your card to the reader.......or Enter the secret code");
  Serial.println();

 lcd.begin();                      
  lcd.backlight();
  // lcd.setCursor(0,0);
  // lcd.print("  RFID & KEYPAD ");
  // lcd.setCursor(0,1);
  // lcd.print("  Lock Project  "); 
  // lcd.clear();  
   lcd.setCursor(0, 0);
  lcd.print("Scan Your Card");
  lcd.setCursor(0, 1);
  lcd.print("Enter the Pass");
}
  
void loop() 
{
  
   char key = keypad.getKey();
  
    if(key != NO_KEY){
    //Serial.println(key);
    //Serial.println("pressed:");    
    //Serial.print(i);    
     key_code[i++]=key;
     k=i;
    delay(200);
    digitalWrite(lock, HIGH);
     
     }
     if(k==3){
   //if(key_code[0]=='3'&&key_code[1]=='2'&&key_code[2]=='1'){
   if(!strncmp(password,key_code,3)){
   lcd.clear() ;
   lcd.setCursor(0, 1);lcd.print("Access Granted");
   
   Serial.println("");
   Serial.println("                                 Accurate secret code ");
   Serial.println("                                 Message : Access Granted");
   digitalWrite(ledp, HIGH);digitalWrite(ledn, LOW);delay(100);digitalWrite(ledp, LOW);digitalWrite(ledn, LOW);
   digitalWrite(buzzp, HIGH);digitalWrite(buzzn, LOW);delay(100);digitalWrite(buzzp, LOW);digitalWrite(buzzn, LOW);
   digitalWrite(lock, LOW);
   delay(1000);digitalWrite(lock, HIGH); 
   
    i=k=0;  
  
  lcd.setCursor(0, 0);
  lcd.print("Scan Your Card");
  lcd.setCursor(0, 1);
  lcd.print("Enter the Pass");
   }
 }

 
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Show UID on serial monitor
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : Access Granted");
  
   lcd.setCursor(0, 0);
  lcd.print("Scan Your Card");
  lcd.setCursor(0, 1);
  lcd.print("Enter the Pass");
  content.toUpperCase();







  
  if (content.substring(1) == "C7 B9 DE 19" || content.substring(1) == "19 79 FC A3" || content.substring(1) == "89 15 14 09" || content.substring(1) == "79 D3 BC 01") //change here the UID of the card/cards that you want to give access
  {
    
 lcd.clear() ; lcd.setCursor(0, 0);lcd.print("Access Granted");
     digitalWrite(ledp, HIGH);digitalWrite(ledn, LOW);delay(100);digitalWrite(ledp, LOW);digitalWrite(ledn, LOW);
   digitalWrite(buzzp, HIGH);digitalWrite(buzzn, LOW);delay(1000);digitalWrite(buzzp, LOW);digitalWrite(buzzn, LOW);
     delay(1000);digitalWrite(lock, HIGH);  delay(2000);
      
    i=k=0;  
    lcd.setCursor(0, 0);
  lcd.print("Scan Your Card");
  lcd.setCursor(0, 1);
  lcd.print("Enter the Pass");
    
    Serial.println();
    delay(500);
  
  }

} 
