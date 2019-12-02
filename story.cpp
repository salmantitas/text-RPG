#include "story.h"

using namespace std;

Story::Story() {
    unfinished = "Unfinished storyline. Press [1] to end game.";
    fin = endChoice();
}

// Warrior Storyline
Choice Story::warriorStoryline()
{
    Choice root;
    root.addText("Ever since you were a child, you have aspired to be a warrior.");
    root.addText("You've seen how great warriors are respected and you have trained from a tender age to be just like them.");
    root.addText("And then one day, your village is attacked by bandits.");
    root.addText("On one hand, you feel the thrill of finally proving your mettle.");
    root.addText("You know that this is the chance you've been waiting for all your life.");
    root.addText("On the other, you realize that you've never been in a real fight before. A wrong move could get you killed.");
    root.addText("Your choices will determine the fate of the ones around you... and of yourself.");
    root.addText("Press [1] to stay and fight!");
    root.addText("Press [2] to run");
    Choice fightPath = warriorFightPath();
    Choice runPath = warriorRunPath();
    root.addChoice(fightPath);
    root.addChoice(runPath);
    return root;
}

// Warrior Path 1: Defend The Village
Choice Story::warriorFightPath()
{
    Choice outAdventure;
    outAdventure.addText("You head out into the world for adventure.");
    outAdventure.addText(unfinished);
//    outAdventure.addChoice(fin);

    Choice relayRunVillage;
    relayRunVillage.addText("You tell yourself that it's not worth getting into a fight.");
    relayRunVillage.markRelay();
    relayRunVillage.addConsequence(AGL_BOOST);
    relayRunVillage.addChoice(outAdventure);

    Choice relayLeaveVillage;
    relayLeaveVillage.addText("You realize that a village where you aren't valued has no meaning to you. So you leave.");
    relayLeaveVillage.markRelay();
    relayLeaveVillage.addChoice(outAdventure);

    Choice overpowered;
    overpowered.addText("You are overpowered by the villagers. There is no way you could taken them on.");
    overpowered.addText("You are disarmed, and then killed.");

    Choice massacreVillage;
    massacreVillage.addText("Suddenly you charge yourself on the nearest person, stabbing your sword into him.");
    massacreVillage.addText("Who he was does not really matter. What matters is that you were challenged.");
    massacreVillage.addText("After the initial onslaught, it becomes clear there are only so many that you can kill.");
    massacreVillage.addText("The villagers retaliate and you sustain an injury.");
    massacreVillage.addText("[1] Continue fighting.");
    massacreVillage.addText("[2] Run away from the village");
    massacreVillage.addConsequence(STR_BOOST);
    for (int i = 0; i < 6; i++)
        massacreVillage.addConsequence(KARMA_DROP);
    massacreVillage.addChoice(overpowered);

    Choice banditDeath;
    banditDeath.addText("The bandits overpower you and kill you.");

    Choice secureOutpost;
    secureOutpost.addText("You secure the outpost.");
    secureOutpost.addText(unfinished);
//    secureOutpost.addChoice(fin);

    Choice surrenderVillage;
    surrenderVillage.addText("You've surrendered to the village elders.");
    surrenderVillage.addText(unfinished);
//    surrenderVillage.addChoice(fin);

    Choice challengeElders;
    challengeElders.addText("You have challenged the authority of the elders.");
    challengeElders.addText(unfinished);
//    challengeElders.addChoice(fin);

    Choice relayRunAway;
    relayRunAway.addText("You run away!");
    relayRunAway.markRelay();
    relayRunAway.addChoice(outAdventure);

    massacreVillage.addChoice(relayRunAway);

    Choice killElders;
    killElders.addText("Faced against the threat of the elders, you suddenly draw your sword and launch yourself upon the elders.");
    killElders.addText("Your sudden onslaught takes everyone by surprise, and you cut through the elders like butter.");
    killElders.addText("Bathed in blood, you stand before the village as the rest stare at you in awe.");
    killElders.addText("You see that there are a few choices in front of you.");
    killElders.addText("[1] Take over the village.");
    killElders.addText("[2] Leave.");
    // drop karma 6 times
    for (int i = 0; i < 6; i++)
        killElders.addConsequence(KARMA_DROP);
    killElders.addConsequence(STR_BOOST);
    killElders.addConsequence(DEF_DROP);
    killElders.addCondCons(STR_DROP, 0.6, 0);

    Choice killEldersFail;
    killEldersFail.addText("The villagers kill you.");
    killEldersFail.addText(unfinished);
    killEldersFail.addChoice(fin);

    killElders.addCondChoice(killEldersFail);

    Choice villageTakeover;
    villageTakeover.addText(unfinished);
    villageTakeover.addChoice(fin);

    killElders.addChoice(villageTakeover);
    killElders.addChoice(relayLeaveVillage);

    Choice gotoOutpost;
    gotoOutpost.addText(unfinished);

    Choice jailDeath;
    jailDeath.addText("You give in to despair. After a few days, you are hanged.");

    Choice jailAttackGuardFail;

    Choice jailAttackGuard;

    Choice relayScream;
    relayScream.addText("You scream, cursing the villagers and jailers, but no one heeds you.");
    relayScream.markRelay();
//    relayScream.addConsequence(Cons.STR_DROP);

    Choice jailLockpickFail;

    Choice jailLockpick;

    Choice jailWait;
    jailWait.addText("You wait and think of what you can do now. You take a look at your cellmates.");
    jailWait.addText("Of them in particular appears to be an old thief.");
    jailWait.addText("After a short conversation, he hands you a lockpick, so that you can try your luck.");
    jailWait.addText("Press [1] to give up hope.");
    jailWait.addText("Press [2] to attempt to lockpick the door.");
    jailWait.addText("Press [3] to attack the guard when he opens the door to deliver food.");
    jailWait.addChoice(jailDeath);

    Choice jail;
    jail.addText("You have been thrown into the jail in a cell along with some other people. Your fate is uncertain.");
    jail.addText("Press [1] to give up hope.");
    jail.addText("Press [2] to scream.");
    jail.addText("Press [3] to wait and think.");
    jail.addChoice(jailDeath);
    jail.addChoice(relayScream);
    jail.addChoice(jailWait);

    Choice relayAttemptRunFail;
    relayAttemptRunFail.addText("You try to run away, but you can barely make it to the door before your are captured.");
    relayAttemptRunFail.markRelay();
    relayAttemptRunFail.addChoice(jail);

    Choice attemptRun;
    attemptRun.addText("Before anyone else realizes, you run for it. You are too fast for anyone to catch.");
    attemptRun.addText("You make it out of the village, and you count your options.");
    attemptRun.addText("Press [1] to leave village.");
    attemptRun.addText("Press [2] to head for the outpost.");
    attemptRun.addChoice(relayLeaveVillage);
    attemptRun.addChoice(gotoOutpost);
    attemptRun.addConsequence(AGL_BOOST);
    attemptRun.addCondCons(AGL_DROP, 0.5, 0);
    attemptRun.addCondChoice(relayAttemptRunFail);

    Choice faceElders;
    faceElders.addText("You have decided to allow yourself to be lead to the elders.");
    faceElders.addText("Upon meeting them, you realize that they demand you be judged for violating the authority of the eldrs.");
    faceElders.addText("Cornered against the wall, you find that you only have four options at hand.");
    faceElders.addText("[1] Surrender to fate and await judgement.");
    faceElders.addText("[2] Challenge the authority of the council.");
    faceElders.addText("[3] Attempt to run away.");
    faceElders.addText("[4] Kill all the elders.");
    faceElders.addChoice(surrenderVillage);
    faceElders.addChoice(challengeElders);
    faceElders.addChoice(attemptRun);
    faceElders.addChoice(killElders);

    Choice returnVillage;
    returnVillage.addText("You return to the village to deliver the news of the outpost.");
    returnVillage.addText("You greet the first villager you see, but instead of greeting you with glee, he appears nervous.");
    returnVillage.addText("Upon questioninig, he reveals that in your absense, the elders have caught up to what had happened.");
    returnVillage.addText("The elders are not pleased with how the decisions were made without their presence.");
    returnVillage.addText("For that matter, they've decided to blame you for defying their authority.");
    returnVillage.addText("You have been ordered to be brought in front of the elders as soon as you return.");
    returnVillage.addText("[1] Stand before the elders.");
    returnVillage.addText("[2] Run away before they have a chance of confronting you.");
    returnVillage.addChoice(faceElders);
    returnVillage.addChoice(relayRunAway);

    Choice attackAlone;
    attackAlone.addText("You make your way to the bandit's hideout and attack alone.");
    attackAlone.addText("You emerge victorious as you slaughter every last one of them.");
    attackAlone.addText("After the fight, as the battle lust ebbs away, you realize you are a force to be reckoned with.");
    attackAlone.addText("You could return to your village or you could move forward, see what fate has in store.");
    attackAlone.addText("[1] Return to the village.");
    attackAlone.addText("[2] Head out for adventure.");
    attackAlone.addConsequence(STR_BOOST);
    attackAlone.addConsequence(AGL_BOOST);
    attackAlone.addCondCons(STR_DROP, 0.5, 0);
    attackAlone.addCondChoice(banditDeath);
    attackAlone.addChoice(returnVillage);
    attackAlone.addChoice(outAdventure);

    Choice relayAttackAlone;
    relayAttackAlone.addText("No one heeds your call to arms.");
    relayAttackAlone.addText("Frustrated at their lack of faith, you decide to do the only thing that's left.");
    relayAttackAlone.markRelay();
    relayAttackAlone.addChoice(attackAlone);

    Choice drawSword;
    drawSword.addText("You draw your sword and stand menacingly, challenging any who would dare to attack you.");
    drawSword.addText("After a moment, it becomes very clear that no one wants to make an enemy of you.");
    drawSword.addText("[1] Leave the village.");
    drawSword.addText("[2] Vent your rage and kill everyone around you.");
    drawSword.addConsequence(INT_BOOST);
    drawSword.addConsequence(DEF_BOOST);
    drawSword.addChoice(relayLeaveVillage);
    drawSword.addChoice(massacreVillage);

    Choice killBandit;
    killBandit.addText("You decide that because of the crime commited against your people, this bandit has no right to live.");
    killBandit.addText("Your decision angers the entire village.");
    killBandit.addText("People start panicking as they realize that you destroyed their only source of information.");
    killBandit.addText("You realize that you will be attacked soon.");
    killBandit.addText("[1] Run before you are attacked.");
    killBandit.addText("[2] Draw your sword in warning.");
    killBandit.addText("[3] Kill anyone who stands before you.");
    killBandit.addChoice(relayRunVillage);
    killBandit.addChoice(drawSword);
    killBandit.addChoice(massacreVillage);

    Choice raiseArmy;
    raiseArmy.addText("You raise an army consisting of the able-bodied men and women from the village.");
    raiseArmy.addText("The might of your attack takes the wounded and injured bandits by surprise.");
    raiseArmy.addText("Now that an enemy so close to home has been neutralized, you realize there are necessary things at hand.");
    raiseArmy.addText("[1] Secure this outpost and fortify it to protect the village from future attacks.");
    raiseArmy.addText("[2] Return to the village to recount the events.");
    raiseArmy.addText("[3] Heed the call of the adventurer in you and head out on a journey.");
    raiseArmy.addCondCons(KARMA_DROP, 90, 0);
    raiseArmy.addConsequence(STR_BOOST);
    raiseArmy.addConsequence(DEF_BOOST);
    raiseArmy.addChoice(secureOutpost);
    raiseArmy.addChoice(returnVillage);
    raiseArmy.addChoice(outAdventure);
    raiseArmy.addCondChoice(relayAttackAlone);

    Choice dealBandit;
    dealBandit.addText("You offer the bandit a deal. That his past transgressions will be forgiven and will be offered a piece of land.");
    dealBandit.addText("The offer pleases him. Overjoyed, he gives up the location of his past compatriots.");
    dealBandit.addText("[1] Attack alone.");
    dealBandit.addText("[2] Raise an army.");
    dealBandit.addConsequence(KARMA_BOOST);
    dealBandit.addConsequence(INT_BOOST);
    dealBandit.addConsequence(WIS_BOOST);
    dealBandit.addChoice(attackAlone);
    dealBandit.addChoice(raiseArmy);

    Choice tortureBandit;
    tortureBandit.addText("You torture the bandit. After a certain point, he breaks and tells you the whereabouts of their last hideout.");
    tortureBandit.addText("You decide it's time to take the fight to them.");
    tortureBandit.addText("[1] Attack alone.");
    tortureBandit.addText("[2] Attempt to raise an army for the attack.");
    tortureBandit.addConsequence(KARMA_DROP);
    tortureBandit.addConsequence(STR_BOOST);
    tortureBandit.addConsequence(WIS_BOOST);
    tortureBandit.addChoice(attackAlone);
    tortureBandit.addChoice(raiseArmy);

    Choice questionBandit;
    questionBandit.addText("You ask the bandit about the whereabouts of his fellow criminals. However, the bandit remains silent.");
    questionBandit.addText("You consider your options. You could torture the bandit until he speaks. Or you could offer him a better deal.");
    questionBandit.addText("[1] Torture.");
    questionBandit.addText("[2] Deal.");
    questionBandit.addChoice(tortureBandit);
    questionBandit.addChoice(dealBandit);

    Choice defendVillage;
    defendVillage.addText("You decide to stay and fight, for honour and for glory.");
    defendVillage.addText("Should you prevail, you will have saved everyone you know and cared for.");
    defendVillage.addText("And should you fail, you know you will have died for a good cause.");
    defendVillage.addText("At the sight of danger, you enter a battle frenzy, effectively applying all your training in the fight.");
    defendVillage.addText("After a long and arduous battle, you heroicly slay a lot of bandits.");
    defendVillage.addText("The villagers are impressed by your feats. Many are calling you a great hero.");
    defendVillage.addText("Most of the attackers escape, but you manage to capture one.");
    defendVillage.addText("The general opinion is to question the captive about their hideout.");
    defendVillage.addText("But some of the villagers believe that he should immediately be put to death for his crimes against your village.");
    defendVillage.addText("Before the village council is involved, they turn to you - the hero of the battle - to decide.");
    defendVillage.addText("Press [1] to kill the bandit.");
    defendVillage.addText("Press [2] to question the bandit.");
    defendVillage.addConsequence(STR_BOOST);
    defendVillage.addConsequence(DEF_BOOST);
    defendVillage.addConsequence(AGL_BOOST);
    defendVillage.addConsequence(KARMA_BOOST);

    defendVillage.addChoice(killBandit);
    defendVillage.addChoice(questionBandit);

    return defendVillage;
}

