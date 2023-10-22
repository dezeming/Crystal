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

#include <cuda.h>
#include <cuda_runtime.h>

#include <string>

namespace CudaTools {

#define HOST_AND_DEVICE __host__ __device__
#define HOST __host__
#define DEVICE __device__
#define GPU_CALL __global__

#define M_PI 3.1415926f
#define OneOver4PI 0.07957747f
#define INV_M_PI 0.3183099f
#define ANGLE(angle) (angle * M_PI / 180.0f)

#define COUT_RED(STRING) std::cout<<"\033[1;31m"<<STRING<<"\033[0m"
#define COUT_GREEN(STRING) std::cout<<"\033[1;32m"<<STRING<<"\033[m"
#define COUT_YELLOW(STRING) std::cout<<"\033[1;33m"<<STRING<<"\033[m"
#define COUT_BLUE(STRING) std::cout<<"\033[1;34m"<<STRING<<"\033[m"


std::string getCudaErrorStr(const char* error, const char* file, int line);

inline bool getCudaError(cudaError_t err);
inline bool getCudaError(cudaError_t err, const char* file, int line);

#define Get_CUDA_ERROR( err ) (getCudaError( err, __FILE__, __LINE__ ))

}









