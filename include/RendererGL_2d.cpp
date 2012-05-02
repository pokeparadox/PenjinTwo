/**
	\section LICENSE
	Penjin is Copyright (c)2005, 2006, 2007, 2008, 2009, 2010, 2011 Kevin Winfield-Pantoja

	This file is part of Penjin.

	Penjin is free software: you can redistribute it and/or modify
	it under the terms of the GNU Lesser General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	Penjin is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU Lesser General Public License for more details.

	You should have received a copy of the GNU Lesser General Public License
	along with Penjin.  If not, see <http://www.gnu.org/licenses/>.
*/
/***************************************************************************************************
*   \file RenderGL_2d is a 2d renderer using GL/ES.
*   \author Kevin Winfield-Pantoja
*/
#if defined (PENJIN_GL) || defined (PENJIN_ES) || defined (PENJIN_ES2)
#include "RendererGL_2d.h"
#include "ErrorHandler.h"
#include "Colour.h"
#include "ConfigManager.h"
#ifdef PENJIN_GL
    #include <SDL/SDL_opengl.h>
#endif
using Penjin::RendererGL_2d;
using Penjin::ErrorHandler;
using Penjin::Colour;
using Penjin::ConfigManager;

//RendererGL_2d* RendererGL_2d::instance = NULL;

RendererGL_2d::RendererGL_2d()
{
    //ctor
    ConfigMan::getInstance()->report("GFXSDL");
    ConfigMan::getInstance()->report("GFX2D");
    ConfigMan::getInstance()->report("GFXGL");
}

RendererGL_2d::~RendererGL_2d()
{
    //dtor
}

/*RendererGL_2d* RendererGL_2d::getInstance()
{
    if( instance == NULL )
    {
        instance = new RendererGL_2d;
    }
    return instance;
}*/

void RendererGL_2d::applyVideoSettings()
{
#if defined(PENJIN_GL)
	const SDL_VideoInfo* info = NULL;	//Information about the current video settings
    int flags = 0;						//Flags for SDL_SetVideoMode
    //Get some video information
    info = SDL_GetVideoInfo();
    if(!info)
	{
	    ErrorMan::getInstance()->forceQuit(PENJIN_SDL_VIDEO_QUERY_FAILED, "RendererGL_2d::applyVideoSettings()");
    }
        //Setup OpenGL window attributes
        SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 5);
        SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 6);
        SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 5);
        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    #ifdef __linux__
        SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
    #else
        SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 16);
    #endif
        flags = SDL_OPENGL;
        SDL_Surface* screen = NULL;

    if(fullScreen)
        flags = flags | SDL_FULLSCREEN;
    if(bpp == 0 || !(bpp == 8 || bpp == 16 || bpp == 32))
        bpp = info->vfmt->BitsPerPixel;

        screen = SDL_SetVideoMode(resolution.x, resolution.y, bpp, flags);
        if(screen  == NULL )
            Penjin::ErrorMan::getInstance()->forceQuit(PENJIN_SDL_SETVIDEOMODE_FAILED, "RendererGL_2d::applyVideoSettings()");
        else
        {
            resolution.x = screen->w;
            resolution.y = screen->h;
        }
    #if defined (PENJIN_GL) || defined(PENJIN_ES) || defined(PENJIN_ES2)
        glEnable(GL_CULL_FACE); // don't render the back of polygons...
    #endif
