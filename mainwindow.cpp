#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <connectiondialog.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    COMPORT = new QSerialPort;
    COMPORT -> setPortName("COM1");
    COMPORT -> setBaudRate(QSerialPort::BaudRate::Baud9600);
    COMPORT -> setParity(QSerialPort::Parity::NoParity);
    COMPORT -> setDataBits(QSerialPort::DataBits::Data8);
    COMPORT -> setStopBits(QSerialPort::StopBits::OneStop);
    COMPORT -> setFlowControl(QSerialPort::FlowControl::NoFlowControl);
    COMPORT -> open(QIODevice::ReadWrite);
    ui->comboBox->addItem("Red");
    ui->comboBox->addItem("Green");
    ui->comboBox->addItem("Blue");
    ui->comboBox->addItem("Yellow");
    ui->comboBox_2->addItem("Red");
    ui->comboBox_2->addItem("Blue");
    ui->comboBox_2->addItem("Green");
    ui->comboBox_2->addItem("Yellow");


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionConnection_triggered()
{
    connectionDialog connectiondialog;
    connectiondialog.setModal(true);
    connectiondialog.exec();

}



void MainWindow::on_actionStart_triggered()
{
    QString ip = ui->ip->text();
    string ip2 = ip.toStdString();
    cv::VideoCapture cap(ip2);
    cap.set(cv::CAP_PROP_FRAME_WIDTH, 1280);
    cap.set(cv::CAP_PROP_FRAME_HEIGHT, 720);

    while (true){
        cv::Mat frame;
        cap.read(frame);

        cv::Mat hsv_frame;
        cv::cvtColor(frame, hsv_frame, cv::COLOR_BGR2HSV);

        int height = frame.rows;
        int width = frame.cols;

        int cx = width / 2;
        int cy = height / 2;

        cv::Vec3b pixel_center = hsv_frame.at<cv::Vec3b>(cy, cx);
        int hue_value = pixel_center[0];
        int hue_value2 = pixel_center[1];
        int hue_value3 = pixel_center[2];
        std::string color = "";

        if ((0 < hue_value && hue_value < 180) && (0 < hue_value2 && hue_value2 < 255) && (200 < hue_value3 && hue_value3 < 255)) {
            color = "White";
        }

        if ((20 < hue_value && hue_value < 30) && (100 < hue_value2 && hue_value2 < 255) && (100 < hue_value3 && hue_value3 < 255)) {
            color = "Yellow";
        }

        if ((25 < hue_value && hue_value < 102) && (52 < hue_value2 && hue_value2 < 255) && (72 < hue_value3 && hue_value3 < 255)) {
            color = "Green";
        }

        if ((78 < hue_value && hue_value < 138) && (158 < hue_value2 && hue_value2 < 255) && (124 < hue_value3 && hue_value3 < 255)) {
            color = "Blue";
        }

        if (((0 < hue_value && hue_value < 10) || (136 < hue_value && hue_value < 180)) && (120 < hue_value2 && hue_value2 < 255) && (70 < hue_value3 && hue_value3 < 255)) {
            color = "Red";
        }

        std::cout << pixel_center << std::endl;

        cv::putText(frame, color, cv::Point(18, 58), cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(255, 0, 0), 2);
        cv::circle(frame, cv::Point(cx, cy), 5, cv::Scalar(255, 0, 0), 3);
        cv::imshow("frame", frame);

        char key = cv::waitKey(1);
        if (key == 27) {
            break;
        }
    }
    cap.release();
    destroyAllWindows();

}



