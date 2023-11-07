# ======================================================================== #
# Copyright 2023 Dezeming                                                  #
#                                                                          #
# Licensed under the Apache License, Version 2.0 (the "License");          #
# you may not use this file except in compliance with the License.         #
# You may obtain a copy of the License at                                  #
#                                                                          #
#     http://www.apache.org/licenses/LICENSE-2.0                           #
#                                                                          #
# Unless required by applicable law or agreed to in writing, software      #
# distributed under the License is distributed on an "AS IS" BASIS,        #
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. #
# See the License for the specific language governing permissions and      #
# limitations under the License.                                           #
# ======================================================================== #

if (POLICY CMP0048)
  cmake_policy(SET CMP0048 NEW)
endif (POLICY CMP0048)
if (POLICY CMP0077)
    cmake_policy(SET CMP0077 NEW)
endif()
cmake_minimum_required(VERSION 3.1)


project(Crystal VERSION 1.0.1)
project(Crystal LANGUAGES CXX CUDA)

########################################################################
################### Third party integration library ####################
########################################################################

########## OpenGL ##########

find_package(OpenGL REQUIRED)

########## Qt Lib ##########

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Qt6Config.cmake
set(Qt_DIR "D:/DevTools/Qt/6.2.4/msvc2019_64/" CACHE PATH "qt6 cmake dir")
list(APPEND CMAKE_PREFIX_PATH ${Qt_DIR})
find_package(Qt6 COMPONENTS 
	Widgets 
	Gui
	Core
	Xml
	OpenGL
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
	Qt6::OpenGL
	Qt6::OpenGLWidgets
)

# set(CMAKE_CXX_FLAGS "-mwindows")

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

set(Optix_SDK "C:/ProgramData/NVIDIA Corporation/OptiX SDK 7.6.0/")
set(Optix_INCLUDE_DIR ${Optix_SDK}include)

########## OpenMP Lib ##########

find_package(OpenMP REQUIRED)
if(OpenMP_FOUND)
	message(STATUS "found openmp") 
	set(CMAKE_C_FLAGS ${CMAKE_C_FLAGS}, ${OPENMP_C_FLAGS})
   	set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS}, ${OPENMP_CXX_FLAGS})
else()
   	message(FATAL_ERROR "openmp not found!")
endif()

############ Other Libs ###########

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Build into static libraries
set (BUILD_SHARED_LIBS OFF)

# stb

set (STB_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/stb)

###########################################################################
# zlib
#set(zlib_dir ${CMAKE_CURRENT_SOURCE_DIR}/CrystalThirdParty/zlib/)
# Build zlib
#set (ZLIB_BUILD_STATIC_LIBS ON CACHE BOOL " " FORCE)
#set (ZLIB_BUILD_SHARED_LIBS OFF CACHE BOOL " " FORCE)
#add_subdirectory (${zlib_dir})
#set (ZLIB_LIBRARIES zlibstatic)
#set (ZLIB_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/CrystalThirdParty/zlib ${CMAKE_CURRENT_BINARY_DIR}/zlib)
#set_property (TARGET zlibstatic PROPERTY FOLDER "CrystalThirdParty")
#set_target_properties(zlibstatic PROPERTIES FOLDER "CrystalThirdParty")
# try to make openexr happy about this...
#set (ZLIB_LIBRARY zlibstatic)
#set (ZLIB_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/CrystalThirdParty/zlib ${CMAKE_CURRENT_BINARY_DIR}/zlib)
#set (ZLIB_FOUND TRUE)
#add_library (ZLIB::ZLIB ALIAS zlibstatic)
#include_directories(${ZLIB_INCLUDE_DIRS}) 
#set (ZLIB_INCLUDE_DIRS ${ZLIB_INCLUDE_DIRS})
#set (ZLIB_LIBRARIES ${ZLIB_LIBARIES})

###########################################################################
# OpenEXR

set(openexr_dir ${CMAKE_CURRENT_SOURCE_DIR}/CrystalThirdParty/openexr/)

set (ILMBASE_NAMESPACE_VERSIONING OFF CACHE BOOL " " FORCE)
set (OPENEXR_NAMESPACE_VERSIONING OFF CACHE BOOL " " FORCE)
set (OPENEXR_BUILD_SHARED_LIBS    OFF CACHE BOOL " " FORCE)
set (ILMBASE_BUILD_SHARED_LIBS    OFF CACHE BOOL " " FORCE)
set (PYILMBASE_ENABLE             OFF CACHE BOOL " " FORCE)
set (OPENEXR_BUILD_UTILS          OFF CACHE BOOL " " FORCE)
add_subdirectory(${openexr_dir})

