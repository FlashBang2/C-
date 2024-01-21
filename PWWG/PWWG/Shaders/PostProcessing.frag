#version 460 core

out vec4 FragColor;

in vec2 textureCoordinates;

uniform sampler2D hdrBuffer;
uniform bool hdr;
uniform bool gammaCorrection;

void main () 
{
	const float gamma = 2.2f;
	vec3 hdrColor = texture(hdrBuffer, textureCoordinates).rgb;
	vec3 result = hdrColor;
	if (hdr && gammaCorrection) 
	{
		result *= 1.0f;
		result = hdrColor / (hdrColor + vec3(1.0f));

		result = pow(result, vec3(1.0 / gamma));
	}
	if(hdr) 
	{
		result *= 1.0f;
		result = hdrColor / (hdrColor + vec3(1.0f));
	}
	if (gammaCorrection) 
	{
		result = pow(hdrColor, vec3(1.0f / gamma));
	}
	FragColor = vec4(result, 1.0f);
}