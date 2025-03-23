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
// ClockPainter - Abstract class
//
void ClockPainter::paint(QPainter* painter, int angle, bool center) {
    painter->save();
    painter->rotate(angle);
    paintImage(painter, center);
    painter->restore();
}
    
// ----------------------------------------------------------------------------
// SvgClockPainter - SVG Clock Painter
//
class SvgClockPainter : public ClockPainter {
private:
    QSvgRenderer* svg;
public:
    SvgClockPainter(QSvgRenderer* svg) : svg(svg) {
        if (svg == nullptr) {
            return;
        }
    }
    
    ~SvgClockPainter() {
        delete svg;
    }

    QString getString(int angle = 0, bool center = true) override {
        QByteArray byteArray;
        QBuffer buffer(&byteArray);
        buffer.open(QIODevice::WriteOnly);
    
        QSvgGenerator generator;
        generator.setOutputDevice(&buffer);
    
        QPainter painter;
        painter.begin(&generator);
        paint(&painter, angle, center);
        painter.end();
    
        buffer.close();
    
        return QString::fromUtf8(byteArray);
    };

protected:
    void paintImage(QPainter* painter, bool center) override {
        QSize size = svg->defaultSize();
        QRectF rectF(-size.width() / 2, -size.height() / (center ? 1 : 2), size.width(), size.height());
        svg->render(painter, rectF.toRect());
    }
};

// ----------------------------------------------------------------------------
// BitmapClockPainter - Bitmap Clock Painter
//
class BitmapClockPainter : public ClockPainter {
private:
    QImage* image;
public:
    BitmapClockPainter(QImage* image) : image(image) {
        if (image == nullptr) {
            return;
        }
    }

    ~BitmapClockPainter() {
        delete image;
    }

    QString getString(int angle = 0, bool center = true) override {
        QByteArray byteArray;
        QBuffer buffer(&byteArray);
        buffer.open(QIODevice::WriteOnly);

        QImage tempImage(*image);
        QPainter painter(&tempImage);
        paint(&painter, angle, center);
        painter.end();
        
        tempImage.save(&buffer, "PNG");
        buffer.close();

        return "data:image/png;base64," + byteArray.toBase64();
    };

protected:
    void paintImage(QPainter* painter, bool center) override {
        QRect rect(-image->width() / 2, -image->height() / (center ? 1 : 2), image->width(), image->height());
        painter->drawImage(rect, *image);
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
