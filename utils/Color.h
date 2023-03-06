//
// Created by alex Cheker on 03.03.2023.
//

#ifndef PHYSICS_COLOR_H
#define PHYSICS_COLOR_H


class Color {


public:
    float red;
    float green;
    float blue;


    Color(float red,float green,float blue)
    {
        this->red=red;
        this->green=green;
        this->blue=blue;
    }
    Color()
    {
        red=.0;
        green=.0;
        blue=.0;
    }
};

static const Color RED = Color(1.0f,.0,.0);
static const Color GREEN = Color(.0,1.0,.0);
static const Color BLUE = Color(.0,.0,1.0);
static const Color CYAN = Color(.0,1.0,1.0);
static const Color MAGENTA = Color(1.0f,.0,1.0);
static const Color YELLOW = Color(1.0f,1.0,.0);
static const Color WHITE = Color(1.0f,1.0,1.0);
static const Color BLACK = Color(.0f,.0,.0);

#endif //PHYSICS_COLOR_H
