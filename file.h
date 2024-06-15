#ifndef FILE_H
#define FILE_H

#include <QFileInfo>

class File
{
private:
    QString url;
    qint64 size;
    bool exist;

public:
    File(const QString &str); // Конструктор класса File

    void fileUpdate(); // Метод для обновления информации о файле

    QString getUrl() const; // Метод для получения URL файла
    qint64 getSize() const; // Метод для получения размера файла
    bool getExist() const; // Метод для получения флага существования файла
};

#endif // FILE_H
