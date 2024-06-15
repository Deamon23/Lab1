#include "file.h"

File::File(const QString &str) : url(str) // Инициализируем URL файла
{
    QFileInfo q(url);
    exist = q.exists();
    size = q.size();
}

void File::fileUpdate() // Метод для обновления информации о файле
{
    QFileInfo q(url);
    exist = q.exists();
    size = q.size();
}

QString File::getUrl() const
{
    return url;
}

qint64 File::getSize() const
{
    return size;
}

bool File::getExist() const
{
    return exist;
}
