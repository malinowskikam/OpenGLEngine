#version 330 core
in vec2 fragUv;

out vec4 color;

uniform sampler2D glyph;
uniform vec3 textColor;

void main()
{    
    color = vec4(textColor, texture(glyph, fragUv).r);
}