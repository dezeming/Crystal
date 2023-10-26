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

#include <QtWidgets/QApplication>

#include "CrystalGUI/Utility/Common.hpp"
#include "MainWindow.hpp"

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    
    COUT_RED("Crystal v1.0.1") << std::endl;
    COUT_YELLOW("Crystal is an open-source medical imaging 3D volume rendering engine using physically-based rendering techniques.") << std::endl;
    COUT_YELLOW("The software is developed by dezeming. We hope that this engine "
        "can offer more promising assistance for surgical planning, surgical simulation, surgical education, and even surgical navigation.") << std::endl;
    COUT_RED("If you have any questions, you can contact me via email at <feimos@mail.ustc.edu.cn>.") << std::endl << std::endl;

    CrystalGUI::InitialMainWindow* w = new CrystalGUI::InitialMainWindow();
    w->show();

    return a.exec();
} 

   
