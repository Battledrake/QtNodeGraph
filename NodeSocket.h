#pragma once

#include <QPointF>

class NodeSocketGraphic;
class Node;
class NodeEdge;

enum class ESocketRegion {
    LeftTop,
    LeftBottom,
    RightTop,
    RightBottom
};

class NodeSocket
{

public:
    NodeSocket(Node* scene, int index, ESocketRegion position=ESocketRegion::LeftTop);

    inline NodeSocketGraphic* GetSocketGraphic() { return m_pSocketGraphic; }
    inline NodeEdge* GetEdge() { return m_pEdge; }
    void SetEdge(NodeEdge* edge) { m_pEdge = edge; }
    inline Node* GetNode() { return m_pNode; }

    void SetConnectedEdge(NodeEdge* edge);
    void DeleteEdge();

private:
    NodeSocketGraphic* m_pSocketGraphic;
    NodeEdge* m_pEdge;

    Node* m_pNode;
    int m_index;
    ESocketRegion m_socketRegion;
};

