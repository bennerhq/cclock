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

#ifndef CLOCKWIDGET_H
#define CLOCKWIDGET_H

#include <QWidget>
#include <QColor>
#include <QPainter>
#include <QSvgRenderer>

class ClockWidget : public QWidget {
    Q_OBJECT

public:
    ClockWidget();

protected:
    void paintEvent(QPaintEvent*) override;

private:
    QTimer* timer;

    QColor dial_color;
    QColor dial_frame_color;
    QColor hour_mark_color;
    QColor minute_mark_color;
    QColor date_background_color;
    QColor date_text_color;
    int date_position;
    QString date_font;

    QSvgRenderer* hourHandRenderer;
    QSvgRenderer* minuteHandRenderer;
    QSvgRenderer* secondHandRenderer; 

    void paintHand(QPainter* painter, QSvgRenderer* renderer, int angle);
};

#endif // CLOCKWIDGET_H
