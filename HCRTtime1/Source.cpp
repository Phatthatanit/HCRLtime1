#include <M5Stack.h> 
#include <WiFi.h>  
#include <time.h>    
#include <SPI.h>
#include <Wire.h>



int timezone1 = 7 * 3600;
int timezone2 = 0;
int dst = 0;



void wifiSetup();
#define WiFi_STA_USERNAME "eieii"       
#define WiFi_STA_PASSWORD "0823268199" 
#define Intervals 100 
unsigned long long previousMillis_WiFi = 0;

void setup() {
    Serial.begin(115200);
    wifiSetup();
    M5.begin();
    M5.Power.begin();

    M5.Lcd.setTextSize(5);
    M5.Lcd.printf("   CLOCK");

    configTime(timezone1, dst, "pool.ntp.org", "time.nist.gov");
    M5.Lcd.println("\nWaiting for NTP...");
    while (!time(nullptr)) {
        Serial.print("*");

        delay(1000);
    }
    M5.Lcd.println("\nTime response....OK");
    M5.Lcd.display();
    delay(1000);

    M5.Lcd.clear();
    M5.Lcd.display();

}



void loop() {
    stoptime();
    configTime(timezone2, dst, "pool.ntp.org", "time.nist.gov");
    time_t now = time(nullptr);
    struct tm* p_tm = localtime(&now);

    M5.Lcd.clear();

    M5.Lcd.setTextSize(3);
    M5.Lcd.setTextColor(WHITE);

    M5.Lcd.setCursor(0, 0);
    M5.Lcd.print(p_tm->tm_hour);
    M5.Lcd.print(":");
    if (p_tm->tm_min < 10)
        M5.Lcd.print("0");
    M5.Lcd.print(p_tm->tm_min);

    M5.Lcd.setTextSize(2);
    M5.Lcd.setCursor(90, 5);
    M5.Lcd.print(".");
    M5.Lcd.setCursor(105, 0);
    M5.Lcd.setTextSize(3);
    if (p_tm->tm_sec < 10)
        M5.Lcd.print("0");
    M5.Lcd.print(p_tm->tm_sec);
    M5.Lcd.setTextSize(2);
    M5.Lcd.setCursor(155, 5);
    M5.Lcd.print("( UTC +0 )");

    M5.Lcd.setTextSize(2);
    M5.Lcd.setCursor(0, 40);
    M5.Lcd.print(p_tm->tm_mday);
    M5.Lcd.print("/");
    M5.Lcd.print(p_tm->tm_mon + 1);
    M5.Lcd.print("/");
    M5.Lcd.print(p_tm->tm_year + 1900);

    //timeline2
    configTime(timezone1, dst, "pool.ntp.org", "time.nist.gov");
    now = time(nullptr);
    p_tm = localtime(&now);

    M5.Lcd.setTextSize(3);
    M5.Lcd.setCursor(0, 80);
    M5.Lcd.print(p_tm->tm_hour);
    M5.Lcd.print(":");
    if (p_tm->tm_min < 10)
        M5.Lcd.print("0");
    M5.Lcd.print(p_tm->tm_min);

    M5.Lcd.setTextSize(2);
    M5.Lcd.setCursor(90, 85);
    M5.Lcd.print(".");
    M5.Lcd.setTextSize(3);
    M5.Lcd.setCursor(105, 80);
    if (p_tm->tm_sec < 10)
        M5.Lcd.print("0");
    M5.Lcd.print(p_tm->tm_sec);
    M5.Lcd.setTextSize(2);
    M5.Lcd.setCursor(155, 85);
    M5.Lcd.print("( UTC +7 )");


    M5.Lcd.setTextSize(2);
    M5.Lcd.setCursor(0, 120);
    M5.Lcd.print(p_tm->tm_mday);
    M5.Lcd.print("/");
    M5.Lcd.print(p_tm->tm_mon + 1);
    M5.Lcd.print("/");
    M5.Lcd.print(p_tm->tm_year + 1900);




    M5.Lcd.display();

    delay(1000); // update every 1 sec



}
void wifiSetup()
{
    Serial.println();
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(WiFi_STA_USERNAME);

    //* WiFi Connection
    WiFi.mode(WIFI_STA);
    WiFi.begin(WiFi_STA_USERNAME, WiFi_STA_PASSWORD);

    Serial.print("Status: [");
    while (WiFi.status() != WL_CONNECTED)
    {
        //* Time Loop Uss Millis
        unsigned long currentMillis = millis(); //? Store Current time
        if (currentMillis - previousMillis_WiFi > Intervals)
        {
            previousMillis_WiFi = currentMillis; //? Save Current time
            Serial.print("=");
        }
    }
    Serial.println("] 100%");

    Serial.println("--- WiFi Connected ---");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
}

void stoptime() {
    for (; M5.BtnB.wasPressed();) {
        M5.Lcd.clear();
        M5.Lcd.fillScreen(BLACK);
        M5.Lcd.setTextColor(WHITE);
        M5.Lcd.setCursor(0, 0);
        M5.Lcd.setTextSize(3);
        M5.Lcd.printf("time start ");
        delay(5000);
        break;

    } 

    M5.update();
}