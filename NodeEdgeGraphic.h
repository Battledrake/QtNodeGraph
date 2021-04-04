#pragma once

#include <QGraphicsPathItem>
#include <QPen>

class NodeEdge;

class NodeEdgeGraphic : public QGraphicsPathItem {

public:
    NodeEdgeGraphic(NodeEdge* nodeEdge, QGraphicsItem* parent=nullptr);

    inline NodeEdge* GetEdge() { return m_pEdge; }

    void SetSourcePos(QPointF source) { m_srcPos = source; }
    void SetDestPos(QPointF dest) { m_destPos = dest; }

protected:
    virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* style, QWidget* widget) override;


private:
    void CalculateDirectPath();
    void CalculateBezierPath();

    QPen defaultPen;
    QPen selectedPen;
    QPen draggingPen;

    NodeEdge* m_pEdge;
    QPointF m_srcPos;
    QPointF m_destPos;
};

