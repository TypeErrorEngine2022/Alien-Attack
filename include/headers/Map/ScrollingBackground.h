#pragma once
#include <SDL2/SDL.h>
#include <memory>
#include "../UtilsHeader/LoaderParams.h"

class ScrollingBackground: public GameObject
{
public:
    ScrollingBackground();

    void load(const std::shared_ptr<LoaderParams> pParams) override;

    void draw() override;
    void update() override;
    void clean() override;

    std::string type() override;

private:
    /**
     * One rect expand while the other contracts, Once the expanding rectangle has reached its full width.
     * Both rectangles are reset and the loop continues
     */
    SDL_Rect m_srcRect1, m_srcRect2, m_destRect1, m_destRect2;
    int m_srcRect1Width, m_destRect1Width, m_srcRect2Width, m_destRect2Width;

    int count, maxcount;
};