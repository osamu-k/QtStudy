#ifdef GL_ES
precision highp float;
#endif

uniform mat4 u_modelMatrix;
uniform mat4 u_viewMatrix;
uniform mat4 u_projectionMatrix;

attribute vec3 a_position;
attribute vec4 a_color;

varying vec4 v_color;

void main(void)
{
    bool useMatrices = true;
    if( useMatrices ){
        gl_Position = u_projectionMatrix
                        * u_viewMatrix
                        * u_modelMatrix
                        * vec4( a_position, 1 );
    }
    else{
        gl_Position = vec4( a_position, 1 );
    }
    v_color = a_color;
}
