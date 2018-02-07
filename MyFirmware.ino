
#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h> no use

/* Set these to your desired credentials. */
const char *ssid = "ESPap";
const char *password = "thereisnospoon";

/* Set your led light. */
const short int BUILTIN_LED1 = 2; //GPIO2

const char* host;
const int httpPort = 80;
const int httpsPort = 443;

ESP8266WebServer server(80); no use

// Use web browser to view and copy
// SHA1 fingerprint of the certificate
const char* fingerprint = "CF 05 98 89 CA FF 8E D8 5E 5C E0 C2 E4 F7 E6 C3 C7 50 DD 5C";

/* Just a little test message.  Go to http://192.168.4.1 in a web browser
 * connected to this access point to see it.
 */
void handleRoot() {
	server.send(200, "text/html", "<h1>You are connected</h1>");
}

void handleRequest() {
  String request = "{\"unlocked\":";
  request += true;
  request += "}";
}

void setup() {
  pinMode(BUILTIN_LED1, OUTPUT);    // Initialize the LED_BUILTIN pin as an output
	delay(1000);
  
	Serial.begin(9600);   // Enable Serial 115200
	Serial.println();
 
  WiFi.mode(WIFI_AP);   // Only Access point
  delay(100);

  uint8_t mac[WL_MAC_ADDR_LENGTH];
  WiFi.softAPmacAddress(mac);
  
	Serial.println("Configuring access point...");
	/* You can remove the password parameter if you want the AP to be open. */
	WiFi.softAP(ssid, password, 6, false);
  
  Serial.print("Connecting to ");
  Serial.println(ssid);

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);

  Serial.print("MAC: ");
  Serial.println(WiFi.softAPmacAddress());

  server.on("/", HTTP_POST, handleRoot);
  
  // Start the server
  server.begin();
  Serial.println("HTTP server started");
}

// the loop function runs over and over again forever
void loop() {
  // TODO: Loop to edit
  int station_num = WiFi.softAPgetStationNum();

  if (station_num > 0) {
    digitalWrite(LED_BUILTIN, LOW);   // Turn the LED on
    delay(1000);                      // Wait for a second
    digitalWrite(LED_BUILTIN, HIGH);  // Turn the LED off by making the voltage HIGH
    delay(1000);                      // Wait for two seconds (to demonstrate the active low LED)
  } else {
    digitalWrite(LED_BUILTIN, LOW);   // Turn the LED on
  }
  
	server.handleClient();
}
