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


namespace CrystalGUI{

    class DisplayWidget;
    class DataPresentDockWidget;

class DisplayMainWindow : public QMainWindow
{
    Q_OBJECT

public:

    DisplayMainWindow(QString sceneFile, QWidget* parent = 0);
    ~DisplayMainWindow();

    //void setQtTsFuncDock(ParserScene& sp);

signals:
    void windowClosed();

protected:

    DisplayWidget* m_DisplayWidget;

    QHBoxLayout * mainLayout;

    QWidget* centralWidget;

    void closeEvent(QCloseEvent* e);

private:
    void setupMenu(void);
    void setupWidget(void);
    void setupDock(void);

};

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



