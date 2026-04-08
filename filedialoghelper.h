#pragma once

#include <QObject>
#include <QString>

class FileDialogHelper : public QObject
{
    Q_OBJECT
public:
    explicit FileDialogHelper(QObject *parent = nullptr);

    // Opens native file dialog and returns selected file path
    Q_INVOKABLE QString openFile(const QString &title = "Select file",
                                 const QString &filter = "Images (*.png *.jpg *.bmp)");
};