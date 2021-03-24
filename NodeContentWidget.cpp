#include "NodeContentWidget.h"

#include <QVBoxLayout>
#include <QLabel>
#include <QTextEdit>

NodeContentWidget::NodeContentWidget(QWidget* parent)
    : QWidget(parent)
{
    InitUI();
}

void NodeContentWidget::InitUI() {
    QVBoxLayout* pLayout = new QVBoxLayout();
    pLayout->setContentsMargins(0, 0, 0, 0);
    this->setLayout(pLayout);

    QLabel* pWidgetLabel = new QLabel("Yup");
    pLayout->addWidget(pWidgetLabel);
    pLayout->addWidget(new QTextEdit("Was im fliegenden fick"));
}
