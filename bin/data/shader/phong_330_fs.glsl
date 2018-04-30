// IFT3100H18 ~ phong_330_fs.glsl

#version 330

// attributs interpolés à partir des valeurs en sortie du shader de sommet
in vec3 viewSpacePosition;
in vec3 viewSpaceNormal;

// attribut en sortie
out vec4 fragmentColor;

// couleurs de réflexion du matériau
uniform vec3 colorAmbient;
uniform vec3 colorDiffuse;
uniform vec3 colorSpecular;
uniform vec3 colorEmissive;

// facteur de brillance spéculaire du matériau
uniform float brightness;

// position d'une source de lumière
uniform vec3 lightPositions[8];
uniform int lightNumber;

void main()
{
  // re-normaliser la normale après interpolation
  vec3 N = normalize(viewSpaceNormal);

  float reflectionSpecular = 0;
  float reflectionDiffuse = 0;
  for(int i=0; i<lightNumber;i++){
	  // calculer la direction de la surface vers la lumière (L)
	  vec3 L = normalize(lightPositions[i] - viewSpacePosition);

	  // calculer le niveau de réflexion diffuse (N • L)
	  reflectionDiffuse += max(dot(N, L), 0.0);

	  // réflexion spéculaire par défaut

	  // calculer la réflexion spéculaire seulement s'il y a réflexion diffuse
	  if (reflectionDiffuse > 0.0)
	  {
		// calculer la direction de la surface vers la caméra (V)
		vec3 V = normalize(-viewSpacePosition);

		// calculer la direction de la réflection (R) du rayon incident (-L) en fonction de la normale (N)
		vec3 R = reflect(-L, N);

		// calculer le niveau de réflexion spéculaire (R • V)
		reflectionSpecular += pow(max(dot(V, R), 0.0), brightness);
	  }
  }
  // calculer la couleur du fragment
  fragmentColor = vec4(
    colorAmbient +
    colorDiffuse * reflectionDiffuse +
    colorSpecular * reflectionSpecular + colorEmissive, 1.0);
}
