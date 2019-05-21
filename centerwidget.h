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

    QStringList getOneNum(int min, int max);
    QStringList getTowNum(int min, int max);
    QStringList getOperator(int index);

    QTextEdit *textEdit;
    QPushButton *btnClose;

signals:

public slots:
    void on_btnGencrate_clicked();
    void on_btnExport_clicked();
    void on_btnPrint_clicked();
    void printDocument(QPrinter *printer);
    void on_sbxOneNumMin_valueChanged(int value);
    void on_sbxOneNumMax_valueChanged(int value);
    void on_sbxTwoNumMin_valueChanged(int value);
    void on_sbxTwoNumMax_valueChanged(int value);
    void on_sbxOperator_currentIndexChanged(int index);

private:
    void createWidget();
    void createLayout();

    void documentConversion(QStringList &twoStrList, QStringList &oneStrList, QStringList operatorStr);

    QLabel *labOne;
    QLabel *labTwo;
    QLabel *labWaveOne;
    QLabel *labWaveTwo;
    QLabel *labOperator;
    QLabel *labFrequency;

    QSpinBox *sbxOneNumMin;
    QSpinBox *sbxOneNumMax;
    QSpinBox *sbxTwoNumMin;
    QSpinBox *sbxTwoNumMax;
    QSpinBox *sbxFrequency;
    QComboBox *cbxOperator;

    QPushButton *btnGencrate;
    QPushButton *btnExport;
    QPushButton *btnPrint;

};

#endif // CENTERWIDGET_H
