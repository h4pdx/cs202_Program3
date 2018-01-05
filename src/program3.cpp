
/* Ryan Hoover
 * CS 202 - Fant
 * 5/17/17
 * Program 3 */
 
/* This was implemented the way I intened. 
 * I ran out of time to do proper swapping between nodes in the list, 
 * and proper sorting of the recent entries.*/


#include "usageList.h"

int main()
{
    app myApp, foundApp;
    //app * foundApp = NULL;
    logbook appHistory;
    usageList recentApps;
    page myPage;
    //appHistory.fileIn();
    int menu = 0;
    char keyword[NAME];
    /* 
    if (appHistory.fileIn())
        cout << "\nText file data read into program.\n";
    else cout << "\nText file data not read into program.\n";
    */
     

    do {
        menu = mainMenu();
        switch (menu) {

            case 1:
       
                do {
                    do {
                        cin >> myApp;
                        cout << "\nYou entered:" << myApp;
                    } while (!confirm());
                    appHistory += myApp;
                    cout << "\nInserted into list.\n";
                } while (again());
                break;

            case 2:
                cout << appHistory;
                break;

            case 3:
                cout << "\nEnter an app to search for: ";
                cin.get(keyword, NAME, '\n'); cin.ignore(NAME, '\n');
                formatName(keyword);
                
                if (appHistory.retrieve(keyword, foundApp)) {
                    cout << foundApp;
                }
                else cout << "\nNothing Found.\n";
                break;
            case 4:
                cout << "\nEnter an app to use: \n";
                if (myPage.create()) {
                    cout << "\nApp created.\n";
                    if (!myPage.display())
                        cout << "\nCOuld not display.\n";
                    if (recentApps.insert(myPage)) {
                        cout << "\nNew page added to front of list.\n";
                    }
                    else cout << "\nPage not inserted\n";
                }
                break;
            case 5:
                cout << "\nRecent Apps: \n";
                if (!recentApps.displayAll())
                    cout << "\nNo recent apps to display.\n";
                break;

        }
    } while (menu != 6 && backToMenu());

    //appHistory.fileOut();
    return 0;
}
