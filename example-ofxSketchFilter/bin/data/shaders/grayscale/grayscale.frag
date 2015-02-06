#version 120
//#extension GL_ARB_texture_rectangle : enable

uniform sampler2D u_source;

uniform float u_intensity = 1.0;
uniform float u_redCoefficient = 1.0;
uniform float u_greenCoefficient = 1.0;
uniform float u_blurCoefficient = 1.0;

//UV値
varying vec2 v_texCoord;

//--------------------------------------------------------------
//
void main(void) {
    vec4 source = texture2D(u_source, v_texCoord);
    float a = source.a;
    
    vec3 grayscale = vec3(source.r * 0.299 + source.g * 0.587 + source.b * 0.114);
    grayscale.r *= u_redCoefficient;
    grayscale.g *= u_greenCoefficient;
    grayscale.b *= u_blurCoefficient;
    
    vec3 compose = (grayscale * u_intensity) + (source.rgb * (1.0 - u_intensity));

    vec4 finalColor = vec4(compose, a);
    gl_FragColor = finalColor;
}