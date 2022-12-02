#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiAP.h>
#include <WebServer.h>
#include <ESPmDNS.h>

#define blue_LED 10
#define yellow_LED 8
#define red_LED 15

const char* ssid = "ESPWagner";
const char* password = "12345678";

int isOn = 0;
int begin = 0;

WebServer server(80);

void setup() {
  pinMode(blue_LED, OUTPUT);
  pinMode(yellow_LED, OUTPUT);
  pinMode(red_LED, OUTPUT);

  Serial.begin(115200);

  WiFi.softAP(ssid, password);
  IPAddress myIP = WiFi.softAPIP();

  Serial.print("SSID: ");
  Serial.println(ssid);
  Serial.print("AP IP Address: ");
  Serial.println(myIP);

  server.begin();

  Serial.println("Servidor iniciado!");

  if (MDNS.begin("esp32")) {
    Serial.println("MDNS responder started");
  }

  server.on("/", handleRoot);
  server.on("/blueOn", handleBlueOn);
  server.on("/yellowOn", handleYellowOn);
  server.on("/redOn", handleRedOn);
  server.on("/off", handleOff);

  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");
}

void handleRoot() {
  String html = "";
  html += "<style>html{text-align: center; padding: 15px} #yellow{background-color: yellow;} #red{background-color: red} #blue{background-color: blue} #white{background-color: #d4d4d4; color: black} a {padding: 10px; font-size: 40px; text-decoration: none; color: white; border-radius: 15px; margin: 10px; transition:200ms} a:hover{opacity: 0.7} .middleBtns{justify-content: center; display: flex; flex-direction: row}</style>";
  html += "<meta charset='UTF-8'>";
  html += "<a id=\"blue\" href=\"/blueOn\">Começar!</a><br><br><br>";
  html += "<div class=\"middleBtns\"> <a id=\"yellow\" href=\"/yellowOn\">Player 1</a><br><br><br>";
  html += "<a id=\"red\" href=\"/redOn\">Player 2</a> </div> <br><br><br>";
  html += "<a id=\"white\" href=\"/off\">Reiniciar</a>";
  server.send(200, "text/html", html);
}

void handleBlueOn() {
  digitalWrite(red_LED, 1);
  delay(1000);
  digitalWrite(red_LED, 0);
  begin++;
  handleRoot();
}

void handleRedOn() {
  if (isOn == 0 && begin == 1) {
    isOn++;
    digitalWrite(blue_LED, 1);
  }
  handleRoot();
}

void handleYellowOn() {
  if (isOn == 0 && begin == 1) {
    isOn++;
    digitalWrite(yellow_LED, 1);
  }
  handleRoot();
}

void handleOff() {
  isOn = 0;
  begin = 0;
  digitalWrite(blue_LED, 0);
  digitalWrite(yellow_LED, 0);
  handleRoot();
}

void handleNotFound() {
  digitalWrite(blue_LED, 1);
  digitalWrite(yellow_LED, 1);
  digitalWrite(red_LED, 1);
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message = +" " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
  digitalWrite(blue_LED, 0);
  digitalWrite(yellow_LED, 0);
  digitalWrite(red_LED, 0);
}



void loop(void) {
  server.handleClient();
  delay(2);
}