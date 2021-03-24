#include "NodeSocketGraphic.h"

#include "NodeSocket.h"
#include "Node.h"

#include <QPainter>

NodeSocketGraphic::NodeSocketGraphic(NodeSocket* socket, QGraphicsItem* parent)
    : QGraphicsItem(parent) {
    m_pSocket = socket;

    m_radius = 6.0f;
    m_outlineWidth = 1.0f;
    m_bgColor = QColor("#FFFF7700");
    m_hoverColor = QColor(Qt::green);
    m_outlineColor = QColor("#FF000000");
    m_selOutlineColor = QColor(Qt::green);

    m_pen = QPen(m_outlineColor);
    m_pen.setWidthF(m_outlineWidth);
    m_brush = QBrush(m_bgColor);

    this->setAcceptHoverEvents(true);
}

void NodeSocketGraphic::NodeEntered() {
    m_pen.setColor(m_selOutlineColor);
    this->update();
}

void NodeSocketGraphic::NodeExited() {
    m_pen.setColor(m_outlineColor);
    this->update();
}

void NodeSocketGraphic::hoverEnterEvent(QGraphicsSceneHoverEvent* event) {
    NodeEntered();
}

void NodeSocketGraphic::hoverLeaveEvent(QGraphicsSceneHoverEvent* event) {
    NodeExited();
}

void NodeSocketGraphic::mouseMoveEvent(QGraphicsSceneMouseEvent* event) {
    qDebug("I felt a tickle");
}

QRectF NodeSocketGraphic::boundingRect() const {
    return QRectF(-m_radius - m_outlineWidth, 0, 2 * m_radius + m_outlineWidth, 2 * m_radius + m_outlineWidth);
}

void NodeSocketGraphic::paint(QPainter* painter, const QStyleOptionGraphicsItem* style, QWidget* widget) {
    //paint circle
    painter->setBrush(m_brush);
    painter->setPen(m_pen);
    painter->drawEllipse(-m_radius, 0, 2 * m_radius, 2 * m_radius);
}

