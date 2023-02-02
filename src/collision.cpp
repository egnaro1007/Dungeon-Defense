
#include "../include/entity.hpp"
#include "../include/platform.hpp"

bool collisionCheck(Entity &p_entity, platform &p_platform) {
    if (p_entity.getBottom() >= p_platform.top,
        p_entity.getTop() <= p_platform.bottom,
        p_entity.getRight() >= p_platform.left,
        p_entity.getLeft() <= p_platform.right) {
            return true;
        }
    return false;
}