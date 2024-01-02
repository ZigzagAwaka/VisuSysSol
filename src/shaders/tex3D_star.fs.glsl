#version 330 core

in vec3 vPosition_vs; // Position du sommet transformé dans l'espace View
in vec3 vNormal_vs; // Normale du sommet transformé dans l'espace View
in vec2 vTexCoords; // Coordonnées de texture du sommet

out vec3 fFragColor;

uniform sampler2D uTexture0;


// vec3 lightEffect() {
//     vec3 d = vec3(0,1,0);
//     vec3 c = vec3(0.7,0.5,0.4);
//     vec3 n = vec3(0,1,0);
//     vec3 en = vec3(0,1,0);
//     float sh = 10.0;
//     float sp = 1.0;
//     float di = 5.0;
//     vec3 diffuseColor = max(dot(d, n),0.0)*c*di;
//     vec3 reflection = normalize(reflect(-d, n));
//     float direction = max(0.0, dot(en, reflection));
//     vec3 specular = pow(direction, sh)*c*sp;
//     return diffuseColor + specular;
// }

void main() {
    vec4 planetaryTex = texture(uTexture0, vTexCoords);
    fFragColor = vec3(planetaryTex.x, planetaryTex.y, planetaryTex.z);
}
