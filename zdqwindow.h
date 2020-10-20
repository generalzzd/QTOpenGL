#ifndef ZDQWINDOW_H
#define ZDQWINDOW_H

#include <QWindow>
#include <QObject>

#include <bx/bx.h>
#include <bx/spscqueue.h>
#include <bx/thread.h>
#include <bgfx/bgfx.h>
#include <bgfx/platform.h>

#include "logo.h"

class ZDQWindow : public QWindow
{
    Q_OBJECT
public:
    explicit ZDQWindow(QWindow *parent = nullptr);
    virtual ~ZDQWindow();

    virtual void render();

    // QObject interface
public:
    virtual bool event(QEvent *event);

    // QWindow interface
protected:
    virtual void resizeEvent(QResizeEvent *);
};

enum class EventType
{
    Exit,
    Key,
    Resize
};

struct ExitEvent
{
    EventType type = EventType::Exit;
};

struct KeyEvent
{
    EventType type = EventType::Key;
    int key;
    int action;
};

struct ResizeEvent
{
    EventType type = EventType::Resize;
    uint32_t width;
    uint32_t height;
};
struct ApiThreadArgs
{
    bgfx::PlatformData platformData;
    uint32_t width;
    uint32_t height;
};

#endif // ZDQWINDOW_H
