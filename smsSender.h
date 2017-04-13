
/* Setup shield-specific #include statements */
#include "Arduino.h"
#include <SPI.h>
#include <Client.h>
#include <C:\Program Files (x86)\Arduino\libraries\Adafruit_CC3000_Library-master\Adafruit_CC3000.h>
#include <C:\Program Files (x86)\Arduino\libraries\Adafruit_CC3000_Library-master\Adafruit_CC3000_Server.h>
#include <C:\Program Files (x86)\Arduino\libraries\Adafruit_CC3000_Library-master\ccspi.h>

#include <C:\Program Files (x86)\Arduino\libraries\Temboo\src\Temboo.h>

;;;;;-7fh
#define ADAFRUIT_CC3000_IRQ 3
#define ADAFRUIT_CC3000_VBAT 5
#define ADAFRUIT_CC3000_CS 10
#define TEMBOO_ACCOUNT "abilashini"  // Your Temboo account name 
#define TEMBOO_APP_KEY_NAME "myFirstApp"  // Your Temboo app key name
#define TEMBOO_APP_KEY "db64995d44da40d3bb659572c4d96ce0"  // Your Temboo app key

#define NULL 0

#define WIFI_SSID "Abi"
#define WPA_PASSWORD "abilashini21"
Adafruit_CC3000 cc3k = Adafruit_CC3000(ADAFRUIT_CC3000_CS, ADAFRUIT_CC3000_IRQ, ADAFRUIT_CC3000_VBAT);

Adafruit_CC3000_Client client;

   

class smsSender
{
private:
        int numRuns ;   // Execution count, so this doesn't run forever
        int maxRuns ;  // Maximum number of times the Choreo should be executed
	static smsSender sms = NULL;  // there is no any instances created for the class
	smsSender();

public:
	static smsSender GetInstance();
	void start();
	void sendSMS();
};
//constructor
smsSender::smsSender(){
    numRuns = 1;   
    maxRuns = 10;
}

smsSender smsSender::GetInstance(){
        // if the class do not has an instance, then this method creates an instance
	if (sms == NULL)
	{
		sms = new smsSender();
	}
	return sms;
}

void smsSender::start() {
  
  delay(4000);
  while(!Serial);

  status_t wifiStatus = STATUS_DISCONNECTED;
  while (wifiStatus != STATUS_CONNECTED) {
    Serial.print("WiFi:");
    if (cc3k.begin()) {
      if (cc3k.connectToAP(WIFI_SSID, WPA_PASSWORD, WLAN_SEC_WPA2)) {
        wifiStatus = cc3k.getStatus();
      }
    }
    if (wifiStatus == STATUS_CONNECTED) {
      Serial.println("OK");
    } else {
      Serial.println("FAIL");
    }
    delay(5000);
  }

  cc3k.checkDHCP();
  delay(1000);

  Serial.println("Setup complete.\n");
}

void smsSender::sendSMS() {
  while (numRuns <= maxRuns){
  if (numRuns <= maxRuns) {
    Serial.println("Running SendSMS - Run #" + String(numRuns++));

    TembooChoreo SendSMSChoreo(client);

    // Invoke the Temboo client
    SendSMSChoreo.begin();

    // Set Temboo account credentials
    SendSMSChoreo.setAccountName(TEMBOO_ACCOUNT);
    SendSMSChoreo.setAppKeyName(TEMBOO_APP_KEY_NAME);
    SendSMSChoreo.setAppKey(TEMBOO_APP_KEY);

    // Set Choreo inputs
    String AuthTokenValue = "92883620aba36eabc41a778d404bbb7d";
    SendSMSChoreo.addInput("AuthToken", AuthTokenValue);
    String BodyValue = "I'm working...";
    SendSMSChoreo.addInput("Body", BodyValue);
    String ToValue = "+94719248432";
    SendSMSChoreo.addInput("To", ToValue);
    String AccountSIDValue = "AC12b8871db885171e92bb2662f7a654bc";
    SendSMSChoreo.addInput("AccountSID", AccountSIDValue);
    String FromValue = "+1 909-726-7691";
    SendSMSChoreo.addInput("From", FromValue);

    // Identify the Choreo to run
    SendSMSChoreo.setChoreo("/Library/Twilio/SMSMessages/SendSMS");

    // Run the Choreo; when results are available, print them to serial
    SendSMSChoreo.run();

    while(SendSMSChoreo.available()) {
      char c = SendSMSChoreo.read();
      Serial.print(c);
    }
    SendSMSChoreo.close();
  }

  Serial.println("\nWaiting...\n");
  delay(30000); // wait 30 seconds between SendSMS calls
  }
}
