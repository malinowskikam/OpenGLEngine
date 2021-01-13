#version 330

in  vec4 gl_FragCoord;
in  int  gl_PrimitiveID;

in vec3 fragPosition;
in vec3 fragLightPosition;
in vec2 fragUv;
in vec3 fragNormal;

out vec4 outColor;

uniform int lightable;
uniform vec3 modelAmbient;
uniform vec3 modelDiffuse;
uniform vec3 modelSpecular;
uniform float modelRoughness;
uniform int modelFlat;

uniform vec3 cameraPosition;

uniform int reflectEnvironment;
uniform float reflectColorPercentage;
uniform int refractEnvironment;
uniform float refractColorPercentage;
uniform float refractCoeff;

uniform int haveCubeTexture;
uniform sampler2D model2DTexture;
uniform samplerCube modelCubeTexture;

uniform samplerCube environmentTexture;

vec3 pointLight(vec3 fragNormal, vec3 lightPosition, float lightAttenuation)
{
	vec3 lightDirection = normalize(lightPosition - vec3(fragPosition));
	vec3 diffusePart = max(dot(fragNormal,lightDirection), 0.0f) * modelDiffuse;
	vec3 specularPart = pow(max(dot(normalize(cameraPosition - vec3(fragPosition)), reflect(-lightDirection, fragNormal)), 0.0f), modelRoughness) * modelSpecular;

	vec3 distanceToLightV = fragPosition - lightPosition;
	float distanceToLight = sqrt(distanceToLightV.x*distanceToLightV.x + distanceToLightV.y*distanceToLightV.y + distanceToLightV.z*distanceToLightV.z);

	return (diffusePart + specularPart) / (1.0f + lightAttenuation * distanceToLight*distanceToLight);
}

vec3 spotLight(vec3 fragNormal, vec3 lightPosition, float lightAttenuation, vec3 lightDirection, float cosAngle)
{
	vec3 fragDirection = normalize(fragPosition - lightPosition);

	if(dot(lightDirection,fragDirection)>cosAngle)
		return pointLight(fragNormal,lightPosition,lightAttenuation);
	else
		return vec3(0.0);
}

vec3 directionLight(vec3 fragNormal, vec3 lightPosition)
{
	vec3 lightDirection = normalize(lightPosition);
	vec3 diffusePart = max(dot(fragNormal,lightDirection), 0.0) * modelDiffuse;

	return (diffusePart);
}

float fogFactor(float fogStart,float fogStrength)
{
	float distance = sqrt(dot(fragPosition-cameraPosition,fragPosition-cameraPosition));
	if(distance<fogStart)
		return 0.0f;
	else
	{
		return clamp(fogStrength * pow(distance-fogStart,2),0,1);
	}
	
}

void main()
{
	vec4 color = texture(modelTexture,fragUv);
	
	if(color.a < 0.2f)
		discard;

	float alpha = outColor.a;

	if(reflectEnvironment == 1 && refractEnvironment == 1)
	{
		vec3 reflectionColor = texture(environmentTexture, reflect(normalize(fragPosition - cameraPosition), fragNormal)).rgb;

		vec3 refractionColor = texture(environmentTexture,refract(normalize(fragPosition - cameraPosition),fragNormal,refractCoeff)).rgb;

		vec3 mixedEnvironmentColor = mix(reflectionColor,refractionColor,reflectColorPercentage/(reflectColorPercentage+refractColorPercentage));
		outColor = vec4(mix(outColor.xyz,mixedEnvironmentColor,reflectColorPercentage+refractColorPercentage),alpha);
	}
	else if(reflectEnvironment == 1 && refractEnvironment == 0)
	{
		vec3 reflectionColor = texture(environmentTexture, reflect(normalize(fragPosition - cameraPosition), fragNormal)).rgb;

		outColor = vec4(mix(outColor.xyz,reflectionColor,reflectColorPercentage),alpha);
	}
	else if(reflectEnvironment == 0 && refractEnvironment == 1)
	{
		vec3 refractionColor = texture(environmentTexture,refract(normalize(fragPosition - cameraPosition),fragNormal,refractCoeff)).rgb;

		outColor = vec4(mix(outColor.xyz,refractionColor,refractColorPercentage),alpha);
	}

	vec3 torchLight = pointLight(fragNormal,torchPosition,torchAttenuation)*torchLightColor;
	vec3 flashlightLight = spotLight(fragNormal,flashlightPosition,flashlightAttenuation,flashlightDirection,flashlightCosAngle)*flashlightLightColor;
	vec3 sunLight = directionLight(fragNormal,sunPosition)*sunLightColor;
	vec3 lanternLight = pointLight(fragNormal,lanternPosition,lanternAttenuation)*lanternLightColor;

	if(modelFlat==1)
	{
		vec3 oppositefragNormal = -fragNormal;
		torchLight += pointLight(oppositefragNormal,torchPosition,torchAttenuation)*torchLightColor;
		flashlightLight += spotLight(oppositefragNormal,flashlightPosition,flashlightAttenuation,flashlightDirection,flashlightCosAngle)*flashlightLightColor;
		sunLight += directionLight(oppositefragNormal,sunPosition)*sunLightColor;
		lanternLight += pointLight(oppositefragNormal,lanternPosition,lanternAttenuation)*lanternLightColor;
	}

	float shadowPart = calculateShadow(fragLightPosition, fragPosition-sunPosition);
	sunLight *= (1-shadowPart);

	shadowPart = calculateTorchShadow();
	torchLight *= (1-shadowPart);

	vec3 light = clamp(modelAmbient+torchLight+flashlightLight+sunLight+lanternLight,0,1);
	outColor = clamp(color * vec4(light,1.0f),0,1);


	outColor = mix(outColor,vec4(backgroundColor,1.0f),fogFactor(fogStart,fogStrength));


	//outColor = vec4(vec3(fogFactor(fogStart,fogStrength)),1.0);
	
}
