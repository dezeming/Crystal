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
#include <QLabel>
#include <QPainter>
#include <QPainterPath>

namespace CrystalGUI {


class FloatSetter : public QGroupBox {
    Q_OBJECT
public:
    FloatSetter(QWidget* parent, QString Name, float min, float max);
    ~FloatSetter();

    void setValue(float val) {
        slider.setValue(val);
        spinbox.setValue(val);
        value = val;
    }
    void getValue(float& val) {
        val = value;
    }
    
private:
    float value;

    QGridLayout layout;

    QPushButton qpb;
    QDoubleSlider slider;
    QDoubleSpinBox spinbox;

signals:
    void signal_valueChanged(double);

private slots:
    void slot_valueChanged(double);

};

class RoundedLabel : public QLabel {
    Q_OBJECT
public:
    RoundedLabel(QWidget* parent = nullptr) : QLabel(parent) {
        setAttribute(Qt::WA_TranslucentBackground);
    }

protected:
    void paintEvent(QPaintEvent* event) override {
        QLabel::paintEvent(event);
        QPainter painter(this);

        QPainterPath path;
        path.addRoundedRect(rect(), 10.0, 10.0);
        QRegion roundedRegion = path.toFillPolygon().toPolygon();

        setMask(roundedRegion);
    }
};

class RGBSetter : public QGroupBox {
    Q_OBJECT
public:
    RGBSetter(QGroupBox* parent, QString Name, float val[3], int filler = 3);
    ~RGBSetter();

    void setValue(float val[3]);
    void getValue(float* val);
    
private:
    float value[3];
    QColor color;

    QGridLayout layout;

    QPushButton qpb;
    QLabel frame;
    QLabel label;

signals:
    void signal_valueChanged(const float* color);

private slots:
    void slot_valueChanged(const QColor& color);
    void slot_setValue();

};

class Margin : public QObject {
    Q_OBJECT
public:
    Margin(QObject* parent = Q_NULLPTR) {

    }
    Margin(int lb, int rb, int tb, int bb, QObject* parent = Q_NULLPTR) {
        left2Boundary = lb;
        right2Boundary = rb;
        top2Boundary = tb;
        bottom2Boundary = bb;
    }
    ~Margin() {

    }

    Margin& operator = (const Margin& Other) {
        left2Boundary = Other.left2Boundary;
        right2Boundary = Other.right2Boundary;
        top2Boundary = Other.top2Boundary;
        bottom2Boundary = Other.bottom2Boundary;
        return *this;
    }
    Margin(const Margin& Other) {
        *this = Other;
    }

public:
    int left2Boundary;
    int right2Boundary;
    int top2Boundary;
    int bottom2Boundary;
};



}

#endif


