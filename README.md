# DSA-project
This is a DSA project that takes in a csv file as input, parses it and places it into a binary tree.
The requirments for this program were to be able to take a csv file as input, open and parse it. Then take each log 
and place it into a chosen data structure. The program should also allow the user to print out the courses alphanumerically,
and search for a specific course and print it.

I had a choice between a vector, hash table, and binary tree for this problem. I broke down what the end goal was and what 
will be done to the data after it has been placed into the data structure. Then I determined which data structure is most 
efficient and effective for this use case. 

I hit a road blcok when creating the parsing routein. The way I was approaching it was become more complex and was not working.
I needed to find a better way of doing this. I thought of the idea to split each line and put it into a vector instead of trying to 
manually spliting the line with new code. This way was significantly more simple and it made it easier to solve the programming problem. 

Since this project and course in general I have gotten a lot better at debugging and testing. Throughout the course I have found several instances where I test the program and at first glance it looks like it works correctly. However closer inspection reveals that some edge cases fail. I feel like I have learned how important rigorous testing is, and have started to implement it when I code. Since this project I have also started to break methods up into smaller methods to make it more maintainable. I found doing it this may not only makes it more maintainable but easier to read and debug.
