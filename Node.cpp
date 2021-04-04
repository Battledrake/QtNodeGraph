#include "Node.h"

#include "NodeScene.h"
#include "NodeGraphics.h"
#include "NodeGraphicsScene.h"
#include "NodeContentWidget.h"
#include "NodeSocketGraphic.h"
#include "NodeEdge.h"

Node::Node(Scene* scene, const char* title, int nodeIndex) {
    m_nodeIndex = nodeIndex;
    m_pScene = scene;
    m_szTitle = title;

    m_pNodeContent = new NodeContentWidget();
    m_pGraphicsNode = new NodeGraphics(this);

    m_socketSpacing = 25.0f;

    //added after m_pGraphicsNode since socket refers to it for it's graphical implementation
    NodeSocket* pInSocket1 = new NodeSocket(this, 0, ESocketRegion::LeftTop);
    NodeSocket* pInSocket2 = new NodeSocket(this, 1, ESocketRegion::LeftTop);
    NodeSocket* pOutSocket1 = new NodeSocket(this, 0, ESocketRegion::RightTop);
    AddInputSocket(pInSocket1);
    AddInputSocket(pInSocket2);
    AddOutputSocket(pOutSocket1);

    if(NodeGraphicsScene* pGraphicsScene = m_pScene->GetGraphicScene()) {
        pGraphicsScene->addItem(m_pGraphicsNode);
    }

    m_pScene->AddNode(this);
}

void Node::SetPosition(int x, int y) {
    m_pGraphicsNode->setPos(x, y);
}

void Node::AddInputSocket(NodeSocket* input) {
    m_inputSockets.append(input);
}

void Node::AddOutputSocket(NodeSocket* output) {
    m_outputSockets.append(output);
}

void Node::UpdateConnectedEdges() {
    QVector<NodeSocket*> allSockets = m_inputSockets + m_outputSockets;
    for(auto& socket : allSockets) {
        if(NodeEdge* edge = socket->GetEdge()) {
            edge->UpdatePositions();
        }
    }
}

QPointF Node::GetSocketLocalPos(int index, ESocketRegion position) {
    float x;
    float y;
    x = (position == ESocketRegion::LeftTop || position == ESocketRegion::LeftBottom) ? 0 : m_pGraphicsNode->GetNodeWidth();
    if(position == ESocketRegion::LeftBottom || position == ESocketRegion::RightBottom) {
        y = m_pGraphicsNode->GetNodeHeight() - m_pGraphicsNode->GetTitleHeight() - index * m_socketSpacing;
    } else {
        y = m_pGraphicsNode->GetTitleHeight() + m_pGraphicsNode->GetNodeEdgeSize() + index * m_socketSpacing;
    }
    return QPointF(x, y);
}
