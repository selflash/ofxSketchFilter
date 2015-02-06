#pragma once

#include <ofMain.h>

namespace ns_ofxSketchFilter {
    
    class GaussianBlurFilter {
        public:
            
        protected:
        
        private:
            int _bufferWidth;
            int _bufferHeight;
        
            ofShader _shader1;
            ofShader _shader2;
        
            ofFbo _destination1;
            ofFbo _destination2;
        
            float _sigma;
            float _horizontalBlurSize;
            float _verticalBlurSize;
        
        public:
            GaussianBlurFilter();
            ~GaussianBlurFilter();
            
            void setup(int width, int height, int internalformat = GL_RGBA);
            void draw();
        
            void begin();
            void end();
        
            void resize(int width, int height, int internalformat = GL_RGBA);
        
            inline ofFbo& result() { return _destination2; }

            //--------------------------------------
            const float sigma();
            void sigma(float value);
        
            const float horizontalBlurSize();
            void horizontalBlurSize(float value);
        
            const float verticalBlurSize();
            void verticalBlurSize(float value);
            //--------------------------------------

        protected:
        
        private:
            void _allocate(int width, int height, int internalformat = GL_RGBA);
        
    };

}