#endif
#if defined PENJIN_ES || defined (PENJIN_ES2)
    Window                      sRootWindow;
    XSetWindowAttributes        sWA;
        unsigned int            ui32Mask;
        int                     i32Depth;

        // Initializes the display and screen
        x11Display = XOpenDisplay(":0");
        if (!x11Display)
        {
            printf("Error: Unable to open X display\n");
            //goto cleanup;
        }
        x11Screen = XDefaultScreen( x11Display );

        // Gets the window parameters
        sRootWindow = RootWindow(x11Display, x11Screen);
        i32Depth = DefaultDepth(x11Display, x11Screen);
        x11Visual = new XVisualInfo;
        XMatchVisualInfo( x11Display, x11Screen, i32Depth, TrueColor, x11Visual);
        if (!x11Visual)
        {
            printf("Error: Unable to acquire visual\n");
            //goto cleanup;
        }
    x11Colormap = XCreateColormap( x11Display, sRootWindow, x11Visual->visual, AllocNone );
    sWA.colormap = x11Colormap;

    // Add to these for handling other events
    sWA.event_mask = StructureNotifyMask | ExposureMask | ButtonPressMask | ButtonReleaseMask | KeyPressMask | KeyReleaseMask;
    ui32Mask = CWBackPixel | CWBorderPixel | CWEventMask | CWColormap;

        // Creates the X11 window
    x11Window = XCreateWindow( x11Display, RootWindow(x11Display, x11Screen), 0, 0, xRes, yRes,
                0, CopyFromParent, InputOutput, CopyFromParent, ui32Mask, &sWA);

    XMapWindow(x11Display, x11Window);
    XFlush(x11Display);

    // Make it fullscreen
    if(fullscreen)
    {
		// Make the window fullscreen
		unsigned char fullScreen = 1;
		Atom wmState = XInternAtom(x11Display, "_NET_WM_STATE", False);
		Atom wmFullScreen = XInternAtom(x11Display,"_NET_WM_STATE_FULLSCREEN", False);

		XEvent xev;
		xev.xclient.type		= ClientMessage;
		xev.xclient.serial		= 0;
		xev.xclient.send_event		= True;
		xev.xclient.window		= x11Window;
		xev.xclient.message_type	= wmState;
		xev.xclient.format		= 32;
		xev.xclient.data.l[0]		= (fullScreen ? _NET_WM_STATE_ADD : _NET_WM_STATE_REMOVE);
		xev.xclient.data.l[1]		= wmFullScreen;
		xev.xclient.data.l[2]		= 0;

		XSendEvent(x11Display, DefaultRootWindow(x11Display), False, SubstructureRedirectMask | SubstructureNotifyMask, &xev);
    }


    eglDisplay = eglGetDisplay((EGLNativeDisplayType)x11Display);
    if(eglDisplay == EGL_NO_DISPLAY)
        return PENJIN_EGL_NO_DISPLAY;
    EGLint iMajorVersion, iMinorVersion;
    if (!eglInitialize(eglDisplay, &iMajorVersion, &iMinorVersion))
    {
            return PENJIN_EGL_INIT_FAILED;
    }
    eglBindAPI(EGL_OPENGL_ES_API);

    EGLint attributes[] =
    {
        EGL_BUFFER_SIZE, 16,
        EGL_RED_SIZE, 5,
        EGL_GREEN_SIZE, 6,
        EGL_BLUE_SIZE, 5,
        EGL_ALPHA_SIZE, 0,
        EGL_DEPTH_SIZE, EGL_DONT_CARE,
        EGL_STENCIL_SIZE, EGL_DONT_CARE,
        EGL_CONFIG_CAVEAT, EGL_NONE,
        EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
    #ifdef PENJIN_ES
        EGL_RENDERABLE_TYPE, EGL_OPENGL_ES_BIT,
    #elif PENJIN_ES2
        EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
    #endif
        EGL_NONE
    };
    EGLint numConfigs;
    if(!eglChooseConfig(eglDisplay,attributes, &eglConfig, 1, &numConfigs))
        return PENJIN_EGL_INIT_FAILED;
    const EGLint contextAttribs[] =
    {
        #ifdef PENJIN_ES
        EGL_CONTEXT_CLIENT_VERSION, 1,
        #elif PENJIN_ES2
        EGL_CONTEXT_CLIENT_VERSION, 2,
        #endif
        EGL_NONE
    };
    eglContext = eglCreateContext(eglDisplay, eglConfig, EGL_NO_CONTEXT, contextAttribs);
    if(eglContext == EGL_NO_CONTEXT)
        return PENJIN_EGL_NO_CONTEXT;
    eglSurface = eglCreateWindowSurface(eglDisplay, eglConfig, (EGLNativeWindowType)x11Window, NULL);
    eglMakeCurrent(eglDisplay,eglSurface,eglSurface,eglContext);
#endif
    initRendering2d();
}

