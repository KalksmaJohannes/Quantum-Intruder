#include "Collisionable.h"


bool Collisionable::isCollision(Collisionable& collisionable) const{

    return getBounds().intersects(collisionable.getBounds());

}
