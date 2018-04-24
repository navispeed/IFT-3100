// IFT3100H18 ~ lambert_120_fs.glsl

#version 120

// attributs interpolés à partir des valeurs en sortie du shader de sommets
varying vec3 viewSpacePosition;
varying vec3 viewSpaceNormal;

// position d'une source de lumière
uniform vec3 lightPosition;

// couleurs de réflexion du matériau
uniform vec3 colorAmbient;
uniform vec3 colorDiffuse;

void main()
{
  // re-normaliser la normale après interpolation (N)
  vec3 n = normalize(viewSpaceNormal);

  // calculer la direction de la surface vers la lumière (L)
  vec3 l = normalize(lightPosition - viewSpacePosition);

  // calculer le niveau de réflexion diffuse (N • L)
  float reflection_diffuse = max(dot(n, l), 0.0);

  // déterminer la couleur du fragment
  gl_FragColor = vec4(colorAmbient + colorDiffuse * reflection_diffuse, 1.0);
}
