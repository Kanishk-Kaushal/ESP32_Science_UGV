// ANALOG INPUT PIN
int sensor_pin = 36;
int value ;

// COLLABORATIVE FACTORS
int dry_air_val = 4095;
int water_val = 1240;

void setup()
{
  Serial.begin(9600);
  Serial.println("Reading");
  delay(2000);
}

void loop()
{

  value = analogRead(sensor_pin);
  value = map(value, dry_air_val, water_val, 0, 100);

  Serial.print("Moisture : ");
  Serial.print(value);
  Serial.println("%");
  
  delay(1000);
}
