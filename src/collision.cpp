
#include "../include/entity.hpp"
#include "../include/platform.hpp"

#include <vector>

bool collisionCheckEtoP(Entity &p_entity, platform &p_platform, int nextMoveDistanceX, int nextMoveDistanceY) {
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
        if (collisionCheckEtoP(p_entity, platform, nextMoveDistanceX, nextMoveDistanceY)) {
            return true;
        }
    }
    return false;
}


bool attackCheck(Entity &p_attacker, Entity &p_opponent, int attackRangeX, int attackRangeY_BACKUPDONTUSE, int direction) {
    if (direction == 3) // Attack left
    {
        // Attack facing left
        // Attack perform when right of opponent is in range between left of attacker and left of attacker - attackRangeX
        if (p_attacker.getLeft() - attackRangeX < p_opponent.getRight() &&
            p_opponent.getRight() < p_attacker.getLeft()) {
                return true;
            }
        return false;
    }
    if (direction == 4) // Attack right
    {
        // Attack facing right
        // Attack perform when left of opponent is in range between right of attacker and right of attacker + attackRangeX
        if (p_attacker.getRight() < p_opponent.getLeft() &&
            p_opponent.getLeft() < p_attacker.getRight() + attackRangeX) {
                return true;
            }
        return false;
    }
    return false;
}