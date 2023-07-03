# Personal Diary
Hello, there somrthing about my Assignment-004 "Personal Diary" you maybe interested in.  
## Files  
There are files:  
* diary.cpp 
* pdadd.cpp
* pdlist.cpp
* pdremove.cpp
* pdshow.cpp
* pdadd.h
* pdlist.h
* pdremove.h
* pdshow.h
* CMakeLists.txt
* diary.txt
* diary.bush
* images
* README.md

## Input
There five command you can input in total, they are:
* Usage: usage
* Add: add <filename\>
* Show: show <filename\> <date\>
* Remove: remove <filename\> <date\>
* List: list <filename\> <start\>(optional) <end\>(optional)

## Demo
In order to operate the Personal Diary more efficiently, I wrote diary.bash. You can run it to test the correctness of this software.
Now, we have the diary.txt contains:
```
2023-04-01
Hello.
2023-04-03
My name is Yichi Zhang. 
2023-04-05
I am an undergradute in ZJU.
2023-04-06
My major is Information Engineering.
2023-04-07
I am interested in Machine Learning,
which sounds really cool.
2023-04-11
I have create my Homepage.
yichics@github.io
```    
We input the command below in the terminal to start the script. 
```
bash diary.bash               
```
![result0](images/pic0.png)

Look up the usage.
```
usage
```
![result1](images/pic1.png)

Try to add a new diary.
```
add diary.txt

Welcome to my Homepage.
.
```
![result2](images/pic2.png)

Try to replace the new diary.
```
add diary.txt

Welcome to my Homepage.
:D
.
```
![result3](images/pic3.png)

Try to list all the diary. 
```
list diary.txt
```
![result4](images/pic4.png)

Try to list the diary after 2023-04-03. 
```
list diary.txt 2023-04-03
```
![result5](images/pic5.png)

Try to list the diary before 2023-04-07. 
```
list diary.txt 2023-04-01 2023-04-07
```
![result6](images/pic6.png)  

Try to list the diary between 2023-04-03 and 2023-04-06. 
```
list diary.txt 2023-04-03 2023-04-06
```
![result7](images/pic7.png) 

Try to show the diary on 2023-04-23. 
```
show diary.txt 2023-04-11
```
![result8](images/pic8.png) 

Try to remove the diary on 2023-04-06
```
remove diary.txt 2023-04-06
```
![result9](images/pic9.png) 

Finally, quit the script.
```
quit
```
![result10](images/pic10.png) 

## Limitation
* The date you input must be "YYYY-MM-DD".
* Can't identify the date exits or not.
* Only support the diary replace.
* Only support add the diary today.
* Don't support changing the diary.
* Something not found yet.  

## Something else
* You may need to make the diary.txt diary.bash and the executable file named "diary" in the same file to run the diary.bash correctly.
* You may attention the output file's positon.
* If there are some bugs I haven't found, please email me at yichics02@gmail.com, your mail do give me a encourage to better work.  
* Wish you a nice day!