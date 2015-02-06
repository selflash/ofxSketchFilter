#pragma once

#include <ofMain.h>

namespace ns_ofxSketchFilter {
    
    class GlayScaleFilter {
        public:
            
        protected:
            
        private:
            int _bufferWidth;
            int _bufferHeight;
            
            ofShader _shader;
            ofFbo _destination;
        
            float _intensity;
            float _redCoefficient;
            float _greenCoefficient;
            float _blueCoefficient;
            float _alphaCoefficient;
        
        public:
            GlayScaleFilter();
            ~GlayScaleFilter();
        
            void setup(int width, int height, int internalformat = GL_RGBA);
            void draw();
        
            void begin();
            void end();
        
            void resize(int width, int height, int internalformat = GL_RGBA);

            inline ofFbo result() { return _destination; }
        
            //----------------------------------
            const float intensity();
            void intensity(float value);
            
            const float redCoefficient();
            void redCoefficient(float value);
            
            const float greenCoefficient();
            void greenCoefficient(float value);

            const float blueCoefficient();
            void blueCoefficient(float value);
        
            const float alphaCoefficient();
            void alphaCoefficient(float value);
            //----------------------------------

        protected:
        
        private:
            void _allocate(int width, int height, int internalformat = GL_RGBA);

    };

}