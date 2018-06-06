#include "CController.h"

class CTestController
{
public:
    // Constructors
    CTestController()
    {
        //init HardwareSerial to monitor and debug Arduino RX / TX and its activity
        Serial.begin(9600);
        Serial.println("Debugging CController");

        m_Controller = new CController();
    };

    // Public methods
    void setup();
    void loop();
    
private:
    // Fields
    CController* m_Controller;
    String m_sSendValue;

    // Private methods
};