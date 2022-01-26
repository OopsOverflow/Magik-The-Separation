//
// Created by pierre on 15/01/2022.
//

#include "CardMaker.h"
#include <iostream>

#include "Creature.h"
#include "Land.h"
#include "Enchantement.h"
#include "Instant.h"
#include "Sorcery.h"

CardMaker& CardMaker::getInst() {
    static CardMaker inst;
    return inst;
}

int CardMaker::registerCard(const Maker& m) {
    factories.push_back(m);
    return (int)(factories.size() - 1);
}

std::unique_ptr<Card> CardMaker::create(uint16_t id) {
	
	if(id >= factories.size()) {
		std::cout<< "Error - card out of range : " << 0 << " to "<< factories.size() - 1 << std::endl;
		return nullptr;	
	} 
    return factories[id]();
}


std::unique_ptr<Card> createPlains() {
	std::unique_ptr<Land> card (new Land(0, "Plains", Color::WHITE));
	return std::move(card);
}

std::unique_ptr<Card> createIsland() {
	std::unique_ptr<Land> card (new Land(1, "Island", Color::BLUE));
	return std::move(card);
}

std::unique_ptr<Card> createSwamp() {
	std::unique_ptr<Land> card (new Land(2, "Swamp", Color::BLACK));
	return std::move(card);
}

std::unique_ptr<Card> createMountain() {
	std::unique_ptr<Land> card (new Land(3, "Mountain", Color::RED));
	return std::move(card);
}

std::unique_ptr<Card> createForest() {
	std::unique_ptr<Land> card (new Land(4, "Forest", Color::GREEN));
	return std::move(card);
}


std::unique_ptr<Card> createCharmedStray() {
    std::map<Color, int> cost =  {{Color::WHITE, 1}};
	std::unique_ptr<Creature> card (new Creature(5, "Charmed Stray", cost, 1, 1));
	card.get()->addStaticAbility(StaticAbility::LIFELINK);
	//TODO event when enter the battlefield
	return std::move(card);
}


std::unique_ptr<Card> createSanctuaryCat() {
    std::map<Color, int> cost =  {{Color::WHITE, 1}};
	std::unique_ptr<Creature> card (new Creature(6, "Sanctuary Cat", cost, 1, 2));
	return std::move(card);
}

std::unique_ptr<Card> createSoulmender() {
	std::map<Color, int> cost =  {{Color::WHITE, 1}};
	std::unique_ptr<Creature> card (new Creature(7, "Soulmender", cost, 1, 1));
	//TODO event when tapped
	return std::move(card);
}

// std::unique_ptr<Card> createTacticalAdvantage() {
// 	std::map<Color, int> cost =  {{Color::WHITE, 1}};
// 	std::unique_ptr<Instant> card (new Instant(8, "Sanctuary Cat", cost, 1, 1));
// 	//TODO event when tapped
// 	return std::move(card);
// }

std::unique_ptr<Card> createFencingAce() {
	std::map<Color, int> cost =  {{Color::WHITE, 1}, {Color::WBBRG, 1}};
	std::unique_ptr<Creature> card (new Creature(9, "Fencing Ace", cost, 1, 1));
	card.get()->addStaticAbility(StaticAbility::DOUBLE_STRIKE);
	return std::move(card);
}

std::unique_ptr<Card> createHallowedPriest() {
	std::map<Color, int> cost =  {{Color::WHITE, 1}, {Color::WBBRG, 1}};
	std::unique_ptr<Creature> card (new Creature(10, "Hallowed Priest", cost, 1, 1));
	//TODO whenever you gain life
	return std::move(card);
}

std::unique_ptr<Card> createImpassionedOrator() {
	std::map<Color, int> cost =  {{Color::WHITE, 1}, {Color::WBBRG, 1}};
	std::unique_ptr<Creature> card (new Creature(11, "Impassioned Orator", cost, 2, 2));
	//TODO whenever a creature enter the battlefield
	return std::move(card);
}

// std::unique_ptr<Card> createKnightsPledge() {
// 	std::map<Color, int> cost =  {{Color::WHITE, 1}, {Color::WBBRG, 1}};
// 	std::unique_ptr<Enchantement> card (new Enchantement(12, "Hallowed Priest", cost, 1, 1));
// 	return std::move(card);
// }

