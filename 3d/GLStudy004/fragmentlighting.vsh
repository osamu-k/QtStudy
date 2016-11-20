#ifdef GL_ES
precision highp float;
#endif

uniform mat4 u_modelMatrix;
uniform mat4 u_viewMatrix;
uniform mat4 u_projectionMatrix;
uniform mat4 u_normalMatrix;

attribute vec3 a_position;  // in world space.
attribute vec3 a_normal;    // in world space.
attribute vec4 a_color;

varying vec3 v_position;    // in world space.
varying vec3 v_normal;      // in world space.
varying vec4 v_color;

void main(void)
{
    gl_Position = u_projectionMatrix * u_viewMatrix * u_modelMatrix * vec4(a_position, 1.0);
    vec4 position = u_modelMatrix * vec4(a_position, 1.0);
    v_position = position.xyz;
    vec4 normal = u_normalMatrix * vec4(a_normal, 1.0);
    v_normal = normal.xyz;
    v_color = a_color;
}
