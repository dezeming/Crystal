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

#ifndef __ScalarTransferFuncGraphicsView_h__
#define __ScalarTransferFuncGraphicsView_h__
#ifdef CRYSTAL_Using_Shared_Lib
#undef _EXPORTING
#endif

#include "CrystalGUI/Utility/Common.hpp"

#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QGraphicsLineItem>
#include <QGraphicsEllipseItem>
#include <QMouseEvent>
#include <QGroupBox>
#include <QScrollArea>
#include <QPen>
#include <QBrush>
#include <QList>

#include <QFile>

#include "CrystalGUI/Utility/Utility.hpp"
#include "CrystalAlgrithm/Scene/ScenePreset.h"

namespace CrystalGUI {

class ScalarTransferFuncGraphicsView;
class STF_NodeDisplayItem;
class ScalarTransferFuncGraphicsView;
class STF_NodeSignals;

const int STF_Node_ZValue = 100;
const int STF_Ligature_ZValue = 95;
const int STF_NodeDisplay_ZValue = 2;

const int STF_AxisGrid_ZValue = 0;
const int STF_ColorBarGrid_ZValue = 0;

class STF_NodeGraphicsItem : public QGraphicsEllipseItem {
public:
    STF_NodeGraphicsItem(QGraphicsEllipseItem* parent = Q_NULLPTR);
    ~STF_NodeGraphicsItem();
    STF_NodeGraphicsItem& operator = (const STF_NodeGraphicsItem& Other) {
        brushColor = Other.brushColor;
        pen_focus = Other.pen_focus;
        pen_nofocus = Other.pen_nofocus;

        isCurrentNode = Other.isCurrentNode;

        index = Other.index;
        
        lastNormalizedPos = Other.lastNormalizedPos;
        currentNormalizedPos = Other.currentNormalizedPos;
        nextNormalizedPos = Other.nextNormalizedPos;
        percentage = Other.percentage;

        startWidth = Other.startWidth;
        startHeight = Other.startHeight;
        endWidth = Other.endWidth;
        endHeight = Other.endHeight;

        return *this;
    }
    STF_NodeGraphicsItem(const STF_NodeGraphicsItem& Other){
        *this = Other;
    };

public:
    double lastNormalizedPos;
    double currentNormalizedPos;
    double nextNormalizedPos;
    double percentage;

    int startWidth, startHeight, endWidth, endHeight;

    STF_NodeDisplayItem* m_STF_NodeDisplayItem;
    STF_NodeSignals* m_STF_NodeSignals;

    bool isCurrentNode;

    int index;

    void paintFocusItem(void) {
        setPen(pen_focus);
        setBrush(brushColor);
    }

private:
    QBrush brushColor;
    QPen pen_nofocus;
    QPen pen_focus;

private:
    void mousePressEvent(QGraphicsSceneMouseEvent* pEvent);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* pEvent);
    void hoverEnterEvent(QGraphicsSceneHoverEvent* pEvent);
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = 0);
    QVariant itemChange(GraphicsItemChange change, const QVariant& value) override;

};

class STF_LigatureGraphicsItem : public QGraphicsLineItem {
public:
    STF_LigatureGraphicsItem(QGraphicsLineItem* parent = Q_NULLPTR) : QGraphicsLineItem(parent) {
        QPen pen(QColor(0, 120, 220));
        pen.setWidth(3);
        setZValue(10000);
        setPen(pen);
    }
    ~STF_LigatureGraphicsItem() {}
};

class STF_NodeSignals : public QObject {
    Q_OBJECT
public:
    STF_NodeSignals(QObject* parent = Q_NULLPTR);

public:
    void onCurrentNodePropertyChanged();
    void onCurrentNodePosChanged();
signals:
    void setCurrentNodePropertyChanged();
    void setCurrentNodePosChanged();
    
};

class STF_NodeDisplayItem : public QGraphicsRectItem {
public:
    STF_NodeDisplayItem(QGraphicsRectItem* parent, CrystalAlgrithm::STF_Preset& stfp);
    ~STF_NodeDisplayItem();

    void refresh();

    QList<STF_NodeGraphicsItem*> STF_NodeGraphicsList;
    QList<STF_LigatureGraphicsItem*> STF_LigatureGraphicsList;
    CrystalAlgrithm::STF_Preset& stfp_ref;

