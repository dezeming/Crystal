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

#ifndef __algrithm_ScatteringDistribution_h__
#define __algrithm_ScatteringDistribution_h__

#include "CrystalAlgrithm/Utility/Common.hpp"

#include "CrystalAlgrithm/Utility/Geometry.h"
#include "CrystalAlgrithm/Utility/Spectrum.h"
#include "CrystalAlgrithm/Utility/Transform.h" 

#include <string>
#include <iostream>
#include <vector>

namespace CrystalAlgrithm {


//texture
class EXPORT_DLL TexturePreset {
public:
	TexturePreset();
	void reset();

	bool isValid();
	std::string ToString();

	std::string name;
	std::string type;
	std::string filePath;
	Spectrum3 albedo;
};

// ScatteringDistributionPreset
class EXPORT_DLL ScatteringDistributionPreset {
public:
	ScatteringDistributionPreset();
	void reset();

	bool isValid();
	std::string ToString();

	std::string name;
	std::string type;

	std::string diffTexName;
	std::string specTexName;
	std::string roughnessTexName;
	std::string metallicTexName;
	std::string alphaTexName;
};

// material
class EXPORT_DLL MaterialPreset {
public:
	MaterialPreset();
	void reset();

	bool isValid();
	std::string ToString();

	unsigned int sdfCount;
	// Name of Scattering Distribution
	std::string SdfName[4];
};



class EXPORT_DLL LambertianReflection {
public:

	unsigned int albedoTexTypeIndex;
	unsigned int albedoTexNumIndex;


};

class EXPORT_DLL SpecularReflection {
public:

	unsigned int albedoTexTypeIndex;
	unsigned int albedoTexNumIndex;


};

class EXPORT_DLL SpecularRefraction {
public:

	unsigned int albedoTexTypeIndex;
	unsigned int albedoTexNumIndex;


};

class EXPORT_DLL MicrosurfaceReflection {
public:




};




}


#endif



