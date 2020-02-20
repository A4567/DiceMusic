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
    point.x = -ofGetWidth()/2;
    point.y = 0;
    radius = 10;
    rot = 0;
    //ofSetBackgroundAuto(false);
    ofSetBackgroundColor(0);
    specLow = -ofGetHeight()/2;
    specHigh = ofGetHeight()/2;
    specCol = 0;
    xStep = 1;
}

//--------------------------------------------------------------
void ofApp::update(){
  float *spectrum = ofSoundGetSpectrum(1);
    *spectrum = *spectrum;
    specMap = ofMap(*spectrum,-1,1,specLow,specHigh);
    specCol = ofMap(point.y,-ofGetHeight()/2,ofGetHeight()/2,10,255);
    color.setHsb(255, 255, 255,250);
  //  float test = *spectrum * 1000000;
 //  cout << specMap << endl;
}

//--------------------------------------------------------------
void ofApp::draw(){
  //  markov.draw(40, 60); // use the built in draw function to show coloured dots indicating the current transition
   
    int currentState;
    currentState = markov.getState(); // get the current state of the matrix
    if(!soundVector[currentState].isPlaying()){
       // soundVector[currentState].setVolume(0.0f);
        soundVector[currentState].play();
    }
    if(soundVector[currentState].getPosition() > 0.5){
//        rot = 0;
//        point.x = 0;
//        point.y = 0;
        soundVector[currentState].stop();
        markov.update();
    }
    switch(currentState){
        case 0:
           // point.y += soundVector[currentState].getPosition() * ofRandom(1, 100);
            point.y = specMap;
            rot += ofRandom(0,180);
            point.x += xStep;
            break;
        case 1:
          //  point.y -= soundVector[currentState].getPosition() * ofRandom(1, 100);
            point.y = specMap;

            rot += ofRandom(0,180);
            point.x += xStep;
            break;
        case 2:
//            point.x += soundVector[currentState].getPosition() * ofRandom(1, 100);
            rot -= ofRandom(0,180);
            point.x += xStep;
            point.y = specMap;
            break;
        case 3:
//            point.x -= soundVector[currentState].getPosition() * ofRandom(1, 100);
            rot -= ofRandom(0,180);
            point.x += xStep;
            point.y = specMap;
            break;
    }
//    ofSetColor(255); // write the current state to the screen
//    ofDrawBitmapString("Press space to step forward \nThe current item in Markov Chain is: " + ofToString( currentState) , 40, 20);
    
    ofPushMatrix();
    
    ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
    ofSetColor(255);
   
    if((point.x < -100)||(point.x > 100)||(point.y < -100)||(point.y > 100)){
     //   ofRotateZDeg(rot);
    }else{
       // ofRotateZDeg(-rot);
    }
//    for(int i = 0; i < markov.getStatesNumber(); i++){
//        ofSetColor(ofRandom(25,200), ofRandom(25,200), ofRandom(25,200), 50);
//        ofDrawCircle(point*(1+i), radius*(i+1));
//    }
    if(point.x > ofGetWidth()/2){
        point.x = -ofGetWidth()/2;
        specLow += 100;
        specHigh += 100;
    }
    if(point.y > ofGetHeight()/2){
        specLow = specLow - ofGetHeight();
        specLow += 25;
        specHigh = 25;
    }
    ofSetColor(color);
    ofDrawCircle(point, radius);

    ofPopMatrix();
}
//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == 'c'){
        //ofClear(0);
        rot = 0;
        point.x = 0;
        point.y = 0;
    }
}
