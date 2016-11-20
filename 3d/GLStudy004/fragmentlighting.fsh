#ifdef GL_ES
precision mediump float;
#endif

const float C_ZERO = 0.0;
const float C_ONE = 1.0;

struct Light {
    vec3 position;  // in world space.
    vec4 ambient;
    vec4 diffuse;
    vec4 specular;
    bool spotEnabled;
    vec3 spotDirection;
    float spotCutOff;
    float spotExponent;
    bool attenuationEnabled;
    vec3 attenuationFactor;
};

struct Material {
//    vec4 ambient;
//    vec4 diffuse;
    vec4 specular;
    float shininess;
};

uniform vec3 u_eyePosition; // in world space.

uniform int u_lightCount;
uniform Light u_light[8];
uniform Material u_material;

varying vec3 v_position;    // in world space.
varying vec3 v_normal;      // in World space.
varying vec4 v_color;

vec4 calcAmbient(
        int lightId,
        vec4 materialAmbient )
{
    return u_light[lightId].ambient * materialAmbient;
}

vec4 calcDiffuse(
        int lightId,
        vec3 normal,
        vec3 lightDirection,
        vec4 materialDiffuse )
{
    float ndotl = max( C_ZERO, dot(normal, lightDirection) );
    return ndotl * u_light[lightId].diffuse * materialDiffuse;
}

vec4 calcSpecular(
        int lightId,
        vec3 normal,
        vec3 lightDirection )
{
    vec4 color = vec4( C_ZERO, C_ZERO, C_ZERO, C_ZERO );
    vec3 eyeDirection = normalize( u_eyePosition - v_position );
    vec3 halfPlane = normalize( lightDirection + eyeDirection );
    float ndoth = dot( normal, halfPlane );
    if( ndoth > C_ZERO ){
        color = ( pow( ndoth, u_material.shininess)
                    * u_light[lightId].specular * u_material.specular );
    }
    return color;
}

float calcAttenuation(
        int lightId,
        float lightDistanceP2,
        vec3 lightDirection )
{
    float attenuation = C_ONE;
    if( u_light[lightId].attenuationEnabled ){
        vec3 distance;
        distance.x = C_ONE;
        distance.z = lightDistanceP2;
        distance.y = sqrt( distance.z );
        attenuation =
                C_ONE / dot( distance, u_light[lightId].attenuationFactor );
    }
    return attenuation;
}

float calcSpotFactor(
        int lightId,
        vec3 normal,
        vec3 lightDirection )
{
    float spotFactor = C_ONE;
    if( u_light[lightId].spotEnabled ){
        if( dot(normal, lightDirection) > 0.0 ) {
            if( u_light[lightId].spotCutOff < 180.0 ){
                spotFactor = dot( lightDirection, - normalize(u_light[lightId].spotDirection) );
                if( spotFactor >= cos( radians(u_light[lightId].spotCutOff) ) ){
                    spotFactor = pow( spotFactor, u_light[lightId].spotExponent );
                }
                else{
                    spotFactor = C_ZERO;
                }
            }
        }
    }
    return spotFactor;
}

vec4 calcOneLight(
        int lightId,
        vec3 normal,
        vec4 materialAmbient,
        vec4 materialDiffuse )
{
    vec4 color = vec4( C_ZERO, C_ZERO, C_ZERO, C_ZERO );

    vec3 lightDirection = ( u_light[lightId].position - v_position );
    float lightDistanceP2 = dot( lightDirection, lightDirection );
    lightDirection = normalize( lightDirection );
    float attenuation = calcAttenuation( lightId, lightDistanceP2, lightDirection );
    float spotFactor = calcSpotFactor( lightId, normal, lightDirection );

    if( attenuation * spotFactor > C_ZERO ){
//    if( spotFactor > C_ZERO ){
        color =
            calcAmbient( lightId, materialAmbient )
            + calcDiffuse( lightId, normal, lightDirection, materialDiffuse )
            + calcSpecular( lightId, normal, lightDirection );
        color = color * attenuation * spotFactor;
//        color = color * spotFactor;
    }
    return color;
}

vec4 lighting(
        vec3 normal,
        vec4 materialAmbient,
        vec4 materialDiffuse )
{
    vec4 color = vec4( C_ZERO, C_ZERO, C_ZERO, C_ZERO );

    for( int lightId = 0; lightId < 8; lightId++ ){
        if( lightId < u_lightCount ){
            color += calcOneLight(
                        lightId,
                        normal,
                        materialAmbient,
                        materialDiffuse );
        }
    }
    return color;
}

void main(void)
{
    vec3 normal = normalize( v_normal );
    if( u_lightCount == 0 ){
        gl_FragColor = v_color;
    }
    else{
        gl_FragColor = lighting( normal, v_color, v_color );
    }
}
