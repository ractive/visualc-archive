// BinaryTree.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


#include <iostream>
#include <sstream>
#include <iomanip>
#include <boost/shared_ptr.hpp>
#include <boost/bind.hpp>
#include <deque>
#include <stack>

using namespace std;

namespace {

template<typename T>
class Equals : public unary_function<T, bool>
{
public:
	Equals(const T &v) : m_value(v) {}

	bool operator()(const T &v) const {
		return m_value == v;	
	}
private:
	const T &m_value;
};

template<typename T>
Equals<T> isEqualTo(const T& v) {
	return Equals<T>(v);
}

} // anonymous namespace

template<typename T>
struct PrintWrapper;

template<typename T>
class BinaryTree
{
public:
	struct Node {
		typedef boost::shared_ptr<Node> Ptr;
		Node(const T &v) : value(v) { }
		Ptr left;
		Ptr right;
		Ptr parent;
		T value;
	};

	typedef typename Node::Ptr NodePtr;
	bool empty() const {
		return m_root == 0;
	}

	NodePtr insertSorted(const T &value) {
		if (empty()) {
			return setNode(m_root, NodePtr(), value);
		}
		return insertSorted(NodePtr(), m_root, value);
	}

	template<typename Func>
	void traversePostorder(Func f) const {
		int level = 0;
		traversePostorder(m_root, level + 1, f);
	}

	template<typename Func>
	void traverseInorder(Func f) const {
		int level = 0;
		traverseInorder(m_root, level + 1, f);
	}

	template<typename Pred>
	NodePtr findDfsIf(Pred pred) const {
		if (empty()) return NodePtr();
		return findDfsIf(m_root, pred);
	}

	template<typename Pred>
	NodePtr findDfsIfX(Pred pred) const {
		if (empty()) return NodePtr();
		stack<NodePtr> to_visit;
		to_visit.push(m_root);
		while(!to_visit.empty()) {
			NodePtr node = to_visit.top();
			to_visit.pop();
		
			cout << "testing " << node->value << "\n";	
			if (pred(node->value)) {
				cout << "!!! found " << node->value << "\n";	
				return node;
			}
			cout << node->value << " != \n";	

			if (node->right) {
				cout << "pushing " << node->right->value << "\n";	
				to_visit.push(node->right);
			}
			if (node->left) {
				cout << "pushing " << node->left->value << "\n";	
				to_visit.push(node->left);
			}
		}
		return NodePtr();
	}

	template<typename Pred>
	NodePtr findBfsIf(Pred pred) const {
		if (empty()) return NodePtr();	
		deque<NodePtr> to_visit;
		to_visit.push_back(m_root);

		while(!to_visit.empty()) {
			NodePtr node = to_visit.front();
			to_visit.pop_front();
			if (pred(node->value)) {
				return node;
			}

			if (node->left) {
				to_visit.push_back(node->left);
			}
			if (node->right) {
				to_visit.push_back(node->right);
			}

		}

		return NodePtr();
	}
	
	NodePtr findBfs(const T &value) const {
		return findBfsIf(isEqualTo(value));
	}

	NodePtr findDfs(const T &value) const {
		return findDfsIf(isEqualTo(value));
	}

	size_t size() const {
		if (empty()) return 0;
		return size(m_root, 1);
	}

	bool isBalanced() const {
		return balanced(m_root) == 0;
	}

	void createBackbone() {
		NodePtr node = m_root;
		while(node) {
			if (node->left) {
				rotateRight(node);
				node = node->parent;
			}
			else {
				node = node->right;
			}
		}
	}

	void reBalance() {
		createBackbone();
		size_t n = size() - 1;
		for (size_t m = n / 2; m > 0; m = n / 2) {
			NodePtr node = m_root;
			for(size_t i = 0; i < m; ++i) {
				node = rotateLeft(node)->right;
			}
			n = n - m - 1;
		}	
	}

private:

	NodePtr rotateRight(NodePtr old_top) {
		if (!old_top->left) return NodePtr();

		NodePtr new_top = old_top->left;
		NodePtr tmp = new_top->right;
		NodePtr current_parent = old_top->parent;

		old_top->parent = new_top;
		new_top->parent = current_parent;
		new_top->right = old_top;
		old_top->left = tmp;
		if (current_parent) {
			if (current_parent->right == old_top) {
				current_parent->right = new_top;
			}
			else {
				current_parent->left = new_top;
			}
		}

		if (old_top == m_root) {
			m_root = new_top;
		}

		return new_top;
	}

	NodePtr rotateLeft(NodePtr old_top) {
		if (!old_top->right) return NodePtr();

		NodePtr new_top = old_top->right;
		NodePtr tmp = new_top->left;
		NodePtr current_parent = old_top->parent;

		old_top->parent = new_top;
		new_top->parent = current_parent;
		new_top->left = old_top;
		old_top->right = tmp;
		if (current_parent) {
			if (current_parent->right == old_top) {
				current_parent->right = new_top;
			}
			else {
				current_parent->left = new_top;
			}
		}

		if (old_top == m_root) {
			m_root = new_top;
		}

		return new_top;
	}

