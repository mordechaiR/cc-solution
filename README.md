Mordechai Rorvig
mrorvig@gmail.com
512-909-7409

Insight Data Engineering - Coding Challenge Submission
July 7, 2015

Background information: 

This README file describes my GitHub repository developed for the Coding Challenge.
I have coded my solution in C++, in one source file, main.cpp, to be found in the
src directory. My solution was developed on a 2013 MacBook Pro on OS X Yosemite. 
It is set to compile using g++ in my bash script called bash.sh, located in the 
root directory. My g++ version, given by g++ -v, is:

Configured with: --prefix=/Applications/Xcode.app/Contents/Developer/usr --with-gxx-include-dir=/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.10.sdk/usr/include/c++/4.2.1
Apple LLVM version 6.1.0 (clang-602.0.53) (based on LLVM 3.6.0svn)
Target: x86_64-apple-darwin14.3.0
Thread model: posix

Running the code:

The code should be executable on entering "bash run.sh" on a Mac command line, or 
by using the appropriate bash script execution commands on other systems. The 
path to the inputfile is specified in the bash.sh script, under the variable
INPUTPATH. This is fed into the C++ program as a command line argument. 

Program description:

My implementation uses hash tables (with C++ type of unordered_map) to store the
counts of each word, as well as the unique words per line. The median words
per line are found by storing the median words per line in a vector, and then 
sorting that vector on each iteration so that the median may be straightforwardly
extracted. 

The sort function has asymptotic time complexity O(k(log k)), where k is the number of
input lines (tweets). The program uses the insert() and find() methods on the hash maps,
which have time complexity O(n), where n is the number of unique words from the input.
Although there are more sophisticated algorithms for finding the median, without having
to use sort (such as the C++ nth_element function), I find the implementation scales
very quickly as written. It processes all the words and medians from the complete works 
of Shakespeare (shakes.txt, located in the /tweet_input directory) in 16 seconds on my 
machine. 

Lastly, I note that my implementation ignores null tweets (blank lines) and does 
not take them into account for calculating the median values. 

END  

