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


#include "ScenePreset.h"

namespace CrystalAlgrithm{

// ScenePreset
ScenePreset::ScenePreset()
{
	reset();
}
void ScenePreset::reset() {
	SceneFilePath = "";
	SceneFileName = "";
	SceneFileDir = "";
	GeometryFileName = "";
	DataMapperFileName = "";

	m_CameraPreset.reset();
	m_VisualizerPreset.reset();
	m_FilmPreset.reset();

	m_MedicalMeshDataPreset.clear();
	m_MedicalMeshDataPreset.shrink_to_fit();
	m_EnvironmentMeshPreset.clear();
	m_EnvironmentMeshPreset.shrink_to_fit();

	m_PointLightPreset.clear();
	m_PointLightPreset.shrink_to_fit();
	m_QuadAreaLightPreset.clear();
	m_QuadAreaLightPreset.shrink_to_fit();

	m_STF_Preset.clear();
	m_STF_Preset.shrink_to_fit();
}


bool ScenePreset::updateScenePresetFromInteraction() {

    return false;
}

bool ScenePreset::isValid() {
	bool flag = true;
	// Basic Check
	flag = flag && m_CameraPreset.isValid();
	flag = flag && m_VisualizerPreset.isValid();
	flag = flag && m_FilmPreset.isValid();

	flag = flag && m_MedicalVolumeDataPreset.isValid();
	for (int i = 0; i < m_MedicalMeshDataPreset.size(); i++) {
		flag = flag && m_MedicalMeshDataPreset[i].isValid();
	}
	for (int i = 0; i < m_EnvironmentMeshPreset.size(); i++) {
		flag = flag && m_EnvironmentMeshPreset[i].isValid();
	}

	for (int i = 0; i < m_PointLightPreset.size(); i++) {
		flag = flag && m_PointLightPreset[i].isValid();
	}
	for (int i = 0; i < m_QuadAreaLightPreset.size(); i++) {
		flag = flag && m_QuadAreaLightPreset[i].isValid();
	}
	flag = flag && m_HdrEnvironmentLightPreset.isValid();

	for (int i = 0; i < m_STF_Preset.size(); i++) {
		flag = flag && m_STF_Preset[i].isValid();
	}

	// Semantic Check

	// Adaptability of Visualizers and DataMapper


	return flag;
}

std::string ScenePreset::ToString() {
	return "ScenePreset: "
		"  SceneFilePath:[" + SceneFilePath + "]" +
		"  SceneFileDir:[" + SceneFileDir + "]" +
		"  SceneFileName:[" + SceneFileName + "]" +
		"  GeometryFileName:[" + GeometryFileName + "]" +
		"  DataMapperFileName:[" + DataMapperFileName + "]";
}




}








