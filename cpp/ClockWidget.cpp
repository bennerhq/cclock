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

#include "h/ConfigYAML.h"
#include "h/ClockWindow.h"
#include "h/ClockWidget.h"

ClockWidget::ClockWidget() : QWidget(nullptr) {
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));

    setMinimumSize(100, 100);
    setAttribute(Qt::WA_TranslucentBackground);

    dialRenderer = config_get_image(config["dial"]["decorate"]);
    dial_background_color = config_get_qcolor(config["dial"]["background_color"]);
    dial_frame_color = config_get_qcolor(config["dial"]["frame_color"]);

    hour_mark_color = config_get_qcolor(config["dial"]["hour_mark_color"]);
    minute_mark_color = config_get_qcolor(config["dial"]["minute_mark_color"]);

    date_background_color = config_get_qcolor(config["date"]["backgroud_color"]);
    date_text_color = config_get_qcolor(config["date"]["text_color"]);
    date_font = config_get_string(config["date"]["font"]);

    no_background_color = config_get_qcolor(config["numbers"]["backgroud_color"]);
    no_text_color = config_get_qcolor(config["numbers"]["text_color"]);
    no_font = config_get_string(config["numbers"]["font"]);  

    QString no_positions_str = config_get_string(config["numbers"]["positions"]);
    if (no_positions_str != "") {
        QStringList no_positions_list = no_positions_str.split(",");
        for (const QString& pos : no_positions_list) {
            no_positions.append(pos);
        }
    }

    hourHandRenderer = config_get_image(config["hands"]["hour"]);
    minuteHandRenderer = config_get_image(config["hands"]["minute"]);
    secondHandRenderer = config_get_image(config["hands"]["second"]);

    int animate_msecs = config["hands"]["animate_msecs"].as<int>();
    timer->start(animate_msecs);
}

void ClockWidget::paintEvent(QPaintEvent*) {
    QPainter painter(this);
    paintClock(&painter);
}

void ClockWidget::paintNumbers(QPainter *painter, int hour_marker, QColor background_color, QColor text_color, QString text_font, QString number) {
    int angle = 30*(hour_marker - 3); // ?
    int x = 90 * std::cos(qDegreesToRadians(static_cast<double>(angle)));
    int y = 90 * std::sin(qDegreesToRadians(static_cast<double>(angle)));
    QRect rect(x - 10, y - 10, 20, 20);

    QFont font = painter->font();
    font.setFamily(text_font);
    font.setPointSize(11);

    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(background_color);
    painter->drawRoundedRect(rect, 5, 5);
    painter->setFont(font);
    painter->setPen(QPen(text_color, 1));
    painter->drawText(rect, Qt::AlignCenter, number);
    painter->restore();
}

void ClockWidget::paintClock(QPainter* painter) {
    QTime current_time = QTime::currentTime();

    painter->setRenderHint(QPainter::Antialiasing);

    QRect rect = this->rect();
    QPoint center = rect.center();
    int radius = std::min(rect.width(), rect.height()) / 2;

    painter->translate(center);
    painter->scale(radius / 100.0, radius / 100.0);

    if (dialRenderer != nullptr) {
        dialRenderer->paint(painter, 0, 0, 0);
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

    if (hour_mark_color.isValid()) {
        QPen hour_mark_pen(hour_mark_color, 2);

        painter->save();
        painter->setPen(hour_mark_pen);
        for (int i = 0; i < 12; ++i) {
            painter->drawLine(88, 0, 96, 0);
            painter->rotate(30);
        }
        painter->restore();
    }

    if (minute_mark_color.isValid()) {
        QPen minute_mark_pen(minute_mark_color, 1);

        painter->save();
        painter->setPen(minute_mark_pen);
        for (int i = 0; i < 60; ++i) {
            if (i % 5 != 0) {
                painter->drawLine(92, 0, 96, 0);
            }
            painter->rotate(6);
        }
        painter->restore();
    }

    for (int i = 0; i < no_positions.size(); ++i) {
        QString no = no_positions[i];
        paintNumbers(painter, i + 1, no_background_color, no_text_color, no_font, no);
    }

    if (date_background_color.isValid()) {
        int date_pos = config["date"]["position"].as<int>();
        QString today = QDateTime::currentDateTime().toString("dd");
        paintNumbers(painter, date_pos, date_background_color, date_text_color, date_font, today);
    }

    hourHandRenderer->paint(painter, 30 * (current_time.hour() + current_time.minute() / 60.0));
    minuteHandRenderer->paint(painter, 6 * (current_time.minute() + current_time.second() / 60.0));
    secondHandRenderer->paint(painter, 6 * (current_time.second() + current_time.msec() / 1000.0));
}

void ClockWidget::saveAsSvg(const QString& filePath) {
    QSvgGenerator generator;
    generator.setFileName(filePath);
    generator.setSize(QSize(150, 150));

    QPainter painter;
    painter.begin(&generator);
    paintClock(&painter);
    painter.end();
}
