/* 
Date  : 07/08/2020
Author: DungTT
To control peripheral/energy consumption/sleep mode/clock speed.
This project is just considered about stable of device!
Including: 

 */
 
/*  
The difference between dual-core and single-core? Well, a regular ESP32 will consume between 27-44mA when running at 160MHz 
while the single-core consumes about 30% less, coming in at 27mA-34mA. 
Reducing the default clock speed from 160MHz to 80MHz can drop the energy consumption another 20%!
setCpuFrequencyMhz(80);

Tip 1: Use the right battery & board
Tip 2: Use the right battery
Tip 3: Pick the right ESP32 board (single-core)
Tip 4: Reduce the clock speed
Tip 5: Turn off everything in deep sleep
Tip 6: Add a WiFi connection timeout
Tip 7: Use RTC memory to reduce WiFi connections
Tip 8: Use static IP & avoid hostnames
*/
#define _DEBUG_ 1

#include "Board_handle.h"

/*
@date : 07/08/2020
@brief: throw ESP32 to deepsleep mode including: turn off Wifi/ADC/Bluetooth
@para :
@return: none
 */

void goToDeepSleep(int interval)
{
    #if _DEBUG_
    Serial.println("Going to sleep...");
    Serial.print("Wake up after ");
    Serial.print(interval);
    Serial.println(" minutes.");
    #endif
    
    WiFi.disconnect(true);
    WiFi.mode(WIFI_OFF);
    btStop();

    // adc_power_off();//keep pin 35 awake for capacity measurement
    esp_wifi_stop();
    esp_bt_controller_disable();

    // Configure the timer to wake us up!
    esp_sleep_enable_timer_wakeup((int)(interval * BASE_TIME_MINUTE * BASE_TIME_US));

    // Go to sleep! Zzzz
    esp_deep_sleep_start();
}

/*
@date : 14/08/2020
@brief: from link https://github.com/Xinyuan-LilyGO/LilyGo-T-Call-SIM800/issues/29
@para :
@return: measure & display battery
 */

int get_Batery_Value() {
    int sample_count = 0;
    int sum = 0;
   
    while (sample_count < NUM_SAMPLES) {
        sum += analogRead(BATTERY_METTER_PIN);
        // Serial.println(sum);
        sample_count++;
        delay(10);
    }

    float voltage = (sum/NUM_SAMPLES)/ 2350.0;
    int batteryLevel = _min(map(sum / NUM_SAMPLES, 2000, 2440, 0, 100), 100); //1100
    if (sum/NUM_SAMPLES < 1200) batteryLevel = 0;
    /* Serial.print("Valor Analogo: ");
    Serial.println(sum);
    Serial.print("Battery Lavel:");
    Serial.print(batteryLevel);
    Serial.println("%"); */
    sample_count = 0; //Reset counter
    sum = 0; //Reset counter
    voltage = voltage * 4.20;
    /* Serial.print(voltage);
    Serial.println (" V"); */
    //batteryLevel *= 100;
    //batteryLevel = (int)(batteryLevel);
    //display.setFont(&Tiny3x3a2pt7b);    
    return batteryLevel;
}

// /*
// @date : 14/08/2020
// @brief: get MAC & convert to string
// @para :
// @return: MAC ID
//  */
// String getMacAddress() {
//     byte mac[6];
//     WiFi.macAddress(mac);
//     String cMac = "";
//     for (int i = 0; i < 6; ++i) {
//         if (mac[i] < 0x10) {
//         cMac += "0";
//         }
//         cMac += String(mac[i], HEX);
//         if (i < 5)
//         cMac += ":"; // put : or - if you want byte delimiters
//     }
//     cMac.toUpperCase();
//     return cMac;
// }