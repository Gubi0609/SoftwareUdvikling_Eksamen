#ifndef ENEMIES_H
#define ENEMIES_H

#include "Enemy.h"
#include <iostream>
#include <string>

using namespace std;

/*
-- PLAINS --
[x] Wolf 2 hp, 1 attackPower, 50 xp
[x] Boar 4 hp, 1 attackPower, 75 xp
[x] Bandit 3 hp, 2 attackPower, 100 xp
[x] Small troll 6 hp, 3 attackPower, 150 xp
[x] Troll 8 hp, 4 attackPower, 250 xp
[x] Nomad Archer 6 hp, 5 attackPower, 300 xp
[x] Wind Sprite 10 hp, 3 attackPower, 350 xp

[x] Alpha Direwolf 20 hp, 5 attackPower, 4000 xp
[x] Warlord Marauder 30 hp, 5 attackPower, 6000 xp

-- CAVE --
[x] Weak Goblin 2 hp, 1 attackPower, 50 xp
[x] Goblin 3 hp, 1 attackPower, 75 xp
[x] Goblin guard 4 hp, 2 attackPower, 100 xp

[x] Umbral Crawler 2 hp, 5 attackPower, 150 xp
[x] Stone Golem 8 hp, 3 attackPower, 250 xp
[x] Pale Watcher 6 hp, 5 attackPower, 300 xp
[x] Crystal Wratih 10 hp, 3 attackPower, 350 xp

[x] Goblin king 20 hp, 5 attackPower, 4000 xp
[x] Gollum 30 hp, 5 attackPower, 6000 xp

-- FOREST --
[x] Spider 2 hp, 1 attackPower, 50 xp
[x] Giant spider 4 hp, 1 attackPower, 75 xp
[x] Bear 3 hp, 2 attackPower, 100 xp
[x] Centaur, 6 hp, 3 attackPower, 150 xp
[x] Treant Sapling 8 hp, 4 attackPower, 250 xp
[x] Elven Rogue 6 hp, 5 attackPower, 300 xp
[x] Forest Wisp 10 hp, 3 attackPower, 350 xp

[x] Corrupted Dryad Queen 20 hp, 5 attackPower, 4000 xp
[x] Ancient Treant 30 hp, 5 attackPower, 6000 xp

-- FINAL BOSS --
[x] Dragon 100 hp, 10 attackPower, 3000 xp
*/

// --- PLAINS --- //
class Wolf : public Enemy {
public:
    Wolf() : Enemy("Wolf", 2, 1, 50, "Lean predators that roam the open plains in small packs, hunting anything that strays too far from safety.") {}   
};

class Boar : public Enemy {
public:
    Boar() : Enemy("Boar", 4, 1, 75, "Ferocious and territorial beasts, boars charge fearlessly at intruders with razor-sharp tusks.") {}
};

class Bandit : public Enemy {
public:
    Bandit() : Enemy("Bandit", 3, 2, 100, "Desperate outlaws who prey on travelers crossing the vast plains, using crude tactics and rusty weapons.") {}
};

class SmallTroll : public Enemy {
public:
    SmallTroll() : Enemy("Small Troll", 6, 3, 150, "Young trolls cast out from their tribes, still dangerous but lacking the brute strength of their elders.") {}
};

class Troll : public Enemy {
public:
    Troll() : Enemy("Troll", 8, 4, 250, "Lumbering, thick-skinned brutes known for their savagery and unnatural resilience to injury.") {}
};

class NomadArcher : public Enemy {
public:
    NomadArcher() : Enemy("Nomad Archer", 6, 5, 300, "Skilled horsemen and archers of the plains, nomads strike from a distance with deadly precision.") {}
};

class WindSprite : public Enemy {
public:
    WindSprite() : Enemy("Wind Sprite", 10, 3, 350, "Spirits of the open air, sprites dart across the grasslands, riding the winds to disorient their foes.") {}
};

class AlphaDirewolf : public Enemy {
public:
    AlphaDirewolf() : Enemy("Alpha Direwolf", 20, 5, 4000, "The colossal leader of a wolf pack, its howl can shake the earth") {}
};

class WarlordMarauder : public Enemy {
public:
    WarlordMarauder() : Enemy("Warlord Marauder", 30, 5, 6000, "A ruthless conqueror who commands raiders across the plains, feared for his brutal raids and iron discipline.") {}
};


