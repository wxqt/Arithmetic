#include "centerwidget.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>

CenterWidget::CenterWidget(QWidget *parent) : QWidget(parent)
{
    createWidget();
    createLayout();
    connect(btnGencrate, &QPushButton::clicked, this, &CenterWidget::on_btnGencrate_clicked);
    connect(btnExport, &QPushButton::clicked, this, &CenterWidget::on_btnExport_clicked);
    connect(btnPrint, &QPushButton::clicked, this, &CenterWidget::on_btnPrint_clicked);
}

QStringList CenterWidget::getOneNum(int index)
{
    QStringList strList;

    QTime time;
    time = QTime::currentTime();
    int seed = time.msec() + time.second() * 1000;
    qsrand((uint)seed);

    if (index == 0)
    {
        for (int i = 0; i < sbxFrequency->value(); i++)
        {
            int num = qrand()%8 + 1;
            strList << QString::number(num);
        }
    }

    if (index == 1)
    {
        for (int i = 0; i < sbxFrequency->value(); i++)
        {
            int num = qrand()%89 + 10;
            strList << QString::number(num);
        }
    }

    if (index == 2)
    {
        for (int i = 0; i < sbxFrequency->value(); i++)
        {
            int num = qrand()%899 + 100;
            strList << QString::number(num);
        }
    }

//    if (index == 3)
//    {
//        for (int i = 0; i < sbxFrequency->value(); i++)
//        {
//            int num = qrand()%8999 + 1000;
//            strList << QString::number(num);
//        }
//    }
    return strList;
}

QStringList CenterWidget::getTowNum(int index)
{
    QStringList strList;

    QTime time;
    time = QTime::currentTime();
    int seed = time.msec() + time.second() * 100;
    qsrand((uint)seed);

    if (index == 0)
    {
        for (int i = 0; i < sbxFrequency->value(); i++)
        {
            int num = qrand()%8 + 1;
            strList << QString::number(num);
        }
    }

    if (index == 1)
    {
        for (int i = 0; i < sbxFrequency->value(); i++)
        {
            int num = qrand()%89 + 10;
            strList << QString::number(num);
        }
    }

    if (index == 2)
    {
        for (int i = 0; i < sbxFrequency->value(); i++)
        {
            int num = qrand()%899 + 100;
            strList << QString::number(num);
        }
    }

//    if (index == 3)
//    {
//        for (int i = 0; i < sbxFrequency->value(); i++)
//        {
//            int num = qrand()%8999 + 1000;
//            strList << QString::number(num);
//        }
//    }
    return strList;
}

QStringList CenterWidget::getOperator(int index)
{
    QStringList strList;

    QTime time;
    time = QTime::currentTime();
    int seed = time.msec() + time.second() * 1000;
    qsrand((uint)seed);

    if (index == 4)
    {
        for (int i = 0; i < sbxFrequency->value(); i++)
        {
            int num = qrand()%2;
            if (num == 0)
                strList << " + ";
            if (num == 1)
                strList << " - ";
        }
    }

    if (index == 0)
    {
        for (int i = 0; i < sbxFrequency->value(); i++)
            strList << " + ";
    }

    if (index == 1)
    {
        for (int i = 0; i < sbxFrequency->value(); i++)
            strList << " - ";
    }

    if (index == 2)
    {
        for (int i = 0; i < sbxFrequency->value(); i++)
            strList << "×";
    }

    if (index == 3)
    {
        for (int i = 0; i < sbxFrequency->value(); i++)
            strList << "÷";
    }

    return  strList;
}

