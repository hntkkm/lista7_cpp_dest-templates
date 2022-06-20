#include <iostream>
#include <string>
using namespace std;

template <class T>
class Tree{
public:

    struct drzewkoPojedyncze {
        T key;
        drzewkoPojedyncze* left;
        drzewkoPojedyncze* right;
    };
    drzewkoPojedyncze *korzen;

    Tree()
    {
        korzen = nullptr;
        cout<<"kontruktor"<<endl;
    }
    ~Tree()
    {
        korzen = deleteAll(korzen);
        cout<< "destruktor"<<endl;
    }
    drzewkoPojedyncze* insert(T addKey, drzewkoPojedyncze* drzewko);
    string draw(drzewkoPojedyncze* drzewko);
    string search(T x, drzewkoPojedyncze* drzewko);
    drzewkoPojedyncze* findMin(drzewkoPojedyncze* drzewko);
    drzewkoPojedyncze* remove(T remoweKey, drzewkoPojedyncze* drzewko);
    drzewkoPojedyncze* deleteAll(drzewkoPojedyncze* drzewko);
};


template<class T>
typename Tree<T>::drzewkoPojedyncze *Tree<T>::insert(T addKey, Tree::drzewkoPojedyncze *drzewko) {
    if(drzewko == nullptr)
    {
        drzewko = new drzewkoPojedyncze;
        drzewko->key = addKey;
        drzewko->left = drzewko->right = nullptr;
    }
    else if(addKey < drzewko->key)
        drzewko->left = insert(addKey, drzewko->left);
    else if(addKey > drzewko->key)
        drzewko->right = insert(addKey, drzewko->right);
    return drzewko;
}

template<class T>
string Tree<T>::draw(Tree::drzewkoPojedyncze *drzewko) {
    if(drzewko == nullptr)
        return "()";
    return "(" + to_string(drzewko->key) + ":" + draw(drzewko->left) + ":" + draw(drzewko->right) + ")";
    // to_string nie dziala dla string
}

template<class T>
string Tree<T>::search(T x, Tree::drzewkoPojedyncze *drzewko) {
    if(drzewko == nullptr)
        return "Nie ma elementu: " + to_string(x) ;
    else if(x < drzewko->key)
        return search(x, drzewko->left);
    else if(x > drzewko->key)
        return search(x, drzewko->right);
    else
        return "Jest element: " + to_string(x);
}

template<class T>
typename Tree<T>::drzewkoPojedyncze *Tree<T>::findMin(Tree::drzewkoPojedyncze *drzewko) {
    if(drzewko == nullptr)
        return nullptr;
    else if(drzewko->left == nullptr)
        return drzewko;
    return findMin(drzewko->left);
}

template<class T>
typename Tree<T>::drzewkoPojedyncze *Tree<T>::remove(T remoweKey, Tree::drzewkoPojedyncze *drzewko) {
    drzewkoPojedyncze* tempDrzewko;
    if(drzewko == nullptr)
        return nullptr;

        //szukamy element do usuniecia
    else if(remoweKey < drzewko->key)
        drzewko->left = remove(remoweKey, drzewko->left);
    else if(remoweKey > drzewko->key)
        drzewko->right = remove(remoweKey, drzewko->right);

        //usuniecie
    else if(drzewko->left && drzewko->right)
    {
        tempDrzewko = findMin(drzewko->right);
        drzewko->key = tempDrzewko->key;
        drzewko->right = remove(drzewko->key, drzewko->right);
    }
    else
    {
        tempDrzewko = drzewko;
        if(drzewko->left == nullptr)
            drzewko = drzewko->right;
        else if(drzewko->right == nullptr)
            drzewko = drzewko->left;
        delete tempDrzewko;
    }
    return drzewko;
}

template<class T>
typename Tree<T>::drzewkoPojedyncze *Tree<T>::deleteAll(Tree::drzewkoPojedyncze *drzewko) {
    if(drzewko == nullptr)
        return nullptr;
    else {
        deleteAll(drzewko->left);
        deleteAll(drzewko->right);
        delete drzewko;
    }
    return nullptr;
}

int main()
{
    Tree<int> root;
    root.korzen = root.remove(5, root.korzen);
    cout << root.draw(root.korzen) << endl;
    root.korzen = root.insert(10, root.korzen);
    root.korzen = root.insert(8, root.korzen);
    root.korzen = root.insert(9, root.korzen);
    root.korzen = root.insert(20, root.korzen);
    root.korzen = root.insert(15, root.korzen);
    root.korzen = root.insert(25, root.korzen);
    root.korzen = root.insert(12, root.korzen);
    cout << root.draw(root.korzen) << endl;
    root.korzen = root.remove(20, root.korzen);
    cout << root.draw(root.korzen) << endl;
    root.korzen = root.remove(10, root.korzen);
    cout << root.draw(root.korzen) << endl;
    root.korzen = root.insert(10,root.korzen);
    cout << root.search(6, root.korzen) << endl;
    cout << root.search(9, root.korzen) << endl;

//todo header
    return 0;
}