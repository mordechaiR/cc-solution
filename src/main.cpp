
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <map>
#include <unordered_map>
#include <string>
using namespace std;

//find the current median value, using appropriate formula for the median.
void medianCalculator (vector<int> &numUniqueWords, vector<double> &medianVals,
                       int &row, bool &rowIsEven) {
    sort(numUniqueWords.begin(), numUniqueWords.end());
    if (rowIsEven == true) {
        medianVals.push_back(numUniqueWords[row/2]);
        rowIsEven = false;
    }
    else {
        medianVals.push_back(((double)numUniqueWords[row/2] + numUniqueWords[row/2+1])/2);
        rowIsEven = true;
    }
}

//determine word counts (overall and unique) from the current tweet.
void wordCounter (unordered_map<string, int> &wordCounts, vector<double> &medianVals,
                  vector<int> &numUniqueWords, string &tweet, int &row) {
    //use an unordered_map to count unique words.
    unordered_map<string, int> uniqueWordsMap;
    numUniqueWords.push_back(0);
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
            numUniqueWords[row]++;
        }
    }
}

//find the word frequencies and median unique words per tweet from the input file of tweets.
void findWordsAndMedians (unordered_map<string, int> &wordCounts, vector<double> &medianVals, string &inputFile) {
    vector<int> numUniqueWords;
    int row = 0;
    bool rowIsEven = true;
    string tweet, word;
    ifstream input (inputFile);
    //process the input file row by row (line by line).
    while (getline(input, tweet)) {
        wordCounter( wordCounts, medianVals, numUniqueWords, tweet, row );
        if (numUniqueWords[row] != 0 ) {
            medianCalculator( numUniqueWords, medianVals, row, rowIsEven );
            row++;
        }
        else {
            numUniqueWords.pop_back();
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

//main program.
int main ( int argc, char *argv[] ) {
    unordered_map<string, int> wordCounts;
    vector<double> medianVals;
    //declare input/output paths.
    string inputFile = argv[1];
    string wordOutputFile = "./tweet_output/ft1.txt";
    string medianOutputFile = "./tweet_output/ft2.txt";
    //process input and output.
    findWordsAndMedians( wordCounts, medianVals, inputFile );
    doWordOutput( wordCounts, wordOutputFile );
    doMedianOutput( medianVals, medianOutputFile );
}




