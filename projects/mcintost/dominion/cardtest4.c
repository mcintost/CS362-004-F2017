/* -----------------------------------------------------------------------
** Thomas McIntosh                                                      **
** CS 362-400                                                           **
** Assignment 4 - unittest4.c                                           **
** testing function: village_card()                                     **
**                                                                      **
** cardtest4: cardtest4.c dominion.o                                    **
**      gcc -o cardtest4 cardtest4.c dominion.c rngs.c $(CFLAGS)        **
** -----------------------------------------------------------------------
**/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "rngs.h"

#define NOISY_TEST 0

void assert_true(int statement)
{
	if(statement)
	{
		#if (NOISY_TEST == 1)
		printf("Test passed\n");
		#endif
	}
	else
	{
		#if (NOISY_TEST == 1)
		printf("Test failed.\n");
		#endif
	}
	return;
};

int main ()
{
    int numPlayers = 2;
    int seed = 10;
    struct gameState game;
    struct gameState backup;
    int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
    
    int testHand1[5] = {village, adventurer, copper, silver, gold};
    
    initializeGame(numPlayers, k, seed, &game);
    
    memcpy(game.hand[0], testHand1, 5*sizeof(int));  
    memcpy(&backup, &game, sizeof(struct gameState));
    
    playCard(0, 0, 0, 0, &game);
	
	// Test 1: Test hand size before and after playing.
    #if (NOISY_TEST == 1)
	printf("Expected number of cards in hand: %d  Reported number of cards in hand: %d: "
            ,backup.handCount[0]+1-1, game.handCount[0]);
	#endif
	assert_true(backup.handCount[0]+1-1 == game.handCount[0]);
  
    // Test 2: Test the number of cards in deck..
	#if (NOISY_TEST == 1)
    printf("Expected number of cards in the deck: %d  Reported number of cards in the deck: %d: "
            ,backup.deckCount[0]-1,game.deckCount[0]);    
	#endif
	assert_true(backup.deckCount[0]-1 == game.deckCount[0]);

    // Test 3: Test the number of cards played.
	#if (NOISY_TEST == 1)
	printf("Expected number of played cards: %d  Reported number of played cards: %d: "
            ,backup.playedCardCount+1, game.playedCardCount);
	#endif
	assert_true(backup.playedCardCount+1 == game.playedCardCount);
	
    // Test 4: Test the number of actions remaining after playing the card.
	#if (NOISY_TEST == 1)
	printf("Expected number of actions remaining: %d  Reported number of actions remaining: %d: "
            ,backup.numActions+1, game.numActions);
	#endif
	assert_true(game.numActions == backup.numActions+1);
    return 0;
}



























