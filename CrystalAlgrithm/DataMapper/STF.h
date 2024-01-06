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

#ifndef __algrithm_STF_H__
#define __algrithm_STF_H__

#include "CrystalAlgrithm/Utility/Common.hpp"

#include "CrystalAlgrithm/Utility/Geometry.h"
#include "CrystalAlgrithm/Utility/Spectrum.h"
#include "CrystalAlgrithm/Utility/Transform.h" 

#include <string>
#include <iostream>
#include <vector>

namespace CrystalAlgrithm {

class VisualizerPreset;

/****** Data Mapper ******/

// Scalar Transfer Function
class EXPORT_DLL STF_Preset {
public:
	STF_Preset();
	void reset();

	// copy constructor
	STF_Preset(const STF_Preset& other);
	STF_Preset& operator=(const STF_Preset& other);

	// global properties

	// local properties

	bool hasDensityScale;
	bool hasOpacity, hasDiffuse, hasSpecular, hasRoughness, hasMetallic;
	bool hasEmission, hasAbsorption, hasScattering, hasHG_Phase;

	std::string type;

	std::vector<float> NormalizedIntensity;
	std::vector<float> DensityScale;
	std::vector<float> Opacity;
	std::vector<float> HG_Phase;
	std::vector<Spectrum3> Emission;
	std::vector<Spectrum3> Absorption;
	std::vector<Spectrum3> Scattering;
	std::vector<Spectrum3> Diffuse;
	std::vector<Spectrum3> Specular;
	std::vector<float> Roughness;
	std::vector<float> Metallic;

	int addNewRandomNode(int currentNode, float ni, float opa);
	int deleteNode(int currentNodeIndex, int deleteNodeIndex);
	int setNodeProperty(int currentNodeIndex, float ni, float opa);

	unsigned int parametersNum() const;

	bool isValid(const VisualizerPreset& vp);

	bool isValid();

	std::string ToString();

private:

};

class EXPORT_DLL STF {
public:


};


}


#endif


