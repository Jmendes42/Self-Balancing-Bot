
#include "Bluetooth.h"

void Bluetooth::serialSetup()
{
    _serialCommunicator.begin("esp32");
    Serial.println("Serial Bluetooth initialized");
}

bool Bluetooth::serialAvailable()
{
    return _serialCommunicator.available();
}

String Bluetooth::getString()
{
    return _serialCommunicator.readStringUntil('\n');
}

void Bluetooth::writeString(String const& message)
{
    _serialCommunicator.println(message);
}
