#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#define DECK_SIZE 52


//make array to hold cards
double deck[DECK_SIZE];
//make array to hold shuffled deck card order
int shuffle_inds[DECK_SIZE];


//helper function to shuffle deck
//creates a random permutation of the numbers
//from 1 to n for shuffling
void randperm(int *arr, int n) {
   // Initialize the array with 1 to n
   for (int i = 0; i < n; i++) {
       arr[i] = i;
   }
   //rand function in C isn't actually random
   //it creates a list of numbers based an an
   //algorithm that uses some number as the
   //initial condition (seed).  Use the current
   // time as the seed to make it seem more random
   srand(time(NULL));
   // Shuffle the array using Fisher-Yates algorithm
   // create a random number from 1 - 52
   // use that as the random ordering, and on every
   // loop iter, exchange arr[i] with the randomly
   // ordered number
   for (int i = n - 1; i > 0; i--) {
       int j = rand() % (i + 1);
       int temp = arr[i];
       arr[i] = arr[j];
       arr[j] = temp;
   }
}


//helper function to create deck and shuffle
void init_and_shuffle(double *deck_ptr) {
   //set deck elements
   int count = 0;
   // all values that will be in dec
   //numbers 2 - 9 are their own card value
   //10.01 - ten
   //10.02 - jack
   //10.03 - queen
   //10.04 - king
   //11 - ace
   double cardset[] = {2,3,4,5,6,7,8,9,10.01,10.02,10.03,10.04,11};
   for (int j = 1; j <5 ; j++) {
       //add digit 1-4 to the tens place
       //1 - spade
       //2 - heart
       //3 - diamond
       //4 - club
       for (int i = 0; i < sizeof(cardset)/sizeof(double); i++) {
           deck_ptr[count++] = round(100*(cardset[i]+(double)(j)/10))/100;
       }
   }
   // shuffle deck and store in temp deck array
   double temp_deck[DECK_SIZE];
   randperm(shuffle_inds, DECK_SIZE);
   for (int i = 0; i < DECK_SIZE; i++) {
       temp_deck[i] = deck_ptr[shuffle_inds[i]];
   }
   //point original deck to shuffled temp deck
   for (int i = 0; i < DECK_SIZE; i++) {
       *(deck_ptr+i) = temp_deck[i];
   }
}


//helper function to print a card name from its number
void print_card_name(double card_num) {
   switch ((int)(card_num)) {
       case 2:
           printf("Two of ");
           break;
       case 3:
           printf("Three of ");
           break;
       case 4:
           printf("Four of ");
           break;
       case 5:
           printf("Five of ");
           break;
       case 6:
           printf("Six of ");
           break;
       case 7:
           printf("Seven of ");
           break;
       case 8:
           printf("Eight of ");
           break;
       case 9:
           printf("Nine of ");
           break;
       case 11:
           printf("Ace of ");
           break;
       default:
           //printf("10 value \n");
           //add 0.01 to deal with rounding error;
           switch ((int)(card_num*100 + 0.01) % 5) {
               case 1:
                   printf("Ten of ");
                   break;
               case 2:
                   printf("Jack of ");
                   break;
               case 3:
                   printf("Queen of ");
                   break;
               case 4:
                   printf("King of ");
                   break;


           }


   }
   switch ((int)(card_num*10) % 5) {
       case 1:
           printf("Spades\n ");
           break;
       case 2:
           printf("Hearts\n ");
           break;
       case 3:
           printf("Diamonds\n ");
           break;
       case 4:
           printf("Clubs\n ");
           break;
   }
}


//ask player if they want to draw another card
//only reads if first char of input is y or n
int ask_player() {
   char draw_again[10];
   printf("Would you like to draw another card (y/n)?: \n");
   scanf("%s",draw_again);
   if (draw_again[0] == 'y' || draw_again[0] == 'Y') {
       return 1;
   } else if (draw_again[0] == 'n' || draw_again[0] == 'N') {
       return 0;
   } else {
       while (draw_again[0] != 'y' && draw_again[0] != 'Y' && \
           draw_again[0] != 'n' && draw_again[0] != 'N') {
           printf("Sorry, I didn't understand that\n");
           printf("Would you like to draw another card (y/n)?: \n");
           scanf("%s",draw_again);
       }
   }
}


