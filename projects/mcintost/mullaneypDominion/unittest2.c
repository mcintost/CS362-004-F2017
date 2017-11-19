/* -----------------------------------------------------------------------
* Thomas McIntosh
* CS 362-400
* Assignment 3 - unittest2.c
* testing function: isGameOver()
*
* unittest2: unittest2.c dominion.o
*      gcc -o unittest2 unittest2.c dominion.c rngs.c $(CFLAGS)
* -----------------------------------------------------------------------
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>

#define NOISY_TEST 1

//Checks if a statement is true or not. Prints output.
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

	int randomSeed = 100;
	int players = 2;
	
     	//Test 1:  Province supply empty, no other victory card piles at 0 
		struct gameState state;
		int initializeResult;
		int supply[10] = {adventurer, council_room, embargo, gardens, sea_hag, remodel, smithy, village, steward, great_hall};

		initializeResult = initializeGame(players, supply, randomSeed, &state);
		state.supplyCount[province] = 0;
		int gameOver = isGameOver(&state);

		#if (NOISY_TEST == 1)
		printf("isGameOver(): Test 1 when province cards at 0: \n");
		#endif
		assert_true(gameOver);
		//End of test1
		
		//Test 2: Test for 3 pile ending, where there are still providence cards left but three supply piles have been emptied.
		//adventurer, sea_hag, and great_hall
 		struct gameState state2;
		int supply2[10] = {adventurer, council_room, embargo, gardens, sea_hag, remodel, smithy, village, steward, great_hall};

		initializeResult = initializeGame(players, supply2, randomSeed, &state2);
		int i;	
		for (i=curse; i<=treasure_map; i++)
		{
			state2.supplyCount[i] = i+2; 
		} 
		state2.supplyCount[adventurer] = 0;
		state2.supplyCount[embargo] = 0;
		state2.supplyCount[great_hall] = 0;  
		
		gameOver = isGameOver(&state2);
		
		#if (NOISY_TEST == 1)	
		printf("isGameOver(): Test 2 when there are still province cards and adventurer, embargo, and great_hall are empty:\n");
		#endif
		assert_true(gameOver);  
		//End of test2

	
		//Test 3: Test that the game is not over when there are still province cards left and no supply piles empty.
		struct gameState state3;
		int supply3[10] = {adventurer, council_room, embargo, gardens, sea_hag, remodel, smithy, village, steward, great_hall};

		initializeResult = initializeGame(players, supply3, randomSeed, &state3);

		for (i=curse; i<=treasure_map; i++)
		{
			state3.supplyCount[i] = i+2; 
		} 
		
		gameOver = isGameOver(&state3);
		
		#if (NOISY_TEST == 1)	
		printf("isGameOver(): Test 3 where no supply pile is at 0:\n");
		#endif 
		assert_true(!gameOver);
		//End of test3

		//Test 4: test what happens when all supply piles are empty.
		struct gameState state4;
		int supply4[10] = {adventurer, council_room, embargo, gardens, sea_hag, remodel, smithy, village, steward, great_hall};

		initializeResult = initializeGame(players, supply4, randomSeed, &state4);

		for (i=curse; i<=treasure_map; i++)
		{
			state4.supplyCount[i] = 0; 
		}

		gameOver = isGameOver(&state4);

		#if (NOISY_TEST == 1)	
		printf("isGameOver: Test 4 when all supply piles are at 0:\n");
	    #endif
		assert_true(gameOver);
		//End of test4
		
		//Test 5: Test that the game does not end when there are only 2 emply supply piles. 
		struct gameState state5;
		int supply5[10] = {adventurer, council_room, embargo, gardens, sea_hag, remodel, smithy, village, steward, great_hall};

		initializeResult = initializeGame(players, supply5, randomSeed, &state5);

		for (i=curse; i<=treasure_map; i++)
		{
			state5.supplyCount[i] = i+1; 
		} 
	
		state5.supplyCount[embargo] = 0;
		state5.supplyCount[smithy] = 0;
		  
		gameOver = isGameOver(&state5);
		
		#if (NOISY_TEST == 1)	
		printf("isGameOver(): Test 5 case where exactly 2 supply piles are at 0:\n");
		#endif
		assert_true(!gameOver); 
		//End of test5
		
		//Test 6: Test for 3 pile ending, where there are still providence cards left but three supply piles have been emptied.
		//Testing if treasure_map works using two known working cards
 		struct gameState state6;
		int supply6[10] = {adventurer, council_room, embargo, gardens, sea_hag, remodel, smithy, village, steward, treasure_map};

		initializeResult = initializeGame(players, supply6, randomSeed, &state6);
		
		for (i=curse; i<=treasure_map; i++)
		{
			state6.supplyCount[i] = i+2; 
		} 
		state6.supplyCount[adventurer] = 0;
		state6.supplyCount[council_room] = 0;
		state6.supplyCount[treasure_map] = 0;  
		
		gameOver = isGameOver(&state6);
		
		#if (NOISY_TEST == 1)	
		printf("isGameOver(): Test 6 when there are still province cards and village, steward, and treasure_map(the last card) are empty:\n");
		#endif
		assert_true(gameOver);  
		//End of test6
		
		//Test 7: Test for 3 pile ending, where there are still providence cards left but three supply piles have been emptied.
		//Testing if curse works using two known working cards
 		struct gameState state7;
		int supply7[10] = {adventurer, council_room, embargo, gardens, sea_hag, remodel, smithy, village, steward, curse};

		initializeResult = initializeGame(players, supply7, randomSeed, &state7);
		
		for (i=curse; i<=treasure_map; i++)
		{
			state7.supplyCount[i] = i+2; 
		} 
		state7.supplyCount[adventurer] = 0;
		state7.supplyCount[council_room] = 0;
		state7.supplyCount[curse] = 0;  
		
		gameOver = isGameOver(&state7);
		
		#if (NOISY_TEST == 1)	
		printf("isGameOver(): Test 7 when there are still province cards and village, steward, and curse(the first card) are empty:\n");
		#endif
		assert_true(gameOver);  
		//End of test6
		
		//Test 8: Test for 3 pile ending, where there are still providence cards left but three supply piles have been emptied.
		//Testing if sea_hag works using two known working cards
 		struct gameState state8;
		int supply8[10] = {adventurer, council_room, embargo, gardens, sea_hag, remodel, smithy, village, steward, treasure_map};

		initializeResult = initializeGame(players, supply8, randomSeed, &state8);
		
		for (i=curse; i<=treasure_map; i++)
		{
			state8.supplyCount[i] = i+2; 
		} 
		state8.supplyCount[adventurer] = 0;
		state8.supplyCount[council_room] = 0;
		state8.supplyCount[sea_hag] = 0;  
		
		gameOver = isGameOver(&state8);
		
		#if (NOISY_TEST == 1)	
		printf("isGameOver(): Test 8 when there are still province cards and village, steward, and sea_hag(the second to last card) are empty:\n");
		#endif
		assert_true(gameOver);  
		//End of test8
		
		//Test 9: Test for 3 pile ending, where there are still providence cards left but three supply piles have been emptied.
		//Testing if salvager works using two known working cards
 		struct gameState state9;
		int supply9[10] = {adventurer, council_room, embargo, gardens, sea_hag, remodel, smithy, village, steward, salvager};

		initializeResult = initializeGame(players, supply9, randomSeed, &state9);
		
		for (i=curse; i<=treasure_map; i++)
		{
			state9.supplyCount[i] = i+2; 
		} 
		state9.supplyCount[adventurer] = 0;
		state9.supplyCount[council_room] = 0;
		state9.supplyCount[salvager] = 0;  
		
		gameOver = isGameOver(&state9);
		
		#if (NOISY_TEST == 1)	
		printf("isGameOver(): Test 9 when there are still province cards and village, steward, and salvager(the third to last card) are empty:\n");
		#endif
		assert_true(gameOver);  
		//End of test9
	
	return 0;
}