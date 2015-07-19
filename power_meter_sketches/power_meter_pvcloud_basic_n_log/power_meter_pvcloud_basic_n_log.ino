// EmonLibrary examples openenergymonitor.org, Licence GNU GPL V3

#include "EmonLib.h"                   // Include Emon Library

EnergyMonitor emon1;                   // Create an instance
EnergyMonitor emon2;
void setup()
{  
  log("setup() begin...");
  Serial.begin(9600);
  Serial1.begin(115200);
  analogReadResolution(ADC_BITS);
  emon1.current(1, 42.55);             // Current: input pin, calibration.
  emon2.current(2, 42.55);
  //42.55 if CT = 60A
  //20 if CT = 30A
  
  pvCloud_Send_String("SKETCH","SETUP COMPLETE!");
  log("setup() end");
}

void loop()
{
  log("loop begin()"); 
  
  log("reading emon1...");
  double Irms1 = emon1.calcIrms(500);  // Calculate Irms only
  log("reading emon2...");
  double Irms2 = emon2.calcIrms(500);
  double Dato1;
  double Dato2;
    

  if (Irms1 > 0.09){
    log("Calculating Dato1 on Irms1 > 0.09");
    Dato1 = Irms1*110.0;
    Serial.print("Apparent power 1: ");
    Serial.print(Dato1);         // Apparent power
    // if bluetooth then sent
    Serial1.print("Apparent power 1: ");
    Serial1.print(Dato1);
    log(Dato1);
    log("Sending Dato1 to pvCloud...");
    pvCloud_Send_Float("POWER_METER_1",Dato1);
    
    Serial.print("     Irms1: ");
    Serial.println(Irms1);           // Irms
    // if bluetooth then sent
    Serial1.print("    Irms1: ");
    Serial1.println(Irms1);
    
  }
  else{
    log("Calculating Dato1 on Irms <= 0.09");
    Dato1 = 0;
    Serial.print("Apparent power 1: ");
    Serial.print(Dato1);         // Apparent power
    // if bluetooth then sent
    Serial1.print("Apparent power 1: ");
    Serial1.print(Dato1);
    log(Dato1);
    log("Sending Dato1 to pvCloud");
    pvCloud_Send_Float("POWER_METER_1",Dato1);
    Serial.print("     Irms1: ");
    Serial.println(Irms1);           // Irms
    // if bluetooth then sent 
    Serial1.print("     Irms1: ");
    Serial1.println(Irms1);
  }

if (Irms2 > 0.09){
  log("Calculating Dato2 on Irms2 > 0.09");
    Dato2 = Irms2*110.0;
    Serial.print("Apparent power 2: ");
    Serial.print(Dato2);         // Apparent power
    // if bluetooth then sent
    Serial1.print("Apparent power 2: ");
    Serial1.print(Dato2);
    
    log(Dato2);
    log("Sending Dato2 to pvCloud...");
    
    pvCloud_Send_Float("POWER_METER_2",Dato2);
    Serial.print("     Irms2: ");
    Serial.println(Irms2);           // Irms
    // if bluetooth then sent
    Serial1.print("    Irms2: ");
    Serial1.println(Irms2);

  }
  else{
    log("Calculating Dato2 on Irms <= 0.09");
    Dato2 = 0;
    Serial.print("Apparent power 2: ");
    Serial.print(Dato2);         // Apparent power
    // if bluetooth then sent
    Serial1.print("Apparent power 2: ");
    Serial1.print(Dato2);
    log(Dato2);
    log("Sending Dato2 to pvCloud...");
    
    pvCloud_Send_Float("POWER_METER_2",Dato2);
    Serial.print("     Irms2: ");
    Serial.println(Irms2);           // Irms
    // if bluetooth then sent 
    Serial1.print("     Irms2: ");
    Serial1.println(Irms2);

  }
  log("loop() end");
}

void pvCloud_Send_String(String label, String value){
  log("BEGIN: pvCloud_Send_String");
  Serial.println("pvCloud_Send_String()");
  Serial1.println("pvCloud_Send_String()");

  String command = "node ~/pvcloud_api.js action='add_value' value_type='FLOAT' captured_datetime='2000-01-01+00:01'";
  command= command + " value_label='" + label + " ' ";
  command = command + " value='";
  command = command + value;
  command = command + "' > lastcommand.txt";
  log(command);
  Serial.println(command);
  Serial1.println(command);
  log("call to Linux now...");
  system ( command.buffer);
  log("COMLPETE: pvCloud_Send_String");
}

void pvCloud_Send_Float(char *label, float value){
  log("BEGIN: pvCloud_Send_Float");
  Serial.println("pvCloud_Send_Double()");
  Serial1.println("pvCloud_Send_Double()");

  char command[1000];
  sprintf(command, "node ~/pvcloud_api.js action='add_value' value_type='FLOAT' captured_datetime='2000-01-01+00:04' value_label='%s' value='%.2f'  > lastcommand.txt", label, value);
  log(command);
  Serial.println(command);
  Serial1.println(command);
  log("call to Linux now...");
  system ( command);
  log("COMLPETE: pvCloud_Send_Float");
}


void sendValueToPvCloud(String label, int value, float valor){
  Serial.println("Send Value to pvCloud");
  Serial1.println("Send Value to pvCloud");
  char stringOne[100];
  String command = "node ~/pvcloud_api.js action='add_value' value_type='FLOAT' captured_datetime='2000-01-01+10:23'";
  command= command + " value_label='" + label + " ' ";
  command = command + " value='";
  command = command + value;
  command = command + "'";
  Serial1.println(command);
  sprintf(stringOne, "node ~/pvcloud_api.js action='add_value' value_type='FLOAT' captured_datetime='2000-01-01+10:23' value_label='' value='%.2f'", valor);
  system ( command.buffer);
  system (stringOne);
  Serial1.println(stringOne);
}

void log(String message){
   String command = "echo \"";
   command = command + message;
   command = command + "\" >> sketch.log";
   system(command.buffer);
}
