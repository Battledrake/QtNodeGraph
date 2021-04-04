#pragma once

#include <QGraphicsScene>

class Scene;

class NodeGraphicsScene : public QGraphicsScene {
public:
    NodeGraphicsScene(Scene* scene, QObject* parent = nullptr);

    inline Scene* GetScene() { return m_pScene; }
    void SetSceneSize(float width, float height);

protected:
    virtual void drawBackground(QPainter* painter, const QRectF& rect) override;

private:
    Scene* m_pScene;

    QColor m_bgColor;
    QColor m_lightColor;
    QColor m_darkColor;
    QPen m_penLight;
    QPen m_penDark;

    int m_gridSize;
    int m_gridSquare;
};
