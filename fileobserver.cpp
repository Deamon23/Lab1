#include "fileobserver.h"
#include <QTextStream>

// Слот для обработки изменения файлов
void FileObserver::onFileChanged(const QString& path, qint64 newSize)
{
    QTextStream qout(stdout); // Поток для вывода текста
    if (newSize == -1) // Проверка, что файл был удален или не существует
    {
        qout << "The file \"" << path << "\" was deleted or does not exist." << Qt::endl; // Вывод сообщения об удалении файла
    }
    else
    {
        qout << "The file \"" << path << "\" size has changed. New size: " << newSize << " bytes" << Qt::endl; // Вывод сообщения об изменении размера файла
    }
}
