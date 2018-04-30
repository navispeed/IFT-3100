// IFT3100H18 ~ gouraud_330_vs.glsl

#version 330

// attributs de sommet
in vec4 position;
in vec4 normal;

// attributs en sortie
out vec3 interpolationColor;

// attributs uniformes
uniform mat4x4 modelViewMatrix;
uniform mat4x4 projectionMatrix;

// couleurs de réflexion du matériau
uniform vec3 colorAmbient;
uniform vec3 colorDiffuse;
uniform vec3 colorSpecular;
uniform vec3 colorEmissive;

// facteur de brillance spéculaire du matériau
uniform float brightness;

// position d'une source de lumière
uniform vec3[8] lightPositions;
uniform int lightNumber;

void main()
{
  // calculer la matrice normale
  mat4x4 normalMatrix = transpose(inverse(modelViewMatrix));

  // transformation de la normale du sommet dans l'espace de vue
  vec3 viewSpaceNormal = vec3(normalMatrix * normal);

  // transformation de la position du sommet dans l'espace de vue
  vec3 viewSpacePosition = vec3(modelViewMatrix * position);

  // re-normaliser la normale
  vec3 N = normalize(viewSpaceNormal);
  float reflectionDiffuse = 0;
  float reflectionSpecular =0;
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
  interpolationColor = vec3(
    colorAmbient +
    colorDiffuse * reflectionDiffuse +
    colorSpecular * reflectionSpecular + colorEmissive);

  // transformation de la position du sommet par les matrices de modèle, vue et projection
  gl_Position = projectionMatrix * modelViewMatrix * position;
}