    STF_NodeSignals* m_STF_NodeSignals;

    int currentNodeIndex;

    int width, height;
    Margin nodeMargin;
    void setSize(int w, int h);
    int paintWidth, paintHeight;
    void setPaintAbleArea(int w, int h);

    void updateNodes();
    void updateLigatures();
    void updateRect();
};

class ScalarTransferFuncAxisGrid : public QGraphicsRectItem {
public:
    ScalarTransferFuncAxisGrid(QGraphicsRectItem* parent = Q_NULLPTR);
    ~ScalarTransferFuncAxisGrid();
    Margin gridMargin;
    void setSize(int w, int h);
    int getPaintAbleWidth() {
        return lineEndColumn - lineStartColumn;
    }
    int getPaintAbleHeight() {
        return lineEndRow - lineStartRow;
    }
    friend class ScalarTransferFuncGraphicsView;
private:
    int width, height;
    void refresh();

    int lineStartColumn, lineSegmentColumn, lineEndColumn;
    int lineStartRow, lineSegmentRow, lineEndRow;
    int gridLineNum[2]; // line number in grid at X and Y axes
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = 0);
};

class ScalarTransferFuncColorBarGrid : public QGraphicsRectItem {
public:
    ScalarTransferFuncColorBarGrid(QGraphicsRectItem* parent = Q_NULLPTR);
    ~ScalarTransferFuncColorBarGrid();
    void setupColorBar(const CrystalAlgrithm::STF_Preset& stfp);
    Margin colorBarMargin;
    void setWidth(const int w);
    unsigned int rectWidth, rectHeight;

    void refresh();
private:

};

class ScalarTransferFuncGraphicsView : public QGraphicsView {
	Q_OBJECT

public:
    ScalarTransferFuncGraphicsView(QGraphicsView* parent, CrystalAlgrithm::STF_Preset& stfp);
	~ScalarTransferFuncGraphicsView();

    STF_NodeSignals* m_STF_NodeSignals;
    
private:
    ScalarTransferFuncAxisGrid* m_ScalarTransferFuncAxisGrid;
    ScalarTransferFuncColorBarGrid* m_ScalarTransferFuncColorBarGrid;
    STF_NodeDisplayItem* m_STF_NodeDisplayItem;

	QGraphicsScene* scene;
    CrystalAlgrithm::STF_Preset & stfp_ref;

signals:
    void setSTFChangedInView();
    void setCurrentNodeIndexChangedInView(int);
private slots:
    void updateForChangedNodePos();

private:
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* pEvent);
    void resizeEvent(QResizeEvent* MyResizeEvent);

};

class ScalarTransferFuncWidget : public QGroupBox {
    Q_OBJECT
public:
    ScalarTransferFuncWidget(QGroupBox* parent, CrystalAlgrithm::STF_Preset& stfp);
    ~ScalarTransferFuncWidget();

private:
    void setupWidget();
    ScalarTransferFuncGraphicsView* m_ScalarTransferFuncGraphicsView;
    QScrollArea* ScalarTransferFuncQScrollArea;
    void setCurrentNode();
signals:
    void setSTFChanged();
private slots:
    void onSTFChangedInView();
    void onCurrentNodeIndexChangedInView(int);

    void onDensityScaleChanged(double);
    void onOpacityChanged(double);
    void onRoughnessChanged(double);
    void onMetallicChanged(double);
    void onHG_PhaseChanged(double);

    void onScatteringChanged(const float* vec);
    void onEmissionChanged(const float* vec);
    void onAbsorptionChanged(const float* vec);
    void onDiffuseChanged(const float* vec);
    void onSpecularChanged(const float* vec);

private:
    CrystalAlgrithm::STF_Preset& stfp;
    int currentNodeIndex;

    QVBoxLayout *layout;

    QVBoxLayout* setterLayout;

    FloatSetter* DensityScaleSetter;
    FloatSetter* HG_PhaseSetter;
    FloatSetter* OpacitySetter;
    FloatSetter* RoughnessSetter;
    FloatSetter* MetallicSetter;

    RGBSetter* ScatteringSetter;
    RGBSetter* EmissionSetter;
    RGBSetter* AbsorptionSetter;
    RGBSetter* DiffuseSetter;
    RGBSetter* SpecularSetter;

};



}


#endif



