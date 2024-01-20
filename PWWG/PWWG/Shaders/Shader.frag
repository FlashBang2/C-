#version 460 core

struct Material 
{
	sampler2D diffuse;
	sampler2D specular;
	float shininess;
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

out vec4 FragColor;

uniform vec3 viewPosition;
uniform Material material;
uniform PointLight pointLight;
uniform SpotLight spotLight;

vec3 calculatePointLight(PointLight pointLight, vec3 Normal, vec3 FragmentPosition, vec3 viewPosition);
vec3 calculateSpotLight(SpotLight spotLight, vec3 Normal, vec3 FragmentPosition, vec3 viewPosition);

void main()
{
	vec3 result = calculatePointLight(pointLight, Normal, FragmentPosition, viewPosition);
	if (spotLight.on) 
	{
		result += calculateSpotLight(spotLight, Normal, FragmentPosition, viewPosition);
	}
	FragColor = vec4(result, 1.0f);
}

vec3 calculatePointLight(PointLight pointLight, vec3 Normal, vec3 FragmentPosition, vec3 viewPosition)
{
	vec3 ambient = pointLight.ambient * texture(material.diffuse, TextureCoordinates).rgb;

	vec3 normal = normalize(Normal);
	vec3 lightDirection = normalize(pointLight.position - FragmentPosition);
	float diffrence = max(dot(normal, lightDirection), 0.0f);
	vec3 diffuse = pointLight.diffuse * diffrence * texture(material.diffuse, TextureCoordinates).rgb;

	vec3 viewDirection = normalize(viewPosition - FragmentPosition);
	vec3 reflectDirection = reflect(-lightDirection, normal);
	float spec = pow(max(dot(viewDirection, reflectDirection), 0.0f), material.shininess);
	vec3 specular = pointLight.specular * spec * texture(material.specular, TextureCoordinates).rgb;

	float distance = length(pointLight.position - FragmentPosition);
	float attenaution = 1.0f / (pointLight.constant + pointLight.linear * distance + pointLight.quadratic * (distance * distance));

	ambient *= attenaution;
	diffuse *= attenaution;
	specular *= attenaution;

	return (ambient + diffuse + specular);
}

vec3 calculateSpotLight(SpotLight spotLight, vec3 Normal, vec3 FragmentPosition, vec3 viewPosition)
{
	vec3 lightDirection = normalize(spotLight.position - FragmentPosition);

	float theta = dot(lightDirection, normalize(-spotLight.direction));

	vec3 ambient = spotLight.ambient * texture(material.diffuse, TextureCoordinates).rgb;
	vec3 diffuse = vec3(0.0f, 0.0f, 0.0f);
	vec3 specular = vec3(0.0f, 0.0f, 0.0f);

	if (theta > spotLight.cutOff) 
	{
		vec3 normal = normalize(Normal);
		float diffrence = max(dot(normal, lightDirection), 0.0f);
		diffuse = spotLight.diffuse * diffrence * texture(material.diffuse, TextureCoordinates).rgb;

		vec3 viewDirection = normalize(viewPosition - FragmentPosition);
		vec3 reflectDirection = reflect(-lightDirection, normal);
		float spec = pow(max(dot(viewDirection, reflectDirection), 0.0f), material.shininess);
		specular = spotLight.specular * spec * texture(material.specular, TextureCoordinates).rgb;

		float distance = length(spotLight.position - FragmentPosition);
		float attenaution = 1.0f / (spotLight.constant + spotLight.linear * distance + spotLight.quadratic * (distance * distance));

		diffuse *= attenaution;
		specular *= attenaution;
	}

	return (ambient + diffuse + specular);
}