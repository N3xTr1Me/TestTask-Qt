#ifndef FILEMODIFIER_H
#define FILEMODIFIER_H

#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QTimer>
#include <QDebug>

class FileModifier : public QObject {

    Q_OBJECT

    //--------------------------------------------------

public:

    bool remove_input_file = false;
    bool overwrite_output_copies = false;

    QDir input_folder_path = QDir::current();
    QDir output_path = QDir(QDir::currentPath() + "/result/");

    QString input_file_mask = "*.txt";
    QByteArray xor_mask = QByteArray::fromHex("0123456789ABCDEF");

    QTimer *timer;
    bool timer_is_set = false;
    int timer_period;

    //--------------------------------------------------

    explicit FileModifier(QObject *parent = nullptr);
    ~FileModifier();

    //--------------------------------------------------

    //Бизнес-логика
    void timed_run();
    void run_modification();
    void modify_file(QFile &file);
    void save_output(QFile &file, QByteArray& data);

public slots:

    //Вспомогательный метод для запуска таймера операции
    void set_timer(int period);

};

#endif // FILEMODIFIER_H