void gameplay() {
    // initialize the deck
    init_and_shuffle(deck);
    
    // initialize player and dealer hands
    double player_deck[100];
    double dealer_deck[100];
    double *top_card = deck;
    int player_hand_size = 0;
    int dealer_hand_size = 0;

    // deal initial cards
    player_deck[player_hand_size++] = *top_card++;
    printf("Your face up card is:\n");
    print_card_name(player_deck[0]);
    
    player_deck[player_hand_size++] = *top_card++;
    printf("Your face down card is:\n");
    print_card_name(player_deck[1]);

    dealer_deck[dealer_hand_size++] = *top_card++;
    printf("Dealer's face up card is:\n");
    print_card_name(dealer_deck[0]);
    
    dealer_deck[dealer_hand_size++] = *top_card++;

    // calculate initial scores
    int player_score = 0;
    int dealer_score = 0;
    for(int i = 0; i < player_hand_size; i++) {
        if((int)player_deck[i] == 11) player_score += 11;
        else if((int)player_deck[i] == 10) player_score += 10;
        else player_score += (int)player_deck[i];
    }
    for(int i = 0; i < dealer_hand_size; i++) {
        if((int)dealer_deck[i] == 11) dealer_score += 11;
        else if((int)dealer_deck[i] == 10) dealer_score += 10;
        else dealer_score += (int)dealer_deck[i];
    }

    printf("You have %d cards in your hand\n", player_hand_size);
    printf("Your current score is: %d\n", player_score);

    // player's turn
    int player_done = 0;
    while(!player_done && player_score < 21) {
        if(ask_player() == 1) {
            player_deck[player_hand_size] = *top_card++;
            printf("Your new card is:\n");
            print_card_name(player_deck[player_hand_size]);
            
            if((int)player_deck[player_hand_size] == 11) player_score += 11;
            else if((int)player_deck[player_hand_size] == 10) player_score += 10;
            else player_score += (int)player_deck[player_hand_size];
            
            player_hand_size++;
            printf("Your current score is: %d\n", player_score);

            // dealer draws if under 16
            if(dealer_score < 16) {
                dealer_deck[dealer_hand_size] = *top_card++;
                if((int)dealer_deck[dealer_hand_size] == 11) dealer_score += 11;
                else if((int)dealer_deck[dealer_hand_size] == 10) dealer_score += 10;
                else dealer_score += (int)dealer_deck[dealer_hand_size];
                dealer_hand_size++;
                printf("Dealer draws a card\n");
            }
        } else {
            player_done = 1;
        }
    }
    
    // check if player busts
    if(player_score > 21) {
        printf("\nYour final hand:\n");
        for(int i = 0; i < player_hand_size; i++) {
            print_card_name(player_deck[i]);
        }
        printf("You bust with %d points! Dealer wins!\n", player_score);
        return;
    }

    // dealer's turn
    while(dealer_score < 16) {
        dealer_deck[dealer_hand_size] = *top_card++;
        if((int)dealer_deck[dealer_hand_size] == 11) dealer_score += 11;
        else if((int)dealer_deck[dealer_hand_size] == 10) dealer_score += 10;
        else dealer_score += (int)dealer_deck[dealer_hand_size];
        dealer_hand_size++;
        printf("Dealer draws a card\n");
    }

    // check if dealer busts
    if(dealer_score > 21) {
        printf("\nDealer's final hand:\n");
        for(int i = 0; i < dealer_hand_size; i++) {
            print_card_name(dealer_deck[i]);
        }
        printf("Dealer busts with %d points! You win!\n", dealer_score);
        return;
    }

    // show final hands
    printf("\nYour final hand:\n");
    for(int i = 0; i < player_hand_size; i++) {
        print_card_name(player_deck[i]);
    }
    printf("Your final score: %d\n\n", player_score);

    printf("Dealer's final hand:\n");
    for(int i = 0; i < dealer_hand_size; i++) {
        print_card_name(dealer_deck[i]);
    }
    printf("Dealer's final score: %d\n\n", dealer_score);

    // determine winner
    if(player_score > dealer_score) {
        printf("You win!\n");
    } else if(dealer_score > player_score) {
        printf("Dealer wins!\n");
    } else if(player_hand_size < dealer_hand_size) {
        printf("You win with fewer cards!\n");
    } else if(player_hand_size > dealer_hand_size){
        printf("Dealer wins with fewer cards!\n");
    } else {
        int has_black_jack = 0;
        
        // check if the player has black jack
        for(int i = 0; i < player_hand_size && !has_black_jack; i++) {
            if((int)(player_deck[i]*100 + 0.01) % 5 == 2 && // Jack
               ((int)(player_deck[i]*10) % 5 == 1 || (int)(player_deck[i]*10) % 5 == 4)) { // Spades or Clubs
                printf("You win with a black jack!\n");
                has_black_jack = 1;
            }
        }
        
        // check if the dealer has black jack if the player doesn't
        if(!has_black_jack) {
            for(int i = 0; i < dealer_hand_size && !has_black_jack; i++) {
                if((int)(dealer_deck[i]*100 + 0.01) % 5 == 2 && // Jack
                   ((int)(dealer_deck[i]*10) % 5 == 1 || (int)(dealer_deck[i]*10) % 5 == 4)) { // Spades or Clubs
                    printf("Dealer wins with a black jack!\n");
                    has_black_jack = 1;
                }
            }
        }

        // if neither has black jack, it's a tie
        if(!has_black_jack) {
            printf("It's a tie!\n");
        }
    }
}

int main(void) {
    gameplay();
}