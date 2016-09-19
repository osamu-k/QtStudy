#ifdef GL_ES
precision mediump float;
#endif

varying vec4 v_color;

uniform bool useTexture;
uniform sampler2D texture;
varying vec2 v_textureCoordinate;

uniform bool useLight;
uniform vec4 ambientColor;
uniform vec4 diffuseColor;
uniform vec4 specularColor;
uniform float ambientReflection;
uniform float diffuseReflection;
uniform float specularReflection;
uniform float shininess;
varying vec3 v_normal;
varying vec3 v_lightDirection;
varying vec3 v_viewerDirection;

void main(void)
{
    vec4 color;
    if( useTexture ){
        color = texture2D(texture, v_textureCoordinate);
    }
    else{
        color = v_color;
    }

    if( useLight ){
        vec3 normal = normalize(v_normal);
        vec3 lightDirection = normalize(v_lightDirection);
        vec3 viewerDirection = normalize(v_viewerDirection);
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
    }
    gl_FragColor = color;
}
