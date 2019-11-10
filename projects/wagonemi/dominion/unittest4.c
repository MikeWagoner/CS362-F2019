#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

void assert(int result){
    if(result == 1){
        printf("Test successful! \n");
    }
    else{
        printf("Test Failed! \n");
    }

}

int main(void){
    // set your card array
    int k[10] = { adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
    // declare the game state
    struct gameState G;
    int handCount = 6;
    int p = 0;
    int seed = 40;
    int r;
    int tributeRevealedCards[2];
    // declare the arrays
    int coppers[MAX_HAND];
    int silvers[MAX_HAND];
    int golds[MAX_HAND];

    printf("Begin Testing play_tribute():\n");
    //
    // set the state of your variables
    // comment on what this is going to test
    //
    memset(&G, 23, sizeof(struct gameState));
    // set the game state
    r = initializeGame(2, k, seed, &G);
    // initialize a new game
    G.handCount[p] = handCount;
    G.handCount[1] = handCount;
    G.handCount[1] = 0;
    G.deckCount[1] = 0;
    G.discardCount[1] = 5;
    // set any other variables
    memcpy(G.hand[p], coppers, sizeof(int) * handCount);
    G.hand[p][1] = tribute;

    memcpy(G.discard[1], silvers, sizeof(int) * handCount);
    G.discard[1][4] = ambassador;
    // call the refactored function
    int initial_coins = G.deckCount[1];
    int discard_card = G.hand[p][0];
    play_tribute(p, 1, tributeRevealedCards, &G);
    // verify that your asserts pass, for the bugs your asserts may fail
    assert(G.coins == (initial_coins +4)); //Checks if current player gets +4 gold from finding 2 treasure cards
    assert(tributeRevealedCards[1] == ambassador); //Checks if the second element of tribute revealed cards contains the correct card
    memset(&G, 0, sizeof(struct gameState));
    // set the game state
    r = initializeGame(3, k, seed, &G);
    // initialize a new game
    handCount = 5;
    G.handCount[p] = handCount;
    G.handCount[1] = 0;
    G.deckCount[1] = 1;
    G.discardCount[1] = 0;
    // set any other variables
    memcpy(G.deck[1], silvers, sizeof(int) * handCount);
    G.deck[1][4] = estate;
    G.deck[1][3] = ambassador;
    G.deck[1][2] = copper;
    // call the refactored function again
    play_tribute(p, 1, tributeRevealedCards, &G);
    assert(G.deckCount[1] == 0); //Checks that deck count is properly decremented
    
    memset(&G, 0, sizeof(struct gameState));
    // set the game state
    r = initializeGame(3, k, seed, &G);
    // initialize a new game
    handCount = 5;
    G.handCount[p] = handCount;
    G.handCount[1] = 0;
    G.deckCount[1] = handCount;
    G.discardCount[1] = 0;
    // set any other variables
    memcpy(G.deck[1], silvers, sizeof(int) * handCount);
    G.deck[1][0] = estate;
    G.deck[1][1] = ambassador;
    G.deck[1][2] = copper;
    // call the refactored function again
    play_tribute(p, 1, tributeRevealedCards, &G);
    assert(G.deckCount[1] != handCount); //Checks that deck count is decremented
    printf("Test completed!\n");
    return 0;
}