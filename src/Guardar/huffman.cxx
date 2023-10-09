#include "huffman.h"
#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <unordered_map>
using namespace std;

#define EMPTY_STRING ""

// Implementación de las funciones de la clase Huffman
// Constructor de Huffman
Huffman::Huffman() {
    root = nullptr;
}

// Función para codificar una cadena de texto
std::string Huffman::compress(const std::string& text) {
    root = buildHuffmanTree(text);
    return "cadena comprimida";
}

// Utility function to check if Huffman Tree contains only a single node
bool Huffman::isLeaf(Node* node) {
    return node->left == nullptr && node->right == nullptr;
}

// Traverse the Huffman Tree and store Huffman Codes in a map.
void Huffman::encode(Node* root, string str, unordered_map<char, string>& huffmanCode) {
    if (root == nullptr) {
        return;
    }

    // found a leaf node
    if (isLeaf(root)) {
        huffmanCode[root->ch] = (str != EMPTY_STRING) ? str : "1";
    }

    encode(root->left, str + "0", huffmanCode);
    encode(root->right, str + "1", huffmanCode);
}

// Traverse the Huffman Tree and decode the encoded string
void Huffman::decode(Node* root, int& index, string str) {
    if (root == nullptr) {
        return;
    }

    // found a leaf node
    if (isLeaf(root)) {
        cout << root->ch;
        return;
    }

    index++;

    if (str[index] == '0') {
        decode(root->left, index, str);
    } else {
        decode(root->right, index, str);
    }
}

// Función para asignar un nuevo nodo de árbol
Node* Huffman::getNode(char ch, int freq, Node* left, Node* right) {
    Node* node = new Node();
    node->ch = ch;
    node->freq = freq;
    node->left = left;
    node->right = right;
    return node;
}

// Builds Huffman Tree and decodes the given input text
Node* Huffman::buildHuffmanTree(const std::string& text)
{
	// base case: empty string
	if (text == EMPTY_STRING) {
		return nullptr;
	}

	// count the frequency of appearance of each character
	// and store it in a map
	unordered_map<char, int> freq;
	for (char ch: text) {
		freq[ch]++;
	}

	// Create a priority queue to store live nodes of the Huffman tree
	priority_queue<Node*, vector<Node*>, comp> pq;

	// Create a leaf node for each character and add it
	// to the priority queue.
	for (auto pair: freq) {
		pq.push(getNode(pair.first, pair.second, nullptr, nullptr));
	}

	// do till there is more than one node in the queue
	while (pq.size() != 1)
	{
		// Remove the two nodes of the highest priority
		// (the lowest frequency) from the queue

		Node* left = pq.top(); pq.pop();
		Node* right = pq.top();	pq.pop();

		// create a new internal node with these two nodes as children and
		// with a frequency equal to the sum of the two nodes' frequencies.
		// Add the new node to the priority queue.

		int sum = left->freq + right->freq;
		pq.push(getNode('\0', sum, left, right));
	}

	// `root` stores pointer to the root of Huffman Tree
	Node* root = pq.top();

	// Traverse the Huffman Tree and store Huffman Codes
	// in a map. Also, print them
	unordered_map<char, string> huffmanCode;
	encode(root, EMPTY_STRING, huffmanCode);

	cout << "Huffman Codes are:\n" << endl;
	for (auto pair: huffmanCode) {
		cout << pair.first << " " << pair.second << endl;
	}

	cout << "\nThe original string is:\n" << text << endl;

	// Print encoded string
	string str;
	for (char ch: text) {
		str += huffmanCode[ch];
	}
    //Guardar el texto codificado en un archivo
    std::ofstream archivo_salida("archivo_comprimido.txt");
    if (!archivo_salida.is_open()) {
        std::cout << "No se pudo abrir el archivo de salida" << std::endl;
        return 0;
    }

    archivo_salida << str;
    archivo_salida.close();

	cout << "\nThe encoded string is:\n" << str << endl;
	cout << "\nThe decoded string is:\n";

	if (isLeaf(root))
	{
		// Special case: For input like a, aa, aaa, etc.
		while (root->freq--) {
			cout << root->ch;
		}
	}
	else {
		// Traverse the Huffman Tree again and this time,
		// decode the encoded string
		int index = -1;
		while (index < (int)str.size() - 1) {
			decode(root, index, str);
		}
	}

    return root;
}