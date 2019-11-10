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

    printf("Begin Testing play_minion():\n");
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
    // call the refactored function
    int initial_coins = G.coins;
    play_minion(1, 0, 0, p, &G);
    // verify that your asserts pass, for the bugs your asserts may fail
    assert(G.coins == (initial_coins + 2)); // Checks that coins was properly incremented when minion choice1 is played.
    
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
    play_minion(0, 1, 0, p, &G);
    assert(G.handCount[p] == 4); // Checks if the players handCount is 4 after play_minion choice2
    assert(G.handCount[1] == 4); // Checks if the players handCount is 4 after play_minion choice2
    
    int minion_check = 0;
    for(int i = 0; i < G.discardCount[p]; i++){
        if(G.discard[p][i] == "minion"){minion_check = 1;}
    }
    assert(minion_check);
    // verify that your asserts pass, for the bugs your asserts may fail
    printf("Test completed!\n");
    return 0;
}