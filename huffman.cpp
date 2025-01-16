//Huffman.cpp
//Create Huffman tree + create codetable from freq.txt
//Write code table to codetable.txt
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
std::vector<std::vector<std::string>> readFile(std::string path);
std::vector<struct Node*> sortNodes(std::vector<struct Node*> input);
std::vector<struct Node*> buildHuffman(std::vector<struct Node*> input);
void printHuffmanTree(struct Node* input);
void printHuffmanCodes(struct Node* input, std::string code);
//global node
struct Node {
int freq;
std::string c;
struct Node* left;
struct Node* right;
Node(int f, std::string ch) {
freq = f;
c = ch;
left = NULL;
right = NULL;
}
};
//global code list
std::vector<std::string> globalCodes;
int main() {
//get freq data from freq.txt
std::vector<std::vector<std::string>> freqMap = readFile("./freq.txt");
//"clean" vector
std::vector<std::vector<std::string>> cleanVector;
for (int i = 0; i < freqMap.size(); i++) {
if (freqMap[i].size() == 0) {
//do nothing, only want to included non-empty spaces
}
else
cleanVector.push_back(freqMap[i]);
}
//construct huffman tree
//make vector of nodes
std::vector<struct Node*> nodes;
for (int i = 0; i < cleanVector.size(); i++) {
struct Node* toAdd = new Node(std::stoi(cleanVector[i][1]),
cleanVector[i][0]);
nodes.push_back(toAdd);
}
//sort nodes
nodes = sortNodes(nodes);
//build tree
nodes = buildHuffman(nodes);
//print Huffman codes
printHuffmanCodes(nodes[0], "");
//write codes to codetable.txt
std::ofstream codeTable;
codeTable.open("codetable.txt");
for (int i = 0; i < globalCodes.size(); i++)
codeTable << globalCodes[i] << std::endl;
codeTable.close();
return 0;
}//end main
std::vector<std::vector<std::string>> readFile(std::string path) {
std::ifstream file;
file.open(path);
if (file.fail()) {
std::cout << "Could not find file" << std::endl;
exit(1);
}
std::string line;
std::vector<std::vector<std::string>> charFreqs;
charFreqs.resize(128);
int count = 0;
while (std::getline(file, line, '\n')) {
std::string character; //character in line of freq.txt
std::string freq; //freq of character
//special cases
if (line.substr(0, 1) == " ") { //check if first char is space
character = line.substr(0, 1);
freq = line.substr(2); //set what's after delimiter as freq
}
else if (line.substr(0, 2) == "LF") { //if "char" is LF
character = "LF";
freq = line.substr(3);
}
else { //case other ASCII characters
character = line.substr(0, 1);
freq = line.substr(2); //freq is what's left after delimiter space
}
//add to input array
charFreqs[count].push_back(character);
charFreqs[count].push_back(freq);
count++;
}
return charFreqs;
} //end readFile
std::vector<struct Node*> sortNodes(std::vector<struct Node*> input) {
//sort by frequency values
bool keepGoing = true;
int nextIndex = input.size() - 1;
while (keepGoing) {
//find max value
struct Node* max = input[0];
int maxIndex = 0;
for (int i = 0; i < nextIndex + 1; i++) {
if (input[i]->freq > max->freq) {
max = input[i];
maxIndex = i;
}
}
//swap max and nextIndex
struct Node* temp = input[nextIndex];
input[nextIndex] = max;
input[maxIndex] = temp;
//decrease range
nextIndex--;
if (nextIndex == 0)
keepGoing = false;
}
return input;
}
std::vector<struct Node*> buildHuffman(std::vector<struct Node*> input) {
int inputSize = input.size();
for (int i = 0; i < inputSize - 1; i++) {
if (input.size() > 1) {
struct Node* z = new Node(999, "placeholder");
struct Node* x = input[0];
struct Node* y = input[1];
input.erase(input.begin() + 0); input.erase(input.begin() + 0);
z->freq = x->freq + y->freq;
z->left = x;
z->right = y;
input.push_back(z);
if (input.size() > 1)
input = sortNodes(input);
}
else {
}
}
return input;
}
void printHuffmanTree(struct Node* input) {
if (input == nullptr)
return;
printHuffmanTree(input->left);
// then recur on right subtree
printHuffmanTree(input->right);
// now the node
if (input->c != "placeholder")
std::cout << input->c << ": " << input->freq << std::endl;
}
void printHuffmanCodes(struct Node* input, std::string code) {
if (!input)
return;
if (input->c != "placeholder") {
std::cout << input->c << " " << code << std::endl;
globalCodes.push_back(input->c + " " + code);
}
printHuffmanCodes(input->left, code + "0");
printHuffmanCodes(input->right, code + "1");
}
