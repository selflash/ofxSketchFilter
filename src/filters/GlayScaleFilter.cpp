#include "GlayScaleFilter.h"

namespace ns_ofxSketchFilter {
    
    //==============================================================
    // CONSTRUCTOR / DESTRUCTOR
    //==============================================================

    //--------------------------------------------------------------
    //
    GlayScaleFilter::GlayScaleFilter() {
        cout << "[GlayScaleFilter]GlayScaleFilter()" << endl;
        
        _intensity = 1.0;
        
        _redCoefficient = 1.0;
        _greenCoefficient = 1.0;
        _blueCoefficient = 1.0;
        _alphaCoefficient = 1.0;
    }

    //--------------------------------------------------------------
    //
    GlayScaleFilter::~GlayScaleFilter() {
        cout << "[GlayScaleFilter]~GlayScaleFilter()" << endl;

        _intensity = 0.0;
        
        _redCoefficient = 0.0;
        _greenCoefficient = 0.0;
        _blueCoefficient = 0.0;
        _alphaCoefficient = 0.0;
    }

    //==============================================================
    // SETUP / UPDATE / DRAW
    //==============================================================

    //--------------------------------------------------------------
    //
    void GlayScaleFilter::setup(int width, int height, int internalformat) {
//        cout << "[GlayScaleFilter]setup()" << endl;
        
        _allocate(width, height, internalformat);
        
        //--------------------------------------
        //シェーダー
        _shader.load(
                     "shaders/grayscale/grayscale.vert",
                     "shaders/grayscale/grayscale.frag"
                     );
        _shader.begin();
        _shader.setUniform1i("u_source", 0);
        _shader.end();
        //--------------------------------------

        intensity(_intensity);
        
        redCoefficient(_redCoefficient);
        greenCoefficient(_greenCoefficient);
        blueCoefficient(_blueCoefficient);
        alphaCoefficient(_alphaCoefficient);
    }

    //--------------------------------------------------------------
    //
    void GlayScaleFilter::draw() {
//        cout << "[GaussianBlur]draw()" << endl;
        
        _destination.draw(0, 0);
    }

    //==============================================================
    // PUBLIC MEHTOD
    //==============================================================

    //--------------------------------------------------------------
    //
    void GlayScaleFilter::begin() {
    //    cout << "[GaussianBlur]begin()" << endl;
        
        //----------------------------------
        _destination.begin();
        glClearColor(0, 0, 0, 0);
        glClear(GL_COLOR_BUFFER_BIT);
        
        _shader.begin();
    }
    //--------------------------------------------------------------
    //
    void GlayScaleFilter::end() {
    //    cout << "[GaussianBlur]end()" << endl;
        
        _shader.end();
        
        _destination.end();
        //----------------------------------
    }

    //--------------------------------------------------------------
    //
    void GlayScaleFilter::resize(int width, int height, int internalformat) {
        _allocate(width, height, internalformat);
    }

    //==============================================================
    // SETTER / GETTER
    //==============================================================
        
    //--------------------------------------------------------------
    //
    const float GlayScaleFilter::intensity() { return _intensity; }
    void GlayScaleFilter::intensity(float value) {
        _intensity = value;
        if(_intensity < 0.0) _intensity = 0.0;
        if(_intensity > 1.0) _intensity = 1.0;
        
        _shader.begin();
        _shader.setUniform1f("u_intensity", _intensity);
        _shader.end();
    }

    //--------------------------------------------------------------
    //
    const float GlayScaleFilter::redCoefficient() { return _redCoefficient; }
    void GlayScaleFilter::redCoefficient(float value) {
        _redCoefficient = value;
        
        _shader.begin();
        _shader.setUniform1f("u_redCoefficient", _redCoefficient * _alphaCoefficient);
        _shader.end();
    }

    //--------------------------------------------------------------
    //
    const float GlayScaleFilter::greenCoefficient() { return _greenCoefficient; }
    void GlayScaleFilter::greenCoefficient(float value) {
        _greenCoefficient = value;
        
        _shader.begin();
        _shader.setUniform1f("u_greenCoefficient", _greenCoefficient * _alphaCoefficient);
        _shader.end();
    }

    //--------------------------------------------------------------
    //
    const float GlayScaleFilter::blueCoefficient() { return _blueCoefficient; }
    void GlayScaleFilter::blueCoefficient(float value) {
        _blueCoefficient = value;
        
        _shader.begin();
        _shader.setUniform1f("u_blueCoefficient", _blueCoefficient * _alphaCoefficient);
        _shader.end();
    }

    //--------------------------------------------------------------
    //
    const float GlayScaleFilter::alphaCoefficient() { return _blueCoefficient; }
    void GlayScaleFilter::alphaCoefficient(float value) {
        _alphaCoefficient = value;
        
        _shader.begin();
        _shader.setUniform1f("u_redCoefficient", _redCoefficient * _alphaCoefficient);
        _shader.setUniform1f("u_greenCoefficient", _greenCoefficient * _alphaCoefficient);
        _shader.setUniform1f("u_blueCoefficient", _blueCoefficient * _alphaCoefficient);
        _shader.end();
    }

    //==============================================================
    // PROTECTED / PRIVATE METHOD
    //==============================================================
        
    //--------------------------------------------------------------
    //
    void GlayScaleFilter::_allocate(int width, int height, int internalformat){
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
}