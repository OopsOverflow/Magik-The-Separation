//
// Created by pierre on 15/01/2022.
//

#include "CardMaker.h"
#include <iostream>

#include "Creature.h"
#include "Land.h"


CardMaker& CardMaker::getInst() {
    static CardMaker inst;
    return inst;
}

int CardMaker::registerCard(Maker m) {
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
	std::unique_ptr<Land> card (new Land(2, "Plains", Color::BLACK));
	return std::move(card);
}

std::unique_ptr<Card> createMountain() {
	std::unique_ptr<Land> card (new Land(3, "Plains", Color::RED));
	return std::move(card);
}

std::unique_ptr<Card> createForest() {
	std::unique_ptr<Land> card (new Land(4, "Plains", Color::GREEN));
	return std::move(card);
}


std::unique_ptr<Card> createCharmedStray() {
    std::map<Color, int> cost =  {{Color::WHITE, 1}};
	std::unique_ptr<Creature> card (new Creature(5, "Charmed Stray", cost, 1, 1));
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
	return std::move(card);;
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
	//TODO Double strike
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
	//TODO
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
	//TODO static
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
	//TODO 
	return std::move(card);
}

/*
std::unique_ptr<Card> createRiversFavor() {
	auto card = std::make_unique<Creature>();
	return std::move(card);
}

std::unique_ptr<Card> createUnsummon() {
	auto card = std::make_unique<Creature>();
	return std::move(card);
}

std::unique_ptr<Card> createWallofRunes() {
	auto card = std::make_unique<Creature>();
	return std::move(card);
}

std::unique_ptr<Card> createZephyrGull() {
	auto card = std::make_unique<Creature>();
	return std::move(card);
}

std::unique_ptr<Card> createCoralMerfolk() {
	auto card = std::make_unique<Creature>();
	return std::move(card);
}

std::unique_ptr<Card> createGlint() {
	auto card = std::make_unique<Creature>();
	return std::move(card);
}

std::unique_ptr<Card> createSwornGuardian() {
	auto card = std::make_unique<Creature>();
	return std::move(card);
}

std::unique_ptr<Card> createWaterkinShaman() {
	auto card = std::make_unique<Creature>();
	return std::move(card);
}

std::unique_ptr<Card> createArmoredWhirlTurtle() {
	auto card = std::make_unique<Creature>();
	return std::move(card);
}

std::unique_ptr<Card> createCloudkinSeer() {
	auto card = std::make_unique<Creature>();
	return std::move(card);
}

std::unique_ptr<Card> createWardenofEvosIsle() {
	auto card = std::make_unique<Creature>();
	return std::move(card);
}

std::unique_ptr<Card> createWaterknot() {
	auto card = std::make_unique<Creature>();
	return std::move(card);
}

std::unique_ptr<Card> createWingedWords() {
	auto card = std::make_unique<Creature>();
	return std::move(card);
}

std::unique_ptr<Card> createOctoprophet() {
	auto card = std::make_unique<Creature>();
	return std::move(card);
}

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
	registerCard(createPlains);
    registerCard(createIsland);
	registerCard(createSwamp);
    registerCard(createMountain);
	registerCard(createForest);
	
    //cards
    registerCard(createCharmedStray);
    registerCard(createSanctuaryCat);
    registerCard(createSoulmender);
    // registerCard(createTacticalAdvantage);
    registerCard(createFencingAce);
    registerCard(createHallowedPriest);
    registerCard(createImpassionedOrator);
    // registerCard(createKnightsPledge);
    registerCard(createMoorlandInquisitor);
    // registerCard(createPacifism);
    registerCard(createShrineKeeper);
    registerCard(createAngelofVitality);
    registerCard(createLoxodonLineBreaker);
    registerCard(createLeoninWarleader);
    // registerCard(createAngelicReward);
    // registerCard(createBondofDiscipline);
    // registerCard(createConfronttheAssault);
    registerCard(createSerraAngel);
    registerCard(createSpiritualGuardian);
    registerCard(createAngelicGuardian);
    registerCard(createInspiringCommander);
    registerCard(createGoringCeratops);
    // registerCard(createRiversFavor);
    // registerCard(createUnsummon);
    // registerCard(createWallofRunes);
    // registerCard(createZephyrGull);
    // registerCard(createCoralMerfolk);
    // registerCard(createGlint);
    // registerCard(createSwornGuardian);
    // registerCard(createWaterkinShaman);
    // registerCard(createArmoredWhirlTurtle);
    // registerCard(createCloudkinSeer);
    // registerCard(createWardenofEvosIsle);
    // registerCard(createWaterknot);
    // registerCard(createWingedWords);
    // registerCard(createOctoprophet);
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
