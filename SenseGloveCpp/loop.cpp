#include <iostream> //Output to console
#include <time.h>
#include <thread>  //To pause the main() while vibrating
#include <chrono>  //To pause the thread for std::chrono::seconds

#include "Library.h"	// Access library details
#include "DeviceList.h" // Access devices and communication state
#include "SenseGlove.h" // SenseGlove interface through which we access data.
#include "Tracking.h"

const int NUM_SECONDS = 100;
void loop()
//int main()
{
    int count = 1;

    double time_counter = 0;

    clock_t this_time = clock();
    clock_t last_time = this_time;

    printf("Gran = %ld\n", NUM_SECONDS * CLOCKS_PER_SEC);
    //If we wish to calculate hand variables, we need a "hand profile" to tell the Sense Glove our hand lengths.
  /* SGCore::SG::SenseGlove testGlove;
    SGCore::SG::SG_GlovePose glovePose;
    SGCore::SG::SG_HandProfile handProfile = SGCore::SG::SG_HandProfile::Default(testGlove.IsRight()); //create a default profile, either left or right.
    SGCore::Kinematics::BasicHandModel handModel = SGCore::Kinematics::BasicHandModel::Default(testGlove.IsRight()); //create a default profile, either left or right.*/
    
    while (true)
    {
        
        this_time = clock();

        time_counter += (double)(this_time - last_time);

        last_time = this_time;

        if (time_counter > (double)(NUM_SECONDS * CLOCKS_PER_SEC))
        {
            time_counter -= (double)(NUM_SECONDS * CLOCKS_PER_SEC);
            printf("%d\n", count);
            count++;
        }
        
       // std::vector<SGCore::Kinematics::Vect3D> tipPositions = glovePose.CalculateFingerTips(handProfile); //calculates fingertip position

        
         // std::cout << std::to_string(((SGCore::Finger)0)) << ": " << tipPositions[0].ToString() << std::endl; //writes "thumb: ", "index: " etc  

        printf("DebugTime = %f\n", time_counter);
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

   std::cout <<  "you did it "  << std::endl;
    //return 0;
}