set_property (
TARGET IexMath IlmThread Half Iex Imath IlmImf HalfTest IexTest
IlmImfExamples IlmImfTest IlmImfUtil IlmImfUtilTest ImathTest
PROPERTY FOLDER "CrystalThirdParty/OpenEXR/")
set_target_properties(IexMath IlmThread Half Iex Imath IlmImf HalfTest IexTest
IlmImfExamples IlmImfTest IlmImfUtil IlmImfUtilTest ImathTest 
PROPERTIES FOLDER "CrystalThirdParty/OpenEXR/")

set (OPENEXR_INCLUDE
  ${CMAKE_CURRENT_SOURCE_DIR}/CrystalThirdParty/openexr/IlmBase/Imath
  ${CMAKE_CURRENT_SOURCE_DIR}/CrystalThirdParty/openexr/IlmBase/Half
  ${CMAKE_CURRENT_SOURCE_DIR}/CrystalThirdParty/openexr/IlmBase/Iex
  ${CMAKE_CURRENT_SOURCE_DIR}/CrystalThirdParty/openexr/OpenEXR/IlmImf
  ${CMAKE_CURRENT_BINARY_DIR}/CrystalThirdParty/openexr/IlmBase/config
  ${CMAKE_CURRENT_BINARY_DIR}/CrystalThirdParty/openexr/OpenEXR/config
)
set (OPENEXR_LIBS OpenEXR::IlmImf IlmBase::Imath IlmBase::Half)

###########################################################################

# include files
INCLUDE_DIRECTORIES(
	${CMAKE_CURRENT_BINARY_DIR}
	${CMAKE_CURRENT_SOURCE_DIR}
	# Qt
	${QT_INCLUDE_DIR}
	# Others
	${STB_INCLUDE}
	${ZLIB_INCLUDE_DIRS}
	${OPENEXR_INCLUDE}
	# Nvidia
	${CUDA_INCLUDE_DIRS}
	${Optix_INCLUDE_DIR}
)

########################################################################
###################### Crystal Algrithm Project ########################
########################################################################

set (BUILD_SHARED_LIBS OFF)

# macros predefined 
add_compile_definitions(_EXPORTING)

# Program output directory
set(publish_debug ${CMAKE_CURRENT_BINARY_DIR}/Debug)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${publish_debug})
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${publish_debug})
set(publish_release ${CMAKE_CURRENT_BINARY_DIR}/Release)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${publish_release})
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${publish_release})
#set(publish_relwithdebuginfo ${CMAKE_CURRENT_BINARY_DIR}/Relwithdebuginfo)
#set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELWITHDEBINFO ${publish_relwithdebuginfo})
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO ${publish_relwithdebuginfo})

if(NOT DEFINED CMAKE_DEBUG_POSTFIX)
set(CMAKE_DEBUG_POSTFIX "_d")
endif()
if(NOT DEFINED CMAKE_RELEASE_POSTFIX)
set(CMAKE_RELEASE_POSTFIX "_r")
endif()
#if(NOT DEFINED CMAKE_RELWITHDEBINFO_POSTFIX)
#set(CMAKE_RELWITHDEBINFO_POSTFIX "_rd")
#endif()

# Utility
set(Utility
	CrystalAlgrithm/Utility/cpu_Common.hpp
	CrystalAlgrithm/Utility/cpu_Common.cpp
	CrystalAlgrithm/Utility/cuda_common.cuh
	CrystalAlgrithm/Utility/cuda_common.cu
	CrystalAlgrithm/Utility/timerRandom.hpp
	CrystalAlgrithm/Utility/timerRandom.cpp
	CrystalAlgrithm/Utility/Geometry.h
	CrystalAlgrithm/Utility/Geometry.cpp
	CrystalAlgrithm/Utility/Transform.h
	CrystalAlgrithm/Utility/Transform.cpp
	CrystalAlgrithm/Utility/Spectrum.h
	CrystalAlgrithm/Utility/Spectrum.cpp
)
# Make the Utility group
SOURCE_GROUP("Utility" FILES ${Utility})

# Scene
set(Scene
	CrystalAlgrithm/Scene/Scene.h
	CrystalAlgrithm/Scene/Scene.cpp
	CrystalAlgrithm/Scene/ScenePreset.h
	CrystalAlgrithm/Scene/ScenePreset.cpp
)
# Make the Scene group
SOURCE_GROUP("Scene" FILES ${Scene})


#set(CMAKE_BUILD_TYPE "release")

cuda_add_library(CrystalAlgrithm STATIC 
	${Utility}
	${Scene}
)
# Do not generate dynamic link libraries
#cuda_add_library(CrystalAlgrithm SHARED ${Utility} )

SET(CrystalAlgrithm_LIBRARY_debug 
	${OPENEXR_LIBS}
)

