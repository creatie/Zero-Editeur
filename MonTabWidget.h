#ifndef MONTABWIDGET_H
#define MONTABWIDGET_H

#include <QTableWidget>

class MonTabWidget : public QTabWidget
{
    Q_OBJECT
public:
    MonTabWidget();
    MonTabWidget(QWidget*);
};

#endif // MONTABWIDGET_H
