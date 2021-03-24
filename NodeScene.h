#pragma once

#include <QList>

class NodeGraphicsScene;
class Node;
class NodeEdge;

class Scene
{
public:
    Scene();

    inline NodeGraphicsScene* GetGraphicScene() { return m_pGraphScene; }

    void AddNode(Node node);
    void AddEdge(NodeEdge edge);
    void RemoveNode(Node node);
    void RemoveEdge(NodeEdge edge);

private:
    void InitUI();

    int m_sceneWidth;
    int m_sceneHeight;

    NodeGraphicsScene* m_pGraphScene;

    //first int = edges/node
    //second int = id
    QList<Node> m_nodes;
    QList<NodeEdge> m_edges;
};

