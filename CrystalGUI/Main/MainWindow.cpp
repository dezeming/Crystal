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

#include "MainWindow.hpp"

// Wdiget
#include "CrystalGUI/Display/DisplayWidget.hpp"

//DockWidget
#include "CrystalGUI/InfoPresent/DataPresentDockWidget.hpp"
#include "CrystalGUI/DataMapper/DataMapperDockWidget.hpp"

#include <QFile>

#define MainWindowDebug true

namespace CrystalGUI{


  
InitialMainWindow::InitialMainWindow(QWidget* parent)
    : QMainWindow(parent) {

    if (MainWindowDebug && !CloseAllDebugInfo) {
        Print_Gui_Info("Create InitialMainWindow Object");
    }

    // Appearance
    setWindowIcon(QIcon("Resources/Icons/sIcon.png"));
    
    QFile qssfile("Resources/qss/InitialMainWindow.qss");
    qssfile.open(QFile::ReadOnly);
    QString styleSheet = QString::fromLatin1(qssfile.readAll());
    this->setStyleSheet(styleSheet);

    setAttribute(Qt::WA_DeleteOnClose, true);

    setFixedSize(500, 483);

    setupMenu();

    setupTool();

    setupWidget();

    setupDock();

    isDisplayMainWindowExist = false;
}

InitialMainWindow::~InitialMainWindow() {
    if (MainWindowDebug && !CloseAllDebugInfo) {
        Print_Gui_Info("Destroy InitialMainWindow Object");
    }

    if (m_DisplayMainWindow && isDisplayMainWindowExist) {
        // Disconnect signals and slots
        disconnect(RunExampleAction, SIGNAL(triggered()), this, SLOT(RunExample()));

        // delete DisplayMainWindow
        m_DisplayMainWindow->~DisplayMainWindow();
        
    }

    

    // Disconnect all signals and slots

}


void InitialMainWindow::setupMenu() {

    menuBar = new QMenuBar;
    setMenuBar(menuBar);

    OpenSceneAction = new QAction;
    OpenSceneAction->setIcon(QIcon("Resources/Icons/OpenScene.png"));
    OpenSceneAction->setText(tr("Open Scene"));

    RunExampleAction = new QAction;
    RunExampleAction->setIcon(QIcon("Resources/Icons/RunExample.png"));
    RunExampleAction->setText(tr("Run Example"));

    connect(RunExampleAction, SIGNAL(triggered()), this, SLOT(RunExample()));

    fileMenu = new QMenu;
    menuBar->addMenu(fileMenu);
    fileMenu->setTitle("File");

    fileMenu->addAction(OpenSceneAction);
    fileMenu->addSeparator();
    fileMenu->addAction(RunExampleAction);
}

void InitialMainWindow::setupTool() {
    mainToolBar = new QToolBar(this);
    addToolBar(Qt::TopToolBarArea, mainToolBar);

    mainToolBar->addAction(OpenSceneAction);
    mainToolBar->addSeparator();
    mainToolBar->addAction(RunExampleAction);
    mainToolBar->addSeparator();
}


void InitialMainWindow::closeEvent(QCloseEvent* e) {
    int ret = QMessageBox::question(this, "close", "Really close Crystal?");
    if (ret == QMessageBox::Yes) {
        e->accept();
    }
    else {
        e->ignore();
    }
}

void InitialMainWindow::RunExample() {
    if (m_DisplayMainWindow && isDisplayMainWindowExist) {
        
        return;
    }
    m_DisplayMainWindow = new DisplayMainWindow("Examples/Example1/Scene.xml", nullptr);
    m_DisplayMainWindow->show();
    // Connect signals and slots
    connect(m_DisplayMainWindow, SIGNAL(windowClosed()), this, SLOT(DisplayMainWindowClosed()));

    isDisplayMainWindowExist = true;
}

void InitialMainWindow::DisplayMainWindowClosed() {
    isDisplayMainWindowExist = false;
}

void InitialMainWindow::setupWidget(void) {

}

void InitialMainWindow::setupDock(void) {
    m_DataPresentDockWidget = new DataPresentDockWidget;
    addDockWidget(Qt::LeftDockWidgetArea, m_DataPresentDockWidget);
    showMemoryInfo();
    showCudaDevicesInfo();
}



DisplayMainWindow::DisplayMainWindow(QString sceneFile, QWidget* parent) {

    if (MainWindowDebug && !CloseAllDebugInfo) {
        Print_Gui_Info("Create DisplayMainWindow Object");
    }

    setMinimumSize(350, 200);

    //m_QtRenderThread = NULL;

    setWindowIcon(QIcon("Resources/Icons/sIcon.png"));
    QFile qssfile("Resources/qss/DisplayMainWindow.qss");
    qssfile.open(QFile::ReadOnly);
    QString styleSheet = QString::fromLatin1(qssfile.readAll());
    this->setStyleSheet(styleSheet);

    centralWidget = new QWidget;
    setCentralWidget(centralWidget);
    
    mainLayout = new QHBoxLayout;
    centralWidget->setLayout(mainLayout);

    // parse XML File
    parser.setFilePath(sceneFile);
    parser.readSceneXML();

    // Initialize TransferFunction DockWidget
    //setQtTsFuncDock(sp);

    // Initialize QtVisualizer
    //m_QtVisualizer = new QtVisualizer;
    //m_QtVisualizer->Initialization(sp.m_ScenePreset.m_VisualizerPreset);

    setupWidget();

    setupDock();

    // start rendering thread
    //m_QtRenderThread = new QtRenderThread();
    //m_QtRenderThread->setVisualizer(m_QtVisualizer->m_Visualizer);
    //m_QtRenderThread->setFrameBuffer(m_QtVisualizer->m_FrameBuffer);

    //m_QtRenderThread->renderBegin();
    //m_QtRenderThread->start();
   // connect(m_QtRenderThread, SIGNAL(generateNewFrame()), displayWidget, SLOT(displayNewFrame()));

    // Test
    // CrystalAlgrithm::printCudaDevice();
    // CrystalAlgrithm::SpectrumTest();

}


DisplayMainWindow::~DisplayMainWindow() {
    if (MainWindowDebug && !CloseAllDebugInfo) {
        Print_Gui_Info("Destroy DisplayMainWindow Object");
    }  

    //disconnect(m_QtRenderThread, SIGNAL(generateNewFrame()), displayWidget, SLOT(displayNewFrame()));
    /*
    if (m_QtRenderThread) {
        m_QtRenderThread->setStopFlag(true);

        // Kill the render thread
        m_QtRenderThread->quit();
        // Wait for thread to end
        m_QtRenderThread->wait();

        delete m_QtRenderThread;
        m_QtRenderThread = NULL;
    }*/

    //if (m_QtVisualizer) {
    //    delete m_QtVisualizer;
    //}

}

void DisplayMainWindow::closeEvent(QCloseEvent* e) {

    int ret = QMessageBox::question(this, "close", "Really close Display Window?");
    if (ret == QMessageBox::Yes) {
        emit windowClosed();
        e->accept();
        delete this;
    }
    else {
        e->ignore();
    }
    showMemoryInfo();
}

void DisplayMainWindow::setupMenu(void) {

}

void DisplayMainWindow::setupWidget(void) {
    // Initialize DisplayWidget
    m_DisplayWidget = new DisplayWidget;
    // thread return 0x1, maybe not a mistake
    mainLayout->addWidget(m_DisplayWidget);
}

void DisplayMainWindow::setupDock(void) {
    m_DataMapperDockWidget = new DataMapperDockWidget;
    addDockWidget(Qt::LeftDockWidgetArea, m_DataMapperDockWidget);

    //tabifyDockWidget(m_DataMapperDockWidget, m_LightSetDockWidget);
    m_DataMapperDockWidget->raise();

}




}