// --- CAVE --- //
class WeakGoblin : public Enemy {
public:
    WeakGoblin() : Enemy("Weak Goblin", 2, 1, 50, "Small, cowardly cave-dwellers who rely on numbers rather than strength.") {}
};

class Goblin : public Enemy {
public:
    Goblin() : Enemy("Goblin", 3, 1, 75, "More cunning than their weaker kin, goblins use traps and ambushes to overwhelm travelers.") {}
};

class GoblinGuard : public Enemy {
public:
    GoblinGuard() : Enemy("Goblin Guard", 4, 2, 100, "Hardened goblins who serve as enforcers within goblin clans, clad in crude armor.") {}
};

class UmbralCrawler : public Enemy {
public:
    UmbralCrawler() : Enemy("Umbral Crawler", 2, 5, 150, "A nightmarish creature of shadows with spindly limbs, it strikes swiftly from the darkness.") {}
};

class StoneGolem : public Enemy {
public:
    StoneGolem() : Enemy("Stone Golem", 8, 3, 250, "Ancient constructs of enchanted stone, tirelessly guarding long-forgotten passageways.") {}
};

class PaleWatcher : public Enemy {
public:
    PaleWatcher() : Enemy("Pale Watcher", 6, 5, 300, "Silent and eyeless sentinels that haunt deep caves, their presence alone saps the will to fight.") {}
};

class CrystalWraith : public Enemy {
public:
    CrystalWraith() : Enemy("Crystal Wraith", 10, 3, 350, "Spirits trapped within shimmering crystals, lashing out with bursts of cold, spectral energy.") {}
};

class GoblinKing : public Enemy {
public:
    GoblinKing() : Enemy("Goblin King", 20, 5, 4000, "The bloated, tyrannical ruler of the goblins, wielding crude magic and commanding absolute loyalty.") {}
};

class Gollum : public Enemy {
public:
    Gollum() : Enemy("Gollum", 30, 5, 6000, "A twisted, ancient creature corrupted by time and greed, guarding the deepest reaches of the caves.") {}
};


// --- FOREST --- //
class Spider : public Enemy {
public:
    Spider() : Enemy("Spider", 2, 1, 50, "Common forest hunters, weaving sticky webs between the trees to catch prey unawares.") {}
};

class GiantSpider : public Enemy {
public:
    GiantSpider() : Enemy("Giant Spider", 4, 1, 75, "Their venomous bites and thick hides make these monstrous spiders the terror of the forest undergrowth.") {}
};

class Bear : public Enemy {
public:
    Bear() : Enemy("Bear", 3, 2, 100, "A massive, territorial beast; few survive an encounter once it sets its sights on prey.") {}
};

class Centaur : public Enemy {
public:
    Centaur() : Enemy("Centaur", 6, 3, 150, "Proud and fierce guardians of the forest paths, striking swiftly with both bow and spear.") {}
};

class TreantSapling : public Enemy {
public:
    TreantSapling() : Enemy("Treant Sapling", 8, 4, 250, "Young and fiercely protective, these living trees are born from the ancient groves and will crush any who threaten the forest's heart.") {}
};

class ElvenRogue : public Enemy {
public:
    ElvenRogue() : Enemy("Elven Rogue", 6, 5, 300, "Outcasts from noble elven courts, these shadowy figures strike swiftly and vanish without a trace.") {}
};

class ForestWisp : public Enemy {
public:
    ForestWisp() : Enemy("Forest Wisp", 10, 3, 350, "Glowing motes of life and magic, wisps lure travelers deeper into the woods, often to their doom.") {}
};

class CorruptedDryadQueen : public Enemy {
public:
    CorruptedDryadQueen() : Enemy("Corrupted Dryad Queen", 20, 5, 4000, "Once a benevolent spirit of the forest, now twisted by dark magic into a malevolent force.") {}
};

class AncientTreant : public Enemy {
public:
    AncientTreant() : Enemy("Ancient Treant", 30, 5, 6000, "A towering, ancient tree-beast that awakens in times of grave threat, its roots shaking the very earth.") {}
};


// --- FINAL BOSS --- //
class Dragon : public Enemy {
public:
    Dragon() : Enemy("Dragon", 100, 10, 100000, "An ancient, awe-inspiring beast of fire and rage, slumbering atop a hoard of forgotten riches.") {}
};

#endif // ENEMIES_H