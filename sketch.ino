#include <DHT.h>

#define DHTPIN 2
#define DHTTYPE DHT22
#define SOIL_PIN A0

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  dht.begin();
  Serial.println("Smart Agriculture Node Started");
}

void loop() {
  float temp = dht.readTemperature();
  float hum = dht.readHumidity();

  int soilRaw = analogRead(SOIL_PIN);
  int soilPercent = map(soilRaw, 0, 1023, 0, 100);

  if (isnan(temp) || isnan(hum)) {
    Serial.println("DHT22 read failed!");
    delay(2000);
    return;
  }

  Serial.print("T:");
  Serial.print(temp, 1);
  Serial.print(",H:");
  Serial.print(hum, 1);
  Serial.print(",S:");
  Serial.println(soilPercent);

  if (soilPercent < 30) {
    Serial.println(">> ALERT: Soil dry, irrigation needed!");
  }

  delay(2000);
}
