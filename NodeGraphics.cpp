#include "NodeGraphics.h"

#include "Node.h"
#include "NodeContentWidget.h"

#include <QGraphicsTextItem>
#include <QPainterPath>
#include <QPainter>
#include <QGraphicsProxyWidget>

NodeGraphics::NodeGraphics(Node* node, QGraphicsItem* parent)
    : QGraphicsItem(parent) {

    m_pNode = node;
    m_szTitle = node->GetNodeTitle();
    m_pNodeContent = m_pNode->GetContentWidget();

    m_titleColor = Qt::white;
    m_titleFont = QFont("Courier", 5);

    m_nodeWidth = 180.0f;
    m_nodeHeight = 240.0f;
    m_nodeEdgeSize = 10.0f;
    m_titleHeight = 24.0f;
    m_titlePadding = 25.0f;

    m_penDefault = QPen(QColor("#7F000000"));
    m_penSelected = QPen(QColor("#FFFFA637"));
    m_titleBrush = QBrush(QColor("#7Fdd1818"));
    m_bgBrush = QBrush(QColor("#E3212121"));

    //init title
    InitTitle();

    //init sockets
    InitSockets();

    //init content
    InitContent();

    InitUI();
}

QRectF NodeGraphics::boundingRect() const {
    return QRectF(0, 0, m_nodeWidth, m_nodeHeight);
}

void NodeGraphics::InitTitle() {
    m_pTitleItem = new QGraphicsTextItem();
    m_pTitleItem->setPlainText(m_szTitle);
    m_pTitleItem->setDefaultTextColor(m_titleColor);
    m_pTitleItem->setFont(m_titleFont);
    m_pTitleItem->setPos(m_titlePadding, 0);
    m_pTitleItem->setParentItem(this);
}

void NodeGraphics::InitSockets() {

}

void NodeGraphics::InitContent() {
    QGraphicsProxyWidget* pProxyWidget = new QGraphicsProxyWidget(this);
    m_pNodeContent->setGeometry(m_nodeEdgeSize, m_titleHeight + m_nodeEdgeSize,
                              m_nodeWidth - 2 * m_nodeEdgeSize,
                              m_nodeHeight - 2 * m_nodeEdgeSize - m_titleHeight);
    pProxyWidget->setWidget(m_pNodeContent);
}

void NodeGraphics::InitUI() {
    this->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);
}

void NodeGraphics::mouseMoveEvent(QGraphicsSceneMouseEvent* event) {
    QGraphicsItem::mouseMoveEvent(event);
    if(m_pNode) {
        m_pNode->UpdateConnectedEdges();
    }
}

void NodeGraphics::SetTitle(const char* title) {
    m_szTitle = title;
    m_pTitleItem->setPlainText(m_szTitle);
}

void NodeGraphics::paint(QPainter* painter, const QStyleOptionGraphicsItem* style, QWidget* widget) {
    //title
    QPainterPath pathTitle;
    pathTitle.setFillRule(Qt::WindingFill);
    pathTitle.addRoundedRect(0, 0, m_nodeWidth, m_titleHeight, m_nodeEdgeSize, m_nodeEdgeSize);
    pathTitle.addRect(0, m_titleHeight - m_nodeEdgeSize, m_nodeEdgeSize, m_nodeEdgeSize);
    pathTitle.addRect(m_nodeWidth - m_nodeEdgeSize, m_titleHeight - m_nodeEdgeSize,
                      m_nodeEdgeSize, m_nodeEdgeSize);
    painter->setPen(Qt::NoPen);
    painter->setBrush(m_titleBrush);
    painter->drawPath(pathTitle.simplified());

    //content
    QPainterPath pathContent;
    pathContent.setFillRule(Qt::WindingFill);
    pathContent.addRoundedRect(0, m_titleHeight, m_nodeWidth, m_nodeHeight - m_titleHeight,
                               m_nodeEdgeSize, m_nodeEdgeSize);
    pathContent.addRect(0, m_titleHeight, m_nodeEdgeSize, m_nodeEdgeSize);
    pathContent.addRect(m_nodeWidth - m_nodeEdgeSize, m_titleHeight, m_nodeEdgeSize, m_nodeEdgeSize);
    painter->setPen(Qt::NoPen);
    painter->setBrush(m_bgBrush);
    painter->drawPath(pathContent.simplified());


    //outline
    QPainterPath pPathOutline;
    pPathOutline.addRoundedRect(0, 0, m_nodeWidth, m_nodeHeight, m_nodeEdgeSize, m_nodeEdgeSize);
    if(!this->isSelected()) {
        painter->setPen(m_penDefault);
    } else if(this->isSelected()) {
        painter->setPen(m_penSelected);
    }
    painter->setBrush(Qt::NoBrush);
    painter->drawPath(pPathOutline.simplified());
}
