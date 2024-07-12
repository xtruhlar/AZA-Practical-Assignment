# AZA-Practical-Assignment

Tasks:
1. Design and implement an algorithm to solve a problem for scheduling with deadlines (Algorithm 4.4).
![image](https://github.com/user-attachments/assets/c4beac9a-c96b-4742-ba8d-da753d55560f)

Table 1.1. Consider the following jobs, deadlines, and profits, and use the scheduling with deadlines algorithm to maximize the total profit. Show the optimal sequence of jobs with max profit on the screen.

![image](https://github.com/user-attachments/assets/eadab862-4f7d-4e02-8599-e7f68416bb18)

2. Consider the procedure schedule in the Scheduling with Deadlines algorithm (Algorithm 4.4). Let d be the maximum of the deadlines for n jobs. Modify the procedure so that it adds a job as late as possible to the schedule being built, but no later than its deadline. Do this by initializing d+1 disjoint sets, containing the integers 0, 1, ..., d. Let small(S) be the smallest member of set S. When a job is scheduled, find the set S containing the minimum of its deadline and n. If small(S) = 0, reject the job. Otherwise, schedule it at time small(S), and
merge S with the set containing small(S)−1.
Assuming we use Disjoint Set Data Structure III in Appendix C, show that this version is θ(nlgm), where m is the minimum of d and n.

3. Suppose we assign n persons to n jobs. Let Cij be the cost of assigning the ith person to the jth job.
a.
Use a greedy approach to write an algorithm that finds an assignment that minimizes the total cost of assigning all n persons to all n jobs. Analyze your algorithm and show the results using order notation.
b.
Use the dynamic programming approach to write an algorithm for the same problem. Analyze your algorithm and show the results using order notation.
![image](https://github.com/user-attachments/assets/cbc0c9ed-eb56-4d5f-a982-d0fbbc367900)

