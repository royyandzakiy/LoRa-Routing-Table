#include <Arduino.h>
#include "Datagram.h"

Datagram::Datagram() {
  // creates an empty Datagram
  hopFrom = "0";
  rssi = "0";
  alertStatus = "0";
}

// DEPRECATED!!! (15/Mar/2020)
// an intermediary function
void Datagram::stringToStringArrayParser(String stringToParse, String outputStringArray[]) {
  // parser
  int tempStart = 0;
  int tempEnd = 0;
  for (int i=0; i<DATAGRAM_SIZE; i++) {
    if (i<DATAGRAM_SIZE-1) tempEnd = stringToParse.indexOf(',', tempStart+1);
    else tempEnd = stringToParse.indexOf(';');

    // adding to string array
    outputStringArray[i] = stringToParse.substring(tempStart, tempEnd);

    tempStart = tempEnd + 1;
  }
}

Datagram::Datagram(String _hopFrom, String _rssi, String _alertStatus) {
  hopFrom = _hopFrom;
  rssi = _rssi;
  alertStatus = _alertStatus;
}

Datagram::Datagram(String stringToParse) {
  // DATAGRAM FORMAT (string): "hopFrom,rssi,alertStatus,datetimeSent,datetimeReceived;"
  // parser
  String tempStringArray[DATAGRAM_SIZE];
  stringToStringArrayParser(stringToParse, tempStringArray);

  hopFrom = tempStringArray[0];
  rssi = tempStringArray[1];
  alertStatus = tempStringArray[2];
}

void Datagram::set(String _hopFrom, String _rssi, String _alertStatus) {
  hopFrom = _hopFrom;
  rssi = _rssi;
  alertStatus = _alertStatus;
}

void Datagram::set_from_string(String stringToParse) {
  // DATAGRAM FORMAT (string): "hopFrom,rssi,alertStatus,datetimeSent,datetimeReceived;"
  // parser
  String tempStringArray[DATAGRAM_SIZE];
  stringToStringArrayParser(stringToParse, tempStringArray);

  set(tempStringArray[0], tempStringArray[1], tempStringArray[2]);
}

String Datagram::get_to_string() {
  String tempDatagramString;
  tempDatagramString = "{\"hopFrom\":" + hopFrom + ",\"rssi\":" + rssi + ",\"alertStatus\":" + alertStatus + "}";
  
  return tempDatagramString;
}

void Datagram::print_to_string() {
  Serial.print(get_to_string());
}