// FileTools.cpp

#include "FileTools.h"
#include <QDebug>

QString FileTools::readText(const QString& filePath)
{
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return QString();

    QTextStream in(&file);
    #if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
        in.setCodec("UTF-8");
    #else
        in.setEncoding(QStringConverter::Utf8);
    #endif

    QString content = in.readAll();
    file.close();
    return content;
}

bool FileTools::writeText(const QString& filePath, const QString& content)
{
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return false;

    QTextStream out(&file);
    out << content;
    file.close();
    return true;
}

void FileTools::log(const QString& filePath, const QString& message)
{
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text))
        return;

    QTextStream out(&file);
    QString timestamp = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    out << QStringLiteral("[%1] %2\n").arg(timestamp, message);
    file.close();
}

// ── 新增实现 ──

std::unique_ptr<QTextStream, FileStreamCloser> FileTools::openStream(const QString& filePath)
{
    auto* file = new QFile(filePath);
    if (!file->open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "openStream failed:" << file->errorString();
        delete file;
        return nullptr;
    }

    auto* stream = new QTextStream(file);
    #if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
        stream->setCodec("UTF-8");
    #else
        stream->setEncoding(QStringConverter::Utf8);
    #endif

    return std::unique_ptr<QTextStream, FileStreamCloser>(stream);
}

QTextStream& FileTools::openStream(QFile& file, const QString& filePath)
{
    file.setFileName(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "openStream failed:" << file.errorString();
        // 返回一个静态空流（应急），建议调用前检查 file.isOpen()
        static QTextStream empty;
        return empty;
    }

    static QTextStream stream;  // 注意：这个写法有线程安全问题
    stream.setDevice(&file);
    #if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
        stream.setCodec("UTF-8");
    #else
        stream.setEncoding(QStringConverter::Utf8);
    #endif

    return stream;
}
