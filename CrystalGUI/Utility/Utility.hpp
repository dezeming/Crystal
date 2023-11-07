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
#ifdef CRYSTAL_Using_Shared_Lib
#undef _EXPORTING
#endif

#ifndef __Utility_h__
#define __Utility_h__
#undef _EXPORTING

#include <QGroupBox>
#include <QPushButton>
#include "CrystalGUI/Utility/QDoubleSlider.hpp"
#include <QDoubleSpinBox>
#include <QGridLayout>
#include <QFrame>

namespace CrystalGUI {


class FloatSetter : public QGroupBox {
    Q_OBJECT
public:
    FloatSetter(QGroupBox* parent, QString Name, float min, float max);
    ~FloatSetter();

    void setValue(float val) {
        slider->setValue(val);
        spinbox->setValue(val);
        value = val;
    }
    void getValue(float& val) {
        val = value;
    }
    
private:
    float value;

    QGridLayout* layout;

    QPushButton* qpb;
    QDoubleSlider* slider;
    QDoubleSpinBox* spinbox;

signals:
    void signal_valueChanged(double);

private slots:
    void slot_valueChanged(double);

};

class RGBSetter : public QGroupBox {
    Q_OBJECT
public:
    RGBSetter(QGroupBox* parent, QString Name);
    ~RGBSetter();

    void setValue(float val[3]) {
        value[0] = val[0];
        value[0] = std::max(std::min(value[0], 1.0f), 0.0f);
        value[1] = val[1];
        value[1] = std::max(std::min(value[1], 1.0f), 0.0f);
        value[2] = val[2];
        value[2] = std::max(std::min(value[2], 1.0f), 0.0f);

        color.setRed(255.9f * value[0]);
        color.setGreen(255.9f * value[1]);
        color.setBlue(255.9f * value[2]);

        QPalette m_palette(color);
        frame->setPalette(m_palette);
    }
    void getValue(float* val) {
        val[0] = value[0];
        val[1] = value[1];
        val[2] = value[2];
    }
    
private:
    float value[3];
    QColor color;

    QGridLayout* layout;

    QPushButton* qpb;
    QFrame* frame;

signals:
    void signal_valueChanged(const QColor& color);

private slots:
    void slot_valueChanged(const QColor& color);
    void slot_setValue();

};







}



#endif


