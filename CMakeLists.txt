cmake_minimum_required(VERSION 3.1)

set(CMAKE_CXX_STANDARD 11)

project(Crystal)

########################################################################
################### Third party integration library ####################
########################################################################

########## Qt Lib ##########

# set Qt moc rcc uic
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Qt6Config.cmake
set(Qt6_DIR "D:/DevTools/Qt6/6.2.4/msvc2019_64/" CACHE PATH "qt6 cmake dir")
set(CMAKE_PREFIX_PATH ${Qt6_DIR})
find_package(Qt6 COMPONENTS 
	Widgets 
	Gui
	Core
	Xml
	OpenGLWidgets
REQUIRED)

if(Qt6_FOUND)
	message(STATUS "found Qt6") 
else()
   	message(FATAL_ERROR "Qt6 not found!")
endif()

SET(QT6_LIBS 
	# Qt Lib
	Qt6::Widgets
	Qt6::Gui
	Qt6::Core
	Qt6::Xml
	Qt6::OpenGLWidgets
)

# set(CMAKE_CXX_FLAGS "-mwindows")

############ OpenEXR Lib ###########



########## OpenMP Lib ##########

find_package(OpenMP REQUIRED)
if(OpenMP_FOUND)
	message(STATUS "found openmp") 
	set(CMAKE_C_FLAGS ${CMAKE_C_FLAGS}, ${OPENMP_C_FLAGS})
   	set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS}, ${OPENMP_CXX_FLAGS})
else()
   	message(FATAL_ERROR "openmp not found!")
endif()

########## Nvidia CUDA Lib ##########

find_package(CUDA REQUIRED)

# Set Nvidia CUDA
set(CUDA_NVCC_FLAGS "-g -G")
# build option
set(GENCODE -gencode=arch=compute_35,code=sm_35)
set(GENCODE ${GENCODE} -gencode=arch=compute_30,code=sm_30)
set(GENCODE ${GENCODE} -gencode=arch=compute_20,code=sm_20)
set(GENCODE ${GENCODE} -gencode=arch=compute_10,code=sm_10)

enable_language(CUDA)

########## Nvidia Optix Lib ##########

set(Optix_SDK "C:/ProgramData/NVIDIA Corporation/OptiX SDK 7.5.0/")
set(Optix_INCLUDE_DIR ${Optix_SDK}include)

# include files
INCLUDE_DIRECTORIES(
	${CMAKE_CURRENT_BINARY_DIR}
	${CMAKE_CURRENT_SOURCE_DIR}
	${QT_INCLUDE_DIR}
	${OPENEXR_INCLUDE_DIRS}
	${CUDA_INCLUDE_DIRS}
	${Optix_INCLUDE_DIR}
)

########################################################################
###################### Crystal Algrithm Project ########################
########################################################################

# macros predefined 
add_compile_definitions(_EXPORTING)

# 程序输出目录
set(publish_debug ${CMAKE_CURRENT_BINARY_DIR}/Debug) 
set(publish_release ${CMAKE_CURRENT_BINARY_DIR}/Release)
set(publish_relwithdebuginfo ${CMAKE_CURRENT_BINARY_DIR}/Relwithdebuginfo)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${publish_release})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${publish_release})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${publish_debug})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${publish_debug})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELWITHDEBINFO ${publish_relwithdebuginfo})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO ${publish_relwithdebuginfo})

if(NOT DEFINED CMAKE_DEBUG_POSTFIX)
set(CMAKE_DEBUG_POSTFIX "_d")
endif()
if(NOT DEFINED CMAKE_RELEASE_POSTFIX)
set(CMAKE_RELEASE_POSTFIX "_r")
endif()
if(NOT DEFINED CMAKE_RELWITHDEBINFO_POSTFIX)
set(CMAKE_RELWITHDEBINFO_POSTFIX "_rd")
endif()

# Utility
set(Utility
	CrystalAlgrithm/Utility/Common.cuh
)
# Make the Utility group
SOURCE_GROUP("Utility" FILES ${Utility})

#set(CMAKE_BUILD_TYPE "debug")

cuda_add_library(CrystalAlgrithm SHARED 
	${Utility}
)

SET(CrystalAlgrithm_LIBRARY_debug 
	# VTK Lib
	${VTK_Debug_Lib_DIR}/*.lib
)

SET(CrystalAlgrithm_LIBRARY_release 
	# VTK Lib
	${VTK_Release_Lib_DIR}/*.lib
)

target_link_libraries (CrystalAlgrithm 
						debug ${CrystalAlgrithm_LIBRARY_debug}
						optimized ${CrystalAlgrithm_LIBRARY_release} )

set_target_properties(CrystalAlgrithm PROPERTIES CUDA_ARCHITECTURES "35;52")
target_compile_features(CrystalAlgrithm PUBLIC cxx_std_17)
target_compile_features(CrystalAlgrithm PUBLIC cuda_std_11)

########################################################################
######################### Crystal GUI Project ##########################
########################################################################

# Main
set(Main
	CrystalGUI/Main/main.cpp
	CrystalGUI/Main/MainWindow.h
	CrystalGUI/Main/MainWindow.cpp
)
# Make the Main group
SOURCE_GROUP("Main" FILES ${Main})

# Utility
set(Utility
	CrystalGUI/Utility/Utility.h
	CrystalGUI/Utility/Utility.cpp
	CrystalGUI/Utility/Common.h
)
# Make the Utility group
SOURCE_GROUP("Utility" FILES ${Utility})


# Create executable
add_executable(CrystalGUI
	WIN32
	${Main}
	${Display}
	${Utility}
)

SET(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR})

SET(LIBRARY_debug 
	# Qt Lib
	${QT6_LIBS}
	# Crystal Algrithm Lib
	${publish_debug}/*.lib
)

SET(LIBRARY_release 
	# Qt Lib
	${QT6_LIBS}
	# Crystal Algrithm Lib
	${publish_release}/*.lib
)

target_link_libraries (CrystalGUI PRIVATE
						debug ${LIBRARY_debug}
						optimized ${LIBRARY_release} 
						)

# set CrystalGUI as start up project
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT CrystalGUI)

# Set to console mode to output content to the cmd
set_target_properties(CrystalGUI PROPERTIES LINK_FLAGS_RELEASE "/SUBSYSTEM:CONSOLE")
set_target_properties(CrystalGUI PROPERTIES COMPILE_DEFINITIONS_RELEASE "_CONSOLE")
set_target_properties(CrystalGUI PROPERTIES LINK_FLAGS_RELWITHDEBINFO "/SUBSYSTEM:CONSOLE")
set_target_properties(CrystalGUI PROPERTIES COMPILE_DEFINITIONS_RELWITHDEBINFO "_CONSOLE")
set_target_properties(CrystalGUI PROPERTIES LINK_FLAGS_DEBUG "/SUBSYSTEM:CONSOLE")
set_target_properties(CrystalGUI PROPERTIES LINK_FLAGS_MINSIZEREL "/SUBSYSTEM:CONSOLE")


file(GLOB Resources "${CMAKE_CURRENT_SOURCE_DIR}/Resources/*")
file(COPY ${Resources} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Resources/)

file(GLOB Examples "${CMAKE_CURRENT_SOURCE_DIR}/Examples/*")
file(COPY ${Examples} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Examples/)




