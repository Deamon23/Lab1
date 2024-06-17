#ifndef LOG_H
#define LOG_H

#include <QTextStream>

class Interlog
{
public:
    virtual void log(const QString &str) const = 0; // Чисто виртуальный метод для логирования
};

class ConsoleLog : public Interlog
{
public:
    void log(const QString &str) const override
    {
        QTextStream cout(stdout);
        cout << str << Qt::endl; // Выводим сообщение в консоль
    }
};

#endif // LOG_H
