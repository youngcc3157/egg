#ifndef MAINWINDOW_MAINWINDOW_H
#define MAINWINDOW_MAINWINDOW_H

#include <QMainWindow>
#include "Tree/treestate.h"
#include "TreeDisplayWidget/treedisplaywidget.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    TreeState* currentTree;
    TreeDisplayWidget* treeDisplayWidget;

protected:
    void keyPressEvent(QKeyEvent *event);
};

#endif // MAINWINDOW_MAINWINDOW_H