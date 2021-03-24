#pragma once

#include <QGraphicsItem>
#include <QPen>
#include <QBrush>

class NodeSocket;

class NodeSocketGraphic : public QGraphicsItem
{
public:
    NodeSocketGraphic(NodeSocket* socket, QGraphicsItem* parent=nullptr);

    inline NodeSocket* GetSocket() { return m_pSocket; }

    void NodeEntered();
    void NodeExited();

protected:
    virtual void hoverEnterEvent(QGraphicsSceneHoverEvent* event) override;
    virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent* event) override;
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;

    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* style, QWidget* widget=nullptr) override;

    QBrush m_brush;
private:
    NodeSocket* m_pSocket;

    float m_radius;
    float m_outlineWidth;
    QColor m_hoverColor;
    QColor m_bgColor;
    QColor m_outlineColor;
    QColor m_selOutlineColor;
    QPen m_pen;
};

class SocketVariation : public NodeSocketGraphic {
public:
    SocketVariation(NodeSocket* socket, QGraphicsItem* parent) : NodeSocketGraphic(socket, parent) {
        m_brush = QBrush(Qt::green);
    }
};

