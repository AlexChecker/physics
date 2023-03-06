//
// Created by alex Cheker on 03.03.2023.
//

#ifndef PHYSICS_BOXOBJECT_H
#define PHYSICS_BOXOBJECT_H
#include "BaseObject.h"


class BoxObject : public BaseObject {
public:
    BoxObject(float w,float h,float x,float y,float angle, b2World* world, Color col=WHITE, bool isDynamic= false, bool debug =false);
    void Draw();
};


#endif //PHYSICS_BOXOBJECT_H
