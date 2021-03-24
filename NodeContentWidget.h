#pragma once

#include <QWidget>

class NodeContentWidget : public QWidget
{
    Q_OBJECT
public:
    NodeContentWidget(QWidget* parent=nullptr);

private:
    void InitUI();
};

