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

#ifndef __MainWindow_h__
#define __MainWindow_h__
#ifdef CRYSTAL_Using_Shared_Lib
#undef _EXPORTING
#endif

#include "CrystalGUI/Utility/Common.hpp"

#include <QtWidgets>

#include <QMainWindow>
#include <QWidget>
#include <QCloseEvent>

#include <QHBoxLayout>

#include "CrystalGUI/ReaderAndWriter/ParserScene.hpp"

namespace CrystalAlgrithm {
    class Scene;
}

namespace CrystalGUI{

class DisplayWidget;
class DataMapperDockWidget;

class DisplayMainWindow : public QMainWindow
{
    Q_OBJECT

public:

    DisplayMainWindow(QString sceneFile, QWidget* parent = 0);
    ~DisplayMainWindow();

signals:
    void windowClosed();

protected:
    QHBoxLayout * mainLayout;
    QWidget* centralWidget;

    DisplayWidget* m_DisplayWidget;

    // Docks
    DataMapperDockWidget* m_DataMapperDockWidget;

    void closeEvent(QCloseEvent* e);

    ParserScene parser;
    CrystalAlgrithm::Scene* m_Scene;

private:
    void setupMenu(void);
    void setupWidget(void);
    void setupDock(void);

};


class DataPresentDockWidget;

class InitialMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    InitialMainWindow(QWidget* parent = Q_NULLPTR);
    ~InitialMainWindow();

protected:
    QToolBar* mainToolBar;

    QMenuBar* menuBar;
    QMenu* fileMenu;

    QAction* OpenSceneAction;
    QAction* RunExampleAction;

    // Widgets
    DisplayMainWindow* m_DisplayMainWindow;

    // Dock Widgets
    DataPresentDockWidget* m_DataPresentDockWidget;

    bool isDisplayMainWindowExist;

private:
    void setupWidget(void);
    void setupDock(void);
    void setupMenu();
    void setupTool();

    void closeEvent(QCloseEvent* e);
private:
    QWidget* centralWidget;


private slots:
    void RunExample();
    void DisplayMainWindowClosed();

};







}



#endif



