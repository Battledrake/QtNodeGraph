#pragma once

#include "NodeSocket.h"

#include <QVector>

class Scene;
class NodeGraphics;
class NodeContentWidget;
class NodeSocket;
enum class ESocketRegion;

class Node {

public:
    Node(Scene* scene, const char* title="Undefined Node", int nodeIndex=-1);

    void SetPosition(int x, int y);

    void AddInputSocket(NodeSocket* input);
    void AddOutputSocket(NodeSocket* output);

    void UpdateConnectedEdges();

    inline const char* GetNodeTitle() { return m_szTitle; }
    inline NodeGraphics* GetNodeGraphics() { return m_pGraphicsNode; }
    inline NodeContentWidget* GetContentWidget() { return m_pNodeContent; }
    inline QVector<NodeSocket*> GetInputSockets() { return m_inputSockets; }
    inline QVector<NodeSocket*> GetOutputSockets() { return m_outputSockets; }
    inline int GetNodeIndex() { return m_nodeIndex; }

    QPointF GetSocketLocalPos(int index, ESocketRegion region);

private:
    int m_nodeIndex;

    Scene* m_pScene;
    const char* m_szTitle;
    NodeGraphics* m_pGraphicsNode;
    NodeContentWidget* m_pNodeContent;

    float m_socketSpacing;

    QVector<NodeSocket*> m_inputSockets;
    QVector<NodeSocket*> m_outputSockets;
};

