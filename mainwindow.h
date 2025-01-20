#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QApplication>
#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QRadioButton>
#include <QLineEdit>
#include <QSharedPointer>
#include <Qmap>
#include <QList>
#include <QWidget>
#include <QFormLayout>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT

    Ui::MainWindow *ui;

    QList<QPushButton*> buttons;
    QList<QLineEdit*> text_fields;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void add_controls(const QList<QPushButton*>& buttons, const QList<QLineEdit*>& text_fields);

    void reset_start_button();

public slots:

    void start_button_style_change(bool checked);
    void delete_input_style_change(bool checked);
    void output_handle_style_change(bool checked);

};


#endif // MAINWINDOW_H
