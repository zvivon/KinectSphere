#pragma once

#include "ofxGui.h"
#include "ofMain.h"
#include "ofxKinect.h"
#include "DepthProcessor.h"


class ofApp: public ofBaseApp
{
public:
	void setup() override;
	void update() override;
    void draw() override;

    // Kinect v1.
    ofxKinect kinect;

    // The Depth Processor
    DepthProcessor depthProcessor;
    ofPixels depthPixels;
    
    
};
