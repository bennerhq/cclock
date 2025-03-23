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

#include <QString>
#include <QPainter>

class ClockPainter {
public:
    virtual ~ClockPainter() {}

    void paint(QPainter* painter, int angle, bool center);
    virtual QString getString(int angle = 0, bool center = true) = 0; 

protected:
    virtual void paintImage(QPainter* painter, bool center) = 0;
};

ClockPainter* factoryClockPainter(const QString& key);

#endif // CLOCKPAINTER_H
