# Sign Test

What is the sign test?
The sign test is a statistical test for consistent differences between pairs of observations, such as subjects' weight before and after treatment. Given pairs of observations (such as weight pre- and post-treatment) for each subject, the sign test determines if one member of the pair (such as pre-treatment) tends to be greater than (or less than) the other member of the pair (such as post-treatment).
The sign test can also test if the median of a collection of numbers is significantly greater than or less than a specified value. For example, given a list of student grades in a class, the sign test can determine if the median grade is significantly different from, say, 75 out of 100.

The code itself is two parts a Python API file to get the normal and binomial table values as needed in the test, and the test itself using C++.

**To use it first run the Python server using this command in the terminal**

```fastapi dev distribution_api.py```

**Then run the C++ file and follow the steps below**

Steps to solve the sign test using my code:
1.	Type “yes” if it’s a paired test else type “no”
2.	Then enter the sample size (N)
3.	Then enter the alpha (level of significance)
4.	Then enter the sample values if it’s a paired test input the before value first then the after value second as pairs ex: (x y) where x is the before value and y is the after value
5.	Then it will ask you which type of test to do ex: (>, < , ≠) after that the program will choose the appropriate rule and make a call to the API to get the respected value depending on the size of the sample if its greater than or equal to 20 it will choose the rules for the normal distribution else it will choose the rules for the binomial table
6.	Lastly it will print out the decision rule it chose and the decision itself
