
/* Ryan Hoover
 * CS 202 - Fant
 * 5/17/17
 * Program 3 */

#include "app.h"

//----------------------------------------------------------

// default constructor
app::app():
    appName(NULL),
    appType(NULL),
    sessionInfo(NULL),
    usageDate(NULL),
    sessionLength(0),
    timesUsed(0)
{}

//----------------------------------------------------------

/*
   app::app()
   {
   appName = appType = sessionInfo = usageDate = NULL;
   sessionLength = timesUsed = 0;
   }
   */

// copy constructor calls explicit copy function
app::app(const app & source) {
    (*this).copy(source);
    //clear();
    //if (!copy(source))
    //    cout << "\nCopy failed.\n";
    //cout << "\nCould not copy\n";
}

//----------------------------------------------------------

// constructor with all 6 data member arguments
app::app(char*nName,char*nType,char*nInfo,char*nDate,int nTime, int nUsage) {
    (*this).create(nName,nType,nInfo,nDate,nTime,nUsage);
}

//----------------------------------------------------------

// calls explicit destructor
app::~app() {
    clear();
}

//----------------------------------------------------------

// assignment operator performs deep copy
app& app::operator = (const app& source) {
    if (!this) return (*this);
    if (this == &source)
        return (*this); 
    (*this).clear();
    (*this).copy(source);
    return (*this);
}

//----------------------------------------------------------

// increment app.timesUsed
app& app::operator ++ (void) {
    (*this).timesUsed += 1;
    return (*this);
}

//----------------------------------------------------------

// decrement app.timesUsed
app& app::operator -- (void) {
    (*this).timesUsed -= 1;
    return (*this);
}

//----------------------------------------------------------

// overloaded (+) is used to add to the timesUsed (frequency of use stat)
app operator + (const app& add1, const app& add2) {
    app temp(add1);
    temp.timesUsed += add2.timesUsed;
    return temp;
}

app operator + (const app& add1, int add2) {
    app temp(add1);
    temp.timesUsed += add2;
    return temp;
}

app operator + (int add1, const app& add2) {
    app temp(add2);
    temp.timesUsed += add1;
    return temp;
}

//----------------------------------------------------------

// overloaded (-) operator, used for frequency of use stat
app operator - (const app& sub1, const app& sub2) {
    app temp(sub1);
    temp.timesUsed -= sub2.timesUsed;
    return temp;
}

// object.timesUsed - int
app operator - (const app& sub1, int sub2) {
    app temp(sub1);
    temp.timesUsed -= sub2;
    return temp;
}

// int - object.timesUsed
app operator - (int sub1, const app& sub2) {
    int temp1 = sub1;
    app temp2(sub2);
    temp1 -= temp2.timesUsed;
    temp2.timesUsed = temp1;
    return temp2;
}
    
//----------------------------------------------------------

// object1 add and assign object2
app& app::operator += (const app& toAdd) {
    (*this).timesUsed += toAdd.timesUsed;
    return (*this);
}

// object add and assign int
app& app::operator += (int toAdd) {
    (*this).timesUsed += toAdd;
    return (*this);
}

//----------------------------------------------------------

// object1 subtract and assign object2
app& app::operator -= (const app& toSub) {
    (*this).timesUsed -= toSub.timesUsed;
    return (*this);
}

// object subtract and assign int
app& app::operator -= (int toSub) {
    (*this).timesUsed -= toSub;
    return (*this);
}

//----------------------------------------------------------

// object1 not equal to object2
bool operator != (const app& cmp1, const app& cmp2) {
    //int cmp = cmp1.comparison(cmp1, cmp2);
    if (cmp1.timesUsed == cmp2.timesUsed)
        return false;
    else
        return true;
}

// object.timesUsed not equal to int
bool operator != (const app& cmp1, int cmp2) {
    bool notEqual = true;
    if (cmp1.timesUsed == cmp2)
        notEqual = false;
    return notEqual;
}

// int not equal to object.timesUsed
bool operator != (int cmp1, const app& cmp2) {
    bool notEqual = true;
    if (cmp1 == cmp2.timesUsed)
        notEqual = false;
    return notEqual;
}

//----------------------------------------------------------

// object1.timesUsed is equal to object2.timesUsed
bool operator == (const app& cmp1, const app& cmp2) {
    //int cmp = cmp1.comparison(cmp1, cmp2);
    if (cmp1.timesUsed == cmp2.timesUsed)
        return true;
    else
        return false;
}

// object.timesUsed is equal to int
bool operator == (const app& cmp1, int cmp2) {
    bool isEqual = false;
    if (cmp1.timesUsed == cmp2)
        isEqual = true;
    return isEqual;
}

