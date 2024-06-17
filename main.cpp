#include <QCoreApplication>
#include <QFile>
#include "filemanager.h"
#include <chrono>
#include <thread>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QTextStream cin(stdin);

    ConsoleLog l;
    FileManager& FM = FileManager::Instance(&l);

    // Вывод доступных команд
    l.log("Commands:");
    l.log("  add <file_path>   - Add file to watch");
    l.log("  remove <file_path> - Remove file from watch");
    l.log("  list              - List all watched files");
    l.log("  exit              - Exit the application");

    while (true)
    {
        l.log("Enter command: ");
        QString input = cin.readLine();
        QStringList args = input.split(" ", Qt::SkipEmptyParts); // Разделение строки на части

        if (args.isEmpty())
        {
            continue;
        }

        QString command = args[0].toLower(); // Получение команды

        if (command == "add" && args.size() == 2) // Проверка команды "add"
        {
            FM.addFile(args[1]); // Добавление файла в список наблюдения
        }
        else if (command == "remove" && args.size() == 2) // Проверка команды "remove"
        {
            FM.removeFile(args[1]); // Удаление файла из списка наблюдения
        }
        else if (command == "list") // Проверка команды "list"
        {
            FM.listFiles(); // Вывод списка файлов
        }
        else if (command == "exit") // Проверка команды "exit"
        {
            break; // Выход из цикла
        }
        else // Обработка неизвестной команды
        {
            l.log("Unknown command. Please try again."); // Вывод сообщения об ошибке
        }
    }

    while (true)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        FM.check(); // Проверяем состояние файлов
    }

    return a.exec(); // Запускаем цикл обработки событий
}

// C:/gits/test/test1.txt
