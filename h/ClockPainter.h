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
    virtual void paint(QPainter* painter, int angle, bool center) = 0;
    static ClockPainter* factory(const QString& key);
};

#endif // CLOCKPAINTER_H
