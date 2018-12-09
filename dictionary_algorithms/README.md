Dictionary comparison project is written in C++.

It comparises time and memory usage of node dictionary algorithm, the algorithm with STL map, and algorithm with STL unordered_map. Project consists of 2 parts: voc_gen.cpp and node_algorithm.cpp:
* first part, voc_gen.cpp is a generator which creates a file (strvoc.txt) with lines of pairs of words which consists of randomly chosen letters. Each time when this module executes, dictionary file changes and new random sets of letters are generated. 
* second part, node_algorithm.cpp reads data from the previously generated strvoc.txt file, builds node structure, fills STL map and STL unordered_map, calculates memory usage for these structures. If some word from dictionary has several entries of translations, then the first of them is counted as a translation for all three algorithms. This part also measures time which needed for each algorithm to find translations. Appropriate information about speed and memory usage then displayed: the first line for node algorithm, second -- for STL map algorithm, and third -- for the unordered_map algorithm.

In node algorithm, each node consists of node character which can be found in words, a boolean variable which indicated if this node has translation, translation string if this translation was gotten and an array of pointers to other nodes. A number of pointers in this array should be the same as the number of possible distinct letters in words. The root node has '\0' character. Approximate possible structure:

![Node structure diagram](https://github.com/alex-and-ria/pet_projects/blob/master/dictionary_algorithms/node_structure.svg)

If you have questions or ideas for improving this project, don't hesitate and mail me (alex.and.riaqqq@gmail.com).
