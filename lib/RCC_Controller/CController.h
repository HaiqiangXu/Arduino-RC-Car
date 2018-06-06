/*
Name:		CController.h
Created:	09/04/2016 12:15:51
Version:	1.0
*/

#include "CBluetooth.h"
#include "CMotors.h"
#include "CJoystick.h"
#include "CCommon.h"

const int iInButtonX = 4;
const int iInButtonA = 3;			//Common.PowerDown is linked to INT 1 for wake up -> INPUT 3 is now linked to button 'A' which is used to wake-up when pressed
const int iInButtonB = 5;
const int iOutLed = 13;
const int iOutRx = 11;
const int iOutTx = 12;
const int iInAxisX = 0;
const int iInAxisY = 1;
const int iInButton = 8;
const unsigned long lTimeToPowerDown = 60000;

class CController
{
public:
	// Contructors
	CController()
	{
		m_bluetooth = new CBluetooth(iOutRx, iOutTx, EBluetoothAdapter::HC_05);	//RX, TX, EBluetoothAdapter
		m_joystick = new CJoystick(iInAxisX, iInAxisY, iInButton);	//analogInputX, analogInputY, digitalInputButton
		m_motors = new CMotors();									//create virtual motor to calculate motor movement, so send command only when needed
	};

	// Public methods
	void setup();
	void loop();

	// Data accessors
	String GetLastCommand()
	{
		return m_sLastCmd;
	};
private:
	//Fields
	CBluetooth* m_bluetooth;
	CJoystick* m_joystick;
	CMotors* m_motors;
	int m_iX, m_iY;
	int m_iCurrentSpeed;
	EMovements m_CurrentMovement;
	String m_sSendValue, m_sLastCmd;
	unsigned long m_lLastTime;

	// Private methods
};