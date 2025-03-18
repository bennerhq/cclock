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

#include <QVector>
#include <QWidget>
#include <QColor>
#include <QPainter>
#include <QSvgRenderer>

#include "h/ClockPainter.h"

class ClockWidget : public QWidget {
    Q_OBJECT

public:
    ClockWidget();

protected:
    void paintEvent(QPaintEvent*) override;

private:
    QTimer* timer;

    QColor dial_background_color;
    QColor dial_frame_color;

    QColor hour_mark_color;
    QColor minute_mark_color;

    QColor date_background_color;
    QColor date_text_color;

    int date_position;
    QString date_font;

    QVector<QString> no_positions;
    QColor no_background_color;
    QColor no_text_color;
    QString no_font;

    ClockPainter* dialRenderer;
    ClockPainter* hourHandRenderer;
    ClockPainter* minuteHandRenderer;
    ClockPainter* secondHandRenderer; 

    void paintClock(QPainter* painter);
    void paintNumbers(QPainter *painter, int hour_marker, QColor background_color, QColor text_color, QString font, QString number);
    void saveAsSvg(const QString& filePath);
};

#endif // CLOCKWIDGET_H
