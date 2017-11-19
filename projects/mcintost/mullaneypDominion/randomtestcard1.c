/* -----------------------------------------------------------------------
** Thomas McIntosh                                                      **
** CS 362-400                                                           **
** Assignment 3 - randomtestcard1.c                                     **
** testing function: smithy_card()                                      **
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
int checkSmithyEffect(struct gameState*, struct gameState*, int);

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

    
    printf("Testing Smithy Card");
    printf("\n%d RANDOM TEST ITERATION", NUM_RAND_TESTS);
    
    for(i = 0; i < NUM_RAND_TESTS; i++)
    {
        numPlayers = 2 + rand()%(MAX_PLAYERS - 2 + 1); 
        randomKingdomCards(k, smithy);
        initializeGame(numPlayers, k, rand()%INT_MAX, &game);
        generateRandomHand(game.hand[0], k, smithy, &handPos);

        
        memcpy(&backupGame, &game, sizeof(struct gameState));
        
        //TEST: card on game
        playCard(handPos, 0, 0, 0, &game);
        
        //COMPARE: test game to backup game to confirm correct behavior 
        if(checkSmithyEffect(&game, &backupGame, i))
        {
            iterationsFailed++;
            failedIterations[j] = i+1;
            j++;
        }
    }
    
    printf("\n\nPass Rate: %d of %d\n", NUM_RAND_TESTS-iterationsFailed, NUM_RAND_TESTS);
 
    if(iterationsFailed > 0)
    {
        printf("Iterations failed:");
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

int checkSmithyEffect(struct gameState *game, struct gameState *backupGame, int iteration)
{
    int i;
    int failed = 0;
    int beforeSmithyCount = 0;
    int afterSmithyCount = 0;
    int currentCard;
    
	#if (NOISY_TEST == 1)
    printf("\n\nIteration: %d   Number of Players: %d", iteration+1, game->numPlayers);
    #endif
	
    //1 CHECK: P1 played pile before and after
    failed = assert_true(game->playedCardCount == backupGame->playedCardCount+1);

	#if (NOISY_TEST == 1)
    printf("Expected P1 played card count: %d  Reported P1 played card count: %d"
            ,backupGame->playedCardCount+1, game->playedCardCount);
    #endif 
	
    //2 CHECK: P1 hand count before and after
    failed = assert_true(backupGame->handCount[0]+3-1 == game->handCount[0]); 

    printf("Expected P1 hand count: %d  Reported P1 hand count: %d"
            ,backupGame->handCount[0] + 3 -1, game->handCount[0]);
    
    //3 CHECK: P1 discard count before and after
    failed = assert_true((backupGame->discardCount[0]) 
            == (game->discardCount[0]));

	#if (NOISY_TEST == 1)	
    printf("Expected P1 discard: %d  Reported P1 discard: %d"
            ,backupGame->discardCount[0]
            ,game->discardCount[0]);
    #endif 
	
	
	//4 CHECK: P1 deck count before and after.
	failed = assert_true((backupGame->deckCount[0] - 3) 
            == (game->deckCount[0]));
	
	#if (NOISY_TEST == 1)	
    printf("Expected P1 deck: %d  Reported P1 deck: %d"
            ,backupGame->deckCount[0] - 3
            ,game->deckCount[0]);
    #endif 
	
    //5 COUNT: smithies in hand before cardEffect triggers
    for (i = 0; i < backupGame->handCount[0]; i++)
    {
        currentCard = backupGame->hand[0][i];
        
        if(currentCard == smithy)
            beforeSmithyCount++;
    }
    
    //6 COUNT: smithies in hand after cardEffect triggers
    for (i = 0; i < game->handCount[0]; i++)
    {
        currentCard = game->hand[0][i];
        
        if(currentCard == smithy)
            afterSmithyCount++;
    }
    
    //7 CHECK: P1 discarded smithy after cardEffect
    failed = assert_true(afterSmithyCount == beforeSmithyCount-1);
 
	#if (NOISY_TEST == 1)
    printf("Expected P1 hand smithies: %d  Reported P1 hand smithies: %d"
            ,beforeSmithyCount-1, afterSmithyCount);
    #endif 
	
    //8 CONFIRM: no change in other players states
    for(i = 1; i < game->numPlayers; i ++)
    {
        
    //9 CHECK: hand count before and after for player i
    failed = assert_true(backupGame->handCount[i] == game->handCount[i]);
 
	#if (NOISY_TEST == 1)
    printf("Expected P%d hand count: %d  Reported P2 hand count: %d"
            ,i+1,backupGame->handCount[1], game->handCount[1]);
    #endif
	
    //10 CHECK: deck and discard before and after for player i
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