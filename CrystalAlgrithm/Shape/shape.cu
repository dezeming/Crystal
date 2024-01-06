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

#include "shape.h"

namespace CrystalAlgrithm {

// MedicalMeshDataPreset
MedicalMeshDataPreset::MedicalMeshDataPreset() {
    reset();
}

void MedicalMeshDataPreset::reset() {

}
bool MedicalMeshDataPreset::isValid() {
    return true;
}
std::string MedicalMeshDataPreset::ToString() {

    return "";
}


// EnvironmentMeshPreset
EnvironmentMeshPreset::EnvironmentMeshPreset() {
    reset();
}

void EnvironmentMeshPreset::reset() {

}
bool EnvironmentMeshPreset::isValid() {
    return true;
}
std::string EnvironmentMeshPreset::ToString() {

    return "";
}

// SphereDataPreset
SphereDataPreset::SphereDataPreset() {

}
void SphereDataPreset::reset() {

}

bool SphereDataPreset::isValid() {
    return true;
}
std::string SphereDataPreset::ToString() {
    return "";
}







}


