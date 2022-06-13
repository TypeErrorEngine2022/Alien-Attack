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

    void collision() override;
    std::string type() override;

protected:
    ShooterObject();
    
    void doDyingAnimation();

    //how fast will this object fire bullets? with a counter
    int m_bulletFiringSpeed;
    int m_bulletCounter;

    int m_moveSpeed;
    double m_angle;
    int m_alpha;

    //how long will the death animation takes? with a counter
    int m_dyingTime;
    int m_dyingCounter;

    //has the explosion sound played?
    bool m_bPlayedDeathSound;
};