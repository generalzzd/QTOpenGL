#include "zdglrender.h"

#include <iostream>

#include <bx/bx.h>
#include <bx/spscqueue.h>
#include <bx/thread.h>
#include <bgfx/bgfx.h>
#include <bgfx/platform.h>
#include "logo.h"

using namespace std;

bx::Thread apiThread;

ZDGLRender::ZDGLRender()
{

}

ZDGLRender::~ZDGLRender()
{
    while (bgfx::RenderFrame::NoContext != bgfx::renderFrame()) {}
    apiThread.shutdown();
    apiThread.getExitCode();
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
static int32_t runApiThread(bx::Thread *self, void *userData)
{
    auto args = (ApiThreadArgs *)userData;
    // Initialize bgfx using the native window handle and window resolution.
    bgfx::Init init;
    init.type = bgfx::RendererType::Enum::OpenGL;
    init.platformData = args->platformData;
    init.resolution.width = args->width;
    init.resolution.height = args->height;
    init.resolution.reset = BGFX_RESET_VSYNC;
    if (!bgfx::init(init))
        return 1;
    // Set view 0 to the same dimensions as the window and to clear the color buffer.
    const bgfx::ViewId kClearView = 0;
    bgfx::setViewClear(kClearView, BGFX_CLEAR_COLOR);
    bgfx::setViewRect(kClearView, 0, 0, bgfx::BackbufferRatio::Equal);
    uint32_t width = args->width;
    uint32_t height = args->height;
    bool showStats = false;
    bool exit = false;
    while (!exit) {
        // Handle events from the main thread.

        // This dummy draw call is here to make sure that view 0 is cleared if no other draw calls are submitted to view 0.
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
    }
    bgfx::shutdown();
    return 0;
}

void ZDGLRender::initialize()
{
    initializeOpenGLFunctions();

    bgfx::renderFrame();

    ApiThreadArgs apiThreadArgs;

    QVariant ctx = QOpenGLContext::currentContext()->nativeHandle();
    if(ctx.isNull())
        exit(-1);

    apiThreadArgs.platformData.context = ctx.value();
    apiThreadArgs.width = 640;
    apiThreadArgs.height = 480;

    apiThread.init(runApiThread, &apiThreadArgs);


}

void ZDGLRender::render()
{

     bgfx::renderFrame();
}



