/*
Name:		CController.c
Created:	09/04/2016 12:15:51
Version:	1.0
*/

#include "CController.h"

#pragma region Public methods

void CController::setup()
{
	m_bluetooth->Begin(9600);
	m_iCurrentSpeed = 0;
	m_CurrentMovement = EMovements::Stop;
	m_lLastTime = millis();
	pinMode(iInButtonX, INPUT_PULLUP);
	pinMode(iInButtonA, INPUT_PULLUP);
	pinMode(iInButtonB, INPUT_PULLUP);
	pinMode(iOutLed, OUTPUT);			//activates Led output when a button press is detected
}

void CController::loop()
{
	m_sSendValue = "";
	m_sLastCmd = "";

	//read from buttons and send through Bluetooth
	if (digitalRead(iInButtonX) == LOW)
		m_sSendValue += "x";
	if (digitalRead(iInButtonA) == LOW)
		m_sSendValue += "a";
	if (digitalRead(iInButtonB) == LOW)
		m_sSendValue += "b";
	if (m_joystick->ReadButton() == LOW)
		m_sSendValue += "j";
	if (m_sSendValue.length() > 0)
	{
		m_bluetooth->Send(" ");		//WORKAROUND: send dummy value to ¿wake up/synchronize? bluetooth
		m_bluetooth->SendCommand(m_sSendValue);
		m_lLastTime = millis();		//reset count to PowerDown
		digitalWrite(iOutLed, HIGH);
		while ( digitalRead(iInButtonX) == LOW ||
				digitalRead(iInButtonA) == LOW ||
				digitalRead(iInButtonB) == LOW ||
				m_joystick->ReadButton() == LOW )	//wait while buttons are pressed instead of setting a fixed delay
		{
			// // Sleep to save power -> resets the millis() value so use delay
			// Common.Sleep(SLEEP_30MS);
			delay(30);
		}
	}
	else
	{
		digitalWrite(iOutLed, LOW);
	}

	//read from joystick and send through Bluetooth
	m_iX = m_joystick->ReadAxisX();
	m_iY = m_joystick->ReadAxisY();
	m_motors->ProcessMotors((byte)m_iX, (byte)m_iY);
	if (abs(m_motors->GetCurrentSpeed() - m_iCurrentSpeed) > 3 ||
			m_motors->GetCurrentMovement() != m_CurrentMovement)
	{
		m_iCurrentSpeed   = m_motors->GetCurrentSpeed();
		m_CurrentMovement = m_motors->GetCurrentMovement();

		m_bluetooth->Send(" ");		//WORKAROUND: send dummy value to ¿wake up/synchronize? bluetooth
		m_bluetooth->SendCommand(m_iX, m_iY);
		m_lLastTime = millis();		//reset count to PowerDown
		
		//set m_sLastCmd -> mainly for debug
		m_sLastCmd = "BT-> " + m_bluetooth->GetMessage() + " | Speed: " + String(m_iCurrentSpeed) + " | X: " + String(m_iX) + " | Y: " + String(m_iY);
	
		//sleep between transmissions
		// Common.Sleep(SLEEP_30MS);
		delay(30);
	}

	// check if enter Power Down to save battery
	if (millis() - m_lLastTime >= lTimeToPowerDown)
	{
		digitalWrite(iOutLed, LOW);		//switch off to save power
		Common.PowerDownInt1();
		m_sLastCmd = "RCC -> PowerDown off";
	}
}

#pragma endregion

#pragma region Private methods

#pragma endregion