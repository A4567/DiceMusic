#pragma once

#include "ofMain.h"
#include "ofxMarkovChain.h"


class ofApp : public ofBaseApp{

    public:
        void setup();
        void update();
        void draw();

        void keyPressed(int key);

    // make a new markov chain object using the new type from the markov addon
     ofxMC::MarkovChain markov;
    vector<ofSoundPlayer> soundVector;
    ofVec3f point;
    int radius;
    int rot;
};
