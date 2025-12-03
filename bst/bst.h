#ifndef BST_H_
#define BST_H_

#include <string>
#include <sstream>

template <class T> class BST;

template <class T>
class TreeNode {
private:
	T value;
	TreeNode *left, *right;

public:
	TreeNode(T);
	void add(T);
	bool find(T) const;
	void preorder(std::stringstream&) const;
	void inorder(std::stringstream&) const;
	void postorder(std::stringstream&) const;
	int height() const;
	bool ancestors(std::stringstream&, T) const;
	int whatlevelamI(T, int) const;

	friend class BST<T>;
};

// ---------- Implementación TreeNode ----------

template <class T>
TreeNode<T>::TreeNode(T val) : value(val), left(0), right(0) {}

template <class T>
void TreeNode<T>::add(T val) {
	if (val < value) {
		if (left == 0)
			left = new TreeNode<T>(val);
		else
			left->add(val);
	} else if (val > value) {
		if (right == 0)
			right = new TreeNode<T>(val);
		else
			right->add(val);
	}
}

template <class T>
bool TreeNode<T>::find(T val) const {
	if (val == value)
		return true;
	else if (val < value)
		return (left != 0 && left->find(val));
	else
		return (right != 0 && right->find(val));
}

template <class T>
void TreeNode<T>::preorder(std::stringstream &aux) const {
	aux << value;
	if (left != 0) {
		aux << " ";
		left->preorder(aux);
	}
	if (right != 0) {
		aux << " ";
		right->preorder(aux);
	}
}

template <class T>
void TreeNode<T>::inorder(std::stringstream &aux) const {
	if (left != 0)
		left->inorder(aux);
	if (aux.tellp() > 1)
		aux << " ";
	aux << value;
	if (right != 0)
		right->inorder(aux);
}

template <class T>
void TreeNode<T>::postorder(std::stringstream &aux) const {
	if (left != 0)
		left->postorder(aux);
	if (right != 0)
		right->postorder(aux);
	if (aux.tellp() > 1)
		aux << " ";
	aux << value;
}

template <class T>
int TreeNode<T>::height() const {
    int leftHeight = 0;
    int rightHeight = 0;

    // Si hay subárbol izquierdo, obtenemos su altura
    if (left != 0) {
        leftHeight = left->height();
    }

    // Si hay subárbol derecho, obtenemos su altura
    if (right != 0) {
        rightHeight = right->height();
    }

    // Comparamos y sumamos 1 por el nivel actual
    if (leftHeight > rightHeight) {
        return leftHeight + 1;
    } else {
        return rightHeight + 1;
    }
}


template <class T>
bool TreeNode<T>::ancestors(std::stringstream &aux, T val) const {
	if (val == value) {
		return true; // encontramos el nodo, se detiene
	}

	if (val < value && left != 0) {
		aux << value << " ";            // imprimimos antes de ir a la izquierda
		if (left->ancestors(aux, val))  // si el valor está más abajo
			return true;
	}
	else if (val > value && right != 0) {
		aux << value << " ";            // imprimimos antes de ir a la derecha
		if (right->ancestors(aux, val))
			return true;
	}

	return false; // valor no encontrado en este subárbol
}

template <class T>
int TreeNode<T>::whatlevelamI(T val, int level) const {
	if (val == value) {
        return level;
    }
	if (val < value && left != 0){
		return left->whatlevelamI(val, level + 1);
    }
	if (val > value && right != 0){
		return right->whatlevelamI(val, level + 1);
    }
	return -1;
}

// ---------- Clase BST ----------

template <class T>
class BST {
private:
	TreeNode<T> *root;

	void deleteTree(TreeNode<T>*);
	void printLevel(TreeNode<T>*, int, std::stringstream&) const;

public:
	BST();
	~BST();
	bool empty() const;
	void add(T);
	std::string visit() const;
	int height() const;
	std::string ancestors(T) const;
	int whatlevelamI(T) const;
	void removeAll();
};

// ---------- Implementación BST ----------

template <class T>
BST<T>::BST() : root(0) {}

template <class T>
BST<T>::~BST() {
	removeAll();
}

template <class T>
bool BST<T>::empty() const {
	return (root == 0);
}

template <class T>
void BST<T>::add(T val) {
	if (root == 0)
		root = new TreeNode<T>(val);
	else if (!root->find(val))
		root->add(val);
}

template <class T>
void BST<T>::deleteTree(TreeNode<T>* node) {
	if (node == 0) return;
	deleteTree(node->left);
	deleteTree(node->right);
	delete node;
}

template <class T>
void BST<T>::removeAll() {
	deleteTree(root);
	root = 0;
}

template <class T>
void BST<T>::printLevel(TreeNode<T>* node, int level, std::stringstream &aux) const {
	if (node == 0) {
        return;
    }
	if (level == 1) {
		if (aux.tellp() > 1) {
            aux << " ";
        }
		aux << node->value;
	}
	else {
		printLevel(node->left, level - 1, aux);
		printLevel(node->right, level - 1, aux);
	}
}

template <class T>
std::string BST<T>::visit() const {
	std::stringstream preorder, inorder, postorder, levelorder;
	preorder << "[";
	inorder << "[";
	postorder << "[";
	levelorder << "[";

	if (!empty()) {
		root->preorder(preorder);
		root->inorder(inorder);
		root->postorder(postorder);

		int h = height();
		for (int i = 1; i <= h; i++){
			printLevel(root, i, levelorder);
        }
	}

	preorder << "]";
	inorder << "]";
	postorder << "]";
	levelorder << "]";

	std::stringstream res;
	res << preorder.str() << "\n"
	    << inorder.str() << "\n"
	    << postorder.str() << "\n"
	    << levelorder.str();
	return res.str();
}

template <class T>
int BST<T>::height() const {
	if (empty()) {
        return 0;
    }
	return root->height();
}

template <class T>
std::string BST<T>::ancestors(T val) const {
	std::stringstream aux;
    
	if (!empty() && root->find(val)) {
		root->ancestors(aux, val);
		std::string s = aux.str();
		if (!s.empty() && s.back() == ' ')
			s.pop_back(); // quitar espacio final
		aux.str("");     // limpiamos el stringstream
		aux << "[" << s << "]";
		return aux.str();
	}

	aux << "]";
	return aux.str();
}

template <class T>
int BST<T>::whatlevelamI(T val) const {
	if (empty()){ 
        return -1;
    }
	return root->whatlevelamI(val, 1);
}

#endif /* BST_H_ */
