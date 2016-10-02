#ifdef GL_ES
precision highp float;
#endif

uniform mat4 u_modelMatrix;
uniform mat4 u_viewMatrix;
uniform mat4 u_projectionMatrix;

// for lighting
uniform mat3 u_normalMatrix;
uniform vec4 u_lightPosition;
uniform vec4 u_eyePosition;

attribute vec4 a_position;
attribute vec4 a_color;
attribute vec3 a_normal;

varying vec4 v_color;
varying vec3 v_normal;

varying vec3 v_lightDirection;
varying vec3 v_eyeDirection;

void main(void)
{
    gl_Position = u_projectionMatrix * u_viewMatrix * u_modelMatrix * a_position;
    v_color = a_color;

    // for lighting
    v_normal = normalize(u_normalMatrix * a_normal);
    vec4 vertexInView = u_viewMatrix * u_modelMatrix * a_position;
    vec4 lightInView = u_viewMatrix * u_lightPosition;
    vec4 eyeInView = u_viewMatrix * u_eyePosition;
//    vec4 vertexInView = u_modelMatrix * a_position;
//    vec4 lightInView = u_lightPosition;
//    vec4 eyeInView = u_eyePosition;
    v_lightDirection = normalize(lightInView.xyz - vertexInView.xyz);
    v_eyeDirection = normalize(eyeInView.xyz - vertexInView.xyz);
}
