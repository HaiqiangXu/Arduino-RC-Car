#include "CTestCar.h"

#pragma region Public methods

void CTestCar::setup()
{
    m_CarAble->setup();
}

void CTestCar::loop()
{
	m_CarAble->loop();

    //read from Bluetooth module received message
	m_sReadValue = m_CarAble->GetReadValue();
    if (m_sReadValue.length() >= 2)
	{
        Serial.println("BT->" + m_sReadValue);

        //read processed command (joystick, movement, etc.)
        Serial.println(m_CarAble->GetLastCommand());
	}
}

#pragma endregion

// Private methods
