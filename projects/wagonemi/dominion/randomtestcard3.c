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
    int k[14] = {adventurer, estate, copper, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
    // declare the game state
    struct gameState G;
    int tributeRevealedCards[2];
    // declare the arrays
    int coppers[MAX_HAND];
    int silvers[MAX_HAND];
    int golds[MAX_HAND];
    int p2, r, handCount, p, deckCount, discardCount, seed;
    srand(time(0));

    printf("Begin Testing play_tribute():\n");
    for(int i = 0; i < 50; i++){
        handCount = rand() % 5;
        p = rand() % 2;
        deckCount = rand() % 5;
        discardCount = rand() % 5;
        seed = rand() % 100;
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
            p2 = 1;
        }
        // set any other variables
        memcpy(G.hand[p], coppers, sizeof(int) * handCount);
        for(int j = 0; j < handCount; j++){
            G.hand[p][j] =k[rand() % 3];
        }
        memcpy(G.hand[p2], coppers, sizeof(int) * handCount);
        for(int j = 0; j < handCount; j++){
            G.hand[p2][j] =k[rand() % 3];
        }
        memcpy(G.discard[p], coppers, sizeof(int) * discardCount);
        for(int j = 0; j < discardCount; j++){
            G.discard[p][j] =k[rand() % 3];
        }
        memcpy(G.discard[p2], coppers, sizeof(int) * discardCount);
        for(int j = 0; j < discardCount; j++){
            G.discard[p2][j] =k[rand() % 3];
        }
        memcpy(G.deck[p], coppers, sizeof(int) * deckCount);
        for(int j = 0; j < deckCount; j++){
            G.deck[p][j] =k[rand() % 3];
        }
        memcpy(G.deck[p2], coppers, sizeof(int) * deckCount);
        for(int j = 0; j < deckCount; j++){
            G.deck[p2][j] =k[rand() % 3];
        }
        // call the refactored function

        int initial_coins = G.coins;
        int discard_card = G.hand[p][0];
        play_tribute(p, p2, tributeRevealedCards, &G);
        // verify that your asserts pass, for the bugs your asserts may fail
        assert(G.coins == (initial_coins + 4)); //Checks if current player gets +4 gold from finding 2 treasure cards
        
        assert(tributeRevealedCards[1] == ambassador); //Checks if the second element of tribute revealed cards contains the correct card
        
        assert(G.deckCount[1] == 0); //Checks that deck count is properly decremented
        
        assert(G.deckCount[1] != handCount); //Checks that deck count is decremented
        printf("Test completed!\n");
    }
    return 0;
}