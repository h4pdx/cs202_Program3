
/* Ryan Hoover - 3/10/17
 * CS163 - K. Fant
 * PROGRAM 4 
 * logbook.cpp */

/* AVL Tree implementations.
 * Recursive Calls kept in private section, public wrappers used for implemenation
 * Stores node object data (app class) in bst logbook
 * Search, Remove, Insert, Display ,and efficiency report
 * - 7 functions related to the balancing of the tree
 *  + getHeight to determine height, balanceFactor to determine balance factor,
 *  + balanceAll to determine which action to take based on balance factor
 *  + 4 rotate functions for Left heavy (right or left) and right heavy (right or left)
 *  Several online resources used for inspriation for AVL model
 *  - all listed in write-up
 * overloaded operators are used for insertion and display 
 * Node is derived from app data class,
 * with added pointers for organization by logbook into a balanced tree */


#ifndef _LOGBOOK_H_
#define _LOGBOOK_H_
#include "app.h"

/*********************************************************************/

class node: public app {
    public:
        node(void);
        node(const app & copyFrom); // trigger app copy constructor
        node(char* nName,char* nType,char* nInfo,char* usageDate,int nTime, int nUsage);
        ~node(void);
        node*& goLeft(void);        // go node->left
        node*& goRight(void);       // go node->right
        void setLeft(node* setTo);  // node->left = setTo
        void setRight(node* setTo); // node->right = setTo
        bool ifLeft(void)const;     // if left != NULL
        bool ifRight(void)const;    // if right != NULL
    private:
        node * left;
        node * right;
};

/*********************************************************************/

// appHistory in main, used as data structure for app usage history
class logbook {
    public:
        logbook(void);        // Read in from external file
        logbook(const logbook& copyFrom);
        ~logbook(void);       // Save to external file
        int insert(const app& toAdd);       // Client program enters new data
        void copy(const logbook& source);
        int removeMatch(char* keyWord);    // Search and delete by keyword(title)
        int retrieve(char* keyWord, app& found)const;     // Search for data by keyword
        int getHeight(void)const;    // Return the height of the tree as an int, used in isEfficient
        int balanceFactor(void)const;
        int displayAll(void)const;   // In sorted order by keyword
        int displayRange(char* loRange, char* hiRange); // Two arguemnts, display all info between those two (K thru P)
        int removeAll(void);    // explicit destructor
        int fileIn(void);     // read data from an external file and store it in the logbook
        int fileOut(void);    // calls app::write() in a recursive loop thru the entire tree
        int balanceTree(logbook& tree); // can be called on an etire logbook object to balance it
        friend ostream& operator << (ostream& output, const logbook& toDisplay);
        logbook& operator = (const logbook& source);
        logbook& operator += (const app& toAdd);
        logbook& operator += (const node& toAdd);
        app& operator [] (char* keyword)const;
        
    private:
        node * root;    // pointer to node
        int totalUsage; // total nodes
        int appUsage;   // total app nodes
        int webUsage;   // total website nodes
        int utilUsage;  // total utitlity nodes
        /* Recursive functions */
        int insert(node*& root, const app& toAdd);      // insert pre-order
        int removeMatch(node*& root, char* keyWord);    // recursive, remove by keyword search
        int removeAll(node*& root);         // explicit destructor
        int displayAll(node* root)const;    // recursively display all data 
        int retrieve(node* root, char* keyWord, app& found)const;   // find and populate object based on keyword
        int getHeight(node* root)const;         // recursively count tree levels, down all branches
        int balanceFactor(node * root)const;    // use height (0 balanced, +0 left-heavy, -0 right-heavy)
        int fileOut(node* root, ofstream& fout);// recursive file-writer (.txt)
        void copy(node*& dest, node* source);   // recursive copy function
        int balanceAll(node*& root)const;      // recursive function to balance nodes, bottom up
        int rotateDoubleLeft(node*& root)const;  // unbalanced Left subtree is Right-heavy
        int rotateSingleLeft(node*& root)const;   // unbalanced Left subtree is Left-heavy
        int rotateDoubleRight(node*& root)const;  // unbalanced Right subtree is Left-heavy
        int rotateSingleRight(node*& root)const; // unbalanced Right subtree is Right-heavy
};

/*********************************************************************/

#endif //_LOGBOOK_H_

