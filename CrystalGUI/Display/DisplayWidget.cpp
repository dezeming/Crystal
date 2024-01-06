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

#include <QElapsedTimer>

#include "CrystalGUI/Utility/Common.hpp"
#include "CrystalAlgrithm/Scene/Scene.h"

#define DisplayWidget_Debug true

namespace CrystalGUI {

RenderingThread::RenderingThread(QObject* parent) : QThread(parent) {
    if (DisplayWidget_Debug && !CloseAllDebugInfo) {
        Print_Gui_Info("Create RenderingThread Object");
    }
    runFlag = true;
}
RenderingThread::~RenderingThread() {
    if (DisplayWidget_Debug && !CloseAllDebugInfo) {
        Print_Gui_Info("Destroy RenderingThread Object");
    }
}
void RenderingThread::run() {

    qint64 minInterval = 20;

    while (runFlag) {
        QElapsedTimer timer;
        timer.start();

        m_Scene->film.setColorChanged(m_Scene->film.finalUChar4Buffer_host);

        emit finishRenderAFrame();

        

        qint64 elapsedMilliseconds = timer.elapsed();
        while (timer.elapsed() < minInterval);
    }

    if (DisplayWidget_Debug && !CloseAllDebugInfo) {
        Print_Gui_Info("Stop rendering thread");
    }
}


DisplayWidget::DisplayWidget(QWidget* parent) { 
    if (DisplayWidget_Debug && !CloseAllDebugInfo) {
        Print_Gui_Info("Create DisplayWidget Object");
    }

    setMinimumWidth(800);

    QFile qssfile("Resources/qss/DisplayWindow.qss");
    qssfile.open(QFile::ReadOnly);
    QString styleSheet = QString::fromLatin1(qssfile.readAll());
    this->setStyleSheet(styleSheet);

    qm = QImage("Resources/Icons/Crystal-Initial.png");
    qm.rgbSwap();
    qm.mirror(false, true);

    width = qm.width();
    height = qm.height();
    data = qm.bits();
    needUpdate = true;

    m_RenderingThread = nullptr;
    m_Scene = nullptr;
}

DisplayWidget::~DisplayWidget() {
    if (DisplayWidget_Debug && !CloseAllDebugInfo) {
        Print_Gui_Info("Destroy DisplayWidget Object");
    }

    m_RenderingThread->runFlag = false;
    if (m_RenderingThread->isRunning()) {
        m_RenderingThread->quit();
        m_RenderingThread->wait();
    }
    delete m_RenderingThread;

    makeCurrent();
    glDeleteTextures(1, &textureID);
    doneCurrent();
}

void DisplayWidget::initializeGL() {

    initializeOpenGLFunctions();
    glClearColor(0.0, 0.0, 0.0, 1.0);

    glEnable(GL_TEXTURE_2D);
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    // Set texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
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
    if (needUpdate) {
        //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, \
            GL_UNSIGNED_BYTE, imageSrc);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA,
            GL_UNSIGNED_BYTE, data); 

        needUpdate = false;
    }

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
void DisplayWidget::setImageData(void* imageSrc, uint w, uint h) {

    data = (unsigned char *)imageSrc;
    width = w;
    height = h;
    needUpdate = true;

    update();

}

void DisplayWidget::startRenderScene(CrystalAlgrithm::Scene* s)
{
    m_Scene = s;
    m_RenderingThread = new RenderingThread(this);
    connect(m_RenderingThread, SIGNAL(finishRenderAFrame()), this, SLOT(onFinishRenderAFrame()));

    m_RenderingThread->m_Scene = m_Scene;
    m_RenderingThread->start();
    
    m_Scene->film.setRed(m_Scene->film.finalUChar4Buffer_host);

    setImageData(m_Scene->film.finalUChar4Buffer_host, \
        m_Scene->film.resolution.x, m_Scene->film.resolution.y);
}

void DisplayWidget::onFinishRenderAFrame() {
    needUpdate = true;
    update();
}



}



