#pragma once

class Scene;
class NodeSocket;
class NodeEdgeGraphic;

class NodeEdge
{
public:
    NodeEdge(Scene* scene, NodeSocket* start, NodeSocket* end);
    ~NodeEdge();

    inline NodeSocket* GetStartSocket() { return m_pStartSocket; }
    inline NodeSocket* GetEndSocket() { return m_pEndSocket; }
    inline NodeEdgeGraphic* GetEdgeGraphic() { return m_pEdgeGraphics; }

    void SetEndSocket(NodeSocket* socket);

    void UpdatePositions();
    void RemoveFromSockets();

private:
    Scene* m_pScene;
    NodeSocket* m_pStartSocket;
    NodeSocket* m_pEndSocket;

    NodeEdgeGraphic* m_pEdgeGraphics;
};

