/* -----------------------------------------------------------------------
* Thomas McIntosh
* CS 362-400
* Assignment 3 - unittest1.c
* testing function: gainCard()
*
* unittest1: unittest1.c dominion.o
*      gcc -o unittest1 unittest1.c dominion.c rngs.c $(CFLAGS)
* -----------------------------------------------------------------------
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>

#define NUM_CARDS 27 

#define NOISY_TEST 0

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

//Determines the number of times that a card appears in the array, either the hand or deck.
int countCard(int numToCount, int array[], int arraySize)
{
	int i;
	int count=0;
	
	for (i = 0; i<arraySize; i++)
	{
		if (array[i]== numToCount)
		{
			count++;
		}
	}
	return count;
}

//Determines that exactly one card has been added. 
int addedToPile (int pileBefore[], int pileCountBefore, int pileAfter[], int pileCountAfter)
{
	int countBefore[NUM_CARDS]; 
	int i;
	
	for (i = 0; i < NUM_CARDS; i++)
	{
  		 countBefore[i] = 0;
	} 

	int countAfter[NUM_CARDS];
	
	for (i = 0; i < NUM_CARDS; i++)
	{
		countAfter[i] = 0;
	}
			
	int cardAdded = -1; 		
	int found = 0; 

	for (i = 0; i < NUM_CARDS; i++)
	{
		countAfter[i] = countCard(i, pileAfter, pileCountAfter);
		countBefore[i] = countCard(i, pileBefore, pileCountBefore);

		if (countBefore[i] == countAfter[i]-1)
		{
			cardAdded = i;
			found++;
		}
		else if (countBefore[i] != countAfter[i])
		{
			return -1; 
		}	
	}

	if (found !=1) 
	{
		return -1;
	}
	return cardAdded;
}

int checkPileUnchanged(int pile1[], int pile1Count,int pile2[], int pile2Count)
{
	int unchanged = 1; 	
	int i;
     
	if (pile1Count != pile2Count)
	{
		unchanged = 0;
	}

	int cardCount1;
	int cardCount2;
	
	for (i = 0; i < NUM_CARDS;i++)
	{
		cardCount1 = countCard(i, pile1, pile1Count);
		cardCount2 = countCard(i, pile2, pile2Count);
		if (cardCount1 != cardCount2)
		{
			unchanged = 0;
		}
	}
	return unchanged;
}

int checkAllUnchanged(struct gameState* state1, struct gameState* state2, int player)
{
	int unchanged; // 1 indicates all unchanged, 0 means changed

	int discardUnchanged;
	int handUnchanged;
	int deckUnchanged;

	discardUnchanged = checkPileUnchanged(state1->discard[player], state1->discardCount[player], state2->discard[player], state2->discardCount[player]);
	handUnchanged = checkPileUnchanged(state1->hand[player], state1->handCount[player], state2->hand[player], state2->handCount[player]);
	deckUnchanged = checkPileUnchanged(state1->deck[player], state1->deckCount[player], state2->deck[player], state2->deckCount[player]);

	unchanged = (discardUnchanged & handUnchanged & deckUnchanged); // all must be true for unchanged to be true
	return unchanged;
}

void checkGainCard(int playerNum, int supplyPos)
{
	
    // Case 1: Card is gained by the deck
   
	int randomSeed = 758000;
	int players = MAX_PLAYERS;
	
	struct gameState state1;
	int initializeResult;
	int supply1[10] = {adventurer, council_room, embargo, gardens, sea_hag, remodel, smithy, village, steward, great_hall};

	initializeResult = initializeGame(players, supply1, randomSeed, &state1);

	struct gameState origState1;
	origState1 = state1;
		
	int returnedByFunction;
	int addedToDeck;
	int discardUnchanged;
	int handUnchanged;
 	
	returnedByFunction = gainCard(supplyPos, &state1, 1, playerNum);	
	
	#if (NOISY_TEST == 1)
	printf("gainCard: deck flagged, test whether the supply count has been decremented: ");
	#endif
	
	int supplyCountBefore = origState1.supplyCount[supplyPos];
	int supplyCountAfter = state1.supplyCount[supplyPos];

	assert_true(supplyCountAfter == supplyCountBefore-1);

	#if (NOISY_TEST == 1)
	printf("gainCard: deck flagged, test for card added to deck: ");
	#endif

	addedToDeck = addedToPile(origState1.deck[playerNum], origState1.deckCount[playerNum], state1.deck[playerNum], state1.deckCount[playerNum]);
	assert_true(addedToDeck != -1);  // -1 indicates not correctly added to deck
	
	#if (NOISY_TEST == 1)
	printf("gainCard: deck flagged, test for discard pile unchanged: ");
	#endif
	discardUnchanged = checkPileUnchanged(origState1.discard[playerNum], origState1.discardCount[playerNum], state1.discard[playerNum], state1.discardCount[playerNum]);
	assert_true(discardUnchanged);	

	#if (NOISY_TEST == 1)
	printf("gainCard: deck flagged, testing for hand unchanged: ");
	#endif
	
	handUnchanged = checkPileUnchanged(origState1.hand[playerNum], origState1.handCount[playerNum], state1.hand[playerNum], state1.handCount[playerNum]);	
	assert_true(handUnchanged);

	//Case 2: Card is gained by hand

	randomSeed = 758000;
	players = MAX_PLAYERS;
	
	struct gameState state2;
	int supply2[10] = {adventurer, council_room, embargo, gardens, sea_hag, remodel, smithy, village, steward, great_hall};

	initializeResult = initializeGame(players, supply2, randomSeed, &state2);

	struct gameState origState2;
	origState2 = state2;

	returnedByFunction = gainCard(supplyPos, &state2, 2, playerNum);	
	
	#if (NOISY_TEST == 1)
	printf("gainCard: hand flagged, test whether supply count has been decremented: ");
	#endif

	supplyCountBefore = origState2.supplyCount[supplyPos];
	supplyCountAfter = state2.supplyCount[supplyPos];

	assert_true(supplyCountAfter == supplyCountBefore-1);

	#if (NOISY_TEST == 1)
	printf("gainCard: hand flagged, test whether card was added to the hand: ");
	#endif

	int addedToHand;
	addedToHand = addedToPile(origState2.hand[playerNum], origState2.handCount[playerNum], state2.hand[playerNum], state2.handCount[playerNum]);
	assert_true(addedToHand != -1);
	
	#if (NOISY_TEST == 1)
	printf("gainCard: hand flagged, test for discard pile unchanged: ");
	#endif
	
	discardUnchanged = checkPileUnchanged(origState2.discard[playerNum], origState2.discardCount[playerNum], state2.discard[playerNum], state2.discardCount[playerNum]);
	assert_true(discardUnchanged);	

	#if (NOISY_TEST == 1)
	printf("gainCard: hand flagged, test for deck unchanged: ");
	#endif

	int deckUnchanged;
	deckUnchanged = checkPileUnchanged(origState2.deck[playerNum], origState2.deckCount[playerNum], state2.deck[playerNum], state2.deckCount[playerNum]);	
	assert_true(deckUnchanged);

	//Case 3 Card is gained by discard pile
 		
	randomSeed = 758000;
	players = MAX_PLAYERS;
	
	struct gameState state3;
	int supply3[10] = {adventurer, council_room, embargo, gardens, sea_hag, remodel, smithy, village, steward, great_hall};
	initializeResult = initializeGame(players, supply3, randomSeed, &state3);

	struct gameState origState3;
	origState3 = state3;

	returnedByFunction = gainCard(supplyPos, &state3, 0, playerNum);	
	
	#if (NOISY_TEST == 1)	
	printf("gainCard: discard flagged, testing whether the supply count decremented: ");
	#endif

	supplyCountBefore = origState3.supplyCount[supplyPos];
	supplyCountAfter = state3.supplyCount[supplyPos];

	assert_true(supplyCountAfter == supplyCountBefore-1);
	
	#if (NOISY_TEST == 1)
	printf("gainCard: discard flagged, test for card added to the discard: ");
	#endif

	int addedToDiscard;
	addedToDiscard = addedToPile(origState3.discard[playerNum], origState3.discardCount[playerNum], state3.discard[playerNum], state3.discardCount[playerNum]);
	assert_true(addedToDiscard != -1);
	
	#if (NOISY_TEST == 1)
	printf("gainCard: discard flagged, test for hand unchanged: ");
	#endif

	handUnchanged = checkPileUnchanged(origState3.hand[playerNum], origState3.handCount[playerNum], state3.hand[playerNum], state3.handCount[playerNum]);
	assert_true(handUnchanged);	

	#if (NOISY_TEST == 1)
	printf("gainCard: discard flagged, test for deck unchanged: ");
	#endif
	deckUnchanged = checkPileUnchanged(origState2.deck[playerNum], origState2.deckCount[playerNum], state2.deck[playerNum], state2.deckCount[playerNum]);	
	assert_true(deckUnchanged);

	//Case 4 Supply pile is empty 
	 
	randomSeed = 758000;
	players = MAX_PLAYERS;
	
	struct gameState state4;
	int supply4[10] = {adventurer, council_room, embargo, gardens, sea_hag, remodel, smithy, village, steward, great_hall};

	initializeResult = initializeGame(players, supply4, randomSeed, &state4);
	
	state4.supplyCount[supplyPos] = 0;

	struct gameState origState4;
	origState4 = state4;
	
	int pilesUnchanged;
	int flag;

	for (flag = 0; flag < 4; flag++) 
	{	
		#if (NOISY_TEST == 1)
		printf("gainCard: supply empty, test for -1 return value: ");
		#endif
		returnedByFunction = gainCard(supplyPos, &state4, flag, playerNum);	
		assert_true(returnedByFunction == -1); 

		#if (NOISY_TEST == 1)
		printf("gainCard: supply empty, test for all piles unchanged: ");
		#endif
		pilesUnchanged = checkAllUnchanged(&origState4, &state4, playerNum);
		assert_true(pilesUnchanged);
	}
 	
	return;

}  


int main()
{
	checkGainCard(0, 0);

	return 0;
}

