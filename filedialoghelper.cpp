#include "filedialoghelper.h"
#include <QFileDialog>
#include <QGuiApplication>

FileDialogHelper::FileDialogHelper(QObject *parent)
    : QObject(parent)
{
}

QString FileDialogHelper::openFile(const QString &title, const QString &filter)
{
    QString fileName = QFileDialog::getOpenFileName(
        nullptr,          // no parent, will create a top-level dialog
        title,            // dialog title
        QString(),        // initial directory
        filter            // file filter
        );

    return fileName;      // returns empty string if user cancels
}