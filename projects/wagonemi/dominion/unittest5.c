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

    printf("Begin Testing play_mine():\n");
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
    G.hand[p][1] = ambassador;
    // call the refactored function
    play_mine(1, silver, 0, p, &G);
    // verify that your asserts pass, for the bugs your asserts may fail
    assert(G.hand[p][6] == silver); // Checks that if not supplied a treasure card the function will error
    
    memset(&G, 0, sizeof(struct gameState));
    // set the game state
    r = initializeGame(3, k, seed, &G);
    // initialize a new game
    handCount = 5;
    G.handCount[p] = handCount;
    // set any other variables
    memcpy(G.hand[p], silvers, sizeof(int) * handCount);
    G.hand[p][0] = copper;
    G.hand[p][2] = ambassador;
    G.hand[p][3] = copper;
    // call the refactored function again
    play_mine(4, gold, 2, p, &G);
    assert(G.handCount[p] == (handCount - 1)); 
    printf("Test completed!\n");
    return 0;
}