#include "imagereader.h"

ImageReader::ImageReader(QObject *parent)
    : QObject(parent)
{
}

QString calculateColorBits(int colorValue)
{
    if (colorValue < 64)
        return "00";
    if (colorValue < 128)
        return "01";
    if (colorValue < 192)
        return "10";

    return "11";
}

QString ImageReader::loadAndRead(const QString &path)
{
    QImage img(path);
    if (img.isNull())
        return "Failed to load image";

    QString result;
    result += QString("{\n");
    for (int y = 0; y < img.height(); y++) {
        result += QString("{");
        for (int x = 0; x < img.width(); x++) {
            QColor c = img.pixelColor(x, y);

            result += QString("0b00%1%2%3")
                          .arg(calculateColorBits(c.blue()))
                          .arg(calculateColorBits(c.green()))
                          .arg(calculateColorBits(c.red()));

            if (x < img.width() - 1) result += QString(", ");
        }
        result += QString("}");
        if (y < img.height() - 1) result += QString(",\n");
    }
    result += QString("\n}");

    return result;
}

void ImageReader::copyText(const QString &text) {
    QGuiApplication::clipboard()->setText(text);
}