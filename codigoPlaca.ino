#include <WiFi.h>
#include <WiFiClient.h>
#include <ArduinoJson.h>
#include <HTTPClient.h>
// CONECTAR A REDE DO CELULAR 
const char* ssid = "LocationConnection";
const char* password = "12345678";
const char* nameAp = "AP2";
const char* serverName = "http://181.222.167.71:3000/tcp-data";
WiFiClient client;
void setup() {
  WiFi.mode(WIFI_STA);
  Serial.begin(115200);
  Serial.println("Conectando-se à rede WiFi...");
  // Substitua "NomeDaRede" e "SenhaDaRede" pelas informações da sua rede WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Ainda não conectado...");
  }
  Serial.println("Conectado à rede WiFi!");
  Serial.println(WiFi.RSSI());
}

void loop() {
  // Lê o RSSI (Received Signal Strength Indicator) da rede WiFi atual
  WiFiClient client;
  HTTPClient http;
  StaticJsonDocument<500> doc;
  JsonArray clientArray = doc.createNestedArray("clients");
  JsonObject clientObject = clientArray.createNestedObject();
  clientObject["AP"] = nameAp;
  clientObject["RSSI"] = WiFi.RSSI();
  String jsonString;
  serializeJson(doc, jsonString);
  Serial.println(WiFi.RSSI());
  // Your Domain name with URL path or IP address with path
  http.begin(client, serverName);
  http.addHeader("Content-Type", "application/json");
  int httpResponseCode = http.POST(jsonString);
  Serial.print("HTTP Response code: ");
  Serial.println(httpResponseCode);
  http.end();
  // client.print(jsonString);
  //delay(500);
}