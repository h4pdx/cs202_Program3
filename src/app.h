/* Ryan Hoover
 * CS 202 - Fant
 * 5/17/17
 * Program 3 */

/* The App calls keeps track of app usage, and stores data related to it. 
 * Since we are simulating app usage by user input and reading info from a file, 
 * No actual app functionality is needed, just to update what my program keeps track of.
 * This app history info will be stored in a tree, within a linear linked list of trees
 * organized on the condition that each tree will have matching timesUsed data.
 * Each node in the list will have a tree of app usage info that corresponds to how
 * many times a particular app has been used. */

#ifndef _APP_H_
#define _APP_H_
#include <iostream>
#include <cstdlib>
#include <cctype>
#include <cstring>
#include <fstream>
#include <stdexcept>
using namespace std;
const int NAME = 41;
const int INFO = 281;
const int DATE = 9;
const int SIZE = 100;

// compare each new appType input to one of these, and if it matches,
// increment how many times it has appeared
const char type1[NAME] = {"App"};
const char type2[NAME] = {"Website"};
const char type3[NAME] = {"Utility"};

class app {
    public:
        app(void);
        app(const app& source);
        app(char*, char*, char*, char*, int, int);
        ~app(void);
        void clear(void);
        //void create();
        //int create(const app & toAdd);
        void create(char*newName,char*newType,char*newInfo,char*newDate,int newLen,int newUsage);
        void copy(const app& source);
        bool validateType(const char* toValidate)const;
        bool display(void)const;
        void format(char* toFormat);
        int retrieve(char* keyword, app& found)const;
        int sessionLen(void)const;
        int comparison(const app& cmp1, const app& cmp2)const;
        int fileOut(ofstream& fout)const;
        char* getType(void);
        app& operator = (const app& source);
        friend ostream& operator << (ostream& output, const app& toDisplay);
        friend istream& operator >> (istream& input, app& toCreate);
        // These relational operators are for manipulating times used within each app
        app& operator ++ (void);
        app& operator -- (void);
        friend app operator + (const app& add1, const app& add2);
        friend app operator + (const app& add1, int add2);
        friend app operator + (int add1, const app& add2);
        friend app operator - (const app& sub1, const app& sub2);
        friend app operator - (const app& sub1, int sub2);
        friend app operator - (int sub1, const app& sub2);
        app& operator += (const app& toAdd);
        app& operator += (int toAdd);
        app& operator -= (const app& toSub);
        app& operator -= (int toSub);
        friend bool operator == (const app& cmp1, const app& cmp2);
        friend bool operator == (const app& cmp1, int cmp2);
        friend bool operator == (int cmp1, const app& cmp2);
        friend bool operator != (const app& cmp1, const app& cmp2);
        friend bool operator != (const app& cmp1, int cmp2);
        friend bool operator != (int cmp1, const app& cmp2);
        friend bool operator < (const app& cmp1, const app& cmp2);
        friend bool operator < (const app& cmp1, int cmp2);
        friend bool operator < (int cmp1, const app& cmp2);
        friend bool operator > (const app& cmp1, const app& cmp2);
        friend bool operator > (const app& cmp1, int cmp2);
        friend bool operator > (int cmp1, const app& cmp2);
        friend bool operator <= (const app& cmp1, const app& cmp2);
        friend bool operator <= (const app& cmp1, int cmp2);
        friend bool operator <= (int cmp1, const app& cmp2);
        friend bool operator >= (const app& cmp1, const app& cmp2);
        friend bool operator >= (const app& cmp1, int cmp2);
        friend bool operator >= (int cmp1, const app& cmp2);


    protected:
        char * appName; // Facebook (newsfeed) or Facebook (messenger)
        char * appType; // one of the three catgories of apps - match input with const chars?
        char * sessionInfo; // record of what actions were taken in the app
        char * usageDate; // format 05/17/2017
        int sessionLength; // round to the nearest minute
        int timesUsed; // keep track of how many times this kind of app has been used.
        // might need some sort of checking function to check how many instances of a given app
        // name appear within the data structure already.
        // a counter that would strcmp each entry and return how many exist already, prior to
        // this current objects creation, then set the timesUsed variable to return_val+1

};

int mainMenu(void);
bool again(void);
bool confirm(void);
bool backToMenu(void);
int formatName(char * aName);

#endif // _APP_H_
