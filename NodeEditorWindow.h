#pragma once

#include <QWidget>
#include <QFile>

class QGraphicsView;
class NodeGraphicsView;
class Scene;

class NodeEditorWindow : QWidget {
public:
    NodeEditorWindow();

    void LoadStyleSheet(const char* szFileName);

private:
    void InitUI();

    const char* m_szFileName;

    NodeGraphicsView* m_pGraphView;
    Scene* m_pScene;
};
