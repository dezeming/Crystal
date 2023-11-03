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

namespace CrystalGUI {


bool ParserScene::readMedicalVolumeData(const QDomNodeList& nodes) {
    bool readFlag = true;
	for (int i = 0; i < nodes.count(); i++) {
		QDomNode childNode = nodes.at(i);
		QString tag = childNode.toElement().tagName();
		if ("DataFile" == tag) {
			
			childNode.toElement().attribute("value").toStdString();
		}
		else if ("Transform" == tag) {
			
		}
		else if ("Structure" == tag) {
			
		}
		else {
			readFlag = false;
			Print_Gui_Error("Unwanted tag name while parsering Scene Xml: " + tag.toStdString());
		}
	}
    return readFlag;
}

bool ParserScene::readMedicalMeshData(const QDomNodeList& nodes) {
    bool readFlag = true;
    return readFlag;
}

bool ParserScene::readEnvironmentMeshData(const QDomNodeList& nodes) {
    bool readFlag = true;
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


