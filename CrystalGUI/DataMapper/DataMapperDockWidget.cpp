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

#include "CrystalGUI/Utility/Common.hpp"

#define DataMapperDockDebug true

namespace CrystalGUI {

DataMapperDockWidget::DataMapperDockWidget(QWidget* pParent) : QDockWidget(pParent) {

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

    


    setupWidgets();

}

DataMapperDockWidget::~DataMapperDockWidget() {

	if (DataMapperDockDebug && !CloseAllDebugInfo) {
        Print_Gui_Info("Destroy DataMapperDockWidget Object");
	}

}

void DataMapperDockWidget::setupWidgets() {
    stackedWidget = new QStackedWidget;
    dockMainLayout->addWidget(stackedWidget,0,0);



}




}




