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


#ifndef __ScalarTransferFuncNodePropertiesWidget_h__
#define __ScalarTransferFuncNodePropertiesWidget_h__
#ifdef CRYSTAL_Using_Shared_Lib
#undef _EXPORTING
#endif

#include "CrystalGUI/Utility/Common.hpp"

#include <QGroupBox>

namespace CrystalGUI {

class ScalarTransferFuncNodePropertiesWidget : public QGroupBox {
	Q_OBJECT

public:
	ScalarTransferFuncNodePropertiesWidget(QWidget* parent = Q_NULLPTR);

	~ScalarTransferFuncNodePropertiesWidget();



};


/** Optional node attributes
* NormalizedIntensity: Value\in[0,1]
* DensityScale: Value\in[0,10]
* 
* Emission: L_{e}
* Absorption: \sigma_{a}
* Scattering: \sigma_{s}
* Henyey-Greenstein: HG_Phase g\in[-1,1]
* 
* Opacity: Value\in[0,1]
* Diffuse: 
* Specular: 
* Roughness: 
* Metallic: 
*/

/*
<OneNodeProperties Name="OneNodeProperties">
	<DensityScale components="1" type="float" RangeBtn="0.0" RangeTop="10.0" />
	<!-- Strictly Physically-based -->
	<Emission components="3" type="float" RangeBtn="0" RangeTop="1.0" />
	<Absorption components="3" type="float" RangeBtn="0" RangeTop="1.0" />
	<Scattering components="3" type="float" RangeBtn="0" RangeTop="1.0" />
	<HG_Phase components="1" type="float" RangeBtn="-1.0" RangeTop="1.0" />
	<!-- Physically-based -->
	<Opacity components="1" type="float" RangeBtn="0" RangeTop="1.0" />
	<Diffuse components="3" type="float" RangeBtn="0" RangeTop="1.0" />
	<Specular components="3" type="float" RangeBtn="0" RangeTop="1.0" />
	<Roughness components="1" type="float" RangeBtn="0" RangeTop="1.0" />
	<Metallic components="1" type="float" RangeBtn="0" RangeTop="1.0"  />
</OneNodeProperties>
*/





}

#endif


