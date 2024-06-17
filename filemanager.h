#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include "file.h"
#include "Log.h"
#include "LogFormatter.h"
#include <QVector>
#include <QObject>

class FileManager : public QObject
{
    Q_OBJECT
private:
    explicit FileManager(Interlog* logger); // Конструктор класса FileManager
    ~FileManager(); // Деструктор класса FileManager
    FileManager(FileManager const&) = delete; // Запрещаем копирование
    FileManager& operator=(FileManager const&) = delete; // Запрещаем присваивание

protected:
    QVector<File*> files;
    Interlog* l;

public:
    static FileManager& Instance(Interlog* logger); // Метод для получения экземпляра класса FileManager
    void addFile(const QString &str); // Метод для добавления файла
    void removeFile(const QString &str); // Метод для удаления файла
    void listFiles() const; // Метод для вывода списка файлов
    void setLog(Interlog *logger); // Метод для установки логгера
    void check(); // Метод для проверки состояния файлов

signals:
    void upd_signal(File* F); // Сигнал об обновлении файла

private slots:
    void update(File* F); // Слот для обновления файла
};

#endif // FILEMANAGER_H
