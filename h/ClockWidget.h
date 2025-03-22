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

#include "h/Config.h"
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

    int date_position;
    QColor date_background_color;
    QVector<QString> no_positions;

    ClockPainter* minuteMarkerRenderer; 
    ClockPainter* hourMarkerRenderer; 

    ClockPainter* dialRenderer;
    ClockPainter* hourHandRenderer;
    ClockPainter* minuteHandRenderer;
    ClockPainter* secondHandRenderer; 

    void paintNumbers(QPainter *painter, const QString root, int hour_pos, QString number);
    void paintClock(QPainter* painter);

    void saveAsSvg(const QString& filePath);
};

#endif // CLOCKWIDGET_H
