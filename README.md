Write a C++ program called Huffman.cpp to create Huffman codes. Program input is a file
called freq.txt (make up your own file for testing) that contains data on the characters in some
cleartext file in the form of each character's non-zero frequency of occurrence in the cleartext
file. (Note that these are frequency counts, not percentages, and it doesn't matter if the values do
not sum to 100.) You can assume that freq.txt contains only characters from the standard ASCII
128 character set and that the results are ordered by the ASCII integer for each character. The
end-of-line character in a text file is a non-printable line feed character, with ASCII code 10, and
will be written in the freq.txt file as LF. Thus the freq.txt file might look like
LF 2
. 1
M 7
c 3
d 5
e 14
f 2
etc.
[Hint: Suppose your text is
Mary had a little lamb.
Its fleece was white as snow.
What is the most frequently occurring character? It's not "a" (6 occurrences).]
Your program should create a "code table" that gives each character and its binary Huffman
code. Save this information in an external file called codetable.txt where each line of the file is a
character and its code, ordered by the ASCII value of the character.
