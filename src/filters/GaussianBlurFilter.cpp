#include "GaussianBlurFilter.h"

namespace ns_ofxSketchFilter {

    //==============================================================
    // CONSTRUCTOR / DESTRUCTOR
    //==============================================================

    //--------------------------------------------------------------
    //
    GaussianBlurFilter::GaussianBlurFilter() {
        cout << "[GaussianBlurFilter]GaussianBlurFilter()" << endl;
        
        _sigma = 1.0;
        _horizontalBlurSize = 0.0;
        _verticalBlurSize = 0.0;
    }

    //--------------------------------------------------------------
    //
    GaussianBlurFilter::~GaussianBlurFilter() {
        cout << "[GaussianBlurFilter]~GaussianBlurFilter()" << endl;
        
        _sigma = 0.0;
        _horizontalBlurSize = 0.0;
        _verticalBlurSize = 0.0;
    }

    //==============================================================
    // SETUP / UPDATE / DRAW
    //==============================================================

    //--------------------------------------------------------------
    //
    void GaussianBlurFilter::setup(int width, int height, int internalformat) {
    //    cout << "[GaussianBlurFilter]setup()" << endl;
        
        _allocate(width, height, internalformat);
        
        //--------------------------------------
        //シェーダー
        _shader1.load(
                      "shaders/gaussianBlur/gaussianBlurH.vert",
                      "shaders/gaussianBlur/gaussianBlurH.frag"
        );
        _shader2.load(
                       "shaders/gaussianBlur/gaussianBlurV.vert",
                       "shaders/gaussianBlur/gaussianBlurV.frag"
        );
        //--------------------------------------
        
        sigma(_sigma);
        horizontalBlurSize(_horizontalBlurSize);
        verticalBlurSize(_verticalBlurSize);
    }
    
    //--------------------------------------------------------------
    //
    void GaussianBlurFilter::draw() {
    //    cout << "[GaussianBlurFilter]draw()" << endl;
        
        _destination2.draw(0, 0);
    }

    //==============================================================
    // PUBLIC MEHTOD
    //==============================================================

    //--------------------------------------------------------------
    //
    void GaussianBlurFilter::begin() {
    //    cout << "[GaussianBlurFilter]begin()" << endl;
        
        //----------------------------------
        _destination1.begin();
        glClearColor(0, 0, 0, 0);
        glClear(GL_COLOR_BUFFER_BIT);
        
        _shader1.begin();
    }
    //--------------------------------------------------------------
    //
    void GaussianBlurFilter::end() {
    //    cout << "[GaussianBlurFilter]end()" << endl;
        
        _shader1.end();

        _destination1.end();
        //----------------------------------
        
        //----------------------------------
        _destination2.begin();
        glClearColor(0, 0, 0, 0);
        glClear(GL_COLOR_BUFFER_BIT);
        
        _shader2.begin();
        
        _destination1.draw(0, 0);

        _shader2.end();
        
        _destination2.end();
        //----------------------------------
    }

    //--------------------------------------------------------------
    //
    void GaussianBlurFilter::resize(int width, int height, int internalformat) {
        _allocate(width, height, internalformat);
    }

    //==============================================================
    // SETTER / GETTER
    //==============================================================

    //--------------------------------------------------------------
    //
    const float GaussianBlurFilter::sigma() { return _sigma; }
    void GaussianBlurFilter::sigma(float value) {
        _sigma = value;
        
        //----------------------------------
        _shader1.begin();
        _shader1.setUniform1f("u_sigma", _sigma);
        _shader1.end();
        //----------------------------------
        
        //----------------------------------
        _shader2.begin();
        _shader2.setUniform1f("u_sigma", _sigma);
        _shader2.end();
        //----------------------------------
    }

    //--------------------------------------------------------------
    //
    const float GaussianBlurFilter::horizontalBlurSize() { return _horizontalBlurSize; }
    void GaussianBlurFilter::horizontalBlurSize(float value) {
        _horizontalBlurSize = value;
        if(_horizontalBlurSize <= 0.0) _horizontalBlurSize = 0.0;
        
        //----------------------------------
        _shader1.begin();
        _shader1.setUniform1f("u_blurSize", _horizontalBlurSize);
        _shader1.end();
        //----------------------------------
    }

    //--------------------------------------------------------------
    //
    const float GaussianBlurFilter::verticalBlurSize() { return _verticalBlurSize; }
    void GaussianBlurFilter::verticalBlurSize(float value) {
        _verticalBlurSize = value;
        if(_verticalBlurSize <= 0.0) _verticalBlurSize = 0.0;
        
        //----------------------------------
        _shader2.begin();
        _shader2.setUniform1f("u_blurSize", _verticalBlurSize);
        _shader2.end();
        //----------------------------------
    }

    //==============================================================
    // PROTECTED / PRIVATE METHOD
    //==============================================================
        
    //--------------------------------------------------------------
    //
    void GaussianBlurFilter::_allocate(int width, int height, int internalformat){
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
        
        _destination1.allocate(settings);
        _destination1.begin();
        glClearColor(0, 0, 0, 0);
        glClear(GL_COLOR_BUFFER_BIT);
        _destination1.end();
        
        _destination2.allocate(settings);
        _destination2.begin();
        glClearColor(0, 0, 0, 0);
        glClear(GL_COLOR_BUFFER_BIT);
        _destination2.end();
    }

}