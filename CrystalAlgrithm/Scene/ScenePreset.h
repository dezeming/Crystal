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


#ifndef __PresetScene_h__
#define __PresetScene_h__

#include "CrystalAlgrithm/Utility/Geometry.h"
#include "CrystalAlgrithm/Utility/Spectrum.h"
#include "CrystalAlgrithm/Utility/Transform.h" 

#include <string>
#include <iostream>
#include <vector>

namespace CrystalAlgrithm{

/****** Basic ******/ 

class CameraPreset {
public:
	CameraPreset() {
		reset();
	}
	void reset() {
		CameraType = "perspective";
		fov = 45.0f;
		lookatFrom[0] = 0.0f; lookatFrom[1] = 0.0f; lookatFrom[2] = 5.0f;
		lookatTo[0] = 0.0f; lookatTo[1] = 0.0f; lookatTo[2] = 0.0f;
	}
	std::string CameraType;
	float fov;
	Point3f lookatFrom, lookatTo;

	bool isValid() {
		if (fov < 5.0f || fov > 170.f) return false;
		// Currently only supports perspective projection cameras
		if (CameraType != "perspective") return false;
		return true;
	}

	std::string ToString() {
		return "CameraPreset: "
			"  CameraType:[" + CameraType + "]" + 
			"  fov:[" + std::to_string(fov) + "]" +
			" LookAt:from[" + std::to_string(lookatFrom[0]) + "," + std::to_string(lookatFrom[1]) + "," + std::to_string(lookatFrom[2]) + "]" + 
			"to[" + std::to_string(lookatTo[0]) + "," + std::to_string(lookatTo[1]) + "," + std::to_string(lookatTo[2]) +"]";
	}
};

class FilmPreset {
public:
	FilmPreset() {
		width = 1024;
		height = 768;
	}
	void reset() {
		width = 1024;
		height = 768;
	}
	size_t width, height;

	bool isValid() {
		// Currently, only resolutions up to 4000 * 4000 are supported.
		if (width > 4000 || height > 4000) {
			return false;
		}
		return true;
	}

	std::string ToString() {
		return "FilmPreset: "
			"  width:[" + std::to_string(width) + "]"
			+ "  height:[" + std::to_string(height) + "]";
	}
};

class VisualizerPreset {
public:
	VisualizerPreset() {
		reset();
	}
	void reset() {
		VisualizerType = "";
	}
	std::string VisualizerType;

	bool isValid() {
		if (VisualizerType != "kroesSSVisualizer") {
			return false;
		}
		return true;
	}

	std::string ToString() {
		return "VisualizerPreset: " 
		"  VisualizerType:[" + VisualizerType + "]";
	}
};

/****** Geometry ******/

// Volume & Mesh

class MedicalVolumeDataPreset {
public:
	MedicalVolumeDataPreset() {
		reset();
	}

	void reset() {

	}
	bool isValid() {

	}
	std::string ToString() {

		return "";
	}
};

class MedicalMeshDataPreset {
public:
	MedicalMeshDataPreset() {
		reset();
	}

	void reset() {

	}
	bool isValid() {

	}
	std::string ToString() {

		return "";
	}
};

class EnvironmentMeshPreset {
public:
	EnvironmentMeshPreset() {
		reset();
	}

	void reset() {

	}
	bool isValid() {

	}
	std::string ToString() {

		return "";
	}
};

// Light

class PointLightPreset {
public:
	PointLightPreset() {
		reset();
	}

	void reset() {

	}
	bool isValid() {

	}
	std::string ToString() {

		return "";
	}
};

class QuadAreaLightPreset {
public:
	QuadAreaLightPreset() {
		reset();
	}

	void reset() {

	}
	bool isValid() {

	}
	std::string ToString() {

		return "";
	}
};

class HdrEnvironmentLightPreset {
public:
	HdrEnvironmentLightPreset() {
		reset();
	}

	void reset() {

	}
	bool isValid() {

	}

	std::string ToString() {

		return "";
	}
};

/****** Data Mapper ******/ 

// Scalar Transfer Function
class STF_Preset {
public:
	STF_Preset() {
		reset();
	}

	void reset() {
		hasDensityScale = false;
		hasOpacity = hasDiffuse = hasSpecular = hasRoughness = hasMetallic = false;
		hasEmission = hasAbsorption = hasScattering = hasHG_Phase = false;

		type = "";

		NormalizedIntensity.clear();
		NormalizedIntensity.shrink_to_fit();
		DensityScale.clear();
		DensityScale.shrink_to_fit();
		Opacity.clear();
		Opacity.shrink_to_fit();
		HG_Phase.clear();
		HG_Phase.shrink_to_fit();
		Emission.clear();
		Emission.shrink_to_fit();
		Absorption.clear();
		Absorption.shrink_to_fit();
		Scattering.clear();
		Scattering.shrink_to_fit();
		Diffuse.clear();
		Diffuse.shrink_to_fit();
		Specular.clear();
		Specular.shrink_to_fit();
		Roughness.clear();
		Roughness.shrink_to_fit();
		Metallic.clear();
		Metallic.shrink_to_fit();
	}

