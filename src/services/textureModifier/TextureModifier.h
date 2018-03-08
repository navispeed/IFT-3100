#pragma once
#include <ofMain.h>



// énumération des types de kernel de convolution
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

// kernel de convolution (3x3) : identité
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

// kernel de convolution (3x3) : détection de bordure
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

	static const int nbTexture=3;
	ofImage textures[nbTexture];
	ofImage texture1;
	ofImage texture2;
	ofImage texture3;

	ofImage textureActuel;
	ofImage textureRetour;

	ConvolutionKernel kernel_type;
	Composition compOption;
	int cText=0;

	public:
	void setup();
	
	

	int image_width;
	int image_height;
	
	void filter();
	ofImage cycleTexture();
	ofImage cycleFiltre();
	ofImage compositionTexture();

};