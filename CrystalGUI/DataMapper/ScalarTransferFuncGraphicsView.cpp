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


#include "ScalarTransferFuncGraphicsView.hpp"

#include "CrystalAlgrithm/Scene/ScenePreset.h"

namespace CrystalGUI {

#define ScalarTransferFuncGraphicsViewDebug true



ScalarTransferFuncGraphicsView::ScalarTransferFuncGraphicsView(QGraphicsView* parent, const CrystalAlgrithm::STF_Preset& stfp) :
	QGraphicsView(parent){
    if (ScalarTransferFuncGraphicsViewDebug && !CloseAllDebugInfo) {
        Print_Gui_Info("Create ScalarTransferFuncGraphicsView Object");
    }
	setMinimumSize(200,100);

    

}

ScalarTransferFuncGraphicsView::~ScalarTransferFuncGraphicsView() {
    if (ScalarTransferFuncGraphicsViewDebug && !CloseAllDebugInfo) {
        Print_Gui_Info("Destroy ScalarTransferFuncGraphicsView Object");
    }


}


ScalarTransferFuncWidget::ScalarTransferFuncWidget(QGroupBox* parent, const CrystalAlgrithm::STF_Preset& stfp) : QGroupBox(parent) {
    if (ScalarTransferFuncGraphicsViewDebug && !CloseAllDebugInfo) {
        Print_Gui_Info("Create ScalarTransferFuncWidget Object");
    }

	setTitle("Scalar Transfer Function");
    layout = new QVBoxLayout;
    setLayout(layout);

    if (stfp.hasOpacity) {
        OpacitySetter = new FloatSetter(Q_NULLPTR, "Opacity", 0.0f, 1.0f);
        layout->addWidget(OpacitySetter);
    }

    if (stfp.hasDiffuse) {
        DiffuseSetter = new RGBSetter(Q_NULLPTR, "Diffuse");
        layout->addWidget(DiffuseSetter);
    }

    if (stfp.hasSpecular) {
        SpecularSetter = new RGBSetter(Q_NULLPTR, "Specular");
        layout->addWidget(SpecularSetter);
    }

    if (stfp.hasRoughness) {
        RoughnessSetter = new FloatSetter(Q_NULLPTR, "Roughness", 0.0f, 1.0f);
        layout->addWidget(RoughnessSetter);
    }

}

ScalarTransferFuncWidget::~ScalarTransferFuncWidget() {
    if (ScalarTransferFuncGraphicsViewDebug && !CloseAllDebugInfo) {
        Print_Gui_Info("Create ScalarTransferFuncWidget Object");
    }
}





}




