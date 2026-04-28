#include <QApplication>
#include <QFont>

#include "mainwindow.h"
#include "processmanager.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    // Enable SeDebugPrivilege to open protected processes
    ProcessManager::enableDebugPrivilege();

    QFont defaultFont(QStringLiteral("Inter"), 18);
    defaultFont.setStyleStrategy(QFont::PreferAntialias);
    app.setFont(defaultFont);

    app.setApplicationName(QStringLiteral("ProcessWarden"));
    app.setApplicationVersion(QStringLiteral("1.2.4"));
    app.setOrganizationName(QStringLiteral("ProcessWarden"));

    MainWindow w;
    w.show();

    return app.exec();
}
