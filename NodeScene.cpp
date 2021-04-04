#include "NodeScene.h"

#include "NodeGraphicsScene.h"
#include "Node.h"
#include "NodeEdge.h"

Scene::Scene()
{
    m_sceneWidth = 1000;
    m_sceneHeight = 1000;

    InitUI();
}

void Scene::InitUI() {
    m_pGraphScene = new NodeGraphicsScene(this);
    m_pGraphScene->SetSceneSize(m_sceneWidth, m_sceneHeight);
}

void Scene::AddNode(Node* node) {
    m_nodes.append(node);
}

void Scene::AddEdge(NodeEdge* edge) {
    m_edges.append(edge);
}

void Scene::RemoveNode(Node* node) {
}

void Scene::RemoveEdge(NodeEdge* edge) {
    auto iterator = std::find(m_edges.begin(), m_edges.end(), edge);
    if(iterator != m_edges.end()) {
        m_edges.erase(iterator);
        delete edge;
    }
}
