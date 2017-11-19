/* -----------------------------------------------------------------------
* Thomas McIntosh
* CS 362-400
* Assignment 3 - unittest3.c
* testing function: updateCoins()
*
* unittest3: unittest3.c dominion.o
*      gcc -o unittest3 unittest3.c dominion.c rngs.c $(CFLAGS)
* -----------------------------------------------------------------------
*/

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
    struct gameState game;
    int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
    int testsFailed = 0;
    
    // test cases
    int test_Hand1[5] = {adventurer, council_room, gold, copper, silver};
    int test_Hand2[5] = {adventurer, council_room, feast, gardens, mine};
    int test_Hand3[5] = {copper, adventurer, council_room, feast, gardens};
    int test_Hand4[5] = {silver, adventurer, council_room, feast, gardens};
    int test_Hand5[5] = {gold, adventurer, council_room, feast, gardens};
    int test_Hand6[5] = {copper, copper, copper, copper, copper};
    int test_Hand7[5] = {silver, silver, silver, silver, silver};
    int test_Hand8[5] = {gold, gold, gold, gold, gold};
	int test_Hand10[0] = {};
    
    initializeGame(numPlayers, k, seed, &game);
    
    game.handCount[0] = 5;
			
	// Test 1: Random hand.
		for(i = 0; i < 5; i++)
		{
			game.hand[0][i] = test_Hand1[i];
		}
		
		updateCoins(0, &game, 0);
		
		#if (NOISY_TEST == 1)
		printf("\nCase 1 Random hand: Expected total: %d  Reported total: %d", 6, game.coins);
		#endif 
		
		if (game.coins != 6) testsFailed++;
		else 
			#if (NOISY_TEST == 1)
			printf("  PASS");
			#endif
	
    // Test 2: Hand with no coins. 
		for(i = 0; i < 5; i++)
		{
			game.hand[0][i] = test_Hand2[i];
		}
		
		updateCoins(0, &game, 0);
		#if (NOISY_TEST == 1)
		printf("\nCase2 No coins: Expected total: %d  Reported total: %d", 0, game.coins);
		#endif
		
		if (game.coins != 0) testsFailed++;
		
		else 
			#if (NOISY_TEST == 1)
			printf("  PASS");
			#endif
			
	// Test 3: Hand with only one copper.
		for(i = 0; i < 5; i++)
		{
			game.hand[0][i] = test_Hand3[i];
		}
		
		updateCoins(0, &game, 0);
		#if (NOISY_TEST == 1)
		printf("\nCase 3 one copper: Expected total: %d  Reported total: %d", 1, game.coins);
		#endif
		
		if (game.coins != 1) testsFailed++;
		else 
			#if (NOISY_TEST == 1)
			printf("  PASS");
			#endif

	// Test 4: Hand with only one silver
		for(i = 0; i < 5; i++)
		{
			game.hand[0][i] = test_Hand4[i];
		}
		
		updateCoins(0, &game, 0);
		#if (NOISY_TEST == 1)
		printf("\nCase 4 one silver: Expected total: %d  Reported total: %d", 2, game.coins);
		#endif
		
		if (game.coins != 2) testsFailed++;
		else 
			#if (NOISY_TEST == 1)
			printf("  PASS");
			#endif
	
    // Test 5: Hand with only one gold. 
    
		for(i = 0; i < 5; i++)
		{
			game.hand[0][i] = test_Hand5[i];
		}
		
		updateCoins(0, &game, 0);
		#if (NOISY_TEST == 1)
		printf("\nCase 5 one gold: Expected total: %d  Reported total: %d", 3, game.coins);
		#endif
		
		if (game.coins != 3) testsFailed++;
		else 
			#if (NOISY_TEST == 1)
			printf("  PASS");
			#endif

    // Test 6: Hand with five copper
		for(i = 0; i < 5; i++)
		{
			game.hand[0][i] = test_Hand6[i];
		}
		
		updateCoins(0, &game, 0);
		#if (NOISY_TEST == 1)
		printf("\nCase 6 five copper: Expected total: %d  Reported total: %d", 5, game.coins);
		#endif
		if (game.coins != 5) testsFailed++;
		else 
			#if (NOISY_TEST == 1)
			printf("  PASS");
			#endif
	
    // Test 7: Hand with five silver.
		for(i = 0; i < 5; i++)
		{
			game.hand[0][i] = test_Hand7[i];
		}
		
		updateCoins(0, &game, 0);
		#if (NOISY_TEST == 1)
		printf("\nCase 7 five silver: Expected total: %d  Reported total: %d", 10, game.coins);
		#endif
		
		if (game.coins != 10) testsFailed++;
		else 
			#if (NOISY_TEST == 1)
			printf("  PASS");
			#endif
	
    // Test 8: Hand with five gold. 
		for(i = 0; i < 5; i++)
		{
			game.hand[0][i] = test_Hand8[i];
		}
		
		updateCoins(0, &game, 0);
		#if (NOISY_TEST == 1)
		printf("\nCase 8 five gold: Expected total: %d  Reported total: %d", 15, game.coins);
		#endif
		
		if (game.coins != 15) testsFailed++;
		else 
			#if (NOISY_TEST == 1)
			printf("  PASS");
			#endif

	
    // Test 9: Random hand with 2 bonus. 
    
		for(i = 0; i < 5; i++)
		{
			game.hand[0][i] = test_Hand1[i];
		}
		
		updateCoins(0, &game, 3);
		#if (NOISY_TEST == 1)
		printf("\nCase 9 Random hand with bonus: Expected total: %d  Reported total: %d", 9, game.coins);
		#endif
		if (game.coins != 9) testsFailed++;
		else 
			#if (NOISY_TEST == 1)
			printf("  PASS");
			#endif 
			
	// Test 10: Empty hand. 
	game.handCount[0] = 0;
	
		//for(i = 0; i < 2; i++)
		//{
			game.hand[0][i] = test_Hand10[i];
		//}
		updateCoins(0, &game, 0);
		#if (NOISY_TEST == 1)
		printf("\nCase 10 Empty hand: Expected total: %d  Reported total: %d", 0, game.coins);
		#endif
		
		if (game.coins != 0) testsFailed++;
		else 
			#if (NOISY_TEST == 1)
			printf("  PASS");
			#endif

	
	#if (NOISY_TEST == 1)
	printf("\n%d of %d test passed \n", 10 - testsFailed, 10);
    #endif
    return 0;
}




























