Mordechai Rorvig

mrorvig@gmail.com

512-909-7409

Insight Data Engineering - Coding Challenge Submission

July 9, 2015


**Background information:**


This README file describes my GitHub repository developed for the Coding Challenge.
I have coded my solution in C++, in one source file, /src/main.cpp. My solution was 
developed on a 2013 MacBook Pro on OS X Yosemite. It is set to compile using g++ 
in my bash script /bash.sh. My g++ version, given by g++ -v, is:

Configured with: --prefix=/Applications/Xcode.app/Contents/Developer/usr --with-gxx-include-dir=/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.10.sdk/usr/include/c++/4.2.1
Apple LLVM version 6.1.0 (clang-602.0.53) (based on LLVM 3.6.0svn)
Target: x86_64-apple-darwin14.3.0
Thread model: posix


**Running the code:**


The code should be executable on entering "bash run.sh" on a Mac command line, or 
by using the appropriate bash script execution commands on other systems. The 
path to the inputfile is specified in the bash.sh script, under the variable
INPUTPATH. This is fed into the C++ program as a command line argument. 


**Program description:**


The objective of the challenge is to determine the frequency of words appearing in 
a list of tweets, as well as the running median unique number of words per tweet. 
Here, word denotes any text delimited by spaces or whitespace.

My primary goals for my implementation were correctness, speed/scalability, and readability. 
I tried to keep my solution concise to aid the latter goal, and my code is all 
contained with a single source file.

The two separate objectives of the challenge are distinct and motivated the choice 
of two different primary algorithms for achieving the solution. Common to both algorithms 
is the necessity of parsing the document line by line and word by word. This leads to a 
lower limit of time complexity for any solution of O(N), where N is the number of words
in the document. 

For finding the frequency of words, a C++ hash table type "unordered_map<string,int>" is used. 
The word acts as the key for the map, and the frequency acts as the associated integer value. As 
each word is processed, it is either inserted into the map (if not found) or its associated 
map frequency is incremented by one. The insertion and find methods are constant time 
complexity, or worst case O(N), where N is the number of entries in the map. Thus, the 
time complexity of the overall word frequency algorithm is worst-case O(N^2), and best case 
O(N). This solution is relatively fast, scalable, and also exceptionally concise
and easy to read and understand. 

One of the requirements of the challenge is to output the word frequencies in ASCII 
order. I accomplish this by converting the word frequency hash table into a 
"vector<pair<string,int> >" data type. This is then efficiently sorted in ASCII order
using the C++ "sort()" function and made ready for output. 

For finding the running median of unique words per line, I use a histogram based 
algorithm. Each resultant median is stored in a "vector<double>" data type for eventual 
output. The histogram based algorithm works in the following manner. First, as the word 
frequencies are counted, the unique number of words per line is also stored. If we 
had a vector or array of the unique number of words per line, all we would have to do 
to find the median would be to sort that array, then choose the element with the middle 
index. (In the case of an even array size, we would take the average of the two centrally 
indexed elements). Sorting the array on each line would be O(K log K) complexity, where K
denotes the number of lines (tweets) considered. (K is related to N as K=N/x, where x 
is the average number of words per line.)

Instead of sorting the array, however, we may simply insert each element into a histogram, 
where the key of each bin is the unique words per line. For example, if we had an array of 
{20, 10} unique words in two lines, we could store them in a histogram H where H{10}=1, 
H{20}=1, and H{i}=0 for all other i. Then, to find the median value, we are able to iterate
through the bins, keeping track of the total number of counts in each bin, until at least 
half the total number of counts for the entire histogram is reached. At that point, we 
have effectively chosen the central element of the array of unique words per line, 
without having to have sorted it. 

The histogram based algorithm is essentially constant time complexity, with a number of 
operations proportional to the maximum number of unique words found in the document. I 
assume there are no more than 100 unique words per line. Thus, the median finding algorithm 
is O(N) asymptotic time complexity. 

Lastly, I note that my implementation ignores null tweets (blank lines) and does 
not take them into account for calculating the median values. 


**Results:**

The program has been tested and found to perform correctly. I find the program to be 
highly scalable, for example, processing the complete works of Shakespeare 
(125,000 lines) in 2.6 seconds on my machine. 


**END**

