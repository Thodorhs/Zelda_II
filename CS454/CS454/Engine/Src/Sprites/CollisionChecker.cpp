#include "../../Include/Sprites/CollisionChecker.h"

CollisionChecker CollisionChecker::singleton;

auto CollisionChecker::Find(Sprite* s1, Sprite* s2) -> std::list<Entry>::iterator {
    return std::find_if(
        entries.begin(),
        entries.end(),
        [s1, s2](const Entry& e) {
            return std::get<0>(e) == s1 && std::get<1>(e) == s2 ||
                std::get<0>(e) == s2 && std::get<1>(e) == s1;
        }
    );
}
void CollisionChecker::Cancel(Sprite* s1, Sprite* s2) {
    entries.erase(Find(s1, s2));
}
void CollisionChecker::Check(void) const {
    for (auto& e : entries)
        if (std::get<0>(e)->CollisionCheck(std::get<1>(e)))
            std::get<2>(e)(std::get<0>(e), std::get<1>(e));
}