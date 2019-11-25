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
    // declare the arrays
    int coppers[MAX_HAND];
    int silvers[MAX_HAND];
    int golds[MAX_HAND];

    printf("Begin Testing play_baron():\n");
    //
    // set the state of your variables
    // comment on what this is going to test
    //
    memset(&G, 23, sizeof(struct gameState));
    // set the game state
    r = initializeGame(2, k, seed, &G);
    // initialize a new game
    G.handCount[p] = handCount;
    // set any other variables
    memcpy(G.hand[p], coppers, sizeof(int) * handCount);
    G.hand[p][0] = estate;
    // call the refactored function
    int initial_coins = G.coins;
    baroncardEffect(1, &G);
    // verify that your asserts pass, for the bugs your asserts may fail
    assert(G.coins == (initial_coins + 4)); // Checks that coins was properly incremented when an estate is found.
    
    memset(&G, 0, sizeof(struct gameState));
    // set the game state
    r = initializeGame(3, k, seed, &G);
    // initialize a new game
    G.handCount[p] = handCount;
    G.handCount[1] = handCount;
    // set any other variables
    memcpy(G.hand[p], silvers, sizeof(int) * handCount);
    memcpy(G.hand[1], silvers, sizeof(int) * handCount);
    // call the refactored function again
    baroncardEffect(0, &G);
    
    int estate_check = 0;
    for(int i = 0; i < G.deckCount[p]; i++){
        if(G.deck[p][i] == estate){estate_check = 1;}
    }
    assert(estate_check); //Checks if estate is found in the players hand

    memset(&G, 0, sizeof(struct gameState));
    // set the game state
    r = initializeGame(3, k, seed, &G);
    // initialize a new game
    G.handCount[p] = handCount;
    memcpy(G.hand[p], silvers, sizeof(int) * handCount);
    G.hand[p][1] = estate;
    initial_coins = G.coins;
    baroncardEffect(1, &G);
    assert(G.coins == (initial_coins + 4));
    assert(DEBUG); //Checks if DEBUG var is enabled
    // verify that your asserts pass, for the bugs your asserts may fail
    printf("Test completed!\n");
    return 0;
}