

#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>
#include <dht.h> 
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
 
#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
#define outPin 6 
dht DHT;
Servo servo;
LiquidCrystal_I2C lcd(0x27,16,2);
byte Heart[8] = {
0b00000,
0b01010,
0b11111,
0b11111,
0b01110,
0b00100,
0b00000,
0b00000
};
byte Skull[8] = {
0b00000,
0b01110,
0b10101,
0b11011,
0b01110,
0b01110,
0b00000,
0b00000
};


 
void setup() 
{
  Serial.begin(9600);   // Initiate a serial communication
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  Serial.println("Approximate your card to the reader...");
  Serial.println();
  servo.attach(8);
  servo.write(180);
  pinMode(7, OUTPUT);
  lcd.init();
  lcd.clear();         
  lcd.backlight(); 
  lcd.createChar(0, Heart);
  lcd.createChar(6, Skull);
}
void loop() 
{
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
  Serial.print("Message : ");
  content.toUpperCase();
  
 int readData = DHT.read11(outPin);
  float t = DHT.temperature;  // Read temperature
  float h = DHT.humidity;   // Read humidity
  Serial.print("Temperature = ");
  Serial.print(t);
  Serial.print("°C | ");
  Serial.print("Humidity = ");
  Serial.print(h);
  Serial.println("% ");
  Serial.println("");

  if (content.substring(1) == "C5 18 60 21" || content.substring(1) == "5C 22 90 6C") //change here the UID of the card/cards that you want to give access
  {
    Serial.println("Authorized access");
    Serial.println();
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Welcome Back!");
    lcd.write(0);
    lcd.setCursor(0,1);
    lcd.print("Door opened!");
    delay(2000);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Temp: ");
    lcd.setCursor(7,0);
    lcd.print(t);
    lcd.setCursor(13,0);
    lcd.print("C");
    lcd.setCursor(0,1);
    lcd.print("Humid: ");
    lcd.setCursor(7,1);
    lcd.print(h);
    lcd.setCursor(13,1);
    lcd.print("%");
    servo.write(90);
    delay(10000);
    servo.write(-90);
    Serial.println();
    delay(1000);
  }
 
 else   {
   
    digitalWrite(7,HIGH);
    delay(1000);
    digitalWrite(7,LOW);
    lcd.clear();
    lcd.setCursor(2,0);
    lcd.print("Sorry");
    lcd.write(6);
    lcd.setCursor(0,1);
    lcd.print(" Wrong card!");
    Serial.println(" Access denied");
    delay(2000);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Temp: ");
    lcd.setCursor(7,0);
    lcd.print(t);
    lcd.setCursor(13,0);
    lcd.print("C");
    lcd.setCursor(0,1);
    lcd.print("Humid: ");
    lcd.setCursor(7,1);
    lcd.print(h);
    lcd.setCursor(13,1);
    lcd.print("%");
    
  }
}   
