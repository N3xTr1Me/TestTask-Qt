#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {

    ui->setupUi(this);

}


MainWindow::~MainWindow() {
    delete ui;

    for (QPushButton* button : this->buttons) {
        delete button;
    }

    for (QLineEdit* field : this->text_fields) {
        delete field;
    }
}


void MainWindow::add_controls(const QList<QPushButton *> &buttons, const QList<QLineEdit *> &text_fields) {

    // [remove_input_file, output_copies_handle, start_btn]
    this->buttons = buttons;
    // [input_path, output_path, input_file_mask, timer_value]
    this->text_fields = text_fields;

    QWidget* main_menu = new QWidget();
    QFormLayout* menu_layout = new QFormLayout(main_menu);
    this->setCentralWidget(main_menu);

    // добавляем поля в окно
    for (QLineEdit* field : this->text_fields) {

        menu_layout->addRow(
            field->property("heading").value<QLabel*>(),
            field
            );

    }

    for (QPushButton* btn : this->buttons) {

        menu_layout->addRow(
            btn->property("heading").value<QLabel*>(),
            btn
            );

    }

}

void MainWindow::reset_start_button() {

    QSignalBlocker block(this->buttons[2]);
    this->buttons[2]->setChecked(false);
    this->start_button_style_change(false);

}


void MainWindow::start_button_style_change(bool checked) {

    if (checked) {
        this->buttons[2]->setStyleSheet("QPushButton { background-color: red; }");
        this->buttons[2]->setText("отмена");
    }
    else {
        this->buttons[2]->setStyleSheet("QPushButton { background-color: green; }");
        this->buttons[2]->setText("запуск");
    }

}

void MainWindow::delete_input_style_change(bool checked) {

    if (checked) {
        this->buttons[0]->setText("да");
    }
    else {
        this->buttons[0]->setText("нет");
    }

}


void MainWindow::output_handle_style_change(bool checked) {

    if (checked) {
        this->buttons[1]->setText("нумеровать копии");
    }
    else {
        this->buttons[1]->setText("перезаписать файл");
    }

}
