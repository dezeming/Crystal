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

#ifndef __DataPresentDockWidget_hpp__
#define __DataPresentDockWidget_hpp__
#ifdef CRYSTAL_Using_Shared_Lib
#undef _EXPORTING
#endif


#include <QDockWidget>
#include <QFrame>
#include <QVBoxLayout>

namespace CrystalGUI {

class DataTreeWidget;

class DataPresentDockWidget : public QDockWidget {
	Q_OBJECT

public:
	DataPresentDockWidget(QWidget* parent = Q_NULLPTR);
	~DataPresentDockWidget();

private:
	QVBoxLayout* centerLayout;
	QFrame* dockCentralWidget;

	DataTreeWidget* m_DataTreeWidget;

protected:
	void closeEvent(QCloseEvent* event);

private slots:


};




}


	
#endif







