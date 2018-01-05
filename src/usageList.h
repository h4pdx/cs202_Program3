
/* Ryan Hoover
 * CS 202 - Fant
 * 5/17/17
 * Program 3 */
#ifndef _USAGELIST_H_
#define _USAGELIST_H_
#include "logbook.h"


/* Implementation of the list of apps and their related usage history
 * page contains a char app name, to simulate app usage, user will insert
 * usageList stores these at head and will delete duplicates and upadete usage
 * page stores an AVL tree of balanced nodes */

class page {
    public:
        page(void);
        page(const page& source);
        page(char * nName, int nUsage, logbook& nLog);
        ~page();
        void clear();
        page*& goNext(void);
        void setNext(page * setTo);
        bool ifNext(void);
        int create(void);
        int display(void);
        int copy(const page& source);
        page& operator = (const page& source);
        
    private:
        char * appName;
        int timesUsed;
        logbook appLog;
        page * next;
};


class usageList {
    public:
        usageList(void);
        usageList(const usageList& source);
        ~usageList(void);
        int insert(page& toAdd);
        int displayAll(void);
        int displayRecent(void);
        usageList& operator = (const usageList& source);
        int copy(const usageList& source);
        
    private:
        page * head;
        int displayAll(page*& head);
        int copy(page*& dest, page * source);
        int removeAll(page*& head);
        

};




#endif //_USAGELIST_H_

