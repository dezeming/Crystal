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

#ifndef __ParserLight_h__
#define __ParserLight_h__

#include "CrystalGUI/Utility/Common.hpp"

#include "ParserGeometry.hpp"

#define ParserGeometryDebug true

namespace CrystalGUI {


bool ParserScene::readMedicalVolumeData(const QDomNodeList& nodes) {
    bool readFlag = true;
	for (int i = 0; i < nodes.count(); i++) {
		QDomNode childNode = nodes.at(i);
		QString tag = childNode.toElement().tagName();
		if ("DataFile" == tag) {
			m_ScenePreset.m_MedicalVolumeDataPreset.dataFileType = 
				childNode.toElement().attribute("type").toStdString();
			m_ScenePreset.m_MedicalVolumeDataPreset.dataFilePath = 
				childNode.toElement().attribute("path").toStdString();
			m_ScenePreset.m_MedicalVolumeDataPreset.datatype = 
				childNode.toElement().attribute("datatype").toStdString();
		}
		else if ("DataDim" == tag) {

			std::string res = childNode.toElement().attribute("Resolution").toStdString();
			std::vector<unsigned int> resValue = stringToUIntVector(res, ",");
			if (resValue.size() != 3) {
				readFlag = false;
				Print_Gui_Error("Incorrect number of data loads");
				break;
			}
			m_ScenePreset.m_MedicalVolumeDataPreset.resolution
				= CrystalAlgrithm::Vector3ui(resValue[0], resValue[1], resValue[2]);
			std::string ps = childNode.toElement().attribute("PixelSpacing").toStdString();
			std::vector<float> psValue = stringToFloatVector(ps, ",");
			if (psValue.size() != 3) {
				readFlag = false;
				Print_Gui_Error("Incorrect number of data loads");
				break;
			}
			m_ScenePreset.m_MedicalVolumeDataPreset.pixelSpacing
				= CrystalAlgrithm::Vector3f(psValue[0], psValue[1], psValue[2]);
		}
		else if ("Transform" == tag) {
			
			QDomNodeList transformNodes = childNode.childNodes();
			for (int i = 0; i < transformNodes.count(); i++) {
				QDomNode transchildNode = transformNodes.at(i);
				QString childTag = transchildNode.toElement().tagName();
				if (childTag == "Permute") {
					std::string axis = transchildNode.toElement().attribute("Axis").toStdString();
					std::vector<unsigned int> axisValue = stringToUIntVector(axis, ",");
					if (axisValue.size() != 3) {
						readFlag = false;
						Print_Gui_Error("Incorrect number of data loads");
						break;
					}
					m_ScenePreset.m_MedicalVolumeDataPreset.permute
						= CrystalAlgrithm::Vector3ui(axisValue[0], axisValue[1], axisValue[2]);
				}
				else if (childTag == "RotateXY") {
					
					float rotateX = transchildNode.toElement().attribute("X").toFloat();
					float rotateY = transchildNode.toElement().attribute("Y").toFloat();

					m_ScenePreset.m_MedicalVolumeDataPreset.RotateXY.x = rotateX;
					m_ScenePreset.m_MedicalVolumeDataPreset.RotateXY.y = rotateY;
				}
				else if (childTag == "Translate") {
					m_ScenePreset.m_MedicalVolumeDataPreset.Translate_V.x
						= transchildNode.toElement().attribute("X").toFloat();
					m_ScenePreset.m_MedicalVolumeDataPreset.Translate_V.y
						= transchildNode.toElement().attribute("Y").toFloat();
					m_ScenePreset.m_MedicalVolumeDataPreset.Translate_V.z
						= transchildNode.toElement().attribute("Z").toFloat();
				}
				else {
					readFlag = false;
					Print_Gui_Error("Unwanted tag name " + childTag.toStdString() +  "while parsering Scene Xml: " + tag.toStdString());
				}
			}

		}
		else if ("Structure" == tag) {
			m_ScenePreset.m_MedicalVolumeDataPreset.structure = 
				childNode.toElement().attribute("type").toStdString();
		}
		else {
			readFlag = false;
			Print_Gui_Error("Unwanted tag name while parsering Scene Xml: " + tag.toStdString());
		}
	}
	if (ParserGeometryDebug && !CloseAllDebugInfo) {
		Print_String(m_ScenePreset.m_MedicalVolumeDataPreset.ToString());
	}
    return readFlag;
}

bool ParserScene::readMedicalMeshData(const QDomNodeList& nodes) {
    bool readFlag = true;
	for (int i = 0; i < nodes.count(); i++) {
		QDomNode childNode = nodes.at(i);
		QString tag = childNode.toElement().tagName();
		if ("File" == tag) {

			childNode.toElement().attribute("value").toStdString();
		} 
		else if ("Material" == tag) {

			childNode.toElement().attribute("value").toStdString();
		}
		else if ("Transform" == tag) {

			childNode.toElement().attribute("value").toStdString();
		}
		else {
			readFlag = false;
			Print_Gui_Error("Unwanted tag name while parsering Scene Xml: " + tag.toStdString());
		}
	}
    return readFlag;
}

bool ParserScene::readEnvironmentMeshData(const QDomNodeList& nodes) {
    bool readFlag = true;
	for (int i = 0; i < nodes.count(); i++) {
		QDomNode childNode = nodes.at(i);
		QString tag = childNode.toElement().tagName();
		if ("File" == tag) {

			childNode.toElement().attribute("value").toStdString();
		}
		else if ("Material" == tag) {

			childNode.toElement().attribute("value").toStdString();
		}
		else if ("Transform" == tag) {

			childNode.toElement().attribute("value").toStdString();
		}
		else {
			readFlag = false;
			Print_Gui_Error("Unwanted tag name while parsering Scene Xml: " + tag.toStdString());
		}
	}
    return readFlag;
}

bool ParserScene::readLightData(const QDomNodeList& nodes) {
    bool readFlag = true;
	for (int i = 0; i < nodes.count(); i++) {
		QDomNode childNode = nodes.at(i);
		QString tag = childNode.toElement().tagName();
		if ("PointLight" == tag) {

			childNode.toElement().attribute("value").toStdString();
		}
		else if ("QuadAreaLight" == tag) {

		}
		else if ("HdrEnvironmentLight" == tag) {

		}
		else {
			readFlag = false;
			Print_Gui_Error("Unwanted tag name while parsering Scene Xml: " + tag.toStdString());
		}
	}
    return readFlag;
}





}

#endif


