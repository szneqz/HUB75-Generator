#include "imagereader.h"

ImageReader::ImageReader(QObject *parent)
    : QObject(parent)
{
}

QString calculateColorBits(int colorValue, const int t1, const int t2, const int t3)
{
    if (colorValue < t1)
        return "00";
    if (colorValue < t2)
        return "01";
    if (colorValue < t3)
        return "10";

    return "11";
}

QString ImageReader::loadAndRead(const QString &path, const int t1, const int t2, const int t3)
{
    if (t1 > t2 || t1 > t3 || t2 > t3) {
        return "Wrong color threshold values (T1 < T2 < T3)";
    }

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
                          .arg(calculateColorBits(c.blue(), t1, t2, t3))
                          .arg(calculateColorBits(c.green(), t1, t2, t3))
                          .arg(calculateColorBits(c.red(), t1, t2, t3));

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