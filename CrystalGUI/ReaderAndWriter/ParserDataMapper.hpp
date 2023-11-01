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

#ifndef __ParserDataMapper_hpp__
#define __ParserDataMapper_hpp__

#include "CrystalGUI/Utility/Common.hpp"

#include <QtXml/QtXml>
#include <QtXml/QDomDocument>


namespace CrystalGUI {

class ParserTransferFunction : public QObject {
	Q_OBJECT

public:
	ParserTransferFunction(QObject* parent = Q_NULLPTR);
	~ParserTransferFunction();
	void setTsFuncFilePath(std::string path) {
        TsFuncFilePath = path;
	}

private:
	std::string TsFuncFilePath;

	QDomDocument reader;
	QDomDocument writer;




};






}


#endif








