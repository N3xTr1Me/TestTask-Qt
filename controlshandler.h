#ifndef CONTROLSHANDLER_H
#define CONTROLSHANDLER_H


#include <QObject>
#include <QIntValidator>

#include "filemodifier.h"
#include "mainwindow.h"


class Controller : public QObject
{
    Q_OBJECT

    //---------------------------------------------

    FileModifier modifier;
    MainWindow gui;

    //---------------------------------------------

    inline QList<QPushButton*> create_buttons();
    inline QList<QLineEdit*> create_text_fields();

public:

    explicit Controller(QObject *parent = nullptr);

private slots:

    void toggle_run_program(bool toggled);
    void toggle_remove_input(bool toggled);
    void toggle_output_handle(bool toggled);

    void input_path_edited(const QString& data);
    void output_path_edited(const QString& data);
    void input_mask_edited(const QString& data);
    void xor_mask_edited(const QString& data);
    void timer_value_edited(const QString& data);

};

#endif // CONTROLSHANDLER_H
