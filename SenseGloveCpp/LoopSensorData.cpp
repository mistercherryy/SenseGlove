#include <iostream> //Output to console
#include <time.h>
#include <thread>  //To pause the main() while vibrating
#include <chrono>  //To pause the thread for std::chrono::seconds

#include "Library.h"	// Access library details
#include "DeviceList.h" // Access devices and communication state
#include "SenseGlove.h" // SenseGlove interface through which we access data.
#include "Tracking.h"

const int NUM_SECONDS = 10;

void SensorDataLoop()
//int main()
{
    std::cout << "Testing " << SGCore::Library::Version() << std::endl;
    std::cout << "=======================================" << std::endl;

    //SGCore::PosTrackingHardware testvar = SGCore::PosTrackingHardware::ViveTracker;

    if (SGCore::DeviceList::SenseCommRunning()) //check if the Sense Comm is running. If not, warn the end user.
    {
        SGCore::SG::SenseGlove testGlove;

        if (SGCore::SG::SenseGlove::GetSenseGlove(testGlove)) //retrieves the first Sense Glove it can find. Returns true if one can be found
        {
            std::cout << "Activating " << testGlove.ToString() << " on key press." << std::endl;
            system("pause");

            while (true) {
               
                //Retrieving Sensor Data (raw). The lowest level data available
                SGCore::SG::SG_SensorData sensorData;
                if (testGlove.GetSensorData(sensorData)) //if GetSensorData is true, we have sucesfully recieved data
                {
                    std::cout << std::endl;
                    std::cout << sensorData.ToString() << std::endl;
                }
                
                
                
                /*              std::cout << "Press any key to get next pose" << std::endl;
                              system("pause");*/

                std::this_thread::sleep_for(std::chrono::milliseconds(400)); //wait for 10ms.
            }
        }
        else {
            std::cout << "No sense gloves connected to the system. Ensure the USB connection is secure, then try again." << std::endl;
        }
    }
    else
        std::cout << "SenseComm is not running. Please start it and try again." << std::endl;

    std::cout << "=======================================" << std::endl;
    std::cout << "Press any key to exit." << std::endl;
    system("pause");
}