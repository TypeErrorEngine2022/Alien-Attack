#pragma once
#include <memory>
#include <string>
#include "GameObject.h"
#include "../UtilsHeader/LoaderParams.h"
#include "../UtilsHeader/Vector2D.h"

class ShooterObject: public GameObject
{
public:
    
    virtual ~ShooterObject(){}

    void draw() override;
    void update() override;
    void clean() override;

    void load(const std::shared_ptr<LoaderParams> pParams) override;

    void collsion() override;
    std::string type() override;

    //Is the object "state"?
    bool dead();
    bool dying();

protected:
    ShooterObject();

    bool m_bDead;
    bool m_bDying;

    void doDyingAnimation();

    //how fast will this object fire bullets? with a counter
    int m_bulletFiringSpeed;
    int m_bulletCounter;

    int m_moveSpeed;

    //how long will the death animation takes? with a counter
    int m_dyingTime;
    int m_dyingCounter;

    //has the explosion sound played?
    bool m_bPlayedDeathSound;
};