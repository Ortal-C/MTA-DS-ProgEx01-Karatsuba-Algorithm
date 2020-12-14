# MTA-Data_Structure_Course-ProgEx01

Project summary: 
The program receives non-negative n  integer and 2 n-digits numbers x and y.
The program multiplies x and y and calculates the result in 3 ways:
       (1) Long multiplication
       (2) Karatsub'a algorithm (Recursive)
       (3) Karatsub'a algorithm (Iterative)

Comments + project-assumption:
(1) The printed-output should not contain leading zeros. However, the result-vector of each algorithm can contain leading zeros.
(2) Can use only with <iostream>, <vector>, <string> libraries (<chrono>, <fstream>, <iomanip> are used for measure time-complexity).
(3) main() is measuring each algorithm's time-complexity and write it into Measure.txt. 
(4) The given n which represents a number of digits can't include leading-zeros and characters that are not a digit.
    However, n can start with a space-character. 
(5) Each given factor would be a n-digit number and could be bigger than int, long int, etc.
