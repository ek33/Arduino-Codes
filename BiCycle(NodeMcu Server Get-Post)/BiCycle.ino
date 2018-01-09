#include <ESP8266WiFi.h>

// WiFi information
const char WIFI_SSID[] = "Vamorte";
const char WIFI_PSK[] = "rilekez5";
 
// Remote site information
const char http_site[] = "furkantokac.com";
const int http_port = 9977;

// Pin definitions
const int LED_PIN = 5; //D1
const int Motora= 0; //D3
const int Motorb= 2; //D4

const int SensorPin = A0;
// Global variables
int weight=15;
WiFiClient client;

void setup() {
  
  // Set up serial console to read web page
  Serial.begin(115200);
  Serial.println();
  Serial.println("BiCycle Recyle Bin");
  
  // Set up LED for debugging
  pinMode(LED_PIN, OUTPUT);
  
  pinMode(Motora, OUTPUT);
  pinMode(Motorb, OUTPUT);
  // Connect to WiFi
  connectWiFi();
}

void loop() {
  while(checkStatus()!=1){  //Loop until opening command is received
    delay(999);
  }
  
  Serial.println("ACIK");
  digitalWrite(Motora, HIGH);
  digitalWrite(Motorb, HIGH);
  
  
  while(checkStatus()!=0){  //Loop until closing command is received
    delay(999);
  }
  Serial.println("KAPALI");
  digitalWrite(Motora, LOW);
  digitalWrite(Motorb, LOW);

  //measure weight here. (For now, random values are assigned)
  if(weight==15||weight==14){
    weight=3+random(2); //3 or 4
  }else if(weight==3||weight==4){
    weight=7+random(2); //7 or 8
  }else if(weight==7||weight==8){
    weight=14+random(2); //14 or 15
  }else{
    weight=4;
  }
  
  if(postData()){
    Serial.println("DATA Has Been Sent Succesfully");
  }
}
 
// Attempt to connect to WiFi
void connectWiFi() {
  
  byte led_status = 0;
  
  // Set WiFi mode to station (client)
  WiFi.mode(WIFI_STA);
  
  // Initiate connection with SSID and PSK
  WiFi.begin(WIFI_SSID, WIFI_PSK);
  
  // Blink LED while we wait for WiFi connection
  while ( WiFi.status() != WL_CONNECTED ) {
    digitalWrite(LED_PIN, led_status);
    led_status ^= 0x01;
    delay(100);
  }
  
  // Turn LED on when we are connected
  digitalWrite(LED_PIN, HIGH);
}
 
// Perform an HTTP GET request to a remote page
bool getPage() {
  
  // Attempt to make a connection to the remote server
  if ( !client.connect(http_site, http_port) ) {
    return false;
  }
  
  // Make an HTTP GET request
  client.println("GET /is_bin_opened?binId=112233445566 HTTP/1.1\r\n");
  client.print("Host: ");
  client.println(http_site);
  client.println("Connection: close");
  client.println();
  
  return true;
}

int checkStatus(){
  if ( !getPage() ) {
    Serial.println("GET request failed");
  }
  while(true){
    // If there are incoming bytes, print them
    if ( client.available() ) {
      char c = client.read();
      Serial.print(c);
      if(c=='*'){       //'*' is the opening command
        return 1;       //return 1 means opening command received 
      }else if(c=='+'){ //'+' is the closing command
        return 0;       //return 0 means closing command received
      }
    }
    
    // If the server has disconnected, stop the client 
    if ( !client.connected() ) {
      Serial.println();
      
      // Close socket 
      client.stop();
      //if ( WiFi.status() != WL_DISCONNECTED ) { WiFi.disconnect();}
      
      // Turn off LED
      digitalWrite(LED_PIN, LOW);
      Serial.print("Close ");
      break;
    }
    
  }
  return 2;   //return 2 means no command received (Hold status)
}

bool postData(){
  String postUrl1= "POST /server_amount?binId=112233445566&amount=";    // Here the posting Url is being prepared
  String postUrl2= " HTTP/1.1\r\n";                                     // normal form of the url is like this:
  postUrl1 += weight;                                                   // "POST /server_amount?binId=112233445566&amount=15 HTTP/1.1\r\n"
  postUrl1 += postUrl2;                                                 // where bin id is 1122233445566 and weight is 15

  if ( !client.connect(http_site, http_port) ) {
    return false;
  }
  
  // Make an HTTP POST
  client.println(postUrl1);
  client.print("Host: ");
  client.println(http_site);
  client.println("Connection: close");
  client.println();
  
  if ( !client.connected() ) {
      Serial.println();
      // Close socket
      client.stop();
  }
  return true;
}

