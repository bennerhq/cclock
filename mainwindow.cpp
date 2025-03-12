#include <QMainWindow>
#include <QX11Info>
#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include <QString>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr) : QMainWindow(parent) {
        // ...existing code...

        // Example usage of QString instead of std::string
        QString exampleString = "This is a QString";

        // Make the window stick to all virtual desktops
        Display *display = QX11Info::display();
        Window window = winId();
        Atom atom = XInternAtom(display, "_NET_WM_DESKTOP", False);
        long data = 0xFFFFFFFF; // Special value to make the window sticky
        XChangeProperty(display, window, atom, XA_CARDINAL, 32, PropModeReplace, (unsigned char *)&data, 1);
    }

    // ...existing code...
};
