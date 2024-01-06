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


#include "ScalarTransferFuncGraphicsView.hpp"

#include <QGraphicsSceneMouseEvent>

namespace CrystalGUI {

#define ScalarTransferFuncGraphicsViewDebug true

ScalarTransferFuncGraphicsView::ScalarTransferFuncGraphicsView(QGraphicsView* parent, CrystalAlgrithm::STF_Preset& stfp) :
	QGraphicsView(parent),
    stfp_ref(stfp){
    if (ScalarTransferFuncGraphicsViewDebug && !CloseAllDebugInfo) {
        Print_Gui_Info("Create ScalarTransferFuncGraphicsView Object");
    }
	setMinimumSize(200,100);
    setFrameShadow(Sunken);

    scene = new QGraphicsScene;
    scene->setBackgroundBrush(QColor(225, 255, 255, 255));
    setScene(scene);
    //set anti-aliasing
    setRenderHint(QPainter::Antialiasing, true);
    //disable the scroll
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // ScalarTransferFuncAxisGrid
    m_ScalarTransferFuncAxisGrid = new ScalarTransferFuncAxisGrid;
    m_ScalarTransferFuncAxisGrid->setZValue(STF_AxisGrid_ZValue);
    scene->addItem(m_ScalarTransferFuncAxisGrid);

    //ScalarTransferFuncColorBarGrid
    m_ScalarTransferFuncColorBarGrid = new ScalarTransferFuncColorBarGrid;
    m_ScalarTransferFuncColorBarGrid->setZValue(STF_ColorBarGrid_ZValue);
    scene->addItem(m_ScalarTransferFuncColorBarGrid);
    m_ScalarTransferFuncColorBarGrid->setupColorBar(stfp_ref);

    setMinimumHeight(m_ScalarTransferFuncColorBarGrid->rectHeight + 200);
    
    m_STF_NodeSignals = new STF_NodeSignals;

    m_STF_NodeDisplayItem = new STF_NodeDisplayItem(Q_NULLPTR, stfp_ref);
    scene->addItem(m_STF_NodeDisplayItem);
    m_STF_NodeDisplayItem->m_STF_NodeSignals = m_STF_NodeSignals;
    connect(m_STF_NodeSignals, SIGNAL(setCurrentNodePosChanged()), this, SLOT(updateForChangedNodePos()));
}

ScalarTransferFuncGraphicsView::~ScalarTransferFuncGraphicsView() {
    if (ScalarTransferFuncGraphicsViewDebug && !CloseAllDebugInfo) {
        Print_Gui_Info("Destroy ScalarTransferFuncGraphicsView Object");
    }

    delete m_STF_NodeSignals;
}

void ScalarTransferFuncGraphicsView::updateForChangedNodePos() {
    m_STF_NodeDisplayItem->updateLigatures();
    emit setSTFChangedInView();
}

void ScalarTransferFuncGraphicsView::mousePressEvent(QMouseEvent* pEvent) {
    QGraphicsView::mousePressEvent(pEvent);

    QPoint qpnt = pEvent->pos();
    QPointF  scenePos = mapToScene(qpnt);

    STF_NodeGraphicsItem* pNodeItem = dynamic_cast<STF_NodeGraphicsItem*>(scene->itemAt(qpnt.x(), qpnt.y(), QTransform()));
    bool needToUpdate = false;
    if (!pNodeItem) {
        if (scenePos.x() > m_ScalarTransferFuncAxisGrid->lineStartColumn 
            && scenePos.x() < m_ScalarTransferFuncAxisGrid->lineEndColumn
            && scenePos.y() > m_ScalarTransferFuncAxisGrid->lineStartRow
            && scenePos.y() < m_ScalarTransferFuncAxisGrid->lineEndRow) {

            float normalizedIntensity = (double)(scenePos.x() - m_ScalarTransferFuncAxisGrid->lineStartColumn) /
                (double)(m_ScalarTransferFuncAxisGrid->lineEndColumn - m_ScalarTransferFuncAxisGrid->lineStartColumn);
            float percentage = (double)(m_ScalarTransferFuncAxisGrid->lineEndRow - scenePos.y()) /
                (double)(m_ScalarTransferFuncAxisGrid->lineEndRow - m_ScalarTransferFuncAxisGrid->lineStartRow);

            int insertNodeIndex = stfp_ref.addNewRandomNode(
                m_STF_NodeDisplayItem->currentNodeIndex, 
                normalizedIntensity, percentage);
            if (insertNodeIndex > 0) {
                needToUpdate = true;
                m_STF_NodeDisplayItem->currentNodeIndex = insertNodeIndex;

                emit setCurrentNodeIndexChangedInView(m_STF_NodeDisplayItem->currentNodeIndex);
            }

        }
    }
    else {
        if (pEvent->button() == Qt::LeftButton) {
            m_STF_NodeDisplayItem->currentNodeIndex = pNodeItem->index;
            emit setCurrentNodeIndexChangedInView(m_STF_NodeDisplayItem->currentNodeIndex);
        }
        else if (pEvent->button() == Qt::RightButton) {
            if (pNodeItem->index != 0 && pNodeItem->index != (stfp_ref.NormalizedIntensity.size() - 1)) {
                m_STF_NodeDisplayItem->currentNodeIndex = 
                    stfp_ref.deleteNode(m_STF_NodeDisplayItem->currentNodeIndex, pNodeItem->index);
                needToUpdate = true;

                emit setCurrentNodeIndexChangedInView(m_STF_NodeDisplayItem->currentNodeIndex);
            }
        }

    }

    if (needToUpdate) {
        m_STF_NodeDisplayItem->updateNodes();
        m_STF_NodeDisplayItem->updateLigatures();
        emit setSTFChangedInView();
    }

}

void ScalarTransferFuncGraphicsView::mouseReleaseEvent(QMouseEvent* pEvent) {
    QGraphicsView::mouseReleaseEvent(pEvent);
    m_STF_NodeDisplayItem->updateNodes();
    m_STF_NodeDisplayItem->updateLigatures();

    m_ScalarTransferFuncAxisGrid->refresh();
    m_ScalarTransferFuncColorBarGrid->refresh();
    m_STF_NodeDisplayItem->refresh();

    int c_width = width(), c_height = height();
    resize(c_width + 1, c_height);
    resize(c_width, c_height);
}

void ScalarTransferFuncGraphicsView::resizeEvent(QResizeEvent* MyResizeEvent) {
    QGraphicsView::resizeEvent(MyResizeEvent);

    setSceneRect(0, 0, width(), height() - 2);

    int AxisGridHeight = (height() - 2) - m_ScalarTransferFuncColorBarGrid->rectHeight;

    m_ScalarTransferFuncAxisGrid->setSize(width(), AxisGridHeight);
    m_ScalarTransferFuncAxisGrid->setRect(0, 0, width(), AxisGridHeight);

    int ColorBarGridTop = AxisGridHeight;

    m_ScalarTransferFuncColorBarGrid->colorBarMargin;
    m_ScalarTransferFuncColorBarGrid->setWidth(width());
    m_ScalarTransferFuncColorBarGrid->setPos(0, AxisGridHeight);

    m_STF_NodeDisplayItem->setSize(width(), AxisGridHeight);
    m_STF_NodeDisplayItem->nodeMargin = m_ScalarTransferFuncAxisGrid->gridMargin;
    m_STF_NodeDisplayItem->setPaintAbleArea(
        m_ScalarTransferFuncAxisGrid->getPaintAbleWidth(),
        m_ScalarTransferFuncAxisGrid->getPaintAbleHeight());
    m_STF_NodeDisplayItem->updateNodes();
    m_STF_NodeDisplayItem->updateLigatures();


}



// ScalarTransferFuncWidget

ScalarTransferFuncWidget::ScalarTransferFuncWidget(QGroupBox* parent, CrystalAlgrithm::STF_Preset& stfp) : QGroupBox(parent), stfp(stfp){
    if (ScalarTransferFuncGraphicsViewDebug && !CloseAllDebugInfo) {
        Print_Gui_Info("Create ScalarTransferFuncWidget Object");
    }

	setTitle(QString(stfp.type.c_str()) + " Scalar Transfer Function");
    QFile qssfile("Resources/qss/STFWidget.qss");
    qssfile.open(QFile::ReadOnly);
    QString styleSheet = QString::fromLatin1(qssfile.readAll());
    this->setStyleSheet(styleSheet);


    layout = new QVBoxLayout;
    setLayout(layout);

    setterLayout = new QVBoxLayout;

    setupWidget();

}

ScalarTransferFuncWidget::~ScalarTransferFuncWidget() {
    if (ScalarTransferFuncGraphicsViewDebug && !CloseAllDebugInfo) {
        Print_Gui_Info("Destroy ScalarTransferFuncWidget Object");
    }


}

void ScalarTransferFuncWidget::setupWidget() {
    
    m_ScalarTransferFuncGraphicsView = new ScalarTransferFuncGraphicsView(Q_NULLPTR, stfp);
    
    connect(m_ScalarTransferFuncGraphicsView, SIGNAL(setSTFChangedInView()), 
        this, SLOT(onSTFChangedInView()));
    connect(m_ScalarTransferFuncGraphicsView, SIGNAL(setCurrentNodeIndexChangedInView(int)), 
        this, SLOT(onCurrentNodeIndexChangedInView(int)));

    layout->addWidget(m_ScalarTransferFuncGraphicsView);
    
    ScalarTransferFuncQScrollArea = new QScrollArea;
    QWidget* viewport = new QWidget;
    ScalarTransferFuncQScrollArea->setWidgetResizable(true);
    ScalarTransferFuncQScrollArea->setWidget(viewport);
    ScalarTransferFuncQScrollArea->setMaximumHeight(300);
    viewport->setLayout(setterLayout);

    if (stfp.hasOpacity) {
        //OpacitySetter = new FloatSetter(this, "Opacity", 0.0f, 1.0f);
        //layout->addWidget(OpacitySetter);
        //connect(OpacitySetter,SIGNAL(signal_valueChanged(double)),this,SLOT(onOpacityChanged(double)));
    }
    if (stfp.hasEmission) {
        float vec[3] = {
            stfp.Emission[0][0],
            stfp.Emission[0][1],
            stfp.Emission[0][2] };
        EmissionSetter = new RGBSetter(this, "Emission", vec);
        setterLayout->addWidget(EmissionSetter);
        connect(EmissionSetter, SIGNAL(signal_valueChanged(const float*)), this, SLOT(onEmissionChanged(const float*)));
    }
    if (stfp.hasAbsorption) {
        float vec[3] = {
            stfp.Absorption[0][0],
            stfp.Absorption[0][1],
            stfp.Absorption[0][2] };
        AbsorptionSetter = new RGBSetter(this, "Absorption", vec);
        setterLayout->addWidget(AbsorptionSetter);
        connect(AbsorptionSetter, SIGNAL(signal_valueChanged(const float*)), this, SLOT(onAbsorptionChanged(const float*)));
    }
    if (stfp.hasScattering) {
        float vec[3] = {
            stfp.Scattering[0][0],
            stfp.Scattering[0][1],
            stfp.Scattering[0][2] };
        ScatteringSetter = new RGBSetter(this, "Scattering", vec);
        setterLayout->addWidget(ScatteringSetter);
        connect(ScatteringSetter, SIGNAL(signal_valueChanged(const float*)), this, SLOT(onScatteringChanged(const float*)));
    }
    if (stfp.hasDiffuse) {
        float vec[3] = {
            stfp.Diffuse[0][0],
            stfp.Diffuse[0][1],
            stfp.Diffuse[0][2] };
        DiffuseSetter = new RGBSetter(this, "Diffuse", vec);
        setterLayout->addWidget(DiffuseSetter);
        connect(DiffuseSetter, SIGNAL(signal_valueChanged(const float*)), this, SLOT(onDiffuseChanged(const float*)));
    }
    if (stfp.hasSpecular) {
        float vec[3] = {
            stfp.Specular[0][0],
            stfp.Specular[0][1],
            stfp.Specular[0][2] };
        SpecularSetter = new RGBSetter(this, "Specular", vec);
        setterLayout->addWidget(SpecularSetter);
        connect(SpecularSetter, SIGNAL(signal_valueChanged(const float*)), this, SLOT(onSpecularChanged(const float*)));
    }
    if (stfp.hasRoughness) {
        RoughnessSetter = new FloatSetter(this, "Roughness", 0.0f, 1.0f);
        setterLayout->addWidget(RoughnessSetter);
        connect(RoughnessSetter, SIGNAL(signal_valueChanged(double)), this, SLOT(onRoughnessChanged(double)));
    }
    if (stfp.hasMetallic) {
        MetallicSetter = new FloatSetter(this, "Metallic", 0.0f, 1.0f);
        setterLayout->addWidget(MetallicSetter);
        connect(MetallicSetter, SIGNAL(signal_valueChanged(double)), this, SLOT(onMetallicChanged(double)));
    }
    if (stfp.hasDensityScale) {
        DensityScaleSetter = new FloatSetter(this, "DensityScale", 0.0f, 10.0f);
        setterLayout->addWidget(DensityScaleSetter);
        connect(DensityScaleSetter, SIGNAL(signal_valueChanged(double)), this, SLOT(onDensityScaleChanged(double)));
    }
    if (stfp.hasHG_Phase) {
        HG_PhaseSetter = new FloatSetter(this, "HG Phase", -1.0f, 1.0f);
        setterLayout->addWidget(HG_PhaseSetter);
        connect(HG_PhaseSetter, SIGNAL(signal_valueChanged(double)), this, SLOT(onHG_PhaseChanged(double)));
    }
    setterLayout->setSpacing(-50);

    layout->addWidget(ScalarTransferFuncQScrollArea);

    currentNodeIndex = 0;
    setCurrentNode();
}

void ScalarTransferFuncWidget::setCurrentNode() {
    int index = currentNodeIndex;
    if (stfp.hasDiffuse) {
        float vec[3] = {
            stfp.Diffuse[index][0],
            stfp.Diffuse[index][1],
            stfp.Diffuse[index][2] };
        DiffuseSetter->setValue(vec);
    }
    if (stfp.hasSpecular) {
        float vec[3] = {
            stfp.Specular[index][0],
            stfp.Specular[index][1],
            stfp.Specular[index][2] };
        SpecularSetter->setValue(vec);
    }
    if (stfp.hasEmission) {
        float vec[3] = {
            stfp.Emission[index][0],
            stfp.Emission[index][1],
            stfp.Emission[index][2] };
        EmissionSetter->setValue(vec);
    }
    if (stfp.hasAbsorption) {
        float vec[3] = {
            stfp.Absorption[index][0],
            stfp.Absorption[index][1],
            stfp.Absorption[index][2] };
        AbsorptionSetter->setValue(vec);
    }
    if (stfp.hasScattering) {
        float vec[3] = {
            stfp.Scattering[index][0],
            stfp.Scattering[index][1],
            stfp.Scattering[index][2] };
        ScatteringSetter->setValue(vec);
    }

    if (stfp.hasRoughness) {
        RoughnessSetter->setValue(stfp.Roughness[index]);
    }
    if (stfp.hasDensityScale) {
        DensityScaleSetter->setValue(stfp.DensityScale[index]);
    }
    if (stfp.hasMetallic) {
        MetallicSetter->setValue(stfp.Metallic[index]);
    }
    if (stfp.hasHG_Phase) {
        HG_PhaseSetter->setValue(stfp.HG_Phase[index]);
    }

}

void ScalarTransferFuncWidget::onSTFChangedInView() {

    emit setSTFChanged();
}

void ScalarTransferFuncWidget::onCurrentNodeIndexChangedInView(int index) {

    currentNodeIndex = index;

    if (stfp.hasDiffuse) {
        float vec[3] = { 
            stfp.Diffuse[index][0], 
            stfp.Diffuse[index][1], 
            stfp.Diffuse[index][2] };
        DiffuseSetter->setValue(vec);
    }
    if (stfp.hasSpecular) {
        float vec[3] = {
            stfp.Specular[index][0],
            stfp.Specular[index][1],
            stfp.Specular[index][2] };
        SpecularSetter->setValue(vec);
    }
    if (stfp.hasEmission) {
        float vec[3] = {
            stfp.Emission[index][0],
            stfp.Emission[index][1],
            stfp.Emission[index][2] };
        EmissionSetter->setValue(vec);
    }
    if (stfp.hasAbsorption) {
        float vec[3] = {
            stfp.Absorption[index][0],
            stfp.Absorption[index][1],
            stfp.Absorption[index][2] };
        AbsorptionSetter->setValue(vec);
    }
    if (stfp.hasScattering) {
        float vec[3] = {
            stfp.Scattering[index][0],
            stfp.Scattering[index][1],
            stfp.Scattering[index][2] };
        ScatteringSetter->setValue(vec);
    }

    if (stfp.hasRoughness) {
        RoughnessSetter->setValue(stfp.Roughness[index]);
    }
    if (stfp.hasDensityScale) {
        DensityScaleSetter->setValue(stfp.DensityScale[index]);
    }
    if (stfp.hasMetallic) {
        MetallicSetter->setValue(stfp.Metallic[index]);
    }
    if (stfp.hasHG_Phase) {
        HG_PhaseSetter->setValue(stfp.HG_Phase[index]);
    }


}

void ScalarTransferFuncWidget::onDensityScaleChanged(double val) {
    stfp.DensityScale[currentNodeIndex] = val;
    emit setSTFChanged();
}

void ScalarTransferFuncWidget::onOpacityChanged(double val) {
    stfp.Opacity[currentNodeIndex] = val;
    emit setSTFChanged();
}

void ScalarTransferFuncWidget::onRoughnessChanged(double val) {
    stfp.Roughness[currentNodeIndex] = val;
    emit setSTFChanged();
}

void ScalarTransferFuncWidget::onMetallicChanged(double val) {
    stfp.Metallic[currentNodeIndex] = val;
    emit setSTFChanged();
}

void ScalarTransferFuncWidget::onHG_PhaseChanged(double val) {
    stfp.HG_Phase[currentNodeIndex] = val;
    emit setSTFChanged();
}

void ScalarTransferFuncWidget::onScatteringChanged(const float* vec) {
    CrystalAlgrithm::Spectrum3 col;
    col[0] = vec[0]; col[1] = vec[1]; col[2] = vec[2]; 
    stfp.Scattering[currentNodeIndex] = col;
    emit setSTFChanged();
}

void ScalarTransferFuncWidget::onEmissionChanged(const float* vec) {
    CrystalAlgrithm::Spectrum3 col;
    col[0] = vec[0]; col[1] = vec[1]; col[2] = vec[2];
    stfp.Emission[currentNodeIndex] = col;
    emit setSTFChanged();
}

void ScalarTransferFuncWidget::onAbsorptionChanged(const float* vec) {
    CrystalAlgrithm::Spectrum3 col;
    col[0] = vec[0]; col[1] = vec[1]; col[2] = vec[2];
    stfp.Absorption[currentNodeIndex] = col;
    emit setSTFChanged();
}

void ScalarTransferFuncWidget::onDiffuseChanged(const float* vec) {
    CrystalAlgrithm::Spectrum3 col;
    col[0] = vec[0]; col[1] = vec[1]; col[2] = vec[2];
    stfp.Diffuse[currentNodeIndex] = col;
    
    emit setSTFChanged();
}

void ScalarTransferFuncWidget::onSpecularChanged(const float* vec) {
    CrystalAlgrithm::Spectrum3 col;
    col[0] = vec[0]; col[1] = vec[1]; col[2] = vec[2];
    stfp.Specular[currentNodeIndex] = col;
    emit setSTFChanged();
}

// NodeGraphicsItem

STF_NodeGraphicsItem::STF_NodeGraphicsItem(QGraphicsEllipseItem* parent) : QGraphicsEllipseItem(parent) {
    setZValue(STF_Node_ZValue);

    pen_nofocus.setWidth(2);
    pen_nofocus.setColor(Qt::red);
    setPen(pen_nofocus);

    pen_focus.setWidth(2);
    pen_focus.setColor(QColor(255, 255, 0));
    //setPen(pen_focus);

    brushColor.setColor(QColor(0, 210, 217));
    setBrush(brushColor);

    setRect(-5, -5, 10, 10);

    setFlags(QGraphicsItem::ItemIsFocusable | QGraphicsItem::ItemIsSelectable
        | QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemSendsGeometryChanges);
    setAcceptHoverEvents(true);

    isCurrentNode = false;
}
STF_NodeGraphicsItem::~STF_NodeGraphicsItem() {

}

void STF_NodeGraphicsItem::mousePressEvent(QGraphicsSceneMouseEvent* pEvent) {
    QGraphicsItem::mousePressEvent(pEvent);
    if (pEvent->button() == Qt::LeftButton) {
        setFocus();
    }
    //setCursor(Qt::ClosedHandCursor);
}
void STF_NodeGraphicsItem::mouseReleaseEvent(QGraphicsSceneMouseEvent* pEvent) {
    QGraphicsItem::mouseReleaseEvent(pEvent);
    clearFocus();
    //setCursor(Qt::OpenHandCursor);
}
void STF_NodeGraphicsItem::hoverEnterEvent(QGraphicsSceneHoverEvent* pEvent) {
    setToolTip("Node");
}
void STF_NodeGraphicsItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
    if (hasFocus() || isCurrentNode) {
        painter->setPen(pen_focus);
    }
    else {
        painter->setPen(pen_nofocus);
    }
    painter->setBrush(QColor(0, 190, 27));
    painter->drawEllipse(-4, -4, 8, 8);
}
QVariant STF_NodeGraphicsItem::itemChange(GraphicsItemChange change, const QVariant& value) {
    if (change == ItemPositionChange && scene()){
        QPointF newPos = value.toPointF();

        QRectF rect(startWidth, startHeight, endWidth - startWidth, endHeight - startHeight);
        if (!rect.contains(newPos)) {
            newPos.setX(qMin(rect.right(), qMax(newPos.x(), rect.left())));
            newPos.setY(qMin(rect.bottom(), qMax(newPos.y(), rect.top())));
        }
        
        float currentNormalizedPosX = 
            (double)(newPos.x() - m_STF_NodeDisplayItem->nodeMargin.left2Boundary) / 
            (double)(m_STF_NodeDisplayItem->paintWidth);
        float currentPecentage = 
            (double)(m_STF_NodeDisplayItem->nodeMargin.top2Boundary + m_STF_NodeDisplayItem->paintHeight - newPos.y()) / 
            (double)(m_STF_NodeDisplayItem->paintHeight);
        
        m_STF_NodeDisplayItem->stfp_ref.setNodeProperty(
            m_STF_NodeDisplayItem->currentNodeIndex, 
            currentNormalizedPosX, 
            currentPecentage);

        m_STF_NodeSignals->onCurrentNodePosChanged();
        return newPos;
    }
    return QGraphicsItem::itemChange(change, value);
}

