#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "centerwidget.h"
#include <QMainWindow>
#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include <QStatusBar>
#include <QFontDialog>
#include <QMessageBox>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void on_actSetFont_triggered();
    void on_actHelp_triggered();

private:
    void setupMenuBar();
    void setupStatusBar();
    void setupCenterWidget();

    QAction *actNewFile;
    QAction *actExportFile;
    QAction *actPrintFile;
    QAction *actHelp;
    QAction *actSetFont;
    QAction *actClose;

    QMenu* fileMenu;
    QMenu* helpMenu;

    CenterWidget *centerWidget;
};

#endif // MAINWINDOW_H
