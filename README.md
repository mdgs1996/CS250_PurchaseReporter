# CS250_PurchaseReporter
## Summarize the project and what problem it was solving.
A fictional grocery company wants to observe the frequency of items purchased throughout the day. The purpose of this C++ project was to create a program that does the following:

1. Read an `input.txt` file containing a line-separated list of items purchased in chronological order.
2. Write a `frequency.txt` file that summarizes all the items purchsaed associated with their purchase frequency.
3. Provide an interface that gives a series of options:
   * View a specific item's purchase frequency
   * View the consolidated list of items with their associated purchase frequency
   * View a histogram of all items' purchase frequencies


## What did you do particularly well?

As I reflect back in this code, I feel particularly proud of how I was able to compute the correct alignment for the interface. Rather than having everything left-aligned,
I chose to have specific formatting per option. Both option 'a' and 'b' printed a 'y x 5' table of items (i.e. each row displays 5 items). I chose to have the histogram center-aligned
to allow all items' bars easily compared. I also loved the ability for the generated frequency map as read-only, since there should be no way to alter the results of the 
end-of-day report.

## Where could you enhance your code? How would these improvements make your code more efficient, secure, and so on?

Although this is a project for a fictional company, I would like to further enhance the program's ability to store all `frequency.txt` files to a cloud, where larger-scale
observations can be made. I think that it would be beneficial for this company to see how items purchase frequency performs through certain times of the 
week, month, season, or even year and make decisions based off these results.

## Which pieces of the code did you find most challenging to write, and how did you overcome this? What tools or resources are you adding to your support network?

I found the formatting the most challenging to write in this program. It was here that I had to manually plan and write down on a piece of paper what needs to be calculated 
to *dynamically* configure each table/graph's size. Every item and associated frequency has a different string value length, (e.g. 'Apples 3' as opposed to 'Watermelon 100').
Each whitespace value is different with each entry's string length, so brute-forcing whitespace values would be highly inefficient and unreliable. I needed to make simple 
"max value" utility methods to achieve this dynamic formatting.

## What skills from this project will be particularly transferable to other projects or course work?

This C++ project, in connection to other learned backend languages such as Java, JavaScript and Python, have fortified my understanding of organizing program workflow. 
While the syntax varies slightly between languages, they all have the capability to serve the same purpose of fulfilling the functional requirements of a program.

## How did you make this program maintainable, readable, and adaptable?

As I was writing this project, I wanted the complexity of the code to increase the deeper you go. In `main()`, only the `Menu` class and its associated `runMainMenu()` method 
was called. `runMainMenu()` presents a switch statement that calls specifically named trigger methods depending on the chosen option. All trigger methods have associated helper 
methods that run its overall function. All of this was to make the workflow of this program readable. As mentioned before, all results are dynamically formatted, making
cleaner and more adaptable code. 
