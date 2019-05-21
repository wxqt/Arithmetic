#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setWindowTitle(tr("四则运算出题软件"));
    this->resize(700, 550);

    setupMenuBar();
    setupStatusBar();
    setupCenterWidget();
    connect(actNewFile, &QAction::triggered, centerWidget, &CenterWidget::on_btnGencrate_clicked);
    connect(actExportFile, &QAction::triggered, centerWidget, &CenterWidget::on_btnExport_clicked);
    connect(actPrintFile, &QAction::triggered, centerWidget, &CenterWidget::on_btnPrint_clicked);
    connect(actSetFont, &QAction::triggered, this, &MainWindow::on_actSetFont_triggered);
    connect(actHelp, &QAction::triggered, this, &MainWindow::on_actHelp_triggered);
    connect(actClose, &QAction::triggered, this, &MainWindow::close);
    connect(centerWidget->btnClose, &QPushButton::clicked, this, &MainWindow::close);
}

MainWindow::~MainWindow()
{

}

void MainWindow::on_actSetFont_triggered()
{
    bool ok;
    QFont font = QFontDialog::getFont(&ok, this);

    if (ok)
        centerWidget->textEdit->setFont(font);
}

void MainWindow::on_actHelp_triggered()
{
    QString str = "版本: 0.2.0\n\n制作: 五行缺铁\n\nQQ: 19691705";
    QMessageBox::about(this, tr("关于"), str);
}

void MainWindow::setupMenuBar()
{
    fileMenu = menuBar()->addMenu(tr("文件"));
    actNewFile = fileMenu->addAction(tr("生成"));
    fileMenu->addSeparator();
    actExportFile = fileMenu->addAction(tr("导出"));
    actPrintFile = fileMenu->addAction(tr("打印"));
    fileMenu->addSeparator();
    actClose = fileMenu->addAction(tr("退出"));

    helpMenu = menuBar()->addMenu(tr("关于"));
    actSetFont = helpMenu->addAction(tr("设置字体"));
    helpMenu->addSeparator();
    actHelp = helpMenu->addAction(tr("关于"));
}

void MainWindow::setupStatusBar()
{
    statusBar()->showMessage(tr("欢迎使用..."), 0);
}

void MainWindow::setupCenterWidget()
{
    centerWidget = new CenterWidget;
    this->setCentralWidget(centerWidget);
}