 Hello, here is my Student two homework.Something you may interested in is written below.
## Files
Three file is contained, the source code, the test file and this ReadMe file.
## Input
Sample Input:
```
Mike A 99 B 78 C 87
Hill A 21 B 74 C 33      
Anna A 56 B 45 C 12 D 98   
Bob  B 78 D 89   
Jay  A 88 C 89 E 65 D 90   
GSU D 88            dajsoi  9     jdoasi 78     
hdu dfrg 88 dhue 88 de 0  dejm4  5
poole A 85 F 88 E 89 

9
```
Sample Output:
```
How mant students do you want to inquire?
Enter here please :
9
Querying the grades of 9 students for you now.
Sorry, there is not have so many students. Output all the students instead.
no      name    A       B       C       D       E       dajsoi  jdoasi  dfrg    dhue    de      dejm4   F       average
1       Mike    99      78      87                                                                              88
2       Hill    21      74      33                                                                              42.6667
3       Anna    56      45      12      98                                                                      52.75
4       Bob             78              89                                                                      83.5
5       Jay     88              89      90      65                                                              83
6       GSU                             88              9       78                                              58.3333
7       hdu                                                             88      88      0       5               45.25
8       poole   85                              89                                                      88      87.3333
        average 69.8    68.75   55.25   91.25   77      9       78      88      88      0       5       88
        max     99      78      89      98      89      9       78      88      88      0       5       88
        min     21      45      12      88      65      9       78      88      88      0       5       88
 Wish you a nice day!
```
You can rewrite the tst file by your own, but there somthing you should pay attention to:  
* You should input the single student's grades in this order:
  ``` 
  name courseName courseGrade ...
  ```
  I have given 8 success example in the test data file. Please don't set a too long courseName which cause a ugly output.
* The program support you input any length of ' ' between the data, which don't do damage to the output. This will be comfortale for you to input.
* You are supposed to input the number of students you want to inquire when the program is running, if there don't exsist so many students, the program will output all the students instead.
## Output 
* The output contain the courses chosen by the chosen students instead of all the courses chosen by all the students. If one student don't choose the course, the grade below the course will be empty.
* All the average is the average of students who shoose the course. The max and the min are the same.  

## Something else
* if there are some bugs I haven't found, please email me at yichics02@gmail.com, your mail do give me a encourage to better work.  
* Wish you a nice day!