#version 330 core

in vec3 vPosition_vs; // Position du sommet transformé dans l'espace View
in vec3 vNormal_vs; // Normale du sommet transformé dans l'espace View
in vec2 vTexCoords; // Coordonnées de texture du sommet

out vec3 fFragColor;

uniform sampler2D uTexture;
uniform sampler2D uTexture2;


void main() {
    vec4 planetaryTex = texture(uTexture, vTexCoords);
    vec4 cloudTex = texture(uTexture2, vTexCoords);
    fFragColor = vec3(planetaryTex.x, planetaryTex.y, planetaryTex.z)
                    + vec3(cloudTex.x, cloudTex.y, cloudTex.z);
}
