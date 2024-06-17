#ifndef LOGFORMATTER_H
#define LOGFORMATTER_H

#include <QString>

class LogFormatter
{
public:
    static QString formatFileAdded(const QString &filePath, qint64 size)
    {
        return QString("File %1 added. Size: %2").arg(filePath).arg(size);
    }

    static QString formatFileRemoved(const QString &filePath)
    {
        return QString("File %1 has been removed from tracking.").arg(filePath);
    }

    static QString formatFileCreated(const QString &filePath, qint64 size)
    {
        return QString("File %1 has been created. Current size: %2").arg(filePath).arg(size);
    }

    static QString formatFileChanged(const QString &filePath, qint64 size)
    {
        return QString("File %1 has been changed. Current size: %2").arg(filePath).arg(size);
    }

    static QString formatFileDeleted(const QString &filePath)
    {
        return QString("File %1 has been deleted.").arg(filePath);
    }
};

#endif // LOGFORMATTER_H
