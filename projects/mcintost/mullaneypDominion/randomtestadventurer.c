/* -----------------------------------------------------------------------
** Thomas McIntosh                                                      **
** CS 362-400                                                           **
** Assignment 3 - unittest3.c                                           **
** testing function: randomtestadventurer.c()                           **
**                                                                      **
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
int checkAdventurerEffect(struct gameState*, struct gameState*, int);

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

    #if (NOISY_TEST == 1)
    printf("Testing Adventurer Card");
    printf("\n%d RANDOM TEST ITERATION", NUM_RAND_TESTS);
    #endif 
	
    for(i = 0; i < NUM_RAND_TESTS; i++)
    {
        numPlayers = 2 + rand()%(MAX_PLAYERS - 2 + 1); //2 to MAX_PLAYERS incl.
        randomKingdomCards(k, adventurer);
        initializeGame(numPlayers, k, rand()%INT_MAX, &game);
        generateRandomHand(game.hand[0], k, adventurer, &handPos);

        memcpy(&backupGame, &game, sizeof(struct gameState));
        
        //TEST: card on game
        playCard(handPos, 0, 0, 0, &game);
        
        //COMPARE: test to backup game to confirm proper behavior 
        if(checkAdventurerEffect(&game, &backupGame, i))
        {
            iterationsFailed++;
            failedIterations[j] = i+1;
            j++;
        }
    }
    
    printf("\n\nPass Rate: %d of %d", NUM_RAND_TESTS-iterationsFailed, NUM_RAND_TESTS);

	#if (NOISY_TEST == 1)
	if(iterationsFailed > 0)
    {
        printf("Iteration failed:");
		for(i = 0; i < j; i++)
        {
            if(i%20 == 0)
                printf("\n");
				printf("%d ", failedIterations[i]);
        }	
        printf("\n");
        printf("\n");
    }
	#endif 
    return 0;
}

int checkAdventurerEffect(struct gameState *game, struct gameState *backupGame, int iteration)
{
    int i;
    int beforeTreasure = 0;
    int afterTreasure = 0;
    int currentCard;
    int failed = 0;
    
	#if (NOISY_TEST == 1)
    printf("\n\nIteration: %d   number of players: %d \n", iteration+1, game->numPlayers);
    #endif
	
    //1 CHECK: P1 hand count before and after
    failed = assert_true(backupGame->handCount[0]+2 == game->handCount[0]);
	
	#if (NOISY_TEST == 1)
    printf("Expected P1 hand count: %d  Actual P1 hand count: %d "
            ,backupGame->handCount[0] + 2, game->handCount[0]);
    #endif
	
    //2 CHECK: P1 deck and discard count before and after
    failed = assert_true((backupGame->deckCount[0] + backupGame->discardCount[0] - 2) 
            == (game->deckCount[0] + game->discardCount[0]));
	
	#if (NOISY_TEST == 1)	
    printf("Expected P1 deck and discard: %d  Actual P1 deck and discard: %d "
            ,backupGame->deckCount[0] + backupGame->discardCount[0] - 2
            ,game->deckCount[0] + game->discardCount[0]);
    #endif 
	
    //3 COUNT: treasures in hand before adventurer (from backupGame)
    for (i = 0; i < backupGame->handCount[0]; i++)
    {
        currentCard = backupGame->hand[0][i];
        
        if(currentCard == copper || currentCard == silver || currentCard == gold)
            beforeTreasure++;
    }
    
    //4 COUNT: treasures in hand after adventurer (from game)
    for (i = 0; i < game->handCount[0]; i++)
    {
        currentCard = game->hand[0][i];
        
        if(currentCard == copper || currentCard == silver || currentCard == gold)
            afterTreasure++;
    }
    
    //5 CHECK: P1 hand treasure count before and after
    failed = assert_true(beforeTreasure+2 == afterTreasure);
	
	#if (NOISY_TEST == 1)
    printf("Expected P1 hand treasures: %d  Actual P1 hand treasures: %d"
            ,beforeTreasure + 2, afterTreasure);
    #endif
    
    //6 VERIFY: no change in other players states
    
    for(i = 1; i < game->numPlayers; i ++)
    {
        
    //7 CHECK: hand count before and after for player i
    failed = assert_true(backupGame->handCount[i] == game->handCount[i]);
	
	#if (NOISY_TEST == 1)
    printf("Expected P%d hand count: %d  Actual P2 hand count: %d"
            ,i+1,backupGame->handCount[1], game->handCount[1]);
    #endif 
	
    //8 CHECK: deck and discard before and after for player i
    failed = assert_true((backupGame->deckCount[i] + backupGame->discardCount[i]) 
            == (game->deckCount[i] + game->discardCount[i]));
	#if (NOISY_TEST == 1)
    printf("Expected P%d deck and discard: %d  Actual P2 deck and discard: %d"
            ,i+1,backupGame->deckCount[1]+backupGame->discardCount[1]
            ,game->deckCount[1]+game->discardCount[1]);  
	#endif
    }
    
    return(failed);
}