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

#include <string>
#include <iostream>
#include <vector>

namespace CrystalAlgrithm{

class MedicalVolumeDataPreset;
class STF_Preset;

class PointLightPreset;
class QuadAreaLightPreset;



class SceneGeometryPreset {
public:
	SceneGeometryPreset() {
		SceneGeometryFile = "";
	}

	std::string SceneGeometryFile;

	std::string ToString() {
		return "SceneGeometryPreset: "
			"  SceneGeometryFile:[" + SceneGeometryFile + "]";
	}
};

class CameraPreset {
public:
	CameraPreset() {
		CameraType = "";
		fov = 45.0f;
		lookatFrom[0] = 0.0f; lookatFrom[1] = 0.0f; lookatFrom[2] = 5.0f;
		lookatTo[0] = 0.0f; lookatTo[1] = 0.0f; lookatTo[2] = -1.0f;
	}
	std::string CameraType;
	float fov;
	float lookatFrom[3], lookatTo[3];

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
		width = 0;
		height = 0;
	}
	int width, height;

	std::string ToString() {
		return "FilmPreset: "
			"  width:[" + std::to_string(width) + "]"
			+ "  height:[" + std::to_string(height) + "]";
	}
};

class VisualizerPreset {
public:
	VisualizerPreset() {
		VisualizerType = "";
	}
	std::string VisualizerType;

	std::string ToString() {
		return "VisualizerPreset: " 
		"  VisualizerType:[" + VisualizerType + "]";
	}
};

class MedicalVolumeDataPreset {
public:
	std::string ToString() {

		return "";
	}
};

class MedicalMeshDataPreset {
public:

};

class EnvironmentMeshPreset {
public:

};

class PointLightPreset {
public:
	std::string ToString() {

		return "";
	}
};

class QuadAreaLightPreset {
public:
	std::string ToString() {

		return "";
	}
};

class HdrEnvironmentLightPreset {
public:
	std::string ToString() {

		return "";
	}
};

// Scalar Transfer Function
class STF_Preset {
public:
	STF_Preset() {

	}

	std::string ToString() {

		return "";
	}
};

class ScenePreset {
public:
	ScenePreset() :
		m_CameraPreset(),
		m_VisualizerPreset(),
		m_FilmPreset(),
		m_SceneGeometryPreset()
	{
		SceneFilePath = "";
		SceneFileName = "";
		SceneFileDir = "";
	}

	CameraPreset m_CameraPreset;
	VisualizerPreset m_VisualizerPreset;
	FilmPreset m_FilmPreset;

	SceneGeometryPreset m_SceneGeometryPreset;
	std::vector<STF_Preset> m_STF_Preset;

	std::vector<PointLightPreset> m_PointLightPreset;
	std::vector<QuadAreaLightPreset> m_QuadAreaLightPreset;

	std::string SceneFilePath;
	std::string SceneFileName;
	std::string SceneFileDir;

	std::string ToString() {
		return "ScenePreset: "
			"  SceneFilePath:[" + SceneFilePath + "]" +
			"  SceneFileName:[" + SceneFileName + "]" +
			"  SceneFileDir:[" + SceneFileDir + "]";
	}
};



}



#endif




