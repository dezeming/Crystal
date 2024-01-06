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

#ifndef __DisplayWidget_h__
#define __DisplayWidget_h__
#ifdef CRYSTAL_Using_Shared_Lib
#undef _EXPORTING
#endif

#include "CrystalGUI/Utility/Common.hpp"

#include <QImage>
#include <QObject>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QOpenGLWidget>

#include <QThread>

namespace CrystalAlgrithm {
    class Scene;
}


namespace CrystalGUI {

class DisplayWidget;
class RenderingThread : public QThread {
    Q_OBJECT
public:
    RenderingThread(QObject* parent = nullptr);
    ~RenderingThread();

protected:
    void run() override;
private:
    CrystalAlgrithm::Scene* m_Scene;

    bool runFlag;
    friend class DisplayWidget;

signals:
    void finishRenderAFrame();

};

class DisplayWidget : public QOpenGLWidget, protected QOpenGLFunctions {
    Q_OBJECT
public:
    explicit DisplayWidget(QWidget* parent = 0);
    ~DisplayWidget();
    void startRenderScene(CrystalAlgrithm::Scene* s);

    void setImageData(void* imageSrc, uint width, uint height);

protected:
    void initializeGL() Q_DECL_OVERRIDE;
    void resizeGL(int w, int h) Q_DECL_OVERRIDE;
    void paintGL() Q_DECL_OVERRIDE;


    QImage qm;

private:
    GLuint textureID;

    bool needUpdate;
    unsigned char* data;
    unsigned int width, height;

private:
    CrystalAlgrithm::Scene* m_Scene;
    RenderingThread *m_RenderingThread;
private slots:
    void onFinishRenderAFrame();

};




}


#endif


