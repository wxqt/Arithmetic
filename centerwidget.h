#ifndef CENTERWIDGET_H
#define CENTERWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QComboBox>
#include <QSpinBox>
#include <QTextEdit>
#include <QTextBlock>
#include <QTextCursor>
#include <QTextBlockFormat>
#include <QString>
#include <QStringList>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QTime>
#include <QPrinter>
#include <QPrintPreviewDialog>

class CenterWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CenterWidget(QWidget *parent = nullptr);

    QStringList getOneNum(int index);
    QStringList getTowNum(int index);
    QStringList getOperator(int index);

    QTextEdit *textEdit;
    QPushButton *btnClose;

signals:

public slots:
    void on_btnGencrate_clicked();
    void on_btnExport_clicked();
    void on_btnPrint_clicked();

    void printDocument(QPrinter *printer);

private:
    void createWidget();
    void createLayout();

    QLabel *labOne;
    QLabel *labTow;
    QLabel *labOperator;
    QLabel *labFrequency;

    QComboBox *cbxOneNum;
    QComboBox *cbxTowNum;
    QComboBox *cbxOperator;

    QSpinBox *sbxFrequency;

    QPushButton *btnGencrate;
    QPushButton *btnExport;
    QPushButton *btnPrint;

};

#endif // CENTERWIDGET_H
