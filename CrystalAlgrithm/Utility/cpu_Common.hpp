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

#ifndef __cpu_Common_hpp__
#define __cpu_Common_hpp__

/**
* copy mode: Copy memory data to a new buffer.
* assign mode: Assign memory data to a new buffer.
*/

#include <iostream>
#include <string>

#include <opencv2/opencv.hpp>

namespace cputools {

#define COUT_RED(STRING) std::cout<<"\033[1;31m"<<STRING<<"\033[0m"
#define COUT_GREEN(STRING) std::cout<<"\033[1;32m"<<STRING<<"\033[m"
#define COUT_YELLOW(STRING) std::cout<<"\033[1;33m"<<STRING<<"\033[m"
#define COUT_BLUE(STRING) std::cout<<"\033[1;34m"<<STRING<<"\033[m"

inline void getCpuError(std::string err, const char* file, int line) {
	COUT_RED("Error: ") << std::string(err) + " in " + std::string(file) + " at line " + std::to_string(line) << std::endl;
}

inline void getCpuWarning(std::string err, const char* file, int line) {
	COUT_BLUE("Warning: ") << std::string(err) + " in " + std::string(file) + " at line " + std::to_string(line) << std::endl;
}

#define Print_CPU_Warning( err ) (getCpuWarning( err, __FILE__, __LINE__ ))
#define Print_CPU_Error( err ) (getCpuError( err, __FILE__, __LINE__ ))

inline void Error_InconsistentImageSizes() {
	Print_CPU_Error("Inconsistent image sizes");
}

inline void Error_InconsistentImageTypes() {
	Print_CPU_Error("Inconsistent image types");
}

inline void Error_IllegalImageType() {
	Print_CPU_Error("Illegal image type");
}

inline void Error_ImageWriteError() {
	Print_CPU_Error("Image write error");
}

inline void Error_ImageConvertError() {
	Print_CPU_Error("Image convert error");
}

inline void Error_ExceedingImageBoundaries() {
	Print_CPU_Error("Exceeding image boundaries");
}

inline void Warning_ExceedingImageBoundaries() {
	Print_CPU_Warning("Exceeding image boundaries");
}

inline void Error_EmptyMat() {
	Print_CPU_Error("Mat is empty");
}

struct ImageSize {
	ImageSize() {
		reset();
	}
	void reset() {
		width = height = channels = 0;
	}
	int width, height, channels;
};







}




#endif











