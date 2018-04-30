// IFT3100H18 ~ phong_120_vs.glsl

#version 120

// attributs en sortie
varying vec3 viewSpacePosition;
varying vec3 viewSpaceNormal;

void main()
{
  // transformation de la normale du sommet dans l'espace de vue
  viewSpaceNormal = vec3(gl_NormalMatrix * gl_Normal);

  // transformation de la position du sommet dans l'espace de vue
  viewSpacePosition = vec3(gl_ModelViewMatrix * gl_Vertex);

  // transformation de la position du sommet par les matrices de modèle, vue et projection
  gl_Position = gl_ProjectionMatrix * gl_ModelViewMatrix * gl_Vertex;
}
