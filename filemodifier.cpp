#include "filemodifier.h"

FileModifier::FileModifier(QObject *parent) : QObject(parent) {}


FileModifier::~FileModifier() { delete this->timer; }


//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


void FileModifier::timed_run() {

    this->timer->start(this->timer_period);

}


void FileModifier::run_modification() {

    QStringList files = this->input_folder_path.entryList(QStringList() << this->input_file_mask, QDir::Files);

    if (files.empty()) { qDebug() << this->input_folder_path.absolutePath() + " - в папке нет подходящих файлов!"; }

    for (const QString &file_name : files) {

        QFile file(this->input_folder_path.absolutePath() + "/" + file_name);
        QFileInfo fileInfo(file);

        if (!file.exists()) {
            qDebug() << file.fileName() + " - не существует!\n";
            continue;
        }

        // Защита от дурака
        if (fileInfo.isReadable() && !file.isOpen()) {

            modify_file(file);

        }

        else { qDebug() << file.fileName() + " - занят или не может быть открыт!\n"; }

    }
}


void FileModifier::modify_file(QFile &file) {

    if (!file.open(QIODevice::ReadWrite)) {

        qDebug() << "Не удалось открыть файл" << file.fileName();
        return;

    }

    QByteArray data = file.readAll();

    qDebug() << xor_mask << "\n";

    for (int i = 0; i < data.size(); ++i) {

        data[i] ^= this->xor_mask[i % 8];

    }

    file.close();
    this->save_output(file, data);

    if (this->remove_input_file) { file.remove(); }

}


void FileModifier::save_output(QFile &file, QByteArray& data) {

    QFileInfo output_info(file);
    QString output_destination = this->output_path.absolutePath() + "/" + output_info.baseName() + "." + output_info.suffix();

    if (this->overwrite_output_copies) {

        QFile output_file(output_destination);

        if (output_file.exists())
        { output_file.open(QIODevice::WriteOnly | QIODevice::Truncate); }
        else
        { output_file.open(QIODevice::WriteOnly); }

        output_file.write(data);
        output_file.close();

    }
    else {

        QString new_file;
        int index = 0;

        do {
            new_file = this->output_path.absolutePath() + "/" + output_info.baseName() + "_" + QString::number(++index) + "." + output_info.suffix();
        }
        while (QFile::exists(new_file));

        QFile unique_output(new_file);

        unique_output.open(QIODevice::WriteOnly);
        unique_output.write(data);
        unique_output.close();

    }

}


//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


void FileModifier::set_timer(int period) {

    if (period <= 0) { return; }

    this->timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &FileModifier::run_modification);
    this->timer_is_set = true;
    this->timer_period = period;

}