// STF_NodeSignals

STF_NodeSignals::STF_NodeSignals(QObject* parent) : QObject(parent) {

}

void STF_NodeSignals::onCurrentNodePropertyChanged() {
    emit setCurrentNodePropertyChanged();
}
void STF_NodeSignals::onCurrentNodePosChanged() {
    emit setCurrentNodePosChanged();
}

// STF_NodeDisplayItem

STF_NodeDisplayItem::STF_NodeDisplayItem(QGraphicsRectItem* parent, CrystalAlgrithm::STF_Preset& stfp)
    : QGraphicsRectItem(parent),
stfp_ref(stfp) {
    
    setZValue(STF_NodeDisplay_ZValue);

    currentNodeIndex = 0;
    setBrush(QBrush(QColor(100, 190, 210, 50)));
}

STF_NodeDisplayItem::~STF_NodeDisplayItem() {
    for (int i = 0; i < STF_NodeGraphicsList.size(); i++)
    {
        scene()->removeItem(STF_NodeGraphicsList[i]);
        delete STF_NodeGraphicsList[i];
    }
    STF_NodeGraphicsList.clear();

    for (int i = 0; i < STF_LigatureGraphicsList.size(); i++)
    {
        scene()->removeItem(STF_LigatureGraphicsList[i]);
        delete STF_LigatureGraphicsList[i];
    }
    STF_LigatureGraphicsList.clear();
}

