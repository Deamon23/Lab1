#ifndef FILEWATCHER_H
#define FILEWATCHER_H

#include <QObject>
#include <QFileInfo>
#include <QTimer>
#include <QMap>

// Класс FileWatcher для наблюдения за изменениями файлов
class FileWatcher : public QObject
{
    Q_OBJECT

public:
    explicit FileWatcher(QObject *parent = nullptr); // Конструктор
    void addFile(const QString& path); // Метод для добавления файла в список наблюдения
    void removeFile(const QString& path); // Метод для удаления файла из списка наблюдения
    void listFiles() const; // Метод для вывода списка файлов

signals:
    void fileChanged(const QString& path, qint64 newSize); // Сигнал об изменении файла

private slots:
    void checkFiles(); // Слот для проверки состояния файлов

private:
    QMap<QString, qint64> files; // Qmap для хранения путей файлов и их размеров
    QTimer timer; // Таймер для периодической проверки файлов
};

#endif // FILEWATCHER_H
