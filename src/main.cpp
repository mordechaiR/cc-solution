// Insight Coding Challenge Solution
// C++ source code, /src/main.cpp
// See /README.md for further documentation
// Mordechai Rorvig, mrorvig@gmail.com
// July 9, 2015

//libraries included for functionality:
#include <fstream>        //ifstream, ofstream
#include <sstream>        //istringstream
#include <iomanip>        //setw, left, fixed
#include <vector>         //vector
#include <unordered_map>  //unordered_map
#include <string>         //string
//use std namespace to aid readability
using namespace std;

//main class for solution
class WordsAndMediansProcessor {
private:
    //assume tweets contain no more than 100 unique words each.
    int MAX_UNIQUE_WORDS_PER_TWEET = 100;
    //use histogram for tracking median values.
    vector<int> histogram;
public:
    //find the current median value, using algorithm based on histogram counts;
    //use appropriate formula for median based on even vs. odd number considerations.
    void medianFromHistogram (vector<double> &medianVals, int &row, bool &rowIsEven) {
        //total number of tweets considered (counting from 1).
        int totalCounts = row+1;
        int halfTotal = totalCounts/2;
        //current sum & count of tweets considered.
        int sumCounts = 0;
        int currCounts = 0;
        //keep track of previous unique words and sum.
        int prevUniqueWords = 0;
        int prevSumCounts = 0;
        //iterate through each bin, until reaching at least half of total tweets considered;
        //at that point, the median value will have been reached, since we iterate through
        //a sorted, ascending set.
        for (int uniqueWords = 1; uniqueWords < MAX_UNIQUE_WORDS_PER_TWEET; uniqueWords++) {
            currCounts = histogram[uniqueWords];
            if (currCounts > 0) {
                sumCounts += currCounts;
                if (sumCounts > halfTotal) {
                    //if row is currently even, the central index of an ordered set is reached
                    //and the median is directly extracted.
                    if (rowIsEven == true) {
                        medianVals.push_back(uniqueWords);
                        rowIsEven = false;
                    }
                    //if row is currently odd, check if prevCounts was exactly at the halfway point
                    else {
                        if (prevSumCounts == halfTotal)
                            medianVals.push_back( ( (double)uniqueWords + prevUniqueWords)/2);
                        else
                            medianVals.push_back(uniqueWords);
                        rowIsEven = true;
                    }
                    break;
                }
                prevUniqueWords = uniqueWords;
                prevSumCounts = sumCounts;
            }
        }
    }
    
    //determine word counts (overall and unique) from the current tweet.
    void wordCounter (unordered_map<string, int> &wordCounts, vector<double> &medianVals,
                      int &numUniqueWords, string &tweet, int &row) {
        //use an unordered_map to count unique words.
        unordered_map<string, int> uniqueWordsMap;
        numUniqueWords = 0;
        string word;
        istringstream iss (tweet);
        //inner loop to step through each word of the tweet.
        while (iss >> word) {
            //if current word has been found before, increment the count.
            if (wordCounts.find(word) != wordCounts.end()) {
                wordCounts[word]++;
            }
            //otherwise, add the word to the map.
            else {
                wordCounts.insert(pair<string, int> (word, 1));
            }
            //use uniqueWordsMap to keep track of unique words per line;
            //if word has not been found before on this tweet, add it to map and increment count.
            if (uniqueWordsMap.find(word) == uniqueWordsMap.end()) {
                uniqueWordsMap.insert(pair<string, int> (word, 1));
                numUniqueWords++;
            }
        }
    }
    
    //find the word frequencies and median unique words per tweet from the input file of tweets.
    void findWordsAndMedians (unordered_map<string, int> &wordCounts, vector<double> &medianVals,
                              string &inputFile) {
        histogram.resize(MAX_UNIQUE_WORDS_PER_TWEET,0);
        int numUniqueWords = 0;
        int row = 0;
        bool rowIsEven = true;
        string tweet, word;
        ifstream input (inputFile);
        //process the input file row by row (line by line).
        while (getline(input, tweet)) {
            wordCounter( wordCounts, medianVals, numUniqueWords, tweet, row );
            if (numUniqueWords != 0 ) {
                histogram[numUniqueWords]++;
                medianFromHistogram( medianVals, row, rowIsEven );
                row++;
            }
        }
        input.close();
    }
    
    //output the data on the words and their frequencies.
    void doWordOutput (unordered_map<string, int> &wordCounts, string &wordOutputFile) {
        //first, sort the wordCount data by making conversion to a vector type.
        vector<pair<string,int> > orderedWordCounts;
        for (auto iter = wordCounts.begin(); iter != wordCounts.end(); iter++) {
            orderedWordCounts.push_back(pair<string, int> (iter->first, iter->second));
        }
        sort(orderedWordCounts.begin(), orderedWordCounts.end());
        //next, print the sorted output.
        ofstream wordOutput ( wordOutputFile );
        for (auto iter = orderedWordCounts.begin(); iter != orderedWordCounts.end(); iter++) {
            wordOutput << setw(27) << left << iter->first << " " << iter->second << endl;
        }
        wordOutput.close();
    }
    
    //output the data on the median number of unique words per line.
    void doMedianOutput (vector<double> &medianVals, string &medianOutputFile) {
        ofstream medianOutput ( medianOutputFile );
        medianOutput << fixed << setprecision(2);
        for (auto iter = medianVals.begin(); iter != medianVals.end(); iter++) {
            medianOutput << *iter << endl;
        }
        medianOutput.close();
    }
};

//main program.
int main ( int argc, char *argv[] ) {
    unordered_map<string, int> wordCounts;
    vector<double> medianVals;
    //declare input/output paths.
    string inputFile = argv[1];
    string wordOutputFile = "./tweet_output/ft1.txt";
    string medianOutputFile = "./tweet_output/ft2.txt";
    //process input and output.
    WordsAndMediansProcessor solution;
    solution.findWordsAndMedians( wordCounts, medianVals, inputFile );
    solution.doWordOutput( wordCounts, wordOutputFile );
    solution.doMedianOutput( medianVals, medianOutputFile );
}