	/**
	 * @return <1 if height of left is >, > 1 if height right > 0,
	 *         0 if the tree is balanced
	 */
	int balanced(NodePtr node) const {
		int diff = static_cast<int>(size(node->right, 0) - size(node->left, 0));
		return abs(diff) < 2 ? 0 : diff;

	}

	size_t size(NodePtr node, size_t c) const {
		if (!node) return c;

		if (node->left) {
			c = size(node->left, c + 1);
		}
		if (node->right) {
			c = size(node->right, c + 1);
		}
		return c;
	}


	template<typename Pred>
	NodePtr findDfsIf(NodePtr node, Pred pred) const {
		if (node == 0) return NodePtr();
		if (pred(node->value)) return node;

		NodePtr left = findDfsIf(node->left, pred);
		if(left) {
			return left;
		}
		NodePtr right = findDfsIf(node->right, pred);
		if(right) {
			return right;
		}

		return NodePtr();
	}

	template<typename Func>
	void traverseInorder(NodePtr node, int level, Func f) const {
		if (!node) {
		       	return;
		}

		traverseInorder(node->left, level + 1, f);
		f(node);
		traverseInorder(node->right, level + 1, f);
	}

	template<typename Func>
	void traversePostorder(NodePtr node, int level, Func f) const {
		if (!node) {
		       	return;
		}

		f(node, level);
		traversePostorder(node->left, level + 1, f);
		traversePostorder(node->right, level + 1, f);
	}

	NodePtr setNode(NodePtr &node, NodePtr parent, const T &value) {
		node.reset(new Node(value));
		node->parent = parent;
		return node;
	}


	NodePtr insertSorted(NodePtr parent, NodePtr node, const T &value) {
		if (node == 0) {
			cout << "node is null, creating one with value " << value << " and parent " << parent->value << "\n";
			return setNode(node, parent, value);
		}

		if (value <= node->value) {
			if (node->left == 0) {
				return setNode(node->left, node, value);
			}

			return insertSorted(node, node->left, value);
		}
		else {
			if (node->right == 0) {
				return setNode(node->right, node, value);
			}
			return insertSorted(node, node->right, value);
		}
	}

	ostream & printValue(ostream &os, NodePtr node) const {
		if (!node) {
			os << "<null>\n";
		}
		else {
			os << node->value;
		}

		return os;
	}

	NodePtr m_root;
};

template<typename T>
struct PrintWrapper {
public:
	typedef typename BinaryTree<T>::NodePtr NodePtr;
	PrintWrapper(NodePtr node) : m_node(node) {}
	const NodePtr &get() const { return m_node; };
private:
	NodePtr m_node;
};

template<typename T>
string valueOf(const T &node)
{
	if (!node) return "<0>";

	ostringstream oss;
	oss << node->value;
	return oss.str();
}

template<typename T>
ostream & operator<<(ostream &os, const PrintWrapper<T> &node) {
	if (!node.get()) {
		os << "<null>\n";
	}
	else {
		string left  =  valueOf(node.get()->left);
		string right =  valueOf(node.get()->right);
		string parent = valueOf(node.get()->parent);
	
		os << "value: " << setw(4)<< node.get()->value << ", left: " << setw(4)<< left
		   << ", right: " << setw(4)<< right << ", parent: " << setw(4)<< parent  << "\n";
	}

	return os;
}

template<typename NodePtr>
struct PrintNode {
	void operator()(NodePtr node, int level) const {
		cout << setw(level) << ' ' << node->value << " (" << valueOf(node->parent) << ")\n";
	}
	void operator()(NodePtr node) const {
		cout << node->value << "\n";
	}
};

void divider() {
	cout << "--------------------------------------------\n";
}

int main()
{
	typedef BinaryTree<int> IntTree;
	IntTree tree;
	tree.insertSorted(33);
	tree.insertSorted(3);
	tree.insertSorted(23);
	tree.insertSorted(25);
	tree.insertSorted(6);
	tree.insertSorted(1);
	tree.insertSorted(41);
	tree.insertSorted(35);
	tree.insertSorted(99);
	tree.insertSorted(60);
	tree.insertSorted(100);

	tree.traversePostorder(PrintNode<IntTree::NodePtr>());
	divider();
	tree.traverseInorder(PrintNode<IntTree::NodePtr>());
	divider();

	assert(tree.findBfs(41));
	assert(!tree.findBfs(42));

	IntTree::NodePtr f = tree.findBfsIf(boost::bind(greater<int>(), _1,  99));
	cout << f->value << " > 99\n";

	cout << "*************************\n";
	assert(tree.findDfs(41));
	assert(!tree.findDfs(42));

	f = tree.findDfsIf(boost::bind(greater<int>(), _1,  99));
	cout << f->value << " > 99\n";
	 
	cout << "*************************\n";
	cout << "size: " << tree.size() << "\n";
	cout << "balanced: " << tree.isBalanced() << "\n";
	cout << "*************************\n";
	tree.createBackbone();
	tree.traversePostorder(PrintNode<IntTree::NodePtr>());
	tree.reBalance();
	tree.traversePostorder(PrintNode<IntTree::NodePtr>());
	divider();

}
