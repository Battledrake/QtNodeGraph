#include "NodeSocket.h"

#include "NodeSocketGraphic.h"
#include "Node.h"
#include "NodeEdge.h"

NodeSocket::NodeSocket(Node* node, int index, ESocketRegion region)
{
    m_pNode = node;
    m_pEdge = NULL;
    m_index = index;
    m_socketRegion = region;
    m_pSocketGraphic = new NodeSocketGraphic(this, (QGraphicsItem*)m_pNode->GetNodeGraphics());

    m_pSocketGraphic->setPos(m_pNode->GetSocketLocalPos(m_index, m_socketRegion));
}

void NodeSocket::DeleteEdge() {
    delete m_pEdge;
    m_pEdge = NULL;
}
