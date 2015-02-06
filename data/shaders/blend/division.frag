#version 120
//#extension GL_ARB_texture_rectangle : enable

uniform sampler2D u_base;
uniform sampler2D u_blend;

//UV値
varying vec2 v_texCoord;

//--------------------------------------------------------------
//
void main(void) {
    vec4 base = texture2D(u_base, v_texCoord);
    float a = base.a;

    vec4 blend = texture2D(u_blend, v_texCoord);
    
    vec3 compose = base.rgb / blend.rgb;
    //Comment out if you need
    compose = compose * compose * compose * compose * compose;
    vec4 finalColor = vec4(compose, a);
    gl_FragColor = finalColor;
}