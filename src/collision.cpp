
#include "../include/entity.hpp"
#include "../include/platform.hpp"

#include <vector>

bool collisionCheck(Entity &p_entity, platform &p_platform, int nextMoveDistanceX, int nextMoveDistanceY) {
    if (p_entity.getBottom() + nextMoveDistanceY > p_platform.top &&
        p_entity.getTop() - nextMoveDistanceY < p_platform.bottom &&
        p_entity.getRight() + nextMoveDistanceX > p_platform.left &&
        p_entity.getLeft() - nextMoveDistanceX < p_platform.right) {
            return true;
        }
    return false;
}

bool platformCollisionCheck(Entity &p_entity, std::vector<platform> &p_platform, int nextMoveDistanceX, int nextMoveDistanceY) {
    for (platform platform : p_platform) {
        if (collisionCheck(p_entity, platform, nextMoveDistanceX, nextMoveDistanceY)) {
            return true;
        }
    }
    return false;
}