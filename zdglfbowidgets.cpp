#include "zdglfbowidgets.h"

#include <QtGui/QOpenGLFramebufferObject>
#include "zdglrender.h"

#include <QtQuick/QQuickWindow>
#include <QtGui/qopenglshaderprogram.h>
#include <QtGui/qopenglfunctions.h>
#include <QtGui/QOpenGLFramebufferObject>

#include <qsgsimpletexturenode.h>
#include <iostream>

#include <bx/bx.h>
#include <bx/spscqueue.h>
#include <bx/thread.h>
#include <bgfx/bgfx.h>
#include <bgfx/platform.h>
#include "logo.h"
using namespace std;

class LogoInFboRenderer
        : public QQuickFramebufferObject::Renderer,
        public QOpenGLFunctions
{
public:
    LogoInFboRenderer()
    {
        //logo.initialize(fbo);
        bgfx::renderFrame();
    }

    void render() override {
        //logo.render();
        static const bgfx::ViewId kClearView = 0;
        uint32_t width = 640;
        uint32_t height = 480;
        const static bool showStats = false;

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
        update();
    }

    QOpenGLFramebufferObject *createFramebufferObject(const QSize &size) override {
        QOpenGLFramebufferObjectFormat format;
        format.setAttachment(QOpenGLFramebufferObject::CombinedDepthStencil);
        format.setSamples(4);
        fbo = new QOpenGLFramebufferObject(size, format);
        cout <<"Create FBO"<<endl;
        static bool isInit = false;
        if(!isInit)
        {
            initializeOpenGLFunctions();
            cout <<"BGFX Initialized"<<endl;
            bgfx::Init init;
            init.type = bgfx::RendererType::Enum::Count;
            //init.platformData.context = ctx.convert;
            init.platformData.backBuffer = fbo;
            init.platformData.backBufferDS = fbo;
            init.resolution.width = 640;
            init.resolution.height = 480;
            init.resolution.reset = BGFX_RESET_VSYNC;
            if (!bgfx::init(init))
                return NULL;
            // Set view 0 to the same dimensions as the window and to clear the color buffer.
            const bgfx::ViewId kClearView = 0;
            bgfx::setViewClear(kClearView, BGFX_CLEAR_COLOR);
            bgfx::setViewRect(kClearView, 0, 0, bgfx::BackbufferRatio::Equal);
            isInit = true;
        }
        return fbo;
    }

    //ZDGLRender logo;
    QOpenGLFramebufferObject* fbo;
};

QQuickFramebufferObject::Renderer *ZDGLFBOWidgets::createRenderer() const
{
    return new LogoInFboRenderer();
}
