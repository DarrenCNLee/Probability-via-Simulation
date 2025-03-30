/* =============================================================
# You may define helper functions, but DO NOT MODIFY
# the parameters or names of the provided functions.
# =============================================================
*/
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

/*
The data for this problem is provided in pokemon.txt and follows the
following format.
Col 1: pokemon_id: A unique identifier for the Pokemon.
Col 2: is_legendary: A 1 if the Pokemon is legendary, and 0 otherwise.
Col 3: height: The height of the Pokemon in meters.
Col 4: weight: The weight of the Pokemon in kilograms.
Col 5: encounter_prob: The probability of encountering this Pokemon 
in the wild grass. Note the sum of this entire column is 1, since when
you make an encounter, exactly one of these Pokemon appears.
Col 6: catch_prob: Once you have encountered a Pokemon, the probability 
you catch it. (Ignore any mechanics of the actual game if you've played 
a Pokemon game in the past.)
*/

float *part_a(char* filename){
    /*
    Compute the proportion of Pokemon that are legendary, the average
    height, the average weight, the average encounter_prob, and average 
    catch_prob. 
    :param filename: The path to the file as described in the pset.
    :return: An array of length 5 with these 5 quantities.
    */
    // TODO: Your code here
    
    float probEncount=0,probCatch=0,totalProbEncount=0,totalProbCatch=0;
    int id=0,legend=0, totalLegend=0;
    float height=0,weight=0,totalHeight=0,totalWeight=0,numPoke=0;

    // open the input file
    ifstream infile;
    infile.open(filename);
    
    // read the data
    while(infile >> id >> legend >> height >> weight >> probEncount >> probCatch){
  
        totalLegend+=legend;
        
        totalHeight+=height;

        totalWeight+=weight;
        
        totalProbEncount+=probEncount;
        
        totalProbCatch+=probCatch;
        
        numPoke++;
    }

    // calculate the data
    float probLegend=(float)totalLegend/(float)numPoke;
    float avgHeight=(float)totalHeight/(float)numPoke;
    float avgWeight=(float)totalWeight/(float)numPoke;
    float avgEncounterProb=(float)totalProbEncount/(float)numPoke;
    float avgCatchProb=(float)totalProbCatch/(float)numPoke;
    
    // create the array of data
    static float arr[] = {probLegend, avgHeight, avgWeight, avgEncounterProb, avgCatchProb};

    infile.close();

    return arr;
}


float *part_b(char* filename){
    /*
    Compute the proportion of Pokemon that are legendary, the average
    height, the average weight, the average encounter_prob, and average 
    catch_prob OF ONLY those Pokemon STRICTLY heavier than the median weight. 
    :param filename: The path to the file as described in the pset.
    :return: A numpy array of length 5 with these 5 quantities.
    */
    //pass # TODO: Your code here
    float probEncount=0,probCatch=0,totalProbEncount=0,totalProbCatch=0;
    int id=0,legend=0,totalLegend=0;
    float height=0,weight=0,totalHeight=0,totalWeight=0,numPoke=0;
        
    // create a list of weights
    vector<int> weightList; 

    // open the input file
    ifstream infile;
    infile.open(filename);
    
    // read the data
    while(infile >> id >> legend >> height >> weight >> probEncount >> probCatch){
             
        // add the weights to the list of weights
        weightList.push_back(weight);
    }

    // sort the weights
    sort(weightList.begin(),weightList.end());
    // get the median index of the list of weights
    int medianIndex=weightList.size()/2+1;

    // return to the beginning of the input file
    infile.clear();
    infile.seekg(0);
    
    // read the data again
    while(infile >> id >> legend >> height >> weight >> probEncount >> probCatch){

        // if the weight is heavier than the median weight
        if(weight>weightList[medianIndex]){
            // add the data to the totals
            totalLegend+=legend;
            totalHeight+=height;
            totalWeight+=weight;
            totalProbEncount+=probEncount;
            totalProbCatch+=probCatch;
            numPoke++;
        }
    }

    // calculate
    float probLegend=(float)totalLegend/(float)numPoke;
    float avgHeight=(float)totalHeight/(float)numPoke;
    float avgWeight=(float)totalWeight/(float)numPoke;
    float avgEncounterProb=(float)totalProbEncount/(float)numPoke;
    float avgCatchProb=(float)totalProbCatch/(float)numPoke;

    // make the array
    static float arr[] = {probLegend, avgHeight, avgWeight, avgEncounterProb, avgCatchProb};

    infile.close();

    return arr;
}


