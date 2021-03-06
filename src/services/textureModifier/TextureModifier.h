#pragma once
#include <ofMain.h>



// �num�ration des types de kernel de convolution
enum class ConvolutionKernel
{
	IDENTITY,
	EMBOSS,
	SHARPEN,
	EDGE_DECTECT,
	BLUR
};

enum class Composition
{
	DARKEN,
	LIGHTEN,
	ADD,
	AVERAGE,
	SUBSTRACT,
	FOCUSFIRST,
	FOCUSSECOND
};

// kernel de convolution (3x3) : identit�
const std::array<float, 9> convolution_kernel_identity
{
	0.0f,  0.0f,  0.0f,
	0.0f,  1.0f,  0.0f,
	0.0f,  0.0f,  0.0f
};

// kernel de convolution (3x3) : aiguiser
const std::array<float, 9> convolution_kernel_sharpen
{
	0.0f, -1.0f,  0.0f,
	-1.0f,  5.0f, -1.0f,
	0.0f, -1.0f,  0.0f
};

// kernel de convolution (3x3) : d�tection de bordure
const std::array<float, 9> convolution_kernel_edge_detect
{
	0.0f,  1.0f,  0.0f,
	1.0f, -4.0f,  1.0f,
	0.0f,  1.0f,  0.0f
};

// kernel de convolution (3x3) : bosseler
const std::array<float, 9> convolution_kernel_emboss
{
	-2.0f, -1.0f,  0.0f,
	-1.0f,  1.0f,  1.0f,
	0.0f,  1.0f,  2.0f
};

// kernel de convolution (3x3) : flou
const std::array<float, 9> convolution_kernel_blur
{
	1.0f / 9.0f,  1.0f / 9.0f,  1.0f / 9.0f,
	1.0f / 9.0f,  1.0f / 9.0f,  1.0f / 9.0f,
	1.0f / 9.0f,  1.0f / 9.0f,  1.0f / 9.0f
};

class textureModifier {
	// fonction de filtrage par convolution
	private:

		int nbTexture;
		vector<ofImage> textures;

		ofImage textureActuel;
		ofImage textureRetour;

		ConvolutionKernel kernel_type;
		Composition compOption;

		int image_width;
		int image_height;
		int cText = 0;

	public:
		textureModifier() {};

		textureModifier(string path[], int nbTexture);

		ofImage filter(ofImage textureOrig, ConvolutionKernel kernel);

		void cycleTexture();

		ofImage getNextTexture();

		ofImage applyTexture();

		ConvolutionKernel cycleFiltre();

		ofImage compositionTexture(ofImage texture1, ofImage texture2, Composition comp);

		Composition cycleComposition();
};