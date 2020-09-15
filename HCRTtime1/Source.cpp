
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
int sec = 0, m = 0, h = 0;
unsigned long startMillis;
unsigned long currentMillis;
const unsigned long period = 1000;
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

    startMillis = millis();
}


void loop() {
    timee();
    starttime();
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
void starttime() {
    for (; M5.BtnA.wasPressed();) {
        M5.Lcd.clear();
        delay(500);
        for (; M5.BtnA.wasPressed();) {

            M5.Lcd.setCursor(0, 0);
            M5.Lcd.setTextSize(3);
            M5.Lcd.println("time start \n");
            M5.Lcd.print(h);
            M5.Lcd.print(" : ");
            M5.Lcd.print(m);
            M5.Lcd.print(" : ");
            M5.Lcd.print(sec);
            currentMillis = millis();
            if (currentMillis - startMillis >= 1000)
            {

                // Function here
                startMillis = currentMillis;
                M5.Lcd.fillRect(161, 47, 24, 22, BLACK);
                M5.Lcd.fillRect(135, 47, 24, 22, BLACK);
                sec++;
                if (sec >= 60) {
                    M5.Lcd.fillRect(70, 47, 24, 22, BLACK);
                    M5.Lcd.fillRect(45, 47, 24, 22, BLACK);
                    m++;
                    sec = 0;
                }

                if (m >= 60) {
                    M5.Lcd.fillRect(0, 47, 20, 23, BLACK);
                    M5.Lcd.fillRect(19, 47, 20, 23, BLACK);
                    h++;
                    m = 0;
                }
                if (h >= 24) {
                    h = 0;
                }
                M5.Lcd.setCursor(0, 0);
                M5.Lcd.setTextSize(3);
                M5.Lcd.println("time start \n");
                M5.Lcd.print(h);
                M5.Lcd.print(" : ");
                M5.Lcd.print(m);
                M5.Lcd.print(" : ");
                M5.Lcd.print(sec);

            }
        }
    }
    M5.update();

}


void timee() {

    currentMillis = millis();
    if (currentMillis - startMillis >= period)
    {

        // Function here
        startMillis = currentMillis;
        configTime(timezone2, dst, "pool.ntp.org", "time.nist.gov");
        time_t now = time(nullptr);
        struct tm* p_tm = localtime(&now);

        //s1
        M5.Lcd.fillRect(121, 0, 22, 21, BLACK);
        M5.Lcd.fillRect(101, 0, 22, 22, BLACK);
        //m1
        M5.Lcd.fillRect(70, 0, 22, 21, BLACK);
        M5.Lcd.fillRect(51, 0, 22, 22, BLACK);
        //h1
        M5.Lcd.fillRect(20, 0, 22, 21, BLACK);
        M5.Lcd.fillRect(1, 0, 22, 22, BLACK);

        //s2
        M5.Lcd.fillRect(121, 80, 22, 21, BLACK);
        M5.Lcd.fillRect(101, 80, 22, 22, BLACK);
        //m1
        M5.Lcd.fillRect(70, 80, 22, 21, BLACK);
        M5.Lcd.fillRect(51, 80, 22, 22, BLACK);
        //h1
        M5.Lcd.fillRect(20, 80, 22, 21, BLACK);
        M5.Lcd.fillRect(1, 80, 22, 22, BLACK);

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


    }

}
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
int sec = 0, m = 0, h = 0;
unsigned long startMillis;
unsigned long currentMillis;
const unsigned long period = 1000;
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

    startMillis = millis();
}


void loop() {
    timee();
    starttime();
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
void starttime() {
    for (; M5.BtnA.wasPressed();) {
        M5.Lcd.clear();
        delay(500);
        for (; M5.BtnA.wasPressed();) {

            M5.Lcd.setCursor(0, 0);
            M5.Lcd.setTextSize(3);
            M5.Lcd.println("time start \n");
            M5.Lcd.print(h);
            M5.Lcd.print(" : ");
            M5.Lcd.print(m);
            M5.Lcd.print(" : ");
            M5.Lcd.print(sec);
            currentMillis = millis();
            if (currentMillis - startMillis >= 1000)
            {

                // Function here
                startMillis = currentMillis;
                M5.Lcd.fillRect(161, 47, 24, 22, BLACK);
                M5.Lcd.fillRect(135, 47, 24, 22, BLACK);
                sec++;
                if (sec >= 60) {
                    M5.Lcd.fillRect(70, 47, 24, 22, BLACK);
                    M5.Lcd.fillRect(45, 47, 24, 22, BLACK);
                    m++;
                    sec = 0;
                }

                if (m >= 60) {
                    M5.Lcd.fillRect(0, 47, 20, 23, BLACK);
                    M5.Lcd.fillRect(19, 47, 20, 23, BLACK);
                    h++;
                    m = 0;
                }
                if (h >= 24) {
                    h = 0;
                }
                M5.Lcd.setCursor(0, 0);
                M5.Lcd.setTextSize(3);
                M5.Lcd.println("time start \n");
                M5.Lcd.print(h);
                M5.Lcd.print(" : ");
                M5.Lcd.print(m);
                M5.Lcd.print(" : ");
                M5.Lcd.print(sec);

            }
        }
    }
    M5.update();

}


void timee() {

    currentMillis = millis();
    if (currentMillis - startMillis >= period)
    {

        // Function here
        startMillis = currentMillis;
        configTime(timezone2, dst, "pool.ntp.org", "time.nist.gov");
        time_t now = time(nullptr);
        struct tm* p_tm = localtime(&now);

        //s1
        M5.Lcd.fillRect(121, 0, 22, 21, BLACK);
        M5.Lcd.fillRect(101, 0, 22, 22, BLACK);
        //m1
        M5.Lcd.fillRect(70, 0, 22, 21, BLACK);
        M5.Lcd.fillRect(51, 0, 22, 22, BLACK);
        //h1
        M5.Lcd.fillRect(20, 0, 22, 21, BLACK);
        M5.Lcd.fillRect(1, 0, 22, 22, BLACK);

        //s2
        M5.Lcd.fillRect(121, 80, 22, 21, BLACK);
        M5.Lcd.fillRect(101, 80, 22, 22, BLACK);
        //m1
        M5.Lcd.fillRect(70, 80, 22, 21, BLACK);
        M5.Lcd.fillRect(51, 80, 22, 22, BLACK);
        //h1
        M5.Lcd.fillRect(20, 80, 22, 21, BLACK);
        M5.Lcd.fillRect(1, 80, 22, 22, BLACK);

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


    }

}