SET(CrystalAlgrithm_LIBRARY_release 
	${OPENEXR_LIBS}
)

target_link_libraries (CrystalAlgrithm 
						#debug ${CrystalAlgrithm_LIBRARY_debug}
						optimized ${CrystalAlgrithm_LIBRARY_release} )

set_target_properties(CrystalAlgrithm PROPERTIES CUDA_ARCHITECTURES "35;52")
target_compile_features(CrystalAlgrithm PUBLIC cxx_std_17)
target_compile_features(CrystalAlgrithm PUBLIC cuda_std_11)

########################################################################
######################### Crystal GUI Project ##########################
########################################################################

# set Qt moc rcc uic
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Main
set(Main
	CrystalGUI/Main/main.cpp
	CrystalGUI/Main/MainWindow.hpp
	CrystalGUI/Main/MainWindow.cpp
)
# Make the Main group
SOURCE_GROUP("Main" FILES ${Main})

# Display
set(Display
	CrystalGUI/Display/DisplayWidget.hpp
	CrystalGUI/Display/DisplayWidget.cpp
)
# Make the Display group
SOURCE_GROUP("Display" FILES ${Display})

# Utility
set(Utility
	CrystalGUI/Utility/Utility.hpp
	CrystalGUI/Utility/Utility.cpp
	CrystalGUI/Utility/Common.hpp
	CrystalGUI/Utility/Status.hpp
	CrystalGUI/Utility/Status.cpp
	CrystalGUI/Utility/QDoubleSlider.hpp
	CrystalGUI/Utility/QDoubleSlider.cpp
	CrystalGUI/Utility/QSliderDoubleRange.hpp
	CrystalGUI/Utility/QSliderDoubleRange.cpp
)
# Make the Utility group
SOURCE_GROUP("Utility" FILES ${Utility})

# InfoPresent
set(InfoPresent
	CrystalGUI/InfoPresent/DataPresentDockWidget.hpp
	CrystalGUI/InfoPresent/DataPresentDockWidget.cpp
	CrystalGUI/InfoPresent/MemoryRecord.cpp
	CrystalGUI/InfoPresent/DevicesRecord.cpp
	CrystalGUI/InfoPresent/DataTreeWidget.hpp
	CrystalGUI/InfoPresent/DataTreeWidget.cpp
)
# Make the InfoPresent group
SOURCE_GROUP("InfoPresent" FILES ${InfoPresent})

# ReaderAndWriter
set(ReaderAndWriter
	CrystalGUI/ReaderAndWriter/ParserScene.hpp
	CrystalGUI/ReaderAndWriter/ParserScene.cpp
	CrystalGUI/ReaderAndWriter/ParserGeometry.hpp
	CrystalGUI/ReaderAndWriter/ParserGeometry.cpp
	CrystalGUI/ReaderAndWriter/ParserDataMapper.hpp
	CrystalGUI/ReaderAndWriter/ParserDataMapper.cpp
)
# Make the ReaderAndWriter group
SOURCE_GROUP("ReaderAndWriter" FILES ${ReaderAndWriter})

# DataMapper
set(DataMapper
	# DataMapper
	CrystalGUI/DataMapper/DataMapperStatistics.hpp
	CrystalGUI/DataMapper/DataMapperStatistics.cpp
	CrystalGUI/DataMapper/DataMapperDockWidget.hpp
	CrystalGUI/DataMapper/DataMapperDockWidget.cpp
	# Scalar Transfer function
	CrystalGUI/DataMapper/ScalarTransferFuncNodePropertiesWidget.hpp
	CrystalGUI/DataMapper/ScalarTransferFuncNodePropertiesWidget.cpp
	CrystalGUI/DataMapper/ScalarTransferFuncGraphicsView.hpp
	CrystalGUI/DataMapper/ScalarTransferFuncGraphicsView.cpp
)
# Make the DataMapper group
SOURCE_GROUP("DataMapper" FILES ${DataMapper})

# Create executable
add_executable(CrystalGUI WIN32
	${Main}
	${Display}
	${Utility}
	${InfoPresent}
	${DataMapper}
	${ReaderAndWriter}
)

SET(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR})

