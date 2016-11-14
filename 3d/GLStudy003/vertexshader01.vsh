#ifdef GL_ES
precision highp float;
#endif

uniform mat4 u_modelViewMatrix;
uniform mat4 u_projectionMatrix;
uniform mat3 u_invModelViewMatrix;

uniform vec4 u_eyePosition;

uniform bool u_useTexture;
uniform sampler2D u_texture;

uniform bool u_lightEnabled;
uniform int u_lightCount;
uniform bool u_lightModeTwoSide;

struct LightState{
    vec4 position;
    vec4 ambientColor;
    vec4 diffuseColor;
    vec4 specularColor;
    vec4 spotDirection;
    float spotExponent;
    float spotCutOffAngle;
};
LightState u_lightState[8];

struct MaterialState{
    vec4 ambientColor;
    vec4 diffuseColor;
    vec4 specularColor;
};
MaterialState u_materialState;

attribute vec3 a_position;
attribute vec4 a_color;

varying vec3 v_normal;
varying vec4 v_color;
varying vec2 v_textureCoord;

void main(void)
{
    bool useMatrices = true;
    if( useMatrices ){
        gl_Position = u_projectionMatrix
                        * u_modelViewMatrix
                        * vec4( a_position, 1 );
    }
    else{
        gl_Position = vec4( a_position, 1 );
    }
    v_color = a_color;
}
