#include <QtGui>
#include "mainwindow.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    QString locale = QLocale::system().name();
    QTranslator translator;
    translator.load(QString("shema_") + locale);
    app.installTranslator(&translator);


    MainWindow* const window = new MainWindow;
    window->showMaximized();
    return app.exec();
}
