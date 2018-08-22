
void  finger_setup()
{
  Serial.begin(9600);
  while (!Serial);
  Serial.println("\n\nAdafruit finger detect test");

  // set the data rate for the sensor serial port
  finger.begin(57600);
  
  if (finger.verifyPassword()) {
    Serial.println("Found fingerprint sensor!");
  } else {
    Serial.println("Did not find fingerprint sensor :(");
    while (1) { delay(1); }
  }

  finger.getTemplateCount();
  Serial.print("Sensor contains "); Serial.print(finger.templateCount); Serial.println(" templates");
  Serial.println("Waiting for valid finger..."); 
}



int getFingerprintIDez() {
  
  uint8_t p = finger.getImage();
  if (p != FINGERPRINT_OK) return -1;


  p = finger.image2Tz();
  if (p != FINGERPRINT_OK) return -1;


  p = finger.fingerFastSearch();
  if (p != FINGERPRINT_OK)
  {
    if (p == FINGERPRINT_NOTFOUND)
    {
      Serial.println("not found");
      count ++;
      if(count == 3)
      {
        tone(bu,2000,1000);
        count = 0;
        Serial.println("buzzer");
      }
    }
    return -1;
  }

  
  // found a match!
  Serial.print("Found ID #"); Serial.print(finger.fingerID); 
  Serial.print(" with confidence of "); Serial.println(finger.confidence);
  if(finger.confidence>threshold)
  {
    motor_run(1,50);
    delay(1000);
    motor_stop();
    
  }
  return finger.fingerID; 
   
}


