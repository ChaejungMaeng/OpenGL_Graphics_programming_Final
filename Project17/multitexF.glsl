#version 430

in vec2 TexCoord;
 
uniform sampler2D BrickTex;
uniform sampler2D MossTex;

out vec4 color;

void main(void)
{
   vec4 bcolor = texture(BrickTex, TexCoord);
   vec4 mcolor = texture(MossTex, TexCoord);
   color = mix(bcolor, mcolor, mcolor.a);
}