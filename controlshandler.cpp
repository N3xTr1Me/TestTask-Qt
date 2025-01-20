#include "controlshandler.h"

Controller::Controller(QObject *parent) : QObject{parent} {

    this->gui.add_controls(this->create_buttons(), this->create_text_fields());
    this->gui.show();

}


QList<QPushButton*> Controller::create_buttons() {

    QPushButton *start_btn = new QPushButton("запуск");
    QPushButton *remove_input_file = new QPushButton("нет");
    QPushButton *output_copies_handle = new QPushButton("нумеровать копии");

    start_btn->setCheckable(true);
    remove_input_file->setCheckable(true);
    output_copies_handle->setCheckable(true);

    // приведение кнопок в нужное состояние
    remove_input_file->setChecked(false);
    output_copies_handle->setChecked(true);

    // добавление текстовых заголовков к кнопкам
    start_btn->setProperty("heading", QVariant::fromValue(new QLabel("Начать работу:", start_btn)));
    remove_input_file->setProperty("heading", QVariant::fromValue(new QLabel("Удалить исходные файлы?", remove_input_file)));
    output_copies_handle->setProperty("heading", QVariant::fromValue(new QLabel("Режим сохранения файлов при наличии копий:", output_copies_handle)));


    // графические изменения кнопок
    connect(start_btn, &QPushButton::toggled, &this->gui, &this->gui.start_button_style_change);
    connect(remove_input_file, &QPushButton::toggled, &this->gui, &this->gui.delete_input_style_change);
    connect(output_copies_handle, &QPushButton::toggled, &this->gui, &this->gui.output_handle_style_change);

    // присоединение бизнес-логики к нажатию
    connect(start_btn, &QPushButton::toggled, this, &this->toggle_run_program);
    connect(remove_input_file, &QPushButton::toggled, this, &this->toggle_remove_input);
    connect(output_copies_handle, &QPushButton::toggled, this, &this->toggle_output_handle);

    QList<QPushButton*> buttons = {remove_input_file, output_copies_handle, start_btn};

    return buttons;

}


QList<QLineEdit*> Controller::create_text_fields() {

    QLineEdit* input_path = new QLineEdit();
    QLineEdit* output_path = new QLineEdit();
    QLineEdit* input_file_mask = new QLineEdit();
    QLineEdit* xor_mask = new QLineEdit();

    // добавление текстовых заголовков к полям
    input_path->setProperty("heading", QVariant::fromValue(new QLabel("Папка с исходными файлами:", input_path)));
    output_path->setProperty("heading", QVariant::fromValue(new QLabel("Папка для сохранения результата:", output_path)));
    input_file_mask->setProperty("heading", QVariant::fromValue(new QLabel("маска исходных файлов:", input_file_mask)));
    xor_mask->setProperty("heading", QVariant::fromValue(new QLabel("маска операции XOR (HEX):", xor_mask)));

    // поле таймера требует ограничение на ввод только цифр
    QLineEdit* timer_value = new QLineEdit();
    timer_value->setValidator(new QIntValidator(0, INT_MAX)); // 0 - для разового запуска программы
    timer_value->setProperty("heading", QVariant::fromValue(new QLabel("таймер повторения программы (мс):", timer_value)));

    // добавление бизнес-логики к заполнению поля
    connect(input_path, QLineEdit::textChanged, this, &this->input_path_edited);
    connect(output_path, QLineEdit::textChanged, this, &this->output_path_edited);
    connect(input_file_mask, QLineEdit::textChanged, this, &this->input_mask_edited);
    connect(timer_value, QLineEdit::textChanged, this, &this->timer_value_edited);

    QList<QLineEdit*> text_fields = {input_path, output_path, input_file_mask, xor_mask, timer_value};

    return text_fields;

}


//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


void Controller::toggle_run_program(bool toggled) {

    if (!toggled) {

        if (this->modifier.timer_is_set) {

            this->modifier.timer->stop();
            this->modifier.timer_is_set = false;

        }

        return;
    }

    if (this->modifier.timer_is_set) { this->modifier.timed_run(); }

    else {

        this->modifier.run_modification();
        this->gui.reset_start_button();
    }

}

void Controller::toggle_remove_input(bool toggled) {

    if (toggled) {
        this->modifier.remove_input_file = true;
        return;
    }

    this->modifier.remove_input_file = false;
}

void Controller::toggle_output_handle(bool toggled) {

    if (toggled) {
        this->modifier.overwrite_output_copies = false;
        return;
    }

    this->modifier.overwrite_output_copies = true;

}


void Controller::input_path_edited(const QString& data) { this->modifier.input_folder_path = QDir(data); }

void Controller::output_path_edited(const QString& data) { this->modifier.output_path = QDir(data); }

void Controller::input_mask_edited(const QString& data) { this->modifier.input_file_mask = data; }

void Controller::xor_mask_edited(const QString &data) { this->modifier.xor_mask = data.toUtf8();}

void Controller::timer_value_edited(const QString& data) { this->modifier.set_timer(data.toInt()); }

