
/* Ryan Hoover
 * CS 202 - Fant
 * 5/17/17
 * Program 3 */

#include "usageList.h"

//----------------------------------------------------------

// default
page::page(void):
    appName(NULL), timesUsed(0), next(NULL)
{}

//----------------------------------------------------------

// copy constructor
page::page(const page& source) {
    (*this).copy(source);
}

//----------------------------------------------------------

// 3 argument constructor
page::page(char * nName, int nUsage, logbook& nLog) {
    if (nName) {
        appName = new char[strlen(nName)+1];
        strcpy(appName, nName);
    }
    timesUsed = nUsage;
    appLog = nLog; //overloaded for deep copy
    next = NULL;
}

//----------------------------------------------------------

// delete everything
page::~page(void) {
    clear();
}

void page::clear(void) {
    if (appName) {
        delete appName;
        appName = NULL;
    }
    if (next)
        next = NULL;
    timesUsed = 0;
}

page& page::operator = (const page& source) {
    if (this == &source)
        return (*this);
    (*this).clear();
    (*this).copy(source);
    return (*this);
}

// return next
page*& page::goNext(void) {
    return next;
}

//----------------------------------------------------------

// set value of next ptr
void page::setNext(page * setTo) {
    if (setTo)
        next = setTo;
    else next = NULL;
}

//----------------------------------------------------------

// check to see if next exists
bool page::ifNext(void) {
    if (next)
        return true;
    else return false;
}

//----------------------------------------------------------

// create new app data
int page::create(void) {
    char nName[NAME];
    cout << "\nWhat app was used: ";
    cin.get(nName, NAME, '\n'); cin.ignore(NAME< '\n');
    appName = new char[strlen(nName)+1];
    strcpy(appName, nName);
    ++timesUsed;
    next = NULL;
    return 1;
}

//----------------------------------------------------------

// dipslay page
int page::display(void) {
    int success = 0;
    if (appName) {
        cout << "\nApp name: " << appName << endl;
        ++success;
    }
    cout << "\nTimes used: " << timesUsed;
    cout << appLog; // overloaded << for tree
    return success;
}

//----------------------------------------------------------

// copy single page contents
int page::copy(const page& source) {
    int success = 0;
    if (source.appName) {
        appName = new char[strlen(source.appName)+1];
        strcpy(appName, source.appName);
        ++success; // successful strcpy is sufficient enough for return true
    }
    appLog = source.appLog; // overloaded = operator for tree class
    timesUsed = source.timesUsed;
    next = NULL;
    return success;
}


/*********************************************************************/

usageList::usageList(void):
    head(NULL)
{}


//----------------------------------------------------------

usageList::usageList(const usageList& source) {
    copy(head, source.head);
}

//----------------------------------------------------------


usageList::~usageList(void) {
    removeAll(head);
}

//----------------------------------------------------------

// overloaded for deep copy
usageList& usageList::operator = (const usageList& source) {
    if (this == &source)
        return (*this);
    (*this).removeAll(head);
    (*this).copy(source);
    return (*this);
}


// insert at head (recent)
int usageList::insert(page& toAdd) {
    int success = 0;
    if (!head) {
        head = new page(toAdd);
        head->setNext(NULL);
        ++success;
    }
    else {
        page * temp = new page(toAdd);
        temp->setNext(head);
        head = temp;
        ++success;
    }
    return success;
}

//----------------------------------------------------------

// recursively display all
int usageList::displayAll(void) {
    return displayAll(head);
}

//----------------------------------------------------------

// display all in order
int usageList::displayAll(page*& head) {
    if (!head)
        return 0;
    int success = 0;
    success = head->display();
    success += displayAll(head->goNext());
    return success;
}

//----------------------------------------------------------

//display just the first one(most recent)
int usageList::displayRecent(void) {
    if (!head)
        return 0;
    int success = 0;
    success = head->display();
    return success;
}

//----------------------------------------------------------

//explicit delete function
int usageList::removeAll(page*& head) {
    if (!head)
        return 0;
    int counter = 0;
    counter += removeAll(head->goNext());
    delete head;
    head = NULL;
    if (!head)
        ++counter;
    return counter;
}

//----------------------------------------------------------

// wrapper for two  arguemnt deep copy
int usageList::copy(const usageList& source) {
    return copy(head, source.head);
}

// copies entire list
int usageList::copy(page*& dest, page* source) {
    if (!source) {
        dest = NULL;
        return 0;
    }
    int counter = 0;
    if (!dest) {
        dest = new page(*source);
        ++counter;
    }
    counter += copy(dest->goNext(), source->goNext());
    return counter;
}

//----------------------------------------------------------


