/* -----------------------------------------------------------------------
** Thomas McIntosh                                                      **
** CS 362-400                                                           **
** Assignment 3 - unittest2.c                                           **
** testing function: smithy_card()                                      **
**                                                                      **
** cardtest2: cardtest2.c dominion.o                                    **
**      gcc -o cardtest2 cardtest2.c dominion.c rngs.c $(CFLAGS)        **
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

int main()
{
	int i;
    int numPlayers = 2;
    int seed = 10;
    int beforeSmithy = 1;
    int afterSmithy = 0;
    int currentCard = -1;
    struct gameState game;
    struct gameState backupGame;
    int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
    int testHand1[5] = {smithy, council_room, copper, silver, gold};
	
	initializeGame(numPlayers, k, seed, &game);
	
	for(i = 0; i < game.handCount[0]; i++)
    {
        game.hand[0][i] = testHand1[i];
    }
	
	memcpy(&backupGame, &game, sizeof(struct gameState));
	
	playCard(0, 0, 0, 0, &game);
	
	
	//Test 1: The number of cards registering as played.
	#if (NOISY_TEST == 1)
	printf("Expected number of played cards: %d  Reported number of played cards: %d: " 
			,backupGame.playedCardCount+1, game.playedCardCount);
	#endif
	assert_true(game.playedCardCount == backupGame.playedCardCount+1);
  
  
    //Test 2: The number of cards in hand after playing the smithy. 
	#if (NOISY_TEST == 1)
	printf("Expected number of cards in hand: %d  Reported number of cards in hand: %d: "
            ,backupGame.handCount[0] + 3 -1, game.handCount[0]);
	#endif
	assert_true(backupGame.handCount[0]+3-1 == game.handCount[0]);
 
    
	//Test 3: The number of cards in deck and discard. 
	#if (NOISY_TEST == 1)
	printf("Expected umber of cards in deck and discard: %d  Reported umber of cards in deck and discard: %d: "
           ,backupGame.deckCount[0] + backupGame.discardCount[0] - 3
           ,game.deckCount[0] + game.discardCount[0]);
	#endif
    assert_true((backupGame.deckCount[0] + backupGame.discardCount[0] - 3) 
            == (game.deckCount[0] + game.discardCount[0]));


    //Test 4: The number of smithies left in the hand. 
	for (i = 0; i < game.handCount[0]; i++)
    {
        currentCard = game.hand[0][i];
        
        if(currentCard == smithy)
            afterSmithy++;
    }
	
	#if (NOISY_TEST == 1)
	printf("Expected number of smithies left in hand: %d  Reported number of smithies left in hand: %d: "
            ,beforeSmithy-1, afterSmithy);
    #endif
	
	// check P1 discarded smithy after cardEffect
    assert_true(afterSmithy == beforeSmithy-1);
    
    
    return 0;

}