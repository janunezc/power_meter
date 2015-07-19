/*
  pvcloud_lib.h - Library for pvcloyud
  Created by Jose Nunez, July 18 2015
  Copyright 2015(c) Intel Corporation
  MIT License
  Official Development: https://github.com/janunezc/pvcloud_arduino_library
*/
#include "Arduino.h"
class PVCloud
{
  public:

    void SendString(String label, String value);
    void SendFloat(char *label, float value);
    void LogEntry(String message);
    void LogEntry(double value);
 
};

