
/* Ryan Hoover
 * CS 202 - Fant
 * 5/17/17
 * Program 3
 * logbook.cpp *
 * logbook.h function implementations */

#include "logbook.h"

/*********************************************************************/

// node default, null body
node::node(void):
    left(NULL), right(NULL)
{}
    //left = right = NULL;

// null body node app argument constructor
node::node(const app& copyFrom):
    app(copyFrom), left(NULL), right(NULL)
{}
    //left = copyFrom.left;
    //right = copyFrom.right;

// null body node constructor with full 6 data member arguments
node::node(char*nName,char*nType,char*nInfo,char*nDate,int nTime, int nUsage):
    app(nName,nType,nInfo,nDate,nTime,nUsage), left(NULL), right(NULL)
{}

// node destructor, set left and right to null ONLY to not bulldoze DS on removal
node::~node(void) {
    if (left)
        left = NULL;
    if (right)
        right = NULL;
}

//----------------------------------------------------------

// getter for node->left 
node*& node::goLeft(void) {
    return left;
}

//----------------------------------------------------------

// getter for node->right
node*& node::goRight(void) {
    return right;
}

//----------------------------------------------------------

//setter for node->left
void node::setLeft(node * setTo) {
    if (setTo)
        left = setTo;
    else left = NULL;
}

//----------------------------------------------------------

// setter for node->right
void node::setRight(node * setTo) {
    if (setTo)
        right = setTo;
    else right = NULL;
}

//----------------------------------------------------------

// check to see if ->left points to any data
bool node::ifLeft(void)const {
    if (left != NULL)
        return true;
    else return false;
}

//----------------------------------------------------------

// check to see if ->right points to any data
bool node::ifRight(void)const {
    if (right != NULL)
        return true;
    else return false;
}

/*********************************************************************/

// default constructor
logbook::logbook(void):
    root(NULL), totalUsage(0), appUsage(0), webUsage(0), utilUsage(0)
{
    (*this).fileIn();
   //     cout << "\nProgram data read in from external text file.\n";
    //else cout << "\nError - Program data NOT read in from external text file.\n";
}
    
//----------------------------------------------------------

// copy constructor, calls recursive copy function
logbook::logbook(const logbook& source) {
    copy(source);
    totalUsage = source.totalUsage;
    appUsage = source.appUsage;
    webUsage = source.webUsage;
    utilUsage = source.utilUsage;
}

//----------------------------------------------------------

// wrapper for recursive copy function
void logbook::copy(const logbook& source) {
    copy((*this).root, source.root);
}

//----------------------------------------------------------

void logbook::copy(node*& dest, node* source) {
    if (!source)
        dest = NULL;
    else {
        dest = new node(*source);
        copy(dest->goLeft(), source->goLeft());
        copy(dest->goRight(), source->goRight());
    }
    return;
}

//----------------------------------------------------------

logbook& logbook::operator = (const logbook& source) {
    if (this == &source)
        return (*this);
    (*this).removeAll();
    (*this).copy(source);
    return (*this);
}

//----------------------------------------------------------

// desctructor, writes to file
logbook::~logbook(void) {
    
    (*this).fileOut();
    //    cout << "\nData written to external file.\n";
    //else cout << "\nData not written to file.\n";
    removeAll();
    if (root) {
        delete root;
        root = NULL;
    }
}

//----------------------------------------------------------

/*
logbook logbook::operator + (const logbook& list1, const logbook& list2) {
    logbook temp(list1);
    if (!temp.root)
        temp = list2;
    else {
        node *

}
*/

//----------------------------------------------------------

logbook& logbook::operator += (const app& toAdd) {
    (*this).insert(toAdd);
    return (*this);
}


logbook& logbook::operator += (const node& toAdd) {
    (*this).insert(toAdd);
    return (*this);
}

//----------------------------------------------------------

// Wrapper for recursive function below
int logbook::insert(const app& toAdd) {
    int success = insert(root,toAdd);
    if (balanceAll(root))
        ++success;
    return success;
}

//----------------------------------------------------------

