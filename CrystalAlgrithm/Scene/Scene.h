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


#ifndef __algrithm_Scene_h__
#define __algrithm_Scene_h__

#include "CrystalAlgrithm/Camera/Camera.h"

#include "CrystalAlgrithm/Shape/Primitive.h"

#include "CrystalAlgrithm/Visualizer/Visualizer.h"

#include "CrystalAlgrithm/Material/Texture.h"
#include "CrystalAlgrithm/Material/Material.h"

#include "CrystalAlgrithm/Shape/bvhTree.h"

#include "CrystalAlgrithm/Volume/Texture3DVolume.h"
#include "CrystalAlgrithm/Volume/OctreeVolume.h"

#include "CrystalAlgrithm/DataMapper/STF.h"

#include <memory>

namespace CrystalAlgrithm {

class ScenePreset;

class EXPORT_DLL Scene {
public:
    Scene();
    ~Scene();

    // Init Scene
    bool initScene(const ScenePreset& m_ScenePreset);

    bool initSceneCamera(const ScenePreset& m_ScenePreset);

    bool initSceneFilm(const ScenePreset& m_ScenePreset);

    bool initSceneVisualizer(const ScenePreset& m_ScenePreset);

    bool initSceneGeometry(const ScenePreset& m_ScenePreset);
    bool initMedicalVolumeData(const ScenePreset& m_ScenePreset);
    bool initMedicalMeshData(const ScenePreset& m_ScenePreset);
    bool initEnvironmentMeshData(const ScenePreset& m_ScenePreset);
    bool initLightData(const ScenePreset& m_ScenePreset);

    bool initSTF(const ScenePreset& m_ScenePreset);


    // shape
    NonLuminousPrimitiveTable nlTable;
    LightPrimitiveTable lTable;
    MedicalPrimitiveTable mTable;

    // accelerator
    BVHTree nlTree;
    BVHTree lTree;
    BVHTree mTree;
    Bounds3f volumeObjBound;

    // Textures
    TextureManager textureManager;

    // Materials
    MaterialManager materialManager;

    // DataMapper
    bool hasIntensitySTF, hasGradientMagnitudeSTF, hasMaskSTF1, hasMaskSTF2;
    STF intensitySTF;
    STF gradientMagnitudeSTF;
    STF maskSTF[2];

    // Volume
    unsigned int volType;
    Texture3DVolume tex3dVolume;
    OctreeVolume octVolume;

    // Camera
    unsigned int camType;
    Camera camera;

    // Film
    Film film;

};



}

#endif




