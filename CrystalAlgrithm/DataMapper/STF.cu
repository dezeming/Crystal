/*
    Copyright (C) <2023>  <Dezeming>  <feimos@mail.ustc.edu.cn>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or any
    later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.

    Github site: <https://github.com/dezeming/Crystal>
*/

#include "STF.h"
#include "CrystalAlgrithm/Scene/ScenePreset.h"

namespace CrystalAlgrithm {

// STF_Preset
STF_Preset::STF_Preset() {
	reset();
}
void STF_Preset::reset() {
	hasDensityScale = false;
	hasOpacity = hasDiffuse = hasSpecular = hasRoughness = hasMetallic = false;
	hasEmission = hasAbsorption = hasScattering = hasHG_Phase = false;

	type = "";

	NormalizedIntensity.clear();
	NormalizedIntensity.shrink_to_fit();
	DensityScale.clear();
	DensityScale.shrink_to_fit();
	Opacity.clear();
	Opacity.shrink_to_fit();
	HG_Phase.clear();
	HG_Phase.shrink_to_fit();
	Emission.clear();
	Emission.shrink_to_fit();
	Absorption.clear();
	Absorption.shrink_to_fit();
	Scattering.clear();
	Scattering.shrink_to_fit();
	Diffuse.clear();
	Diffuse.shrink_to_fit();
	Specular.clear();
	Specular.shrink_to_fit();
	Roughness.clear();
	Roughness.shrink_to_fit();
	Metallic.clear();
	Metallic.shrink_to_fit();
}

STF_Preset::STF_Preset(const STF_Preset& other) {
	*this = other;
}
STF_Preset& STF_Preset::operator=(const STF_Preset& other) {
	if (this != &other) {
		this->hasDensityScale = other.hasDensityScale;
		this->hasOpacity = other.hasOpacity;
		this->hasDiffuse = other.hasDiffuse;
		this->hasSpecular = other.hasSpecular;
		this->hasRoughness = other.hasRoughness;
		this->hasMetallic = other.hasMetallic;
		this->hasEmission = other.hasEmission;
		this->hasAbsorption = other.hasAbsorption;
		this->hasScattering = other.hasScattering;
		this->hasHG_Phase = other.hasHG_Phase;

		this->type = other.type;

		this->NormalizedIntensity = other.NormalizedIntensity;
		this->DensityScale = other.DensityScale;
		this->Opacity = other.Opacity;
		this->HG_Phase = other.HG_Phase;
		this->Emission = other.Emission;
		this->Absorption = other.Absorption;
		this->Scattering = other.Scattering;
		this->Diffuse = other.Diffuse;
		this->Specular = other.Specular;
		this->Roughness = other.Roughness;
		this->Metallic = other.Metallic;
	}
	return *this;
}

int STF_Preset::addNewRandomNode(int currentNode, float ni, float opa) {
	double temp1, temp2;
	for (int i = 0; i < NormalizedIntensity.size() - 1; i++) {
		temp1 = NormalizedIntensity[i];
		temp2 = NormalizedIntensity[i + 1];
		if (ni >= temp1 && ni <= temp2) {

			NormalizedIntensity.insert(NormalizedIntensity.begin() + i + 1, (float)ni);
			Opacity.insert(Opacity.begin() + i + 1, (float)opa);
			if (hasDensityScale)
				DensityScale.insert(DensityScale.begin() + i + 1, (float)1.0);
			if (hasHG_Phase)
				HG_Phase.insert(HG_Phase.begin() + i + 1, (float)0.0);
			if (hasEmission)
				Emission.insert(Emission.begin() + i + 1, (float)1.0);
			if (hasAbsorption)
				Absorption.insert(Absorption.begin() + i + 1, (float)1.0);
			if (hasScattering)
				Scattering.insert(Scattering.begin() + i + 1, (float)1.0);
			if (hasDiffuse)
				Diffuse.insert(Diffuse.begin() + i + 1, (float)1.0);
			if (hasSpecular)
				Specular.insert(Specular.begin() + i + 1, (float)1.0);
			if (hasMetallic)
				Metallic.insert(Metallic.begin() + i + 1, (float)1.0);

			return i + 1;
			break;
		}
	}
	return -1;
}
int STF_Preset::deleteNode(int currentNodeIndex, int deleteNodeIndex) {
	NormalizedIntensity.erase(NormalizedIntensity.begin() + deleteNodeIndex);
	if (hasOpacity)
		Opacity.erase(Opacity.begin() + deleteNodeIndex);
	if (hasDensityScale)
		DensityScale.erase(DensityScale.begin() + deleteNodeIndex);
	if (hasHG_Phase)
		HG_Phase.erase(HG_Phase.begin() + deleteNodeIndex);
	if (hasEmission)
		Emission.erase(Emission.begin() + deleteNodeIndex);
	if (hasAbsorption)
		Absorption.erase(Absorption.begin() + deleteNodeIndex);
	if (hasScattering)
		Scattering.erase(Scattering.begin() + deleteNodeIndex);
	if (hasDiffuse)
		Diffuse.erase(Diffuse.begin() + deleteNodeIndex);
	if (hasSpecular)
		Specular.erase(Specular.begin() + deleteNodeIndex);
	if (hasMetallic)
		Metallic.erase(Metallic.begin() + deleteNodeIndex);

	if (currentNodeIndex >= deleteNodeIndex) return currentNodeIndex - 1;
	return currentNodeIndex;
}
int STF_Preset::setNodeProperty(int currentNodeIndex, float ni, float opa) {
	NormalizedIntensity[currentNodeIndex] = ni;
	if (hasOpacity)
		Opacity[currentNodeIndex] = opa;

	return currentNodeIndex;
}

unsigned int STF_Preset::parametersNum() const {
	unsigned int para = 0;
	if (hasOpacity) para++;
	if (hasDiffuse) para++;
	if (hasSpecular) para++;
	if (hasRoughness) para++;
	if (hasMetallic) para++;
	if (hasEmission) para++;
	if (hasAbsorption) para++;
	if (hasScattering) para++;
	if (hasHG_Phase) para++;
	return para;
}

bool STF_Preset::isValid(const VisualizerPreset& vp) {
	if (vp.VisualizerType == "KroesSingleScattering" && type == "Intensity") {
		if (!hasOpacity) return false;
		if (!hasDiffuse) return false;
		if (!hasSpecular) return false;
		if (!hasRoughness) return false;
		if (!hasDensityScale) return false;
	}
	if (!isValid()) return false;
	return true;
}

bool STF_Preset::isValid() {
	size_t dataSize = NormalizedIntensity.size();
	if (dataSize < 2) return false;
	if (hasOpacity && Opacity.size() != dataSize) return false;
	if (hasDensityScale && DensityScale.size() != dataSize) return false;
	if (hasDiffuse && Diffuse.size() != dataSize) return false;
	if (hasSpecular && Specular.size() != dataSize) return false;
	if (hasRoughness && Roughness.size() != dataSize) return false;
	if (hasMetallic && Metallic.size() != dataSize) return false;
	if (hasEmission && Emission.size() != dataSize) return false;
	if (hasAbsorption && Absorption.size() != dataSize) return false;
	if (hasScattering && Scattering.size() != dataSize) return false;
	if (hasHG_Phase && HG_Phase.size() != dataSize) return false;

	if (type != "Intensity" && type != "GradientMagnitude" && type != "Mask") return false;

	// Determine whether the elements are in ascending order
	for (size_t i = 1; i < NormalizedIntensity.size(); ++i) {
		if (NormalizedIntensity[i] < NormalizedIntensity[i - 1]) {
			return false;
		}
	}
	// Determine if the maximum and minimum values are 0 and 1 respectively
	if (!IS_CLOSE(NormalizedIntensity[0], 0.0f, 0.001) ||
		!IS_CLOSE(NormalizedIntensity[dataSize - 1], 1.0f, 0.001)) {
		return false;
	}
	NormalizedIntensity[0] = 0.0f; NormalizedIntensity[dataSize - 1] = 1.0f;

	return true;
}

std::string STF_Preset::ToString() {
	std::string s;
	if (!isValid()) {
		s += "Invalid ";
	}
	s += "Scalar TransferFunction Preset Properties: Size=[" + std::to_string(NormalizedIntensity.size()) + "]";
	if (hasOpacity) s += " Opacity ";
	if (hasDensityScale) s += " DensityScale ";
	if (hasDiffuse) s += " Diffuse ";
	if (hasSpecular) s += " Specular ";
	if (hasRoughness) s += " Roughness ";
	if (hasMetallic) s += " Metallic ";
	if (hasEmission) s += " Emission ";
	if (hasAbsorption) s += " Absorption ";
	if (hasScattering) s += " Scattering ";
	if (hasHG_Phase) s += " HG_Phase ";
	return s;
}

}