void RendererGL_2d::initRendering2d()
{
    // Setup OpenGL
    glDisable(GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glShadeModel(GL_SMOOTH);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    //Setup viewport
    glViewport(0, 0, resolution.x, resolution.y);

    //Setup world view
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    #ifdef PENJIN_GL
    glOrtho(0, resolution.x, resolution.y, 0, 0, 1);
    #else
    glOrthof(0, resolution.x, resolution.y, 0, 0, 1);
    #endif

    //glMatrixMode(GL_TEXTURE);
    //glRotated(90,0,0,1);
    //glLoadIdentity();
    //Setup modelview matrix
    glMatrixMode( GL_MODELVIEW );
    //glMatrixMode(GL_TEXTURE);
    glLoadIdentity();
    glColor4f(1.0f,1.0f,1.0f,1.0f);
    //glCullFace(GL_FRONT);   // we have inverted the Y to mic drawing like SDL so we have to cull the front face
}

void RendererGL_2d::blit()
{
    #ifdef PENJIN_GL
        SDL_GL_SwapBuffers();
    #elif defined(PENJIN_ES) || defined(PENJIN_ES2)
        eglSwapBuffers(eglDisplay,eglSurface);
    #endif
}

void RendererGL_2d::clear()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
}

void RendererGL_2d::drawPixel(const Vector2d<float> & v)
{
    glEnable(GL_BLEND);
    //  Setup vertex pointers
        glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(2, GL_FLOAT, sizeof(Vector2d<float>), &v);
        glEnableClientState(GL_COLOR_ARRAY);
        glColorPointer(4, GL_FLOAT, sizeof(Colour), &drawColour);
            glDrawArrays(GL_POINTS,0,1);
        glDisableClientState(GL_VERTEX_ARRAY);
        glDisableClientState(GL_COLOR_ARRAY);
    glDisable(GL_BLEND);
}

void RendererGL_2d::drawLine(const Vector2d<float> & p1, const Vector2d<float> & p2)
{
    glEnable(GL_BLEND);
    //  Set OpenGL alpha and colour
        glLineWidth(drawWidth);
        glEnableClientState(GL_VERTEX_ARRAY);

        float verts[] = {   p1.x, p1.y,
                                    p2.x, p2.y};
        glVertexPointer(2, GL_FLOAT, 0,verts);
        glEnableClientState(GL_COLOR_ARRAY);
            float c[] = {   drawColour.r, drawColour.g, drawColour.b, drawColour.a ,drawColour.r, drawColour.g, drawColour.b, drawColour.a};
            glColorPointer(4, GL_FLOAT, 0,c);
            glDrawArrays(GL_LINES,0,2);
        glDisableClientState(GL_VERTEX_ARRAY);
        glDisableClientState(GL_COLOR_ARRAY);
    glDisable(GL_BLEND);
}

void RendererGL_2d::drawRectangle(const Vector2d<float> & pos, const Vector2d<int> & dims)
{
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            glEnable(GL_BLEND);
            //  Set OpenGL alpha and colour
            glEnableClientState(GL_VERTEX_ARRAY);
                //  prepare vertices
                float verts[] = {   pos.x,pos.y + dims.y,
                                    pos.x + dims.x,pos.y + dims.y,
                                    pos.x + dims.x, pos.y,
                                    pos.x,pos.y};
                glVertexPointer(2, GL_FLOAT, 0,verts);

            glEnableClientState(GL_COLOR_ARRAY);
                float c[] = {  drawColour.r, drawColour.g, drawColour.b, drawColour.a,
                drawColour.r, drawColour.g, drawColour.b, drawColour.a,
                drawColour.r, drawColour.g, drawColour.b, drawColour.a,
                drawColour.r, drawColour.g, drawColour.b, drawColour.a};
                glColorPointer(4, GL_FLOAT, 0,c);
                if(drawWidth>0)
                {
                    glLineWidth(drawWidth);
                    glDrawArrays(GL_LINE_LOOP,0,4);
                }
                else
                {
                    glDrawArrays(GL_TRIANGLE_FAN,0,4);
                }
            glDisableClientState(GL_VERTEX_ARRAY);
            glDisableClientState(GL_COLOR_ARRAY);
        glDisable(GL_BLEND);
}

void RendererGL_2d::drawEllipse(const Vector2d<float> & centre, const float& rX, const float& rY)
{

}

Colour RendererGL_2d::getPixel(Vector2d<int> pos)
{
    return Colour(MAGENTA);
}

#endif // GL or ES or ES2 only

