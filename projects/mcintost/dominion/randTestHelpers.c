#include "randTestHelpers.h"
#include "dominion.h"
#include "interface.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <limits.h>

void randomKingdomCards(int kCardsSelected[], int testCard)
{
    int selectableKCards = NUM_TOTAL_K_CARDS - 7;
    int i;
    int tmpCards[selectableKCards]; 
    int swapCardIndex;
    int tmpSwap;
    int addedTestCard = 0;
    
    for(i = 0; i < selectableKCards; i++)
    {
        tmpCards[i] = i + 7;
    }
    
    for(i = 0; i < selectableKCards; i++)
    {
        swapCardIndex = rand() % selectableKCards;
        tmpSwap = tmpCards[i];
        tmpCards[i] = tmpCards[swapCardIndex];
        tmpCards[swapCardIndex] = tmpSwap;
    }
    
    for(i = 0; i < 10; i++)
    {
        
        kCardsSelected[i] = tmpCards[i];
        if(kCardsSelected[i] == testCard)
        {
            addedTestCard = 1;
        }
        if((i==9)&&(addedTestCard == 0))
        {
            kCardsSelected[rand()%10] = testCard;
        }
    }
}

void populateDrawableCards(int drawCards[], int kingdomCards[])
{
    int i;
    
    for(i = 0; i < 10; i++)
    {
        drawCards[i] = kingdomCards[i];
    }
    
    drawCards[10] = copper;
    drawCards[11] = silver;
    drawCards[12] = gold;
    
}

void generateRandomHand(int hand[], int kingdomCards[], int testCard, int *handPos)
{
    int i;
    int drawable[13];
    int testCardAdded = 0;
    
    populateDrawableCards(drawable, kingdomCards);
    
    for(i = 0; i < 5; i++)
    {
        hand[i] = drawable[rand() % 13];
        if(hand[i] == testCard)
        {
            testCardAdded = 1;
            *handPos = i;
        }
        if((i==4)&&!testCardAdded)
        {
            *handPos = rand() % 5;
            hand[*handPos] = testCard;
        }
    }
}