void CenterWidget::on_btnGencrate_clicked()
{
    int oneIndex = cbxOneNum->currentIndex();
    int towIndex = cbxTowNum->currentIndex();
    int operatorIndex = cbxOperator->currentIndex();

    QStringList strList;
    QString str;

    QStringList oneStrList = getOneNum(oneIndex);
    QStringList twoStrList = getTowNum(towIndex);
    QStringList operatorStr = getOperator(operatorIndex);
    QString equalStr = " = ";


/***************************相减 相除 第二位数要小于第一位数****************************/
    if (cbxOneNum->currentIndex() == 0 && cbxTowNum->currentIndex() == 0
            && (cbxOperator->currentIndex() == 1
            || cbxOperator->currentIndex() == 3
            || cbxOperator->currentIndex() == 4))
    {
        for (int i = 0; i < sbxFrequency->value(); i++)
        {
            int oneNum = oneStrList.at(i).toInt();
            int twoNum = twoStrList.at(i).toInt();

            if (oneNum < twoNum)
            {
                twoNum = oneNum / 2 + 1;
                twoStrList.replace(i, QString::number(twoNum));
            }
        }
    }

    if (cbxOneNum->currentIndex() == 1 &&  cbxTowNum->currentIndex() == 1
            && (cbxOperator->currentIndex() == 1
            || cbxOperator->currentIndex() == 3
            || cbxOperator->currentIndex() == 4))
    {
        for (int i = 0; i < sbxFrequency->value(); i++)
        {
            int oneNum = oneStrList.at(i).toInt();
            int twoNum = twoStrList.at(i).toInt();

            if (oneNum < twoNum)
            {
                twoNum = oneNum / 2 + 5;
                twoStrList.replace(i, QString::number(twoNum));
            }
        }
    }

    if (cbxOneNum->currentIndex() == 2 &&  cbxTowNum->currentIndex() == 2
            && (cbxOperator->currentIndex() == 1
            || cbxOperator->currentIndex() == 3
            || cbxOperator->currentIndex() == 4))
    {
        for (int i = 0; i < sbxFrequency->value(); i++)
        {
            int oneNum = oneStrList.at(i).toInt();
            int twoNum = twoStrList.at(i).toInt();

            if (oneNum < twoNum)
            {
                twoNum = oneNum / 2 + 50;
                twoStrList.replace(i, QString::number(twoNum));
            }
        }
    }

//    if (cbxOneNum->currentIndex() == 3 &&  cbxTowNum->currentIndex() == 3
//            && (cbxOperator->currentIndex() == 1
//            || cbxOperator->currentIndex() == 3
//            || cbxOperator->currentIndex() == 4))
//    {
//        for (int i = 0; i < sbxFrequency->value(); i++)
//        {
//            int oneNum = oneStrList.at(i).toInt();
//            int twoNum = twoStrList.at(i).toInt();

//            if (oneNum < twoNum)
//            {
//                twoNum = oneNum / 2 + 500;
//                twoStrList.replace(i, QString::number(twoNum));
//            }
//        }
//    }


/*********************************相加 不得超过同位数***********************************/
    if (cbxOperator->currentIndex() == 0 && cbxOneNum->currentIndex() == 0 && cbxTowNum->currentIndex() == 0)
    {
        for (int i = 0; i < sbxFrequency->value(); i++)
        {
            int oneNum = oneStrList.at(i).toInt();
            int twoNum = twoStrList.at(i).toInt();
            int calcNum = oneNum + twoNum;

            if (calcNum >= 100)
            {
                oneNum = calcNum - twoNum - 1 ;
                oneStrList.replace(i, QString::number(oneNum));
            }
        }
    }

    if (cbxOperator->currentIndex() == 0 && cbxOneNum->currentIndex() == 1 && cbxTowNum->currentIndex() == 0)
    {
        for (int i = 0; i < sbxFrequency->value(); i++)
        {
            int oneNum = oneStrList.at(i).toInt();
            int twoNum = twoStrList.at(i).toInt();
            int calcNum = oneNum + twoNum;

            if (calcNum >= 100)
            {
                oneNum = calcNum - twoNum - 9 ;
                oneStrList.replace(i, QString::number(oneNum));
            }
        }
    }

//    if (cbxOperator->currentIndex() == 0 && cbxOneNum->currentIndex() == 2 && cbxTowNum->currentIndex() == 1)
//    {
//        for (int i = 0; i < sbxFrequency->value(); i++)
//        {
//            int oneNum = oneStrList.at(i).toInt();
//            int twoNum = twoStrList.at(i).toInt();
//            int calcNum = oneNum + twoNum;

//            if (calcNum >= 1000)
//            {
//                oneNum = calcNum - twoNum - 9 ;
//                oneStrList.replace(i, QString::number(oneNum));
//            }
//        }
//    }

/************************生成文本写到TextEdit**********************/
    for (int i = 0; i < sbxFrequency->value(); i++)
    {

        strList << oneStrList.at(i) + operatorStr.at(i) + twoStrList.at(i) + equalStr;
        str.append(strList.at(i) + "\t");
        if ((i+1) % 4 == 0)
            str.append("\n");
    }

    textEdit->clear();
    textEdit->setPlainText(str);

/*********************设置行间距************************/
    QTextDocument *doc =  textEdit->document();
    QTextCursor textcursor = textEdit->textCursor();
    for(QTextBlock it = doc->begin(); it !=doc->end();it = it.next())
    {
        QTextBlockFormat tbf = it.blockFormat();
        tbf.setLineHeight(10,QTextBlockFormat::LineDistanceHeight);
        textcursor.setPosition(it.position());
        textcursor.setBlockFormat(tbf);
        textEdit->setTextCursor(textcursor);
    }
}

