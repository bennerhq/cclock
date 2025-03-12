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

#ifndef CLOCKWINDOW_H
#define CLOCKWINDOW_H

#include <optional>

#include <QMainWindow>
#include <QVBoxLayout>
#include <QMouseEvent>

#include "h/ClockWidget.h"

class ClockWindow : public QMainWindow {
    Q_OBJECT

public:
    ClockWindow();

protected:
    bool is_on_edge(const QPoint& pos);
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void wheelEvent(QWheelEvent *event) override;
    void onScreenGeometryChanged(const QRect &geometry);

private:
    ClockWidget* clock_widget;
    QWidget* central_widget;
    QVBoxLayout* layout;
    std::optional<QPointF> old_pos;
    bool resizing;
    int resize_margin;
};

#endif // CLOCKWINDOW_H