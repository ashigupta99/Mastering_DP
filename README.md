****Assignment 1:****


****Ques 1:****

Setting up global variables for easy updation- for **sales**, **purch** (cost of items restocked), **loan** taken, **repay** (cost to be repayed including interest) and **profit** (negative for loss)

Data structures:
**Products** list: Vector- tuple (bcs vector can take only 1 template parameter- Example- vector<int,int> is not possible) of product_id, quantity, cp and sp
**Translog**: In from of string
**Queries** of Customer: Vector- tuple (same reason) of prod_id, quantity and payoff value (in proc_cust function)

Functions:
**getsp** for getting selling price of a product corresponding to provided product id
**getcp** for getting cost price of a product corresponding to provided product id
**getst** for getting stock of a product corresponding to provided product id
**updst** for updating stock of a product corresponding to provided product id
**setup_user** for setting up products by user input
**pre_setup** for pre setting products
**proc_cust** for processing all transactions related to a customer
**printsum** for printing final transcation log at day-end

When user begins, he is asked if he wants to set up products on his own or wants pre-set products (10), which are displayed on screen (customers must take care of entering correct product ids). Then customers can add their information and queries as asked, 
- If any query has invalid product id, that query is skipped and a message is shown on the screen.
- If any query is out of customer's budget, its rejected immediately and a message is shown on the screen.
- Also if no queries of customer can be accepted due to above reasons, a message is shown on the screen.
- Then the filtered queries are sorted based on payoff value per cost paid (selling price * quantity asked) so that payoff value is maximised.
- Now based on budget of the customer- every query is processed, if low budget for some query, a message is shown on the screen.
- Now if the required quantity is in the stock, the stock is updated and sales and profit are updated too.
- If not, then we restock.
- Now, we have two options, restocking(only what is required by the customer and less in the stock) can be done from profit, a message is displayed on screen and stock, profit, sales updated accordingly.
- Next is not enough money for restocking, so taking a loan- only for the amount less in the profit, updating variables accordingly and displaying a message.
- Next when its the end of the day, or no new customer- We print the transaction log and summary details.

****Ques 2:****

I could accomplish this problem in **TC- O(n. log n)** and **SC- O(n)**.
O(n) could have been done if order was sorted.

Let the vector of elements be arr. Also I created another vector (dp) for storing the increasing subsequence vector that has the smallest value of last element (might not be the only vector of elements).
I iterated over all elements of vector arr and found the first element thats not less than (equal or greater than) arr[i]. 
If not found- then the arr element is pushed, else if lower bound is found then it is replaced- to maintain smallest possible tail of the vector- so that length can be made maximum. 

****Ques 3:****

I could accomplish this problem in **TC- O(n+k)** and **SC- O(k)**, where k is maximum element.
Find maximum element in the vector and make a dp array for counting number of elements from 0 to maximum element. Then based on this dp array, replace the elements in original array to make it in sorted order.