std::unique_ptr<Card> createMoorlandInquisitor() {
	std::map<Color, int> cost =  {{Color::WHITE, 1}, {Color::WBBRG, 1}};
	std::unique_ptr<Creature> card (new Creature(13, "Moorland Inquisitor", cost, 2, 2));
	//TODO ability
	return std::move(card);
}

// std::unique_ptr<Card> createPacifism() {
// 	std::map<Color, int> cost =  {{Color::WHITE, 1}, {Color::WBBRG, 1}};
// 	std::unique_ptr<Enchantement> card (new Enchantement(14, "Pacifism", cost, 2, 2));
// 	//TODO ability
// 	return std::move(card);
// }


std::unique_ptr<Card> createShrineKeeper() {
	std::map<Color, int> cost =  {{Color::WHITE, 2}};
	std::unique_ptr<Creature> card (new Creature(15, "Shrine Keeper", cost, 2, 2));
	return std::move(card);
}

std::unique_ptr<Card> createAngelofVitality() {
	std::map<Color, int> cost =  {{Color::WHITE, 1}, {Color::WBBRG, 2}};
	std::unique_ptr<Creature> card (new Creature(16, "Angel of Vitality", cost, 2, 2));
	card.get()->addStaticAbility(StaticAbility::FLY);
	return std::move(card);
}

std::unique_ptr<Card> createLoxodonLineBreaker() {
	std::map<Color, int> cost =  {{Color::WHITE, 1}, {Color::WBBRG, 2}};
	std::unique_ptr<Creature> card (new Creature(17, "Loxodon Line Breaker", cost, 3, 2));
	return std::move(card);
}

std::unique_ptr<Card> createLeoninWarleader() {
	std::map<Color, int> cost =  {{Color::WHITE, 2}, {Color::WBBRG, 2}};
	std::unique_ptr<Creature> card (new Creature(18, "Leonin Warleader", cost, 4, 4));
	//TODO when attack
	return std::move(card);
}

// std::unique_ptr<Card> createAngelicReward() {
// 	std::map<Color, int> cost =  {{Color::WHITE, 2}, {Color::WBBRG, 3}};
// 	std::unique_ptr<Enchantement> card (new Enchantement(19, "Leonin Warleader", cost, 4, 4));
// 	//TODO when attack
// 	return std::move(card);
// }

// std::unique_ptr<Card> createBondofDiscipline() {
// 	std::map<Color, int> cost =  {{Color::WHITE, 2}, {Color::WBBRG, 2}};
// 	std::unique_ptr<Creature> card (new Creature(20, "Leonin Warleader", cost, 4, 4));
// 	//TODO when attack
// 	return std::move(card);
// }

// std::unique_ptr<Card> createConfronttheAssault() {
// 	std::map<Color, int> cost =  {{Color::WHITE, 2}, {Color::WBBRG, 2}};
// 	std::unique_ptr<Creature> card (new Creature(21, "Leonin Warleader", cost, 4, 4));
// 	//TODO when attack
// 	return std::move(card);
// }

std::unique_ptr<Card> createSerraAngel() {
	std::map<Color, int> cost =  {{Color::WHITE, 2}, {Color::WBBRG, 3}};
	std::unique_ptr<Creature> card (new Creature(22, "Serra Angel", cost, 4, 4));
	card.get()->addStaticAbility(StaticAbility::FLY);
	card.get()->addStaticAbility(StaticAbility::VIGILANCE);
	return std::move(card);
}

std::unique_ptr<Card> createSpiritualGuardian() {
	std::map<Color, int> cost =  {{Color::WHITE, 2}, {Color::WBBRG, 3}};
	std::unique_ptr<Creature> card (new Creature(23, "Spiritual Guardian", cost, 3, 4));
	//TODO when enter the battlefield
	return std::move(card);
}

std::unique_ptr<Card> createAngelicGuardian() {
	std::map<Color, int> cost =  {{Color::WHITE, 2}, {Color::WBBRG, 4}};
	std::unique_ptr<Creature> card (new Creature(24, "Angelic Guardian", cost, 5, 5));
	card.get()->addStaticAbility(StaticAbility::FLY);
	//TODO
	return std::move(card);
}

