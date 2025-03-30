/**********************************************
	C++ code for project 1 in
	CSE 107 in 2022 winter, UC Santa Cruz,
			for Prof. Chen Qian.
**********************************************/
/*
	Student name: Darren Lee
	UCSC email: danalee@ucsc.edu
*/

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <string>

#include "marsaglia-rng.cpp"

using namespace std;

/*
Make a scatter plot of the distribution for these three RNG.
You'll generate num = 10,000 random number in range [0, num).
Make a single scatter plot using matplotlib with the x-axis being 
index of number and the y-axis being the number.

Since it's not easy to plot directly in C++,
You'll need to output your random number to a txt file first,
and then do the scatter plot in Google sheet.
Make sure to label your axis and title your plot appropriately.
*/
void distribution_random()
{
    // set the seed to 0
    srand(0);

    int num = 10000;
    int gen = 0;

    // generate num = 10,000 random numbers in range [0,num)
    for (int i = 0; i < num; i++)
    {
        gen = rand() % num;

        // print the index and the generated number
        cout << i << ", " << gen << "\n"; 
    }

    return;
}

void distribution_KISS()
{
    int num = 10000;
    uint32_t gen = 0;

    // generate num = 10,000 random numbers in range [0,num)
    for (int i = 0; i < num; i++)
    {
        gen = KISS;

        // print the index and the generated number
        cout << i << ", " << gen % num << "\n";
    }

    return;
}

void distribution_SHR3()
{
    int num = 10000;
    uint32_t gen = 0;

    // generate num = 10,000 random numbers in range [0,num)
    for (int i = 0; i < num; i++)
    {
        gen = SHR3;

        // print the index and the generated number
        cout << i << ", " << gen % num << "\n";
    }

    return;
}

bool sim_one_game(int n, float p)
{
    /*
    Write code to simulate one ping pong game to n points
    return the result of win/lose.
    True for win, and False for lose.
    TODO: Your code here
    */
    
    // initialize my points and friend's points
    int myPoints=0,friendPoints=0;

    // loop until the game ends
    while(true){
        
        // check if the randomly generated float is < p
        if ((rand() / double(RAND_MAX)) < p){
            // if it is, I win, increment my points
            myPoints++;
        }

        else{
            // else my friend wins
            friendPoints++;
        }

        // if either my points or my friend's points are >= n and the person with more points is up
        // by at least 2 points
        if (max(myPoints, friendPoints) >= n && abs(myPoints - friendPoints) >= 2){
            // if I have more points, I win, else my friend wins
            return (myPoints > friendPoints);
        } 
    }
    
}

float pingpong(int n = 21, float p = 0.3, int ntrials = 5000, int seed = 0)
{
    /*
    Write code to simulate a ping pong game to n points,
    where the probability of you winning a single point is p.
    You must win by 2; for example, if the score is 21 − 20, 
    the game isn’t over yet. Simulate ntrials # of games.
    :param n: The number of points to play to.
    :param p: The probability of YOU winning a single point.
    :param ntrials: The number of trials to simulate.
    :return: returns the probability YOU win the overall game.
    You can ONLY use the system function rand() to generate randomness.
    You need to generate a random float from the interval [0, 1).

    // TODO: Your code here
    */

    // set the seed
    srand(seed);

    // initialize the number of times I win 
    int numWins=0;

    // loop for ntrials times
    for (int i=0; i<ntrials; i++){

        // if I win the game
        if (sim_one_game(n, p)){
            // increment my number of wins
            numWins++;
        }
        
    }
    
    // return the probabilty that I win
    return (float) numWins/ntrials;

}

void plot_output()
{
    /*
    Consider the result of different p in {0, 0.04, 0.08,...,0.96, 1.0}
    and plot a figure with x-axis being p, and the y-axis being the 
    probability of winning the overall game (use your previous function).
    Plot 3 “curves” in different colors, one for each n in {3,11,21}.

    You'll output your probability result to a txt file in this fuction.
    And then do the plot in Google sheet.
    Make sure to label your axis and title your plot appropriately, 
    as well as include a  legend!
    */

    // TODO: Your code here
    // array for different n values
    int arr[]={3, 11, 21};

    // loop through the n values 
    for (int i = 0; i < 3; i++){

        // print out the n value
        cout<<"n="<<arr[i]<<"\n";

        // loop for floats in range [0,1] incrementing by 0.04
        for (float j = 0; j <= 1.04; j+=0.04){
            // print out the P(win point) and P(win game) using seed = 5
            cout<<j<<" "<<pingpong(arr[i], j, 5000, 5)<<"\n";
        }
        cout<<"\n";

    }

    return;
}

int main()
{
    // You can test out things here. Feel free to write anything below.
    // Example of rng usage:
    /*
    unsigned int i;
    uint32_t k;
    for(i = 0; i< 10; i++){
        k = KISS;
        printf("%"PRIu32"\n", k);
        printf("%d\n", k%100);
    }

    for(i = 0; i< 10; i++){
        k = SHR3;
        printf("%"PRIu32"\n", k);
        printf("%d\n", k%100);
    }
	*/

    // distribution_random();
    // distribution_KISS();
    // distribution_SHR3();

    // cout<<sim_one_game(21, 0.3)<<endl;
    // cout<<pingpong()<<endl;
    plot_output();
}
