uniform sampler2D texture;

//uniform vec4 color;
//varying vec4 varyingColor;
varying vec2 varyingTextureCoordinate;

void main(void)
{
//    gl_FragColor = varyingColor;
    gl_FragColor = texture2D(texture, varyingTextureCoordinate);
}
