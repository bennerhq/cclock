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

#include "h/yamlConfig.h"
#include "h/ClockWidget.h"
#include "h/ClockWindow.h"

ClockWindow::ClockWindow()
    : QMainWindow(nullptr), 
        resizing(false), 
        resize_margin(5) {
    setWindowTitle("Analog Clock");

    QRect screenGeometry = QGuiApplication::primaryScreen()->geometry();

    int x = config_get_int("window.x"); 
    if (x < 0) x = screenGeometry.width() + x;

    int y = config_get_int("window.y");
    if (y < 0) y = screenGeometry.height() + y;

    int width = config_get_int("window.width");
    int height = config_get_int("window.height");

    Qt::WindowFlags winFlags = Qt::Widget;
    if (config_get_bool("window.frameless")) {
        winFlags |= Qt::FramelessWindowHint;
    }
    if (config_get_bool("window.always_on_top")) {
        winFlags |= Qt::WindowStaysOnTopHint;
    }
    if (config_get_bool("window.tool")) {
        winFlags |= Qt::Tool;
    }
    setWindowFlags(winFlags);
    setGeometry(x, y, width, height);

    QColor background_color = config_get_qcolor("colors.background");
    if (background_color.alpha() == 0) {
        setAttribute(Qt::WA_TranslucentBackground);
    } else {
        setAutoFillBackground(true);
        QPalette palette = this->palette();
        palette.setColor(this->backgroundRole(), background_color);
        this->setPalette(palette);
    }

    central_widget = new QWidget(this);
    central_widget->setAttribute(Qt::WA_TranslucentBackground);
    setCentralWidget(central_widget);
    layout = new QVBoxLayout(central_widget);
    layout->setContentsMargins(0, 0, 0, 0);

    clock_widget = new ClockWidget();
    layout->addWidget(clock_widget);
}

bool ClockWindow::is_on_edge(const QPoint& pos) {
    QRect rect = this->rect();
    return (pos.x() >= rect.width() - resize_margin ||
            pos.y() >= rect.height() - resize_margin);
}

void ClockWindow::mousePressEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton) {
        old_pos = event->globalPos(); // Change globalPosition to globalPos
        if (is_on_edge(event->pos())) {
            resizing = true;
        }
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
            QPointF delta = event->globalPos() - old_pos.value(); // Change globalPosition to globalPos
            move(this->x() + delta.x(), this->y() + delta.y());
        }
        old_pos = event->globalPos(); // Change globalPosition to globalPos
    }
}

void ClockWindow::mouseReleaseEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton) {
        old_pos.reset();
        resizing = false;
    }
}

void ClockWindow::wheelEvent(QWheelEvent *event) {
    int dir = event->angleDelta().y() > 0 ? 10 : -10;
    resize(this->width() + dir, this->height() + dir);
}
