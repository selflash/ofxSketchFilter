#pragma once

#include "BilateralFilter.h"
#include "GlayScaleFilter.h"
#include "GaussianBlurFilter.h"
#include "BinarizationFilter.h"

typedef ns_ofxSketchFilter::BilateralFilter BilateralFilter;
typedef ns_ofxSketchFilter::GlayScaleFilter GlayScaleFilter;
typedef ns_ofxSketchFilter::GaussianBlurFilter GaussianBlurFilter;
typedef ns_ofxSketchFilter::BinarizationFilter BinarizationFilter;

class ofxSketchFilter {
    public:
        
    protected:
        
    private:
        ofFbo _sourceFbo;
        ofFbo _tempFbo;
        ofFbo _distinationFbo;

        BilateralFilter _bilateralFilter;
        GlayScaleFilter _glayScaleFilter;
        GaussianBlurFilter _gaussianBlurFilter1;
        GaussianBlurFilter _gaussianBlurFilter2;
        ofShader _divisionShader;
        BinarizationFilter _binarizationFilter;

        ofShader _luminosityShader;

        bool _bilateralEnabled;
        bool _fillEnabled;
        bool _lineBoldEnabled;

    public:
        ofxSketchFilter();
        ~ofxSketchFilter();

        void setup(int width, int height);
        void draw();
        
        void begin();
        void end();
    
        void resize(int width, int height);

        inline bool bilateralEnabled() { return _bilateralEnabled; }
        inline void bilateralEnabled(bool value) { _bilateralEnabled = value; }

        inline bool fillEnabled() { return _fillEnabled; }
        inline void fillEnabled(bool value) { _fillEnabled = value; }

        inline bool lineBoldEnabled() { return _lineBoldEnabled; }
        inline void lineBoldEnabled(bool value) { _lineBoldEnabled = value; }

        inline float bilateralNormalization() { return _bilateralFilter.normalization(); }
        inline void bilateralNormalization(float value) { _bilateralFilter.normalization(value); }
        
        inline float bilateralBlurOffset() { return _bilateralFilter.blurOffset(); }
        inline void bilateralBlurOffset(float value) { _bilateralFilter.blurOffset(value); }

        inline float horizontalBlurSize1() { return _gaussianBlurFilter1.horizontalBlurSize(); }
        inline void horizontalBlurSize1(float value) { _gaussianBlurFilter1.horizontalBlurSize(value); }
    
        inline float verticalBlurSize1() { return _gaussianBlurFilter1.verticalBlurSize(); }
        inline void verticalBlurSize1(float value) { _gaussianBlurFilter1.verticalBlurSize(value); }

        inline float horizontalBlurSize2() { return _gaussianBlurFilter2.horizontalBlurSize(); }
        inline void horizontalBlurSize2(float value) { _gaussianBlurFilter2.horizontalBlurSize(value); }
        
        inline float verticalBlurSize2() { return _gaussianBlurFilter2.verticalBlurSize(); }
        inline void verticalBlurSize2(float value) { _gaussianBlurFilter2.verticalBlurSize(value); }

        inline float binarizationThreshold() { return _binarizationFilter.threshold(); }
        inline void binarizationThreshold(float value) { _binarizationFilter.threshold(value); }

    protected:
    
    private:
        void _applyEffects1();
        void _applyEffects2();
    
};
