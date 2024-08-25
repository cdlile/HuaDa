// HuaDa.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
/*
已知有一系列的代表文件路径的字符串, 例如, "/home/z6/src/tech.cpp", "/home/sle/include/tech.h", "/bin/make/makefile", etc.
现需要按如下格式输出这种目录层次，请设计一种的数据结构来存储这种目录层次，要求输出时，访问效率尽量可能的高。
Hierarchy id    file or directory      parent directory
0               /                      (NULL)
1               home                 /
1               bin                    /
2               z6                    home
2               sle                   home
2               make               bin
3               src                   z6
3               include            sle
3               makefile          make
4               tech.cpp          src
4               tech.h              include

*/

#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>
#include <map>

using namespace std;

class Node
{
public:
	Node(std::string name , int index);
	~Node();

//private:
	int nIndex;
	std::string strName;
	Node* pPararent;
	std::map<std::string, Node*> mapChildren;

};

Node::Node(std::string name, int index)
{
	nIndex = index;
	strName = name;
	pPararent = NULL;
	std::cout << "creat  node index =[" << nIndex << "] name= [" << strName << "] ,this" <<this<<std::endl;
}

Node::~Node()
{
	std::cout << "destory  node index =[" << nIndex << "] name= [" << strName << "],this" << this << std::endl;
}


class PathTree
{
public:
	PathTree();
	~PathTree();
public:
	void AddPathNode(std::string strPath);
	Node * FindNode(std::string name ,int index);
	void PrintTree(Node *pRoot);
	Node *pRoot;
private:
	int nCountDeep;
	

};

PathTree::PathTree()
{
	nCountDeep = 0;
	pRoot = new Node("NULL" , 0);
}

PathTree::~PathTree()
{
	//删除所有Nodes申请的内存
}

void PathTree::AddPathNode(std::string strPath)
{
	//解析路径
	//strPath ="/home/z6/src/tech.cpp"
	std::vector<std::string> subPath;
	int pos1 = 0;
	int pos2 = 0;
	while (strPath.find("/") != std::string::npos)
	{
		pos1 = strPath.find("/" , pos1);
		pos2= strPath.find("/" ,pos1+1);
		if (pos1 != std::string::npos && pos2 != std::string::npos)
		{
			pos1++;
			std::string temp = strPath.substr(pos1, pos2 - pos1);
			subPath.push_back(temp);
			
		}
		else if (pos1 != std::string::npos && pos2 == std::string::npos)
		{
			std::string temp = strPath.substr(pos1 +1, strPath.length() -pos1 -1);
			subPath.push_back(temp);
			break;
		}
	}
	std::cout << subPath.size()<<std::endl;
	//先查找改路径name和深度是否存在
	Node* current = pRoot;
	for (int i = 0 ;i < subPath.size();i++)
	{
		std::string name = subPath[i];
		int deep = i + 1;
		if (current->mapChildren.find(name) != current->mapChildren.end())
		{
			//说明该节点已经存在,需要对下面一层比较
			current = current->mapChildren[name];
		}
		else//说明需要新建节点
		{
			Node * newNode = new Node(name ,deep);
			newNode->pPararent = current;
			current->mapChildren[name] = newNode;
			current = newNode;
		}
			
	}
	

}

Node * PathTree::FindNode(std::string name, int index)
{
	if (nCountDeep == 0)//说明还没有子节点
	{
		return NULL;
	}
}

void PathTree::PrintTree(Node *pRoot)
{
	Node *pCurent = pRoot;
	if (!pCurent){return;}
	std::cout <<"********"<< pCurent->nIndex<< "   "<< pCurent->strName << "   ";
	if (pCurent->pPararent == NULL)
	{
		std::cout <<"NULL" << "   "<<endl;
	}
	else
	{
		std::cout << pCurent->pPararent->strName << endl;
	}
		std::map<std::string, Node*>::iterator it = pCurent->mapChildren.begin();
		for ( ;it!= pCurent->mapChildren.end();it++)
		{
			std::string name = it->second->strName;
			std::cout << name << "  " << it->second->nIndex << endl;
			Node *p = it->second->mapChildren[name];
			PrintTree(p);
	}
}
/*
class TrieNode {
public:
	string strName;
	TrieNode* pParent = NULL;
	map<string, TrieNode*> children;
	int id;
	TrieNode(string name, int id); 
};

TrieNode::TrieNode(string name, int id)
:name(name), id(id) 
{
	name = name;
	children.clear();
}

class FileHierarchyTrie {
private:
	TrieNode* root;
	int idCounter = 0;

public:
	FileHierarchyTrie() : root(new TrieNode("/", 0)) {}

	void insert(const string& path) {
		TrieNode* current = root;
		vector<string> parts;

		// Split path into parts
		size_t prev = 0, pos;
		while ((pos = path.find('/', prev)) != string::npos) {
			parts.push_back(path.substr(prev, pos - prev));
			prev = pos + 1;
		}
		parts.push_back(path.substr(prev)); // Last part

											// Insert each part into the Trie
		for (const string& part : parts) {
			if (current->children.find(part) == current->children.end()) {
				TrieNode* newNode = new TrieNode(part, ++idCounter);
				newNode->parent = current;
				current->children[part] = newNode;
			}
			current = current->children[part];
		}
	}

	void printHierarchy(TrieNode* node, int depth = 0) {
		if (!node) return;

		// Adjust depth and parent display based on the root
		string parentDisplay = depth == 0 ? "(NULL)" : node->parent->name;

		// Print current node info
		cout << setw(depth) << "" << node->id << " " << node->name << " " << parentDisplay << endl;

		// Recursively print children
		for (auto& child : node->children) {
			printHierarchy(child.second, depth + 1);
		}
	}

	&#126;FileHierarchyTrie() {
		// Implement destructor to delete allocated nodes (omitted for brevity)
	}
};
*/
int main() {
	PathTree trie;
	trie.AddPathNode("/home/z6/src/tech.cpp");
 	trie.AddPathNode("/home/sle/include/tech.h");
 	trie.AddPathNode("/bin/make/makefile");
// 
 	trie.PrintTree(trie.pRoot);

	return 0;
}
