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
    int k[11] = { adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall, estate};
    // declare the game state
    struct gameState G;
    int handCount = rand() % 10;
    int p = rand() % 2;
    int p2;
    int seed = rand() % 100;
    int r;
    // declare the arrays
    int coppers[MAX_HAND];
    int silvers[MAX_HAND];
    int golds[MAX_HAND];

    printf("Begin Testing play_minion():\n");
    for(int i = 0; i < 50; i++){
        //
        // set the state of your variables
        // comment on what this is going to test
        //
        memset(&G, 23, sizeof(struct gameState));
        // set the game state
        r = initializeGame(2, k, seed, &G);
        // initialize a new game
        G.handCount[p] = handCount;
        if(p == 1){
            G.handCount[0] = handCount;
            p2 = 0;
            
        }
        else{
            G.handCount[1] = handCount;
            p2 = 0;
        }
        // set any other variables
        memcpy(G.hand[p], coppers, sizeof(int) * handCount);
        for(int j = 0; j < handCount; j++){
            G.hand[p][j] =k[rand() % 11];
        }
        memcpy(G.hand[p2], coppers, sizeof(int) * handCount);
        for(int j = 0; j < handCount; j++){
            G.hand[p2][j] =k[rand() % 11];
        }
        // call the refactored function
        int initial_coins = G.coins;
        minioncardEffect(rand() % 2, rand() % 2, &G, rand() % handCount);
        // verify that your asserts pass, for the bugs your asserts may fail
        assert(G.coins == (initial_coins + 2)); // Checks that coins was properly incremented when minion choice1 is played.
        
        assert(G.handCount[p] == 4); // Checks if the players handCount is 4 after play_minion choice2
        
        int minion_check = 0;
        for(int i = 0; i < G.discardCount[p]; i++){
            if(G.discard[p][i] == "minion"){minion_check = 1;}
        }
        assert(minion_check);
        // verify that your asserts pass, for the bugs your asserts may fail
        printf("Test %d completed!\n", i);
        }
    return 0;
}