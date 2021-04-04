#include "NodeEdge.h"

#include "NodeScene.h"
#include "NodeSocket.h"
#include "NodeEdgeGraphic.h"
#include "NodeGraphicsScene.h"
#include "NodeSocketGraphic.h"
#include "Node.h"
#include "NodeGraphics.h"

NodeEdge::NodeEdge(Scene* scene, NodeSocket* startSocket, NodeSocket* endSocket)
{
    m_pScene = scene;

    m_pStartSocket = startSocket;
    m_pStartSocket->SetEdge(this);

    m_pEndSocket = endSocket;
    if(m_pEndSocket)
        m_pEndSocket->SetEdge(this);

    m_pEdgeGraphics = new NodeEdgeGraphic(this);

    UpdatePositions();
    m_pScene->GetGraphicScene()->addItem(m_pEdgeGraphics);
    m_pScene->AddEdge(this);
}

void NodeEdge::UpdatePositions() {
    m_pEdgeGraphics->SetSourcePos(m_pStartSocket->GetSocketGraphic()->scenePos());

    if(m_pEndSocket) {
        m_pEdgeGraphics->SetDestPos(m_pEndSocket->GetSocketGraphic()->scenePos());
    } else {
        m_pEdgeGraphics->SetDestPos(m_pStartSocket->GetSocketGraphic()->scenePos());
    }
    m_pEdgeGraphics->update();
}

void NodeEdge::SetEndSocket(NodeSocket *socket) {
    socket->SetEdge(this);
    m_pEndSocket = socket;
}

void NodeEdge::RemoveFromSockets() {
    if(m_pStartSocket) {
        m_pStartSocket->DeleteEdge();
    }
    if(m_pEndSocket) {
        m_pEndSocket->DeleteEdge();
    }
}

NodeEdge::~NodeEdge() {
    RemoveFromSockets();

    m_pScene->GetGraphicScene()->removeItem(m_pEdgeGraphics);
}
