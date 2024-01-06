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

#ifndef __DataMapperDockWidget_h__
#define __DataMapperDockWidget_h__
#ifdef CRYSTAL_Using_Shared_Lib
#undef _EXPORTING
#endif

#include "CrystalGUI/Utility/Common.hpp"

#include <QFrame>
#include <QGridLayout>
#include <QHBoxLayout>

#include <QDockWidget>
#include <QStackedWidget>
#include <QPushButton>

#include "ScalarTransferFuncGraphicsView.hpp"

namespace CrystalAlgrithm {
    class ScenePreset;
}

namespace CrystalGUI {

const int MaxSTFCount = 4;
const int MaxDataMapperCount = 5;

class DataMapperDockWidget : public QDockWidget
{
	Q_OBJECT

public:
    DataMapperDockWidget(QWidget* pParent, CrystalAlgrithm::ScenePreset& sp);
	~DataMapperDockWidget();

protected:

    QFrame* dockCentralWidget;
    QGridLayout* dockMainLayout;

    QStackedWidget* stackedWidget;

    // Scalar Transfer Function
    ScalarTransferFuncWidget* STF_Widgets[MaxSTFCount];
    int STF_Widgets_Count;

    QPushButton* DataMapper_SelectionButton[MaxDataMapperCount];
    QGridLayout* DataMapper_SelectionButton_Layout;
    int DataMapper_Button_Used;

    void setupWidgets(CrystalAlgrithm::ScenePreset& sp);

};




}


#endif