void STF_NodeDisplayItem::setSize(int w, int h) {
    width = w;
    height = h;
    setRect(0, 0, width, height);
}

void STF_NodeDisplayItem::refresh() {
    setRect(0, 0, width, height);
}

void STF_NodeDisplayItem::setPaintAbleArea(int w, int h) {
    paintWidth = w; 
    paintHeight = h;
}

void STF_NodeDisplayItem::updateNodes() {
    for (int i = 0; i < STF_NodeGraphicsList.count(); i++) {

        scene()->removeItem(STF_NodeGraphicsList[i]);
        delete STF_NodeGraphicsList[i];
    }
    STF_NodeGraphicsList.clear();

    int i = 0;
    for (i = 0; i < stfp_ref.NormalizedIntensity.size(); i++) {
        STF_NodeGraphicsItem * item = new STF_NodeGraphicsItem();
        item->index = i;
        item->percentage = stfp_ref.Opacity[i];

        if (i == 0) {
            item->lastNormalizedPos = 0;
            item->currentNormalizedPos = 0;
            item->nextNormalizedPos = 0;
        }
        else if (i < stfp_ref.NormalizedIntensity.size() - 1) {
            item->lastNormalizedPos = STF_NodeGraphicsList[i - 1]->currentNormalizedPos;
            item->currentNormalizedPos = stfp_ref.NormalizedIntensity[i];
            item->nextNormalizedPos = stfp_ref.NormalizedIntensity[i + 1];
        }
        else {
            item->lastNormalizedPos = 1;
            item->currentNormalizedPos = 1;
            item->nextNormalizedPos = 1;
        } 

        {
            item->startWidth = nodeMargin.left2Boundary + item->lastNormalizedPos * paintWidth;
            item->startHeight = nodeMargin.top2Boundary;
            item->endWidth = nodeMargin.left2Boundary + item->nextNormalizedPos * paintWidth;
            item->endHeight = nodeMargin.top2Boundary + paintHeight;

            item->m_STF_NodeDisplayItem = this;
            item->m_STF_NodeSignals = m_STF_NodeSignals;
        }

        STF_NodeGraphicsList.append(item);
    }

    for (int i = 0; i < STF_NodeGraphicsList.size(); i++) {
        if (i == currentNodeIndex) 
            STF_NodeGraphicsList[i]->isCurrentNode = true;
        else 
            STF_NodeGraphicsList[i]->isCurrentNode = false;
        
        int w = nodeMargin.left2Boundary + STF_NodeGraphicsList[i]->currentNormalizedPos * paintWidth;
        int h = nodeMargin.top2Boundary + paintHeight * (1 - STF_NodeGraphicsList[i]->percentage);
        STF_NodeGraphicsList[i]->setPos(w, h);
        STF_NodeGraphicsList[i]->setZValue(STF_Node_ZValue);
        scene()->addItem(STF_NodeGraphicsList[i]);
    } 
}

