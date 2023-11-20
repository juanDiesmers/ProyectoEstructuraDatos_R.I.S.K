#ifndef HUFFMAN_H
#define HUFFMAN_H

using namespace std;

#include <string>
#include <unordered_map>

// Estructura de nodo para el árbol Huffman
struct Node
{
    char ch;
    int freq;
    Node *left, *right;
};

// Comparison object to be used to order the heap
struct comp
{
    bool operator()(const Node* l, const Node* r) const
    {
        // the highest priority item has the lowest frequency
        return l->freq > r->freq;
    }
};

class Huffman {
public:
    Huffman(); // Constructor
    std::string compress(const std::string& text);

    // Declaración de la función isLeaf en la clase Huffman
    bool isLeaf(Node* node);
    Node* getNode(char ch, int freq, Node* left, Node* right);

    //funciones para guardar y leer la estructura del árbol
    void guardarArbolHuffman(Node* root, const std::string& nombre_archivo);
    void setRoot(Node* newRoot) { root = newRoot;}
    void decode(Node* root, int& index, string str);

    void inicializar(const std::string& nombre_archivo);
    Node* cargarArbolHuffman(const std::string& nombre_archivo);
    Node* getRoot() { return root; } // Agregar una función para obtener la raíz

private:
    Node* buildHuffmanTree(const std::string& text);
    void encode(Node* root, string str, unordered_map<char, string>& huffmanCode);
    
    void guardarArbolEnArchivo(Node* root, std::ofstream& archivo);
    Node* cargarArbolDesdeArchivo(std::ifstream& archivo);

    Node* root; // Raíz del árbol Huffman
};

#endif // HUFFMAN_H