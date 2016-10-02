#ifdef GL_ES
precision mediump float;
#endif

varying vec4 v_color;
varying vec3 v_normal;

// for lighting
uniform vec4 ambientColor;
uniform vec4 diffuseColor;
uniform vec4 specularColor;

uniform float ambientReflection;
uniform float diffuseReflection;
uniform float specularReflection;
uniform float shininess;

varying vec3 v_lightDirection;
varying vec3 v_eyeDirection;

//uniform vec3 spotDirection;
//uniform vec3 attenuationFactors;
//uniform float spotExponent;
//uniform float spotCutoffAngle;
//uniform bool computeDistanceAttenuation;

void main(void)
{
    vec4 color = v_color;
    vec3 normal = normalize(v_normal);
    vec3 lightDirection = normalize(v_lightDirection);
    vec3 viewerDirection = normalize(v_eyeDirection);
    vec4 ambientIllumination = ambientReflection * ambientColor;
    vec4 diffuseIllumination = diffuseReflection
                                * max(0.0, dot(lightDirection, normal))
                                * diffuseColor;
    vec4 specularIllumination = specularReflection
                                * pow(max(0.0,
                                          dot(-reflect(lightDirection,normal),
                                              viewerDirection)),
                                      shininess)
                                * specularColor;
    color = color
            * (ambientIllumination + diffuseIllumination)
            + specularIllumination;

    gl_FragColor = color;
}
