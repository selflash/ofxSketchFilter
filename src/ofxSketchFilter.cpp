#include "ofxSketchFilter.h"

//--------------------------------------------------------------
//
ofxSketchFilter::ofxSketchFilter() {
    _bilateralEnabled = false;
    _fillEnabled = false;
    _lineBoldEnabled = false;
}
//--------------------------------------------------------------
//
ofxSketchFilter::~ofxSketchFilter() {
    _bilateralEnabled = false;
    _fillEnabled = false;
    _lineBoldEnabled = false;
}

//--------------------------------------------------------------
// SETUP / UPDATE / DRAW
//--------------------------------------------------------------

//--------------------------------------------------------------
void ofxSketchFilter::setup(int width, int height) {
    int w = width;
    int h = height;
    
    //----------------------------------
    ofFbo::Settings settings;
    settings.width = w;
    settings.height = h;
    settings.numSamples = 8;
//    settings.textureTarget = GL_TEXTURE_RECTANGLE_ARB;
    
    _sourceFbo.allocate(settings);
    _sourceFbo.begin();
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);
    _sourceFbo.end();
    
    _tempFbo.allocate(settings);
    _tempFbo.begin();
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);
    _tempFbo.end();
    
    _distinationFbo.allocate(settings);
    _distinationFbo.begin();
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);
    _distinationFbo.end();
    //----------------------------------
    
    //----------------------------------
    //Bilateral Filter
    _bilateralFilter.setup(w, h, 4, 4);
    
    //Gray scale
    _glayScaleFilter.setup(w, h);
    
    //Gaussian blur
    _gaussianBlurFilter1.setup(w, h);
//    _gaussianBlurFilter1.horizontalBlurSize(5.9);
//    _gaussianBlurFilter1.verticalBlurSize(5.9);
    _gaussianBlurFilter1.horizontalBlurSize(_gaussianBlurFilter1.horizontalBlurSize() + 0.001);
    _gaussianBlurFilter1.verticalBlurSize(_gaussianBlurFilter1.verticalBlurSize() + 0.001);

    _gaussianBlurFilter2.setup(w, h);
//    _gaussianBlurFilter2.horizontalBlurSize(2.8);
//    _gaussianBlurFilter2.verticalBlurSize(2.8);
    
    //Binarization
    _binarizationFilter.setup(w, h);
    _binarizationFilter.threshold(0.95);
    
    //Division
    _divisionShader.load("shaders/blend/division");
    //Luminosity
    _luminosityShader.load("shaders/blend/luminosity");
    //----------------------------------
    
    _bilateralEnabled = false;
    _lineBoldEnabled = false;
}

//--------------------------------------------------------------
void ofxSketchFilter::draw() {
    _distinationFbo.draw(0, 0);
    
//    _luminosityShader.begin();
//    _luminosityShader.setUniformTexture("u_blend", _distinationFbo.getTextureReference(), 1);
//    
//    _sourceFbo.draw(0, 0);
//    
//    _luminosityShader.end();
}

//--------------------------------------------------------------
// PUBLIC METHOD
//--------------------------------------------------------------

//--------------------------------------------------------------
//
void ofxSketchFilter::begin() {
    _sourceFbo.begin();
    ofClear(0, 0, 0, 1);
}

//--------------------------------------------------------------
//
void ofxSketchFilter::end() {
    _sourceFbo.end();
    
    if(!_lineBoldEnabled) {
        _applyEffects1();
    } else {
        _applyEffects2();
    }
}

//--------------------------------------------------------------
//
void ofxSketchFilter::resize(int width, int height) {
    int w = width;
    int h = height;
    
    //----------------------------------
    ofFbo::Settings settings;
    settings.width = w;
    settings.height = h;
    settings.numSamples = 8;
//    settings.textureTarget = GL_TEXTURE_RECTANGLE_ARB;
    
    _sourceFbo.allocate(settings);
    _sourceFbo.begin();
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);
    _sourceFbo.end();
    
    _tempFbo.allocate(settings);
    _tempFbo.begin();
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);
    _tempFbo.end();
    
    _distinationFbo.allocate(settings);
    _distinationFbo.begin();
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);
    _distinationFbo.end();
    //----------------------------------
    
    _bilateralFilter.resize(w, h);

    _glayScaleFilter.resize(w, h);
    _gaussianBlurFilter1.resize(w, h);
    _gaussianBlurFilter2.resize(w, h);

    _binarizationFilter.resize(w, h);
}

