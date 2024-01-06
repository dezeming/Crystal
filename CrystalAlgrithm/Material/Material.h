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

#ifndef __algrithm_Material_h__
#define __algrithm_Material_h__

#include "CrystalAlgrithm/Material/ScatteringDistribution.h"

namespace CrystalAlgrithm {


class Material {
public:
	Material();
	~Material();

	// scattering distribution type
	unsigned int sdType[4];
	// scattering distribution type
	unsigned int sdIndex[4];
	// scattering distribution ratio
	float ratio[4];

};

class MaterialManager {
public:
	MaterialManager();
	~MaterialManager();


	// Scattering Distribution
	unsigned int lambReflectCount;
	LambertianReflection* lambReflect;

	// Material
	unsigned int materialCount;
	Material* material;

};




}


#endif






