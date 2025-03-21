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

#ifndef CLOCKPAINTER_H
#define CLOCKPAINTER_H

#include <QPainter>
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

class ClockPainter {
public:
    virtual void paint(QPainter* painter, int angle, bool center) = 0;
    virtual ~ClockPainter() {}

    virtual QString getString(int angle = 0, bool center = true) = 0; 
};

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

    void paint(QPainter* painter, int angle, bool center) override {
        QSize size = svg->defaultSize();
        QRectF rectF(-size.width() / 2, -size.height() / (center ? 1 : 2), size.width(), size.height());
        QRect rect = rectF.toRect();

        painter->save();
        painter->rotate(angle);
        svg->render(painter, rect);
        painter->restore();
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
};

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

    void paint(QPainter* painter, int angle, bool center) override {
        QRect rect(-image->width() / 2, -image->height() / (center ? 1 : 2), image->width(), image->height());

        painter->save();
        painter->rotate(angle);
        painter->drawImage(rect, *image);
        painter->restore();
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
};

#endif // CLOCKPAINTER_H
