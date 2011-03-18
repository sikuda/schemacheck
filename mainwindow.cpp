#include <QtGui>
#include <QtXmlPatterns>

#include "mainwindow.h"
#include "xmlsyntaxhighlighter.h"

class MessageHandler : public QAbstractMessageHandler
{
public:
    MessageHandler()
        : QAbstractMessageHandler(0)
    {
    }

    QString statusMessage() const
    {
        return m_description;
    }

    int line() const
    {
        return m_sourceLocation.line();
    }

    int column() const
    {
        return m_sourceLocation.column();
    }

protected:
    virtual void handleMessage(QtMsgType type, const QString &description,
                               const QUrl &identifier, const QSourceLocation &sourceLocation)
    {
        Q_UNUSED(type);
        Q_UNUSED(identifier);

        m_messageType = type;
        m_description = description;
        m_sourceLocation = sourceLocation;
    }

private:
    QtMsgType m_messageType;
    QString m_description;
    QSourceLocation m_sourceLocation;
};

MainWindow::MainWindow()
{
    setupUi(this);
    localEncoding = false;

    new XmlSyntaxHighlighter(schemaView->document());

    connect(validateButton, SIGNAL(clicked()), SLOT(validate()));
    connect(instanceEdit, SIGNAL(textChanged()), SLOT(textChanged()));
    validationStatus->setAlignment(Qt::AlignCenter | Qt::AlignVCenter);

    //file - open, save
    QMenu *menu = new QMenu(tr("&File"), this);
    menuBar()->addMenu(menu);
    QAction* actionOpen = new QAction(QIcon::fromTheme("document-open"), tr("&Open file..."), this);
    actionOpen->setShortcut(QKeySequence::Open);
    connect(actionOpen, SIGNAL(triggered()), this, SLOT(fileOpen()));
    menu->addAction(actionOpen);
    QAction* actionSave = new QAction(QIcon::fromTheme("document-save"), tr("&Save file..."), this);
    actionOpen->setShortcut(QKeySequence::Save);
    connect(actionSave, SIGNAL(triggered()), this, SLOT(fileSave()));
    menu->addAction(actionSave);
    menu->addSeparator();

    //file - open schema
    QAction* actionOpenSchema = new QAction(tr("&Open schema..."), this);
    connect(actionOpenSchema, SIGNAL(triggered()), this, SLOT(fileOpenSchema()));
    menu->addAction(actionOpenSchema);

    //file - close
    menu->addSeparator();
    QAction* actionClose = new QAction(tr("&Quit"), this);
    actionClose->setShortcut(Qt::CTRL + Qt::Key_Q);
    connect(actionClose, SIGNAL(triggered()), this, SLOT(close()));
    menu->addAction(actionClose);

    //help
    QMenu *helpMenu = new QMenu(tr("Help"), this);
    menuBar()->addMenu(helpMenu);
    helpMenu->addAction(tr("About"), this, SLOT(about()));
    helpMenu->addAction(tr("About &Qt"), qApp, SLOT(aboutQt()));

    progressBar->setMinimum(0);
    progressBar->setMaximum(100);
    progressBar->reset();
    schemaSelected();
}

void MainWindow::schemaSelected()
{
    textChanged();
    QFile schemaFile(QString(":/schema.xsd").arg(0));
    schemaFile.open(QIODevice::ReadOnly);
    const QString schemaText(QString::fromUtf8(schemaFile.readAll()));
    schemaView->setPlainText(schemaText);
}

void MainWindow::validate()
{
    QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
    validationStatus->setText(tr("not validated"));
    const QByteArray schemaData = schemaView->toPlainText().toUtf8();
    const QByteArray instanceData = instanceEdit->toPlainText().toUtf8();

    MessageHandler messageHandler;

    QXmlSchema schema;
    schema.setMessageHandler(&messageHandler);

    schema.load(schemaData);

    bool errorOccurred = false;
    if (!schema.isValid()) {
        errorOccurred = true;
    } else {
        QXmlSchemaValidator validator(schema);
        if (!validator.validate(instanceData))
            errorOccurred = true;
    }

    if (errorOccurred) {
        validationStatus->setText(messageHandler.statusMessage());
        moveCursor(messageHandler.line(), messageHandler.column());
    } else {
        validationStatus->setText(tr("validation successful"));
    }

    const QString styleSheet = QString("QLabel {background: %1; padding: 3px}")
                               .arg(errorOccurred ? QColor(Qt::red).lighter(160).name() :
                                    QColor(Qt::green).lighter(160).name());
    validationStatus->setStyleSheet(styleSheet);
    QApplication::restoreOverrideCursor();
}

