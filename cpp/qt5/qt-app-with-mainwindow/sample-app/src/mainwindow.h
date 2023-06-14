#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QSettings>
#include <QtWidgets/QMainWindow>


namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    // required at least for translation
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
protected:
    void resizeEvent(QResizeEvent *event);
private:
    Ui::MainWindow *ui;
    QSettings *mSettings;
};

#endif // MAINWINDOW_H
