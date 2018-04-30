#pragma once
#include "MaterialType.h"
class MaterialLambert : public MaterialType {
private:
	ofShader shader;
public:
	MaterialLambert();

	void beginMaterial(map<int, ofLight*>& lights) override;

	void endMaterial() override;

	void setEmissiveColor(ofColor color) override;

	void setDiffuseColor(ofColor color) override;

	void setSpecularColor(ofColor color) override;

	void setAmbientColor(ofColor color) override;

	void setShininess(float shininess) override;
};