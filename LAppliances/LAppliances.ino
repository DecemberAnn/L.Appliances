#include <LWiFi.h>

const char* ssid     = "網路名稱";   
const char* pass     = "網路密碼"; 

WiFiClient client;

const int buttonPin = 6;  
const int ledPin =  7;  
int buttonState = 0; 

const char* server = "maker.ifttt.com"; 
const char* resource = 
            "/trigger/Lining!/with/key/b3osAnTyR4OvgnHDhXwWBB?value1=p_vuaH4HrKacoPSHaemMtf11GgBdapvYW6C14Ff4I7o";

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);
  Serial.begin(115200);
  Serial.print("Attempting to connect to SSID: ");
  Serial.println(ssid);
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);
  Serial.println();
}

void loop() {
  buttonState = digitalRead(buttonPin);
  if (buttonState == HIGH) {
    // Read Appliances information
    digitalWrite(ledPin, HIGH);
    int light = analogRead(A0);
    
    // connect to server  
    Serial.println("Starting connection to server...");
    while(!client.connect(server, 80)){
      // wait for connecting server...
    }
  
    //Send GET request to IFTTT server
    client.print("GET https://");
    client.print(server);
    client.print(resource);
    client.println(light);
    delay(1000);
    client.stop();
  } else {
    digitalWrite(ledPin, LOW);
  }
}


