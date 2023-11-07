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
#include <QDir>

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
		Print_Gui_Error("The format of the Scene XML file is incorrect and please check the file");
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
		Print_Gui_Error("The format of the Geometry XML file is incorrect and please check the file");
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
		else if ("Texture" == e.tagName()) {

		}
		else if ("Material" == e.tagName()) {

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
		Print_Gui_Error("No scene dataMapper file");
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
		Print_Gui_Error("The format of the DataMapper XML file is incorrect and please check the file");
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

bool ParserScene::writeSceneXML(QString folderPath) {

	QDir folder(folderPath);

	if (!folder.exists()) {
		if (!folder.mkpath(".")) {
			return false;
		}
	}
	QFile sceneFile(folderPath + "/" + "Scene.xml");
	QFile SceneGeometryFile(folderPath + "/" + "SceneGeometry.xml");
	QFile DataMapperFile(folderPath + "/" + "DataMapper.xml");
	if (sceneFile.exists() || SceneGeometryFile.exists() || DataMapperFile.exists())
		return false;

	if (!sceneFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
		return false;
	}
	if (!SceneGeometryFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
		return false;
	}
	if (!DataMapperFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
		return false;
	}

	// write scene file

	writer.clear();
	QDomProcessingInstruction instruction = writer.createProcessingInstruction("xml", "version=\"1.0\" encoding=\"UTF-8\"");
	writer.appendChild(instruction);

	QDomElement root = writer.documentElement();
	root = writer.createElement(rootName);
	writer.appendChild(root);

	root.appendChild(getSceneCameraXML());
	root.appendChild(getSceneFilmXML());
	root.appendChild(getSceneVisualizerXML());

	QDomElement SceneGeometryNodeElement = writer.createElement("Film");
	QDomElement SceneGeometryNode = writer.documentElement();
	SceneGeometryNode = writer.createElement("GeometryFileName");
	SceneGeometryNode.setAttribute("file", "SceneGeometry.xml");
	SceneGeometryNodeElement.appendChild(SceneGeometryNode);

	root.appendChild(SceneGeometryNodeElement);

	QDomElement DataMapperNodeElement = writer.createElement("Film");
	QDomElement DataMapperNode = writer.documentElement();
	DataMapperNode = writer.createElement("DataMapperFileName");
	DataMapperNode.setAttribute("file", "DataMapper.xml");
	DataMapperNodeElement.appendChild(DataMapperNode);

	root.appendChild(DataMapperNodeElement);

	// output to file
	QTextStream out_stream(&sceneFile);
	writer.save(out_stream, 4); //Ëõ½ø4¸ñ
	sceneFile.close();

	// write sceneGeometry file




	// write data mapper file




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

QDomElement ParserScene::getSceneCameraXML() {

	QDomDocument doc;
	QDomElement TsNodesElement = doc.createElement("Camera");

	QDomElement CameraTypeElement = doc.documentElement();
	CameraTypeElement = doc.createElement("CameraType");
	CameraTypeElement.setAttribute("type", m_ScenePreset.m_CameraPreset.CameraType.c_str());

	QDomElement FovElement = doc.documentElement();
	FovElement = doc.createElement("Fov");
	FovElement.setAttribute("Value", m_ScenePreset.m_CameraPreset.fov);

	QDomElement LookAtElement = doc.documentElement();
	LookAtElement = doc.createElement("LookAt");
	LookAtElement.setAttribute("from", m_ScenePreset.m_CameraPreset.fromToString().c_str());
	LookAtElement.setAttribute("to", m_ScenePreset.m_CameraPreset.toToString().c_str());

	TsNodesElement.appendChild(CameraTypeElement);
	TsNodesElement.appendChild(FovElement);
	TsNodesElement.appendChild(LookAtElement);

	return TsNodesElement;
}

QDomElement ParserScene::getSceneFilmXML() {

	QDomDocument doc;
	QDomElement TsNodesElement = doc.createElement("Film");

	QDomElement FrameBufferSizeElement = doc.documentElement();
	FrameBufferSizeElement = doc.createElement("FrameBufferSize");
	FrameBufferSizeElement.setAttribute("width", m_ScenePreset.m_FilmPreset.width);
	FrameBufferSizeElement.setAttribute("height", m_ScenePreset.m_FilmPreset.height);

	TsNodesElement.appendChild(FrameBufferSizeElement);

	return TsNodesElement;
}

QDomElement ParserScene::getSceneVisualizerXML() {

	QDomDocument doc;
	QDomElement TsNodesElement = doc.createElement("Visualizer");

	QDomElement VisualizerElement = doc.documentElement();
	VisualizerElement = doc.createElement("Visualizer");
	VisualizerElement.setAttribute("type", m_ScenePreset.m_VisualizerPreset.VisualizerType.c_str());

	TsNodesElement.appendChild(VisualizerElement);

	return TsNodesElement;

}




}






