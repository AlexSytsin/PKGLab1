#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QVector>
#include <QPainter>
#include <QPaintEvent>
#include <iostream>
#include <algorithm>
#include <QColorDialog>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    this->setFixedSize(QSize(800, 450));

    ui->setupUi(this);
    connect(ui->R, SIGNAL(textEdited(QString)), this, SLOT(changeRGB()));
    connect(ui->G, SIGNAL(textEdited(QString)), this, SLOT(changeRGB()));
    connect(ui->B, SIGNAL(textEdited(QString)), this, SLOT(changeRGB()));
    connect(ui->H, SIGNAL(textEdited(QString)), this, SLOT(changeHSL()));
    connect(ui->S, SIGNAL(textEdited(QString)), this, SLOT(changeHSL()));
    connect(ui->L, SIGNAL(textEdited(QString)), this, SLOT(changeHSL()));
    connect(ui->C, SIGNAL(textEdited(QString)), this, SLOT(changeCMYK()));
    connect(ui->M, SIGNAL(textEdited(QString)), this, SLOT(changeCMYK()));
    connect(ui->Y, SIGNAL(textEdited(QString)), this, SLOT(changeCMYK()));
    connect(ui->K, SIGNAL(textEdited(QString)), this, SLOT(changeCMYK()));
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(changeColor()));
    changeRGB();
    connect(ui->R_sl, SIGNAL(sliderMoved(int)), this, SLOT(changeSliderRGB()));
    connect(ui->G_sl, SIGNAL(sliderMoved(int)), this, SLOT(changeSliderRGB()));
    connect(ui->B_sl, SIGNAL(sliderMoved(int)), this, SLOT(changeSliderRGB()));
    connect(ui->H_sl, SIGNAL(sliderMoved(int)), this, SLOT(changeSliderHSL()));
    connect(ui->S_sl, SIGNAL(sliderMoved(int)), this, SLOT(changeSliderHSL()));
    connect(ui->L_sl, SIGNAL(sliderMoved(int)), this, SLOT(changeSliderHSL()));
    connect(ui->C_sl, SIGNAL(sliderMoved(int)), this, SLOT(changeSliderCMYK()));
    connect(ui->M_sl, SIGNAL(sliderMoved(int)), this, SLOT(changeSliderCMYK()));
    connect(ui->Y_sl, SIGNAL(sliderMoved(int)), this, SLOT(changeSliderCMYK()));
    connect(ui->K_sl, SIGNAL(sliderMoved(int)), this, SLOT(changeSliderCMYK()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeColor(){

    QVector <double> rgb(3);
    rgb[0] = ui->R->text().toDouble();
    rgb[1] = ui->G->text().toDouble();
    rgb[2] = ui->B->text().toDouble();
    QColor color(rgb[0],rgb[1],rgb[2]);
    color = QColorDialog::getColor(QColor(color));
    int r,g,b;
    color.getRgb(&r,&g,&b);
    rgb={(double)r,(double)g,(double)b};
    setRGB(rgb);
    changeRGB();
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter;
    painter.begin(this);
    QRect r(QPoint(0,0), this->size());
    QBrush b(current_color);
    painter.setBrush(b);
    painter.drawRect(r);
    painter.end();
}

void MainWindow::setRGB(QVector <double> rgb){

    ui->R->setText(QString::number(round(rgb[0])));
    ui->G->setText(QString::number(round(rgb[1])));
    ui->B->setText(QString::number(round(rgb[2])));


    current_color = QColor(round(rgb[0]),round(rgb[1]),round(rgb[2]));

}

void MainWindow::setSliderRGB(QVector <double> rgb){
    ui->R_sl->setValue(round(rgb[0]));
    ui->G_sl->setValue(round(rgb[1]));
    ui->B_sl->setValue(round(rgb[2]));

}



void MainWindow::setHSL(QVector <double> hsl){

    ui->H->setText(QString::number(round(hsl[0])));
    ui->S->setText(QString::number(round(hsl[1])));
    ui->L->setText(QString::number(round(hsl[2])));


}

void MainWindow::setSliderHSL(QVector <double> hsl){

    ui->H_sl->setValue(round(hsl[0]));
    ui->S_sl->setValue(round(hsl[1]));
    ui->L_sl->setValue(round(hsl[2]));

}

void MainWindow::setCMYK(QVector <double> cmyk){

    ui->C->setText(QString::number(round(cmyk[0])));
    ui->M->setText(QString::number(round(cmyk[1])));
    ui->Y->setText(QString::number(round(cmyk[2])));
    ui->K->setText(QString::number(round(cmyk[3])));


    if(ui->K->text().toDouble()>50.0){
        QColor color;
        color.setRgb(255, 255, 255);
        QString styleSheet = QString("color: %1").arg(color.name());
        ui->label->setStyleSheet(styleSheet);
        ui->label_2->setStyleSheet(styleSheet);
        ui->label_3->setStyleSheet(styleSheet);
        ui->label_4->setStyleSheet(styleSheet);
        ui->label_5->setStyleSheet(styleSheet);
        ui->label_6->setStyleSheet(styleSheet);
    }
    else{
        QColor color;
        color.setRgb(0, 0, 0);
        QString styleSheet = QString("color: %1").arg(color.name());
        ui->label->setStyleSheet(styleSheet);
        ui->label_2->setStyleSheet(styleSheet);
        ui->label_3->setStyleSheet(styleSheet);
        ui->label_4->setStyleSheet(styleSheet);
        ui->label_5->setStyleSheet(styleSheet);
        ui->label_6->setStyleSheet(styleSheet);
    }

}

void MainWindow::setSliderCMYK(QVector <double> cmyk){
    ui->C_sl->setValue(round(cmyk[0]));
    ui->M_sl->setValue(round(cmyk[1]));
    ui->Y_sl->setValue(round(cmyk[2]));
    ui->K_sl->setValue(round(cmyk[3]));

}


void MainWindow::changeSliderRGB(){
    QVector <double> rgb(3);
    rgb[0] = (double)ui->R_sl->value();
    rgb[1] = (double)ui->G_sl->value();
    rgb[2] = (double)ui->B_sl->value();



    for (int i=0;i<3;i++){
        rgb[i]=std::max(0.0,std::min(rgb[i],255.0));
    }

    QVector <double> cmyk = RgbToCmyk(rgb);
    QVector <double> hsl = RgbToHsl(rgb);

    setHSL(hsl);
    setCMYK(cmyk);
    setRGB(rgb);
    setSliderHSL(hsl);
    setSliderCMYK(cmyk);
    update();
}

void MainWindow::changeSliderHSL(){
    QVector <double> hsl(3);
    hsl[0] = (double)ui->H_sl->value();
    hsl[1] = (double)ui->S_sl->value();
    hsl[2] = (double)ui->L_sl->value();

    hsl[0] = std::max(0.0,std::min(hsl[0],360.0));
    for (int i=1;i<3;i++){
        hsl[i]=std::max(0.0,std::min(hsl[i],100.0));
    }

    QVector <double> cmyk = HslToCmyk(hsl);
    QVector <double> rgb = HslToRgb(hsl);

    setHSL(hsl);
    setCMYK(cmyk);
    setRGB(rgb);
    setSliderRGB(rgb);
    setSliderCMYK(cmyk);
    update();
}

void MainWindow::changeSliderCMYK(){

    QVector <double> cmyk(4);
    cmyk[0] = (double)ui->C_sl->value();
    cmyk[1] = (double)ui->M_sl->value();
    cmyk[2] = (double)ui->Y_sl->value();
    cmyk[3] = (double)ui->K_sl->value();


    for (int i=0;i<4;i++){
        cmyk[i]=std::max(0.0,std::min(cmyk[i],100.0));
    }

    QVector <double> rgb = CmykToRgb(cmyk);
    QVector <double> hsl = CmykToHsl(cmyk);
    QVector <double> cmyk2 = RgbToCmyk(rgb);
    bool DiffBig = false;
    for(int i = 0;i<4;i++){
        if (abs(cmyk2[i]-cmyk[i])>=1){
            DiffBig = true;
        }
    }
    if (DiffBig){
        QVector <double> rgb2(3);
        rgb2[0] = ui->R->text().toDouble();
        rgb2[1] = ui->G->text().toDouble();
        rgb2[2] = ui->B->text().toDouble();
        cmyk2 = RgbToCmyk(rgb2);
        setCMYK(cmyk2);
        update();

    }
    else{
        setHSL(hsl);
        setRGB(rgb);
        setCMYK(cmyk);
        setSliderHSL(hsl);
        setSliderRGB(rgb);
        update();

    }
}

void MainWindow::changeRGB(){
    QVector <double> rgb(3);
    rgb[0] = ui->R->text().toDouble();
    rgb[1] = ui->G->text().toDouble();
    rgb[2] = ui->B->text().toDouble();

    for (int i=0;i<3;i++){
        rgb[i]=std::max(0.0,std::min(rgb[i],255.0));
    }

    QVector <double> cmyk = RgbToCmyk(rgb);
    QVector <double> hsl = RgbToHsl(rgb);

    setHSL(hsl);
    setCMYK(cmyk);
    setRGB(rgb);
    setSliderHSL(hsl);
    setSliderCMYK(cmyk);
    setSliderRGB(rgb);
    update();
}

void MainWindow::changeHSL(){
    QVector <double> hsl(3);
    hsl[0] = ui->H->text().toDouble();
    hsl[1] = ui->S->text().toDouble();
    hsl[2] = ui->L->text().toDouble();

    hsl[0] = std::max(0.0,std::min(hsl[0],360.0));
    for (int i=1;i<3;i++){
        hsl[i]=std::max(0.0,std::min(hsl[i],100.0));
    }

    QVector <double> cmyk = HslToCmyk(hsl);
    QVector <double> rgb = HslToRgb(hsl);

    setCMYK(cmyk);
    setRGB(rgb);
    setHSL(hsl);
    setSliderHSL(hsl);
    setSliderCMYK(cmyk);
    setSliderRGB(rgb);
    update();

}

void MainWindow::changeCMYK(){

    QVector <double> cmyk(4);
    cmyk[0] = ui->C->text().toDouble();
    cmyk[1] = ui->M->text().toDouble();
    cmyk[2] = ui->Y->text().toDouble();
    cmyk[3] = ui->K->text().toDouble();


    for (int i=0;i<4;i++){
        cmyk[i]=std::max(0.0,std::min(cmyk[i],100.0));
    }

    QVector <double> rgb = CmykToRgb(cmyk);
    QVector <double> hsl = CmykToHsl(cmyk);
    QVector <double> cmyk2 = RgbToCmyk(rgb);
    bool DiffBig = false;
    for(int i = 0;i<4;i++){
        if (abs(cmyk2[i]-cmyk[i])>=1){
            DiffBig = true;
        }
    }
    if (DiffBig){
        QVector <double> rgb2(3);
        rgb2[0] = ui->R->text().toDouble();
        rgb2[1] = ui->G->text().toDouble();
        rgb2[2] = ui->B->text().toDouble();
        cmyk2 = RgbToCmyk(rgb2);
        setCMYK(cmyk2);
        setSliderCMYK(cmyk2);
        update();

    }
    else{
        setHSL(hsl);
        setRGB(rgb);
        setCMYK(cmyk);
        setSliderHSL(hsl);
        setSliderCMYK(cmyk);
        setSliderRGB(rgb);
        update();
    }


}


QVector<double> MainWindow::RgbToCmyk(QVector<double> rgb) {
    QVector<double> cmyk(4);
    double r = rgb[0] / 255.0;
    double g = rgb[1] / 255.0;
    double b = rgb[2] / 255.0;

    double k = 1 - std::max({r, g, b});

    if (k == 1) {
        cmyk[0] = 0;
        cmyk[1] = 0;
        cmyk[2] = 0;
        cmyk[3] = 100;
    } else {
        cmyk[0] = (1 - r - k) / (1 - k) * 100;
        cmyk[1] = (1 - g - k) / (1 - k) * 100;
        cmyk[2] = (1 - b - k) / (1 - k) * 100;
        cmyk[3] = k * 100;
    }

    return cmyk;
}

QVector<double> MainWindow::RgbToHsl(QVector<double> rgb) {
    double r = rgb[0] / 255.0;
    double g = rgb[1] / 255.0;
    double b = rgb[2] / 255.0;

    double max = qMax(r, qMax(g, b));
    double min = qMin(r, qMin(g, b));

    double l = (max + min) / 2;

    double s;
    if (l == 0 || max == min) {
        s = 0;
    } else {
        s = (max - min) / (1 - qAbs(2 * l - 1));
    }


    double h;
    if (max == min) {
        h = 0;
    } else {
        if (max == r) {
            h = 60 * (g - b) / (max - min);
        } else if (max == g) {
            h = 60 * (b - r) / (max - min) + 120;
        } else {
            h = 60 * (r - g) / (max - min) + 240;
        }
        if (h < 0) {
            h += 360;
        }
    }


    s *= 100;
    l *= 100;
    return QVector<double>{h, s, l};
}

QVector<double> MainWindow::HslToRgb(QVector<double> hsl) {

    double h = (std::isnan(hsl[0]) ? 0 : hsl[0]) / 360.0;
    double s = (std::isnan(hsl[1]) ? 0 : hsl[1]) / 100.0;
    double l = (std::isnan(hsl[2]) ? 0 : hsl[2]) / 100.0;

    QVector<double> rgb(3, 0.0);

    if (s == 0) {
        // If saturation is 0, the color is a shade of gray
        rgb[0] = rgb[1] = rgb[2] = l * 255;
        return rgb;
    }

    double t1, t2, t3, val;

    if (l < 0.5) {
        t2 = l * (1 + s);
    } else {
        t2 = l + s - l * s;
    }
    t1 = 2 * l - t2;

    for (int i = 0; i < 3; i++) {
        t3 = h + 1.0 / 3.0 * - (i - 1);
        if (t3 < 0) {
            t3++;
        }
        if (t3 > 1) {
            t3--;
        }

        if (6 * t3 < 1) {
            val = t1 + (t2 - t1) * 6 * t3;
        } else if (2 * t3 < 1) {
            val = t2;
        } else if (3 * t3 < 2) {
            val = t1 + (t2 - t1) * (2.0 / 3.0 - t3) * 6;
        } else {
            val = t1;
        }

        rgb[i] = std::round(val * 255);
    }

    return rgb;
}

QVector<double> MainWindow::CmykToRgb(QVector<double> cmyk) {

    double c = cmyk[0] / 100.0;
    double m = cmyk[1] / 100.0;
    double y = cmyk[2] / 100.0;
    double k = cmyk[3] / 100.0;

    c = c * (1 - k) + k;
    m = m * (1 - k) + k;
    y = y * (1 - k) + k;

    double r = 1 - c;
    double g = 1 - m;
    double b = 1 - y;

    r = std::round(255 * r);
    g = std::round(255 * g);
    b = std::round(255 * b);

    return QVector<double>{r, g, b};
}

QVector<double> MainWindow::HslToCmyk(QVector<double> hsl) {
    QVector <double> rgb = HslToRgb(hsl);
    QVector <double> cmyk = RgbToCmyk(rgb);
    return cmyk;
}

QVector<double> MainWindow::CmykToHsl(QVector<double> cmyk) {
    QVector <double> rgb = CmykToRgb(cmyk);
    QVector <double> hsl = RgbToHsl(rgb);
    return hsl;
}
