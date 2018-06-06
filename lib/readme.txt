Generic-Libraries
|--external-libs
|   |-- <LowPower>
|   |-- <MD_MAX72XX>
|--lib
|   |-- <CommonLib>
|   |   |-- CCommon.h
|   |-- <Bluetooth_Lib>
|   |   |-- CBluetooth.cpp
|   |   |-- CBluetooth.h
|   |-- <Joystick_Lib>
|   |   |-- CJoystick.cpp
|   |   |-- CJoystick.h
|   |-- <Marquee_Lib>
|   |   |-- CMarquee.cpp
|   |   |-- CMarquee.h
|   |-- <Melodies_Lib>
|   |   |-- CMelodies.cpp
|   |   |-- CMelodies.h
|   |-- <Motors_Lib>
|   |   |-- CMotors.cpp
|   |   |-- CMotors.h
|   |   |-- Speed_voltage.txt
-------------
RCC
|--lib
|   |-- <RCC_Able>
|   |   |-- CAble.cpp
|   |   |-- CAble.h
|   |-- <RCC_Controller>
|   |   |-- CController.cpp
|   |   |-- CController.h
|   |-- <RCCTest_Car>
|   |   |-- CTestCar.cpp
|   |   |-- CTestCar.h
|   |-- <RCCTest_Controller>
|   |   |-- CTestController.cpp
|   |   |-- CTestController.h
|--src
|   |- main.cpp
|   |- main.h    
-------------
This directory is intended for the project specific (private) libraries.
PlatformIO will compile them to static libraries and link to executable file.

The source code of each library should be placed in separate directory, like
"lib/private_lib/[here are source files]".

For example, see how can be organized `Foo` and `Bar` libraries:

|--lib
|  |--Bar
|  |  |--docs
|  |  |--examples
|  |  |--src
|  |     |- Bar.c
|  |     |- Bar.h
|  |--Foo
|  |  |- Foo.c
|  |  |- Foo.h
|  |- readme.txt --> THIS FILE
|- platformio.ini
|--src
   |- main.c

Then in `src/main.c` you should use:

#include <Foo.h>
#include <Bar.h>

// rest H/C/CPP code

PlatformIO will find your libraries automatically, configure preprocessor's
include paths and build them.

More information about PlatformIO Library Dependency Finder
- http://docs.platformio.org/page/librarymanager/ldf.html
