#include "TextureModifier.h"

void textureModifier::setup()
{
	// importer l'image source
	string fileName;
	stringstream ss;
	for (int i = 1; i <= nbTexture; i++) {
		fileName = "texture" + to_string(i) + ".jpg";
		textures[i-1].load(fileName);
	}
	textureActuel = textures[0];

	// sélectionner le filtre de convolution par défaut
	kernel_type = ConvolutionKernel::IDENTITY;
	compOption = Composition::ADD;
}


// fonction de filtrage par convolution
void textureModifier::filter()
{
	int ind;
	int xOff;
	int yOff;
	float mod;
	float colors[3];
	ofColor newColor;
	ofColor color1;

	int width = textureActuel.getWidth();
	int height = textureActuel.getHeight();
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
						switch (kernel_type)
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
						color1 = textureActuel.getColor(xOff, yOff);
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
}


ofImage textureModifier::compositionTexture() {
	int ind1 = cText;
	int ind2 = (cText+1)%nbTexture;
		int width = min(textures[ind1].getWidth(),textures[ind2].getWidth());
		int height = min(textures[ind1].getHeight(), textures[ind2].getHeight());

		textureRetour.allocate(width, height, OF_IMAGE_COLOR);

		ofColor newColor;
		ofColor color1;
		ofColor color2;

		
		for (int y = 0; y < height; ++y)
		{
			for (int x = 0; x < width; ++x)
			{
				color1 = textures[cText].getColor(x, y);
				color2 = textures[(cText+1)%nbTexture].getColor(x, y);
				switch (compOption) {
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
	switch (compOption) {
	case Composition::DARKEN:
		compOption = Composition::LIGHTEN;
		break;
	case Composition::LIGHTEN:
		compOption = Composition::ADD;
		break;
	case Composition::ADD:
		compOption = Composition::AVERAGE;
		break;
	case Composition::AVERAGE:
		compOption = Composition::SUBSTRACT;
		break;
	case Composition::SUBSTRACT:
		compOption = Composition::FOCUSFIRST;
		break;
	case Composition::FOCUSFIRST:
		compOption = Composition::FOCUSSECOND;
		break;
	case Composition::FOCUSSECOND:
		compOption = Composition::DARKEN;
		break;

	}
	return textureRetour;
}

ofImage textureModifier::cycleTexture()
{
	++cText;
	cText %= nbTexture;
	std::cout << cText << endl;
	textureActuel = textures[cText];
	return textureActuel;
}

ofImage textureModifier::cycleFiltre()
{
	switch (kernel_type) {
	case ConvolutionKernel::IDENTITY:
		kernel_type = ConvolutionKernel::BLUR;
		break;
	case ConvolutionKernel::BLUR:
		kernel_type = ConvolutionKernel::EDGE_DECTECT;
		break;
	case ConvolutionKernel::EDGE_DECTECT:
		kernel_type = ConvolutionKernel::EMBOSS;
		break;
	case ConvolutionKernel::EMBOSS:
		kernel_type = ConvolutionKernel::SHARPEN;
		break;
	case ConvolutionKernel::SHARPEN:
		kernel_type = ConvolutionKernel::IDENTITY;
		break;
	}
	filter();
	return textureRetour;
}


