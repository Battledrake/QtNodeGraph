#pragma once

#include <QGraphicsPathItem>

class NodeEdge;

class NodeEdgeGraphic : public QGraphicsPathItem {

public:
    NodeEdgeGraphic(NodeEdge* nodeEdge, QGraphicsItem* parent=nullptr);

    void SetSourcePos(QPointF source) { m_srcPos = source; }
    void SetDestPos(QPointF dest) { m_destPos = dest; }

protected:
    virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* style, QWidget* widget) override;


private:
    void CalculateDirectPath();
    void CalculateBezierPath();

    NodeEdge* m_pEdge;
    QPointF m_srcPos;
    QPointF m_destPos;
};