SET(LIBRARY_debug 
	# Qt Lib
	${QT6_LIBS}
	# OpenGL
	OpenGL::GL
	# Crystal Algrithm Lib
	${publish_debug}/CrystalAlgrithm_d.lib
	${publish_debug}/*.lib
	${CUDA_LIBRARIES}
)

SET(LIBRARY_release 
	# Qt Lib
	${QT6_LIBS}
	# OpenGL
	OpenGL::GL
	# Crystal Algrithm Lib
	${publish_release}/CrystalAlgrithm_r.lib
	${publish_release}/*.lib
	${CUDA_LIBRARIES}
)

target_link_libraries (CrystalGUI PRIVATE
						#debug ${LIBRARY_debug}
						optimized ${LIBRARY_release} 
						)
set_target_properties(CrystalGUI PROPERTIES OUTPUT_NAME "Crystal")

# set CrystalGUI as start up project
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT CrystalGUI)

# Set to console mode to output content to the cmd
set_target_properties(CrystalGUI PROPERTIES LINK_FLAGS_RELEASE "/SUBSYSTEM:CONSOLE")
set_target_properties(CrystalGUI PROPERTIES COMPILE_DEFINITIONS_RELEASE "_CONSOLE")
set_target_properties(CrystalGUI PROPERTIES LINK_FLAGS_DEBUG "/SUBSYSTEM:CONSOLE")
set_target_properties(CrystalGUI PROPERTIES LINK_FLAGS_MINSIZEREL "/SUBSYSTEM:CONSOLE")
#set_target_properties(CrystalGUI PROPERTIES LINK_FLAGS_RELWITHDEBINFO "/SUBSYSTEM:CONSOLE")
#set_target_properties(CrystalGUI PROPERTIES COMPILE_DEFINITIONS_RELWITHDEBINFO "_CONSOLE")

file(GLOB Resources "${CMAKE_CURRENT_SOURCE_DIR}/Resources/*")
file(COPY ${Resources} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Resources/)

file(GLOB Examples "${CMAKE_CURRENT_SOURCE_DIR}/Examples/*")
file(COPY ${Examples} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Examples/)

################################################################
### Qt ###
file(GLOB QT_BINS_Release
	${Qt_DIR}/bin/Qt6Widgets.dll
	${Qt_DIR}/bin/Qt6Gui.dll
	${Qt_DIR}/bin/Qt6Core.dll
	${Qt_DIR}/bin/Qt6Xml.dll
	${Qt_DIR}/bin/Qt6OpenGL.dll
	${Qt_DIR}/bin/Qt6OpenGLWidgets.dll
)
file(GLOB QT_BINS_Debug
	${Qt_DIR}/bin/Qt6Widgetsd.dll
	${Qt_DIR}/bin/Qt6Guid.dll
	${Qt_DIR}/bin/Qt6Cored.dll
	${Qt_DIR}/bin/Qt6Xmld.dll
	${Qt_DIR}/bin/Qt6OpenGLd.dll
	${Qt_DIR}/bin/Qt6OpenGLWidgetsd.dll
)
file(COPY ${QT_BINS_Debug} DESTINATION ${EXECUTABLE_OUTPUT_PATH}/Debug/)
file(COPY ${QT_BINS_Release} DESTINATION ${EXECUTABLE_OUTPUT_PATH}/Release/)

file(GLOB QT_Dependencies_icon
	"${Qt_DIR}/plugins/iconengines/*.dll"
	)
file(GLOB QT_Dependencies_imageformats
	${Qt_DIR}/plugins/imageformats/*.dll
	)
file(GLOB QT_Dependencies_platforms
	${Qt_DIR}/plugins/platforms/*.dll
	)
file(GLOB QT_Dependencies_styles
	${Qt_DIR}/plugins/styles/*.dll
	)
file(GLOB QT_Dependencies_translations
	${Qt_DIR}/translations/*
	)

file(COPY ${QT_Dependencies_icon} DESTINATION ${EXECUTABLE_OUTPUT_PATH}/Debug/iconengines/)
file(COPY ${QT_Dependencies_imageformats} DESTINATION ${EXECUTABLE_OUTPUT_PATH}/Debug/imageformats/)
file(COPY ${QT_Dependencies_platforms} DESTINATION ${EXECUTABLE_OUTPUT_PATH}/Debug/platforms/)
file(COPY ${QT_Dependencies_styles} DESTINATION ${EXECUTABLE_OUTPUT_PATH}/Debug/styles/)
file(COPY ${QT_Dependencies_translations} DESTINATION ${EXECUTABLE_OUTPUT_PATH}/Debug/translations/)

file(COPY ${QT_Dependencies_icon} DESTINATION ${EXECUTABLE_OUTPUT_PATH}/Release/iconengines/)
file(COPY ${QT_Dependencies_imageformats} DESTINATION ${EXECUTABLE_OUTPUT_PATH}/Release/imageformats/)
file(COPY ${QT_Dependencies_platforms} DESTINATION ${EXECUTABLE_OUTPUT_PATH}/Release/platforms/)
file(COPY ${QT_Dependencies_styles} DESTINATION ${EXECUTABLE_OUTPUT_PATH}/Release/styles/)
file(COPY ${QT_Dependencies_translations} DESTINATION ${EXECUTABLE_OUTPUT_PATH}/Release/translations/)