std::unique_ptr<Card> createInspiringCommander() {
	std::map<Color, int> cost =  {{Color::WHITE, 2}, {Color::WBBRG, 4}};
	std::unique_ptr<Creature> card (new Creature(25, "Inspiring Commander", cost, 1, 4));
	//TODO when enter battlefield
	return std::move(card);
}

std::unique_ptr<Card> createGoringCeratops() {
	std::map<Color, int> cost =  {{Color::WHITE, 2}, {Color::WBBRG, 5}};
	std::unique_ptr<Creature> card (new Creature(26, "Goring Ceratops", cost, 3, 3));
	card.get()->addStaticAbility(StaticAbility::DOUBLE_STRIKE);
	//TODO 
	return std::move(card);
}


// std::unique_ptr<Card> createRiversFavor() {
// 	std::map<Color, int> cost =  {{Color::WHITE, 2}, {Color::WBBRG, 5}};
// 	std::unique_ptr<Enchantement> card (new Enchantement(27, "Goring Ceratops", cost, 3, 3));
// 	card.get()->addStaticAbility(StaticAbility::DOUBLE_STRIKE);
// 	//TODO 
// 	return std::move(card);
// }

// std::unique_ptr<Card> createUnsummon() {
// 	std::map<Color, int> cost =  {{Color::WHITE, 2}, {Color::WBBRG, 5}};
// 	std::unique_ptr<Enchantement> card (new Enchantement(28, "Goring Ceratops", cost, 3, 3));
// 	card.get()->addStaticAbility(StaticAbility::DOUBLE_STRIKE);
// 	//TODO 
// 	return std::move(card);
// }

std::unique_ptr<Card> createWallofRunes() {
	std::map<Color, int> cost =  {{Color::BLUE, 1}};
	std::unique_ptr<Creature> card (new Creature(29, "Wall of Runes", cost, 0, 4));
	card.get()->addStaticAbility(StaticAbility::DEFENDER);
	//TODO 
	return std::move(card);
}

std::unique_ptr<Card> createZephyrGull() {
	std::map<Color, int> cost =  {{Color::BLUE, 1}};
	std::unique_ptr<Creature> card (new Creature(30, "Zephyr Gull", cost, 1, 1));
	card.get()->addStaticAbility(StaticAbility::FLY);
	return std::move(card);
}

std::unique_ptr<Card> createCoralMerfolk() {
	std::map<Color, int> cost =  {{Color::BLUE, 1}, {Color::WBBRG, 1}};
	std::unique_ptr<Creature> card (new Creature(31, "Coral Merfolk", cost, 2, 1));
	return std::move(card);
}

// std::unique_ptr<Card> createGlint() {
// 	std::map<Color, int> cost =  {{Color::WHITE, 2}, {Color::WBBRG, 5}};
// 	std::unique_ptr<Instant> card (new Instant(32, "Goring Ceratops", cost, 3, 3));
// 	card.get()->addStaticAbility(StaticAbility::DOUBLE_STRIKE);
// 	//TODO 
// 	return std::move(card);
// }

std::unique_ptr<Card> createSwornGuardian() {
	std::map<Color, int> cost =  {{Color::BLUE, 1}, {Color::WBBRG, 1}};
	std::unique_ptr<Creature> card (new Creature(33, "Sworn Guardian", cost, 1, 3));
	return std::move(card);
}

std::unique_ptr<Card> createWaterkinShaman() {
	std::map<Color, int> cost =  {{Color::BLUE, 1}, {Color::WBBRG, 1}};
	std::unique_ptr<Creature> card (new Creature(34, "Waterkin Shaman", cost, 2, 1));
	//TODO 
	return std::move(card);
}

std::unique_ptr<Card> createArmoredWhirlTurtle() {
	std::map<Color, int> cost =  {{Color::WHITE, 1}, {Color::WBBRG, 2}};
	std::unique_ptr<Creature> card (new Creature(35, "Armored Whirl Turtle", cost, 0, 5));
	return std::move(card);
}

