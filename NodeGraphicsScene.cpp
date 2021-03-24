#include "NodeGraphicsScene.h"

#include <QPainter>

NodeGraphicsScene::NodeGraphicsScene(Scene* scene, QObject* parent)
    : QGraphicsScene(parent) {

    m_pScene = scene;

    m_bgColor = QColor("#393939");
    m_lightColor = QColor("#2f2f2f");
    m_darkColor = QColor("#292929");

    m_penLight = QPen(m_lightColor);
    m_penLight.setWidth(1);
    m_penDark = QPen(m_darkColor);
    m_penDark.setWidth(2);

    m_gridSize = 20;
    m_gridSquare = 5;

    this->setBackgroundBrush(m_bgColor);
}

void NodeGraphicsScene::SetSceneSize(float width, float height) {
    this->setSceneRect(-250, -250, width, height);
}

void NodeGraphicsScene::drawBackground(QPainter* painter, const QRectF& rect){
    QGraphicsScene::drawBackground(painter, rect);

    QVector<QLine> lightLines;
    QVector<QLine> darkLines;

    //Create Grid
    int left = floor(rect.left());
    int right = ceil(rect.right());
    int top = floor(rect.top());
    int bottom = ceil(rect.bottom());

    int first_left = left - (left % m_gridSize);
    int first_top = top - (top % m_gridSize);

    //Calculate grid lines
    for(int x = first_left; x < right; x += m_gridSize) {
        if(x % (m_gridSize * m_gridSquare) != 0) {
            lightLines.push_back(QLine(x, top, x, bottom));
        } else {
            darkLines.push_back(QLine(x, top, x, bottom));
        }
    }
    for(int y = first_top; y < bottom; y += m_gridSize) {
        if(y % (m_gridSize * m_gridSquare) != 0) {
            lightLines.push_back(QLine(left, y, right, y));
        } else {
            darkLines.push_back(QLine(left, y, right, y));
        }

    }

    //draw lines
    painter->setPen(m_penLight);
    painter->drawLines(lightLines);

    painter->setPen(m_penDark);
    painter->drawLines(darkLines);

}
