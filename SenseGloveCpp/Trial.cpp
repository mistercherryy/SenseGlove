#include <iostream> //Output to console

#include <thread>  //To pause the main() while vibrating
#include <chrono>  //To pause the thread for std::chrono::seconds

#include "Library.h"	// Access library details
#include "DeviceList.h" // Access devices and communication state
#include "SenseGlove.h" // SenseGlove interface through which we access data.
#include "Tracking.h"

//int main(){
static void Trial() {
	std::cout << "Testing " << SGCore::Library::Version() << std::endl;
	std::cout << "=======================================" << std::endl;

	if (SGCore::DeviceList::SenseCommRunning()) //check if the Sense Comm is running. If not, warn the end user.
	{
		SGCore::SG::SenseGlove testGlove;
		if (SGCore::SG::SenseGlove::GetSenseGlove(testGlove)) //retrieves the first Sense Glove it can find. Returns true if one can be found
		{
			std::cout << "Activating " << testGlove.ToString() << " on key press." << std::endl;
			system("pause");

			testGlove.SendHaptics(SGCore::Haptics::SG_BuzzCmd(80, 80, 80, 80, 80)); //vibrate the index fingerat 80% intensity.
			std::this_thread::sleep_for(std::chrono::milliseconds(1000)); //vibrating for for 200ms.

			testGlove.SendHaptics(SGCore::Haptics::SG_BuzzCmd::off); //turn off all Buzz Motors.
			testGlove.StopHaptics();
			std::this_thread::sleep_for(std::chrono::milliseconds(10)); //wait for 10ms.

			SGCore::SG::SG_GloveInfo model = testGlove.GetGloveModel(); //Retrieve device information
			std::cout << std::endl;
			std::cout << model.ToString(true) << std::endl; //Log some basic information to the user. (true indicates a short notation is desired)

			//HERE CALIBRATIONS BEGINN!
			
			
			// Step 1: Open hand - Calibrates extension
			std::cout << std::endl;
			std::cout << "Step 1: Place your hand on a flat surface, like a table, and spread your thumb and fingers." << std::endl;
			// Once you get the hang of this motion, you can do it without the surface.
			std::cout << "Once your hand is in the right position, press any key to continue" << std::endl;
			system("pause");

			// This function updates the calibration range of testGlove.
			testGlove.UpdateCalibrationRange();

			// Step 2: Fist - Calibrates flexion
			std::cout << std::endl;
			std::cout << "Step 2: Close your hand into a fist. Make sure your fingers aren't wrapped around your thumb." << std::endl;
			std::cout << "Once your hand is in the right position, press any key to continue" << std::endl;
			system("pause");

			// This function updates the calibration range of testGlove. 
			testGlove.UpdateCalibrationRange();

			// At this point, we've collected data while the hand was open, and when it was closed. 
			// The calibration range should now have the two extremes to interpolate between.
			// Let's check & ouput the ranges:
			std::vector<SGCore::Kinematics::Vect3D> minRanges, maxRanges;
			testGlove.GetCalibrationRange(minRanges, maxRanges);


			//ADD HERE
			//Retrieving Glove Pose: The position / rotation of the glove, as well as its sensor angles placed in the right direction.
			SGCore::SG::SG_GlovePose glovePose;
			if (testGlove.GetGlovePose(glovePose))
			{
				//As an example, lets calculate fingertip positions.

				//If we wish to calculate hand variables, we need a "hand profile" to tell the Sense Glove our hand lengths.
				SGCore::SG::SG_HandProfile handProfile = SGCore::SG::SG_HandProfile::Default(testGlove.IsRight()); //create a default profile, either left or right.
				/*SGCore::HandProfile handProfile = SGCore::HandProfile::Default(testGlove.IsRight()); //a default profile for the right-sided glove.
				testGlove.ApplyCalibration(handProfile); //create a default profile, either left or right.*/
				
				SGCore::Kinematics::BasicHandModel handModel = SGCore::Kinematics::BasicHandModel::Default(testGlove.IsRight()); //create a default profile, either left or right.
				std::vector<SGCore::Kinematics::Vect3D> tipPositions=glovePose.CalculateFingerTips(handProfile);; //calculates fingertip position


				std::cout << std::endl;

				for (int f = 0; f < tipPositions.size(); f++)
					std::cout << std::to_string(((SGCore::Finger)f)) << ": " << tipPositions[f].ToString() << std::endl; //writes "thumb: ", "index: " etc.

				float dThumbIndex = tipPositions[0].DistTo(tipPositions[1]); //calculates the distance between thumb (0) and index finger (1), in mm.
				std::cout << "The distance between thumb and index finger is " << std::to_string(dThumbIndex) << "mm." << std::endl;

				//HandPose Example

				SGCore::HandPose handPose;
				if (testGlove.GetHandPose(handModel, handProfile, handPose))
				{
					std::cout << std::endl;
					std::cout << "Calculated Hand Pose: " << std::endl << handPose.ToString() << std::endl;
				}
				else
				{
					std::cout << "Could not retrieve a hand pose" << std::endl;
				}
			}


			// Now we apply the calibration to a default profile
			SGCore::HandProfile cachedProfile = SGCore::HandProfile::Default(testGlove.IsRight()); //a default profile for the right-sided glove.
			testGlove.ApplyCalibration(cachedProfile);

			std::cout << std::endl;
			std::cout << "Step 3: Make any pose with your hand." << std::endl;
			std::cout << "Once your hand is in the right position, press any key to calculate it." << std::endl;
			system("pause");


			// And can now use it to calculate handPoses
			SGCore::HandPose handPose;
			if (testGlove.GetHandPose(cachedProfile, handPose))
			{
				std::cout << std::endl << "With these ranges, we've calculated the following hand angles:" << std::endl;
				std::cout << handPose.ToString() << std::endl;
			}
			else
			{
				std::cout << "Something went wrong while trying to calucate a handPose. Perhaps a packet was dropped or an exception occurs." << std::endl;
			}
			// Finally, we can store the profile in its serialized form to use later
			std::string serializedProfile = cachedProfile.Serialize();
			
			// And Deserialize it back into a useable profile
			SGCore::HandProfile loadedProfile = SGCore::HandProfile::Deserialize(serializedProfile);


		
		}
		else
		{
			std::cout << "SenseComm is not running. Please start it and try again." << std::endl;
		}
		std::cout << "=======================================" << std::endl;
		std::cout << "Press any key to exit." << std::endl;
		system("pause");

	}
}