std::unique_ptr<Card> createCloudkinSeer() {
	std::map<Color, int> cost =  {{Color::BLUE, 1}, {Color::WBBRG, 2}};
	std::unique_ptr<Creature> card (new Creature(36, "Cloudkin Seer", cost, 2, 1));
	card.get()->addStaticAbility(StaticAbility::FLY);
	//TODO 
	return std::move(card);
}

std::unique_ptr<Card> createWardenofEvosIsle() {
	std::map<Color, int> cost =  {{Color::BLUE, 1}, {Color::WBBRG, 2}};
	std::unique_ptr<Creature> card (new Creature(37, "Warden of Evos Isle", cost, 2, 2));
	card.get()->addStaticAbility(StaticAbility::FLY);
	//TODO 
	return std::move(card);
}

// std::unique_ptr<Card> createWaterknot() {
// 	std::map<Color, int> cost =  {{Color::BLUE, 1}, {Color::WBBRG, 2}};
// 	std::unique_ptr<Enchantement> card (new Enchantement(38, "Cloudkin Seer", cost, 2, 1));
// 	card.get()->addStaticAbility(StaticAbility::FLY);
// 	//TODO 
// 	return std::move(card);
// }

// std::unique_ptr<Card> createWingedWords() {
// 	std::map<Color, int> cost =  {{Color::BLUE, 1}, {Color::WBBRG, 2}};
// 	std::unique_ptr<Sorcery> card (new Sorcery(39, "Cloudkin Seer", cost, 2, 1));
// 	card.get()->addStaticAbility(StaticAbility::FLY);
// 	//TODO 
// 	return std::move(card);
// }

std::unique_ptr<Card> createOctoprophet() {
	std::map<Color, int> cost =  {{Color::BLUE, 1}, {Color::WBBRG, 3}};
	std::unique_ptr<Creature> card (new Creature(40, "Octoprophet", cost, 3, 3));
	//TODO 
	return std::move(card);
}

