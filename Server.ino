

#include <Adafruit_CC3000.h>
#include <SPI.h>
#include "utility/debug.h"
#include "utility/socket.h"

// These are the interrupt and control pins
#define ADAFRUIT_CC3000_IRQ   7  // MUST be an interrupt pin!
// These can be any two pins
#define ADAFRUIT_CC3000_VBAT  5
#define ADAFRUIT_CC3000_CS    10
// Use hardware SPI for the remaining pins
// On an UNO, SCK = 13, MISO = 12, and MOSI = 11
Adafruit_CC3000 cc3000 = Adafruit_CC3000(ADAFRUIT_CC3000_CS, ADAFRUIT_CC3000_IRQ, ADAFRUIT_CC3000_VBAT,
                                         SPI_CLOCK_DIVIDER); // you can change this clock speed

#define WLAN_SSID       "PangaeaW"           // cannot be longer than 32 characters!
#define WLAN_PASS       "pangaeawifi"
// Security can be WLAN_SEC_UNSEC, WLAN_SEC_WEP, WLAN_SEC_WPA or WLAN_SEC_WPA2
#define WLAN_SECURITY   WLAN_SEC_WPA2

#define LISTEN_PORT           6000    // What TCP port to listen on for connections.  The echo protocol uses port 7.

Adafruit_CC3000_Server echoServer(LISTEN_PORT);

//add 8 ports key
boolean running1 = false;
boolean running2 = false;
boolean running3 = false;
boolean running4 = false;
boolean running5 = false;
boolean running6 = false;
boolean running7 = false;
int key0=13;
int key1=12;
int key2=11;
int key3=9;
int key4=8;
int key5=6;
int key6=4;
int key7=3;

void setup(void)
{

  pinMode(key0,OUTPUT);
  pinMode(key1,OUTPUT);
  pinMode(key2,OUTPUT);
  pinMode(key3,OUTPUT);
  pinMode(key4,OUTPUT);
  pinMode(key5,OUTPUT);
  pinMode(key6,OUTPUT);
  pinMode(key7,OUTPUT);
  
  Serial.begin(115200);
  Serial.println(F("Hello, CC3000!\n")); 

  Serial.print("Free RAM: "); Serial.println(getFreeRam(), DEC);
  
  /* Initialise the module */
  Serial.println(F("\nInitializing..."));
  if (!cc3000.begin())
  {
    Serial.println(F("Couldn't begin()! Check your wiring?"));
    while(1);
  }
  
  Serial.print(F("\nAttempting to connect to ")); Serial.println(WLAN_SSID);
  if (!cc3000.connectToAP(WLAN_SSID, WLAN_PASS, WLAN_SECURITY)) {
    Serial.println(F("Failed!"));
    while(1);
  }
   
  Serial.println(F("Connected!"));
  
  Serial.println(F("Request DHCP"));
  while (!cc3000.checkDHCP())
  {
    delay(100); // ToDo: Insert a DHCP timeout!
  }  

  /* Display the IP address DNS, Gateway, etc. */  
  while (! displayConnectionDetails()) {
    delay(1000);
  }

  // Start listening for connections
  echoServer.begin();
  
  Serial.println(F("Listening for connections..."));
}

void loop(void)
{

    int num;
  // Try to get a client which is connected.
  Adafruit_CC3000_ClientRef client = echoServer.available();
  if (client) {
     // Check if there is data available to read.
     if (client.available() > 0) {
       // Read a byte and print it.
       char ch = client.read();
       Serial.println(ch);
       switch(ch){
        case 49:
        running1=!running1;
        digitalWrite(key0,running1);
        break;
        case 50:
        running2=!running2;
        digitalWrite(key1,running2);
        break;
        case 51:
        running3=!running3;
        digitalWrite(key2,running3);
        break;
        case 52:
        running4=!running4;
        digitalWrite(key3,running4);
        break;
        case 53:
        running5=!running5;
        digitalWrite(key4,running5);
        break;
        case 54:
        running6=!running6;
        digitalWrite(key5,running6);
        break;
        case 55:
        running7=!running7;
        digitalWrite(key6,running7);
        break;
        case 56:
        num=rand()%4+2;
        digitalWrite(key7,HIGH);
        delay(num*1000);
        digitalWrite(key7,LOW);
        break;
        default:
         ;
        }
     }
  }
}

/**************************************************************************/
/*!
    @brief  Tries to read the IP address and other connection details
*/
/**************************************************************************/
bool displayConnectionDetails(void)
{
  uint32_t ipAddress, netmask, gateway, dhcpserv, dnsserv;
  
  if(!cc3000.getIPAddress(&ipAddress, &netmask, &gateway, &dhcpserv, &dnsserv))
  {
    Serial.println(F("Unable to retrieve the IP Address!\r\n"));
    return false;
  }
  else
  {
    Serial.print(F("\nIP Addr: ")); cc3000.printIPdotsRev(ipAddress);
    Serial.print(F("\nNetmask: ")); cc3000.printIPdotsRev(netmask);
    Serial.print(F("\nGateway: ")); cc3000.printIPdotsRev(gateway);
    Serial.print(F("\nDHCPsrv: ")); cc3000.printIPdotsRev(dhcpserv);
    Serial.print(F("\nDNSserv: ")); cc3000.printIPdotsRev(dnsserv);
    Serial.println();
    return true;
  }
}