// int is equal to object.timesUsed
bool operator == (int cmp1, const app& cmp2) {
    bool isEqual = false;
    if (cmp1 == cmp2.timesUsed)
        isEqual = true;
    return isEqual;
}

//----------------------------------------------------------

// obj1.timesUsed less than obj2.timesUsed
bool operator < (const app& cmp1, const app& cmp2) {
    if (cmp1.timesUsed < cmp2.timesUsed)
        return true;
    else
        return false;
}

// obj.timesUsed less than int
bool operator < (const app& cmp1, int cmp2) {
    if (cmp1.timesUsed < cmp2)
        return true;
    else return false;
}

// int less than obj.timesUsed
bool operator < (int cmp1, const app& cmp2) {
    if (cmp1 < cmp2.timesUsed)
        return true;
    else return false;
}

//----------------------------------------------------------

// obj1.timesUsed greater than obj2
bool operator > (const app& cmp1, const app& cmp2) {
    if (cmp1.timesUsed > cmp2.timesUsed)
        return true;
    else return false;
}

// obj.timesUsed greater than int
bool operator > (const app& cmp1, int cmp2) {
    if (cmp1.timesUsed > cmp2)
        return true;
    else return false;
}

// int greater than obj.timesUsed
bool operator > (int cmp1, const app& cmp2) {
    if (cmp1 > cmp2.timesUsed)
        return true;
    else return false;
}

//----------------------------------------------------------
 
// obj1.timesUsed less than or equal to obj2.timesUsed
bool operator <= (const app& cmp1, const app& cmp2) {
    if (cmp1.timesUsed <= cmp2.timesUsed)
        return true;
    else return false;
}

// obj.timesUsed less than or equal to int
bool operator <= (const app& cmp1, int cmp2) {
    if (cmp1.timesUsed <= cmp2)
        return true;
    else return false;
}

//int less than or equal to obj.timesUsed 
bool operator <= (int cmp1, const app& cmp2) {
    if (cmp1 <= cmp2.timesUsed)
        return true;
    else return false;
}

//----------------------------------------------------------

// obj1.timesUsed greater than or equal to obj2.timesUsed
bool operator >= (const app& cmp1, const app& cmp2) {
    if (cmp1.timesUsed >= cmp2.timesUsed)
        return true;
    else return false;
}

// obj.timesUsed greater than or equal to int
bool operator >= (const app& cmp1, int cmp2) {
    if (cmp1.timesUsed >= cmp2)
        return true;
    else return false;
}

//int less greater or equal to obj.timesUsed 
bool operator >= (int cmp1, const app& cmp2) {
    if (cmp1 >= cmp2.timesUsed)
        return true;
    else return false;
}

//----------------------------------------------------------

// replace void arg create() function,
// calls app::create(6 arg list) for deep copies into obj
istream& operator >> (istream& input, app& toCreate) {
    //clear();
    //cout << "\nSuccessfully overloaded (cin >>) operator.dope.\n";
    char newName[NAME], newType[NAME], newInfo[INFO], newDate[DATE];
    int newLen, newUsage, len;
    newLen = newUsage = len = 0;
    // Enter the name of the current app/website/utility
    cout << "\n >> App name: ";
    input.get(newName, NAME, '\n'); input.ignore(NAME,'\n');
    toCreate.format(newName);
    // The type must match with one of the const char types (1,2,or 3)
    cout << "\n >> App Type (App, Website, Utility): ";
    do {
        input.get(newType, NAME,'\n'); input.ignore(NAME,'\n');
        toCreate.format(newType);
        if (!toCreate.validateType(newType))
            cout << "\nEnter one of the three app types: ";
    } while (!toCreate.validateType(newType));
    // Information about actions taken during session
    cout << "\n >> Summary of actions taken during individual session: ";
    input.get(newInfo, INFO,'\n'); input.ignore(INFO,'\n');
    // will be displayed as MM/DD/YYY (05/17/2017)
    do {
        cout << "\n >> Date of session (format MMDDYYYY): ";
        input.get(newDate,DATE,'\n'); input.ignore(DATE,'\n');
        len = strlen(newDate);
    } while(len < 8);

    // will be converted to hours, minutes for display. 
    // storage too? (for sorting by time used, down to the minute)
    cout << "\n >> Session length (in minutes): ";
    input >> newLen; input.ignore(100,'\n');
    while (input.fail()) {
        input.clear(); input.ignore(100,'\n');
        input >> newLen; input.ignore(100,'\n');
    }
    //newUsage = timesUsed(appName) +1;
    // something will need to be done about this, but for now just to see it works.
    newUsage = 1;
    toCreate.create(newName,newType,newInfo,newDate,newLen,newUsage);
    //return success;
    return input;
}

//----------------------------------------------------------


