
#ifndef __BLUETOOTH_H__
#define __BLUETOOTH_H__

#include <BluetoothSerial.h>


class Bluetooth
{
public:
    void serialSetup();
    bool serialAvailable();
    String getString();
    void writeString(String const& message);

private:
    BluetoothSerial _serialCommunicator;
};


#endif
