#version 460 core

layout (location = 0) out vec4 FragColor;
layout (location = 1) out vec4 BrightColor;

struct Material 
{
	sampler2D diffuse;
	sampler2D specular;
	float shininess;
};

struct DirectionalLight {
    vec3 direction;
	
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight 
{
	vec3 position;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	float constant;
	float linear;
	float quadratic;
};

struct SpotLight 
{
	bool on;

	vec3 position;
	vec3 direction;
	float cutOff;
	float outerCutOff;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	
	float constant;
	float linear;
	float quadratic;
};

in vec3 FragmentPosition;
in vec3 Normal;
in vec2 TextureCoordinates;

#define NUMBER_OF_POINT_LIGHTS 1

uniform vec3 viewPosition;
uniform Material material;
uniform PointLight pointLight[NUMBER_OF_POINT_LIGHTS];
uniform SpotLight spotLight;
uniform DirectionalLight directionalLight;

vec3 calculatePointLight(PointLight pointLight, vec3 Normal, vec3 FragmentPosition, vec3 viewDirection);
vec3 calculateSpotLight(SpotLight spotLight, vec3 Normal, vec3 FragmentPosition, vec3 viewDirection);
vec3 calculateDirectionalLight(DirectionalLight directionalLight, vec3 Normal, vec3 FragmentPosition, vec3 viewDirection);

void main()
{
	vec3 normal = normalize(Normal);
	vec3 viewDirection = normalize(viewPosition - FragmentPosition);

	vec3 result = calculateDirectionalLight(directionalLight, normal, FragmentPosition, viewDirection);
	for(int i = 0; i < NUMBER_OF_POINT_LIGHTS; i++)
	{
		result += calculatePointLight(pointLight[i], normal, FragmentPosition, viewDirection);
	}
	if (spotLight.on) 
	{
		result += calculateSpotLight(spotLight, normal, FragmentPosition, viewDirection);
	}
	float brightness = dot(result, vec3(0.2126f, 0.7152f, 0.0722f));
	BrightColor = vec4(0.0f, 0.0f, 0.0f, 1.0f);
	if (brightness > 1.0f) 
	{
		BrightColor = vec4(result, 1.0f);
	}
	FragColor = vec4(result, 1.0f);
}

vec3 calculateDirectionalLight(DirectionalLight directionalLight, vec3 Normal, vec3 FragmentPosition, vec3 viewDirection)
{
	vec3 ambient = directionalLight.ambient * texture(material.diffuse, TextureCoordinates).rgb;

	vec3 lightDirection = normalize(-directionalLight.direction);
	float diffrence = max(dot(Normal, lightDirection), 0.0);
	vec3 diffuse = directionalLight.diffuse * diffrence * texture(material.diffuse, TextureCoordinates).rgb;

	vec3 halfwayDirection = normalize(lightDirection + viewDirection);
	float spec = pow(max(dot(viewDirection, halfwayDirection), 0.0f), material.shininess);
	vec3 specular = directionalLight.specular * spec * texture(material.specular, TextureCoordinates).rgb;

	return (ambient + diffuse + specular);
}

vec3 calculatePointLight(PointLight pointLight, vec3 Normal, vec3 FragmentPosition, vec3 viewDirection)
{
	vec3 ambient = pointLight.ambient * texture(material.diffuse, TextureCoordinates).rgb;

	vec3 lightDirection = normalize(pointLight.position - FragmentPosition);
	float diffrence = max(dot(Normal, lightDirection), 0.0f);
	vec3 diffuse = pointLight.diffuse * diffrence * texture(material.diffuse, TextureCoordinates).rgb;

	vec3 halfwayDirection = normalize(lightDirection + viewDirection);
	float spec = pow(max(dot(Normal, halfwayDirection), 0.0f), material.shininess);
	vec3 specular = pointLight.specular * spec * texture(material.specular, TextureCoordinates).rgb;

	float distance = length(pointLight.position - FragmentPosition);
	float attenaution = 1.0f / (pointLight.constant + pointLight.linear * distance + pointLight.quadratic * (distance * distance));

	ambient *= attenaution;
	diffuse *= attenaution;
	specular *= attenaution;

	return (ambient + diffuse + specular);
}

vec3 calculateSpotLight(SpotLight spotLight, vec3 Normal, vec3 FragmentPosition, vec3 viewDirection)
{
	vec3 lightDirection = normalize(spotLight.position - FragmentPosition);

	vec3 ambient = spotLight.ambient * texture(material.diffuse, TextureCoordinates).rgb;
	vec3 diffuse = vec3(0.0f, 0.0f, 0.0f);
	vec3 specular = vec3(0.0f, 0.0f, 0.0f);

	float diffrence = max(dot(Normal, lightDirection), 0.0f);
	diffuse = spotLight.diffuse * diffrence * texture(material.diffuse, TextureCoordinates).rgb;

	vec3 halfwayDirection = normalize(lightDirection + viewDirection);
	float spec = pow(max(dot(Normal, halfwayDirection), 0.0f), material.shininess);
	specular = spotLight.specular * spec * texture(material.specular, TextureCoordinates).rgb;

	float theta = dot(lightDirection, normalize(-spotLight.direction));
	float epsilon = (spotLight.cutOff - spotLight.outerCutOff);
	float intensity = clamp((theta - spotLight.outerCutOff) / epsilon, 0.0f, 1.0f);
	diffuse *= intensity;
	specular *= intensity;

	float distance = length(spotLight.position - FragmentPosition);
	float attenaution = 1.0f / (spotLight.constant + spotLight.linear * distance + spotLight.quadratic * (distance * distance));

	diffuse *= attenaution;
	specular *= attenaution;

	return (ambient + diffuse + specular);
}