float part_c(char* filename, int ntrials=5000){
    /*
    Suppose you are walking around the wild grass, and you wonder: how
    many encounters do you expect to make until you ENCOUNTER each Pokemon 
    (at least) once? 
    :param filename: The path to the file as described in the pset.
    :param ntrials: How many simulations to run.
    :return: The (simulated) average number of ENCOUNTERS you expect to 
    make, until you ENCOUNTER each Pokemon (at least) once.
    Hint(s): You only need to use one of the columns for this part!
    */
    // TODO: Your code here
    
    // set the random seed to 1
    srand(1);

    float probEncount=0,probCatch=0;
    int id=0,legend=0;
    float height=0,weight=0;
       
    int totalEncounters=0;

    // open the input file
    ifstream infile;
    infile.open(filename);

    // create array for cumulative encounter probability distribution
    float cpd[26];

    cpd[0]=0;

    // initialize cumulative probability
    float cumProb=0;

    // create set of ids
    set<int> idSet;

    // initialize the index of the cpd array
    int j=0;

    // read the data
    while(infile >> id >> legend >> height >> weight >> probEncount >> probCatch){
        // insert the ids into a set
        idSet.insert(id);

        // increase cumulative probability by the encounter probability
        cumProb+=probEncount;

        j++;

        // set cumulative probability
        cpd[j]=cumProb;
    }

    // loop for ntrials
    for (int i=0;i<ntrials;i++){
        
        // create set of ids of pokemon we have encountered
        set<int> encountSet;

        while(true){
            // increment number of encounters
            totalEncounters++;

            // generate a random number from 0 to 1
            float gen=rand()/double(RAND_MAX);

            // loop through the cpd array
            for(int k=0;k<26;k++){
                
                // check if gen is between probabilities
                if(cpd[k]<gen<cpd[k+1]){
                    // we encountered the pokemon so insert the id 
                    encountSet.insert(k-1);
                
                    break;
                } 
            }
  
            // once we have encountered all the pokemon
            if (encountSet==idSet){
                // then break out of the infinite loop
                break;
            }
        }
    
    }

    infile.close();

    // return the average number of encounters required to encounter each pokemon
    return (float) totalEncounters/ntrials;

}


float part_d(char* filename, int ntrials=5000){
    /*
    Suppose you are walking around the wild grass, and you wonder: how
    many encounters do you expect to make until you CATCH each Pokemon 
    (at least) once? 
    :param filename: The path to the file as described in the pset.
    :param ntrials: How many simulations to run.
    :return: The (simulated) average number of ENCOUNTERS you expect to 
    make, until you CATCH each Pokemon (at least) once.
    Hint(s):
    1. You only need to use two of the columns for this part!
    2. You may want to use rand(...).
    */
    // TODO: Your code here

    // set the seed to 1
    srand(1);

    float probEncount=0,probCatch=0;
    int id=0,legend=0;
    float height=0,weight=0;
        
    int totalEncounters=0;

    // open the input file
    ifstream infile;
    infile.open(filename);
    
    // create vector for catch rates
    vector<float> catchRateVec;

    // create array for cumulative encounter probability distribution
    float cpd[26];

    cpd[0]=0;

    // initialize cumulative probability
    float cumProb=0;

    // create set of ids
    set<int> idSet;

    // initialize the index of the cpd array
    int j=0;

    // read the data
    while(infile >> id >> legend >> height >> weight >> probEncount >> probCatch){
        // insert the ids into a set
        idSet.insert(id);

        // set the catch rate in the catch rate vector
        catchRateVec.push_back(probCatch);

        // increase cumulative probability by the encounter probability
        cumProb+=probEncount;

        j++;

        // set cumulative probability
        cpd[j]=cumProb;

    }

    // loop for ntrials
    for (int i=0;i<ntrials;i++){

        // set for pokemon we have caught
        set<int> caughtSet;
        
        while(true){
            // increment number of encounters
            totalEncounters++;

             // generate a random number from 0 to 1
            float gen=rand()/double(RAND_MAX);

            // loop through the cpd array
            for(int k=0;k<26;k++){
        
                // if the generated number is between probabilites in the cpd
                if(cpd[k]<gen<cpd[k+1]){
                                    
                    // we encountered a pokemon and we check if we catch it or not
                    if(rand()/double(RAND_MAX)<catchRateVec[k-1]){

                        // we caught the pokemon so insert into the set of caught pokemon
                        caughtSet.insert(k-1);

                        
                    }
                    break;
                } 
            }

            // if we caught all the pokemon
            if(caughtSet==idSet){
                // then break out of the infinite loop
                break;
            }
        }
    }

    infile.close();

    // return the average number of encounters before you encounter and catch all the pokemon
    return (float) totalEncounters/ntrials;
}


int main(){
    // You can test out things here. Feel free to write anything below.
    char filename[] = "data/pokemon.txt";

	//Print the results of part_a to d here.
    // print results of a
    float *arrA=part_a(filename);
    cout<<"part_a: "<<endl;    

    cout<<"proportion legendary: "<<arrA[0]<<endl;
    cout<<"average height: "<<arrA[1]<<endl;
    cout<<"average weight: "<<arrA[2]<<endl;
    cout<<"average encounter probability: "<<arrA[3]<<endl;
    cout<<"average catch probability: "<<arrA[4];

    cout<<endl;
    cout<<endl;

    // print results of b
    float * arrB=part_b(filename);
    cout<<"part_b: "<<endl;

    cout<<"proportion legendary: "<<arrB[0]<<endl;
    cout<<"average height: "<<arrB[1]<<endl;
    cout<<"average weight: "<<arrB[2]<<endl;
    cout<<"average encounter probability: "<<arrB[3]<<endl;
    cout<<"average catch probability: "<<arrB[4];

    cout<<endl;
    cout<<endl;

    // print results of c
    cout<<"part_c: ";
    cout<<part_c(filename)<<endl;
    cout<<endl;


    // print results of d
    cout<<"part_d: ";
    cout<<part_d(filename)<<endl;
}