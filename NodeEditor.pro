QT = core gui

greaterThan(QT_MAJOR_VERSION, 4) : QT += widgets

CONFIG += c++11 console
CONFIG -= app_bundle

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        Edge.cpp \
        Node.cpp \
        NodeContentWidget.cpp \
        NodeEdge.cpp \
        NodeEdgeGraphic.cpp \
        NodeEditorWindow.cpp \
        NodeGraphics.cpp \
        NodeGraphicsScene.cpp \
        NodeGraphicsView.cpp \
        NodeScene.cpp \
        NodeSocket.cpp \
        NodeSocketGraphic.cpp \
        main.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    Edge.h \
    Node.h \
    NodeContentWidget.h \
    NodeEdge.h \
    NodeEdgeGraphic.h \
    NodeEditorWindow.h \
    NodeGraphics.h \
    NodeGraphicsScene.h \
    NodeGraphicsView.h \
    NodeScene.h \
    NodeSocket.h \
    NodeSocketGraphic.h

RESOURCES += \
    qss/NodeStyle.qss
