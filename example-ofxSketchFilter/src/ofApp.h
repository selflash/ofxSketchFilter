#pragma once

#include "ofMain.h"

#include "ofxSketchFilter.h"

class ofApp : public ofBaseApp {
    public:
        int videoWidth;
        int videoHeight;
        ofVideoGrabber videoGrabber;
        
        ofxSketchFilter sketchFilter;
        
    public:
        void setup();
        void update();
        void draw();
        
        void updateSource();
        
        void keyPressed(int key);
        void keyReleased(int key);
        void mouseMoved(int x, int y );
        void mouseDragged(int x, int y, int button);
        void mousePressed(int x, int y, int button);
        void mouseReleased(int x, int y, int button);
        void windowResized(int w, int h);
        void dragEvent(ofDragInfo dragInfo);
        void gotMessage(ofMessage msg);
        
    protected:
        
    private:
    
};
