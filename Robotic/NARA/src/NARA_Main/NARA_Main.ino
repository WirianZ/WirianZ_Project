/* * NARA: The Revived Robot 
 * Fixed: Corrected Frame usage (no buf/len members in esp32cam::Frame), 
 * back to writeTo() method, added more logging.
 */
#include <WiFi.h>
#include <WebServer.h>

// --- KONFIGURASI WI-FI ---
const char* SSID = "RAMA";
const char* PASS = "12341234";

//--VARIABELS--

//Ultra sonic sensor---
const int trigPin = 18;
const int echoPin = 19;
long duration;
int olddata = 0;
int newdata = 0;
//---------------------

void setup() {
  Serial.begin(115200);
  Serial.println("\nMemulai NARA...");

  // 2. Koneksi Wi-Fi
  WiFi.mode(WIFI_STA);
  WiFi.begin(SSID, PASS);
  Serial.print("Menghubungkan ke Wi-Fi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("\n✅ Wi-Fi Terhubung!");
  Serial.print("📍 Akses NARA di: http://");
  Serial.println(WiFi.localIP());

//--Ultrasonic sensor---
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
//----------------------
}
void loop() {
  check_growht();
}

void check_growht(){
    newdata = olddata;

  // 2. Trigger the Ultrasonic Sensor
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // 3. Calculate current distance and store it in newdata
  duration = pulseIn(echoPin, HIGH);
  newdata = duration * 0.0343 / 2;
  
  // 4. Print results
  Serial.print("Previous: ");
  Serial.print(olddata);
  Serial.print(" cm | Current: ");
  Serial.print(newdata);
  Serial.println(" cm");

  // 5. Logic: If current distance (newdata) is GREATER than previous (olddata)
  // Note: Only run this if olddata isn't 0 (to avoid "Grow" on the very first start)
  if (newdata > olddata && olddata != 0){
    int difference = newdata - olddata;
    Serial.print("--- Distance Grew by: ");
    Serial.print(difference);
    Serial.println(" cm ---");
  }
  
}
