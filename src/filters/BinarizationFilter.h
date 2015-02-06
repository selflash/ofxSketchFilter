#pragma once

#include <ofMain.h>

namespace ns_ofxSketchFilter {

    class BinarizationFilter {
        public:
            
        protected:
            
        private:
            int _bufferWidth;
            int _bufferHeight;
            
            ofShader _shader;
            ofFbo _destination;
        
            float _threshold;
        
        public:
            BinarizationFilter();
            ~BinarizationFilter();
        
            void setup(int width, int height, int internalformat = GL_RGBA);
            void draw();
            
            void begin();
            void end();
        
            void resize(int width, int height, int internalformat = GL_RGBA);
            
            inline ofFbo& result() { return _destination; }
        
            //--------------------------------------
            const float threshold();
            void threshold(float value);
            //--------------------------------------
        
        protected:
        
        private:
            void _allocate(int width, int height, int internalformat = GL_RGBA);
    };

}