/*
std::unique_ptr<Card> createSleep() {
	auto card = std::make_unique<Creature>();
	return std::move(card);
}

std::unique_ptr<Card> createAirElemental() {
	auto card = std::make_unique<Creature>();
	return std::move(card);
}

std::unique_ptr<Card> createSoulbladeDjinn() {
	auto card = std::make_unique<Creature>();
	return std::move(card);
}

std::unique_ptr<Card> createWindstormDrake() {
	auto card = std::make_unique<Creature>();
	return std::move(card);
}

std::unique_ptr<Card> createFrilledSeaSerpent() {
	auto card = std::make_unique<Creature>();
	return std::move(card);
}

std::unique_ptr<Card> createRiddlemasterSphinx() {
	auto card = std::make_unique<Creature>();
	return std::move(card);
}

std::unique_ptr<Card> createOverflowingInsight() {
	auto card = std::make_unique<Creature>();
	return std::move(card);
}

std::unique_ptr<Card> createWindreaderSphinx() {
	auto card = std::make_unique<Creature>();
	return std::move(card);
}

std::unique_ptr<Card> createCompoundFracture() {
	auto card = std::make_unique<Creature>();
	return std::move(card);
}

std::unique_ptr<Card> createRaiseDead() {
	auto card = std::make_unique<Creature>();
	return std::move(card);
}

std::unique_ptr<Card> createSanitariumSkeleton() {
	auto card = std::make_unique<Creature>();
	return std::move(card);
}

std::unique_ptr<Card> createTyphoidRats() {
	auto card = std::make_unique<Creature>();
	return std::move(card);
}

std::unique_ptr<Card> createCruelCut() {
	auto card = std::make_unique<Creature>();
	return std::move(card);
}

std::unique_ptr<Card> createEternalThirst() {
	auto card = std::make_unique<Creature>();
	return std::move(card);
}

std::unique_ptr<Card> createKrovikanScoundrel() {
	auto card = std::make_unique<Creature>();
	return std::move(card);
}

std::unique_ptr<Card> createMalakirCullblade() {
	auto card = std::make_unique<Creature>();
	return std::move(card);
}

std::unique_ptr<Card> createNimblePilferer() {
	auto card = std::make_unique<Creature>();
	return std::move(card);
}

std::unique_ptr<Card> createUnlikelyAid() {
	auto card = std::make_unique<Creature>();
	return std::move(card);
}

std::unique_ptr<Card> createVampireOpportunist() {
	auto card = std::make_unique<Creature>();
	return std::move(card);
}

std::unique_ptr<Card> createMarduOutrider() {
	auto card = std::make_unique<Creature>();
	return std::move(card);
}

std::unique_ptr<Card> createMurder() {
	auto card = std::make_unique<Creature>();
	return std::move(card);
}

std::unique_ptr<Card> createSavageGorger() {
	auto card = std::make_unique<Creature>();
	return std::move(card);
}

std::unique_ptr<Card> createScatheZombies() {
	auto card = std::make_unique<Creature>();
	return std::move(card);
}

std::unique_ptr<Card> createWitchsFamiliar() {
	auto card = std::make_unique<Creature>();
	return std::move(card);
}

std::unique_ptr<Card> createSkeletonArcher() {
	auto card = std::make_unique<Creature>();
	return std::move(card);
}

std::unique_ptr<Card> createSengirVampire() {
	auto card = std::make_unique<Creature>();
	return std::move(card);
}

std::unique_ptr<Card> createSoulhunterRakshasa() {
	auto card = std::make_unique<Creature>();
	return std::move(card);
}

std::unique_ptr<Card> createBadDeal() {
	auto card = std::make_unique<Creature>();
	return std::move(card);
}

std::unique_ptr<Card> createNightmare() {
	auto card = std::make_unique<Creature>();
	return std::move(card);
}

std::unique_ptr<Card> createDemonofLoathing() {
	auto card = std::make_unique<Creature>();
	return std::move(card);
}

std::unique_ptr<Card> createRagingGoblin() {
	auto card = std::make_unique<Creature>();
	return std::move(card);
}

std::unique_ptr<Card> createShock() {
	auto card = std::make_unique<Creature>();
	return std::move(card);
}

std::unique_ptr<Card> createStormStrike() {
	auto card = std::make_unique<Creature>();
	return std::move(card);
}

std::unique_ptr<Card> createTinStreetCadet() {
	auto card = std::make_unique<Creature>();
	return std::move(card);
}

std::unique_ptr<Card> createGoblinTunneler() {
	auto card = std::make_unique<Creature>();
	return std::move(card);
}

std::unique_ptr<Card> createManiacalRage() {
	auto card = std::make_unique<Creature>();
	return std::move(card);
}

std::unique_ptr<Card> createNestRobber() {
	auto card = std::make_unique<Creature>();
	return std::move(card);
}

std::unique_ptr<Card> createBombard() {
	auto card = std::make_unique<Creature>();
	return std::move(card);
}

std::unique_ptr<Card> createBurnBright() {
	auto card = std::make_unique<Creature>();
	return std::move(card);
}

std::unique_ptr<Card> createFearlessHalberdier() {
	auto card = std::make_unique<Creature>();
	return std::move(card);
}

std::unique_ptr<Card> createGoblinGathering() {
	auto card = std::make_unique<Creature>();
	return std::move(card);
}

std::unique_ptr<Card> createHurloonMinotaur() {
	auto card = std::make_unique<Creature>();
	return std::move(card);
}

std::unique_ptr<Card> createMoltenRavager() {
	auto card = std::make_unique<Creature>();
	return std::move(card);
}

std::unique_ptr<Card> createRaidBombardment() {
	auto card = std::make_unique<Creature>();
	return std::move(card);
}

std::unique_ptr<Card> createGoblinGangLeader() {
	auto card = std::make_unique<Creature>();
	return std::move(card);
}

std::unique_ptr<Card> createGoblinTrashmaster() {
	auto card = std::make_unique<Creature>();
	return std::move(card);
}

std::unique_ptr<Card> createOgreBattledriver() {
	auto card = std::make_unique<Creature>();
	return std::move(card);
}

std::unique_ptr<Card> createImmortalPhoenix() {
	auto card = std::make_unique<Creature>();
	return std::move(card);
}

std::unique_ptr<Card> createInescapableBlaze() {
	auto card = std::make_unique<Creature>();
	return std::move(card);
}

std::unique_ptr<Card> createVolcanicDragon() {
	auto card = std::make_unique<Creature>();
	return std::move(card);
}

std::unique_ptr<Card> createSiegeDragon() {
	auto card = std::make_unique<Creature>();
	return std::move(card);
}

std::unique_ptr<Card> createChargingBadger() {
	auto card = std::make_unique<Creature>();
	return std::move(card);
}

std::unique_ptr<Card> createJungleDelver() {
	auto card = std::make_unique<Creature>();
	return std::move(card);
}

std::unique_ptr<Card> createStonyStrength() {
	auto card = std::make_unique<Creature>();
	return std::move(card);
}

std::unique_ptr<Card> createFeralRoar() {
	auto card = std::make_unique<Creature>();
	return std::move(card);
}

std::unique_ptr<Card> createGreenwoodSentinel() {
	auto card = std::make_unique<Creature>();
	return std::move(card);
}

std::unique_ptr<Card> createIlysianCaryatid() {
	auto card = std::make_unique<Creature>();
	return std::move(card);
}

std::unique_ptr<Card> createRabidBite() {
	auto card = std::make_unique<Creature>();
	return std::move(card);
}

std::unique_ptr<Card> createTitanicGrowth() {
	auto card = std::make_unique<Creature>();
	return std::move(card);
}

std::unique_ptr<Card> createTreetopWarden() {
	auto card = std::make_unique<Creature>();
	return std::move(card);
}

std::unique_ptr<Card> createWoodlandMystic() {
	auto card = std::make_unique<Creature>();
	return std::move(card);
}

std::unique_ptr<Card> createColossalMajesty() {
	auto card = std::make_unique<Creature>();
	return std::move(card);
}

std::unique_ptr<Card> createGenerousStray() {
	auto card = std::make_unique<Creature>();
	return std::move(card);
}

std::unique_ptr<Card> createWildwoodPatrol() {
	auto card = std::make_unique<Creature>();
	return std::move(card);
}

std::unique_ptr<Card> createBalothPackhunter() {
	auto card = std::make_unique<Creature>();
	return std::move(card);
}

std::unique_ptr<Card> createPrizedUnicorn() {
	auto card = std::make_unique<Creature>();
	return std::move(card);
}

std::unique_ptr<Card> createRumblingBaloth() {
	auto card = std::make_unique<Creature>();
	return std::move(card);
}

std::unique_ptr<Card> createWorldShaper() {
	auto card = std::make_unique<Creature>();
	return std::move(card);
}

std::unique_ptr<Card> createGigantosaurus() {
	auto card = std::make_unique<Creature>();
	return std::move(card);
}

std::unique_ptr<Card> createSentinelSpider() {
	auto card = std::make_unique<Creature>();
	return std::move(card);
}

std::unique_ptr<Card> createEpicProportions() {
	auto card = std::make_unique<Creature>();
	return std::move(card);
}

std::unique_ptr<Card> createRampagingBrontodon() {
	auto card = std::make_unique<Creature>();
	return std::move(card);
}
*/

