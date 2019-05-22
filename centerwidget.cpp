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

QStringList CenterWidget::getOneNum(int min , int max)
{
    QStringList strList;

    QTime time;
    time = QTime::currentTime();
    int seed = time.msec() + time.second() * 1000;
    qsrand(QString::number(seed).toUInt());

    for (int i = 0; i < sbxFrequency->value(); i++)
    {
        int num = qrand()%(max - min + 1) + min;
        strList << QString::number(num);
    }

    return strList;
}

QStringList CenterWidget::getTowNum(int min, int max)
{
    QStringList strList;

    QTime time;
    time = QTime::currentTime();
    int seed = time.msec() + time.second() * 2000;
    qsrand(QString::number(seed).toUInt());

    for (int i = 0; i < sbxFrequency->value(); i++)
    {
        int num = qrand()%(max - min + 1) + min;
        strList << QString::number(num);
    }

    return strList;
}

QStringList CenterWidget::getOperator(int index)
{
    QStringList strList;

    QTime time;
    time = QTime::currentTime();
    int seed = time.msec() + time.second() * 1000;
    qsrand(QString::number(seed).toUInt());

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
    int onemin = sbxOneNumMin->value();
    int onemax = sbxOneNumMax->value();
    int twomin = sbxTwoNumMin->value();
    int twomax = sbxTwoNumMax->value();
    int operatorIndex = cbxOperator->currentIndex();

    QString equalStr = " = ";
    QStringList strList;
    QString str;

    QStringList operatorStr = getOperator(operatorIndex);
    QStringList oneStrList = getOneNum(onemin, onemax);
    QStringList twoStrList = getTowNum(twomin, twomax);

/***************************条件过滤*****************************/
    for(int i = 0; i < sbxFrequency->value(); i++)
    {
        QString operStr = operatorStr.at(i);
        int oneNum = oneStrList.at(i).toInt();
        int twoNum = twoStrList.at(i).toInt();
        int totalNum = oneNum + twoNum;

        // 两位数加一位数时 值不得超过100
        if(operatorIndex == 0 || (operatorIndex == 4 && operStr == " + "))
        {
            if ((onemax <= 10 || twomax <= 10) && (onemax >= 10 || twomax >= 10))
            {
                if(totalNum > 100 && totalNum < 1000)
                {
                    if(oneNum > twoNum)
                    {
                        oneNum = totalNum - twoNum - 9;
                        oneStrList.replace(i, QString::number(oneNum));
                    }
                    else
                    {
                        twoNum = totalNum - oneNum - 9;
                        twoStrList.replace(i, QString::number(twoNum));
                    }
                }
            }
        }

        //相减 相除时 第二位数要小于第一位数
        else if(operatorIndex == 1 || operatorIndex == 3 || (operatorIndex == 4 && operStr == " - "))
        {
            if(oneNum < twoNum && (totalNum < 20))
            {
                twoNum = oneNum / 2 + 1;
                twoStrList.replace(i, QString::number(twoNum));
            }
            else if(oneNum < twoNum && (totalNum < 200))
            {
                twoNum = oneNum / 2 + 5;
                twoStrList.replace(i, QString::number(twoNum));
            }
            else if(oneNum < twoNum && (totalNum < 2000))
            {
                twoNum = oneNum / 2 + 50;
                twoStrList.replace(i, QString::number(twoNum));
            }
        }
    }


    // 如果是加法或乘法 调用档转换 打乱两位数的排列
    if(operatorIndex == 0 || operatorIndex == 2 || operatorIndex == 4)
    {
        documentConversion(oneStrList, twoStrList, operatorStr);
    }

/*******************生成文本写到TextEdit*******************/
    for (int i = 0; i < sbxFrequency->value(); i++)
    {

        strList << oneStrList.at(i) + operatorStr.at(i) + twoStrList.at(i) + equalStr;
        str.append(strList.at(i) + "\t");
        if ((i+1) % 4 == 0)
            str.append("\n");
    }

    textEdit->clear();
    textEdit->setPlainText(str);

/***********************设置行间距************************/
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

void CenterWidget::on_sbxOneNumMin_valueChanged(int value)
{
    if(value >= sbxOneNumMax->value())
        sbxOneNumMin->setValue(sbxOneNumMax->value() - 1);
}

void CenterWidget::on_sbxOneNumMax_valueChanged(int value)
{
    if(value <= sbxOneNumMin->value())
        sbxOneNumMax->setValue(sbxOneNumMin->value() + 1);
}

void CenterWidget::on_sbxTwoNumMin_valueChanged(int value)
{
    if(value >= sbxTwoNumMax->value())
        sbxTwoNumMin->setValue(sbxTwoNumMax->value() - 1);
}

void CenterWidget::on_sbxTwoNumMax_valueChanged(int value)
{
    if(value <= sbxTwoNumMin->value())
        sbxTwoNumMax->setValue(sbxTwoNumMin->value() + 1);
}

void CenterWidget::on_sbxOperator_currentIndexChanged(int index)
{
    if (index == 3)
    {
        sbxTwoNumMin->setRange(1, 9999);
        sbxTwoNumMin->setValue(1);
    }
    else {
        sbxTwoNumMin->setRange(0, 9999);
        sbxTwoNumMin->setValue(0);
    }
}

void CenterWidget::createWidget()
{
    QFont font;
    font.setPixelSize(15);

    labOne = new QLabel(tr("第一位数: "));
    labTwo = new QLabel(tr("第二位数: "));
    labWaveOne = new QLabel(tr("~"));
    labWaveTwo = new QLabel(tr("~"));
    labOperator = new QLabel(tr("四则运算: "));
    labFrequency = new QLabel(tr("题目数量: "));

    sbxOneNumMin = new QSpinBox;
    sbxOneNumMin->setRange(0, 9999);
    sbxOneNumMin->setValue(10);
    connect(sbxOneNumMin, QOverload<int>::of(&QSpinBox::valueChanged),
            this, &CenterWidget::on_sbxOneNumMin_valueChanged);

    sbxOneNumMax = new QSpinBox;
    sbxOneNumMax->setRange(1, 9999);
    sbxOneNumMax->setValue(99);
    connect(sbxOneNumMax, QOverload<int>::of(&QSpinBox::valueChanged),
            this, &CenterWidget::on_sbxOneNumMax_valueChanged);

    sbxTwoNumMin = new QSpinBox;
    sbxTwoNumMin->setRange(0, 9999);
    sbxTwoNumMin->setValue(0);
    connect(sbxTwoNumMin, QOverload<int>::of(&QSpinBox::valueChanged),
            this, &CenterWidget::on_sbxTwoNumMin_valueChanged);

    sbxTwoNumMax = new QSpinBox;
    sbxTwoNumMax->setRange(1, 9999);
    sbxTwoNumMax->setValue(9);
    connect(sbxTwoNumMax, QOverload<int>::of(&QSpinBox::valueChanged),
            this, &CenterWidget::on_sbxTwoNumMax_valueChanged);

    sbxFrequency = new QSpinBox;
    sbxFrequency->setRange(0, 9999);
    sbxFrequency->setValue(100);

    cbxOperator = new QComboBox;
    cbxOperator->addItem(tr("加法"));
    cbxOperator->addItem(tr("减法"));
    cbxOperator->addItem(tr("乘法"));
    cbxOperator->addItem(tr("除法"));
    cbxOperator->addItem(tr("加减混合"));
    connect(cbxOperator, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &CenterWidget::on_sbxOperator_currentIndexChanged);

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
    layOperator->addWidget(sbxOneNumMin, 1, 0);
    layOperator->addWidget(labWaveOne, 1, 1);
    layOperator->addWidget(sbxOneNumMax, 1, 2);
    layOperator->addWidget(labTwo, 2, 0);
    layOperator->addWidget(sbxTwoNumMin, 3, 0);
    layOperator->addWidget(labWaveTwo, 3, 1);
    layOperator->addWidget(sbxTwoNumMax, 3, 2);
    layOperator->addWidget(labOperator, 0, 3);
    layOperator->addWidget(cbxOperator, 1, 3);
    layOperator->addWidget(labFrequency, 2, 3);
    layOperator->addWidget(sbxFrequency, 3, 3);
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

void CenterWidget::documentConversion(QStringList &twoStrList, QStringList &oneStrList, QStringList operatorStr)
{
    QStringList strList;
    strList = oneStrList;

    QTime time;
    time = QTime::currentTime();
    int seed = time.msec() + time.second() * 1000;
    qsrand(QString::number(seed).toUInt());

    for(int i = 0; i < sbxFrequency->value(); i++)
    {
        if(operatorStr.at(i) == " - ")
            continue;

        int num = qrand() % 2;
        if(num == 0)
        {
            oneStrList.replace(i, twoStrList.at(i));
            twoStrList.replace(i, strList.at(i));
        }
    }
}
