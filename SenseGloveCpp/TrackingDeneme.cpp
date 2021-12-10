#include <iostream> //Output to console

#include <thread>  //To pause the main() while vibrating
#include <chrono>  //To pause the thread for std::chrono::seconds

#include "Library.h"	// Access library details
#include "DeviceList.h" // Access devices and communication state
#include "SenseGlove.h" // SenseGlove interface through which we access data.
#include "Tracking.h"
    void Deneme(){
 //int main(){

     //If we wish to calculate hand variables, we need a "hand profile" to tell the Sense Glove our hand lengths.
     SGCore::SG::SenseGlove testGlove;
     SGCore::SG::SG_GlovePose glovePose;
     SGCore::SG::SG_HandProfile handProfile = SGCore::SG::SG_HandProfile::Default(testGlove.IsRight()); //create a default profile, either left or right.
     SGCore::Kinematics::BasicHandModel handModel = SGCore::Kinematics::BasicHandModel::Default(testGlove.IsRight()); //create a default profile, either left or right.
     std::vector<SGCore::Kinematics::Vect3D> tipPositions = glovePose.CalculateFingerTips(handProfile); //calculates fingertip position
     
     
     //static void Deneme() {
    SGCore::Tracking track;
    SGCore::PosTrackingHardware::ViveTracker;

   //Offsets
    //Vect3D sg_viveToAttach_Pos;
    SGCore::Kinematics::Vect3D myPosOffset = track.sg_viveToAttach_Pos;
    SGCore::Kinematics::Quat myRotOffset = track.sg_viveToAttach_Rot;


    std::vector<SGCore::Kinematics::Vect3D> myFingerVec= track.sg_fingerToGloveOrigin_Pos;
    

   //current positions
   // SGCore::Kinematics::Vect3D tipIndexPosition = tipPositions[1];

   // track.CalculateLocation(Kinematics::Vect3D trackedPos, Kinematics::Quat trackedRot, Kinematics::Vect3D posOffset, Kinematics::Quat rotOffset, Kinematics::Vect3D & newPos, Kinematics::Quat & newRot);

    for (int f = 0; f < myFingerVec.size(); f++)
        std::cout << std::to_string(((SGCore::Finger)f)) << ": " << myFingerVec[f].ToString() << std::endl; //writes "thumb: ", "index: " etc.

   // std::cout << "position: " << myvect.ToString() << std::endl;
    //std::cout <<"rotation: " << myquat.ToString() << std::endl;
}
    
     


