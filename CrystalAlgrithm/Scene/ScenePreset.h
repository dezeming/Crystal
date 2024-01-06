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


#ifndef __algrithm_PresetScene_h__
#define __algrithm_PresetScene_h__

#include "CrystalAlgrithm/Utility/Geometry.h"
#include "CrystalAlgrithm/Utility/Spectrum.h"
#include "CrystalAlgrithm/Utility/Transform.h" 

#include "CrystalAlgrithm/DataMapper/STF.h"
#include "CrystalAlgrithm/Camera/Camera.h"
#include "CrystalAlgrithm/Material/ScatteringDistribution.h"
#include "CrystalAlgrithm/Visualizer/Visualizer.h"
#include "CrystalAlgrithm/Volume/Volume.h"
#include "CrystalAlgrithm/Shape/shape.h"
#include "CrystalAlgrithm/Light/Light.h"

#include <string>
#include <iostream>
#include <vector>

namespace CrystalAlgrithm {

/****** Basic ******/ 

inline std::string Point3fToString(const Point3f& pot) {
	return std::to_string(pot[0]) + "," + std::to_string(pot[1]) + "," + std::to_string(pot[2]);
}
inline std::string Vector3fToString(const Vector3f& vec) {
	return std::to_string(vec[0]) + "," + std::to_string(vec[1]) + "," + std::to_string(vec[2]);
}
inline std::string Vector2fToString(const Vector2f& vec) {
	return std::to_string(vec[0]) + "," + std::to_string(vec[1]);
}
inline std::string Vector3uiToString(const Vector3ui& vec) {
	return std::to_string(vec[0]) + "," + std::to_string(vec[1]) + "," + std::to_string(vec[2]);
}


class EXPORT_DLL ScenePreset {
public:
	ScenePreset();
	void reset();

	// Basic
	CameraPreset m_CameraPreset;
	VisualizerPreset m_VisualizerPreset;
	FilmPreset m_FilmPreset;

	// There can only be one volume; but because multiple meshes may form one medical data, multiple meshes are supported.
	MedicalVolumeDataPreset m_MedicalVolumeDataPreset;
	std::vector<MedicalMeshDataPreset> m_MedicalMeshDataPreset;
	std::vector<EnvironmentMeshPreset> m_EnvironmentMeshPreset;

	// Light
	std::vector<PointLightPreset> m_PointLightPreset;
	std::vector<QuadAreaLightPreset> m_QuadAreaLightPreset;
	std::vector<MeshAreaLightPreset> m_MeshAreaLightPreset;
	std::vector<DirectionalLightPreset> m_DirectionalLightPreset;

	HdrEnvironmentLightPreset m_HdrEnvironmentLightPreset;

	// DataMapper
	std::vector<STF_Preset> m_STF_Preset;

	// File path
	std::string SceneFilePath;
	std::string SceneFileName;
	std::string SceneFileDir;
	std::string GeometryFileName;
	std::string DataMapperFileName;

	// update ScenePreset From Interaction
	bool updateScenePresetFromInteraction();

	bool isValid();

	std::string ToString();
};



}



#endif




