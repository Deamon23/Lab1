#ifndef LOG_H
#define LOG_H

#include <QTextStream>
#include <QObject>

class Interlog : public QObject
{
    Q_OBJECT
public slots:
    virtual void log(const QString &str) const = 0; // Чисто виртуальный метод для логирования

    void logFileAdded(const QString &filePath, qint64 size) const // Метод для логирования добавления файла
    {
        log(QString("File %1 added. Size: %2").arg(filePath).arg(size)); // Логируем сообщение о добавлении файла
    }

    void logFileRemoved(const QString &filePath) const // Метод для логирования удаления файла
    {
        log(QString("File %1 has been removed from tracking.").arg(filePath)); // Логируем сообщение об удалении файла
    }

    void logFileCreated(const QString &filePath, qint64 size) const // Метод для логирования создания файла
    {
        log(QString("File %1 has been created. Current size: %2").arg(filePath).arg(size)); // Логируем сообщение о создании файла
    }

    void logFileChanged(const QString &filePath, qint64 size) const // Метод для логирования изменения файла
    {
        log(QString("File %1 has been changed. Current size: %2").arg(filePath).arg(size)); // Логируем сообщение об изменении файла
    }

    void logFileDeleted(const QString &filePath) const // Метод для логирования удаления файла
    {
        log(QString("File %1 has been deleted.").arg(filePath)); // Логируем сообщение об удалении файла
    }
};

class ConsoleLog : public Interlog
{
    Q_OBJECT
public slots:
    void log(const QString &str) const override
    {
        QTextStream cout(stdout);
        cout << str << Qt::endl; // Выводим сообщение в консоль
    }
};

#endif // LOG_H
