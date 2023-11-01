/**
Copyright (C) <2023>  <Dezeming>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#ifdef CRYSTAL_Using_Shared_Lib
#undef _EXPORTING
#endif

#include "DataTreeWidget.hpp"

#include <qtreeview.h>
#include <QHeaderView>

namespace CrystalGUI {

DataTreeWidget::DataTreeWidget(QWidget* pParent) :
	QTreeWidget(pParent) {

	// Set the size policy, making sure the widget fits nicely in the layout
	setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
	// Status and tooltip
	setToolTip("Statistics");
	//setStatusTip("Statistics");

	// Configure tree
	setColumnCount(3);

	QStringList ColumnNames;

	ColumnNames << "Property" << "Value" << "Unit";
	setHeaderLabels(ColumnNames);
	// Configure headers
	header()->resizeSection(0, 200);
	header()->resizeSection(1, 100);
	header()->resizeSection(2, 100);
	//header()->setWindowIcon(GetIcon("table-export"));
	//header()->setVisible(false);

	generateTree();
}
void DataTreeWidget::generateTree() {
	addTreeItem(NULL, "Performance", "", "", "application-monitor");
}

QTreeWidgetItem* DataTreeWidget::addTreeItem(QTreeWidgetItem* pParent,
	const QString& Property, const QString& Value, const QString& Unit, const QString& Icon)
{
	// Create new item
	QTreeWidgetItem* pItem = new QTreeWidgetItem(pParent);

	// Set item properties
	pItem->setText(0, Property);
	pItem->setText(1, Value);
	pItem->setText(2, Unit);
	QIcon ic = QIcon("Icons/" + Icon + ".png");
	pItem->setIcon(0, ic);
	if (!pParent)
		addTopLevelItem(pItem);
	return pItem;
}

void DataTreeWidget::UpdateData(const QString& Group, const QString& Name,
	const QString& Value, const QString& Unit, const QString& Icon)
{
	QTreeWidgetItem* pGroup = FindItem(Group);

	if (!pGroup)
	{
		pGroup = addTreeItem(NULL, Group);

		addTreeItem(pGroup, Name, Value, Unit, Icon);
	}
	else
	{
		bool Found = false;

		for (int i = 0; i < pGroup->childCount(); i++)
		{
			if (pGroup->child(i)->text(0) == Name)
			{
				pGroup->child(i)->setText(1, Value);
				pGroup->child(i)->setText(2, Unit);

				Found = true;
			}
		}

		if (!Found)
			addTreeItem(pGroup, Name, Value, Unit, Icon);
	}

	pGroup->setExpanded(true);
}

QTreeWidgetItem* DataTreeWidget::FindItem(const QString& Name)
{
	QList<QTreeWidgetItem*> Items = findItems(Name, Qt::MatchRecursive, 0);
	if (Items.size() <= 0)
		return NULL;
	else
		return Items[0];
}

void DataTreeWidget::dataChanged(const QString& Group, const QString& Name,
	const QString& Value, const QString& Unit, const QString& Icon)
{
	UpdateData(Group, Name, Value, Unit, Icon);
}



}






