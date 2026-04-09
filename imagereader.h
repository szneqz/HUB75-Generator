#pragma once

#include <QObject>
#include <QString>
#include <QImage>
#include <QColor>
#include <QGuiApplication>
#include <QClipboard>

class ImageReader : public QObject
{
    Q_OBJECT

public:
    explicit ImageReader(QObject *parent = nullptr);

    Q_INVOKABLE QString loadAndRead(const QString &path, const int t1, const int t2, const int t3);
    Q_INVOKABLE void copyText(const QString &text);
};