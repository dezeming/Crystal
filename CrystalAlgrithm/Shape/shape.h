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

#ifndef __algrithm_shape_h__
#define __algrithm_shape_h__

#include "CrystalAlgrithm/Utility/Common.hpp"

#include "CrystalAlgrithm/Utility/Geometry.h"
#include "CrystalAlgrithm/Utility/Spectrum.h"
#include "CrystalAlgrithm/Utility/Transform.h" 

#include <string>
#include <iostream>
#include <vector>

namespace CrystalAlgrithm {

class EXPORT_DLL MedicalMeshDataPreset {
public:
	MedicalMeshDataPreset();
	void reset();

	bool isValid();
	std::string ToString();
};

class EXPORT_DLL EnvironmentMeshPreset {
public:
	EnvironmentMeshPreset();
	void reset();

    bool isValid();
    std::string ToString();
};

class EXPORT_DLL SphereDataPreset {
public:
    SphereDataPreset();
    void reset();

    bool isValid();
    std::string ToString();
};








}


#endif






