#include "../../include/headers/UtilsHeader/TextureManager.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

TextureManager* TextureManager::s_pInstance = nullptr;

TextureManager::~TextureManager()
{
    std::cout << "Release textures\n";
    for (std::map<std::string, SDL_Texture*>::value_type it: m_textureMap)
    {
        SDL_DestroyTexture(it.second); // it.second refers to SDL_Texture*
    }
}

TextureManager* TextureManager::Instance()
{
    if (s_pInstance == nullptr)
    {
        s_pInstance = new TextureManager();
        return s_pInstance;
    }

    return s_pInstance;
}

void TextureManager::clean()
{
    std::cout << "Release TextureManager Instance\n";
    delete s_pInstance;
    s_pInstance = nullptr;
}

bool TextureManager::load(std::string fileName, std::string id, 
          SDL_Renderer* pRenderer)
{
    SDL_Surface* pTempSurface = IMG_Load(fileName.c_str()); //convert string to const char* (C-style string)

    if (pTempSurface == nullptr)
    {
        return false;
    }

    SDL_Texture* pTexture = SDL_CreateTextureFromSurface(pRenderer, pTempSurface);

    SDL_FreeSurface(pTempSurface);

    if (pTexture != 0)
    {
        m_textureMap[id] = pTexture;
        return true;
    }

    return false;
}

std::map<std::string, SDL_Texture*>& TextureManager::getTextureMap()
{
    return m_textureMap;
}

//draw the whole image
void TextureManager::draw(std::string id, int x, int y, int width, int height,
          SDL_Renderer* pRenderer, SDL_RendererFlip flip)
{
    SDL_Rect srcRect;
    SDL_Rect destRect;

    srcRect.x = 0;
    srcRect.y = 0;
    srcRect.w = destRect.w = width;
    srcRect.h = destRect.h = height;
    destRect.x = x;
    destRect.y = y;

    SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect,
                     &destRect, 0, nullptr, flip);
}

//draw the current frame
void TextureManager::drawFrame(std::string id, int x, int y, int width, int height,
                                int currentRow, int currentFrame, SDL_Renderer* pRenderer, double angle,
                                int alpha, SDL_RendererFlip flip)
{
    SDL_Rect srcRect;
    SDL_Rect destRect;
    srcRect.x = width * currentFrame;
    srcRect.y = height * (currentRow - 1);
    srcRect.w = destRect.w = width;
    srcRect.h = destRect.h = height;
    destRect.x = x;
    destRect.y = y;

    SDL_SetTextureAlphaMod(m_textureMap[id], alpha);
    SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect,
                     &destRect, angle, nullptr, flip);
}

void TextureManager::drawTile(std::string id, std::size_t margin, std::size_t spacing,
                                int x, int y, std::size_t width, std::size_t height, 
                                int currentRow, int currentFrame, SDL_Renderer* pRenderer)
{
    SDL_Rect srcRect;
    SDL_Rect destRect;
    srcRect.x = margin + (spacing + width) * currentFrame;
    srcRect.y = margin + (spacing + height) * currentRow;
    srcRect.w = destRect.w = width;
    srcRect.h = destRect.h = height;
    destRect.x = x;
    destRect.y = y;

    SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect,
                     &destRect, 0, nullptr, SDL_FLIP_NONE);
}

void TextureManager::clearFromTextureMap(std::string ID)
{
    m_textureMap.erase(ID);
}
