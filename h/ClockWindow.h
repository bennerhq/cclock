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
    ClockWindow(QString& config_save_filename);

protected:
    void onScreenGeometryChanged(const QRect &geometry);
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void wheelEvent(QWheelEvent *event) override;

private:
    QString config_save_filename;
    ClockWidget* clock_widget;
    QWidget* central_widget;
    QVBoxLayout* layout;
    std::optional<QPointF> old_pos;
    bool resizing;
    int resize_margin;

    bool is_on_edge(const QPoint& pos);
};

#endif // CLOCKWINDOW_H
