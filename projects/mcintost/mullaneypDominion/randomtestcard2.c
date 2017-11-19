/* -----------------------------------------------------------------------
** Thomas McIntosh                                                      **
** CS 362-400                                                           **
** Assignment 3 - randomtestcard2.c                                     **
** testing function: greathall_card()                                   **
** -----------------------------------------------------------------------
**/

#include "dominion.h"
#include "dominion_helpers.h"
#include "interface.h"
#include "rngs.h"
#include "randTestHelpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

#define NUM_RAND_TESTS 500

#define NOISY_TEST 1

int assert_true(int statement)
{
	int iterationsFailed = 0;
	if(statement)
	{
		
		#if (NOISY_TEST == 1)
		printf("\n Test passed: ");
		#endif
	}
	else
	{
		iterationsFailed = 1;
		#if (NOISY_TEST == 1)
		printf("\n Test failed: ");
		#endif
		return(iterationsFailed);
	}
	return;
}; 

//Oracle to determine if the test passes or fails. 
int checkGreatHallEffect(struct gameState*, struct gameState*, int);

int main ()
{
    int randSeed = time(NULL);     
    srand(randSeed);
    
    int i;          
    int handPos;   
    int numPlayers;
    struct gameState game;
    struct gameState backupGame;
    int k[10];
    int iterationsFailed = 0;
    int failedIterations[NUM_RAND_TESTS];
    int j = 0; 

    
    printf("Testing Great Hall Card");
    printf("\n%d RANDOM TEST ITERATION", NUM_RAND_TESTS);
    
    for(i = 0; i < NUM_RAND_TESTS; i++)
    {
        numPlayers = 2 + rand()%(MAX_PLAYERS - 2 + 1); 
        randomKingdomCards(k, great_hall);
        initializeGame(numPlayers, k, rand()%INT_MAX, &game);
        generateRandomHand(game.hand[0], k, great_hall, &handPos);

        memcpy(&backupGame, &game, sizeof(struct gameState));
        
        //TEST: card on game
        playCard(handPos, 0, 0, 0, &game);
        
        //COMPARE: test game to backup game to confirm correct behavior
        if(checkGreatHallEffect(&game, &backupGame, i))
        {
            iterationsFailed++;
            failedIterations[j] = i+1;
            j++;
        }
    }
    
    printf("\n\nPass Rate: %d of %d", NUM_RAND_TESTS-iterationsFailed, NUM_RAND_TESTS);
    
    if(iterationsFailed > 0)
    {
        printf("\nItertations failed:");
        for(i = 0; i < j; i++)
        {
            if(i%20 == 0)
                printf("\n");
            printf("%d ", failedIterations[i]);
        }
        printf("\n");
        printf("\n");
    }
  return 0;
}

int checkGreatHallEffect(struct gameState *game, struct gameState *backupGame, int iteration)
{
    int i;
    int failed = 0;
    
	#if (NOISY_TEST == 1)
    printf("\n\nIteration: %d   Number of Players: %d \n", iteration+1, game->numPlayers);
    #endif 
	
    // CHECK: P1 hand count before and after
    // draw 1 card, discard great hall so should be 5 before and after
    failed = assert_true(backupGame->handCount[0]+1-1 == game->handCount[0]);

	#if (NOISY_TEST == 1)
    printf("Expected P1 hand count: %d  Reported P1 hand count: %d"
            ,backupGame->handCount[0]+1-1, game->handCount[0]);
    #endif 
	
    //CHECK: P1 deck count before and after
		failed = assert_true((backupGame->deckCount[0]-1) 
            == (game->deckCount[0]));
			
	#if (NOISY_TEST == 1)
    printf("Expected P1 deck: %d  Reported P1 deck: %d"
            ,backupGame->deckCount[0]-1
            ,game->deckCount[0]);
    #endif
	
    // check P1 played count before and after
    // played should be +1 because discarded the great hall
    failed = assert_true(backupGame->playedCardCount+1 == game->playedCardCount);

	#if (NOISY_TEST == 1)
    printf("Expected P1 played card count: %d  Reported P1 played card count: %d"
            ,backupGame->playedCardCount+1, game->playedCardCount);
    #endif 
	
    // check numActions before and after
    // should be no change bc hall costs 1 and restores 1
    failed = assert_true(game->numActions == backupGame->numActions);

	#if (NOISY_TEST == 1)
    printf("Expected P1 number of actions: %d  Reported P1 number of actions: %d"
            ,backupGame->numActions, game->numActions);
    #endif 
	
    // verify no change in other players states
    for(i = 1; i < game->numPlayers; i ++)
    {
		
    // check hand count before and after for player i
    failed = assert_true(backupGame->handCount[i] == game->handCount[i]);

	#if (NOISY_TEST == 1)
    printf("Expected P%d hand count: %d  Reported P2 hand count: %d"
            ,i+1,backupGame->handCount[1], game->handCount[1]);
    #endif
	
    // check deck+discard before and after for player i
    failed = assert_true((backupGame->deckCount[i] + backupGame->discardCount[i]) 
            == (game->deckCount[i] + game->discardCount[i]));
 
	#if (NOISY_TEST == 1)
    printf("Expected P%d deck and discard: %d  Reported P2 deck and discard: %d"
            ,i+1,backupGame->deckCount[1]+backupGame->discardCount[1]
            ,game->deckCount[1]+game->discardCount[1]);  
    #endif
	}
	
	return(failed);
}