//--------------------------------------------------------------
// PROTECTED / PRIVATE METHOD
//--------------------------------------------------------------

//--------------------------------------------------------------
//
void ofxSketchFilter::_applyEffects1() {
    //------------------------------------
    _bilateralFilter.begin();
    
    _sourceFbo.draw(0, 0);
    
    _bilateralFilter.end();
    //------------------------------------
    
    //------------------------------------
    _glayScaleFilter.begin();
    
    if(_bilateralEnabled) {
        _bilateralFilter.draw();
    } else {
        _sourceFbo.draw(0, 0);
    }
    
    _glayScaleFilter.end();
    //------------------------------------
    
    //------------------------------------
    _gaussianBlurFilter1.begin();
    
    _glayScaleFilter.draw();
    
    _gaussianBlurFilter1.end();
    //------------------------------------
    
    if(_fillEnabled) {
        //------------------------------------
        _tempFbo.begin();
        glClearColor(0, 0, 0, 0);
        glClear(GL_COLOR_BUFFER_BIT);
        
        _divisionShader.begin();
        _divisionShader.setUniformTexture("u_blend", _gaussianBlurFilter1.result().getTextureReference(), 1);
        
        _glayScaleFilter.result().draw(0, 0);
        
        _divisionShader.end();
        
        _tempFbo.end();
        //------------------------------------
        
        //------------------------------------
        _distinationFbo.begin();
        glClearColor(0, 0, 0, 0);
        glClear(GL_COLOR_BUFFER_BIT);
        
        _luminosityShader.begin();
        _luminosityShader.setUniformTexture("u_blend", _tempFbo.getTextureReference(), 1);
        
        _sourceFbo.draw(0, 0);
        
        _luminosityShader.end();
        
        _distinationFbo.end();
        //------------------------------------
    } else {
        //------------------------------------
        _distinationFbo.begin();
        glClearColor(0, 0, 0, 0);
        glClear(GL_COLOR_BUFFER_BIT);
        
        _divisionShader.begin();
        _divisionShader.setUniformTexture("u_blend", _gaussianBlurFilter1.result().getTextureReference(), 1);
        
        _glayScaleFilter.result().draw(0, 0);
        
        _divisionShader.end();
        
        _distinationFbo.end();
        //------------------------------------
    }
}

//--------------------------------------------------------------
//
void ofxSketchFilter::_applyEffects2() {
    //------------------------------------
    _bilateralFilter.begin();
    
    _sourceFbo.draw(0, 0);
    
    _bilateralFilter.end();
    //------------------------------------
    
    //------------------------------------
    _glayScaleFilter.begin();
    
    if(_bilateralEnabled) {
        _bilateralFilter.draw();
    } else {
        _sourceFbo.draw(0, 0);
    }
    
    _glayScaleFilter.end();
    //------------------------------------
    
    //------------------------------------
    _gaussianBlurFilter1.begin();
    
    _glayScaleFilter.draw();
    
    _gaussianBlurFilter1.end();
    //------------------------------------
    
    //------------------------------------
    _distinationFbo.begin();
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);
    
    _divisionShader.begin();
    _divisionShader.setUniformTexture("u_blend", _gaussianBlurFilter1.result().getTextureReference(), 1);
    
    _glayScaleFilter.result().draw(0, 0);
    
    _divisionShader.end();
    
    _distinationFbo.end();
    //------------------------------------
    
    //------------------------------------
    _gaussianBlurFilter2.begin();
    _distinationFbo.draw(0, 0);
    _gaussianBlurFilter2.end();
    //------------------------------------
    
    //------------------------------------
    _binarizationFilter.begin();
    _gaussianBlurFilter2.draw();
    _binarizationFilter.end();
    //------------------------------------
    
    //------------------------------------
    _distinationFbo.begin();
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);
    
    _binarizationFilter.draw();
    
    _distinationFbo.end();
    //------------------------------------
}