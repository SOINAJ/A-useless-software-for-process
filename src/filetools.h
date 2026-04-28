#pragma once

#include <QString>
#include <QStringList>
#include <QVector>
#include <QFile>
#include <QTextStream>
#include <QDateTime>
#include <memory>

struct FileStreamCloser {
    void operator()(QTextStream* s) const {
        delete s->device();
        delete s;
    }
};

class FileTools {
public:
    // Read entire file as QString. Returns empty string on failure.
    static QString readText(const QString& filePath);

    // Write text to file (overwrite). Returns true on success.
    static bool writeText(const QString& filePath, const QString& content);

    // Append a timestamped line to a log file. Creates file if absent.
    static void log(const QString& filePath, const QString& message);

    // Export a container of strings to file, one entry per line.
    template<typename Container>
    static bool exportList(const QString& filePath, const Container& lines);

    // ── 新增：返回 QTextStream 缓冲流 ──

    // 打开文件并返回 QTextStream 智能指针，支持逐行/逐词操作
    // 使用方式：
    //   auto stream = FileTools::openStream("path.txt");
    //   while (!stream->atEnd()) {
    //       QString line = stream->readLine();
    //   }
    // 文件在 stream 销毁时自动关闭
    static std::unique_ptr<QTextStream, FileStreamCloser> openStream(const QString& filePath);

    // 打开文件并返回 QTextStream 引用（需配合 QFile 使用，更灵活）
    // 使用方式：
    //   QFile file;
    //   QTextStream& stream = FileTools::openStream(file, "path.txt");
    //   QString word; stream >> word;
    static QTextStream& openStream(QFile& file, const QString& filePath);
};

// ── Template implementation ──

template<typename Container>
bool FileTools::exportList(const QString& filePath, const Container& lines)
{
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return false;

    QTextStream out(&file);
    for (const auto& item : lines)
        out << item << QStringLiteral("\n");

    file.close();
    return true;
}
