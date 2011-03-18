#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ui_schema.h"

class MainWindow : public QMainWindow,
                   private Ui::SchemaMainWindow
{
    Q_OBJECT

  public:
    MainWindow();

  private Q_SLOTS:
    void schemaSelected();
    void fileOpen();
    void fileSave();
    void fileOpenSchema();
    void validate();
    void textChanged();
    void about();

  private:
    void moveCursor(int line, int column);
    bool localEncoding;
};
#endif
