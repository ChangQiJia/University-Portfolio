#version 330 core

// interpolated values from the vertex shaders
in vec3 vNormal;
in vec3 vPosition;

#define MAX_LIGHTS 3
#define MAX_ITEM 10 
struct LightProperties
{
	vec4 position;
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
	float shininess;
	vec3 attenuation;
	float cutoffAngle;
	vec3 direction;
	float spotlight;
};

struct MaterialProperties
{
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
};


// uniform input data
uniform LightProperties uLightingProperties[MAX_LIGHTS];
uniform MaterialProperties uMaterialProperties;
uniform vec3 uViewPoint;

// output data
out vec3 fColor;

vec3 calculateLighting(int lightIndex, vec3 N)
{
	// calculate vectors for lighting
    vec3 L;
	float attenuation = 1.0f;
	
	// determine whether the light is a point light source or directional light
	if(uLightingProperties[lightIndex].position.w == 0.0f)
		{
			L = normalize((uLightingProperties[lightIndex].position).xyz);
		}
	else
		{
			L = ((uLightingProperties[lightIndex].position).xyz - vPosition);
			float distance = length(L);
			L = normalize(L);

			attenuation = 1/(uLightingProperties[lightIndex].attenuation.x 
						+ uLightingProperties[lightIndex].attenuation.y * distance 
						+ uLightingProperties[lightIndex].attenuation.z * distance * distance);
		}

	vec3 V = normalize(uViewPoint - vPosition);
	vec3 R = reflect(-L, N);

	vec3 direction = normalize(uLightingProperties[lightIndex].direction);
	float angle = degrees(acos(dot(-L, direction)));
	
	vec3 colour = vec3(0.0f, 0.0f, 0.0f);

	if (uLightingProperties[lightIndex].spotlight != 0.0f) 
	{
		if(angle <= uLightingProperties[lightIndex].cutoffAngle)
			{
				vec4 ambient  = uLightingProperties[lightIndex].ambient * uMaterialProperties.ambient;
				vec4 diffuse  = uLightingProperties[lightIndex].diffuse * uMaterialProperties.diffuse * max(dot(L, N), 0.0);
				vec4 specular = vec4(0.0f, 0.0f, 0.0f, 1.0f);

				if(dot(L, N) > 0.0f)
				{
					specular = uLightingProperties[lightIndex].specular * uMaterialProperties.specular
						* pow(max(dot(V, R), 0.0), uLightingProperties[lightIndex].shininess);
				}

				colour = (attenuation * (diffuse + specular)).rgb + ambient.rgb;
				colour *= 1.0f - angle/uLightingProperties[lightIndex].cutoffAngle;

				return colour; 
			}
	}
	else
	{	
	// calculate Phong lighting

		vec4 ambient  = uLightingProperties[lightIndex].ambient * uMaterialProperties.ambient;
		vec4 diffuse  = uLightingProperties[lightIndex].diffuse * uMaterialProperties.diffuse * max(dot(L, N), 0.0);
		vec4 specular = vec4(0.0f, 0.0f, 0.0f, 1.0f);

		if(dot(L, N) > 0.0f)
		{
			specular = uLightingProperties[lightIndex].specular * uMaterialProperties.specular
				* pow(max(dot(V, R), 0.0), uLightingProperties[lightIndex].shininess);
		}

		colour = (attenuation * (diffuse + specular)).rgb + ambient.rgb;

		return colour; 
	}
}


void main()
{
	vec3 normal = normalize(vNormal);
	vec3 colour = vec3(0.0f, 0.0f, 0.0f);

	for(int i = 0; i < MAX_LIGHTS; i++)
	{
		colour += calculateLighting(i, normal);
	}
	
	// set output color
	fColor = colour;
}