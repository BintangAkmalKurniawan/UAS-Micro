#include <WiFi.h>
#include <HTTPClient.h>

// 1. Pengaturan Jaringan WiFi & n8n
const char* ssid = "Naon";         
const char* password = "kelapoho"; 
const char* n8n_webhook_url = "https://n8n.dedigi.id/webhook/coba-gemini"; 

// 2. Mendefinisikan pin
const int sensorPin = 34; 
const int buzzerPin = 4;  
const int relayPin = 5;   
const int ledPin = 13;     

const int batasAir = 1000;
bool statusBahaya = false; 

void setup() {
  Serial.begin(115200);           
  pinMode(buzzerPin, OUTPUT);     
  pinMode(relayPin, OUTPUT);      
  pinMode(ledPin, OUTPUT);        

  digitalWrite(relayPin, HIGH);   
  digitalWrite(ledPin, LOW);      // LED OFF

  // Memulai koneksi WiFi
  WiFi.begin(ssid, password);
  Serial.print("Menghubungkan ke WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi Terhubung! IP: " + WiFi.localIP().toString());
}

void loop() {
  int nilaiSensor = analogRead(sensorPin); 
  Serial.print("Tingkat Air: ");
  Serial.println(nilaiSensor);             

  if (nilaiSensor > batasAir) {
    // KONDISI BAHAYA
    digitalWrite(buzzerPin, HIGH); 
    digitalWrite(relayPin, LOW);   // Relay ON
    digitalWrite(ledPin, HIGH);    // LED ON
    
    if (!statusBahaya) {
      Serial.println("STATUS: AWAS, AIR NAIK! Mengirim data ke n8n...");
      kirimDataKeN8n(nilaiSensor);
      statusBahaya = true; 
    }
  } else {
    // KONDISI AMAN
    digitalWrite(buzzerPin, LOW);  
    digitalWrite(relayPin, HIGH);  // Relay OFF
    digitalWrite(ledPin, LOW);     // LED OFF
    
    if (statusBahaya) {
      Serial.println("STATUS: Air sudah surut.");
      statusBahaya = false; 
    }
  }
  delay(500); 
}

void kirimDataKeN8n(int tinggiAir) {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(n8n_webhook_url);
    http.addHeader("Content-Type", "application/json");

    String jsonPayload = "{\"Tinggi_air\":" + String(tinggiAir) + "}";
    int httpResponseCode = http.POST(jsonPayload);

    if (httpResponseCode > 0) {
      Serial.println("HTTP Response: " + String(httpResponseCode));
    } else {
      Serial.println("Gagal kirim, Error: " + http.errorToString(httpResponseCode));
    }
    http.end(); 
  } else {
    Serial.println("WiFi terputus, tidak bisa kirim data.");
  }
}