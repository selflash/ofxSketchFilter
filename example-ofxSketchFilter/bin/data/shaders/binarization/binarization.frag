#version 120
//#extension GL_ARB_texture_rectangle : enable

uniform sampler2D u_source;
uniform float u_threshold = 0.5;

//UV値
varying vec2 v_texCoord;

//--------------------------------------------------------------
//
void main(void) {
    vec4 source = texture2D(u_source, v_texCoord);
    float a = source.a;
    
    vec3 grayscale = vec3(source.r * 0.299 + source.g * 0.587 + source.b * 0.114);
    
    vec3 binarization = vec3(step(u_threshold, grayscale));
    vec4 finalColor = vec4(binarization, a);
    gl_FragColor = finalColor;
}