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
#include <QColor>
#include <QtMath>

#include "h/ConfigYAML.h"
#include "h/ClockWindow.h"
#include "h/ClockWidget.h"

ClockWidget::ClockWidget() : QWidget(nullptr) {
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));

    setMinimumSize(100, 100);
    setAttribute(Qt::WA_TranslucentBackground);

    dial_color = config_qcolor(config["colors"]["dial"]);
    dial_frame_color = config_qcolor(config["colors"]["dial_frame"]);
    hour_mark_color = config_qcolor(config["colors"]["hour_mark"]);
    minute_mark_color = config_qcolor(config["colors"]["minute_mark"]);
    hour_hand_color = config_qcolor(config["colors"]["hour_hand"]);
    minute_hand_color = config_qcolor(config["colors"]["minute_hand"]);
    second_hand_color = config_qcolor(config["colors"]["second_hand"]);
    middle_dot_color = config_qcolor(config["colors"]["middle_dot"]);
    date_background_color = config_qcolor(config["colors"]["date_background"]);
    date_text_color = config_qcolor(config["colors"]["date_text"]);
    date_font = config["colors"]["date_font"].as<std::string>().c_str();

    QString animate = config["window"]["animate"].as<std::string>().c_str();
    if (animate == "float") {
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
    if (dial_color.isValid()) {
        painter.save();
        painter.setBrush(dial_color);
        painter.setPen(Qt::NoPen);
        painter.drawEllipse(-100, -100, 200, 200);
        painter.restore();
    }

    // Draw dial frame
    if (dial_frame_color.isValid()) {
        painter.save();
        painter.setPen(QPen(dial_frame_color, 3));
        painter.setBrush(Qt::NoBrush);
        painter.drawEllipse(-99, -99, 198, 198);
        painter.restore();
    }

    // Draw hour marks
    if (hour_mark_color.isValid()) {
        QPen hour_mark_pen(hour_mark_color, 2);

        painter.save();
        painter.setPen(hour_mark_pen);
        for (int i = 0; i < 12; ++i) {
            painter.drawLine(88, 0, 96, 0);
            painter.rotate(30);
        }
        painter.restore();
    }

    // Draw minute marks
    if (minute_mark_color.isValid()) {
        QPen minute_mark_pen(minute_mark_color, 1);

        painter.save();
        painter.setPen(minute_mark_pen);
        for (int i = 0; i < 60; ++i) {
            if (i % 5 != 0) {
                painter.drawLine(92, 0, 96, 0);
            }
            painter.rotate(6);
        }
        painter.restore();
    }

    // Draw day number at 15:00 o'clock
    if (date_background_color.isValid()) {
        int hour_marker = config["colors"]["date_position"].as<int>();
        int angle = hour_marker * 30 - 30*3; // ?
        int x = 90 * std::cos(qDegreesToRadians(static_cast<double>(angle)));
        int y = 90 * std::sin(qDegreesToRadians(static_cast<double>(angle)));
        QRect rect(x - 10, y - 10, 20, 20);
        QString today = QDateTime::currentDateTime().toString("dd");

        QFont font = painter.font();
        font.setFamily(date_font);
        font.setPointSize(11);

        painter.save();
        painter.setPen(Qt::NoPen);
        painter.setBrush(date_background_color);
        painter.drawRoundedRect(rect, 5, 5);
        painter.setFont(font);
        painter.setPen(QPen(date_text_color, 1));
        painter.drawText(rect, Qt::AlignCenter, today);
        painter.restore();
    }

    // Draw hour hand
    if (hour_hand_color.isValid()) {
        QPen hour_hand_pen(hour_hand_color, 6, Qt::SolidLine, Qt::RoundCap);

        painter.save();
        painter.setPen(hour_hand_pen);
        painter.rotate(30 * (current_time.hour() + current_time.minute() / 60.0));
        painter.drawLine(0, 0, 0, -50);
        painter.restore();
    }

    // Draw minute hand
    if (minute_hand_color.isValid()) {
        QPen minute_hand_pen(minute_hand_color, 4, Qt::SolidLine, Qt::RoundCap);

        painter.save();
        painter.setPen(minute_hand_pen);
        painter.rotate(6 * (current_time.minute() + current_time.second() / 60.0));
        painter.drawLine(0, 0, 0, -70);
        painter.restore();
    }

    // Draw second hand
    if (second_hand_color.isValid()) {
        qreal seconds_with_fraction = current_time.second() + current_time.msec() / 1000.0;
        QPen second_hand_pen(second_hand_color, 2, Qt::SolidLine, Qt::RoundCap);

        painter.save();
        painter.setPen(second_hand_pen);
        painter.rotate(6 * seconds_with_fraction);
        painter.drawLine(0, 0, 0, -90);
        painter.restore();
    }

    // Draw center circle on top of all hands
    if (middle_dot_color.isValid()) {
        painter.save();
        painter.setBrush(middle_dot_color);
        painter.setPen(Qt::NoPen);
        painter.drawEllipse(-5, -5, 10, 10);
        painter.restore();
    }
}
