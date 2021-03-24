#include "NodeEditorWindow.h"
#include "NodeScene.h"
#include "NodeGraphicsScene.h"
#include "NodeGraphicsView.h"
#include "Node.h"
#include "NodeSocket.h"
#include "NodeEdge.h"

#include <QVBoxLayout>
#include <QApplication>

NodeEditorWindow::NodeEditorWindow()
    :QWidget() {

    m_szFileName = "D:/Qt_Files/NodeEditor/qss/NodeStyle.qss";
    LoadStyleSheet(m_szFileName);


    InitUI();
}

void NodeEditorWindow::InitUI() {
    this->setGeometry(600, 300, 800, 600);

    QVBoxLayout* pLayout = new QVBoxLayout();
    pLayout->setContentsMargins(0, 0, 0, 0);
    this->setLayout(pLayout);

    //Create graphics scene
    m_pScene = new Scene();

    Node* pNodeOne = new Node(m_pScene, "Swear On Me Mum", 0);
    Node* pNodeTwo = new Node(m_pScene, "I'm the twin", 1);
    Node* pNodeThree = new Node(m_pScene, "Triplets? WTF!", 2);

    pNodeOne->SetPosition(-200, -100);
    pNodeTwo->SetPosition(0, 0);
    pNodeThree->SetPosition(200, -100);

    NodeEdge* pEdge = new NodeEdge(m_pScene, pNodeOne->GetOutputSockets()[0], pNodeTwo->GetInputSockets()[0]);
    NodeEdge* pEdgeTwo = new NodeEdge(m_pScene, pNodeTwo->GetOutputSockets()[0], pNodeThree->GetInputSockets()[1]);

    //Create graphics view
    m_pGraphView = new NodeGraphicsView(m_pScene->GetGraphicScene(), this);
    pLayout->addWidget(m_pGraphView);

    this->setWindowTitle("Node Editor");
    this->show();
}

void NodeEditorWindow::LoadStyleSheet(const char* szFileName) {
    QFile file(szFileName);
    if(file.exists() && file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QString styleSheet = file.readAll();
        qApp->setStyleSheet(styleSheet);
        file.close();
    }
}