void STF_NodeDisplayItem::updateLigatures() {
    for (int i = 0; i < STF_LigatureGraphicsList.count(); i++) {
        scene()->removeItem(STF_LigatureGraphicsList[i]);
        delete STF_LigatureGraphicsList[i];
    }
    STF_LigatureGraphicsList.clear();

    setBrush(QBrush(QColor(100, 190, 210, 50)));
    scene()->backgroundBrush();

    for (int i = 0; i < STF_NodeGraphicsList.size() - 1; i++) {
        int w1 = nodeMargin.left2Boundary + stfp_ref.NormalizedIntensity[i] * paintWidth;
        int h1 = nodeMargin.top2Boundary + paintHeight * (1 - stfp_ref.Opacity[i]);
        int w2 = nodeMargin.left2Boundary + stfp_ref.NormalizedIntensity[i + 1] * paintWidth;
        int h2 = nodeMargin.top2Boundary + paintHeight * (1 - stfp_ref.Opacity[i + 1]);
        STF_LigatureGraphicsItem * ligatureitem = new STF_LigatureGraphicsItem;
        ligatureitem->setLine(w1, h1, w2, h2);
        STF_LigatureGraphicsList.append(ligatureitem);
        STF_LigatureGraphicsList[i]->setZValue(STF_Ligature_ZValue);
        scene()->addItem(STF_LigatureGraphicsList[i]);
    }
}

