# cs202_Program3

Programming Assignment #3
CS 202 Programming Systems

Primary Goal for program #3:

The primary goal for program #3 is to experience operator overloading in an object oriented environment. We want to correctly create classes that properly support the copy constructor, destructor, and now the assignment operator when dynamic memory is involved. Remember that copy constructors in a hierarchy require the use of initialization lists to cause the base class copy constructor to be invoked.

Your primary goal with program #3 is to apply the functionality of the operators, the appropriate arguments (operand data types) and returned types (residual values for the operators) to the following problem. Think about how the operators are used and try to mimic the behavior in your own classes. How is the returned type used? Who controls the memory of the residual value? The client program (lvalue) or the operator (rvalue). Make sure to pass (and return) by reference whenever possible!

Remember OOP:
With OOP the key idea is to break down the problem outlined (below) into small pieces and assign those responsibilities to individual classes. For each assignment, your job will be to create an OO design and program that shows how Object Oriented constructs could be used to solve a real-world problem. You will want to focus on how to design classes that are well structured, efficient, that work together, and where each class has a specific “job”. This time you are adding operator overloading as the new syntax for your solution!

Before you design this program, take a look back at your first two programs. Did you tie the data structures into the midst of your OO designs? Did the designs really become all about the data structure and not so much about the problem at hand? The key to OOP in my opinion is to create the design based on the problem prior to applying the data structure. The data structures are about how we handle the data – not necessarily the key to OOP. For this assignment, your application will be the OOP portion of the assignment. Then, implement the data structures in Abstract Data Types (ADTs) with the full support of operators (via operator overloading).

Program #3 – The Problem

For this assignment, we will create a program that ultimately will become an app. But, before it does, we need to test out the idea. As I go about my life, I would like an app to be able to keep track of what I do and how long I spend at it. Then I can look back and see how I spent my time and whether or not I need to make some adjustments. Do I sit there on my phone battling a gym or reading Facebook instead of taking a hike? This program would include what websites we go to most frequently along with all of the other apps or programs that are used on a daily basis – such as how much I use Facebook or snapchat versus Pokémon Go.

The Data: Of course, your job IS NOT to write the code to detect when different apps are being used. That is something that we would do in industry to finalize the product. Instead, we want to “test market” the idea. This means that our data will all be coming from an external data file as well as from the user. The data should include at least the following (you may add to this): (a) the name of the application or website used, (b) information about actions the user was taking (c) the date used, (d) the length of the session using the app or program. Possibly you will want to keep some historical data as well about how much this app is used.

Making it OO: We will use this concept to develop a OO application to most quickly find the most recently used applications. You will want to develop at least five classes, as normal, to design the program, using single inheritance as appropriate. To break down the problem, think about what is similar or different about the apps and programs that we use on a daily basis. For example, a website will need an address (e.g., http://pdx.edu/) where most other apps do not have this. And with websites, there may be websites that are related and would still count for the same session So when the user goes to https://my.pdx.edu/contact-us isn’t it still the same pdx.edu session? On the other hand, facebook might need to take how much you use the newsfeed versus messenger and so on.

Your job will be to pick three different varieties of applications. They should be different types of applications so that you can experience some of the nuances between them. Make sure to build an inheritance hierarchy. Break down the common elements in the types of applications you are supporting and push those up to the base class! Then, have the derived classes handle the differences. Remember to avoid getters as much as possible with these classes – instead implement the functions that actually work ON the data IN the classes that own the data!! This is where you will get the most benefit of OOP.

Searching and the Data structure: For this program to be useful, we need to provide the most frequently accessed information first – for quick access; we would never use it if we had to scroll through 100’s of items. In this case, we will be working with a type of self-organizing list. The idea here is that the list is searched for a given app. If the app does not already appear in the list, then it is inserted at the beginning; otherwise, if it has been found, it is moved from its current position, forward. So, the first time Pokemon Go is used, it starts at the beginning. If it is never used again, it will be near the end. However, if you use it often, each day it is used - it will be moved from its current location in the list, forward until it reaches the beginning. Therefore, the client can always get the most frequently used applications and programs because they are at the beginning. This list will be a linear linked list.

Each node in the list is to contain a BST of apps and programs that have the same frequency. The BST allows us to keep these sub-lists in sorted order and minimize sequential searches. This means the first node has all of the apps most frequently accessed and the last node will have a BST of the apps rarely accessed. This data structure is useful for situations where the data items involved represents “locality of reference” – where a data item is referenced frequently for a while, and then over time it exhibits less and less usage, only to reappear again frequently for a while and so on.

You have an option with this – the BST can be a balanced tree of your choosing. Or, you can wait until the next program to implement a balanced tree (in Java).

Operator Overloading: The key part of this assignment is to create a new list data type that has a complete set of operators. It should allow one to add, remove, search, “use”, and display apps based on their frequency. You might also want to retrieve all of the top used apps (the first BST in the list).

The operators to support must include: =, +, +=, ==, !=, the relational operators, and the ability to input/output data. I imagine the [] would be useful as well where index 0 would be the top used apps. Remember if you implement the + operator you should implement the +=. But, what about the equality operator? As you decide how to apply the operators, make sure to stay within the rules of how the operators are expected to behave. You may find that some operators don’t apply at all (and therefore shouldn’t be implemented). And, don’t forget your copy constructor!

Yes, you CAN now write your own STRING data type, but it can’t be the only place you use operator overloading…since we did that in topic #6!). However, if you implement a string class, the operators for that class “do not count” for this assignment. You need to overload the operators for a “list” data type specifically.

Questions to ask…about operator overloading

When using operator overloading, remember to ask yourself the following questions:
a) What should be the residual value (and what data type is this)?
- Never have a void returning operator!
b) Should the result be a modifiable lvalue or an rvalue?
- Lvalues are returned by reference, most rvalues are returned by value.
c) What are the data types of the operator’s operands?
- If the operand isn’t changed, then make it a const
- Remember to pass as a constant reference whenever possible.
d) Is the first operand always an object of class?
- If so, then it could be a member function.
e) Can the operator be used with constant operands?
- If the first operand can be a constant, and IF it is a member function, then it should be a constant member function.
