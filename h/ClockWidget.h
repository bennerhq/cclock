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
    QColor hour_hand_color;
    QColor minute_hand_color;
    QColor second_hand_color;
    QColor middle_dot_color;
    QColor date_background_color;
    QColor date_text_color;
    int date_position;
    QString date_font;
};

#endif // CLOCKWIDGET_H