	// global properties

	// local properties

	bool hasDensityScale;
	bool hasOpacity, hasDiffuse, hasSpecular, hasRoughness, hasMetallic;
	bool hasEmission, hasAbsorption, hasScattering, hasHG_Phase;

	std::string type;

	std::vector<float> NormalizedIntensity;
	std::vector<float> DensityScale;
	std::vector<float> Opacity;
	std::vector<float> HG_Phase;
	std::vector<Spectrum3> Emission;
	std::vector<Spectrum3> Absorption;
	std::vector<Spectrum3> Scattering;
	std::vector<Spectrum3> Diffuse;
	std::vector<Spectrum3> Specular;
	std::vector<float> Roughness;
	std::vector<Spectrum3> Metallic;

	bool isValid(const VisualizerPreset& vp) {
		if (vp.VisualizerType == "kroesSSVisualizer") {
			if (!hasOpacity) return false;
			if (!hasDiffuse) return false;
			if (!hasSpecular) return false;
			if (!hasRoughness) return false;
			if (!hasDensityScale) return false;
		}
		if (!isValid()) return false;
		return true;
	}

	bool isValid() {
		size_t dataSize = NormalizedIntensity.size();
		if (dataSize < 2) return false;
		if (hasOpacity && Opacity.size() != dataSize) return false;
		if (hasDensityScale && DensityScale.size() != dataSize) return false;
		if (hasDiffuse && Diffuse.size() != dataSize) return false;
		if (hasSpecular && Specular.size() != dataSize) return false;
		if (hasRoughness && Roughness.size() != dataSize) return false;
		if (hasMetallic && Metallic.size() != dataSize) return false;
		if (hasEmission && Emission.size() != dataSize) return false;
		if (hasAbsorption && Absorption.size() != dataSize) return false;
		if (hasScattering && Scattering.size() != dataSize) return false;
		if (hasHG_Phase && HG_Phase.size() != dataSize) return false;

		if (type != "Intensity" && type != "GradientMagnitude") return false;

		// Determine whether the elements are in ascending order
		for (size_t i = 1; i < NormalizedIntensity.size(); ++i) {
			if (NormalizedIntensity[i] < NormalizedIntensity[i - 1]) {
				return false; 
			}
		}
		// Determine if the maximum and minimum values are 0 and 1 respectively
		if (!IS_CLOSE(NormalizedIntensity[0], 0.0f, 0.001) ||
			!IS_CLOSE(NormalizedIntensity[dataSize - 1], 1.0f, 0.001)) {
			return false;
		}
		NormalizedIntensity[0] = 0.0f; NormalizedIntensity[dataSize - 1] = 1.0f;

		return true;
	}

	std::string ToString() {	
		std::string s;
		if (!isValid()) {
			s += "Invalid ";
		}
		s += "Scalar TransferFunction Preset Properties: Size=[" + std::to_string(NormalizedIntensity.size()) + "]";
		if (hasOpacity) s += " Opacity ";
		if (hasDensityScale) s += " DensityScale ";
		if (hasDiffuse) s += " Diffuse ";
		if (hasSpecular) s += " Specular ";
		if (hasRoughness) s += " Roughness ";
		if (hasMetallic) s += " Metallic ";
		if (hasEmission) s += " Emission ";
		if (hasAbsorption) s += " Absorption ";
		if (hasScattering) s += " Scattering ";
		if (hasHG_Phase) s += " HG_Phase ";
		return s;
	}

private:

};

class ScenePreset {
public:
	ScenePreset()
	{
		reset();
	}

	void reset() {
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
	HdrEnvironmentLightPreset m_HdrEnvironmentLightPreset;

	// DataMapper
	std::vector<STF_Preset> m_STF_Preset;

	// File path
	std::string SceneFilePath;
	std::string SceneFileName;
	std::string SceneFileDir;
	std::string GeometryFileName;
	std::string DataMapperFileName;

	std::string ToString() {
		return "ScenePreset: "
			"  SceneFilePath:[" + SceneFilePath + "]" +
			"  SceneFileDir:[" + SceneFileDir + "]" +
			"  SceneFileName:[" + SceneFileName + "]" +
			"  GeometryFileName:[" + GeometryFileName + "]" +
			"  DataMapperFileName:[" + DataMapperFileName + "]";
	}
};



}



#endif




