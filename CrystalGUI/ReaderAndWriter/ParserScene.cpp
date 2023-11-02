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

#include "ParserScene.hpp"

#include "CrystalGUI/Utility/Common.hpp"

#include <QObject>
#include <QString>
#include <QFileInfo>
#include <QFile>

#include <QtXml\QtXml>
#include <QtXml\QDomDocument>

#include <iostream>
#include <vector>
#include <sstream>

#define ParserSceneDebug true

namespace CrystalGUI {

ParserScene::ParserScene(QObject* parent) {

}

ParserScene::~ParserScene() {
	if (ParserSceneDebug && !CloseAllDebugInfo) {
		Print_Gui_Info("Create ParserScene Object");
	}
}

bool ParserScene::readSceneXML() {

	if (sceneFilePath == "") {
		Print_Gui_Error("(filePath == \"\")");
		return false;
	}

	QFile file(sceneFilePath);
	if (!file.open(QIODevice::ReadOnly)) {
		Print_Gui_Error( "Cannot open file" );
		return false;
	}

	if (!reader.setContent(&file)) {
		file.close();
		Print_Gui_Error("(!reader.setContent(&file))");	
		return false;
	}
	file.close();

	sceneFileName = obtainFileNameFromFilePath(sceneFilePath);
	QFileInfo fileInfo(sceneFilePath);
	sceneFileDir = fileInfo.absolutePath();
	sceneFilePath = sceneFileDir + "/" + sceneFileName;
	
	m_ScenePreset.SceneFilePath = sceneFilePath.toStdString();
	m_ScenePreset.SceneFileDir = sceneFileDir.toStdString();
	m_ScenePreset.SceneFileName = sceneFileName.toStdString();

	// version
	QDomNode firstChild = reader.firstChild();
	if (firstChild.nodeName() == "xml") {
		if(ParserSceneDebug && !CloseAllDebugInfo) {
			Print_Data_Info("firstChild.nodeName()", firstChild.nodeName());
			Print_Data_Info("firstChild.nodeValue()", firstChild.nodeValue());
		}
	}
	else {
		// "No version , No Format"
		if (ParserSceneDebug && !CloseAllDebugInfo) {
			Print_String("No version , No Format");
		}
	}

	QDomElement root = reader.documentElement();
	rootName = root.tagName();
	if (ParserSceneDebug && !CloseAllDebugInfo) {
		Print_Data_Info("rootName", rootName);
	}

	bool readFlag = true;
	QDomNode child = root.firstChild();
	while (!child.isNull())
	{
		QDomElement e = child.toElement(); // try to convert the node to an element. 
		if (ParserSceneDebug && !CloseAllDebugInfo) {
			Print_Data_Info("e.tagName()", e.tagName());
		}
		
		if ("Camera" == e.tagName()) {
			readFlag = readFlag && readSceneCameraXML(child.childNodes());
		}
		else if ("Film" == e.tagName()) {
			readFlag = readFlag && readSceneFilmXML(child.childNodes());
		}
		else if ("Visualizer" == e.tagName()) {
			readFlag = readFlag && readSceneVisualizerXML(child.childNodes());
		}
		else if ("SceneGeometry" == e.tagName()) {
			readFlag = readFlag && readSceneGeometryXML(child.childNodes());
		}
		else if ("DataMapper" == e.tagName()) {
			readFlag = readFlag && readSceneDataMapperXML(child.childNodes());
		}
		else {
			readFlag = false;
			Print_Gui_Error("Unwanted tag name while parsering Scene Xml: " + e.tagName().toStdString());
		}
		//find next node
		child = child.nextSiblingElement();
	}

	if (ParserSceneDebug && !CloseAllDebugInfo) {
		Print_String(m_ScenePreset.ToString());
	}

	return readFlag;
}

bool ParserScene::readSceneCameraXML(const QDomNodeList& nodes) {
	bool readFlag = true;
	
	for (int i = 0; i < nodes.count(); i++) {
		QDomNode childNode = nodes.at(i);
		QString tag = childNode.toElement().tagName();
		if ("CameraType" == tag) {
			m_ScenePreset.m_CameraPreset.CameraType =
				childNode.toElement().attribute("type").toStdString();
		}
		else if("Fov" == tag) {
			m_ScenePreset.m_CameraPreset.fov = 
				childNode.toElement().attribute("value").toFloat();;
		}
		else if ("LookAt" == tag) {
			std::string from = childNode.toElement().attribute("from").toStdString();
			std::vector<float> fromValue = stringToFloatVector(from, ",");
			if (fromValue.size() != 3) {
				readFlag = false;
				break;
			}
			else {
				m_ScenePreset.m_CameraPreset.lookatFrom[0] = fromValue[0];
				m_ScenePreset.m_CameraPreset.lookatFrom[1] = fromValue[1];
				m_ScenePreset.m_CameraPreset.lookatFrom[2] = fromValue[2];
			}
			std::string to = childNode.toElement().attribute("to").toStdString();
			std::vector<float> toValue = stringToFloatVector(to, ",");
			if (toValue.size() != 3) {
				readFlag = false;
				break;
			}
			else {
				m_ScenePreset.m_CameraPreset.lookatTo[0] = toValue[0];
				m_ScenePreset.m_CameraPreset.lookatTo[1] = toValue[1];
				m_ScenePreset.m_CameraPreset.lookatTo[2] = toValue[2];
			}
		}
		else {
			readFlag = false;
			Print_Gui_Error("Unwanted tag name while parsering Scene Xml: " + tag.toStdString());
		}
	}
	if (ParserSceneDebug && !CloseAllDebugInfo) {
		Print_String(m_ScenePreset.m_CameraPreset.ToString());
	}
	return readFlag;
}

bool ParserScene::readSceneFilmXML(const QDomNodeList& nodes) {
	bool readFlag = true;
	for (int i = 0; i < nodes.count(); i++) {
		QDomNode childNode = nodes.at(i);
		QString tag = childNode.toElement().tagName();
		if ("FrameBufferSize" == tag) {
			m_ScenePreset.m_FilmPreset.width =
				childNode.toElement().attribute("width").toULongLong();
			m_ScenePreset.m_FilmPreset.height =
				childNode.toElement().attribute("height").toULongLong();
		}
		else {
			readFlag = false;
			Print_Gui_Error("Unwanted tag name while parsering Scene Xml: " + tag.toStdString());
		}
	}
	if (ParserSceneDebug && !CloseAllDebugInfo) {
		Print_String(m_ScenePreset.m_FilmPreset.ToString());
	}
	return readFlag;
}

bool ParserScene::readSceneVisualizerXML(const QDomNodeList& nodes) {
	bool readFlag = true;
	for (int i = 0; i < nodes.count(); i++) {
		QDomNode childNode = nodes.at(i);
		QString tag = childNode.toElement().tagName();
		if ("Visualizer" == tag) {
			m_ScenePreset.m_VisualizerPreset.VisualizerType =
				childNode.toElement().attribute("type").toStdString();
		}
		else {
			readFlag = false;
			Print_Gui_Error("Unwanted tag name while parsering Scene Xml: " + tag.toStdString());
		}
	}
	if (ParserSceneDebug && !CloseAllDebugInfo) {
		Print_String(m_ScenePreset.m_VisualizerPreset.ToString());
	}
	return readFlag;
}

bool ParserScene::readSceneGeometryXML(const QDomNodeList& nodes) {
	bool readFlag = true;
	
	for (int i = 0; i < nodes.count(); i++) {
		QDomNode childNode = nodes.at(i);
		QString tag = childNode.toElement().tagName();
		if ("GeometryFileName" == tag) {
			m_ScenePreset.GeometryFileName =
				childNode.toElement().attribute("file").toStdString();
		}
		else {
			readFlag = false;
			Print_Gui_Error("Unwanted tag name while parsering Scene Xml: " + tag.toStdString());
		}
	}

	QString GeometryFilePath = (m_ScenePreset.SceneFileDir + "/" + m_ScenePreset.GeometryFileName).c_str();
	QFile file(GeometryFilePath);
	if (m_ScenePreset.GeometryFileName == "") {
		Print_Gui_Error("No scene geometry file");
		return false;
	}
	else if(!file.exists()){	 
		Print_Gui_Error("No scene geometry file");
		return false;
	}
	if (!file.open(QIODevice::ReadOnly)) {
		Print_Gui_Error("Cannot open geometry file");
		return false;
	}
	QDomDocument geoReader;
	if (!geoReader.setContent(&file)) {	
		file.close();
		Print_Gui_Error("(!reader.setContent(&file))");
		return false;
	}
	file.close();

	QDomElement root = geoReader.documentElement();
	rootName = root.tagName();
	if (ParserSceneDebug && !CloseAllDebugInfo) {
		Print_Data_Info("rootName", rootName);
	}

	QDomNode child = root.firstChild();
	while (!child.isNull())
	{
		QDomElement e = child.toElement(); // try to convert the node to an element. 
		if (ParserSceneDebug && !CloseAllDebugInfo) {
			Print_Data_Info("e.tagName()", e.tagName());
		}

		if ("MedicalVolumeData" == e.tagName()) {
			readFlag = readFlag && readMedicalVolumeData(child.childNodes());
		}
		else if ("MedicalMeshData" == e.tagName()) {
			readFlag = readFlag && readMedicalMeshData(child.childNodes());
		}
		else if ("EnvironmentMesh" == e.tagName()) {
			readFlag = readFlag && readEnvironmentMeshData(child.childNodes());
		}
		else if ("Light" == e.tagName()) {
			readFlag = readFlag && readLightData(child.childNodes());
		}
		else {
			readFlag = false;
			Print_Gui_Error("Unwanted tag name while parsering Scene Xml: " + e.tagName().toStdString());
		}
		//find next node
		child = child.nextSiblingElement();
	}

	return readFlag;
}

bool ParserScene::readSceneDataMapperXML(const QDomNodeList& nodes) {

	bool readFlag = true;
	
	for (int i = 0; i < nodes.count(); i++) {
		QDomNode childNode = nodes.at(i);
		QString tag = childNode.toElement().tagName();
		if ("DataMapperFileName" == tag) {
			m_ScenePreset.DataMapperFileName =
				childNode.toElement().attribute("file").toStdString();
		}
		else {
			readFlag = false;
			Print_Gui_Error("Unwanted tag name while parsering Scene Xml: " + tag.toStdString());
		}
	}

	QString DataMapperFilePath = (m_ScenePreset.SceneFileDir + "/" + m_ScenePreset.DataMapperFileName).c_str();
	QFile file(DataMapperFilePath);
	if (m_ScenePreset.DataMapperFileName == "") {
		Print_Gui_Error("No scene ataMapper file");
		return false;
	}
	else if (!file.exists()) {
		Print_Gui_Error("No scene dataMapper file");
		return false;
	}
	if (!file.open(QIODevice::ReadOnly)) {
		Print_Gui_Error("Cannot open dataMapper file");
		return false;
	}
	QDomDocument mapReader;
	if (!mapReader.setContent(&file)) {
		file.close();
		Print_Gui_Error("(!reader.setContent(&file))");
		return false;
	}
	file.close();

	QDomElement root = mapReader.documentElement();
	rootName = root.tagName();
	if (ParserSceneDebug && !CloseAllDebugInfo) {
		Print_Data_Info("rootName", rootName);
	}

	QDomNode child = root.firstChild();
	while (!child.isNull())
	{
		QDomElement e = child.toElement(); // try to convert the node to an element. 
		if (ParserSceneDebug && !CloseAllDebugInfo) {
			Print_Data_Info("e.tagName()", e.tagName());
		}

		if ("ScalarTransferFunction" == e.tagName()) {
			readFlag = readFlag && readScalarTransFuncXML(child.childNodes());
		}
		else {
			readFlag = false;
			Print_Gui_Error("Unwanted tag name while parsering Scene Xml: " + e.tagName().toStdString());
		}
		//find next node
		child = child.nextSiblingElement();
	}

	return readFlag;
}

bool ParserScene::writeSceneXML() {

	return true;
}


std::vector<float> ParserScene::stringToFloatVector(std::string input, std::string separator) {
	std::vector<std::string> Result;
	std::vector<float> FloatResult;

	std::istringstream ss(input);
	std::string token;
	while (std::getline(ss, token, ',')) {
		Result.push_back(token);
	}
	if (Result.size() != 3) return FloatResult;

	for (int i = 0; i < 3; i++) {
		try {
			float floatValue = std::stof(Result[i]);
			FloatResult.push_back(floatValue);
		}
		catch (const std::invalid_argument& e) {
			Print_Gui_Error("invalid argument for converting string into float value");
		}
		catch (const std::out_of_range& e) {
			Print_Gui_Error("conversion exceeds the representable range of data");
		}
	}

	return FloatResult;
}


}






