/*
Name:		CAble.h
Created:	09/04/2016 12:15:51
Version:	1.0
*/

#include "CBluetooth.h"
#include "CMotors.h"
#include "CMelodies.h"
#include "CCommon.h"

const int iOutSpeaker = 8;
const int iOutLed = 13;
const int iOutRx = 3;			//changed from 2 to 3 because Common.PowerDown is linked to INT 1 for wake up -> INPUT 3 is now linked to Rx which is used to wake-up when BT receives data
const int iOutTx = 2;			//physically not needed in normal functionality. Needed when AT commands need to be send
const int iOutLeft1 = 11;
const int iOutLeft2 = 12;
const int iOutRight1 = 9;
const int iOutRight2 = 10;
const int iOutEna = 5;
const int iOutEnb = 6;
const unsigned long lTimeToPowerDown = 60000;

class CAble
{
public:
	// Contructors
	CAble()
	{
		m_bluetooth = new CBluetooth(iOutRx, iOutTx, EBluetoothAdapter::HC_06);	//RX, TX, EBluetoothAdapter
		m_motors = new CMotors(iOutLeft1, iOutLeft2, iOutRight1, iOutRight2, iOutEna, iOutEnb); //NOTE: pinENA and pinENB must be PWM pins!!!!!
		m_melodies = new CMelodies(iOutSpeaker);
	};
	
	// Public methods
	void setup();
	void loop();

	// Data accessors
	String GetLastCommand()
	{
		return m_sLastCmd;
	};

	String GetReadValue()
	{
		return m_sReadValue;
	};
private:
	// Fields
	CBluetooth* m_bluetooth;
	CMotors* m_motors;
	CMelodies* m_melodies;
	String m_sReadValue;
	int* m_intValues;
	char m_char;
	String m_sCmd, m_sLastCmd;
	unsigned long m_lLastTime;
	
	// Private methods
	void ProcessJoystick(String sCommand);
	void ProcessButtons(String sCommand);
};