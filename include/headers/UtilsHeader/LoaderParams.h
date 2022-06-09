#pragma once
#include <SDL2/SDL.h>
#include <string>

class LoaderParams
{
public:
    LoaderParams(int x, int y, int width, int height, std::string textureID, 
                    int numFrames, int callbackID = 0, int animSpeed = 0);
    ~LoaderParams(){};

    int getX() const;
    int getY() const;
    int getWidth() const;
    int getHeight() const;
    std::string getTextureID() const;
    int getNumFrames() const;
    int getCallbackID() const;
    int getAnimSpeed() const;

private:
    int m_x;
    int m_y;
    int m_width;
    int m_height;
    std::string m_textureID;
    int m_numFrames;
    int m_callbackID;
    int m_animSpeed;
};