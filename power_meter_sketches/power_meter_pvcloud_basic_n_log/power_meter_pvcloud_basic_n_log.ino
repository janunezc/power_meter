// EmonLibrary examples openenergymonitor.org, Licence GNU GPL V3

#include "EmonLib.h"                   // Include Emon Library
#include "pvcloud_lib.h"

EnergyMonitor emon1;                   // Create an instance
EnergyMonitor emon2;
PVCloud pvCloud;

void setup()
{ 
  delay(2000);
  pvCloud.LogEntry("setup() begin...");
  Serial.begin(9600);
  Serial1.begin(115200);

  pinMode(13, OUTPUT);
  blinkSignal();
  
  
  analogReadResolution(ADC_BITS);
  emon1.current(1, 42.55);             // Current: input pin, calibration.
  emon2.current(2, 42.55);
  //42.55 if CT = 60A
  //20 if CT = 30A

  digitalWrite(13,HIGH);
  pvCloud.SendString("SKETCH","SETUP COMPLETE!");
  digitalWrite(13,LOW);
  
  pvCloud.LogEntry("setup() end");
}

void loop()
{
  pvCloud.LogEntry("loop begin()"); 
    
  pvCloud.LogEntry("reading emon1...");
  double Irms1 = emon1.calcIrms(500);  // Calculate Irms only
  pvCloud.LogEntry("reading emon2...");
  double Irms2 = emon2.calcIrms(500);
  double Dato1;
  double Dato2;
    

  if (Irms1 > 0.03){
    pvCloud.LogEntry("Calculating Dato1 on Irms1 > 0.03");
    Dato1 = Irms1*110.0;
    Serial.print("Apparent power 1: ");
    Serial.println(Dato1);         // Apparent power
    // if bluetooth then sent
    Serial1.print("Apparent power 1: ");
    Serial1.println(Dato1);
    pvCloud.LogEntry(Dato1);
    pvCloud.LogEntry("Sending Dato1 to pvCloud...");

    digitalWrite(13,HIGH);
    pvCloud.SendFloat("POWER_METER_1",Dato1);
    digitalWrite(13,LOW);
    
    Serial.print("     Irms1: ");
    Serial.println(Irms1);           // Irms
    // if bluetooth then sent
    Serial1.print("    Irms1: ");
    Serial1.println(Irms1);
    
  }
  else{
    pvCloud.LogEntry("Calculating Dato1 on Irms <= 0.03");
    Dato1 = 0;
    Serial.print("Apparent power 1: ");
    Serial.println(Dato1);         // Apparent power
    // if bluetooth then sent
    Serial1.print("Apparent power 1: ");
    Serial1.println(Dato1);
    pvCloud.LogEntry(Dato1);
    pvCloud.LogEntry("Sending Dato1 to pvCloud");

    digitalWrite(13,HIGH);
    pvCloud.SendFloat("POWER_METER_1",Dato1);
    digitalWrite(13,LOW);
    
    Serial.print("     Irms1: ");
    Serial.println(Irms1);           // Irms
    // if bluetooth then sent 
    Serial1.print("     Irms1: ");
    Serial1.println(Irms1);
  }

if (Irms2 > 0.09){
    pvCloud.LogEntry("Calculating Dato2 on Irms2 > 0.09");
    Dato2 = Irms2*110.0;
    Serial.print("Apparent power 2: ");
    Serial.println(Dato2);         // Apparent power
    // if bluetooth then sent
    Serial1.print("Apparent power 2: ");
    Serial1.println(Dato2);
    
    pvCloud.LogEntry(Dato2);
    pvCloud.LogEntry("Sending Dato2 to pvCloud...");

    digitalWrite(13,HIGH);
    pvCloud.SendFloat("POWER_METER_2",Dato2);
    digitalWrite(13,LOW);
    
    Serial.print("     Irms2: ");
    Serial.println(Irms2);           // Irms
    // if bluetooth then sent
    Serial1.print("    Irms2: ");
    Serial1.println(Irms2);

  }
  else{
    pvCloud.LogEntry("Calculating Dato2 on Irms <= 0.09");
    Dato2 = 0;
    Serial.print("Apparent power 2: ");
    Serial.println(Dato2);         // Apparent power
    // if bluetooth then sent
    Serial1.print("Apparent power 2: ");
    Serial1.println(Dato2);
    pvCloud.LogEntry(Dato2);
    pvCloud.LogEntry("Sending Dato2 to pvCloud...");

    digitalWrite(13,HIGH);
    pvCloud.SendFloat("POWER_METER_2",Dato2);
    digitalWrite(13,LOW);
    
    Serial.print("     Irms2: ");
    Serial.println(Irms2);           // Irms
    // if bluetooth then sent 
    Serial1.print("     Irms2: ");
    Serial1.println(Irms2);

  }
  pvCloud.LogEntry("loop() end");
}

void blinkSignal(){
  Serial.println("BLINK SIGNAL INITIATED");
  for(int i=0; i<12; i++){
    Serial.println("BLINK SIGNAL");
    digitalWrite(13,HIGH);
    delay(200);
    digitalWrite(13,LOW);
    delay(200);
  }
  Serial.println("BLINK SIGNAL COMPLETE");
}

