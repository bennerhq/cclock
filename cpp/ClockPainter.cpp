// ----------------------------------------------------------------------------
// "THE BEER-WARE LICENSE" (Revision 43):
//
// Github Co-pilot & <jens@bennerhq.com> wrote this file.  As long as you 
// retain this notice you can do whatever you want with this stuff. If we meet 
// some day, and you think this stuff is worth it, you can buy me a beer in 
// return.   
//
// /benner
// ----------------------------------------------------------------------------

#include <QSvgRenderer>
#include <QSvgGenerator>
#include <QImage>
#include <QBuffer>
#include <QByteArray>
#include <QString>
#include <QRect>
#include <QRectF>
#include <QSize>
#include <QPoint>
#include <QDebug>
#include "h/Config.h"
#include "h/ClockPainter.h"

// ----------------------------------------------------------------------------
// SvgClockPainter - SVG Clock Painter
//
class SvgClockPainter : public ClockPainter {
private:
    QSvgRenderer* svg;

    ~SvgClockPainter() {
        delete svg;
    }

public:
    SvgClockPainter(QSvgRenderer* svg) : svg(svg) {
        if (svg == nullptr) {
            return;
        }
    }
    
    void paint(QPainter* painter, int angle, bool center) override {
        painter->save();
        painter->rotate(angle);

        QSize size = svg->defaultSize();
        QRect rect(-size.width() / 2, -size.height() / (center ? 1 : 2), size.width(), size.height());
        svg->render(painter, rect);

        painter->restore();
    }
};

// ----------------------------------------------------------------------------
// BitmapClockPainter - Bitmap Clock Painter
//
class BitmapClockPainter : public ClockPainter {
private:
    QImage* image;

    ~BitmapClockPainter() {
        delete image;
    }

public:
    BitmapClockPainter(QImage* image) : image(image) {
        if (image == nullptr) {
            return;
        }
    }

    void paint(QPainter* painter, int angle, bool center) override {
        painter->save();
        painter->rotate(angle);

        QRect rect(-image->width() / 2, -image->height() / (center ? 1 : 2), image->width(), image->height());
        painter->drawImage(rect, *image);

        painter->restore();
    }
};

// ----------------------------------------------------------------------------
// factoryClockPainter - Factory method for creating ClockPainter
//
ClockPainter* factoryClockPainter(const QString& key) {
    QString data_str = config_get_image(key);
    if (data_str.isEmpty()) {
        return nullptr;
    }

    if (data_str.startsWith("data:image/")) {
        int index = data_str.indexOf("base64,");
        if (index != -1) {
            data_str.remove(0, index + QString("base64,").length());
        }

        QByteArray byteArray = QByteArray::fromBase64(data_str.toUtf8());
        QImage* image = new QImage();
        image->loadFromData(byteArray);
        if (!image->isNull()) {
            return new BitmapClockPainter(image);
        }
        delete image;
    }
    else {
        QSvgRenderer* svg = new QSvgRenderer(data_str.toUtf8());
        if (svg->isValid()) {
            return new SvgClockPainter(svg);
        }
        delete svg;
    }

    return nullptr;
}
