#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    // load and set up our transition matrix into the markov chain addOn
    ofxMC::Matrix matrix("transitionMatrix.txt");
    markov.setup(matrix, 0);
    ofSoundPlayer p1,p2,p3,p4;
    p1.load("c.mp3");
    p2.load("g.mp3");
    p3.load("d.mp3");
    p4.load("f.mp3");
    soundVector.push_back(p1);
    soundVector.push_back(p2);
    soundVector.push_back(p3);
    soundVector.push_back(p4);
}

//--------------------------------------------------------------
void ofApp::update(){
    
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    markov.draw(40, 60); // use the built in draw function to show coloured dots indicating the current transition
    
    int currentState;
    currentState = markov.getState(); // get the current state of the matrix
    if(!soundVector[currentState].isPlaying()){
        soundVector[currentState].play();
    }
    if(soundVector[currentState].getPosition() > 0.7){
        soundVector[currentState].stop();
        markov.update();
    }
    ofSetColor(255); // write the current state to the screen
    ofDrawBitmapString("Press space to step forward \nThe current item in Markov Chain is: " + ofToString( currentState) , 40, 20);
}
//--------------------------------------------------------------
void ofApp::keyPressed(int key){
}
