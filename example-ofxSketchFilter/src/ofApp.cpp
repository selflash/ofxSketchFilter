#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetVerticalSync(true);
	ofSetFrameRate(60);
    ofDisableArbTex();
    
    //------------------------------------
    videoWidth = 320;
    videoHeight = 240;
    
    videoGrabber.setDeviceID(0);
    videoGrabber.setDesiredFrameRate(60);
    videoGrabber.setVerbose(true);
    videoGrabber.initGrabber(videoWidth, videoHeight);
    //------------------------------------
    
    //----------------------------------
    sketchFilter.setup(ofGetWidth(), ofGetHeight());
    //----------------------------------
}

//--------------------------------------------------------------
void ofApp::update() {
    videoGrabber.update();
    if (videoGrabber.isFrameNew()) {
        sketchFilter.begin();
        
        ofPushMatrix();
        ofTranslate(ofGetWidth(), 0);
        ofScale(-1.0, 1.0);
        videoGrabber.draw(0, 0, ofGetWidth(), ofGetHeight());
        ofPopMatrix();
        
        sketchFilter.end();
    }
}

//--------------------------------------------------------------
void ofApp::draw() {
    sketchFilter.draw();
    
    //------------------------------------
    ofPushStyle();
    ofSetColor(255, 100, 100);
    string text = "";
    text += "'f'           : ofToggleFullscreen\n";
    text += "'1'           : bilateralEnabled = " + ofToString(sketchFilter.bilateralEnabled()) + "\n";
    text += "'2'           : fillEnabled = " + ofToString(sketchFilter.fillEnabled()) + "\n";
    text += "'3'           : lineBoldEnabled = " + ofToString(sketchFilter.lineBoldEnabled()) + "\n";
    text += "[When 'bilateralEnabled' is true.]\n";
    text += "'k' or 'm'    : bilateralNormalization = " + ofToString(sketchFilter.bilateralNormalization()) + "\n";
    text += "'l' or ','    : bilateralBlurOffset = " + ofToString(sketchFilter.bilateralBlurOffset()) + "\n";
    text += "[Always can change.]\n";
    text += "';' or '.'    : blurSize1 = " + ofToString(sketchFilter.horizontalBlurSize1()) + "\n";
    text += "[When 'lineBoldEnabled' is true.]\n";
    text += "':' or '/'    : blurSize2 = " + ofToString(sketchFilter.horizontalBlurSize2()) + "\n";
    text += "']' or '_'    : binarizationThreshold = " + ofToString(sketchFilter.binarizationThreshold()) + "\n";
    ofDrawBitmapString(text, 20, 20);
    ofPopStyle();
    //------------------------------------
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
    if(key == 'f') ofToggleFullscreen();
    
    if(key == '1') sketchFilter.bilateralEnabled(!sketchFilter.bilateralEnabled());
    if(key == '2') sketchFilter.fillEnabled(!sketchFilter.fillEnabled());
    if(key == '3') sketchFilter.lineBoldEnabled(!sketchFilter.lineBoldEnabled());
    
    if(key == 'k') sketchFilter.bilateralNormalization(sketchFilter.bilateralNormalization() + 0.1);
    if(key == 'm') sketchFilter.bilateralNormalization(sketchFilter.bilateralNormalization() - 0.1);
    
    if(key == 'l') sketchFilter.bilateralBlurOffset(sketchFilter.bilateralBlurOffset() + 0.1);
    if(key == ',') sketchFilter.bilateralBlurOffset(sketchFilter.bilateralBlurOffset() - 0.1);
    
    if(key == ';') {
        sketchFilter.horizontalBlurSize1(sketchFilter.horizontalBlurSize1() + 0.001);
        sketchFilter.verticalBlurSize1(sketchFilter.verticalBlurSize1() + 0.001);
    }
    if(key == '.') {
        sketchFilter.horizontalBlurSize1(sketchFilter.horizontalBlurSize1() - 0.001);
        sketchFilter.verticalBlurSize1(sketchFilter.verticalBlurSize1() - 0.001);
    }
    
    if(key == ':') {
        sketchFilter.horizontalBlurSize2(sketchFilter.horizontalBlurSize2() + 0.001);
        sketchFilter.verticalBlurSize2(sketchFilter.verticalBlurSize2() + 0.001);
    }
    if(key == '/') {
        sketchFilter.horizontalBlurSize2(sketchFilter.horizontalBlurSize2() - 0.001);
        sketchFilter.verticalBlurSize2(sketchFilter.verticalBlurSize2() - 0.001);
    }
    
    if(key == ']') sketchFilter.binarizationThreshold(sketchFilter.binarizationThreshold() + 0.01);
    if(key == '_') sketchFilter.binarizationThreshold(sketchFilter.binarizationThreshold() - 0.01);
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ) {
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {
    sketchFilter.resize(w, h);
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {
    
}
