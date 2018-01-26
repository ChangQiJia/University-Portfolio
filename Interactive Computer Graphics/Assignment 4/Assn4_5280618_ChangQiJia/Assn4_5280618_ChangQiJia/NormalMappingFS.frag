#version 330 core

// interpolated values from the vertex shaders
in vec3 vPosition;
in vec3 vNormal;
in vec3 vTangent;
in vec2 vTexCoord;

// uniform input data
struct LightProperties
{
	vec4 position;
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
	float shininess;
	float cutoffAngle;
	vec3 direction;
};

struct MaterialProperties
{
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
};

uniform LightProperties uLightingProperties;
uniform MaterialProperties uMaterialProperties;
uniform vec3 uViewPoint;

uniform sampler2D uTextureSampler;
uniform sampler2D uNormalSampler;
uniform float uAlpha;

// output data
out vec4 fColor;

void main()
{
	vec4 colour = vec4 (0.0f, 0.0f, 0.0f, 0.0f);

	// calculate normal map vectors
		vec3 normal = normalize(vNormal);
		vec3 tangent = normalize(vTangent);
		vec3 biTangent = normalize(cross(tangent, normal));

		vec3 normalMap = 2.0f * texture(uNormalSampler, vTexCoord).xyz - 1.0f;

		// calculate vectors for lighting
		vec3 N = normalize(mat3(tangent, biTangent, normal) * normalMap);
		vec3 L;
	
		// determine whether the light is a point light source or directional light
		if(uLightingProperties.position.w == 0.0f)
			L = normalize((uLightingProperties.position).xyz);
		else
			L = normalize((uLightingProperties.position).xyz - vPosition);

		vec3 V = normalize(uViewPoint - vPosition);
		vec3 R = reflect(-L, N);

		// calculate Phong lighting
		vec4 ambient = uLightingProperties.ambient * uMaterialProperties.ambient;
		vec4 diffuse = uLightingProperties.diffuse * uMaterialProperties.diffuse * max(dot(L, N), 0.0);
		vec4 specular = vec4(0.0f, 0.0f, 0.0f, 1.0f);

		if(dot(L, N) > 0.0f)
		{
			specular = uLightingProperties.specular * uMaterialProperties.specular 
				* pow(max(dot(V, R), 0.0), uLightingProperties.shininess);
		}

		// set output color
		colour = vec4 ((diffuse + specular + ambient).rgb, uAlpha) ;	
		colour *= texture(uTextureSampler, vTexCoord);


	fColor = colour;
		

}