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

#ifndef __algrithm_Volume_h__
#define __algrithm_Volume_h__

#include "CrystalAlgrithm/Utility/Common.hpp"

#include "CrystalAlgrithm/Utility/Geometry.h"
#include "CrystalAlgrithm/Utility/Spectrum.h"
#include "CrystalAlgrithm/Utility/Transform.h" 

#include <string>
#include <iostream>
#include <vector>

namespace CrystalAlgrithm {

class VolumeInfo;

class EXPORT_DLL MedicalVolumeDataPreset {
public:

	MedicalVolumeDataPreset();
	void reset();

	bool loadAndInit(VolumeInfo& volume);
	bool isValid();

	std::string dataFileType;
	std::string dataFilePath;

	std::string datatype;

	Vector3ui resolution;
	Vector3f pixelSpacing;

	Vector3ui permute;

	Vector2f RotateXY;
	Vector3f Translate_V;
	Transform RotateX, RotateY, Translate;

	std::string structure;

	std::string ToString();
};

class EXPORT_DLL VolumeInfo {

public:
	Vector3ui resolution;
	Vector3f pixelSpacing;

	Vector3ui permute;

	Vector2f RotateXY;
	Vector3f Translate_V;
	Transform RotateX, RotateY, Translate;

	float* data;
	BoundsVolume volumeBound;

};








}

#endif

