#include "Window.hpp"
#include <stdio.h>
#include <string>
#include <sstream>

Window::Window()
{
	//Initialize non-existant window
	mWindow = NULL;
	mMouseFocus = false;
	mKeyboardFocus = false;
	mFullScreen = false;
	mMinimized = false;
	mWidth = 0;
	mHeight = 0;
}

bool Window::init()
{
	//Create window
	mWindow = SDL_CreateWindow( "4981 Linux Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE );
	if( mWindow != NULL )
	{
		mMouseFocus = true;
		mKeyboardFocus = true;
		mWidth = SCREEN_WIDTH;
		mHeight = SCREEN_HEIGHT;
	}

	return mWindow != NULL;
}

SDL_Surface* Window::getScreenSurface()
{
	return  SDL_GetWindowSurface( this->mWindow );
}

SDL_Renderer* Window::createRenderer()
{
	return SDL_CreateRenderer( mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
}

void Window::handleEvent( SDL_Event& e )
{
	//Window event occured
	if( e.type == SDL_WINDOWEVENT )
	{

		switch( e.window.event )
		{
			//Get new dimensions and repaint on window size change
			case SDL_WINDOWEVENT_SIZE_CHANGED:
			mWidth = e.window.data1;
			mHeight = e.window.data2;
			break;

			//Repaint on exposure
			case SDL_WINDOWEVENT_EXPOSED:
			break;

			//Mouse entered window
			case SDL_WINDOWEVENT_ENTER:
			mMouseFocus = true;
			break;
			
			//Mouse left window
			case SDL_WINDOWEVENT_LEAVE:
			mMouseFocus = false;
			break;

			//Window has keyboard focus
			case SDL_WINDOWEVENT_FOCUS_GAINED:
			mKeyboardFocus = true;
			break;

			//Window lost keyboard focus
			case SDL_WINDOWEVENT_FOCUS_LOST:
			mKeyboardFocus = false;
			break;

			//Window minimized
			case SDL_WINDOWEVENT_MINIMIZED:
            mMinimized = true;
            break;

			//Window maxized
			case SDL_WINDOWEVENT_MAXIMIZED:
			mMinimized = false;
            break;
			
			//Window restored
			case SDL_WINDOWEVENT_RESTORED:
			mMinimized = false;
            break;
		}
	}
	//Enter exit full screen on return key
	else if( e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_RETURN )
	{
		if( mFullScreen )
		{
			SDL_SetWindowFullscreen( mWindow, SDL_FALSE );
			mFullScreen = false;
		}
		else
		{
			SDL_SetWindowFullscreen( mWindow, SDL_TRUE );
			mFullScreen = true;
			mMinimized = false;
		}
	}
}

void Window::free()
{
	if( mWindow != NULL )
	{
		SDL_DestroyWindow( mWindow );
	}

	mMouseFocus = false;
	mKeyboardFocus = false;
	mWidth = 0;
	mHeight = 0;
}

int Window::getWidth()
{
	return mWidth;
}

int Window::getHeight()
{
	return mHeight;
}

bool Window::hasMouseFocus()
{
	return mMouseFocus;
}

bool Window::hasKeyboardFocus()
{
	return mKeyboardFocus;
}

bool Window::isMinimized()
{
	return mMinimized;
}