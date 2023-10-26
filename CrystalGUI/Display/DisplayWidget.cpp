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

#include "DisplayWidget.hpp"

#include <QDebug>
#include <QGraphicsOpacityEffect>
#include <QFile>

#include "CrystalGUI/Utility/Common.hpp"

#define DisplayWidget_Debug true

namespace CrystalGUI {

DisplayWidget::DisplayWidget(QWidget* parent) { 
    if (DisplayWidget_Debug && !CloseAllDebugInfo) {
        Print_Gui_Info("Create DisplayWidget Object");
    }

    QFile qssfile("Resources/qss/DisplayWindow.qss");
    qssfile.open(QFile::ReadOnly);
    QString styleSheet = QString::fromLatin1(qssfile.readAll());
    this->setStyleSheet(styleSheet);

    qm = QImage("Resources/Icons/Crystal-Initial.png");
    qm.rgbSwap();
    qm.mirror(false, true);

}

DisplayWidget::~DisplayWidget() {
    if (DisplayWidget_Debug && !CloseAllDebugInfo) {
        Print_Gui_Info("Destroy DisplayWidget Object");
    }

}

void DisplayWidget::initializeGL() {

    // Enable texturing
    glEnable(GL_TEXTURE_2D);  

    // Obtain an id for the texture
    glGenTextures(1, &textureID);       
    // Set as the current texture
    glBindTexture(GL_TEXTURE_2D, textureID);  

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, qm.width(), qm.height(), 0, GL_RGBA,
        GL_UNSIGNED_BYTE, qm.bits());

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    glDisable(GL_TEXTURE_2D);
}

void DisplayWidget::resizeGL(int w, int h) {

    glViewport(0, 0, w - 1, h - 1);
}

void DisplayWidget::paintGL() {
    // Set Background Color
    glClearColor(1.0f, 0.4f, 0.6f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex3f(-1, -1, -1);
    glTexCoord2f(1, 0);
    glVertex3f(1, -1, -1);
    glTexCoord2f(1, 1);
    glVertex3f(1, 1, -1);
    glTexCoord2f(0, 1);
    glVertex3f(-1, 1, -1);

    glEnd();

    glDisable(GL_TEXTURE_2D);
}


// Set the data source and its size
void DisplayWidget::setImageData(uchar* imageSrc, uint width, uint height) {

}



}



