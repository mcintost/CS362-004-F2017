/* -----------------------------------------------------------------------
** Thomas McIntosh                                                      **
** CS 362-400                                                           **
** Assignment 3 - unittest1.c                                           **
** testing function: adventurer_card()                                  **
**                                                                      **
** cardtest1: cardtest1.c dominion.o                                    **
**      gcc -o cardtest1 cardtest1.c dominion.c rngs.c $(CFLAGS)        **
** -----------------------------------------------------------------------
**/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "rngs.h"

#define NOISY_TEST 1

int main ()
{
    int i;
    int numPlayers = 2;
    int seed = 10;
    int beforeTreasure = 0;
    int afterTreasure = 0;
    int currentCard = -1;
    struct gameState game;
    struct gameState backup;
    int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
    int testsFailed = 0;
	int testHand1[5] = {adventurer, council_room, copper, silver, gold};
	
	initializeGame(numPlayers, k, seed, &game);
	memcpy(game.hand[0], testHand1, 5*sizeof(int));
    memcpy(&backup, &game, sizeof(struct gameState));
	
	playCard(0, 0, 0, 0, &game);
	

	//Test 1: The handCount.
    printf("Expected hand count: %d Reported handCount: %d:"
            ,backup.handCount[0] + 2, game.handCount[0]);
    
	if(backup.handCount[0]+2 == game.handCount[0])
    {
        printf("PASSED\n");
    }
    else
    {
        testsFailed++;
        printf(" FAILED\n");
    }
	
	//Test 2: The deck and discard count. 
	printf("Expected deck and discard: %d Reported deck and discard: %d:"
            ,backup.deckCount[0] + backup.discardCount[0] - 2
            ,game.deckCount[0] + game.discardCount[0]);
			
    
    if((backup.deckCount[0] + backup.discardCount[0] - 2) 
            == (game.deckCount[0] + game.discardCount[0]))
    {
        printf(" PASSED\n");
	}
    else
    {
        testsFailed++;
        printf(" FAILED\n");
    }
    
    
	
    
    //Test 3: Count treasures in hand after adventurer.
    printf("Expected treasure in hand: %d Reported hand treasures: %d:"
            ,beforeTreasure + 2, afterTreasure);

    for (i = 0; i < game.handCount[0]; i++)
    {
        currentCard = game.hand[0][i];
        
        if(currentCard == copper || currentCard == silver || currentCard == gold)
            afterTreasure++;
    }
    
    if(beforeTreasure+2 == afterTreasure)
    {
        printf(" PASSED\n");
    }
    else
    {
        testsFailed++;
        printf(" FAILED\n");
    }

    printf("%d OF %d TESTS PASSED\n", 3-testsFailed, 3);
    
    return 0;

}