void STF_NodeDisplayItem::updateRect() {
    setRect(0, 0, width, height);
}

// ScalarTransferFuncAxisGrid

ScalarTransferFuncAxisGrid::ScalarTransferFuncAxisGrid(QGraphicsRectItem* parent) {
    gridMargin.left2Boundary = 40;
    gridMargin.right2Boundary = 10;
    gridMargin.top2Boundary = 15;
    gridMargin.bottom2Boundary = 10;
    
    gridLineNum[0] = gridLineNum[1] = 10;
   
    //setFlag(QGraphicsItem::ItemHasNoContents, false);
    //setFlag(QGraphicsItem::ItemIsSelectable, false);
    //setFlag(QGraphicsItem::ItemIsMovable, false);
    setBrush(QBrush(QColor(30, 30, 70, 100)));
}

ScalarTransferFuncAxisGrid::~ScalarTransferFuncAxisGrid() {

}

void ScalarTransferFuncAxisGrid::setSize(int w, int h) {
    width = w; height = h;

    lineStartColumn = gridMargin.left2Boundary;
    lineSegmentColumn = (width - gridMargin.left2Boundary - gridMargin.right2Boundary) / gridLineNum[1];
    lineEndColumn = lineStartColumn + gridLineNum[1] * lineSegmentColumn;

    lineStartRow = gridMargin.top2Boundary;
    lineSegmentRow = (height - gridMargin.top2Boundary - gridMargin.bottom2Boundary) / gridLineNum[0];
    lineEndRow = lineStartRow + gridLineNum[0] * lineSegmentRow;


}

