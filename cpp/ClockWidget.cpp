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
#include <QSvgGenerator>
#include <QDebug>

#include "h/Config.h"
#include "h/ClockWindow.h"
#include "h/ClockWidget.h"

ClockWidget::ClockWidget() : QWidget(nullptr) {
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));

    setMinimumSize(100, 100);
    setAttribute(Qt::WA_TranslucentBackground);

    dialPainter = factoryClockPainter("dial.background");
    dial_background_color = config_get_color("dial.background_color");
    dial_frame_color = config_get_color("dial.frame_color");

    minuteMarkerPainter = factoryClockPainter("dial.minute_marker");
    hourMarkerPainter = factoryClockPainter("dial.hour_marker");

    date_position = config_get_int("date.position");
    QString no_positions_str = config_get_string("numbers.positions");
    if (no_positions_str != "") {
        QStringList no_positions_list = no_positions_str.split(",");
        for (const QString& pos : no_positions_list) {
            no_positions.append(pos);
        }
    }

    hourHandPainter = factoryClockPainter("hands.hour");
    minuteHandPainter = factoryClockPainter("hands.minute");
    secondHandPainter = factoryClockPainter("hands.second");

    int animate_msecs = config_get_int("hands.animate_msecs");
    timer->start(animate_msecs);
}

void ClockWidget::paintEvent(QPaintEvent*) {
    QPainter painter(this);
    paintClock(&painter);
}

void ClockWidget::paintNumbers(QPainter *painter, const QString root, int hour_pos, QString number) {
    QColor no_background_color = config_get_color(root + ".backgroud_color");
    QColor no_text_color = config_get_color(root + ".text_color");
    QString no_font = config_get_string(root + ".font");
    int no_font_size = config_get_int(root + ".font_size");

    int angle = 30*(hour_pos - 3); // ?
    int x = 90 * std::cos(qDegreesToRadians(static_cast<double>(angle)));
    int y = 90 * std::sin(qDegreesToRadians(static_cast<double>(angle)));
    QRect rect(x - 10, y - 10, 20, 20);

    QFont font = painter->font();
    font.setFamily(no_font);
    font.setPointSize(no_font_size);

    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(no_background_color);
    painter->drawRoundedRect(rect, 5, 5);
    painter->setFont(no_font);
    painter->setPen(QPen(no_text_color, 1));
    painter->drawText(rect, Qt::AlignCenter, number);
    painter->restore();
}

void ClockWidget::paintClock(QPainter* painter) {
    QTime current_time = QTime::currentTime();

    QRect rect = this->rect();
    QPoint center = rect.center();
    int radius = std::min(rect.width(), rect.height()) / 2;

    painter->setRenderHint(QPainter::Antialiasing);
    painter->translate(center);
    painter->scale(radius / 100.0, radius / 100.0);

    if (dialPainter != nullptr) {
        dialPainter->paint(painter, 0, false);
    }

    if (dial_background_color.isValid()) {
        painter->save();
        painter->setBrush(dial_background_color);
        painter->setPen(Qt::NoPen);
        painter->drawEllipse(-100, -100, 200, 200);
        painter->restore();
    }

    if (dial_frame_color.isValid()) {
        painter->save();
        painter->setPen(QPen(dial_frame_color, 3));
        painter->setBrush(Qt::NoBrush);
        painter->drawEllipse(-99, -99, 198, 198);
        painter->restore();
    }

    if (hourMarkerPainter != nullptr) {
        for (int i = 0; i < 12; ++i)
            hourMarkerPainter->paint(painter, 30 * i, true);
    }

    if (minuteMarkerPainter != nullptr) {
        for (int i = 0; i < 60; ++i) {
            if (i % 5 != 0) {
                minuteMarkerPainter->paint(painter, 6 * i, true);
            }
        }
    }

    for (int i = 0; i < no_positions.size(); ++i) {
        QString no = no_positions[i];
        paintNumbers(painter, "numbers", i + 1, no);
    }

    if (date_position) {
        int date_pos = config_get_int("date.position");
        QString today = QDateTime::currentDateTime().toString("dd");
        paintNumbers(painter, "date", date_pos, today);
    }

    if (hourHandPainter != nullptr) {
        hourHandPainter->paint(painter, 30 * (current_time.hour() + current_time.minute() / 60.0), true);
    }
    if (minuteHandPainter != nullptr) {
        minuteHandPainter->paint(painter, 6 * (current_time.minute() + current_time.second() / 60.0), true);
    }
    if (secondHandPainter != nullptr) {
        secondHandPainter->paint(painter, 6 * (current_time.second() + current_time.msec() / 1000.0), true);
    }
}

void ClockWidget::saveAsSvg(const QString& filePath) {
    QSvgGenerator generator;
    generator.setFileName(filePath);
    generator.setSize(QSize(200, 200));

    QPainter painter;
    painter.begin(&generator);
    paintClock(&painter);
    painter.end();
}
