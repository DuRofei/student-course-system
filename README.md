# student-course-system
实现简单的学生、课程数据录入（从文件录入和从键盘录入），查询，分页浏览功能。

## 实现

* 学生、课程数据录入（从文件录入和从键盘录入
* 查询
* 分页浏览

## 使用
**先将存储数据的 stuinfo.txt 和 courseinfo.txt 的路径替换为自己的路径。**
### MAC
####方式1： 
* 新建 xcode c 语言工程，将代码粘贴到 main.c 文件中运行即可。

####方式2： 
* 1.打开终端 cd 到当前目录，执行 `$gcc -o main main.c` 
*  2.`$./main`

####方式3： 
* 1.打开终端 cd 到当前目录，执行 `$gcc main.c` 
* 2.`$./a.out`

### Windows
* 1.修改代码中的`system("clear")`为`system("cls")`。
*  2.打开命令 cd 到当前目录，执行 `$gcc main.c`。
*  3.`$./a.exe`
