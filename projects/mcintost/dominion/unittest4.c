/* -----------------------------------------------------------------------
** Thomas McIntosh                                                      **
** CS 362-400                                                           **
** Assignment 3 - unittest4.c                                           **
** testing function: buyCard()                                          **
**                                                                      **
** unittest4: unittest4.c dominion.o                                    **
**      gcc -o unittest4 unittest4.c dominion.c rngs.c $(CFLAGS)        **
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

int main ()
{
    int i;
    int numPlayers = 2;
    int seed = 10;
    struct gameState game;
    struct gameState backup;
    int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
    int testsFailed = 0;
    
	initializeGame(numPlayers, k, seed, &game);
	
	memcpy(&backup, &game, sizeof(struct gameState));  //restore gameState
    
    // Test 1: Normal purchase
    buyCard(feast, &game);
	#if (NOISY_TEST == 1)
    printf("\nTest 1: Normal Purchase");
    printf("\n Expected handCount: %d  Reported handCount: %d", 
            backup.handCount[0], game.handCount[0]);
    printf("\n Expected discardCount: %d  Reported discardCount: %d", 
            backup.discardCount[0]+1, game.discardCount[0]);
    printf("\n Expected coins: %d  Reported coins: %d", 
            backup.coins-4, game.coins);
    printf("\n Expected buys: %d  Reported buys: %d",
            backup.numBuys-1, game.numBuys);
    #endif
	
    if((backup.handCount[0] == game.handCount[0])
            &&(backup.discardCount[0]+1==game.discardCount[0])
            &&(backup.coins-4==game.coins)
            &&(backup.numBuys-1==game.numBuys))
    {
		#if (NOISY_TEST == 1)
        printf("\nPASSED\n");
		#endif
    }
    else 
    {
        testsFailed++;
		#if (NOISY_TEST == 1)
        printf("\nFAILED\n");
		#endif
    }
    
    memcpy(&backup, &game, sizeof(struct gameState));
    
    // Test 2: No buys
    game.numBuys = 0;               // simulate no-buys left
    buyCard(adventurer, &game);
	
	#if (NOISY_TEST == 1)
    printf("\nTest 2: No Buys");
    printf("\n Expected handCount: %d  Reported handCount: %d", 
            backup.handCount[0], game.handCount[0]);
    printf("\n Expected discardCount: %d  Reported discardCount: %d", 
            backup.discardCount[0], game.discardCount[0]);
    printf("\n Expected coins: %d  Reported coins: %d", 
            backup.coins, game.coins);
    printf("\n Expected buys: %d  Reported buys: %d",
            0, game.numBuys);
    #endif
	
    if((backup.handCount[0] == game.handCount[0])
            &&(backup.discardCount[0]==game.discardCount[0])
            &&(backup.coins==game.coins)
            &&(0==game.numBuys))
    {
		#if (NOISY_TEST == 1)
        printf("\nPASSED\n");
		#endif
    }
    else 
    {
        testsFailed++;
		#if (NOISY_TEST == 1)
        printf("\nFAILED\n");
		#endif
    }
    
    
    memcpy(&game, &backup, sizeof(struct gameState));  // restore gameState
    
    // Test 3: no coins left
    game.coins = 0;             // simulate no coins left
    buyCard(adventurer, &game);
    #if (NOISY_TEST == 1)
	printf("\nTest 3: No Coins In Hand");
    printf("\n Expected handCount: %d  Reported handCount: %d", 
            backup.handCount[0], game.handCount[0]);
    printf("\n Expected discardCount: %d  Reported discardCount: %d", 
            backup.discardCount[0], game.discardCount[0]);
    printf("\n Expected coins: %d  Reported coins: %d", 
            0, game.coins);
    printf("\n Expected buys: %d  Reported buys: %d",
            backup.numBuys, game.numBuys);
    #endif
	
    if((backup.handCount[0] == game.handCount[0])
            &&(backup.discardCount[0]==game.discardCount[0])
            &&(0==game.coins)
            &&(backup.numBuys==game.numBuys))
    {
		#if (NOISY_TEST == 1)
        printf("\nPASSED\n");
		#endif
    }
    else 
    {
        testsFailed++;
		#if (NOISY_TEST == 1)
        printf("\nFAILED\n");
		#endif
    }
    
	memcpy(&game, &backup, sizeof(struct gameState));  // restore gameState
    
    // Test 4: Desired purchase not there
    game.supplyCount[adventurer] = 0;  
    buyCard(adventurer, &game);
	#if (NOISY_TEST == 1)
    printf("\nTest 4: No Supply");
    printf("\n Expected handCount: %d  Reported handCount: %d", 
            backup.handCount[0], game.handCount[0]);
    printf("\n Expected discardCount: %d  Reported discardCount: %d", 
            backup.discardCount[0], game.discardCount[0]);
    printf("\n Expected coins: %d  Reported coins: %d", 
            backup.coins, game.coins);
    printf("\n Expected buys: %d  Reported buys: %d",
            backup.numBuys, game.numBuys);
    #endif
	
    if((backup.handCount[0] == game.handCount[0])
            &&(backup.discardCount[0]==game.discardCount[0])
            &&(backup.coins==game.coins)
            &&(backup.numBuys==game.numBuys))
    {	
		#if (NOISY_TEST == 1)
        printf("\nPASSED\n");
		#endif
    }
    else 
    {
        testsFailed++;
        #if (NOISY_TEST == 1)
		printf("\nFAILED\n");
		#endif
    }
	

	#if (NOISY_TEST == 1)
    printf("%d OF %d TESTS PASSED\n", 4-testsFailed, 4);
    #endif
	
    return 0;

}