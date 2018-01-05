#version 300 es

in lowp vec2 vTexCoord;
in lowp vec3 vNormal;
in lowp vec3 vPosition;
in lowp vec3 vColor;

out lowp vec4 color;

uniform lowp vec3 viewPosition;
uniform lowp vec3 lightPosition;
uniform lowp vec3 lightDiffuseColor;
uniform lowp vec3 lightAmbientColor;
uniform sampler2D texture0;

lowp vec3 light() {
    lowp float distance = length(lightPosition - vPosition);
    lowp float attenuation = 1.0f / (0.1f + 0.025*distance + 0.05*distance*distance);

    lowp vec3 lightDir = normalize(lightPosition - vPosition);
    lowp float diff = max(dot(vNormal, lightDir), 0.0);

    lowp vec3 diffuse = lightDiffuseColor * diff;

	lowp vec3 viewDir = normalize(viewPosition - vPosition);
	lowp vec3 reflectDir = reflect(-lightDir, vNormal); 
	lowp float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0);
	lowp vec3 specular = 0.5f * spec * lightDiffuseColor;  

    return vec3(lightAmbientColor + attenuation * (diffuse + specular));
}

void main(){
	lowp vec3 gamma = vec3(1.0/2.2);
	lowp vec3 invGamma = vec3(2.2);
	lowp vec3 colorNonLinear = vec3(texture(texture0, vTexCoord)) * vColor;
	lowp vec3 colorLinear = vec3(pow(colorNonLinear,invGamma)) * light();
    color = vec4(pow(colorLinear, gamma), 1.0f);
	//color = vec4(colorLinear, 1.0f);
}
