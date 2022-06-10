#pragma once
#include <SDL2/SDL.h>
#include <string>
#include <memory>
#include "../UtilsHeader/LoaderParams.h"

#include "../UtilsHeader/Vector2D.h"

class GameObject
{
public:
    //base class need virtual destructor
    virtual ~GameObject(){}

    virtual void load(const std::shared_ptr<LoaderParams> pParams) = 0;

    virtual void draw() = 0;
    virtual void update() = 0;
    virtual void clean() = 0;

    //object has collided, handle accordingly
    virtual void collision() = 0;

    //get the type of the object
    virtual std::string type() = 0;

    Vector2D getPosition() const;
    int getWidth() const;
    int getHeight() const;
    int getCallbackID() const;

    //scroll along with tilemap
    void scroll(double scrollSpeed);

    bool updating();
    void setUpdating(bool updating);

protected:
    GameObject();

    //movement variables
    Vector2D m_position;
    Vector2D m_velocity; // unit/s
    Vector2D m_acceleration;
    
    //size varaibles
    int m_width;
    int m_height;

    //animation variables
    int m_currentRow;
    int m_currentFrame;
    int m_numFrames;
    int m_callbackID;
    int m_animSpeed;
    std::string m_textureID;

    //common boolean varaibles
    bool m_bUpdating;

    //rotation
    double m_angle;

    //blending
    int m_alpha;
};