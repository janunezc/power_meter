/*
  pvcloud_lib.cpp - Library for pvcloyud
  Created by Jose Nunez, July 18 2015
  Copyright 2015(c) Intel Corporation
  MIT License
  Official Development: https://github.com/janunezc/pvcloud_arduino_library
*/

#include "pvcloud_lib.h"

void PVCloud::SendString(String label, String value){
  //log("BEGIN: pvCloud_Send_String");
  Serial.println("pvCloud_Send_String()");
  Serial1.println("pvCloud_Send_String()");

  String command = "node ~/pvcloud_api.js action='add_value' value_type='FLOAT' captured_datetime='2000-01-01+00:01'";
  command= command + " value_label='" + label + " ' ";
  command = command + " value='";
  command = command + value;
  command = command + "' > lastcommand.txt";
  //log(command);
  Serial.println(command);
  Serial1.println(command);
  //log("call to Linux now...");
  system ( command.buffer);
  //log("COMLPETE: pvCloud_Send_String");  
}

void PVCloud::SendFloat(char *label, float value){
  //logEntry("BEGIN: pvCloud_Send_Float");
  Serial.println("pvCloud_Send_Double()");
  Serial1.println("pvCloud_Send_Double()");

  char command[1000];
  sprintf(command, "node ~/pvcloud_api.js action='add_value' value_type='FLOAT' captured_datetime='2000-01-01+00:04' value_label='%s' value='%.2f'  > lastcommand.txt", label, value);
  LogEntry(command);
  Serial.println(command);
  Serial1.println(command);
  //logEntry("call to Linux now...");
  system ( command);
  //logEntry("COMLPETE: pvCloud_Send_Float");
}

void PVCloud::LogEntry(String message){
   String command = "echo \"";
   command = command + message;
   command = command + "\" >> sketch.log";
   system(command.buffer);
}


void PVCloud::LogEntry(double value){
   char command[1000];
   sprintf(command, "echo \"%.2f\" >> sketch.log", value);
   system(command);
}