// Inserts based on strcmp bewteen the current root title and the obj title to be inserted
int logbook::insert(node*& root, const app& toAdd) {
    int success = 0;
    // creates a new node when we traverse out of bounds from the correct subtree
    if (!root) {
        // root to app copy constructors invoked
        root = new node(toAdd);
        //cout << "\nlogbook::insert\n";
        //cout << toAdd;
        ++success;
        ++totalUsage;
    }
    else {
        //if (toAdd.cmpLastName(root->getName()) < 0)
        if (root->sessionLen() > toAdd.sessionLen())
            success += insert(root->goLeft(),toAdd);
        else
            success += insert(root->goRight(), toAdd);
        /*
        else if (toAdd.cmpLastName(root->getName()) > 0)
        {
            success += insert(root->goRight(),toAdd);
        }
        else
        {
            cout << "\nDuplicate data not yet supported!";
            return success;
        }
        */
    }
    // recursive tree balance based after insertion
    //int counter = balanceAll(root);
    //cout << "\ncounter = " << counter << endl;
    return success;
}

//----------------------------------------------------------

// cout << is a wrapper for the display fucntion
ostream& operator << (ostream& output, const logbook& toDisplay) {
    //cout << "\nList class << operator\n";
    toDisplay.displayAll();
    //output << i;
    return output;
}

//----------------------------------------------------------

// Wrapper for recursive function below
int logbook::displayAll(void)const {
    cout << "\nNumber of entries: " << totalUsage << endl;
    int height = getHeight(root);
    int balance = balanceFactor(root);
    cout << "\nTree height = " << height << "\nBalance = " << balance << endl;
    return displayAll(root);
}

// Traverses left subtree, displays, traverses right subtree, Alphabetical order
int logbook::displayAll(node * root)const {
    if (!root) return 0;
    int success = 0;
    if (root->ifLeft()) {
        success += displayAll(root->goLeft());
    }
    //success += root->display();
    cout << (*root); //operator overloading is pretty cool
    ++success;
    if (root->ifRight()) {
        success += displayAll(root->goRight());
    }
    return success;
}

//----------------------------------------------------------

// tried to overload this but I couldnt figure out
//  how to return no match without a segFault (throw an exception?)
app& logbook::operator [] (char* keyword)const {
    /*
    app * found = root;
    if (!(*this).retrieve(keyword,(*found))) {
        app * temp = new app;
        return *temp;
    }
    */
    app * found = new app;
    if (!this->retrieve(keyword, (*found))) {
        //return (*this->root);
        //throw out_of_range("\nNo Match.\n");
        //app * temp = new app;
        //return (*temp);
        //exit(0);
        //cout << "\nNo Match\n";
        //return (*found); // freezes the program
        // HOW DO I RETURN FALSE IF SEARCH TERM DOESNT EXIST
        app * notFound = NULL;
        return (*notFound);
        
    }
    else return (*found);
}

// Wrapper for recursive function below
int logbook::retrieve(char* keyWord, app& found)const {
    return retrieve(root,keyWord,found);
}

// Pass in a poulated keyword app from main, and and empty app object to be filled by app::retrieve
int logbook::retrieve(node* root, char * keyWord, app& found)const {
    if (!root) return 0;
    int success = 0;
    // app::retrieve returns 1 if it matches & populates empty found obj
    success = root->retrieve(keyWord,found);
    if (success) {
        cout << "\nNew program usage, 1 added to lifetime total.\n";
        // Increment usage for the two programs
        ++found;
        ++(*root);
    }
    success += retrieve(root->goLeft(),keyWord,found);
    success += retrieve(root->goRight(),keyWord,found);
    return success;
}

//----------------------------------------------------------

// public wrapper for recursive getHeight
int logbook::getHeight(void)const {
    return getHeight(root);
}

// traverse down current node subtrees to determine height
int logbook::getHeight(node * root)const {
    if (!root) return 0;
    // populate ints
    int leftHeight = getHeight(root->goLeft()); // how many levels on the left side?
    int rightHeight = getHeight(root->goRight()); // how many levels on the right side?
    int height = max(leftHeight, rightHeight)+1;// take the largest of the two +1 to count current level
    return height;
}

//----------------------------------------------------------

// public wrapper for non-recursive private (node* arg)
int logbook::balanceFactor(void)const {
    return balanceFactor(root);
}

/* This fucntion may or may not need the node argument at all... TBD 
 * when i get further with the balancing implementations,
 * I'll see whats up with this when i use it */

// determine balance of tree using height calc
int logbook::balanceFactor(node * root)const {
    if (!root)
        return 0;
    int balance = 0;
    // height of left tree stored in int balance
    balance += getHeight(root->goLeft());
    // balance = left - right
    balance -= getHeight(root->goRight());
    // (0) balanced, (+0) left heavy, (-0) right heavy
    return balance;
}

//----------------------------------------------------------

