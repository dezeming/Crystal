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

#ifndef __algrithm_Camera_h__
#define __algrithm_Camera_h__

#include "CrystalAlgrithm/Utility/Common.hpp"

#include "CrystalAlgrithm/Utility/Geometry.h"
#include "CrystalAlgrithm/Utility/Spectrum.h"
#include "CrystalAlgrithm/Utility/Transform.h" 

#include <string>
#include <iostream>
#include <vector>

namespace CrystalAlgrithm {

class EXPORT_DLL CameraPreset {
public:
	CameraPreset();
	void reset();
	std::string CameraType;
	float fov;
	Point3f lookatFrom, lookatTo;

	bool isValid();

	std::string ToString();

};

class EXPORT_DLL FilmPreset {
public:
	FilmPreset();
	void reset();
	size_t width, height;

	bool isValid();

	std::string ToString();
};


struct CameraSample {
	Point2f pFilm;
	Point2f pLens;
	float time;
};


class EXPORT_DLL Film {
public:
	Film(); 
	~Film();

	void init(const Point2i& resolution, unsigned int type = 0, float maxSampleLuminance = Infinity);

	// 0:RGB Film  1:GBuffer Film
	unsigned int type;

	// final display buffer
	uchar4* finalUChar4Buffer_device;
	float4* finalFloat4Buffer_device;

	uchar4* finalUChar4Buffer_host;
	float4* finalFloat4Buffer_host;

	// GBuffer related



	//
	HOST void setRed(uchar4* buffer) {
		for (unsigned int i = 0; i < resolution.x; i++) {
			for (unsigned int j = 0; j < resolution.y; j++) {
				setValue(buffer, Point2i(i,j), make_uchar4(255,0,0,255));
			}
		}
	}
	unsigned char a = 0;
	HOST void setColorChanged(uchar4* buffer) {
		for (unsigned int i = 0; i < resolution.x; i++) {
			for (unsigned int j = 0; j < resolution.y; j++) {
				setValue(buffer, Point2i(i, j), make_uchar4(a, 0, a, 255));
			}
			a++;
		}
	}

	HOST_AND_DEVICE void setValue(float4* buffer, Point2i pixel, float4 val) {
		buffer[pixel.x + pixel.y * resolution.x] = val;
	}
	HOST_AND_DEVICE float4 getValue(float4* buffer, Point2i pixel) {
		return buffer[pixel.x + pixel.y * resolution.x];
	}

	HOST_AND_DEVICE void setValue(uchar4* buffer, Point2i pixel, uchar4 val) {
		buffer[pixel.x + pixel.y * resolution.x] = val;
	}
	HOST_AND_DEVICE uchar4 getValue(uchar4* buffer, Point2i pixel) {
		return buffer[pixel.x + pixel.y * resolution.x];
	}


	Point2i resolution;
	float maxSampleLuminance;
	
};

class EXPORT_DLL Camera {
public:
	HOST_AND_DEVICE Camera(unsigned int type = 0);
	HOST_AND_DEVICE ~Camera();

	// 0:perspective  1:orthographic
	unsigned int type;

	Transform Camera2World, World2Camera;
	Transform Camera2Screen;
	Transform Screen2Raster, Raster2Screen;
	Transform Raster2Camera;
	float lensRadius, focalDistance;

	HOST_AND_DEVICE void GenerateRay(
		const CameraSample& sample, 
		CameraRay* ray) const;
	HOST_AND_DEVICE void GenerateRayDifferential(
		const CameraSample& sample,
		CameraRayDifferential* rd) const;

	Film* film;

	bool isInVolume;
};







}

#endif


