#include "huffman.h"
#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include<bitset>
#include <unordered_map>
using namespace std;

#define EMPTY_STRING ""

// Implementación de las funciones de la clase Huffman

 // Función para guardar el árbol de Huffman en un archivo binario
    void Huffman::guardarArbolHuffman(Node* root, const std::string& nombre_archivo) {
        std::ofstream archivo(nombre_archivo, std::ios::binary);

        if (!archivo.is_open()) {
            std::cout << "Error al abrir el archivo." << std::endl;
            return;
        }

        guardarArbolEnArchivo(root, archivo);
        archivo.close();
    }

// Función recursiva para guardar la estructura del árbol en el archivo
    void Huffman::guardarArbolEnArchivo(Node* root, std::ofstream& archivo) {
        if (root == nullptr) {
            archivo << '0'; // Indicador de nodo nulo
            return;
        }

        archivo << '1'; // Indicador de nodo válido
        archivo.write(reinterpret_cast<char*>(&root->ch), sizeof(root->ch));
        archivo.write(reinterpret_cast<char*>(&root->freq), sizeof(root->freq));

        guardarArbolEnArchivo(root->left, archivo);
        guardarArbolEnArchivo(root->right, archivo);
    }







// Función para cargar el árbol de Huffman desde un archivo binario
    Node* Huffman::cargarArbolHuffman(const std::string& nombre_archivo) {
        std::ifstream archivo(nombre_archivo, std::ios::binary);
        if (!archivo.is_open()) {
            std::cout << "Error al abrir el archivo." << std::endl;
            return nullptr;
        }

        char indicator;
        archivo >> indicator;

        Node* root = nullptr;
        if (indicator == '1') {
            char ch;
            int freq;
            archivo.read(reinterpret_cast<char*>(&ch), sizeof(ch));
            archivo.read(reinterpret_cast<char*>(&freq), sizeof(freq));

            root = new Node();
            root->ch = ch;
            root->freq = freq;
            root->left = cargarArbolDesdeArchivo(archivo);
            root->right = cargarArbolDesdeArchivo(archivo);
        }

        archivo.close();
        return root;
    }

    // Función recursiva para cargar la estructura del árbol desde el archivo
    Node* Huffman::cargarArbolDesdeArchivo(std::ifstream& archivo) {
        char indicator;
        archivo >> indicator;

        if (indicator == '0') {
            return nullptr;
        }

        char ch;
        int freq;
        archivo.read(reinterpret_cast<char*>(&ch), sizeof(ch));
        archivo.read(reinterpret_cast<char*>(&freq), sizeof(freq));

        Node* root = new Node();
        root->ch = ch;
        root->freq = freq;
        root->left = cargarArbolDesdeArchivo(archivo);
        root->right = cargarArbolDesdeArchivo(archivo);

        return root;
    }





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

// Traverse the Huffman Tree and decodificacion the encoded string
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

// Construye el árbol de Huffman y decodifica el texto de entrada dado
Node* Huffman::buildHuffmanTree(const std::string& text) {

    // Caso base: cadena vacía
    if (text == EMPTY_STRING) {
        return nullptr;
    }

    // Contar la frecuencia de aparición de cada carácter
    // y almacenarla en un mapa
    std::unordered_map<char, int> freq;
    for (char ch: text) {
        freq[ch]++;
    }

    // Crear una cola de prioridad para almacenar los nodos del árbol de Huffman
    std::priority_queue<Node*, std::vector<Node*>, comp> pq;

    // Crear un nodo hoja para cada carácter y añadirlo
    // a la cola de prioridad.
    for (auto pair: freq) {
        pq.push(getNode(pair.first, pair.second, nullptr, nullptr));
    }

    // Hacer mientras haya más de un nodo en la cola
    while (pq.size() != 1) {
        Node* left = pq.top(); pq.pop();
        Node* right = pq.top(); pq.pop();
        int sum = left->freq + right->freq;
        pq.push(getNode('\0', sum, left, right));
    }

    // `root` almacena un puntero a la raíz del árbol de Huffman
    Node* root = pq.top();

    // Recorrer el árbol de Huffman y almacenar los códigos Huffman
    // en un mapa. Además, mostrarlos
    std::unordered_map<char, std::string> huffmanCode;
    encode(root, EMPTY_STRING, huffmanCode);

    std::cout << "Los códigos Huffman son:\n" << std::endl;
    for (auto pair: huffmanCode) {
        std::cout << pair.first << " " << pair.second << std::endl;
    }

    std::cout << "\nLa cadena original es:\n" << text << std::endl;

    // Imprimir la cadena codificada
    std::string str;
    for (char ch: text) {
        str += huffmanCode[ch];
    }

    // Guardar la cadena codificada en un archivo binario
    std::ofstream outputFile("partida_comprimido.bin", std::ios::binary);
    if (!outputFile.is_open()) {
        std::cout << "No se pudo abrir el archivo de salida" << std::endl;
        return nullptr;
    }

    std::bitset<8> buffer;
    int bitIndex = 0;
    for (char bit : str) {
        if (bit == '1') {
            buffer.set(7 - bitIndex);
        }

        bitIndex++;
        if (bitIndex == 8) {
            outputFile << static_cast<unsigned char>(buffer.to_ulong());
            buffer.reset();
            bitIndex = 0;
        }
    }

    // Escribir el último byte si hay bits restantes en el buffer
    if (bitIndex > 0) {
        outputFile << static_cast<unsigned char>(buffer.to_ulong());
    }

    outputFile.close();

    std::cout << "\nLa cadena codificada es:\n" << str << std::endl;
    std::cout << "\nLa cadena decodificada es:\n";

    if (isLeaf(root)) {
        // Caso especial: para entradas como a, aa, aaa, etc.
        while (root->freq--) {
            std::cout << root->ch;
        }
    } else {
        // Recorrer el árbol de Huffman nuevamente y esta vez,
        // decodificar la cadena codificada
        int index = -1;
        while (index < (int)str.size() - 1) {
            decode(root, index, str);
        }
    }
    
    return root;
}
    // Función para decodificar la información del archivo comprimido usando el árbol existente
    void Huffman::inicializar(const std::string& nombre_archivo) {
        // Lectura del archivo comprimido
        std::ifstream inputFile(nombre_archivo, std::ios::binary);
        if (!inputFile.is_open()) {
            std::cout << "No se pudo abrir el archivo comprimido." << std::endl;
            return;
        }

        // Leer el contenido del archivo comprimido en una cadena
        std::string str((std::istreambuf_iterator<char>(inputFile)), std::istreambuf_iterator<char>());
        inputFile.close();

        // Decodificar la información del archivo comprimido usando el árbol existente
        std::cout << "\nLa informacion decodificada es:\n";
        if (isLeaf(root)) {
            while (root->freq--) {
                std::cout << root->ch;
            }
        } else {
            int index = -1;
            while (index < (int)str.size() - 1) {
                decode(root, index, str);
            }
        }
    }