// called after insertion function to recursively traverse and balance subtrees
int logbook::balanceAll(node*& root)const {
    if (!root)
        return 0;
    int counter = 0;
    // Pre-work recursive calls to balance from the bottom up
    counter += balanceAll(root->goLeft()) + balanceAll(root->goRight());
    // get balance factor of current root, to determine rotation(s)
    int balance = balanceFactor(root);
    // Left-heavy
    if (balance >= 2) {
        int leftBal = balanceFactor(root->goLeft());
        // Left heavy on Left subtree
        if (leftBal >= 1)
            counter += rotateSingleLeft(root);
        // Right-heavy on Left subtree
        else
            counter += rotateDoubleLeft(root);
    }
    // Right heavy
    else if (balance <= -2) {
        int rightBal = balanceFactor(root->goRight());
        // Right heavy on Right subtree
        if (rightBal <= -1)
            counter += rotateSingleRight(root);
        // Left heavy on Right subtree
        else
            counter += rotateDoubleRight(root);
    }
    //accumulated for overall count of rebalances executed
    return counter;
}

//----------------------------------------------------------

// Left subtree, right heavy
int logbook::rotateDoubleLeft(node*& root)const {
    if (!root)
        return 0;
    node * oldRoot = root;  // current root will be moved
    node * hold = oldRoot->goLeft();    // hold root's Left subtree
    node * newRoot = hold->goRight();   // newRoot will be the next largest before oldRoot
    // adopt newRoot's right child as left, will always be smaller
    oldRoot->setLeft(newRoot->goRight());
    // adopt newRoot's left child as right, will be greater than hold 
    hold->setRight(newRoot->goLeft());
    // newRoot is larger than its former parent
    newRoot->setLeft(hold);
    // the oldRoot is larger than the newRoot
    newRoot->setRight(oldRoot); //newRoot->right = oldRoot
    // assign our parent to point to this as its new child
    root = newRoot;
    // rotation complete, return 1
    return 1; 
}

//----------------------------------------------------------

// Left subtree, left heavy
int logbook::rotateSingleLeft(node*& root)const {
    if (!root)
        return 0;
    node * oldRoot = root;  // current root will be swapped
    node * newRoot = oldRoot->goLeft(); // pre-order successor
    // adopt newRoots fromer right child, will be smaller than current root
    oldRoot->setLeft(newRoot->goRight());
    // oldRoot is larger than its former child
    newRoot->setRight(oldRoot);
    root = newRoot; // update root, completing rotation
    return 1;
}

//----------------------------------------------------------

// Right subtree, left heavy
int logbook::rotateDoubleRight(node*& root)const {
    if (!root)
        return 0;
    node * oldRoot = root;  //current root will be moved 
    node * hold = oldRoot->goRight();   // hold root's right subtree
    node * newRoot = hold->goLeft();    // hold's smaller subtree
    oldRoot->setRight(newRoot->goLeft());   // adopt new root's smaller tree
    hold->setLeft(newRoot->goRight());  // adopt newRoot's larger tree
    newRoot->setRight(hold);    // adopt parent as larger subtree
    newRoot->setLeft(oldRoot);  // adopt old root as smaller subtree
    root = newRoot;
    return 1;
}

//----------------------------------------------------------

// Right subtree, right heavy
int logbook::rotateSingleRight(node*& root)const {
    if (!root)
        return 0;
    node * oldRoot = root; // 
    node * newRoot = oldRoot->goRight();
    oldRoot->setRight(newRoot->goLeft());
    newRoot->setLeft(oldRoot);
    root = newRoot;
    return 1;
}

//----------------------------------------------------------

// Wrapper for recursive function below
int logbook::removeAll(void) {
    int success = 0;
    success = removeAll(root);
    return success;
}

//Explicit destructor, clears entire logbook of all data,
//resets logbook::totalUsage to 0
int logbook::removeAll(node * & root) {
    if (!root)
        return 0;
    int success = 0;
    success += removeAll(root->goLeft());
    success += removeAll(root->goRight());
    delete root;
    root = NULL;
    if (!root) {
        ++success;
        --totalUsage;
    }
    return success;
}

//----------------------------------------------------------

