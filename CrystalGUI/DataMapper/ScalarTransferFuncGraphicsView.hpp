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

#ifndef __ScalarTransferFuncGraphicsView_h__
#define __ScalarTransferFuncGraphicsView_h__
#ifdef CRYSTAL_Using_Shared_Lib
#undef _EXPORTING
#endif

#include "CrystalGUI/Utility/Common.hpp"

#include <QGraphicsView>
#include <QMouseEvent>
#include <QGroupBox>

#include "CrystalGUI/Utility/Utility.hpp"

namespace CrystalAlgrithm {
    class STF_Preset;
}

namespace CrystalGUI {


class ScalarTransferFuncGraphicsView : public QGraphicsView {
	Q_OBJECT

public:
    ScalarTransferFuncGraphicsView(QGraphicsView* parent, const CrystalAlgrithm::STF_Preset& stfp);
	~ScalarTransferFuncGraphicsView();

	QGraphicsScene* scene;

};

class ScalarTransferFuncWidget : public QGroupBox {
    Q_OBJECT
public:
    ScalarTransferFuncWidget(QGroupBox* parent, const CrystalAlgrithm::STF_Preset& stfp);
    ~ScalarTransferFuncWidget();

    QVBoxLayout *layout;

    FloatSetter* DensityScaleSetter;
    FloatSetter* HG_PhaseSetter;
    FloatSetter* OpacitySetter;
    FloatSetter* RoughnessSetter;
    FloatSetter* MetallicSetter;

    RGBSetter* ScatteringSetter;
    RGBSetter* EmissionSetter;
    RGBSetter* AbsorptionSetter;
    RGBSetter* DiffuseSetter;
    RGBSetter* SpecularSetter;

};








}


#endif



