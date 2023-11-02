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

#ifndef __CUDA_COMMON_CUH__
#define __CUDA_COMMON_CUH__

#include <cuda.h>
#include <cuda_runtime.h>

#include <iostream>
#include <string>

namespace CrystalAlgrithm {


#define HOST_AND_DEVICE __host__ __device__
#define HOST __host__
#define DEVICE __device__
#define GPU_CALL __global__

#define EMPTY_CHECK \
    do {            \
    } while (false) /* swallow semicolon */

// Use an empty check (rather than expanding the macros to nothing) to swallow the semicolon at the end, and avoid empty if-statements.
#define DCHECK(x) EMPTY_CHECK

#define DCHECK_EQ(a, b) EMPTY_CHECK
#define DCHECK_NE(a, b) EMPTY_CHECK
#define DCHECK_GT(a, b) EMPTY_CHECK
#define DCHECK_GE(a, b) EMPTY_CHECK
#define DCHECK_LT(a, b) EMPTY_CHECK
#define DCHECK_LE(a, b) EMPTY_CHECK

#define M_PI 3.1415926f
#define OneOver4PI 0.07957747f
#define INV_M_PI 0.3183099f
#define ANGLE(angle) (angle * M_PI / 180.0f)

#define MaxFloat std::numeric_limits<float>::max()
#define Infinity std::numeric_limits<float>::infinity()

// Some Utility functions
HOST_AND_DEVICE inline float Clamp(float val, float low, float high) {
    if (val < low)
        return low;
    else if (val > high)
        return high;
    else
        return val;
}
HOST_AND_DEVICE inline float Lerp(float t, float v1, float v2) { return (1 - t) * v1 + t * v2; }

#define COUT_RED(STRING) std::cout<<"\033[1;31m"<<STRING<<"\033[0m"
#define COUT_GREEN(STRING) std::cout<<"\033[1;32m"<<STRING<<"\033[m"
#define COUT_YELLOW(STRING) std::cout<<"\033[1;33m"<<STRING<<"\033[m"
#define COUT_BLUE(STRING) std::cout<<"\033[1;34m"<<STRING<<"\033[m"

std::string getCudaErrorStr(const char* error, const char* file, int line);

inline bool getCudaError(cudaError_t err);
inline bool getCudaError(cudaError_t err, const char* file, int line);

#define Get_CUDA_ERROR( err ) (getCudaError( err, __FILE__, __LINE__ ))


inline void getCpuError(std::string err, const char* file, int line) {
	COUT_RED("Error: ") << std::string(err) + " in " + std::string(file) + " at line " + std::to_string(line) << std::endl;
}
inline void getCpuWarning(std::string warning, const char* file, int line) {
	COUT_BLUE("Warning: ") << std::string(warning) + " in " + std::string(file) + " at line " + std::to_string(line) << std::endl;
}
inline void getCpuInfo(std::string info, const char* file, int line) {
	COUT_GREEN("Info: ") << std::string(info) + " in " + std::string(file) + " at line " + std::to_string(line) << std::endl;
}
#define Print_CPU_Warning( warning ) (getCpuWarning( warning, __FILE__, __LINE__ ))
#define Print_CPU_Error( err ) (getCpuError( err, __FILE__, __LINE__ ))
#define Print_CPU_Info( info ) (getCpuInfo( info, __FILE__, __LINE__ ))



}



#endif





