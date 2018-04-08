#pragma once
#include "MaterialType.h"
class BaseMaterial : public MaterialType {
	private:
		ofMaterial material;
	public:
		void beginMaterial(vector<ofLight> lights) override;

		void endMaterial() override;

		void setEmissiveColor(ofColor color) override;

		void setDiffuseColor(ofColor color) override;

		void setSpecularColor(ofColor color) override;

		void setAmbientColor(ofColor color) override;

		void setShininess(float shininess) override;
};