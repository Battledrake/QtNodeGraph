#include "NodeGraphicsView.h"

#include "NodeSocketGraphic.h"
#include "NodeSocket.h"
#include "Node.h"
#include "NodeGraphicsScene.h"
#include "NodeScene.h"
#include "NodeEdge.h"
#include "NodeEdgeGraphic.h"
#include "NodeGraphics.h"

#include <QGraphicsRectItem>
#include <QPushButton>
#include <QTextEdit>
#include <QGraphicsProxyWidget>
#include <QPainter>

#define DEBUG

NodeGraphicsView::NodeGraphicsView(QGraphicsScene* graphScene, QWidget* parent)
    : QGraphicsView(graphScene, parent) {

    m_pGraphScene = static_cast<NodeGraphicsScene*>(graphScene);
    m_currentMode = EGraphMode::Noop;

    m_pStartSocket = nullptr;
    m_pHoveredSocket = nullptr;
    m_pEndSocket = nullptr;

    InitUI();
}

void NodeGraphicsView::InitUI() {
    this->setRenderHints(QPainter::Antialiasing | QPainter::HighQualityAntialiasing
                         | QPainter::TextAntialiasing | QPainter::SmoothPixmapTransform);

    this->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);

    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    this->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    this->setCacheMode(QGraphicsView::CacheBackground);

    this->setDragMode(QGraphicsView::RubberBandDrag);

    this->centerOn(QPointF(0.0f, 0.0f));
}

void NodeGraphicsView::EdgeDragStart(NodeSocket* socket) {
    m_pDragEdge = new NodeEdge(m_pGraphScene->GetScene(), socket, nullptr);
}

void NodeGraphicsView::EdgeDragEnd() {
    if(m_pHoveredSocket) {
        if(m_pDragEdge) {
            m_pDragEdge->SetEndSocket(m_pHoveredSocket);
        }
    } else {
        m_pGraphScene->GetScene()->RemoveEdge(m_pDragEdge);
        m_pDragEdge = nullptr;
    }
}

void NodeGraphicsView::mousePressEvent(QMouseEvent* mouseEvent) {
    switch(mouseEvent->button()) {
    case Qt::MiddleButton:
        middleMouseButtonPress(mouseEvent);
        break;
    case Qt::LeftButton:
        leftMouseButtonPress(mouseEvent);
        break;
    case Qt::RightButton:
        rightMouseButtonPress(mouseEvent);
        break;
    default:
        QGraphicsView::mousePressEvent(mouseEvent);
        break;
    }
}

void NodeGraphicsView::mouseMoveEvent(QMouseEvent* mouseEvent) {
    if(m_currentMode == EGraphMode::EdgeDrag) {
        QPointF pos = this->mapToScene(mouseEvent->pos());
        m_pDragEdge->GetEdgeGraphic()->SetDestPos(pos);
        m_pDragEdge->GetEdgeGraphic()->update();
    }

    for(Node* pNode : m_pGraphScene->GetScene()->GetNodes()) {
        if(pNode->GetNodeGraphics()->isSelected()) {
            pNode->UpdateConnectedEdges();
        }
    }

    QList<QGraphicsItem*> items = this->items(mouseEvent->pos());
    for(auto& item : items) {
        if(NodeSocketGraphic* pGraphic = dynamic_cast<NodeSocketGraphic*>(item)) {
            if(NodeSocket* pSocket = pGraphic->GetSocket()) {
                if(m_pStartSocket != pSocket) {
                    if(m_pHoveredSocket)
                        m_pHoveredSocket->GetSocketGraphic()->NodeExited();

                    m_pHoveredSocket = pSocket;
                    pSocket->GetSocketGraphic()->NodeEntered();
                }
            }
        }
    }
    if(items.isEmpty()) {
        if(m_pHoveredSocket) {
            m_pHoveredSocket->GetSocketGraphic()->NodeExited();
            m_pHoveredSocket = nullptr;
        }
    }
    QGraphicsView::mouseMoveEvent(mouseEvent);
}

void NodeGraphicsView::mouseReleaseEvent(QMouseEvent* mouseEvent) {
    switch(mouseEvent->button()){
    case Qt::MiddleButton:
        middleMouseButtonRelease(mouseEvent);
        break;
    case Qt::LeftButton:
        leftMouseButtonRelease(mouseEvent);
        break;
    case Qt::RightButton:
        rightMouseButtonRelease(mouseEvent);
        break;
    default:
        QGraphicsView::mouseReleaseEvent(mouseEvent);
        break;
    }
}

void NodeGraphicsView::middleMouseButtonPress(QMouseEvent* mouseEvent) {
    QMouseEvent* releaseEvent = new QMouseEvent(QEvent::MouseButtonRelease, mouseEvent->localPos(),
                                                mouseEvent->screenPos(), Qt::MiddleButton,
                                                mouseEvent->buttons(), mouseEvent->modifiers());
    QGraphicsView::mouseReleaseEvent(releaseEvent);

    this->setDragMode(QGraphicsView::ScrollHandDrag);

    QMouseEvent* fakeEvent = new QMouseEvent(mouseEvent->type(), mouseEvent->localPos(),
                                             mouseEvent->screenPos(), Qt::LeftButton,
                                             mouseEvent->buttons(), mouseEvent->modifiers());
    QGraphicsView::mousePressEvent(fakeEvent);
}

