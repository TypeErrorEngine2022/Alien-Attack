#pragma once
#include <SDL2/SDL.h>
#include <string>
#include <map> 

class TextureManager
{
public:
    TextureManager(const TextureManager&) = delete;
    TextureManager(const TextureManager&&) = delete;

    ~TextureManager();

    static TextureManager* Instance();

    static void clean();

    bool load(std::string fileName, std::string id, 
            SDL_Renderer* pRenderer);

    std::map<std::string, SDL_Texture*>& getTextureMap();

    void draw(std::string id, int x, int y, int width, int height,
            SDL_Renderer* pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);

    void drawFrame(std::string id, int x, int y, int width, int height,
                int currentRow, int currentFrame, SDL_Renderer* pRenderer,
                double angle = 0, int alpha = 255, SDL_RendererFlip flip = SDL_FLIP_NONE);

    void drawTile(std::string id, std::size_t margin, std::size_t spacing,
                    int x, int y, std::size_t width, std::size_t height, 
                    int currentRow, int currentFrame, SDL_Renderer* pRenderer);

    void clearFromTextureMap(std::string ID);

public:
    std::map<std::string, SDL_Texture*> m_textureMap;

private:
    //use Singleton
    TextureManager(){}
    static TextureManager* s_pInstance;
};

typedef TextureManager TheTextureManager;



