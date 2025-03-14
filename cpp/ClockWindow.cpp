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

#include <QScreen>
#include <QGuiApplication>
#include <QDebug>

#include "h/ConfigYAML.h"
#include "h/ClockWidget.h"
#include "h/ClockWindow.h"

ClockWindow::ClockWindow(QString& config_save_filename)
    : QMainWindow(nullptr), 
        config_save_filename(config_save_filename),
        resizing(false), 
        resize_margin(5) {
    setWindowTitle("Analog Clock");

    QRect screenGeometry = QGuiApplication::primaryScreen()->geometry();
    onScreenGeometryChanged(screenGeometry);

    Qt::WindowFlags winFlags = Qt::Widget;
    if (config["window"]["frameless"].as<bool>()) winFlags |= Qt::FramelessWindowHint;
    if (config["window"]["always_on_top"].as<bool>()) winFlags |= Qt::WindowStaysOnTopHint;
    if (config["window"]["tool"].as<bool>()) winFlags |= Qt::Tool;
    setWindowFlags(winFlags);

    QColor background_color = config_qcolor(config["colors"]["background"]);
    if (background_color.isValid()) {
        setAutoFillBackground(true);
        QPalette palette = this->palette();
        palette.setColor(this->backgroundRole(), background_color);
        this->setPalette(palette);
    }
    else {
        setAttribute(Qt::WA_TranslucentBackground);
    }

    central_widget = new QWidget(this);
    central_widget->setAttribute(Qt::WA_TranslucentBackground);
    setCentralWidget(central_widget);
    layout = new QVBoxLayout(central_widget);
    layout->setContentsMargins(0, 0, 0, 0);

    clock_widget = new ClockWidget();
    layout->addWidget(clock_widget);

    // Connect to the screenGeometryChanged signal
    connect(QGuiApplication::primaryScreen(), &QScreen::geometryChanged, this, &ClockWindow::onScreenGeometryChanged);
}

void ClockWindow::onScreenGeometryChanged(const QRect &geometry) {
    int x = config["window"]["x"].as<int>(); 
    if (x < 0) x = geometry.width() + x;

    int y = config["window"]["y"].as<int>(); 
    if (y < 0) y = geometry.height() + y;

    int width = config["window"]["width"].as<int>();
    int height = config["window"]["height"].as<int>();

    setGeometry(x, y, width, height);
}

bool ClockWindow::is_on_edge(const QPoint& pos) {
    QRect rect = this->rect();
    return (pos.x() >= rect.width() - resize_margin ||
            pos.y() >= rect.height() - resize_margin);
}

void ClockWindow::mousePressEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton) {
        old_pos = event->globalPosition();
        if (is_on_edge(event->pos())) {
            resizing = true;
        }
    }
}

void ClockWindow::mouseReleaseEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton) {
        old_pos.reset();
        resizing = false;
    }

    if (config_save_filename != nullptr) {
        config_save(config_save_filename);
    }
}

void ClockWindow::mouseMoveEvent(QMouseEvent* event) {
    if (old_pos.has_value()) {
        if (resizing) {
            QPointF delta = QPointF(-old_pos.value().x(), -old_pos.value().y());
            int new_width = this->width() + delta.x();
            int new_height = this->height() + delta.y();
            setGeometry(this->x(), this->y(), new_width, new_height);
        } else {
            QPointF delta = event->globalPosition() - old_pos.value();
            move(this->x() + delta.x(), this->y() + delta.y());
        }
        old_pos = event->globalPosition();

        if (config_save_filename != nullptr) {
            config["window"]["x"] = this->x();
            config["window"]["y"] = this->y();
        }
    }
}

void ClockWindow::wheelEvent(QWheelEvent *event) {
    int dir = event->angleDelta().y() > 0 ? 10 : -10;
    int width = this->width() + dir;
    int height = this->height() + dir;
    resize(width, height);

    if (config_save_filename != nullptr) {
        config["window"]["width"] = width;
        config["window"]["height"] = height;
    }
}
