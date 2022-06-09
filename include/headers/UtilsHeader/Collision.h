#pragma once
#include <SDL2/SDL.h>

/**
 * @brief Detect collision between two rectangles
 * 
 * @param A - SDL_Rect for A
 * @param B - SDL_Rect for B
 * @return true if collided
 */
bool RectRect(SDL_Rect A, SDL_Rect B)
{
    //To make the rectangles slightly smaller
    //More direct hits are needed before they will be registered as a collision
    const int s_buffer = 4;

    int aHBuf = A.h / s_buffer;
    int aWBuf = A.w / s_buffer;

    int bHBuf = b.h / s_buffer;
    int bWBuf = b.w / s_buffer;

    int TopA = A.y;
    int BottomA = A.y + A.h;
    int RightA = A.x + A.w;
    int LeftA = A.x;

    int TopB = B.y;
    int BottomB = B.y + B.h;
    int RightB = B.x + B.w;
    int LeftB = B.x;

    //Each side takes away side * (1 - 1/s_buffer)
    //So each rectangle is smaller
    //Example:  A.y + A.h - aHBuf will make the bottom higher
    //That means the height is smaller

    //second example: B.x + bWBuf means that rightside is push rightwards
    //Like whole rectangle is compressed rightwards

    //the bottom of A is higher than the top of B
    //the top of A is lower than the bottom of B
    //the right of A is on leftwards of left of B
    //the left of A is on rightwards of right of B
    // => NO COLLISION
    if (BottomA - aHBuf <= TopB + bHBuf ||
        TopA + aHBuf >= BottomB - bHBuf ||
        RightA - aWBuf <= LeftB + bWBuf ||
        LeftA + aWBuf >= RightB - bWBuf)
    {
        return false;
    }

    //HAS COLLISION
    return true;
}