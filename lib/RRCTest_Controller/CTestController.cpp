#include "CTestController.h"

#pragma region Public methods

void CTestController::setup()
{
    m_Controller->setup();
}

void CTestController::loop()
{
    m_Controller->loop();
    
    //read processed command (joystick, movement, etc.)
    m_sSendValue = m_Controller->GetLastCommand();
    if (m_sSendValue.length() > 0)
	    Serial.println(m_sSendValue);
}

#pragma endregion

// Private methods
