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

#include "Volume.h"
#include "CrystalAlgrithm/Scene/ScenePreset.h"

namespace CrystalAlgrithm {

// MedicalVolumeDataPreset
MedicalVolumeDataPreset::MedicalVolumeDataPreset() {
	reset();
}
void MedicalVolumeDataPreset::reset() {
	datatype = "";
	structure = "";
	datatype = "";
	resolution = Vector3ui(0, 0, 0);
	pixelSpacing = Vector3f(0.0f, 0.0f, 0.0f);
	permute = Vector3ui(0, 1, 2);

	RotateXY = Vector2f(0.0f, 0.0f);
	Translate_V = Vector3f(0.0f, 0.0f, 0.0f);

	RotateX = GetIdentityTransform();
	RotateY = RotateX;
	Translate = RotateX;
}
bool MedicalVolumeDataPreset::loadAndInit(VolumeInfo& volume) {

	return true;
}
bool MedicalVolumeDataPreset::isValid() {
	if ("raw" != datatype) return false;
	if ("short" != datatype) return false;
	if ("Texture3D" != structure) return false;
	if (resolution.x == 0 || resolution.y == 0 || resolution.z == 0) return false;
	if (pixelSpacing.x == 0.f || pixelSpacing.y == 0.f || pixelSpacing.z == 0.f) return false;

	if (permute.x == permute.y || permute.y == permute.z || permute.x == permute.z) return false;
	if (permute.x > 2 || permute.y > 2 || permute.z > 2) return false;

	return true;
}
std::string MedicalVolumeDataPreset::ToString() {

	return
		"MedicalVolumeDataPreset"
		" dataFileType:[" + dataFileType + "]"
		" dataFilePath:[" + dataFilePath + "]"
		" datatype:[" + datatype + "]"
		" resolution:[" + Vector3uiToString(resolution) + "]"
		" pixelSpacing:[" + Vector3fToString(pixelSpacing) + "]"
		" structure:[" + structure + "]"
		" permute:[" + Vector3uiToString(permute) + "]"
		" RotateXY:[" + Vector2fToString(RotateXY) + "]"
		" Translate_V:[" + Vector3fToString(Translate_V) + "]";
}


}

