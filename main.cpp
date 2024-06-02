#include <QCoreApplication>
#include <QTextStream>
#include "filewatcher.h"
#include "fileobserver.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv); // Создание объекта приложения

    QTextStream qin(stdin); // Поток для ввода текста
    QTextStream qout(stdout); // Поток для вывода текста

    FileWatcher watcher; // Создание объекта FileWatcher
    FileObserver observer; // Создание объекта FileObserver

    // Подключение сигнала об изменении файла к слоту обработки изменения файла
    QObject::connect(&watcher, &FileWatcher::fileChanged, &observer, &FileObserver::onFileChanged);

    // Вывод доступных команд
    qout << "Commands:" << Qt::endl;
    qout << "  add <file_path>   - Add file to watch" << Qt::endl;
    qout << "  remove <file_path> - Remove file from watch" << Qt::endl;
    qout << "  list              - List all watched files" << Qt::endl;
    qout << "  exit              - Exit the application" << Qt::endl;

    while (true) // Бесконечный цикл для обработки команд
    {
        qout << "Enter command: "; // Вывод приглашения для ввода команды
        qout.flush(); // Очистка буфера вывода
        QString input = qin.readLine(); // Чтение введенной строки
        QStringList args = input.split(" ", Qt::SkipEmptyParts); // Разделение строки на части

        if (args.isEmpty()) // Проверка, что строка не пустая
        {
            continue;
        }

        QString command = args[0].toLower(); // Получение команды (toLower понижает регистр)

        if (command == "add" && args.size() == 2) // Проверка команды "add"
        {
            watcher.addFile(args[1]); // Добавление файла в список наблюдения
        }
        else if (command == "remove" && args.size() == 2) // Проверка команды "remove"
        {
            watcher.removeFile(args[1]); // Удаление файла из списка наблюдения
        }
        else if (command == "list") // Проверка команды "list"
        {
            watcher.listFiles(); // Вывод списка файлов
        }
        else if (command == "exit") // Проверка команды "exit"
        {
            break; // Выход из цикла
        }
        else // Обработка неизвестной команды
        {
            qout << "Unknown command. Please try again." << Qt::endl; // Вывод сообщения об ошибке
        }
    }
    return a.exec();
}

// C:/gits/Lab1/test1.txt
