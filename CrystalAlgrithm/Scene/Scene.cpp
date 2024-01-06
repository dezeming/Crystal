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


#include "Scene.h"
#include "ScenePreset.h"

namespace CrystalAlgrithm{

Scene::Scene() {

}

Scene::~Scene() {

}


bool Scene::initScene(const ScenePreset& m_ScenePreset) {
	bool flag = true;
	flag = flag && initSceneFilm(m_ScenePreset);


	return flag;
}

bool Scene::initSceneCamera(const ScenePreset& m_ScenePreset) {
	return true;
}

bool Scene::initSceneFilm(const ScenePreset& m_ScenePreset) {

	film.init(CrystalAlgrithm::Point2i(m_ScenePreset.m_FilmPreset.width, m_ScenePreset.m_FilmPreset.height), 0, 100.0f);

	return true;
}

bool Scene::initSceneVisualizer(const ScenePreset& m_ScenePreset) {
	return true;
}


bool Scene::initMedicalVolumeData(const ScenePreset& m_ScenePreset) {
	return true;
}

bool Scene::initMedicalMeshData(const ScenePreset& m_ScenePreset) {
	return true;
}

bool Scene::initEnvironmentMeshData(const ScenePreset& m_ScenePreset) {
	return true;
}

bool Scene::initLightData(const ScenePreset& m_ScenePreset) {
	return true;
}

bool Scene::initSceneGeometry(const ScenePreset& m_ScenePreset) {
	return true;
}

bool Scene::initSTF(const ScenePreset& m_ScenePreset) {
	return true;
}


}





