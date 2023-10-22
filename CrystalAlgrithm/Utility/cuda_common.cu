/**
Copyright (C) <2023>  <Dezeming>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "cuda_common.cuh"

#include <cuda.h>
#include <cuda_runtime.h>

#include <string>
#include <iostream>

namespace CudaTools {

void printCudaDevice() {
	COUT_BLUE("Cuda Support Devices") << std::endl;

	cudaDeviceProp prop;
	int count;
	bool accuracy = Get_CUDA_ERROR(cudaGetDeviceCount(&count));
	for (int i = 0; i < count; i++) {
		accuracy = Get_CUDA_ERROR(cudaGetDeviceProperties(&prop, i));
		if (accuracy) {
			std::cout << "GPU sequence " + std::to_string(i) << std::endl;
			std::cout << "  GPU name " << prop.name << std::endl;
			std::cout << "  Compute capability " << prop.major << "." << prop.minor << std::endl;
			std::cout << "  Clock rate " << prop.clockRate << std::endl;
			std::cout << "  Total global memory " << prop.totalGlobalMem / 1024 / 1024 / 1024 << "GB" << std::endl;
			std::cout << "  Total constant memory " << prop.totalConstMem / 1024 << "KB" << std::endl;
			std::cout << "  Multiprocessor count " << prop.multiProcessorCount << std::endl;
		}

	}
}

std::string getCudaErrorStr(const char* error, const char* file, int line) {
	return (std::string(error) + " in " + std::string(file) + " at line " + std::to_string(line));
	//exit(EXIT_FAILURE);
}

bool getCudaError(cudaError_t err, const char* file, int line) {
	if (err != cudaSuccess) {
		COUT_RED("Error: ") << getCudaErrorStr(cudaGetErrorString(err), file, line) << std::endl;
		return false;
	}
	else {
		return true;
	}
}

bool getCudaError(cudaError_t err) {
	if (err != cudaSuccess) {
		COUT_RED("Error: ") << cudaGetErrorString(err) << std::endl;
		return false;
	}
	else {
		return true;
	}
}




}