// Replace named display()const fucntion
ostream& operator << (ostream& output, const app& toDisplay) {
    //toDisplay.display();void app::display()const
    //if (!appName||!appType||!sessionInfo||!usageDate)
    //    return;
    //output << "\nSuccessfully overloaded (cout <<) operator.dope.\n";
    output << "\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n";
    output << "\n" << toDisplay.appType << " : " << toDisplay.appName << "\n"
        << "Summary of session activity...\n" << toDisplay.sessionInfo;
    //int len = strlen(usageDate);
    //if (len == 8)
    output << "\n...";
    // small loops to display the date in proper format
    output << "\nAccessed on (";
    if (toDisplay.usageDate) {
        for (int i=0;i<2;++i) {
            if (toDisplay.usageDate[i])
                output << toDisplay.usageDate[i];
        }
        output << "/";
        for (int i=2;i<4;++i) {
            if (toDisplay.usageDate[i])
                output << toDisplay.usageDate[i];
        }
        output << "/";
        for (int i=4;i<8;++i) {
            if (toDisplay.usageDate[i])
                output << toDisplay.usageDate[i];
        }
        output << ").";
    }
    int hour, minute, len;
    hour = minute = len = 0;
    len = toDisplay.sessionLength;
    hour = len / 60; // simple math to make the minute dipslay fancy
    minute = len % 60; // keep track of minutes, but display will translate into hours, minutes
    output << "\nSession time [";
    if (hour > 0) // only display the hour stat if session time is greater than 1 hour
        output << hour << "hr, ";
    output << minute << "min].\n";
    cout << "Lifetime usage: " << toDisplay.timesUsed;
    output << "\n<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n";
    return output;
    //return true;
}
/*
   app app::operator + (const app & operand1, const app & operand2)
   {
   app temp;
   temp


   }
   */

//----------------------------------------------------------

void app::clear(void) {
    if (appName) {
        delete [] appName;
        appName = NULL;
    }
    if (appType) {
        delete [] appType;
        appType = NULL;
    }
    if (sessionInfo) {
        delete [] sessionInfo;
        sessionInfo = NULL;
    }
    if (usageDate) {
        delete [] usageDate;
        usageDate = NULL;
    }
    sessionLength = 0;
    timesUsed = 0;
}

//----------------------------------------------------------

// fills data members with data from arguments
void app::create(
        char * newName,
        char * newType,
        char * newInfo,
        char * newDate,
        int newLen,
        int newUsage) {
    //int success = 0;
    //clear();
    if (newName) {
        appName = new char[strlen(newName)+1];
        strcpy(appName, newName);
        //++success;
    }
    else
        appName = NULL;
    if (newType) {
        appType = new char[strlen(newType)+1];
        strcpy(appType, newType);
        //++success;
    }
    else
        appType = NULL;
    if (newInfo) {
        sessionInfo = new char[strlen(newInfo)+1];
        strcpy(sessionInfo, newInfo);
        //++success;
    }
    else
        sessionInfo = NULL;
    if (newDate) {
        usageDate = new char[strlen(newDate)+1];
        strcpy(usageDate, newDate);
        //++success;
    }
    else
        usageDate = NULL;
    sessionLength = newLen;
    if (sessionLength != newLen)
        sessionLength = 0;
    // will this be 
    timesUsed = newUsage;
    if (timesUsed != newUsage)
        timesUsed = 0;
    //return success;
}

//----------------------------------------------------------

/*
// perhaps insert can be used 
void app::create()
{
//clear();
char newName[NAME], newType[NAME], newInfo[INFO], newDate[DATE];
int newLen, newUsage;
newLen = newUsage = 0;
// Enter the name of the current app/website/utility
cout << "\n >> App name: ";
cin.get(newName, NAME, '\n'); cin.ignore(NAME,'\n');
format(newName);
// The type must match with one of the const char types (1,2,or 3)
cout << "\n >> App Type (App, Website, Utility): ";
do
{
cin.get(newType, NAME,'\n'); cin.ignore(NAME,'\n');
format(newType);
if (!validateType(newType))
cout << "\nEnter one of the three app types: ";
}
while (!validateType(newType));
// Information about actions taken during session
cout << "\n >> Summary of actions taken during individual session: ";
cin.get(newInfo, INFO,'\n'); cin.ignore(INFO,'\n');
// will be displayed as MM/DD/YYY (05/17/2017)
cout << "\n >> Date of session (format MMDDYYYY): ";
cin.get(newDate,DATE,'\n'); cin.ignore(DATE,'\n');
// will be converted to hours, minutes for display. 
// storage too? (for sorting by time used, down to the minute)
cout << "\n >> Session length (in minutes): ";
cin >> newLen; cin.ignore(100,'\n');
while (cin.fail())
{
cin.clear(); cin.ignore(100,'\n');
cin >> newLen; cin.ignore(100,'\n');
}
//newUsage = timesUsed(appName) +1;
// something will need to be done about this, but for now just to see it works.
newUsage = 1;
create(newName,newType,newInfo,newDate,newLen,newUsage);
//return success;
}
*/

