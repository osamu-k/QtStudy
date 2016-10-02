#ifdef GL_ES
precision highp float;
#endif

attribute vec4 position;
attribute vec4 color;
attribute vec3 normal;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

varying vec4 v_color;
varying vec3 v_normal;

// for lighting
uniform mat3 normalMatrix;
uniform vec3 lightPosition;
uniform vec3 eyePosition;

varying vec3 v_lightDirection;
varying vec3 v_eyeDirection;

void main(void)
{
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * position;
    v_color = color;

    // for lighting
    v_normal = normalize(normalMatrix * normal);
    vec4 vertexPosition = modelMatrix * position;
    v_lightDirection = normalize(lightPosition - vertexPosition.xyz);
    v_eyeDirection = normalize(eyePosition - vertexPosition.xyz);
}
