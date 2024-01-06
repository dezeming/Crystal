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

#ifndef __algrithm_Primitive_h__
#define __algrithm_Primitive_h__


#include "CrystalAlgrithm/Utility/Common.hpp"

#include "CrystalAlgrithm/Utility/Geometry.h"
#include "CrystalAlgrithm/Utility/Spectrum.h"
#include "CrystalAlgrithm/Utility/Transform.h" 

#include <string>
#include <iostream>
#include <vector>

#include "sphere.h"
#include "surface.h"


namespace CrystalAlgrithm {


class EXPORT_DLL NonLuminousPrimitiveTable {
public:
    NonLuminousPrimitiveTable();
    ~NonLuminousPrimitiveTable();

    Sphere* sphereArray;
    Triangle* triangleArray;
    Rectangle* rectangleArray;

    Sphere* sphereArray_device;
    Triangle* triangleArray_device;
    Rectangle* rectangleArray_device;

};

class EXPORT_DLL LightPrimitiveTable {
public:
    LightPrimitiveTable();
    ~LightPrimitiveTable();

    Sphere* sphereArray;
    Triangle* triangleArray;
    Rectangle* rectangleArray;

    Sphere* sphereArray_device;
    Triangle* triangleArray_device;
    Rectangle* rectangleArray_device;
};

class EXPORT_DLL MedicalPrimitiveTable {
public:
    MedicalPrimitiveTable();
    ~MedicalPrimitiveTable();

    Sphere* sphereArray;
    Triangle* triangleArray;

    Sphere* sphereArray_device;
    Triangle* triangleArray_device;


};


class EXPORT_DLL Primitive {
public:
    Primitive(unsigned int typeID, unsigned int numID);
    Primitive();
    ~Primitive();

    // primitive type
    unsigned int typeIndex;
    // primitive number
    unsigned int numIndex;

    Bounds3f ObjectBound() const {
        return Bounds3f();
    }
    Bounds3f WorldBound() const {

        return Bounds3f();
    }
};



}



#endif


