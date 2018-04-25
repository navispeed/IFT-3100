// IFT3100H18 ~ lambert_330_fs.glsl

#version 330

// attributs interpolés à partir des valeurs en sortie du shader de sommets
in vec3 viewSpacePosition;
in vec3 viewSpaceNormal;

// attribut en sortie
out vec4 fragmentColor;

// couleurs de réflexion du matériau
uniform vec3 colorAmbient;
uniform vec3 colorDiffuse;
uniform vec3 colorEmissive;

// position d'une source de lumière
uniform vec3 lightPosition;
uniform vec3[8] lightPositions;
uniform int lightNumber;

void main()
{
  // re-normaliser la normale après interpolation (N)
  vec3 n = normalize(viewSpaceNormal);

  

  
  float reflection_diffuse = 0;
  for(int i=0; i<lightNumber;i++){
	// calculer la direction de la surface vers la lumière (L)
	vec3 l = normalize(lightPositions[i] - viewSpacePosition);
  
	// calculer le niveau de réflexion diffuse (N • L)
	reflection_diffuse += max(dot(n, l), 0.0);
  }

  // déterminer la couleur du fragment
  fragmentColor = vec4(colorAmbient + colorDiffuse * reflection_diffuse + colorEmissive, 1.0);
}
