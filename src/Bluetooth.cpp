
#include "Bluetooth.h"

void Bluetooth::serialSetup()
{
    _SerialCommunicator.begin("esp32");
    Serial.println("Serial Bluetooth initialized");
}

bool Bluetooth::serialAvailable()
{
    return _SerialCommunicator.available();
}

String Bluetooth::getString()
{
    return _SerialCommunicator.readStringUntil('\n');
}

void Bluetooth::writeString(String const& message)
{
    _SerialCommunicator.println(message);
}
