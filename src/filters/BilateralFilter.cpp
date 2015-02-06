#include "BilateralFilter.h"

namespace ns_ofxSketchFilter {
    
    //--------------------------------------------------------------
    //
    BilateralFilter::BilateralFilter() {
        
    }
    //--------------------------------------------------------------
    //
    BilateralFilter::~BilateralFilter() { }

    //--------------------------------------------------------------
    // SETUP / UPDATE / DRAW
    //--------------------------------------------------------------

    //--------------------------------------------------------------
    //
    void BilateralFilter::setup(
                                float w,
                                float h,
                                int internalFormat,
                                float blurOffset,
                                float normalization
                                ) {
        _width = w;
        _height = h;
        _internalFormat = internalFormat;
        _texelSpacing = ofVec2f(blurOffset, blurOffset);
        _normalization = normalization;
        
        _setupFbo();
        
        _shader.load("shaders/bilateral/bilateral");
    }

    //--------------------------------------------------------------
    // PUBLIC METHOD
    //--------------------------------------------------------------

    //--------------------------------------------------------------
    //
    void BilateralFilter::ping() {
        _pingFbo.begin();
        ofClear(0, 0, 0, 0);
    }

    //--------------------------------------------------------------
    //
    void BilateralFilter::pong() {
        _pingFbo.end();
        
        _pongFbo.begin();
        ofClear(0, 0, 0, 0);
        _pingFbo.draw(0, 0);
        _pongFbo.end();
    }

    //--------------------------------------------------------------
    //
    void BilateralFilter::begin() {
        _shader.begin();
        _shader.setUniform1f("texelWidthOffset", _texelSpacing.x / _width);
        _shader.setUniform1f("texelHeightOffset", 0.0);
        _shader.setUniform1f("distanceNormalizationFactor", _normalization);
        
        ping();
    }

    //--------------------------------------------------------------
    //
    void BilateralFilter::end() {
        _shader.setUniform1f("texelWidthOffset", 0.0);
        _shader.setUniform1f("texelHeightOffset", _texelSpacing.y / _height);
        _shader.setUniform1f("distanceNormalizationFactor", _normalization);
        
        pong();
        
        _shader.end();
    }

    //--------------------------------------------------------------
    //
    void BilateralFilter::draw() {
        _pongFbo.getTextureReference().draw(0, 0);
    }

    
    //--------------------------------------------------------------
    //
    void BilateralFilter::resize(int w, int h) {
        _width = w;
        _height = h;
        
        _setupFbo();
    }

    //--------------------------------------------------------------
    // PROTECTED / PRIVATE
    //--------------------------------------------------------------
    
    //--------------------------------------------------------------
    //
    void BilateralFilter::_setupFbo() {
        _pingFbo.allocate(_width, _height, _internalFormat);
        _pingFbo.begin();
        ofClear(0, 0, 0, 0);
        _pingFbo.end();
        
        _pongFbo.allocate(_width, _height, _internalFormat);
        _pongFbo.begin();
        ofClear(0, 0, 0, 0);
        _pongFbo.end();
    }
    
}

