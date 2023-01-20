
/* Comment this out to disable prints and save space */
#define BLYNK_PRINT DebugSerial
#define BLYNK_TEMPLATE_ID "TMPLqQEh9NXn"
#define BLYNK_DEVICE_NAME "MESIIIIII"
#define BLYNK_AUTH_TOKEN "rI8LcL0Fnfuri3nrRyRr9y_8qBIRzxIS"
/* Fill-in your Template ID (only if using Blynk.Cloud) */
#define BLYNK_TEMPLATE_ID   "TMPLqQEh9NXn"


// You could use a spare Hardware Serial on boards that have it (like Mega)
#include <SoftwareSerial.h>
SoftwareSerial DebugSerial(2, 3); // RX, TX

#include <BlynkSimpleStream.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "rI8LcL0Fnfuri3nrRyRr9y_8qBIRzxIS";


void setup()
{
  // Debug console
  DebugSerial.begin(9600);

  // Blynk will work through Serial
  // Do not read or write this serial manually in your sketch
  Serial.begin(9600);
  Blynk.begin(Serial, auth);
}

void loop()
{
  Blynk.run();
}