void ScalarTransferFuncAxisGrid::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
    painter->setPen(QPen(QColor(0, 25, 25, 100)));
    int i = 0;
    // Y axes
    for (i = 0; i <= gridLineNum[1]; i++) {
        painter->drawLine(lineStartColumn + i * lineSegmentColumn, lineStartRow,
                lineStartColumn + i * lineSegmentColumn, lineEndRow);
    }
    // X axes
    for (i = 0; i <= gridLineNum[0]; i++) {
        painter->drawLine(lineStartColumn-2, lineStartRow + i * lineSegmentRow, 
            lineEndColumn, lineStartRow + i * lineSegmentRow);
    }
    
    int percentValue = 0;
    for (int i = 0; i <= gridLineNum[0]; i++) {
        percentValue = 100 - 10 * i;
        painter->drawText(lineStartColumn - 13,
            lineStartRow + 5 + lineSegmentRow * i, QObject::tr("%"));
        painter->drawText(lineStartColumn - 19,
            lineStartRow + 5 + lineSegmentRow * i, QObject::tr("0"));
        if (percentValue != 0)
            painter->drawText(lineStartColumn - 25,
                lineStartRow + 5 + lineSegmentRow * i,
                QObject::tr((QString::number(percentValue % 100 / 10)).toStdString().c_str()));
        if (percentValue == 100)
            painter->drawText(lineStartColumn - 31,
                lineStartRow + 5 + lineSegmentRow * i,
                QObject::tr((QString::number(percentValue / 100)).toStdString().c_str()));

    }


}

void ScalarTransferFuncAxisGrid::refresh() {
    setRect(0, 0, width, height);
}

// ScalarTransferFuncColorBarGrid

ScalarTransferFuncColorBarGrid::ScalarTransferFuncColorBarGrid(QGraphicsRectItem* parent) {
    setBrush(QBrush(QColor(30, 30, 70, 100)));
}

ScalarTransferFuncColorBarGrid::~ScalarTransferFuncColorBarGrid() {

}

void ScalarTransferFuncColorBarGrid::setupColorBar(const CrystalAlgrithm::STF_Preset& stfp) {

    rectWidth = 200;

    // top
    rectHeight = 10;
    // each parameter in TF occupy 40 pixel in longitudinal axis
    rectHeight += stfp.parametersNum() * 40;
    // bottom
    rectHeight += 5;

    setRect(0, 0, rectWidth, rectHeight);


}

void ScalarTransferFuncColorBarGrid::setWidth(const int w) {
    rectWidth = w;

    setRect(0, 0, rectWidth, rectHeight);
}

void ScalarTransferFuncColorBarGrid::refresh() {
    setRect(0, 0, rectWidth, rectHeight);
}



}




