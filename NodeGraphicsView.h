#pragma once

#include <QGraphicsView>

class NodeGraphicsScene;
class NodeSocket;
class NodeEdge;

enum class EGraphMode {
    Noop,
    EdgeDrag
};

class NodeGraphicsView : public QGraphicsView {
public:
    NodeGraphicsView(QGraphicsScene* graphScene, QWidget* parent=nullptr);

protected:
    virtual void mousePressEvent(QMouseEvent* mouseEvent) override;
    virtual void mouseMoveEvent(QMouseEvent* mouseEvent) override;
    virtual void mouseReleaseEvent(QMouseEvent* mouseEvent) override;

    virtual void middleMouseButtonPress(QMouseEvent* mouseEvent);
    virtual void leftMouseButtonPress(QMouseEvent* mouseEvent);
    virtual void rightMouseButtonPress(QMouseEvent* mouseEvent);
    virtual void middleMouseButtonRelease(QMouseEvent* mouseEvent);
    virtual void leftMouseButtonRelease(QMouseEvent* mouseEvent);
    virtual void rightMouseButtonRelease(QMouseEvent* mouseEvent);

    virtual void wheelEvent(QWheelEvent* wheelEvent) override;

private:
    void InitUI();
    void EdgeDragStart(NodeSocket* socket);
    void EdgeDragEnd();

    //Debugging Function
    QGraphicsItem* GetItemAtClick(QMouseEvent* event);

    NodeGraphicsScene* m_pGraphScene;
    EGraphMode m_currentMode;

    NodeEdge* m_pDragEdge;

    NodeSocket* m_pStartSocket;
    NodeSocket* m_pHoveredSocket;
    NodeSocket* m_pEndSocket;
};
