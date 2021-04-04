#include "NodeEdgeGraphic.h"
#include "NodeEdge.h"
#include "NodeSocket.h"
#include "NodeSocketGraphic.h"

#include <QPainter>

NodeEdgeGraphic::NodeEdgeGraphic(NodeEdge* nodeEdge, QGraphicsItem* parent)
    : QGraphicsPathItem(parent) {

    defaultPen = QPen("001000");
    selectedPen = QPen(Qt::green);
    draggingPen = QPen("001000");

    defaultPen.setWidth(2.0f);
    selectedPen.setWidth(2.0f);
    draggingPen.setWidth(2.0f);

    draggingPen.setStyle(Qt::DashLine);

    m_pEdge = nodeEdge;

    m_srcPos = nodeEdge->GetStartSocket()->GetSocketGraphic()->scenePos();

    if(nodeEdge->GetEndSocket())
        m_destPos = nodeEdge->GetEndSocket()->GetSocketGraphic()->scenePos();

    this->setFlags(QGraphicsItem::ItemIsSelectable);
    this->setZValue(-1.0f);

}

void NodeEdgeGraphic::paint(QPainter* painter, const QStyleOptionGraphicsItem* style, QWidget* widget) {
    //    CalculateDirectPath();
    CalculateBezierPath();

    if(!m_pEdge->GetEndSocket()) {
        painter->setPen(draggingPen);
    } else {
        if(this->isSelected()) {
            painter->setPen(selectedPen);
        } else {
            painter->setPen(defaultPen);
        }
    }

    painter->setBrush(Qt::NoBrush);
    painter->drawPath(this->path());
}

void NodeEdgeGraphic::CalculateDirectPath() {
    QPainterPath path(m_srcPos);
    path.lineTo(m_destPos);
    this->setPath(path);
}

void NodeEdgeGraphic::CalculateBezierPath() {
    float dist = (m_destPos.x() - m_srcPos.x()) / 2;
    //Was this supposed to fix backwards lines? It only breaks them. Lines appear to work perfect without this.
    //    if(m_srcPos.x() > m_destPos.x()) {
    //        dist *= -1;
    //    }
    QPainterPath path(m_srcPos);
    path.cubicTo(QPointF(m_srcPos.x() + dist, m_srcPos.y()), QPointF(m_destPos.x() - dist, m_destPos.y()), m_destPos);
    this->setPath(path);
}
