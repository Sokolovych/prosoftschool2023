#include "mainwindow.h"
#include <iostream>
#include <algorithm>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("Moving Game");
    resize(240,300);
    connect(&timerCreation, &QTimer::timeout, this, [this](){
        QPushButton* button = new QPushButton(".", this);
        button->setStyleSheet("background-color: white;"
                          "border-style: outset;"
                          "border-color: gray;"
                          "border-width: 2px;"
                          "border-radius: 4px;");
        button->setGeometry(rand()%(this->geometry().width() - buttonSize), rand()%100, buttonSize, buttonSize);
        connect(button, &QPushButton::clicked, button, &QPushButton::deleteLater);
        button->show();

        uint8_t ySpeed = rand()%3 + 1;
        connect(&timerAnimation, &QTimer::timeout, button, [this, button, ySpeed](){
            if (button->underMouse())
                button->move(button->x(), button->y() + 2 * ySpeed);
            else
                button->move(button->x(), button->y() + ySpeed);
            if (button->y() >= this->geometry().height() - buttonSize) {
                this->setWindowTitle("YOU LOOSE");
                this->setStyleSheet("background-color: red;");
                button->deleteLater();
            }
        });
        timerAnimation.start(100);
        timerCreation.setInterval(rand()%900 + 100);
    });
    timerCreation.start(1000);
}

MainWindow::~MainWindow()
{
}
