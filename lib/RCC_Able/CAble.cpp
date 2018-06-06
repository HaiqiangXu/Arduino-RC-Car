/*
Name:		CAble.cpp
Created:	09/04/2016 12:15:51
Version:	1.0
*/

#include "CAble.h"

#pragma region Public methods

void CAble::setup()
{
	m_lLastTime = millis();
    m_bluetooth->Begin(9600);
	pinMode(iOutLed, OUTPUT);
}

void CAble::loop()
{
	// // Sleep to save power -> resets the millis() value so use delay
	// Common.Sleep(SLEEP_120MS);
	delay(120);
	
	// check if enter Power Down to save battery
	if (millis() - m_lLastTime >= lTimeToPowerDown)
	{
		digitalWrite(iOutSpeaker, HIGH);		//advise entering power down mode
		delay(150);
		digitalWrite(iOutSpeaker, LOW);
		digitalWrite(iOutLed, LOW);				//switch off to save power
		Common.PowerDownInt1();
		m_sLastCmd = "RCC -> PowerDown off";
	}

	//read from Bluetooth module once woken up
	m_sReadValue = m_bluetooth->Receive();

	//filter those messages without a minimum length (at least INI_CMD + END_CMD)
	if (m_sReadValue.length() <= 2)
	{
		return;
	}

	//process received command
	for (int i = 0; i < m_sReadValue.length(); i++)
	{
		m_char = m_sReadValue[i];
		m_sCmd += m_char;			//concatenate chars until '#' end command is detected
		if (m_char == '#')
		{
			if (m_bluetooth->CommandType(m_sCmd) == ECommandType::ArrayBytes)
			{
				ProcessJoystick(m_sCmd);
			}
			else if (m_bluetooth->CommandType(m_sCmd) == ECommandType::StringCommand)
			{
				ProcessButtons(m_sCmd);
			}
			m_sCmd = "";
			m_lLastTime = millis();	//reset count to PowerDown
		}
	}
}

#pragma endregion

#pragma region Private methods

void CAble::ProcessJoystick(String sCommand)
{
	//process joystick values
	m_intValues = m_bluetooth->ProcessArrayBytesCommand(sCommand);

	//move motors accordingly
	m_motors->ProcessMotors((byte)m_intValues[0], (byte)m_intValues[1]);

	//set m_sLastCmd -> mainly for debug
	m_sLastCmd = "Cmd: " + sCommand + " | Motor movement: " + m_motors->GetCurrMovString();
}

void CAble::ProcessButtons(String sCommand)
{
	//process buttons values
	sCommand = m_bluetooth->ProcessStringCommand(sCommand);

	if (sCommand == "j")
	{
		//switch-on LED
		if (digitalRead(iOutLed) == LOW)
			digitalWrite(iOutLed, HIGH);
		else
			digitalWrite(iOutLed, LOW);
	}
	else if (sCommand == "x")
	{
		m_melodies->PlayMelody(EMelodies::Fanfarria);
	}
	else if (sCommand == "a")
	{
		m_melodies->PlayMelody(EMelodies::DogPower);
	}
	else if (sCommand == "b")
	{
		ESpeedMode speed = m_motors->GetSpeedMode();
		if (speed == ESpeedMode::Slow)
			m_motors->SetSpeedMode(ESpeedMode::Normal);
		else if (speed == ESpeedMode::Normal)
			m_motors->SetSpeedMode(ESpeedMode::Fast);
		else if (speed == ESpeedMode::Fast)
			m_motors->SetSpeedMode(ESpeedMode::Turbo);
		else
			m_motors->SetSpeedMode(ESpeedMode::Slow);

		//make a sound to confirm SpeedMode
		speed = m_motors->GetSpeedMode();
		for (int i = 0; i < int(speed); i++)
		{
			digitalWrite(iOutSpeaker, HIGH);
			delay(50);
			digitalWrite(iOutSpeaker, LOW);
			delay(50);
		}
	}
	else
	{
		//Process command from Smartphone/Tablet
		m_motors->ProcessMotors(sCommand);
	}

	//set m_sLastCmd -> mainly for debug
	m_sLastCmd = "Cmd: " + sCommand;
}

#pragma endregion