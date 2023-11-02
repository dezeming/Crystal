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

#include "ParserDataMapper.hpp"

#define ParserDataMapperDebug true

namespace CrystalGUI {

bool ParserScene::readScalarTransFuncGlobalPropXML(const QDomNodeList& nodes, CrystalAlgrithm::STF_Preset& stf) {
	bool readFlag = true;
	for (int i = 0; i < nodes.count(); i++) {
		QDomNode childNode = nodes.at(i);
		QString tag = childNode.toElement().tagName();

	}
	return readFlag;
}

bool ParserScene::readScalarTransFuncOneNodePropXML(const QDomNodeList& nodes, CrystalAlgrithm::STF_Preset& stf) {
	bool readFlag = true;
	for (int i = 0; i < nodes.count(); i++) {
		QDomNode childNode = nodes.at(i);
		QString tag = childNode.toElement().tagName();
		if ("DensityScale" == tag) {
			stf.hasDensityScale = true;
		}else if ("Emission" == tag) {
			stf.hasEmission = true;
		}
		else if ("Absorption" == tag) {
			stf.hasAbsorption = true;
		}
		else if ("Scattering" == tag) {
			stf.hasScattering = true;
		}
		else if ("HG_Phase" == tag) {
			stf.hasHG_Phase = true;
		}
		else if ("Opacity" == tag) {
			stf.hasOpacity = true;
		}
		else if ("Diffuse" == tag) {
			stf.hasDiffuse = true;
		}
		else if ("Specular" == tag) {
			stf.hasSpecular = true;
		}
		else if ("Roughness" == tag) {
			stf.hasRoughness = true;
		}
		else if ("Metallic" == tag) {
			stf.hasMetallic = true;
		}
		else {
			readFlag = false;
			Print_Gui_Error("Unwanted tag name while parsering Scene Xml: " + tag.toStdString());
		}
	}
	return readFlag;
}

bool ParserScene::readScalarTransFuncNodePropXML(const QDomNodeList& nodes, CrystalAlgrithm::STF_Preset& stf) {
	bool readFlag = true;

	CrystalAlgrithm::Spectrum3 Emission(0.0f), Absorption(0.0f), Scattering(0.0f), Diffuse(0.0f), Specular(0.0f), Metallic(0.0f);
	float DensityScale(1.0f), HG_Phase(0.0f), Opacity(0.0f), Roughness(0.0f);



	return readFlag;
}

bool ParserScene::readScalarTransFuncXML(const QDomNodeList& nodes) {
	bool readFlag = true;

	CrystalAlgrithm::STF_Preset stf;

	for (int i = 0; i < nodes.count(); i++) {
		QDomNode childNode = nodes.at(i);
		QString tag = childNode.toElement().tagName();
		if ("Type" == tag) {
			stf.type =
				childNode.toElement().attribute("value").toStdString();
		}
		else if ("GlobalProperties" == tag) {
			readFlag = readFlag && readScalarTransFuncGlobalPropXML(childNode.childNodes(), stf);
		}
		else if ("OneNodeProperties" == tag) {
			readFlag = readFlag && readScalarTransFuncOneNodePropXML(childNode.childNodes(), stf);
		}
		else if ("NodesPropertiesArray" == tag) {
			const QDomNodeList& npa = childNode.childNodes();
			for (int i = 0; i < npa.count(); i++) {
				QString tag = npa.at(i).toElement().tagName();
				if ("Node" == tag)
					readFlag = readFlag && readScalarTransFuncNodePropXML(npa.at(i).childNodes(), stf);
				else {
					readFlag = false;
					Print_Gui_Error("Unwanted tag name while parsering Scene Xml: " + tag.toStdString());
				}
			}
			
		}
		else {
			readFlag = false;
			Print_Gui_Error("Unwanted tag name while parsering Scene Xml: " + tag.toStdString());
		}
	}

	if (readFlag) m_ScenePreset.m_STF_Preset.push_back(stf);
	if (ParserDataMapperDebug && !CloseAllDebugInfo) {
		Print_String(stf.ToString());
	}
	return readFlag;
}






}







