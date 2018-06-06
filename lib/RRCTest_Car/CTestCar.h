#include "CAble.h"

class CTestCar
{
public:
    // Constructors
    CTestCar()
    {
        //init HardwareSerial to monitor and debug Arduino RX / TX and its activity
        Serial.begin(9600);
        Serial.println("Debugging Car Able");

        m_CarAble = new CAble();
    };

    // Public methods
    void setup();
    void loop();
    
private:
    // Fields
    CAble* m_CarAble;
	String m_sReadValue;

    // Private methods
};