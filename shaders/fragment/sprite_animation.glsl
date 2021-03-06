// Fragment shader
#version 330


// Predefiniowane dane wejsciowe
in  vec4 gl_FragCoord;
in  int  gl_PrimitiveID;

// Dane wyjsciowe
in vec2 fragUv;
in vec3 fragNormal;
in vec3 fragPosition;

out vec4 outColor;

uniform sampler2D tex0;


void main()
{
	vec4 color = texture(tex0,Fragment);
	if(color.a < 0.2)
		discard;
	outColor = color; 
}
