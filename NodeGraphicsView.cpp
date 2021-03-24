#include "NodeGraphicsView.h"

#include "NodeSocketGraphic.h"
#include "NodeSocket.h"
#include "Node.h"

#include <QGraphicsRectItem>
#include <QPushButton>
#include <QTextEdit>
#include <QGraphicsProxyWidget>
#include <QPainter>

NodeGraphicsView::NodeGraphicsView(QGraphicsScene* graphScene, QWidget* parent)
    : QGraphicsView(graphScene, parent) {

    m_pGraphScene = graphScene;
    m_currentMode = EGraphMode::Noop;

    m_pStartSocket = NULL;
    m_pHoveredSocket = NULL;
    m_pEndSocket = NULL;

    InitUI();

    zoomInFactor = 1.25f;
    zoom = 10.0f;
    zoomStep = 1.0f;
    zoomMin = 0.0f;
    zoomMax = 10.0f;
}

void NodeGraphicsView::InitUI() {
    this->setRenderHints(QPainter::Antialiasing | QPainter::HighQualityAntialiasing
                         | QPainter::TextAntialiasing | QPainter::SmoothPixmapTransform);

    this->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);

    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    this->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);

    this->centerOn(QPointF(0.0f, 0.0f));
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
    QGraphicsView::mouseMoveEvent(mouseEvent);

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
            m_pHoveredSocket = NULL;
        }
    }
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
    if(NodeSocketGraphic* pGraphic = dynamic_cast<NodeSocketGraphic*>(GetItemAtClick(mouseEvent))) {
        if(NodeSocket* pSocket = pGraphic->GetSocket()) {
            //        qDebug(pSocketGraphic->GetSocket()->GetNode()->GetNodeTitle());
            if(m_currentMode == EGraphMode::Noop) {
                m_currentMode = EGraphMode::EdgeDrag;
                qDebug("Start Dragging Edge");
                //TODO: assign Start Socket
                m_pStartSocket = pSocket;
                return;
            }
        }
    }
    QGraphicsView::mousePressEvent(mouseEvent);
}

void NodeGraphicsView::rightMouseButtonPress(QMouseEvent* mouseEvent) {
    QGraphicsView::mousePressEvent(mouseEvent);
}

void NodeGraphicsView::middleMouseButtonRelease(QMouseEvent* mouseEvent) {
    QMouseEvent* fakeRelease = new QMouseEvent(mouseEvent->type(), mouseEvent->localPos(),
                                               mouseEvent->screenPos(), Qt::LeftButton,
                                               mouseEvent->buttons(), mouseEvent->modifiers());
    QGraphicsView::mouseReleaseEvent(fakeRelease);
    this->setDragMode(QGraphicsView::NoDrag);
}

void NodeGraphicsView::leftMouseButtonRelease(QMouseEvent* mouseEvent) {
    if(m_currentMode == EGraphMode::EdgeDrag) {
        qDebug("End Dragging");
        if(NodeSocketGraphic* pGraphic = dynamic_cast<NodeSocketGraphic*>(GetItemAtClick(mouseEvent))) {
            if(NodeSocket* pSocket = pGraphic->GetSocket()) {
                qDebug(pSocket->GetNode()->GetNodeTitle());
                m_pEndSocket = pSocket;
            }
        }
        m_currentMode = EGraphMode::Noop;
        if(m_pStartSocket) {
            m_pStartSocket->GetSocketGraphic()->NodeExited();
            m_pStartSocket = NULL;
        }
        if(m_pHoveredSocket) {
            m_pHoveredSocket->GetSocketGraphic()->NodeExited();
            m_pHoveredSocket = NULL;
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
    //TODO: Something is wrong with the zoom. It causes lots of lag!

    //Calculate zoom factor
    float zoomOutFactor = 1 / zoomInFactor;

    //calculate zoom
    if(wheelEvent->angleDelta().y() > 0.0f) {
        zoomFactor = zoomInFactor;
        zoom += zoomStep;
    } else {
        zoomFactor = zoomOutFactor;
        zoom -= zoomStep;
    }

    //set screen scale
    scale(zoomFactor, zoomFactor);
}
