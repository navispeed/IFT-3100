#include "TextureModifier.h"


textureModifier::textureModifier(string path[], int nbTexture)
{
	this->nbTexture = nbTexture;
	for (int i = 0; i < nbTexture; i++) {
		textures.push_back(ofImage());
		if (!textures[i].load(path[i])) {
			std::cout << "Impossible de lire le fichier: " + path[i] << endl;
			textures[i].allocate(256, 256, OF_IMAGE_COLOR);
			textures[i].setColor(ofColor::black);
		}
	}
	textureActuel = textures[0];

	// sélectionner le filtre de convolution par défaut
	kernel_type = ConvolutionKernel::IDENTITY;
	compOption = Composition::ADD;
}

// fonction de filtrage par convolution
ofImage textureModifier::filter(ofImage textureOrig, ConvolutionKernel kernel)
{
	int ind;
	int xOff;
	int yOff;
	float mod;
	float colors[3];
	ofColor newColor;
	ofColor color1;

	int width = textureOrig.getWidth();
	int height = textureOrig.getHeight();
	textureRetour.allocate(width, height, OF_IMAGE_COLOR);
	for (int y = 0; y < height; ++y)
	{
		for (int x = 0; x < width; ++x)
		{
			for (int z = 0; z < 3; z++) {
				colors[z] = 0;
			}
			for (int i = -1; i < 2; i++) {
				for (int j = -1; j < 2; j++) {

					ind = i + 1 + (j + 1) * 3;
					xOff = x + i;
					yOff = y + j;

					if (xOff >= 0 && yOff >= 0 && xOff < width && yOff < height) {
						switch (kernel)
						{
						case ConvolutionKernel::IDENTITY:
							mod = convolution_kernel_identity.at(ind);
							break;

						case ConvolutionKernel::EMBOSS:
							mod = convolution_kernel_emboss.at(ind);
							break;

						case ConvolutionKernel::SHARPEN:
							mod = convolution_kernel_sharpen.at(ind);
							break;

						case ConvolutionKernel::EDGE_DECTECT:
							mod = convolution_kernel_edge_detect.at(ind);
							break;

						case ConvolutionKernel::BLUR:
							mod = convolution_kernel_blur.at(ind);
							break;

						default:
							mod = convolution_kernel_identity.at(ind);
							break;
						}
						color1 = textureOrig.getColor(xOff, yOff);
						colors[0] += color1.r*mod;
						colors[1] += color1.g*mod;
						colors[2] += color1.b*mod;
					}
					
				}
			}

			newColor = ofColor((int)ofClamp(colors[0], 0, 255), (int)ofClamp(colors[1], 0, 255), (int)ofClamp(colors[2], 0, 255));
			textureRetour.setColor(x, y, newColor);
		}
	}
	textureRetour.update();
	return textureRetour;
}

void textureModifier::cycleTexture()
{
	++cText;
	cText %= nbTexture;
	textureActuel = textures[cText];
}

ofImage textureModifier::getNextTexture()
{
	return textures[(cText + 1) % nbTexture];
}


ofImage textureModifier::compositionTexture(ofImage texture1, ofImage texture2, Composition comp) {
	int ind1 = cText;
	int ind2 = (cText+1)%nbTexture;
		int width = min(texture1.getWidth(),texture2.getWidth());
		int height = min(texture1.getHeight(), texture2.getHeight());

		textureRetour.allocate(width, height, OF_IMAGE_COLOR);

		ofColor newColor;
		ofColor color1;
		ofColor color2;

		
		for (int y = 0; y < height; ++y)
		{
			for (int x = 0; x < width; ++x)
			{
				color1 = texture1.getColor(x, y);
				color2 = texture2.getColor(x, y);
				switch (comp) {
				case Composition::DARKEN: {
					int temp = color1.r + color1.b + color1.g;
					int temp2 = color2.r + color2.b + color2.g;
					newColor = (temp < temp2) ? color1 : color2;
					break;
				}
				case Composition::LIGHTEN:
				{
					int temp = color1.r + color1.b + color1.g;
					int temp2 = color2.r + color2.b + color2.g;
					newColor = (temp > temp2) ? color1 : color2;
					break;
				}
				case Composition::ADD:
					newColor = color1 + color2;
					break;
				case Composition::AVERAGE:
					newColor = (color1 + color2)*0.5;
					break;
				case Composition::SUBSTRACT:
					newColor = color1 - color2;
					break;
				case Composition::FOCUSFIRST:
					newColor = color1 + color2*0.5;
					break;
				case Composition::FOCUSSECOND:
					newColor = color1*0.5 + color2;
					break;
					
				}
				textureRetour.setColor(x,y,newColor);
			}
		}
	return textureRetour;
}

Composition textureModifier::cycleComposition()
{
	switch (compOption) {
	case Composition::DARKEN:
		compOption = Composition::LIGHTEN;
		std::cout << "Composition: Lighten" << endl;
		break;
	case Composition::LIGHTEN:
		compOption = Composition::ADD;
		std::cout << "Composition: Add" << endl;
		break;
	case Composition::ADD:
		compOption = Composition::AVERAGE;
		std::cout << "Composition: Average" << endl;
		break;
	case Composition::AVERAGE:
		compOption = Composition::SUBSTRACT;
		std::cout << "Composition: Substract" << endl;
		break;
	case Composition::SUBSTRACT:
		compOption = Composition::FOCUSFIRST;
		std::cout << "Composition: FocusFirst" << endl;
		break;
	case Composition::FOCUSFIRST:
		compOption = Composition::FOCUSSECOND;
		std::cout << "Composition: FocusSecond" << endl;
		break;
	case Composition::FOCUSSECOND:
		compOption = Composition::DARKEN;
		std::cout << "Composition: Darken" << endl;
		break;
	}
	return compOption;
}

ofImage textureModifier::applyTexture()
{
	return textureActuel;
}

ConvolutionKernel textureModifier::cycleFiltre()
{
	switch (kernel_type) {
	case ConvolutionKernel::IDENTITY:
		kernel_type = ConvolutionKernel::BLUR;
		std::cout << "Filtre: Blur" << endl;
		break;
	case ConvolutionKernel::BLUR:
		kernel_type = ConvolutionKernel::EDGE_DECTECT;
		std::cout << "Filtre: Edge detect" << endl;
		break;
	case ConvolutionKernel::EDGE_DECTECT:
		kernel_type = ConvolutionKernel::EMBOSS;
		std::cout << "Filtre: Emboss" << endl;
		break;
	case ConvolutionKernel::EMBOSS:
		kernel_type = ConvolutionKernel::SHARPEN;
		std::cout << "Filtre: Sharpen" << endl;
		break;
	case ConvolutionKernel::SHARPEN:
		kernel_type = ConvolutionKernel::IDENTITY;
		std::cout << "Filtre: Identity" << endl;
		break;
	}

	return kernel_type;
}
