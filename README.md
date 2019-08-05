Case Study - I:

Easy selection of Patient monitor using C++:
-------------------------------------------

Problem Statement: Make the Chatbot as a console application. The Chatbot will accept input and give its response on the console. The conversation (sequence of messages) should lead the customer to a purchase-suggestion. It must be easy to re-use this Chatbot for another domain (such as without having to re-compile it. 

Solution Design:  

The chatbot will display questions one by one with options for the user to select. The user should select an option for each question only from the given options  

The first question is default. The subsequent question is selected depending on the user’s selected input for the first question and the other questions are selected the same way 

When there are no more questions to ask for finalizing a product, the chatbot will display the name(s) of the relevant patient monitors for the user 

Design Requirements: 

List of questions with question IDs 

List of patient monitor names with their IDs 

List of options with option IDs for all the question IDs and the linking question ID and patient monitor IDs for all the options 

Class diagram: 

 

Main User story 

As a technical user I need to develop a Chatbot which will interact with the customer and suggest a suitable patient monitor depending on the input. 

Acceptance criteria: 

Keep a record of questions in a database. 

Keep a record of patient monitors in a database. 

When the questions are answered by the user, depending on the input next question should be asked. 

Finally, an apt patient monitor should be selected. 

Test cases: 

When a option is given as an input to a particular question, the option should be analyzed and depending on that next question should be asked or suitable patient monitor should be displayed 

Sub - stories 

# User Story 1: 

As a technical user, I want to store all the questions in a database. 

Acceptance Criteria: 

All the questions to be asked should be saved in a database with question id. 

Options of every question should be saved with its unique option id and its question id. 

Every options should also be mapped to next consequent question. 

  

Test Cases: 

Depending on the question id , corresponding question need to be displayed. 

Depending on the option id, consequent question id need to be mapped correctly. 

  

  

# User Story 2: 

As a technical user I need to keep a record of patient monitors with its monitor id. 

Acceptance criteria: 

The names of all the patient monitor along with the monitor id should be recorded. 

The patient monitor should also be mapped to its specifications. 

  

Test cases: 

When monitor id is given then it should display its respective patient monitor name. 

When a monitor id is given it should display the specification associated with it. 

 

# User Story 3: 

As a technical user I need to have a program that will integrate the database with the code. 

Acceptance Criteria: 

The program must take the right questions and options from the database and display it to the user. 

The program must have a loop to cover all the products and the questions given in database. 

 Test Cases: 

 For a valid input option given by user the program should display the right question to be asked next. 

If the user inputs an invalid option an error message must be displayed on the screen. 

 

 

  

 

 

 

