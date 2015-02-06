#pragma once

#include <ofMain.h>

namespace ns_ofxSketchFilter {
    
    class BilateralFilter {
        public:
            
        protected:

        private:
            float _width;
            float _height;
            ofVec2f _texelSpacing;
            float _normalization;
            int _internalFormat;
        
            ofShader _shader;
        
            ofFbo _pingFbo;
            ofFbo _pongFbo;
        
        public:
            BilateralFilter();
            ~BilateralFilter();

            void setup(
                       float width,
                       float height,
                       int internalFormat = GL_RGBA,
                       float blurOffset = 4.0,
                       float normalization = 6.0
                       );

            void ping();
            void pong();

            void begin();
            void end();
            void draw();
        
            void resize(int w, int h);

            inline float width() { return _width; }
            inline void width(float width) {
                _width = width;
                _setupFbo();
            }
        
            inline float height() { return _height; }
            inline void height(float height) {
                _height = height;
                _setupFbo();
            }

            inline float normalization() { return _normalization; }
            inline void normalization(float value) { _normalization = value; }

            inline float blurOffset() { return _texelSpacing.x; }
            inline void blurOffset(float blurOffset) { _texelSpacing = ofVec2f(blurOffset, blurOffset); }
        
            inline ofShader& shader() { return _shader; }
        
            inline ofFbo& pingFbo() { return _pingFbo; }
            inline ofFbo& pongFbo() { return _pongFbo; }
        
            virtual ofTexture& getTextureReference() { return _pongFbo.getTextureReference(); }
        
        protected:

        private:
            void _setupFbo();
        
    };
    
}
