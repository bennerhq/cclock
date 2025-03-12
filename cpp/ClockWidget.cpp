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


#include <QTimer>
#include <QDateTime>
#include <QPen>
#include <QFont>

#include "h/ConfigYAML.h"
#include "h/ClockWindow.h"
#include "h/ClockWidget.h"

ClockWidget::ClockWidget() : QWidget(nullptr) {
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));

    setMinimumSize(100, 100);
    setAttribute(Qt::WA_TranslucentBackground);

    dial_color = config_get_qcolor("colors.dial");
    hour_mark_color = config_get_qcolor("colors.hour_mark");
    minute_mark_color = config_get_qcolor("colors.minute_mark");
    hour_hand_color = config_get_qcolor("colors.hour_hand");
    minute_hand_color = config_get_qcolor("colors.minute_hand");
    second_hand_color = config_get_qcolor("colors.second_hand");
    date_background_color = config_get_qcolor("colors.date_background");
    date_color = config_get_qcolor("colors.date");
    date_font = config_get_str("colors.date_font");

    if (second_hand_color.alpha() != 0) {
        timer->start(100);  // Update every 100 milliseconds
    } else {
        timer->start(1000); // Update every second
    }
}

void ClockWidget::paintEvent(QPaintEvent*) {
    QTime current_time = QTime::currentTime();

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QRect rect = this->rect();
    QPoint center = rect.center();
    int radius = std::min(rect.width(), rect.height()) / 2;

    painter.translate(center);
    painter.scale(radius / 100.0, radius / 100.0);

    // Draw dial background
    if (dial_color.alpha() != 0) {
        painter.setBrush(dial_color);
        painter.setPen(Qt::NoPen);
        painter.drawEllipse(-100, -100, 200, 200);
    }

    // Draw hour marks
    if (hour_mark_color.alpha() != 0) {
        QPen hour_mark_pen(hour_mark_color, 2);
        painter.setPen(hour_mark_pen);
        for (int i = 0; i < 12; ++i) {
            painter.drawLine(88, 0, 96, 0);
            painter.rotate(30);
        }
    }

    // Draw minute marks
    if (minute_mark_color.alpha() != 0) {
        QPen minute_mark_pen(minute_mark_color, 1);
        painter.setPen(minute_mark_pen);
        for (int i = 0; i < 60; ++i) {
            if (i % 5 != 0) {
                painter.drawLine(92, 0, 96, 0);
            }
            painter.rotate(6);
        }
    }

    // Draw day number at 15:00 o'clock
    if (date_background_color.alpha() != 0) {
        QRect rect(80, -10, 20, 20);
        QString today = QDateTime::currentDateTime().toString("dd");

        painter.setPen(Qt::NoPen);
        painter.setBrush(date_background_color);
        painter.save();
        painter.drawRoundedRect(rect, 5, 5);
        painter.restore();

        painter.setPen(QPen(date_color, 1));

        QFont font = painter.font();
        font.setFamily(date_font);
        font.setPointSize(10);
        painter.setFont(font);
        painter.save();
        painter.drawText(rect, Qt::AlignCenter, today);
        painter.restore();
    }

    // Draw hour hand
    if (hour_hand_color.alpha() != 0) {
        QPen hour_hand_pen(hour_hand_color, 6, Qt::SolidLine, Qt::RoundCap);
        painter.setPen(hour_hand_pen);
        painter.save();
        painter.rotate(30 * (current_time.hour() + current_time.minute() / 60.0));
        painter.drawLine(0, 0, 0, -50);
        painter.restore();
    }

    // Draw minute hand
    if (minute_hand_color.alpha() != 0) {
        QPen minute_hand_pen(minute_hand_color, 4, Qt::SolidLine, Qt::RoundCap);
        painter.setPen(minute_hand_pen);
        painter.save();
        painter.rotate(6 * (current_time.minute() + current_time.second() / 60.0));
        painter.drawLine(0, 0, 0, -70);
        painter.restore();
    }

    // Draw second hand
    if (second_hand_color.alpha() != 0) {
        QPen second_hand_pen(second_hand_color, 2, Qt::SolidLine, Qt::RoundCap);
        painter.setPen(second_hand_pen);
        painter.save();
        qreal seconds_with_fraction = current_time.second() + current_time.msec() / 1000.0;
        painter.rotate(6 * seconds_with_fraction);
        painter.drawLine(0, 0, 0, -90);
        painter.restore();
    }
}