# Probability-via-Simulation
Project I: Probability via Simulation

Darren Lee
CSE 107 Winter 2022

-----------------------------------------------------------------------------------------
Building:

    make - builds prog1 and pokemon executables
    make clean - removes object files and executables

-----------------------------------------------------------------------------------------
Running:

    ./pokemon - prints out results of parts a to d 

-----------------------------------------------------------------------------------------
Code Files:

prog1.cpp
    Contains the code for the function to make scatter plots of the 
    random distributions of the 3 RNGs rand(),  KISS, and SHR3
    
    Also contains the code for functions for simulating one game of pingpong, 
    simulating a pingpong game up to n points, and plotting the output of pingpong with 
    n values of 3 and probabilities that you win p in {0, 0.04, 0.08,...,0.96, 1.0}

    Main function is just used for testing these functions

pokemon.cpp
    Contains the functions for calculating statistics in parts a and b and
    for simulating the numbers of encounters for part c and d

    Part d function generates a random number from 0 to 1 with rand() every time 
    a Pokemon is encountered to try to catch it even if the Pokemon has already been
    caught before

    Main function prints out the results of part a through d

-----------------------------------------------------------------------------------------
Data Files:

distribution_kiss.txt - random distribution for KISS 

distribution_random - random distribution for rand()

distribution_shr3.txt - random distribution for SHR3

pingpong.txt - output for plot_output() function in prog1.cpp for plotting pingpong 
    plot_output

pokemon.txt - contains the data (id, legendary, height weight, encounter probability,
    catch probability) for the Pokemon
