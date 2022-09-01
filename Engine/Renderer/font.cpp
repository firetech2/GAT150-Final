#include "font.h"
#include "Core/logger.h"
#include <SDL_ttf.h>

namespace tech
{
	Font::Font(const std::string& filename, int fontSize)
	{
		Load(filename, fontSize);
	}

	Font::~Font()
	{
		if (m_ttfFont) 
		{ 
			TTF_CloseFont(m_ttfFont); 
			m_ttfFont = nullptr;
		}
	}

	bool Font::Create(std::string name, ...)
	{
		va_list args;
		va_start(args, name);
		int size = va_arg(args, int);
		va_end(args);

		Load(name, size);

		return false;
	}

	SDL_Surface* Font::CreateSurface(const std::string& text, const Color& color)
	{
		SDL_Color c = *((SDL_Color*)(&color));
		SDL_Surface* surface = TTF_RenderText_Solid(m_ttfFont, text.c_str(), c);
		if (!surface)
		{
			LOG(SDL_GetError());
		}

		return surface;
	}

	void Font::Load(const std::string& filename, int fontSize)
	{
		m_ttfFont = TTF_OpenFont(filename.c_str(), fontSize);
	}
}
