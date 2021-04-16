# HackON-068
The project for HackUST from the team 68, HackON

Our main program aims to give suggestions about which food should be produced next for the restaurant.

Our main program is called "Restaurant", it supports 7 functions:
1. Add a new type of possible food.
2. Delete a possible food.
3. Add a new order.
4. which food should you do next?
5. New customers choose to dine in!
6. Some dine-in customers are leaving!
7. Leave the system.

Firstly, users need to add different types of food for the restaurant by typing commend 1, and follow the instructions.
Users can also delete a type of food by calling the function 2 and follow the instructions.
Whenever there's a new food order coming in, users can type commend 3 and following the instructions to add the food order according to its customer's type (either dine in, take-away or online orders).
COMMEND 4 IS OUR MAIN FUNCTION, upon calling it will print out the type of food and the number to be produced based on an self-designed algorithm. 
Commend 5 and 6 are used when there's new customers joining and leaving the restaurant. In order to check whether the restaurant is full or not.
Commend 7 is used to leave the system.


The final.csv and R_prediction.R are separated pars of our project.
The R_prediction.R utilized the R language, aiming at predicting the demand of a type of food during a specific time interval (e.g. at noon). 
And the restaurant can use that model to do the prediction. Hence producing respective types of food beforehand to improve the efficiency.

The final.csv file is a demonstration using the algorithm using R_prediction.R, showing its ability.
