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

#ifndef __Status_hpp__
#define __Status_hpp__
#include "Common.hpp"
#ifdef CRYSTAL_Using_Shared_Lib
#undef _EXPORTING
#endif

#include <QObject>

namespace CrystalGUI {

class GuiStatus : public QObject {
    Q_OBJECT
public:
    GuiStatus() {};
    ~GuiStatus() {};

signals:
    void setDataChanged(const QString& Group, const QString& Name,
        const QString& Value, const QString& Unit = "", const QString& Icon = "");


private slots:


};

extern GuiStatus m_GuiStatus;

class RenderingStatus : public QObject {
    Q_OBJECT
public:
    RenderingStatus() {};
    ~RenderingStatus() {};

signals:


private slots:


};

}

#endif




















