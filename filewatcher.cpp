#include "filewatcher.h"
#include <QTextStream>

// Реализация конструктора FileWatcher
FileWatcher::FileWatcher(QObject *parent)
    : QObject(parent)
{
    // Подключение сигнала таймера к слоту проверки файлов
    connect(&timer, &QTimer::timeout, this, &FileWatcher::checkFiles);
    timer.start(100); // Запуск таймера с интервалом 100 миллисекунд
}

// Метод для добавления файла в список наблюдения
void FileWatcher::addFile(const QString& path)
{
    QFileInfo fileInfo(path); // Получение информации о файле
    qint64 size = -1; // Инициализация размера файла
    if (fileInfo.exists()) // Проверка существования файла
    {
        size = fileInfo.size(); // Получение размера файла
    }
    files.insert(path, size); // Добавление файла в словарь с текущим размером или -1
    QTextStream qout(stdout); // Поток для вывода текста
    qout << "Added watch for file: \"" << path << "\"" << Qt::endl; // Вывод информации о добавленном файле
}

// Метод для удаления файла из списка наблюдения
void FileWatcher::removeFile(const QString& path)
{
    files.remove(path); // Удаление файла из словаря
}

// Метод для вывода списка файлов
void FileWatcher::listFiles() const
{
    QTextStream qout(stdout); // Поток для вывода текста
    qout << "Currently watching the following files:" << Qt::endl; // Вывод заголовка
    for (auto it = files.begin(); it != files.end(); ++it) // Цикл по всем файлам в словаре
    {
        qout << it.key() << Qt::endl; // Вывод пути каждого файла
    }
}

// Слот для проверки состояния файлов
void FileWatcher::checkFiles()
{
    for (auto it = files.begin(); it != files.end(); ++it) // Цикл по всем файлам в словаре
    {
        QFileInfo fileInfo(it.key()); // Получение информации о файле
        if (fileInfo.exists()) // Проверка существования файла
        {
            qint64 newSize = fileInfo.size(); // Получение нового размера файла
            if (newSize != it.value()) // Проверка изменения размера файла
            {
                it.value() = newSize; // Обновление размера файла в словаре
                emit fileChanged(it.key(), newSize); // Вызов сигнала об изменении файла
            }
        }
        else
        {
            if (it.value() != -1) // Проверка, что файл ранее существовал
            {
                it.value() = -1; // Обновление размера файла в словаре на -1
                emit fileChanged(it.key(), -1); // Вызов сигнала об удалении файла
            }
        }
    }
}
