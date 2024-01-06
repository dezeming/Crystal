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

#ifndef __algrithm_Common_hpp__
#define __algrithm_Common_hpp__

/**
* copy mode: Copy memory data to a new buffer.
* assign mode: Assign memory data to a new buffer.
*/

#include <iostream>
#include <string>
#include <vector>

namespace CrystalAlgrithm {

#ifdef _EXPORTING
#define EXPORT_DLL    __declspec(dllexport)
#else
#define EXPORT_DLL    __declspec(dllimport)
#endif

struct EXPORT_DLL CudaDeviceProperty {
	std::string GPU_name;
	std::string Compute_capability;
	std::string Clock_rate;
	std::string Total_global_memory;
	std::string Total_constant_memory;
	std::string Multiprocessor_count;
};

void EXPORT_DLL getCudaDevice(std::vector<CudaDeviceProperty>& cudadevices);

void EXPORT_DLL printCudaDevice();


}




#endif