void MainWindow::textChanged()
{
    instanceEdit->setExtraSelections(QList<QTextEdit::ExtraSelection>());
}

void MainWindow::moveCursor(int line, int column)
{
    instanceEdit->moveCursor(QTextCursor::Start);
    for (int i = 1; i < line; ++i)
        instanceEdit->moveCursor(QTextCursor::Down);

    for (int i = 1; i < column; ++i)
        instanceEdit->moveCursor(QTextCursor::Right);

    QList<QTextEdit::ExtraSelection> extraSelections;
    QTextEdit::ExtraSelection selection;

    const QColor lineColor = QColor(Qt::red).lighter(160);
    selection.format.setBackground(lineColor);
    selection.format.setProperty(QTextFormat::FullWidthSelection, true);
    selection.cursor = instanceEdit->textCursor();
    selection.cursor.clearSelection();
    extraSelections.append(selection);
    instanceEdit->setExtraSelections(extraSelections);
    instanceEdit->setFocus();
}

void MainWindow::fileOpen()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File..."), QString(), tr("XML-Files (*.xml)"));
    if (!fileName.isEmpty())
    {
        if (!QFile::exists(fileName))
            return;
        QFile file(fileName);
        if (!file.open(QFile::ReadOnly | QFile::Text))
            return;

        QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
        instanceEdit->clear();
        instanceEdit->setUpdatesEnabled(false);;
        instanceEdit->textCursor().setVisualNavigation(false);
        qint64 size = file.size();
        qint64 readSize = 0;
        qint64 blockSize = 8096*16;
        progressBar->setMaximum(size);
        QByteArray data = file.readLine(blockSize);
        while(data.size() > 0){
            instanceEdit->textCursor().movePosition(QTextCursor::End);
            if( localEncoding ) instanceEdit->textCursor().insertText(QString::fromLocal8Bit(data, data.size()));
            else instanceEdit->textCursor().insertText(QString::fromUtf8(data, data.size()));
            data = file.readLine(blockSize);
            readSize += data.size();
            progressBar->setValue(readSize);
            QApplication::processEvents();
        }
        progressBar->reset();
        instanceEdit->textCursor().setVisualNavigation(true);
        instanceEdit->setUpdatesEnabled(true);
        QApplication::restoreOverrideCursor();
        validationStatus->setText(tr("not validated"));

        //new XmlSyntaxHighlighter(instanceEdit->document());
        //validate();
    }
}

void MainWindow::fileSave()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Open File..."), QString(), tr("XML-Files (*.xml)"));
    if (!fileName.isEmpty())
    {
        QFile file(fileName);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            if( localEncoding ) file.write(instanceEdit->toPlainText().toLocal8Bit());
            else file.write(instanceEdit->toPlainText().toUtf8());
        }
    }
}

void MainWindow::fileOpenSchema()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open schema file..."), QString(), tr("xml-schema-files(*.xsd *.xml)"));
    if (!fileName.isEmpty())
    {
        if (!QFile::exists(fileName))
            return;
        QFile file(fileName);
        if (!file.open(QFile::ReadOnly | QFile::Text))
            return;
        QByteArray firstLine = file.readLine();
        if( firstLine.indexOf("windows-1251") != -1 ){
            localEncoding = true;
            file.seek(0);
            const QString schemaText(QString::fromLocal8Bit(file.readAll()));
            schemaView->setPlainText(schemaText);
        }
        else{
            localEncoding = false;
            file.seek(0);
            const QString schemaText(QString::fromUtf8(file.readAll()));
            schemaView->setPlainText(schemaText);
        }

    }
}

void MainWindow::about()
{
    QMessageBox::about(this, tr("About"), tr("This application check your XML files"
                                             "to load system of Personal. e-mail: sikuda@yandex.ru"));
}
