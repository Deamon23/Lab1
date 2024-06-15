#include "filemanager.h"
#include <iostream>

FileManager::FileManager(Interlog *logger)
{
    setLog(logger); // Устанавливаем логгер

    connect(this, &FileManager::upd_signal, this, &FileManager::update); // Подключаем сигнал к слоту
}

void FileManager::addFile(const QString &str)
{
    File* F = new File(str); // Создаем новый объект File
    files.push_back(F); // Добавляем объект в вектор
    if (l) { // Если логгер установлен
        l->logFileAdded(str, F->getSize()); // Логируем добавление файла
    }
}

void FileManager::removeFile(const QString &str)
{
    for (int i = 0; i < files.size(); ++i) {
        if (files[i]->getUrl() == str) { // Если URL совпадает
            delete files[i]; // Удаляем объект
            files.remove(i); // Удаляем элемент из вектора
            if (l) { // Если логгер установлен
                l->logFileRemoved(str); // Логируем удаление файла
            }
            break;
        }
    }
}

void FileManager::listFiles() const
{
    if (l) {
        l->log("Watched files:"); // Логируем заголовок списка файлов
        for (int i = 0; i < files.size(); ++i) {
            l->log(files[i]->getUrl()); // Логируем каждый файл
        }
    }
}

void FileManager::setLog(Interlog *logger)
{
    if (logger) {
        l = logger; // Устанавливаем логгер
        connect(this, &FileManager::log_signal, l, &Interlog::log); // Подключаем сигнал к методу логгера
    } else {
        std::cout << "Logger is invalid, messaging will be stopped." << std::endl; // Выводим сообщение об ошибке
    }
}

void FileManager::check()
{
    QFileInfo x;
    for (int i = 0; i < files.length(); ++i) {
        x.setFile(files[i]->getUrl()); // Устанавливаем файл для проверки
        if (x.exists() != files[i]->getExist() || x.size() != files[i]->getSize()) { // Если состояние файла изменилось
            emit upd_signal(files[i]); // Излучаем сигнал обновления
        }
    }
}

FileManager::~FileManager()
{
    for (int i = 0; i < files.size(); ++i) {
        delete files[i];
    }
}

FileManager &FileManager::Instance(Interlog* logger)
{
    static FileManager FM(logger);
    return FM;
}

void FileManager::update(File* F)
{
    QFileInfo x(F->getUrl());
    if (!F->getExist()) { // Если файл не существовал
        F->fileUpdate(); // Обновляем информацию о файле
        if (l) { // Если логгер установлен
            l->logFileCreated(F->getUrl(), F->getSize()); // Логируем создание файла
        }
    } else if (x.exists()) { // Если файл существует
        F->fileUpdate(); // Обновляем информацию о файле
        if (l) { // Если логгер установлен
            l->logFileChanged(F->getUrl(), F->getSize()); // Логируем изменение файла
        }
    } else { // Если файл был удален
        F->fileUpdate(); // Обновляем информацию о файле
        if (l) { // Если логгер установлен
            l->logFileDeleted(F->getUrl()); // Логируем удаление файла
        }
    }
}
