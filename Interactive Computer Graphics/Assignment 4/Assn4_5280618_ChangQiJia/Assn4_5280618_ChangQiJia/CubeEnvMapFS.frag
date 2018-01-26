#version 330 core

// interpolated values from the vertex shaders
in vec3 vNormal;
in vec3 vPosition;

// uniform input data
struct LightProperties
{
	vec4 position;
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
	float shininess;
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

uniform float AddHue;
uniform float AddSat;
uniform float AddLig;

uniform samplerCube uEnvironmentMap;

// output data
out vec3 fColor;

float Hue_2_RGB(float v1, float v2, float vH )
{
	float ret;
   if ( vH < 0.0 )
     vH += 1.0;
   if ( vH > 1.0 )
     vH -= 1.0;
   if ( ( 6.0 * vH ) < 1.0 )
     ret = ( v1 + ( v2 - v1 ) * 6.0 * vH );
   else if ( ( 2.0 * vH ) < 1.0 )
     ret = ( v2 );
   else if ( ( 3.0 * vH ) < 2.0 )
     ret = ( v1 + ( v2 - v1 ) * ( ( 2.0 / 3.0 ) - vH ) * 6.0 );
   else
     ret = v1;
   return ret;
}


void main()
{
    vec3 N = normalize(vNormal);
    vec3 L;

	float Cmax, Cmin;
	float D; 
	float H, S, bright; 
	float red, G, B;
	
	// determine whether the light is a point light source or directional light
	if(uLightingProperties.position.w == 0.0f)
		L = normalize((uLightingProperties.position).xyz);
	else
		L = normalize((uLightingProperties.position).xyz - vPosition);

	vec3 V = normalize(uViewPoint - vPosition);
	vec3 R = reflect(-L, N);

	// calculate the ambient, diffuse and specular components
	vec4 ambient = uLightingProperties.ambient * uMaterialProperties.ambient;
    vec4 diffuse = uLightingProperties.diffuse * uMaterialProperties.diffuse * max(dot(L, N), 0.0);
	vec4 specular = vec4(0.0f, 0.0f, 0.0f, 1.0f);

	if(dot(L, N) > 0.0f)
	{
	    specular = uLightingProperties.specular * uMaterialProperties.specular 
			* pow(max(dot(V, R), 0.0), uLightingProperties.shininess);
	}

	vec3 reflectEnvMap = reflect(-V, N);

	vec3 color; 

	// set output color
	color = texture(uEnvironmentMap, reflectEnvMap).rgb;

	color *= (diffuse + specular + ambient).rgb;	

	red = color.r;
    G = color.g;
    B = color.b;

	Cmax = max (red, max (G, B));
    Cmin = min (red, min (G, B));

	bright = (Cmax + Cmin) / 2.0;

	if (Cmax == Cmin)
	  {
			H = 0.0; 
			S = 0.0;
	  }
	else
	{
		D = Cmax - Cmin; 
	
		if (bright < 0.5)
		{
		  S = D / (Cmax + Cmin);
		}
		else
		{
		  S = D / (2.0 - (Cmax + Cmin));
		}
		 if (red == Cmax)
		{
		  H = (G - B) / D;
		}
		else 
			{
			  if (G == Cmax)
			  {
      			 H = 2.0 + (B - red) /D;
			  }
			  else
			  {
				H = 4.0 + (red - G) / D;
			  }
   		}
	 H = H / 6.0;

	}

	H += AddHue;
	S += AddSat;
	bright += AddLig;

	if (H < 0.0)
	{
		H = H + 1.0;
	}

	H = clamp(H, 0.0, 1.0);
	S = clamp(S, 0.0, 1.0);
	bright = clamp(bright, 0.0, 1.0);

	float var_2, var_1;

	if (S == 0.0)
	{
	   red = bright;
	   G = bright;
	   B = bright;
	}

	else
	{
	   if ( bright < 0.5 )
	   {
	   var_2 = bright * ( 1.0 + S );
	   }
	   else
	   {
	   var_2 = ( bright + S ) - ( S * bright );
	   }

	   var_1 = 2.0 * bright - var_2;

	   red = Hue_2_RGB( var_1, var_2, H + ( 1.0 / 3.0 ) );
	   G = Hue_2_RGB( var_1, var_2, H );
	   B = Hue_2_RGB( var_1, var_2, H - ( 1.0 / 3.0 ) );
	}

	fColor = vec3(red,G,B); 
}