// Creates and then deletes a temp node ptr to take in obj data from file
int logbook::fileIn(void) {
    int success, nLen, nUsage;
    success = nLen = nUsage = 0;
    char nName[NAME], nType[NAME], nInfo[INFO], nDate[DATE];
    ifstream fin;
    app * temp = new app;
    fin.open("usage.txt");
    if (fin){
        ++success;
        fin.get(nName, NAME, ':'); fin.ignore(NAME, ':');
        while (fin && !fin.eof())
        {
            fin.get(nType, NAME, ':'); fin.ignore(NAME, ':');
            fin.get(nInfo, INFO, ':'); fin.ignore(INFO, ':');
            
            fin.get(nDate,DATE,'\n'); fin.ignore(DATE,':');
            fin >> nLen; fin.ignore(SIZE, ':');
            fin >> nUsage; fin.ignore(SIZE,'\n');
            // Uses logbook fucntions for insertion
            temp->create(nName,nType,nInfo,nDate,nLen,nUsage); 
            insert(*temp);
                    //cout << "\nData not properly read in from file.\n";
                //(*this) += temp;
            fin.get(nName, NAME, ':'); fin.ignore(NAME, ':');
        }
        fin.clear();
        fin.close();
        if (temp) {
            delete temp;
            temp = NULL;
        }
    }
    return success;
}


//----------------------------------------------------------

// Wrapper for recursive function below, keeps the file open and passes fout by ref
int logbook::fileOut(void) {
    // fout passed by ref to recursive func & app write func
    ofstream fout;
    fout.open("usage.txt");
    // recursive call
    int success = fileOut(root,fout);
    // clear ostream after recrusive write to file
    if (fout) {
        fout.clear();
        fout.close();
    }
    return success;
}

//----------------------------------------------------------

// Takes &fout obj and passes it to app class write file for the private data members
int logbook::fileOut(node* root, ofstream& fout) {
    if (!root) return 0;
    int success = 0;
    if (fout && !fout.eof()) {
        // app::fileOut returns 1 for each successful write
        success = root->fileOut(fout);
        // pre-order writing
        success += fileOut(root->goLeft(),fout);
        success += fileOut(root->goRight(),fout);
    }
    return success;
}

//----------------------------------------------------------


/*
// Individual delete not required for a balanced tree
//----------------------------------------------------------

// Wrapper for recursive function below
int logbook::removeMatch(char * keyWord)
{
    return removeMatch(root, keyWord);
}

// Finds a title based on a keyWord argument, passed in by client
int logbook::removeMatch(node * & root, char * keyWord)
{
    if (!root)
    {
        return 0;
    }
    int counter = 0;
    //int success = 0;
    // Compare private data members
    if (!root->cmpName(keyWord))
    {
        // If match, look for one of 4(5) sub cases
        // Node is a leaf
        if (!root->isLeft() && !root->isRight())
        {
            cout << "\nRemoval, condition 1 met.\n";
            delete root;
            root = NULL;
            ++counter;
            --totalUsage;
        }
        // Root has a left subtree ONLY
        else if (!root->isRight() && root->isLeft())
        {
            cout << "\nRemoval, condition 2 met.\n";
            node * temp = root->goLeft();
            delete root;
            root = temp;
            ++counter;
            --totalUsage;
            return -1;
        }
        // Root has a right subtree ONLY
        else if (!root->isLeft() && root->isRight())
        {
            cout << "\nRemoval, condition 3 met.\n";
            node * temp = root->goRight();
            delete root;
            root = temp;
            ++counter;
            --totalUsage;
            return -1;
        }
        // Root has two subtrees
        else if (root->isLeft() && root->isRight())
        {
            // Find the in-order-successor and reassign root->data
            node * temp = root->goRight();
            // If the right subtree of Root doesn't have a Left subtree
            if (!temp->isLeft())
            {
                cout << "\nRemoval, condition 4.1 met.\n";
                //root->copy(temp);
                root = temp;
                root->setRight(temp->goRight());
                // cleared root, moved successor's data to root, now temp is a duplicate
                delete temp;
                temp = NULL;
                ++counter;
                --totalUsage;
            }
            else
            {
                cout << "\nRemoval, condition 4.2 met.\n";
                // If right subtree has two subtrees, find the successor down the left subtree
                node * current = temp;
                node * previous = NULL;
                while (current->goLeft())
                {
                    previous = current;
                    current = current->goLeft();
                }
                previous->connectLeft(current->goRight());
                root->copyContact(current);
                delete current;
                current = NULL;
                ++counter;
                --totalUsage;
            } 
        } 
    } // if (root->data.cmpChar(keyWord) == 0)
    else
    {
        if (root->cmpName(keyWord) > 0)
        {
            counter = removeMatch(root->goLeft(), keyWord);
        }
        else
        {
            counter = removeMatch(root->goRight(), keyWord);
        }
    }
    return counter;
}
*/

//----------------------------------------------------------

