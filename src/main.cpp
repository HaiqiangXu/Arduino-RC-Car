#include "main.h"

#ifdef TEST_CAR
    #include "CTestCar.h"
    CTestCar* m_testCar;

    void setup() {
        process();
        m_testCar = new CTestCar();
        m_testCar->setup();
    }

    void loop() {
        // put your main code here, to run repeatedly:
        m_testCar->loop();
    }
#endif

#ifdef TEST_CONTROLLER
    #include "CTestController.h"
    CTestController* m_testController;

    void setup() {
        process();
        m_testController = new CTestController();
        m_testController->setup();
    }

    void loop() {
        // put your main code here, to run repeatedly:
        m_testController->loop();
    }
#endif

#ifdef RCC_CONTROLLER
    #include "CController.h"
    CController* m_Controller;

    void setup() {
        process();
        m_Controller = new CController();
        m_Controller->setup();
    }

    void loop() {
        // put your main code here, to run repeatedly:
        m_Controller->loop();
    }
#endif

#ifdef RCC_ABLE
    #include "CAble.h"
    CAble* m_CarAble;

    void setup() {
        process();
        m_CarAble = new CAble();
        m_CarAble->setup();
    }

    void loop() {
        // put your main code here, to run repeatedly:
        m_CarAble->loop();
    }
#endif

#if defined(TEST_BT_UNO) || defined(TEST_BT_NANO)
    #include "CBluetooth.h"
    #include "CCommon.h"
    CBluetooth* m_bluetooth;

    void setup() {
        #if defined(TEST_BT_UNO)
        m_bluetooth = new CBluetooth(3, 2, HC_06);
        #endif
        #if defined(TEST_BT_NANO)
        m_bluetooth = new CBluetooth(11, 12, HC_05);
        #endif
        m_bluetooth->Begin(9600);

        Serial.begin(9600);
	    Serial.println("Debugging Bluetooth module");
    }

    void loop() {
        //REMEMBER: press HC-05 key button for 1s before sending any AT command. Can be replaced by HIGH signal into KEY pin
        //Read and send bluetooth after read of keyboard
        String sValue = m_bluetooth->DirectReceive();
        if (sValue.length() > 0)
            Serial.println("BT-> " + sValue);
        sValue = Common.ReadKeyboard();
        if (sValue == "a")
        {
            #if defined(TEST_BT_UNO)
            m_bluetooth->SendATCommandHC06(AT, "");
            #endif
            #if defined(TEST_BT_NANO)
            m_bluetooth->SendATCommandHC05(AT, "");
            #endif
        }
        else if (sValue == "b")
        {
            #if defined(TEST_BT_UNO)
            m_bluetooth->SendATCommandHC06(AT_VERSION, "");
            #endif
            #if defined(TEST_BT_NANO)
            m_bluetooth->SendATCommandHC05(AT_VERSION, "");
            #endif
        }
        else if (sValue == "c")
            m_bluetooth->Send("AT+NAME?");
        else if (sValue == "d")
            m_bluetooth->Send("AT+PSWD?");
        else if (sValue == "e")
            m_bluetooth->Send("AT+UART?");
        else if (sValue == "f")
            m_bluetooth->Send("AT+ROLE?");
        else if (sValue == "g")
            m_bluetooth->Send("AT+CMODE?");
        else if (sValue == "h")
            m_bluetooth->Send("AT+BIND?");
        else if (sValue == "i")
        {
            #if defined(TEST_BT_UNO)
            m_bluetooth->SendATCommandHC06(AT_STATE, "");
            #endif
            #if defined(TEST_BT_NANO)
            m_bluetooth->SendATCommandHC05(AT_STATE, "");
            #endif
        }
        if (sValue.length() > 0)
            Serial.println("-> " + sValue);
    }
#endif