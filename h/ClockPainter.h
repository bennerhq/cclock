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

class ClockPainter {
public:
    virtual void paint(QPainter* painter, int angle) = 0;
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

    void paint(QPainter* painter, int angle) override {
        QSize size = svg->defaultSize();
        QRectF rectF(-size.width() / 2, -size.height(), size.width(), size.height());
        QRect rect = rectF.toRect();

        painter->save();
        painter->rotate(angle);
        svg->render(painter, rect);
        painter->restore();
    }
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

    void paint(QPainter* painter, int angle) override {
        QRect rect(-image->width() / 2, -image->height() / 2, image->width(), image->height());

        painter->save();
        painter->rotate(angle);
        painter->drawImage(rect, *image);
        painter->restore();
    }
};    
        
#endif // CLOCKPAINTER_H