/*
   int timesUsed(char * toMatch)
   {
   int usage = 0;
   if (!strcmp(toMatch, type1) || !strcmp(toMatch, type2) || !strcmp(toMatch, type3))
   ++usage;
   return usage;
   }
   */
/*
   int create(const app & toAdd)
   {
   create(
   toAdd.appName,
   toAdd.appType,
   toAdd.sessionInfo,
   toAdd.usageDate,
   toAdd.sessionLength,
   toAdd.timesUsed
   );
   }
   */

//----------------------------------------------------------

int app::fileOut(ofstream& fout)const {
    int success = 0;
    if (fout) {
        ++success;
        fout << appName << ':';
        fout << appType << ':';
        fout << sessionInfo << ':';
        fout << usageDate << ':';
        fout << sessionLength << ':';
        fout << timesUsed << '\n';
    }
    return success;
}

//----------------------------------------------------------

int app::retrieve(char* keyword, app& found)const {
    if (!keyword || !appName)
        return 0;
    int success = 0;
    if (!strcmp(appName, keyword)) {
        found.clear();
        //found.copy(*this)+1;
        found = (*this);
        //++success;
        if (found == (*this))
            ++success;
    }
    return success;
}

//----------------------------------------------------------

void app::copy(const app& source) {
    //clear();
    //int success = create(copyFrom);
    /*bool success = false;
      if (!source)
      return success;
      else success = true;*/
    //if (!source) return;
    create(source.appName,source.appType,source.sessionInfo,source.usageDate,source.sessionLength,source.timesUsed);
    //return success;
    return;
}

//----------------------------------------------------------

bool app::validateType(const char * toValidate)const {
    bool valid = false;
    //int validator = 0;

    // Make sure inputs fall into one of three categories
    if (!strcmp(toValidate, type1) || !strcmp(toValidate, type2) || !strcmp(toValidate, type3)) {
        valid = true;
    }
    /*
       else if (!strcmp(toValidate, type2))
       {
       valid = true;
       }
       else if (!strcmp(toValidate, type3))
       {
       valid = true;
       }
       */
    //validator = strcmp(toValidate, type3);
    return valid;
}

//----------------------------------------------------------

// display all contents, properly formatted
bool app::display(void)const {
    if (!appName||!appType||!sessionInfo||!usageDate)
        return false;
    cout << "\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n";
    cout << "\n" << appType << " : " << appName << "\n"
        << "\n..."
        << "Summary of session activity:\n" << sessionInfo;
    //int len = strlen(usageDate);
    //if (len == 8)
    cout << "\n...";
    cout << "\nAccessed on (";
    for (int i=0;i<2;++i)
        cout << usageDate[i];
    cout << "/";
    for (int i=2;i<4;++i)
        cout << usageDate[i];
    cout << "/";
    for (int i=4;i<8;++i)
        cout << usageDate[i];
    cout << ")";
    int hour, minute;
    hour = minute = 0;
    hour = sessionLength / 60;
    minute = sessionLength % 60;
    cout << "\n[";
    if (hour > 0)
        cout << hour << "hr, ";
    cout << minute << "min] Session Time.\n";

    cout << "\n<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n";
    return true;
}

//----------------------------------------------------------

void app::format(char * toFormat) {
    if (!toFormat)
        return;
    int t = strlen(toFormat);
    toFormat[0] = toupper(toFormat[0]);
    for (int i=1; i < t; ++i) {
        toFormat[i] = tolower(toFormat[i]);
    }
    for (int i=1; i < t; ++i) {
        if (toFormat[i] == ' ') {
            toFormat[i+1] = toupper(toFormat[i+1]);
        }
    }
    return;
}

//----------------------------------------------------------

int app::sessionLen(void)const {
    return sessionLength;
}

//----------------------------------------------------------

int app::comparison(const app& cmp1, const app& cmp2)const {
    int comparison = 0;
    comparison += strcmp(cmp1.appName, cmp2.appName);
    comparison += strcmp(cmp1.appType, cmp2.appType);
    comparison += strcmp(cmp1.sessionInfo, cmp2.sessionInfo);
    comparison += strcmp(cmp1.usageDate, cmp2.usageDate);
    comparison += cmp1.sessionLength - cmp2.sessionLength;
    comparison += cmp2.timesUsed - cmp2.timesUsed;
    return comparison;
}

//----------------------------------------------------------

