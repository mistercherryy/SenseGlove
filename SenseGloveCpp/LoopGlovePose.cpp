#include <iostream> //Output to console
#include <time.h>
#include <thread>  //To pause the main() while vibrating
#include <chrono>  //To pause the thread for std::chrono::seconds

#include "Library.h"	// Access library details
#include "DeviceList.h" // Access devices and communication state
#include "SenseGlove.h" // SenseGlove interface through which we access data.
#include "Tracking.h"

const int NUM_SECONDS = 10;

//void LoopTryConsty()
int main()
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
            //system("pause");

            while (true) {
                std::cout << "Getting new Pose" << std::endl;
                //Retrieving Glove Pose: The position / rotation of the glove, as well as its sensor angles placed in the right direction.
                SGCore::SG::SG_GlovePose glovePose;
                if (testGlove.GetGlovePose(glovePose))
                {
                    //As an example, lets calculate fingertip positions.

                    //If we wish to calculate hand variables, we need a "hand profile" to tell the Sense Glove our hand lengths.
                    SGCore::SG::SG_HandProfile handProfile = SGCore::SG::SG_HandProfile::Default(testGlove.IsRight()); //create a default profile, either left or right.
                    SGCore::Kinematics::BasicHandModel handModel = SGCore::Kinematics::BasicHandModel::Default(testGlove.IsRight()); //create a default profile, either left or right.
                    std::vector<SGCore::Kinematics::Vect3D> tipPositions = glovePose.CalculateFingerTips(handProfile); //calculates fingertip position


                    std::cout << std::endl;

                    //for (int f = 0; f < tipPositions.size(); f++)
                    //    std::cout << std::to_string(((SGCore::Finger)f)) << ": " << tipPositions[f].ToString() << std::endl; //writes "thumb: ", "index: " etc.
                    
                    
                    //std::cout << std::to_string(((SGCore::Finger)0)) << " : thumb : " << tipPositions[0].ToString() << std::endl;
                   // std::cout << std::to_string(((SGCore::Finger)1)) << " : index : " << tipPositions[1].ToString() << std::endl;
                    //std::cout << std::to_string(((SGCore::Finger)2)) << " : middle : " << tipPositions[2].ToString() << std::endl;
                    //std::cout << std::to_string(((SGCore::Finger)3)) << " : ring : " << tipPositions[3].ToString() << std::endl;
                    //std::cout << std::to_string(((SGCore::Finger)4)) << " : pinky : " << tipPositions[4].ToString() << std::endl;

                    float dThumbIndex = tipPositions[0].DistTo(tipPositions[2])-20; //calculates the distance between thumb (0) and index finger (1), in mm.
                    std::cout << "The distance between thumb and middle finger is " << std::to_string(dThumbIndex) << "mm." << std::endl;

                    //HandPose Example

                    SGCore::HandPose handPose;
                    if (testGlove.GetHandPose(handModel, handProfile, handPose))
                    {
                        std::cout << std::endl;
                        //std::cout << "Calculated Hand Pose: " << std::endl << handPose.ToString() << std::endl;
                    }
                    else
                    {
                        std::cout << "Could not retrieve a hand pose" << std::endl;
                    }
                }
  /*              std::cout << "Press any key to get next pose" << std::endl;
                system("pause");*/

                std::this_thread::sleep_for(std::chrono::milliseconds(100)); //wait for 10ms.
            }
            
            
           // //If we wish to calculate hand variables, we need a "hand profile" to tell the Sense Glove our hand lengths.
           //// SGCore::SG::SenseGlove testGlove;

           // SGCore::SG::SG_GlovePose glovePose;

           // SGCore::SG::SG_HandProfile handProfile = SGCore::SG::SG_HandProfile::Default(testGlove.IsRight()); //create a default profile, either left or right.

           // SGCore::Kinematics::BasicHandModel handModel = SGCore::Kinematics::BasicHandModel::Default(testGlove.IsRight()); //create a default profile, either left or right.


           // //int count = 1;

           // //double time_counter = 0;

           // //clock_t this_time = clock();
           // //clock_t last_time = this_time;

           //// printf("Gran = %ld\n", NUM_SECONDS * CLOCKS_PER_SEC);
           // while (true)
           // {

           //    /* this_time = clock();

           //     time_counter += (double)(this_time - last_time);

           //     last_time = this_time;

           //     if (time_counter > (double)(NUM_SECONDS * CLOCKS_PER_SEC))
           //     {
           //         time_counter -= (double)(NUM_SECONDS * CLOCKS_PER_SEC);
           //         printf("%d\n", count);
           //         count++;
           //     }
           //     */
           //     std::vector<SGCore::Kinematics::Vect3D> tipPositions = glovePose.CalculateFingerTips(handProfile); //calculates fingertip position
           //     std::cout << std::endl;
           //     
           //     for (int f = 0; f < tipPositions.size(); f++) {
           //         std::cout << std::to_string(((SGCore::Finger)f)) << ": " << tipPositions[3].ToString() << std::endl; //writes "thumb: ", "index: " etc.
           //     }
           //    // printf("DebugTime = %f\n", time_counter);
           //     std::this_thread::sleep_for(std::chrono::milliseconds(500));
           // }
           // std::cout << "burayı sonra sil" << std::endl;
           // //return 0;
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
