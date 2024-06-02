#ifndef FILEOBSERVER_H
#define FILEOBSERVER_H

#include <QObject>
#include <QString>

// Класс FileObserver для обработки изменений файлов
class FileObserver : public QObject
{
    Q_OBJECT

public slots:
    void onFileChanged(const QString& path, qint64 newSize); // Слот для обработки изменения файлов
};

#endif // FILEOBSERVER_H
