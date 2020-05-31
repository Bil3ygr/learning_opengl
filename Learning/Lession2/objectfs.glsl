#version 330 core
in vec3 fragNormal;
in vec3 fragPos;
in vec2 fragTexCoords;

out vec4 FragColor;

uniform vec3 objectColor;
uniform vec3 viewPos;

struct Material {
	//vec3 ambient;
	//vec3 diffuse;
	//vec3 specular;
	sampler2D diffuse;
	sampler2D specular;
	float shininess;
};

uniform Material material;

struct Light {
	int type;
	vec3 position;
	vec3 direction;
	float cutOff;
	float outCutOff;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

uniform Light light;

void main()
{
	//float ambientStrength = 0.1;
	//vec3 ambient = ambientStrength * lightColor;

	//vec3 norm = normalize(fragNormal);
	//vec3 lightDir = normalize(lightPos - fragPos);
	//float diff = max(dot(norm, lightDir), 0.0);
	//vec3 diffuse = diff * lightColor;

	//float specularStrength = 0.5;
	//vec3 viewDir = normalize(viewPos - fragPos);
	//vec3 reflectDir = reflect(-lightDir, norm);
	//float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
	
	//vec3 result = (ambient + diffuse + spec) * objectColor;
	//FragColor = vec4(result, 1.0);

	// 环境光
	//vec3 ambient = light.ambient * material.ambient;
	vec3 ambient = light.ambient * vec3(texture(material.diffuse, fragTexCoords));
	// 漫反射
	vec3 norm = normalize(fragNormal);
	vec3 lightDir;
	if (light.type == 1)
		lightDir = normalize(-light.direction);
	else
		lightDir = normalize(light.position - fragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	//vec3 diffuse = light.diffuse * (diff * material.diffuse);
	// 漫反射贴图
	vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, fragTexCoords));
	//镜面光
	vec3 viewDir = normalize(viewPos - fragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	//vec3 specular = light.specular * (spec * material.specular);
	vec3 specular = light.specular * spec * vec3(texture(material.specular, fragTexCoords));

	float theta = dot(lightDir, normalize(-light.direction));
	float epsilon = light.cutOff- light.outCutOff;
	float intensity = clamp((theta - light.outCutOff) / epsilon, 0.0, 1.0);
	vec3 result = ambient + diffuse * intensity + specular * intensity;
	FragColor = vec4(result, 1.0);
}
