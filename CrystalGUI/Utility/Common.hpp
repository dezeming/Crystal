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

#ifndef __Common_hpp__
#define __Common_hpp__
#ifdef CRYSTAL_Using_Shared_Lib
#undef _EXPORTING
#endif

#include <iostream>
#include <string>
#include <QString>

namespace CrystalGUI {

#define CloseAllDebugInfo false

/*
#include <Windows.h>
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
*/

#define COUT_RED(STRING) std::cout<<"\033[1;31m"<<STRING<<"\033[0m"
#define COUT_GREEN(STRING) std::cout<<"\033[1;32m"<<STRING<<"\033[m"
#define COUT_YELLOW(STRING) std::cout<<"\033[1;33m"<<STRING<<"\033[m"
#define COUT_BLUE(STRING) std::cout<<"\033[1;34m"<<STRING<<"\033[m"



inline void getGuiError(std::string err, const char* file, int line) {
	COUT_RED("Error: [" + std::string(err) + "]") << " in " + std::string(file) + " at line " + std::to_string(line) << std::endl;
}

inline void getGuiWarning(std::string warning, const char* file, int line) {
	COUT_BLUE("Warning: [" + std::string(warning) + "]") << " in " + std::string(file) + " at line " + std::to_string(line) << std::endl;
}

inline void getGuiInfo(std::string info, const char* file, int line) {
	COUT_GREEN("Info: [" + std::string(info) + "]") << " in " + std::string(file) + " at line " + std::to_string(line) << std::endl;
}


#define Print_Gui_Warning( warning ) (getGuiWarning( warning, __FILE__, __LINE__ ))
#define Print_Gui_Error( err ) (getGuiError( err, __FILE__, __LINE__ ))
#define Print_Gui_Info( info ) (getGuiInfo( info, __FILE__, __LINE__ ))

inline void getDataInfo(std::string info, const char* file, int line) {
	COUT_YELLOW("[" + std::string(info) + "]") << " in " + std::string(file) + " at line " + std::to_string(line) << std::endl;
}
inline void getDataInfo(std::string info, std::string data, const char* file, int line) {
	COUT_YELLOW("[" + std::string(info) + ": " + data + "]") << " in " + std::string(file) + " at line " + std::to_string(line) << std::endl;
}
inline void getDataInfo(std::string info, int data, const char* file, int line) {
	COUT_YELLOW("[" + std::string(info) + ": " + std::to_string(data) + "]") << " in " + std::string(file) + " at line " + std::to_string(line) << std::endl;
}
inline void getDataInfo(std::string info, float data, const char* file, int line) {
	COUT_YELLOW("[" + std::string(info) + ": " + std::to_string(data) + "]") << " in " + std::string(file) + " at line " + std::to_string(line) << std::endl;
}
inline void getDataInfo(std::string info, QString data, const char* file, int line) {
	COUT_YELLOW("[" + std::string(info) + ": " + (data.toStdString()) + "]") << " in " + std::string(file) + " at line " + std::to_string(line) << std::endl;
}

#define Print_String( info, data ) (getDataInfo( info,  __FILE__, __LINE__ ))
#define Print_Data_Info( info, data ) (getDataInfo( info, data,  __FILE__, __LINE__ ))


void showMemoryInfo(void);

void showCudaDevicesInfo(void);



}






#endif


