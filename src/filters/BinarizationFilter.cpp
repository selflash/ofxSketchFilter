#include "BinarizationFilter.h"

namespace ns_ofxSketchFilter {

    //==============================================================
    // CONSTRUCTOR / DESTRUCTOR
    //==============================================================

    //--------------------------------------------------------------
    //
    BinarizationFilter::BinarizationFilter() {
        cout << "[BinarizationFilter]BinarizationFilter()" << endl;
        
        _threshold = 0.85;
    }

    //--------------------------------------------------------------
    //
    BinarizationFilter::~BinarizationFilter() {
        cout << "[BinarizationFilter]~BinarizationFilter()" << endl;
        
        _threshold = 0;
    }

    //==============================================================
    // SETUP / UPDATE / DRAW
    //==============================================================

    //--------------------------------------------------------------
    //
    void BinarizationFilter::setup(int width, int height, int internalformat) {
    //    cout << "[BinarizationFilter]_setup()" << endl;
        
        //--------------------------------------
        //シェーダー
        _shader.load(
                      "shaders/binarization/binarization.vert",
                      "shaders/binarization/binarization.frag"
        );
        //--------------------------------------
        
        threshold(_threshold);
        
        _allocate(width, height, internalformat);
    }

    //--------------------------------------------------------------
    //
    void BinarizationFilter::draw() {
    //    cout << "[BinarizationFilter]draw()" << endl;
        
        _destination.draw(0, 0);
    }

    //==============================================================
    // PUBLIC MEHTOD
    //==============================================================

    //--------------------------------------------------------------
    //
    void BinarizationFilter::begin() {
    //    cout << "[GaussianBlur]begin()" << endl;
        
        //----------------------------------
        _destination.begin();
        glClearColor(0, 0, 0, 0);
        glClear(GL_COLOR_BUFFER_BIT);
        
        _shader.begin();
    }
    //--------------------------------------------------------------
    //
    void BinarizationFilter::end() {
    //    cout << "[GaussianBlur]end()" << endl;
        
        _shader.end();
        
        _destination.end();
        //----------------------------------
    }

    //--------------------------------------------------------------
    //
    void BinarizationFilter::_allocate(int width, int height, int internalformat) {
        _bufferWidth = width;
        _bufferHeight = height;
        
        //----------------------------------
        ofFbo::Settings settings;
        settings.width = _bufferWidth;
        settings.height = _bufferHeight;
        settings.internalformat = internalformat;
//        settings.internalformat = GL_RGBA;
//        settings.internalformat = GL_RGBA16;
//        settings.internalformat = GL_RGB;
//        settings.numSamples = 0;
//        settings.useDepth = true;
//        settings.useStencil = true;
//        settings.depthStencilAsTexture = true;
//        settings.textureTarget = ofGetUsingArbTex() ? GL_TEXTURE_RECTANGLE_ARB : GL_TEXTURE_2D;
//        settings.textureTarget = GL_TEXTURE_RECTANGLE_ARB;
        //----------------------------------
        
        _destination.allocate(settings);
        _destination.begin();
        glClearColor(0, 0, 0, 0);
        glClear(GL_COLOR_BUFFER_BIT);
        _destination.end();
    }

    //--------------------------------------------------------------
    //
    void BinarizationFilter::resize(int width, int height, int internalformat) {
        _allocate(width, height, internalformat);
    }

    //==============================================================
    // SETTER / GETTER
    //==============================================================
        
    //--------------------------------------------------------------
    //
    const float BinarizationFilter::threshold() { return _threshold; }
    void BinarizationFilter::threshold(float value) {
        _threshold = value;
        if(_threshold <= 0.0) _threshold = 0.0;
        if(_threshold >= 1.0) _threshold = 1.0;
        
        //--------------------------------------
        _shader.begin();
        _shader.setUniform1f("u_threshold", _threshold);
        _shader.end();
        //--------------------------------------
    }

    //==============================================================
    // PROTECTED / PRIVATE METHOD
    //==============================================================

}