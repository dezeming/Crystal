/**
Copyright (C) <2023>  <Dezeming>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#ifdef CRYSTAL_Using_Shared_Lib
#undef _EXPORTING
#endif

#include "DataPresentDockWidget.hpp"
#include "DataTreeWidget.hpp"

#include "CrystalGUI/utility/Status.hpp"
#include "CrystalGUI/Utility/Common.hpp"

namespace CrystalGUI {

DataPresentDockWidget::DataPresentDockWidget(QWidget* parent) {
	setWindowTitle("ImageTools");

	setFeatures(QDockWidget::DockWidgetMovable);
	dockCentralWidget = new QFrame;

	setWidget(dockCentralWidget);
	centerLayout = new QVBoxLayout;
	dockCentralWidget->setWindowFlags(Qt::FramelessWindowHint);
	dockCentralWidget->setLayout(centerLayout);

	m_DataTreeWidget = new DataTreeWidget;
	centerLayout->addWidget(m_DataTreeWidget);
	connect(&m_GuiStatus, SIGNAL(setDataChanged(const QString&, const QString&, const QString&, const QString&, const QString&)),
		m_DataTreeWidget, SLOT(dataChanged(const QString&, const QString&, const QString&, const QString&, const QString&)));

	showMemoryInfo();

	setMinimumWidth(400);

}

DataPresentDockWidget::~DataPresentDockWidget() { }

void DataPresentDockWidget::closeEvent(QCloseEvent* event) { }


}