/*
std::unique_ptr<Card> createCat() {
	auto card = std::make_unique<Creature>();
	return std::move(card);
}

std::unique_ptr<Card> createSpirit() {
	auto card = std::make_unique<Creature>();
	return std::move(card);
}

std::unique_ptr<Card> createGoblin() {
	auto card = std::make_unique<Creature>();
	return std::move(card);
}
*/

CardMaker::CardMaker() {
	//lands
	registerCard(createPlains); //0
    registerCard(createIsland); //1
	registerCard(createSwamp); //2
    registerCard(createMountain); //3
	registerCard(createForest); //4
	
    //cards
    registerCard(createCharmedStray); //5
    registerCard(createSanctuaryCat); //6
    registerCard(createSoulmender); //7
    // registerCard(createTacticalAdvantage);
    registerCard(createFencingAce); //8
    registerCard(createHallowedPriest); //9
    registerCard(createImpassionedOrator); //10
    // registerCard(createKnightsPledge);
    registerCard(createMoorlandInquisitor); //11
    // registerCard(createPacifism);
    registerCard(createShrineKeeper); //12
    registerCard(createAngelofVitality); //13
    registerCard(createLoxodonLineBreaker); //14
    registerCard(createLeoninWarleader); //15
    // registerCard(createAngelicReward);
    // registerCard(createBondofDiscipline);
    // registerCard(createConfronttheAssault);
    registerCard(createSerraAngel); //16
    registerCard(createSpiritualGuardian); //17
    registerCard(createAngelicGuardian); //18
    registerCard(createInspiringCommander); //19
    registerCard(createGoringCeratops); //20
    // registerCard(createRiversFavor);
    // registerCard(createUnsummon);
    registerCard(createWallofRunes); //21
    registerCard(createZephyrGull); //22
    registerCard(createCoralMerfolk); //23
    // registerCard(createGlint);
    registerCard(createSwornGuardian); //24
    registerCard(createWaterkinShaman); //25
    registerCard(createArmoredWhirlTurtle); //26
    registerCard(createCloudkinSeer); //27
    registerCard(createWardenofEvosIsle); //28
    // registerCard(createWaterknot);
    // registerCard(createWingedWords);
    registerCard(createOctoprophet); //29
    // registerCard(createSleep);
    // registerCard(createAirElemental);
    // registerCard(createSoulbladeDjinn);
    // registerCard(createWindstormDrake);
    // registerCard(createFrilledSeaSerpent);
    // registerCard(createRiddlemasterSphinx);
    // registerCard(createOverflowingInsight);
    // registerCard(createWindreaderSphinx);
    // registerCard(createCompoundFracture);
    // registerCard(createRaiseDead);
    // registerCard(createSanitariumSkeleton);
    // registerCard(createTyphoidRats);
    // registerCard(createCruelCut);
    // registerCard(createEternalThirst);
    // registerCard(createKrovikanScoundrel);
    // registerCard(createMalakirCullblade);
    // registerCard(createNimblePilferer);
    // registerCard(createUnlikelyAid);
    // registerCard(createVampireOpportunist);
    // registerCard(createMarduOutrider);
    // registerCard(createMurder);
    // registerCard(createSavageGorger);
    // registerCard(createScatheZombies);
    // registerCard(createWitchsFamiliar);
    // registerCard(createSkeletonArcher);
    // registerCard(createSengirVampire);
    // registerCard(createSoulhunterRakshasa);
    // registerCard(createBadDeal);
    // registerCard(createNightmare);
    // registerCard(createDemonofLoathing);
    // registerCard(createRagingGoblin);
    // registerCard(createShock);
    // registerCard(createStormStrike);
    // registerCard(createTinStreetCadet);
    // registerCard(createGoblinTunneler);
    // registerCard(createManiacalRage);
    // registerCard(createNestRobber);
    // registerCard(createBombard);
    // registerCard(createBurnBright);
    // registerCard(createFearlessHalberdier);
    // registerCard(createGoblinGathering);
    // registerCard(createHurloonMinotaur);
    // registerCard(createMoltenRavager);
    // registerCard(createRaidBombardment);
    // registerCard(createGoblinGangLeader);
    // registerCard(createGoblinTrashmaster);
    // registerCard(createOgreBattledriver);
    // registerCard(createImmortalPhoenix);
    // registerCard(createInescapableBlaze);
    // registerCard(createVolcanicDragon);
    // registerCard(createSiegeDragon);
    // registerCard(createChargingBadger);
    // registerCard(createJungleDelver);
    // registerCard(createStonyStrength);
    // registerCard(createFeralRoar);
    // registerCard(createGreenwoodSentinel);
    // registerCard(createIlysianCaryatid);
    // registerCard(createRabidBite);
    // registerCard(createTitanicGrowth);
    // registerCard(createTreetopWarden);
    // registerCard(createWoodlandMystic);
    // registerCard(createColossalMajesty);
    // registerCard(createGenerousStray);
    // registerCard(createWildwoodPatrol);
    // registerCard(createBalothPackhunter);
    // registerCard(createPrizedUnicorn);
    // registerCard(createRumblingBaloth);
    // registerCard(createWorldShaper);
    // registerCard(createGigantosaurus);
    // registerCard(createSentinelSpider);
    // registerCard(createEpicProportions);
    // registerCard(createRampagingBrontodon);


}
