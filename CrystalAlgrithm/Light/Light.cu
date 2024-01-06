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

#include "Light.h"

namespace CrystalAlgrithm {

// PointLightPreset
PointLightPreset::PointLightPreset() {
    reset();
}
void PointLightPreset::reset() {

}
bool PointLightPreset::isValid() {
    return true;
}
std::string PointLightPreset::ToString() {

    return "";
}


// QuadAreaLightPreset
QuadAreaLightPreset::QuadAreaLightPreset() {
    reset();
}
void QuadAreaLightPreset::reset() {

}

bool QuadAreaLightPreset::isValid() {
    return true;
}
std::string QuadAreaLightPreset::ToString() {

    return "";
}


// MeshAreaLightPreset
MeshAreaLightPreset::MeshAreaLightPreset() {

}
void MeshAreaLightPreset::reset() {

}

bool MeshAreaLightPreset::isValid() {
    return true;
}
std::string MeshAreaLightPreset::ToString() {
    return "";
}


// DirectionalLightPreset
DirectionalLightPreset::DirectionalLightPreset() {

}
void DirectionalLightPreset::reset() {

}

bool DirectionalLightPreset::isValid() {
    return true;
}
std::string DirectionalLightPreset::ToString() {
    return "";
}


// HdrEnvironmentLightPreset
HdrEnvironmentLightPreset::HdrEnvironmentLightPreset() {
    reset();
}
void HdrEnvironmentLightPreset::reset() {

}

bool HdrEnvironmentLightPreset::isValid() {
    return true;
}
std::string HdrEnvironmentLightPreset::ToString() {

    return "";
}





}

