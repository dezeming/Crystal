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

#include "DataMapperDockWidget.hpp"
#include "CrystalAlgrithm/Scene/ScenePreset.h"

#include "CrystalGUI/Utility/Common.hpp"

#define DataMapperDockDebug true

namespace CrystalGUI {

DataMapperDockWidget::DataMapperDockWidget(QWidget* pParent, const CrystalAlgrithm::ScenePreset& sp) : QDockWidget(pParent) {

	if (DataMapperDockDebug && !CloseAllDebugInfo) {
        Print_Gui_Info("Create DataMapperDockWidget Object");
	}
    setWindowTitle("Data Mapper");

    dockCentralWidget = new QFrame;
    dockCentralWidget->setWindowFlags(Qt::FramelessWindowHint);

    setWidget(dockCentralWidget);
    setFeatures(QDockWidget::DockWidgetMovable);
    setAutoFillBackground(true);

    dockMainLayout = new QGridLayout(dockCentralWidget);
    dockMainLayout->setAlignment(Qt::AlignTop);
    dockMainLayout->setSpacing(10);

    STF_Widgets_Count = 0;
    DataMapper_Button_Used = 0;

    setupWidgets(sp);

}

DataMapperDockWidget::~DataMapperDockWidget() {

	if (DataMapperDockDebug && !CloseAllDebugInfo) {
        Print_Gui_Info("Destroy DataMapperDockWidget Object");
	}

    for (int i = 0; i < STF_Widgets_Count; i++) {
        QObject::disconnect(STF_Widgets[i], 0, 0, 0);
    }
    STF_Widgets_Count = 0;
}

void DataMapperDockWidget::setupWidgets(const CrystalAlgrithm::ScenePreset& sp) {

    // Check if the number of DataMappers exceeds the maximum limit
    if (sp.m_STF_Preset.size() > 2) {
        Print_Gui_Error("The number of DataMappers exceeds the maximum limit");
        return;
    }
    // MaxDataMapperCount

    STF_Widgets_Count = sp.m_STF_Preset.size();

    stackedWidget = new QStackedWidget;
    dockMainLayout->addWidget(stackedWidget,0,0);

    DataMapper_SelectionButton_Layout = new QHBoxLayout;
    dockMainLayout->addLayout(DataMapper_SelectionButton_Layout, 1, 0);
    DataMapper_Button_Used = 0;
    
    for (int i = 0; i < sp.m_STF_Preset.size(); i++) {
        
        STF_Widgets[i] = new ScalarTransferFuncWidget(Q_NULLPTR, sp.m_STF_Preset[i]);
        stackedWidget->addWidget(STF_Widgets[i]);

        DataMapper_SelectionButton[DataMapper_Button_Used] = new QPushButton;
        DataMapper_SelectionButton[DataMapper_Button_Used]->setText("STF[" + QString::number(i) + "]");

        DataMapper_SelectionButton_Layout->addWidget(DataMapper_SelectionButton[i]); 

        DataMapper_Button_Used++;
    }
    if (1 == DataMapper_Button_Used)
        QObject::connect(DataMapper_SelectionButton[0], &QPushButton::clicked, [&]() {stackedWidget->setCurrentIndex(0); });
    else if (2 == DataMapper_Button_Used) {
        QObject::connect(DataMapper_SelectionButton[0], &QPushButton::clicked, [&]() {stackedWidget->setCurrentIndex(0); });
        QObject::connect(DataMapper_SelectionButton[1], &QPushButton::clicked, [&]() {
            stackedWidget->setCurrentIndex(1); });
    }



}




}




