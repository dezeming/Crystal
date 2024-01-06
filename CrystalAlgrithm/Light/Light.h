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

#ifndef __algrithm_Light_h__
#define __algrithm_Light_h__

#include "CrystalAlgrithm/Utility/Common.hpp"

#include "CrystalAlgrithm/Utility/Geometry.h"
#include "CrystalAlgrithm/Utility/Spectrum.h"
#include "CrystalAlgrithm/Utility/Transform.h" 

#include <string>
#include <iostream>
#include <vector>

namespace CrystalAlgrithm {

// Light
class EXPORT_DLL PointLightPreset {
public:
	PointLightPreset();
	void reset();

	bool isValid();
	std::string ToString();
};

class EXPORT_DLL QuadAreaLightPreset {
public:
	QuadAreaLightPreset();
	void reset();

	bool isValid();
	std::string ToString();
};

class EXPORT_DLL MeshAreaLightPreset {
public:
	MeshAreaLightPreset();
	void reset();

	bool isValid();
	std::string ToString();
};

class EXPORT_DLL DirectionalLightPreset {
public:
	DirectionalLightPreset();
	void reset();

	bool isValid();
	std::string ToString();
};

class EXPORT_DLL HdrEnvironmentLightPreset {
public:
	HdrEnvironmentLightPreset();
	void reset();

	bool isValid();
	std::string ToString();
};


class PointLight {
public:
	PointLight() {

	}

	// emission = radi * scale
	Spectrum3 emission;

	Spectrum3 radi;
	float scale;
	Point3f pos;

};





}

#endif





