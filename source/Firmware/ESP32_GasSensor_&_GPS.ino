#include <WiFi.h>
#include <HTTPClient.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);

#define MQ6_PIN 34
int threshold = 1400;

const char* ssid = "Galaxy M33 5G D2C2";
const char* password = "mxod2996";
const char* serverName = "http://10.106.254.107:5000/gasdata";

/* -------- GPS -------- */
HardwareSerial gpsSerial(1);
String line="";
float latitude=0.0;
float longitude=0.0;
bool gpsFix=false;

float convertToDecimal(String raw,String dir){
  float val=raw.toFloat();
  int deg=(int)(val/100);
  float minutes=val-(deg*100);
  float dec=deg+(minutes/60.0);
  if(dir=="S"||dir=="W") dec=-dec;
  return dec;
}
/* ---------------------- */

void setup(){

  Serial.begin(115200);

  Wire.begin(21,22);
  lcd.init();
  lcd.backlight();

  gpsSerial.begin(9600,SERIAL_8N1,16,17);

  lcd.setCursor(0,0);
  lcd.print("Connecting WiFi");

  WiFi.begin(ssid,password);

  int attempts = 0;

  while(WiFi.status()!=WL_CONNECTED && attempts<20){
    delay(500);
    Serial.print(".");
    attempts++;
  }

  if(WiFi.status()==WL_CONNECTED){
    Serial.println("WiFi Connected");
    lcd.clear();
    lcd.print("WiFi Connected");
  }
  else{
    Serial.println("WiFi Failed");
    lcd.clear();
    lcd.print("WiFi Failed");
  }

  delay(2000);
  lcd.clear();
}

void loop(){

/* -------- GPS READ (NON BLOCKING) -------- */

while(gpsSerial.available()){

  char c = gpsSerial.read();

  if(c=='\n'){
    Serial.println(line);
    if(line.startsWith("$GPRMC")){

      int idx1=line.indexOf(',');
      int idx2=line.indexOf(',',idx1+1);
      int idx3=line.indexOf(',',idx2+1);
      int idx4=line.indexOf(',',idx3+1);
      int idx5=line.indexOf(',',idx4+1);
      int idx6=line.indexOf(',',idx5+1);

      String stat=line.substring(idx2+1,idx3);

      if(stat=="A"){

        String lat=line.substring(idx3+1,idx4);
        String latDir=line.substring(idx4+1,idx5);
        String lon=line.substring(idx5+1,idx6);
        String lonDir=line.substring(idx6+1,line.indexOf(',',idx6+1));

        latitude=convertToDecimal(lat,latDir);
        longitude=convertToDecimal(lon,lonDir);

        gpsFix=true;

      }else{
        gpsFix=false;
      }
    }

    line="";
  }
  else{
    line+=c;
  }
}

/* -------- GAS SENSOR -------- */

int gasValue = analogRead(MQ6_PIN);

Serial.print("Gas value: ");
Serial.println(gasValue);

String gasStatus = (gasValue>threshold)?"LEAK":"SAFE";

/* -------- LCD DISPLAY -------- */

lcd.setCursor(0,0);
lcd.print("Gas:");
lcd.print(gasValue);
lcd.print("   ");

lcd.setCursor(0,1);

if(gpsFix){
  lcd.print("GPS OK ");
}
else{
  lcd.print("No GPS ");
}

/* -------- SEND TO SERVER -------- */

if(WiFi.status()==WL_CONNECTED){

  HTTPClient http;

  http.begin(serverName);
  http.addHeader("Content-Type","application/json");

  String jsonData="{";
  jsonData+="\"gas_value\":"+String(gasValue)+",";
  jsonData+="\"status\":\""+gasStatus+"\",";

  if(gpsFix){
    jsonData+="\"latitude\":"+String(latitude,6)+",";
    jsonData+="\"longitude\":"+String(longitude,6);
  }
  else{
    jsonData+="\"latitude\":0,";
    jsonData+="\"longitude\":0";
  }

  jsonData+="}";

  Serial.println("Sending data:");
  Serial.println(jsonData);

  int httpResponseCode=http.POST(jsonData);

  Serial.print("HTTP Response: ");
  Serial.println(httpResponseCode);

  http.end();
}

delay(3000);

}
