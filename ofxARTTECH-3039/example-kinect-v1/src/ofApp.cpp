#include "ofApp.h"


void ofApp::setup()
{
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
}


void ofApp::draw()
{
    std::vector<ofPolyline> contours = depthProcessor.contourFinder().getPolylines();
    
    ofSetColor(ofColor::yellow);
    for (int i = 0; i < contours.size(); i++)
    {
        glm::vec2 center = contours[i].getCentroid2D();
        //int brightness = depthProcessor.getDepthAtPosition(center.x, center.y);
        int brightness = depthPixels.getColor(center.x, center.y).getBrightness();
        int label = depthProcessor.getLabel(i);
        std::cout << "Label: " << label << ", Brightness: " << brightness << endl;
        //contours[i].draw();
    }
    
}


