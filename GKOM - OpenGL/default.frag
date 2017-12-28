#version 330 core
in vec3 shaderColor;
in vec3 ourPosition;
in vec2 TexCoord;

out vec4 color;

uniform sampler2D ourTexture1;
uniform sampler2D ourTexture2;
uniform vec4 ourColor;

void main()
{
	color = ourColor;  
	if(ourColor.w == 0.0f )
		color = mix(texture(ourTexture1, TexCoord), texture(ourTexture2, vec2(1.0f - TexCoord.x, TexCoord.y)), 0.2 );
	if(ourColor.w == 0.5f)
		color = texture(ourTexture1, TexCoord);
	if(ourColor.w == 0.3f)
		color = texture(ourTexture2, TexCoord);
	if(ourColor.w == 0.1f)
		color = vec4(shaderColor, 1.0f);
}