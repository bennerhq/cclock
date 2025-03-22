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

#include "h/Config.h"
#include "h/ClockWidget.h"
#include "h/ClockWindow.h"

#if QT_VERSION > QT_VERSION_CHECK(5, 15, 13)
#   define globalPos     globalPosition
#endif

ClockWindow::ClockWindow(QString& config_save_filename)
    : QMainWindow(nullptr), 
        config_save_filename(config_save_filename),
        resizing(false), 
        resize_margin(5) {
    setWindowTitle("Analog Clock");

    QRect screenGeometry = QGuiApplication::primaryScreen()->geometry();
    onScreenGeometryChanged(screenGeometry);

    Qt::WindowFlags winFlags = Qt::Widget | Qt::WindowSystemMenuHint;
    if (config_get_bool("window.frameless")) winFlags |= Qt::FramelessWindowHint;
    if (config_get_bool("window.always_on_top")) winFlags |= Qt::WindowStaysOnTopHint;
    if (config_get_bool("window.tool")) winFlags |= Qt::Tool;
    setWindowFlags(winFlags);

    QColor background_color = config_get_color("window.background_color");
    if (background_color.isValid()) {
        setAutoFillBackground(true);
        QPalette palette = this->palette();
        palette.setColor(this->backgroundRole(), background_color);
        this->setPalette(palette);
    }
    else {
        setAttribute(Qt::WA_TranslucentBackground);
    }
    backgroundRenderer = config_get_image("window.background");

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

void ClockWindow::paintEvent(QPaintEvent*) {
    QPainter painter(this);

    QRect rect = this->rect();
    QPoint center = rect.center();
    int radius = std::min(rect.width(), rect.height()) / 2;

    painter.translate(center);
    painter.scale(radius / 100.0, radius / 100.0);
    painter.setRenderHint(QPainter::Antialiasing);

    if (backgroundRenderer != nullptr) {
        backgroundRenderer->paint(&painter, 0, false);
    }
}

void ClockWindow::onScreenGeometryChanged(const QRect &geometry) {
    int x = config_get_int("window.x"); 
    if (x < 0) x = geometry.width() + x;

    int y = config_get_int("window.y"); 
    if (y < 0) y = geometry.height() + y;

    int width = config_get_int("window.width") | 1;
    int height = config_get_int("window.height") | 1;

    setGeometry(x, y, width, height);
}

bool ClockWindow::is_on_edge(const QPoint& pos) {
    QRect rect = this->rect();
    return (pos.x() >= rect.width() - resize_margin ||
            pos.y() >= rect.height() - resize_margin);
}

void ClockWindow::mousePressEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton) {
        old_pos = event->globalPos();
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
            QPointF delta = event->globalPos() - old_pos.value();
            move(this->x() + delta.x(), this->y() + delta.y());
        }
        old_pos = event->globalPos();

        if (config_save_filename != nullptr) {
            config_set_int("window.x", this->x());
            config_set_int("window.y", this->y());
        }
    }
}

void ClockWindow::wheelEvent(QWheelEvent *event) {
    int dir = event->angleDelta().y() > 0 ? 10 : -10;
    int width = this->width() + dir;
    int height = this->height() + dir;
    resize(width, height);

    if (config_save_filename != nullptr) {
        config_set_int("window.width", width);
        config_set_int("window.height", height);
    }
}