void CenterWidget::on_btnExport_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("导出文件"), "./", tr("*.txt"));
    QString str = textEdit->toPlainText();

    QFile file(fileName);
    if (!fileName.isEmpty())
    {
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
            return;
        QTextStream out(&file);
        out << str;
        file.close();
    }
}

void CenterWidget::on_btnPrint_clicked()
{
    QPrinter printer(QPrinter::HighResolution);
    QPrintPreviewDialog preview(&printer, this);
    connect(&preview, SIGNAL(paintRequested(QPrinter*)), this, SLOT(printDocument(QPrinter*)));

    preview.exec();
}

void CenterWidget::printDocument(QPrinter *printer)
{
    textEdit->print(printer);
}

void CenterWidget::createWidget()
{
    QFont font;
    font.setPixelSize(15);

    labOne = new QLabel(tr("第一位数: "));
    labTow = new QLabel(tr("第二位数: "));
    labOperator = new QLabel(tr("四则运算: "));
    labFrequency = new QLabel(tr("题目数量: "));

    cbxOneNum = new QComboBox;
    cbxOneNum->addItem(tr("一位数"));
    cbxOneNum->addItem(tr("二位数"));
    cbxOneNum->addItem(tr("三位数"));
//    cbxOneNum->addItem(tr("四位数"));

    cbxTowNum = new QComboBox;
    cbxTowNum->addItem(tr("一位数"));
    cbxTowNum->addItem(tr("二位数"));
    cbxTowNum->addItem(tr("三位数"));
//    cbxTowNum->addItem(tr("四位数"));

    cbxOperator = new QComboBox;
    cbxOperator->addItem(tr("加法"));
    cbxOperator->addItem(tr("减法"));
    cbxOperator->addItem(tr("乘法"));
    cbxOperator->addItem(tr("除法"));
    cbxOperator->addItem(tr("加减混合"));

    sbxFrequency = new QSpinBox;
    sbxFrequency->setRange(0, 9999);
    sbxFrequency->setValue(100);

    btnGencrate = new QPushButton(tr("生成"));
    btnGencrate->setFont(font);
    btnGencrate->setFixedHeight(60);

    btnExport = new QPushButton(tr("导出"));
    btnExport->setFont(font);
    btnExport->setFixedHeight(60);

    btnPrint = new QPushButton(tr("打印"));
    btnPrint->setFont(font);
    btnPrint->setFixedHeight(60);

    btnClose = new QPushButton(tr("退出"));
    btnClose->setFont(font);
    btnClose->setFixedHeight(60);

    textEdit = new QTextEdit;
    textEdit->setFontPointSize(18);
}

void CenterWidget::createLayout()
{
    QGridLayout *layOperator = new QGridLayout;
    layOperator->addWidget(labOne, 0, 0);
    layOperator->addWidget(cbxOneNum, 0, 1);
    layOperator->addWidget(labTow, 0, 2);
    layOperator->addWidget(cbxTowNum, 0, 3);
    layOperator->addWidget(labOperator, 1, 0);
    layOperator->addWidget(cbxOperator, 1, 1);
    layOperator->addWidget(labFrequency, 1, 2);
    layOperator->addWidget(sbxFrequency, 1, 3);
    layOperator->setVerticalSpacing(10);
    layOperator->setHorizontalSpacing(10);

    QHBoxLayout *layButton = new QHBoxLayout;
    layButton->addWidget(btnGencrate);
    layButton->addSpacing(10);
    layButton->addWidget(btnExport);
    layButton->addWidget(btnPrint);
    layButton->addSpacing(10);
    layButton->addWidget(btnClose);

    QHBoxLayout *layTop = new QHBoxLayout;
    layTop->addLayout(layOperator);
    layTop->addSpacing(40);
    layTop->addStretch(1);
    layTop->addLayout(layButton);

    QVBoxLayout *layMain = new QVBoxLayout(this);
    layMain->addLayout(layTop, 1);
    layMain->addWidget(textEdit, 9);
}
