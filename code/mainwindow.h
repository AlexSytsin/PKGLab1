#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QVector <double> rgb;
    QColor current_color;
    QVector <double> RgbToCmyk(QVector <double> rgb);
    QVector <double> RgbToHsl(QVector  <double> rgb);
    QVector <double> HslToCmyk(QVector <double> hsl);
    QVector <double> CmykToHsl(QVector <double> cmyk);
    QVector <double> HslToRgb(QVector  <double> hsl);
    QVector <double> CmykToRgb(QVector <double> cmyk);
    void paintEvent(QPaintEvent*) override;
    void setHSL(QVector  <double> hsl);
    void setRGB(QVector  <double> rgb);
    void setCMYK(QVector <double> cmyk);
    void setSliderHSL(QVector  <double> hsl);
    void setSliderRGB(QVector  <double> rgb);
    void setSliderCMYK(QVector <double> cmyk);
    Ui::MainWindow *ui;
private slots:
    void changeRGB();
    void changeCMYK();
    void changeHSL();
    void changeSliderRGB();
    void changeSliderCMYK();
    void changeSliderHSL();
    void changeColor();


};
#endif // MAINWINDOW_H
