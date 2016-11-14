#ifdef GL_ES
precision mediump float;
#endif

varying vec4 v_frontColor;
varying vec4 v_backColor;

void main(void)
{
    if (gl_FrontFacing){
        gl_FragColor= v_frontColor;
    }
    else{
        gl_FragColor= v_backColor;
    }
}
