#pragma once

#include <QGraphicsItem>
#include <QFont>
#include <QPen>

class Node;
class NodeContentWidget;

class NodeGraphics : public QGraphicsItem
{
public:
    NodeGraphics(Node* node, QGraphicsItem* parent=nullptr);

    inline const char* GetNodeTitle() { return m_szTitle; }
    inline float GetTitleHeight() { return m_titleHeight; }
    inline float GetTitlePadding() { return m_titlePadding; }
    inline float GetNodeEdgeSize() { return m_nodeEdgeSize; }
    inline float GetNodeWidth() { return m_nodeWidth; }
    inline float GetNodeHeight() { return m_nodeHeight; }
    void SetTitle(const char* title);

protected:
    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* style, QWidget* widget=nullptr) override;

private:
    void InitTitle();
    void InitSockets();
    void InitContent();
    void InitUI();

    Node* m_pNode;
    const char* m_szTitle;
    NodeContentWidget* m_pNodeContent;

    float m_nodeWidth;
    float m_nodeHeight;
    float m_nodeEdgeSize;
    float m_titleHeight;
    float m_titlePadding;
    QPen m_penDefault;
    QPen m_penSelected;
    QBrush m_titleBrush;
    QBrush m_bgBrush;

    QColor m_titleColor;
    QFont m_titleFont;

    QGraphicsTextItem* m_pTitleItem;
};

