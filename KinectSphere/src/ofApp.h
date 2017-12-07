#pragma once

#include "ofxGui.h"
#include "ofMain.h"
#include "ofxKinect.h"
#include "DepthProcessor.h"
#include "ofxCv.h"


class ofApp: public ofBaseApp
{
public:
	void setup() override;
	void update() override;
    void draw() override;
    void keyPressed(int key);
    
    //current state of the rotation
    ofQuaternion curRot;
    
    //a place to store the mouse position so we can measure incremental change
    ofVec2f lastMouse;
    ofVec2f lastPosition;
    
    //slows down the rotation 1 = 1 degree per pixel
    float dampen;
    float leftHand, rightHand;
    //ofxFloatSlider leftHand;
    //ofxFloatSlider rightHand;
    ofxPanel gui;
    // Kinect v1.
    ofxKinect kinect;

    // The Depth Processor
    DepthProcessor depthProcessor;
    ofPixels depthPixels;
    float brightnessLeft, brightnessRight;
    
    // Region of Interest
    ofRectangle rect;
    ofParameter<float> x, y, w, h;
    
    ofxCv::KalmanPosition leftKalman;
    ofxCv::KalmanPosition rightKalman;
};
