#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    reset();

    connect(
        ui->pb1, &QPushButton::clicked,
        this, &MainWindow::on_number_input
        );
    connect(
        ui->pb2, &QPushButton::clicked,
        this, &MainWindow::on_number_input
        );
    connect(
        ui->plusButton, &QPushButton::clicked, this, &MainWindow::on_operation_nput);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_operation_nput() {
    QPushButton* pb = dynamic_cast<QPushButton*>(sender());

    if (state == State::FirstDigit) {
        return;
    }

    if (state == State::InputNumber) {
        bool ok;
        double right = ui->leInput->text().toDouble(&ok);
        pendingOperation = pb->text();

        if (ok) {
            if (pendingOperation == "+")
                currentValue = currentValue + right;

            ui->historyLabel->setText(QString::number(currentValue) + pendingOperation);
            ui->leInput->setText(QString::number(currentValue));
            state = State::FirstDigit;
        }
        return;
    }
}

void MainWindow::on_number_input() {
    QPushButton* pb = dynamic_cast<QPushButton*>(sender());
    QString digit = pb->text();

    if (state == State::FirstDigit) {
        ui->leInput->setText("");
        if (digit != "0")
            state = State::InputNumber;
    }
    ui->leInput->setText(ui->leInput->text() + digit);
}

void MainWindow::save_value() {
    bool ok;
    double value = ui->leInput->text().toDouble(&ok);
    if (ok) {
        rememberedValue = value;
    }
}

void MainWindow::reset() {
    ui->leInput->setText("0");
    state = State::FirstDigit;
    currentValue = 0.0;
    rememberedValue = 0.0;
    addValue = 0.0;
    pendingOperation.clear();
}
