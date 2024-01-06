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

#include "Camera.h"
#include "CrystalAlgrithm/Scene/ScenePreset.h"
#include "CrystalAlgrithm/Utility/Sampling.h"

#include <cuda.h>

#define CameraDebug true

namespace CrystalAlgrithm {

// CameraPreset
CameraPreset::CameraPreset() {
	reset();
}
void CameraPreset::reset() {
	CameraType = "perspective";
	fov = 45.0f;
	lookatFrom[0] = 0.0f; lookatFrom[1] = 0.0f; lookatFrom[2] = 5.0f;
	lookatTo[0] = 0.0f; lookatTo[1] = 0.0f; lookatTo[2] = 0.0f;
}
bool CameraPreset::isValid() {
	if (fov < 5.0f || fov > 170.f) return false;
	// Currently only supports perspective projection cameras
	if (CameraType != "perspective") return false;
	return true;
}
std::string CameraPreset::ToString() {
	return "CameraPreset: "
		"  CameraType:[" + CameraType + "]" +
		"  fov:[" + std::to_string(fov) + "]" +
		" LookAt:from[" + Point3fToString(lookatFrom) + "]" +
		"to[" + Point3fToString(lookatTo) + "]";
}

// FilmPreset
FilmPreset::FilmPreset() {
	width = 1024;
	height = 768;
}
void FilmPreset::reset() {
	width = 1024;
	height = 768;
}
bool FilmPreset::isValid() {
	// Currently, only resolutions up to 4000 * 4000 are supported.
	if (width > 4000 || height > 4000) {
		return false;
	}
	return true;
}
std::string FilmPreset::ToString() {
	return "FilmPreset: "
		"  width:[" + std::to_string(width) + "]"
		+ "  height:[" + std::to_string(height) + "]";
}

// Film

Film::Film() {
	if (CameraDebug && !DisablePrintInfo)
		Print_CPU_Info("Create Film Object");

	finalUChar4Buffer_host = nullptr;
	finalFloat4Buffer_host = nullptr;

	finalUChar4Buffer_device = nullptr;
	finalFloat4Buffer_device = nullptr;
}

void Film::init(const Point2i& res, unsigned int type, float maxSampleLuminance) {
	if (CameraDebug && !DisablePrintInfo)
		Print_CPU_Info("Init Film Object");

	resolution = res;

	finalUChar4Buffer_host = new uchar4[res.x * res.y];
	finalFloat4Buffer_host = new float4[res.x * res.y];

	cudaMalloc(&finalUChar4Buffer_device, res.x * res.y * sizeof(uchar4));
	cudaMalloc(&finalFloat4Buffer_device, res.x * res.y * sizeof(float4));
}

Film::~Film() {
	if (CameraDebug && !DisablePrintInfo)
		Print_CPU_Info("Destroy Film Object");

	if (finalUChar4Buffer_device)
		cudaFree(finalUChar4Buffer_device);
	if (finalFloat4Buffer_device)
		cudaFree(finalFloat4Buffer_device);

	if (finalUChar4Buffer_host)
		delete[] finalUChar4Buffer_host;
	if (finalFloat4Buffer_host)
		delete [] finalFloat4Buffer_host;
}


// Camera
Camera::Camera(unsigned int type):
type(type){

}
Camera::~Camera() {

}

void Camera::GenerateRay(const CameraSample& sample, CameraRay* ray) const {
	// Compute raster and camera sample positions
	Point3f pFilm = Point3f(sample.pFilm.x, sample.pFilm.y, 0);
	Point3f pCamera = Raster2Camera(pFilm);
	*ray = CameraRay(Point3f(0, 0, 0), Normalize(Vector3f(pCamera)));

	// Modify ray for depth of field
	if (lensRadius > 0) {
		// Sample point on lens
		Point2f pLens = lensRadius * ConcentricSampleDisk(sample.pLens);

		// Compute point on plane of focus
		float ft = focalDistance / ray->direction.z;
		Point3f pFocus = (*ray)(ft);

		// Update ray for effect of lens
		ray->origin = Point3f(pLens.x, pLens.y, 0);
		ray->direction = Normalize(pFocus - ray->origin);
	}
	ray->isInVolume = isInVolume;
	*ray = Camera2World(*ray);

}
void Camera::GenerateRayDifferential(const CameraSample& sample,
	CameraRayDifferential* rd) const {

}


}

