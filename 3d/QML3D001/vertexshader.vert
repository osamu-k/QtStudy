#ifdef GL_ES
precision highp float;
#endif

uniform mat4 mvpMatrix;
attribute vec4 vertex;
attribute vec4 color;
varying vec4 v_color;

uniform bool useTexture;
attribute vec2 textureCoordinate;
varying vec2 v_textureCoordinate;

uniform bool useLight;
uniform mat4 mvMatrix;
uniform mat3 normalMatrix;
uniform vec3 lightPosition;
attribute vec3 normal;
varying vec3 v_normal;
varying vec3 v_lightDirection;
varying vec3 v_viewerDirection;

void main(void)
{
    gl_Position = mvpMatrix * vertex;

    if( useTexture ){
        v_textureCoordinate = textureCoordinate;
    }
    else{
        v_color = color;
    }

    if( useLight ){
        vec4 eyeVertex = mvMatrix * vertex;
        eyeVertex /= eyeVertex.w;
        v_normal = normalMatrix * normal;
        v_lightDirection = lightPosition - eyeVertex.xyz;
        v_viewerDirection = - eyeVertex.xyz;
    }
}
