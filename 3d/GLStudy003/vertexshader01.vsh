#ifdef GL_ES
precision highp float;
#endif

const float C_ZERO = 0.0;
const float C_ONE  = 1.0;

uniform mat4 u_modelViewMatrix;
uniform mat4 u_projectionMatrix;

uniform vec4 u_eyePosition; // in world space

uniform bool u_useTexture;
uniform sampler2D u_texture;

uniform bool u_lightEnabled;
uniform int u_lightCount;
uniform bool u_lightModeTwoSide;

struct LightState{
    vec4 position;      // in world space
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
    vec4 specularExponent;
};
MaterialState u_materialState;

attribute vec3 a_position;
attribute vec3 a_normal;
attribute vec4 a_color;

varying vec3 v_normal;
varying vec4 v_frontColor;
varying vec4 v_backColor;
//varying vec2 v_textureCoord;

vec4 positionInVeiw;
vec3 normalInView;
vec4 ambientColor;
vec4 diffuseColor;

vec4 ligtingEquation(int i)
{
    vec4 computedColor = vec4(C_ZERO,C_ZERO,C_ZERO,C_ZERO);
    vec3 halfVector;
    float ndotl, ndoth;
    vec3 lightDirection; // in view space
    float spotFactor = C_ONE;

//    if( u_lightState[i].position.w != C_ZERO ){
//        // spot light
//        lightDirection = u_modelViewMatrix * u_lightState[i].position - positionInVeiw;
//        if( u_lightState[i].spotCutOffAngle < 180.0 ){
//            spotFactor = dot(-lightDirection,
//                             u_modelViewMatrix * u_lightState[i].spotDirection);
//            if( spotFactor > cos(radians(u_lightState[i].spotCutOffAngle)) ){
//                spotFactor = pow(spotFactor, u_lightState[i].spotExponent);
//            }
//            else{
//                spotFactor = C_ZERO;
//            }
//        }
//    }
//    else{
//        // directional light
//        lightDirection = u_modelViewMatrix * u_lightState[i].position;
//    }
//    lightDirection = normalize(lightDirection);

    if( spotFactor > 0 ){
        computedColor += (u_lightState[i].ambientColor * ambientColor);
        ndotl = max(C_ZERO,dot(normalInView, lightDirection));
        computedColor += (ndotl * u_lightState[i].diffuseColor * diffuseColor);
        halfVector = normalize(lightDirection + vec4(C_ZERO,C_ZERO,C_ZERO));
        ndoth = dot(normalInView,halfVector);
        if( ndoth > C_ZERO ){
            computedColor += (pow(ndoth, u_materialState.specularExponent)
                              * u_materialState.specularColor
                              * u_lightState[i].specularColor);
        }
        computedColor *= spotFactor;
    }
    return computedColor;
}

vec4 doLignthing()
{
    vec4 vertexColor;

    vertexColor = vec4(C_ZERO,C_ZERO,C_ZERO,C_ZERO);
    for( int i = 0; i < 8; i++ ){
        if( i > u_lightCount )
            break;
        vertexColor += ligtingEquation(i);
    }
    vertexColor.a = diffuseColor.a;
    return vertexColor;
}

void main(void)
{
    positionInVeiw = (u_modelViewMatrix * vec4(a_position,1.0));
    normalInView = normalize(u_modelViewMatrix * vec4(a_normal,1.0));

    if( u_lightEnabled ){
        ambientColor = a_color;
        diffuseColor = a_color;
        v_frontColor = doLignthing();
        v_backColor = v_frontColor;
        if( u_lightModeTwoSide ){
            normalInView = - normalInView;
            v_backColor = doLignthing();
        }
    }
    else{
        v_frontColor = a_color;
        v_backColor = a_color;
    }

    gl_Position = u_projectionMatrix
                    * u_modelViewMatrix
                    * vec4(a_position,1.0);
}