// Warrior Path 2: Run Away from the conflict
Choice Story::warriorRunPath()
{
    Choice abandonVillage;
    abandonVillage.addText("You grab your belongings and run.");
    abandonVillage.addText("The screams of those being butchered fill the air, but you keep running.");
    abandonVillage.addText("You keep running until you are sure that you are safe.");
    abandonVillage.addText("Night has fallen. You are too tired to continue. You must rest for the night.");
    abandonVillage.addText("[1] Sleep beside the road.");
    abandonVillage.addText("[2] Sleep in the forest.");
    abandonVillage.addConsequence(KARMA_DROP);

    Choice sleepRoad;
    sleepRoad.addText("You spend the night beside the road.");
    sleepRoad.addText(unfinished);
    sleepRoad.addChoice(fin);

    Choice sleepForest;
    sleepForest.addText("You are sleeping on the forest floor.");
    sleepForest.addText(unfinished);
    sleepForest.addChoice(fin);

    Choice wolfDeath;
    wolfDeath.addText("While you slept defenseless and weak, wolves descend upon you.");
    wolfDeath.addText("You scream as they take you by surprise. Your attempts so defend yourself are in vain.");
    wolfDeath.addText("In the end, you feel life ebb away and welcome death.");
    wolfDeath.addText("It seems as if that would be better than the pain.");

    sleepForest.addCondCons(STR_DROP, 0.5, 0);
    sleepForest.addCondChoice(wolfDeath);

    abandonVillage.addChoice(sleepRoad);
    abandonVillage.addChoice(sleepForest);
    return abandonVillage;
}

Choice Story::rogueStoryline()
{
    Choice root;
    root.addText(unfinished);
    return root;
}

Choice Story::mageStoryline()
{
    return rogueStoryline(); // stub
}

// Helpers

Choice Story::endChoice()
{
    Choice end;
    end.addText("");
    return end;
}
