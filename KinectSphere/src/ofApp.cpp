#include "ofApp.h"


void ofApp::setup()
{
    ofNoFill();
    ofSetFrameRate(30);
    ofBackground(0);
    //this slows down the rotate a little bit
    dampen = .4;
    gui.setup();
    
    // Initialize filter.
    leftKalman.init(1/10000., 1/10.);
    rightKalman.init(1/10000., 1/10.);
    
    kinect.setRegistration(true);
    kinect.init();
    kinect.open();
}


void ofApp::update()
{
    kinect.update();
    if (kinect.isFrameNew())
    {
        depthPixels = kinect.getDepthPixels();
        depthProcessor.setRawDepthPixels(kinect.getRawDepthPixels());
        
    }
    float leftHand = ofMap(brightnessLeft, 190, 245, 10, 1000, true);
    glm::vec3 l = glm::vec3(leftHand, 0, 0);
    leftKalman.update(l);
//    leftHand = ofMap(aMapLeft, 10, 500, 10, 1200, true);
    std::cout << "leftHand: " << leftHand << std::endl;
    
    float rightHand = ofMap(brightnessRight, 190, 245, 10, 1000, true);
    glm::vec3 r = glm::vec3(rightHand, 0, 0);
    rightKalman.update(r);

//    rightHand = ofMap(aMapRight, 10, 500, 10, 1200, true);
    std::cout << "rightHand: " << rightHand << std::endl;
    
    glm::vec3 filteredL = leftKalman.getEstimation();
     glm::vec3 filteredR = rightKalman.getEstimation();
    ofVec2f currentPos(filteredL.x,filteredR.x);
    ofQuaternion yRot((currentPos.x-lastPosition.x)*dampen, ofVec3f(0,1,0));
    ofQuaternion xRot((currentPos.y-lastPosition.y)*dampen, ofVec3f(-1,0,0));
    curRot *= yRot*xRot;
    lastPosition = currentPos;
}

void ofApp::draw()
{
    //translate so that 0,0 is the center of the screen
    ofPushMatrix();
    ofTranslate(ofGetWidth()/2, ofGetHeight()/2, 40);
    //Extract the rotation from the current rotation
    ofVec3f axis;
    float angle;
    curRot.getRotate(angle, axis);
    
    //apply the quaternion's rotation to the viewport and draw the sphere
    ofRotateDeg(angle, axis.x, axis.y, axis.z);
    ofDrawSphere(0, 0, 0, 300);
    
    ofPopMatrix();
    
    std::vector<ofPolyline> contours = depthProcessor.contourFinder().getPolylines();
    
    
    for (int i = 0; i < contours.size(); i++)
    {
        if( i < 2 ){
            
            if(i < 1) {
                glm::vec2 center = contours[0].getCentroid2D();
                //int brightness = depthProcessor.getDepthAtPosition(center.x, center.y);
                brightnessLeft = depthPixels.getColor(center.x, center.y).getBrightness();
                int label = depthProcessor.getLabel(i);
                //std::cout << "Label: " << label << ", Brightness: " << brightnessLeft << endl;
                //contours[i].draw();
            }else{
                glm::vec2 center1 = contours[0].getCentroid2D();
                glm::vec2 center2 = contours[1].getCentroid2D();

                //int brightness = depthProcessor.getDepthAtPosition(center.x, center.y);
                brightnessLeft = depthPixels.getColor(center1.x, center1.y).getBrightness();
                std::cout << "brightnessLeft " << brightnessLeft << endl;

                brightnessRight = depthPixels.getColor(center2.x, center2.y).getBrightness();
                std::cout << "brightnessRight: " << brightnessRight << endl;
            }
        }
        
        
    }
    gui.draw();
}

void ofApp::keyPressed(int key) {
    if (key == 'r') {
        ofQuaternion yRot((0)*dampen, ofVec3f(0,1,0));
        ofQuaternion xRot((0)*dampen, ofVec3f(-1,0,0));
        curRot = yRot*xRot;
        lastPosition = glm::vec2(0, 0);
    }
}