void NodeGraphicsView::leftMouseButtonPress(QMouseEvent* mouseEvent) {
    if(mouseEvent->modifiers() & Qt::ShiftModifier) {
        mouseEvent->ignore();
        QMouseEvent* fakeEvent = new QMouseEvent(mouseEvent->type(), mouseEvent->localPos(), mouseEvent->screenPos(),
                                                 Qt::LeftButton, mouseEvent->buttons() | Qt::LeftButton,
                                                 mouseEvent->modifiers() | Qt::ControlModifier);
        QGraphicsView::mousePressEvent(fakeEvent);
        return;
    }

    if(NodeSocketGraphic* pGraphic = dynamic_cast<NodeSocketGraphic*>(GetItemAtClick(mouseEvent))) {
        if(NodeSocket* pSocket = pGraphic->GetSocket()) {
            if(m_currentMode == EGraphMode::Noop) {
                m_currentMode = EGraphMode::EdgeDrag;
#ifdef DEBUG
                qDebug("Start Dragging Edge");
#endif
                m_pStartSocket = pSocket;
                EdgeDragStart(pSocket);
                return;
            }
        }
    }
    QGraphicsView::mousePressEvent(mouseEvent);
}

void NodeGraphicsView::rightMouseButtonPress(QMouseEvent* mouseEvent) {
    QGraphicsView::mousePressEvent(mouseEvent);

#ifdef DEBUG
    if(QGraphicsItem* item = this->GetItemAtClick(mouseEvent)) {
        if(NodeSocketGraphic* pSocketGraphic = dynamic_cast<NodeSocketGraphic*>(item)) {
            if(NodeSocket* pSocket = pSocketGraphic->GetSocket()) {
                qDebug("RMB DEBUG: Socket: %p has Edge: %p", pSocket, pSocket->GetEdge());
                return;
            }
        }
        if(NodeEdgeGraphic* pEdgeGraphic = dynamic_cast<NodeEdgeGraphic*>(item)) {
            if(NodeEdge* pEdge = pEdgeGraphic->GetEdge()) {
                qDebug("RMB DEBUG: Edge: %p connecting Sockets: %p <--> %p", pEdge,
                       pEdge->GetStartSocket(), pEdge->GetEndSocket());
            }
        }
    } else {
        qDebug("SCENE:");
        qDebug(" Nodes:");
        for(auto& node : m_pGraphScene->GetScene()->GetNodes()) {
            qDebug("Node: %p", node);
        }
        qDebug(" Edges:");
        for(auto& edge : m_pGraphScene->GetScene()->GetEdges()) {
            qDebug("Edge: %p", edge);
        }
    }
#endif
}

void NodeGraphicsView::middleMouseButtonRelease(QMouseEvent* mouseEvent) {

    QMouseEvent* fakeRelease = new QMouseEvent(mouseEvent->type(), mouseEvent->localPos(),
                                               mouseEvent->screenPos(), Qt::LeftButton,
                                               mouseEvent->buttons(), mouseEvent->modifiers());
    QGraphicsView::mouseReleaseEvent(fakeRelease);
    this->setDragMode(QGraphicsView::RubberBandDrag);
}

void NodeGraphicsView::leftMouseButtonRelease(QMouseEvent* mouseEvent) {

    if(mouseEvent->modifiers() & Qt::ShiftModifier) {
        mouseEvent->ignore();
        QMouseEvent* fakeEvent = new QMouseEvent(mouseEvent->type(), mouseEvent->localPos(), mouseEvent->screenPos(),
                                                 Qt::LeftButton, Qt::NoButton,
                                                 mouseEvent->modifiers() | Qt::ControlModifier);
        QGraphicsView::mouseReleaseEvent(fakeEvent);
        return;
    }

    if(m_currentMode == EGraphMode::EdgeDrag) {
#ifdef DEBUG
        qDebug("End Dragging");
#endif
        EdgeDragEnd();
        if(NodeSocketGraphic* pGraphic = dynamic_cast<NodeSocketGraphic*>(GetItemAtClick(mouseEvent))) {
            if(NodeSocket* pSocket = pGraphic->GetSocket()) {
                qDebug(pSocket->GetNode()->GetNodeTitle());
                m_pEndSocket = pSocket;
            }
        }
        m_currentMode = EGraphMode::Noop;
        if(m_pStartSocket) {
            m_pStartSocket->GetSocketGraphic()->NodeExited();
            m_pStartSocket = nullptr;
        }
        if(m_pHoveredSocket) {
            m_pHoveredSocket->GetSocketGraphic()->NodeExited();
            m_pHoveredSocket = nullptr;
        }
        return;
    }
    QGraphicsView::mouseReleaseEvent(mouseEvent);
}

void NodeGraphicsView::rightMouseButtonRelease(QMouseEvent* mouseEvent) {
    QGraphicsView::mouseReleaseEvent(mouseEvent);
}

QGraphicsItem* NodeGraphicsView::GetItemAtClick(QMouseEvent* event) {
    QPoint pos = event->pos();
    QGraphicsItem* item = this->itemAt(pos);
    return item;
}

void NodeGraphicsView::wheelEvent(QWheelEvent* wheelEvent) {

    QPoint delta = wheelEvent->angleDelta();

    if(delta.y() == 0.0f) {
        wheelEvent->ignore();
        return;
    }

    float const step = 1.2f;
    float zoomFactor;
    QTransform currentTransform = transform();

    if(delta.y() > 0.0f) {
        if(currentTransform.m11() > 2.0f)
            return;
        zoomFactor = std::pow(step, 1.0);
    } else {
        if(currentTransform.m11() < 0.5f)
            return;
        zoomFactor = std::pow(step, -1.0);
    }

    scale(zoomFactor, zoomFactor);
}
