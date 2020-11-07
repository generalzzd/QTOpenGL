#include "zdglrender.h"

#include <iostream>

#include <bx/bx.h>
#include <bx/spscqueue.h>
#include <bx/thread.h>
#include <bgfx/bgfx.h>
#include <bgfx/platform.h>
#include "logo.h"

using namespace std;

ZDGLRender::ZDGLRender()
{

}

ZDGLRender::~ZDGLRender()
{
    bgfx::shutdown();
    while (bgfx::RenderFrame::NoContext != bgfx::renderFrame()) {}
}

struct ApiThreadArgs
{
    bgfx::PlatformData platformData;
    uint32_t width;
    uint32_t height;
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


void ZDGLRender::initialize(QOpenGLFramebufferObject *fbo)
{
    initializeOpenGLFunctions();

    bgfx::renderFrame();

    QVariant ctx = QOpenGLContext::currentContext()->nativeHandle();

    // Initialize bgfx using the native window handle and window resolution.
    bgfx::Init init;
    init.type = bgfx::RendererType::Enum::OpenGL;
    //init.platformData.context = ctx.convert;
    init.platformData.backBuffer = fbo;
    init.platformData.backBufferDS = fbo;
    init.resolution.width = 640;
    init.resolution.height = 480;
    init.resolution.reset = BGFX_RESET_VSYNC;
    if (!bgfx::init(init))
        return;
    // Set view 0 to the same dimensions as the window and to clear the color buffer.
    const bgfx::ViewId kClearView = 0;
    bgfx::setViewClear(kClearView, BGFX_CLEAR_COLOR);
    bgfx::setViewRect(kClearView, 0, 0, bgfx::BackbufferRatio::Equal);


}

void ZDGLRender::render()
{
    static const bgfx::ViewId kClearView = 0;
    uint32_t width = 640;
    uint32_t height = 480;
    bool showStats = false;

    bgfx::touch(kClearView);
    // Use debug font to print information about this example.
    bgfx::dbgTextClear();
    bgfx::dbgTextImage(bx::max<uint16_t>(uint16_t(width / 2 / 8), 20) - 20, bx::max<uint16_t>(uint16_t(height / 2 / 16), 6) - 6, 40, 12, s_logo, 160);
    bgfx::dbgTextPrintf(0, 0, 0x0f, "Press F1 to toggle stats.");
    bgfx::dbgTextPrintf(0, 1, 0x0f, "Color can be changed with ANSI \x1b[9;me\x1b[10;ms\x1b[11;mc\x1b[12;ma\x1b[13;mp\x1b[14;me\x1b[0m code too.");
    bgfx::dbgTextPrintf(80, 1, 0x0f, "\x1b[;0m    \x1b[;1m    \x1b[; 2m    \x1b[; 3m    \x1b[; 4m    \x1b[; 5m    \x1b[; 6m    \x1b[; 7m    \x1b[0m");
    bgfx::dbgTextPrintf(80, 2, 0x0f, "\x1b[;8m    \x1b[;9m    \x1b[;10m    \x1b[;11m    \x1b[;12m    \x1b[;13m    \x1b[;14m    \x1b[;15m    \x1b[0m");
    const bgfx::Stats* stats = bgfx::getStats();
    bgfx::dbgTextPrintf(0, 2, 0x0f, "Backbuffer %dW x %dH in pixels, debug text %dW x %dH in characters.", stats->width, stats->height, stats->textWidth, stats->textHeight);
    // Enable stats or debug text.
    bgfx::setDebug(showStats ? BGFX_DEBUG_STATS : BGFX_DEBUG_TEXT);
    // Advance to next frame. Main thread will be kicked to process submitted rendering primitives.
    bgfx::frame();

    //bgfx::renderFrame();
}



