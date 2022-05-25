#include <NTPClient.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <ArduinoJson.h>
const char *ssid     = "homespot";
const char *password = "betheforce";
const long utcOffsetInSeconds = 19800;
const int buttonPin = 2; 
int buttonState = 0;
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
const int BUZZER = 15;

// Define NTP Client to get time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", utcOffsetInSeconds);
#define BOT_TOKEN "5188511476:AAGeCpRX07DAf7Ia1jEGyQmQv_jqKmmhUsA"
// Use @myidbot (IDBot) to find out the chat ID of an individual or a group
// Also note that you need to click "start" on a bot before it can
// message you
#define CHAT_ID "900024596"
WiFiClientSecure secured_client;
UniversalTelegramBot bot(BOT_TOKEN, secured_client);
void buzzer()
{
  int buttonState = 0;
    buttonState = digitalRead(buttonPin);
     Serial.println(buttonState);
     bot.sendMessage(CHAT_ID, "Pillbox notified User for meds", "");
     while ( buttonState == LOW )
     {
       digitalWrite(BUZZER, HIGH); 
  delay(5000);
   digitalWrite(BUZZER, LOW); 
   delay(5000);
      
      }
}

void setup() {  
  Serial.begin(115200);
   pinMode(buttonPin, INPUT);
  pinMode(BUZZER, OUTPUT);
    digitalWrite(BUZZER, LOW); 
    

  WiFi.begin(ssid, password);
  while ( WiFi.status() != WL_CONNECTED ) {
    delay ( 500 );
    Serial.print ( "." );
  }
    timeClient.begin();
     secured_client.setCACert(TELEGRAM_CERTIFICATE_ROOT);
   bot.sendMessage(CHAT_ID, "pillbox connected", "");
}
void loop() 
{
   timeClient.update();
   int h = timeClient.getHours();
    int s = timeClient.getMinutes();
   String sh = String(h);
   String ss = String(s);
   String t = sh + ":" +ss;
   Serial.println("Current Time :" + t);

    String time = "16:10";
    
    Serial.println("Set TIME :" + time);
     bot.sendMessage(CHAT_ID, "Alert set to" + time, "");
   delay(5000);
    
   if (time == t){
  buzzer();
   }
         // digitalWrite(BUZZER, HIGH); 

   
}
