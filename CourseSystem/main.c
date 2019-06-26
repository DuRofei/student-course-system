//
//  main.c
//  CourseSystem
//
//  Created by DuRofei on 2019/6/26.
//  Copyright © 2019 DuRofei. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct CourseInfo {
    char courseCode[10];//课程编号
    char courseName[20];//课程名称
    char courseType[10];//课程类别
    int totalPeriod;//总学时
    int classPeriod;//授课学时
    int experiPeriod;//上级学时
    float creditHour;//学分
    int term;//开课学期
} ;

struct StuCourInfo {
    int stuNo;//学号
    char courseCode[10];//课程编号
} ;

struct CourseInfo *courseInfos[1];
struct StuCourInfo *stuCourInfos[1];

//读取学生信息
void readStuInfosNext(int count, int page) {
    printf("\n---------------------\n");
    printf("学号\t课程编号\n");
    for (int p = 0; p < 10 && p < count; p ++) {
        if (page == count/10) {
            if (p > count%10-1) {
                break;
            }
        }
        struct StuCourInfo *p0 = stuCourInfos[page*10+p];
        printf("%d\t%s\n",p0->stuNo,p0->courseCode);
    }
    printf("当前为第%d 页，共%d 页\n",page+1,(count/10)+1);
    printf("---------------------\n");
    int x;
    if (page > 0) {
        printf("\t1.查看上一页\n");
    }
    if (page < count/10) {
        printf("\t2.查看下一页\n");
    }
    if (count > 10) {
        printf("\t3.返回主菜单\n");
        printf("\n请选择:");
        scanf("%d", &x);
        switch (x)
        {
            case 1:
                if (page > 0) {
                    page --;
                    readStuInfosNext(count, page);
                }
                break;
            case 2:
                if (page < count/10) {
                    page ++;
                    readStuInfosNext(count, page);
                }
                break;
            case 3:
                break;
        }
    }
}

void readStuInfos() {
    FILE *fp;
    if ((fp = fopen("/users/durofei/desktop/coursesystem/coursesystem/stuinfo.txt", "r")) == NULL)
    {
        printf("\n 无法读取!");
        exit(0);
    }
    int i = 0, page = 0;

    while(!feof(fp))                     //读取一组数据后指针指向下一组数据，并且判断是否指向最后一行
    {
        struct StuCourInfo *temp = (struct StuCourInfo *)malloc(sizeof(struct StuCourInfo));
        fscanf(fp,"%d\t%s",&temp->stuNo,temp->courseCode);
        if (temp->stuNo == 0) {
            break;
        }

        stuCourInfos[i] = temp;
        i++;
    }

    readStuInfosNext(i, page);
    
    fclose(fp);
}

//存储学生信息
void storeStuInfos(struct StuCourInfo *p1) {
    FILE *fp;
    if ((fp = fopen("/users/durofei/desktop/coursesystem/coursesystem/stuinfo.txt", "a")) == NULL)
    {
        printf("\n 无法储存!");
        exit(0);
    }
    
    fprintf(fp, "%d\t%s\n", p1->stuNo, p1->courseCode);

    fclose(fp);
    printf("已储存入文件!\n");
}

//读取课程信息
void readCourseInfosNext(int count, int page) {
    printf("\n-------------------------------------------------------------------------------\n");
    printf("课程编号\t课程名称\t课程类别\t总学时\t授课学时\t上机学时\t学分\t开课学期\n");
    for (int p = 0; p < 10 && p < count; p ++) {
        if (page == count/10) {
            if (p > count%10-1) {
                break;
            }
        }
        struct CourseInfo *p0 = courseInfos[page*10+p];
        printf("%s\t%s\t%s\t%d\t%d\t%d\t%f\t%d\n", p0->courseCode, p0->courseName, p0->courseType, p0->totalPeriod, p0->classPeriod, p0->experiPeriod, p0->creditHour, p0->term);
    }
    printf("当前为第%d 页，共%d 页\n",page+1,(count/10)+1);
    printf("-------------------------------------------------------------------------------\n");
    int x;
    if (page > 0) {
        printf("\t1.查看上一页\n");
    }
    if (page < count/10) {
        printf("\t2.查看下一页\n");
    }
    if (count > 10) {
        printf("\t3.返回主菜单\n");
        printf("\n请选择:");
        scanf("%d", &x);
        switch (x)
        {
            case 1:
                if (page > 0) {
                    page --;
                    readCourseInfosNext(count, page);
                }
                break;
            case 2:
                if (page < count/10) {
                    page ++;
                    readCourseInfosNext(count, page);
                }
                break;
            case 3:
                break;
        }
    }
    
}

void readCourseInfos() {
    FILE *fp;
    if ((fp = fopen("/users/durofei/desktop/coursesystem/coursesystem/courseinfo.txt", "r")) == NULL)
    {
        printf("\n 无法读取!");
        exit(0);
    }
    int i = 0, page = 0;
    
    while(!feof(fp))                     //读取一组数据后指针指向下一组数据，并且判断是否指向最后一行
    {
        struct CourseInfo *temp = (struct CourseInfo *)malloc(sizeof(struct CourseInfo));
        fscanf(fp,"%s\t%s\t%s\t%d\t%d\t%d\t%f\t%d", temp->courseCode, temp->courseName, temp->courseType, &temp->totalPeriod, &temp->classPeriod, &temp->experiPeriod, &temp->creditHour, &temp->term);
        if (strlen(temp->courseCode) == 0) {
            break;
        }
        
        courseInfos[i] = temp;
        i++;
    }
    
    readCourseInfosNext(i, page);
    
    fclose(fp);
}

//存储课程信息
void storeCourseInfos(struct CourseInfo *p1) {
    FILE *fp;
    if ((fp = fopen("/users/durofei/desktop/coursesystem/coursesystem/courseinfo.txt", "a")) == NULL)
    {
        printf("\n 无法储存!");
        exit(0);
    }
    
    fprintf(fp, "%s\t%s\t%s\t%d\t%d\t%d\t%f\t%d\n", p1->courseCode, p1->courseName, p1->courseType, p1->totalPeriod, p1->classPeriod, p1->experiPeriod, p1->creditHour, p1->term);
    
    fclose(fp);
    printf("已储存入文件!\n");
}

//信息浏览
void scanInfo() {
    int i;
    printf("信息浏览\n");
    printf("\t1.浏览学生信息\n");
    printf("\t2.浏览课程信息\n");
    printf("\t3.返回主菜单\n");
    printf("\n请选择1-3:");
    scanf("%d", &i);
    switch (i)
    {
        case 1:
            readStuInfos();
            break;
        case 2:
            readCourseInfos();
            break;
        case 3:
            break;
    }
}

//信息查询
void queryStuInfo() {
    int a,i = 0;
    struct StuCourInfo *p;
    printf("请输入学生编号:");
    scanf("%d", &a);

    printf("学号\t课程编号\n");
    readStuInfos();

    while (stuCourInfos[i] != NULL)
    {
        p = stuCourInfos[i];
        if (p->stuNo == a) {
            printf("%d %s\n",p->stuNo,p->courseCode);
        }
        i ++;
    }
}

void queryCourseInfo() {
    int a,i = 0;
    struct CourseInfo *p;
    printf("请输入课程编号:");
    scanf("%d", &a);
    
    printf("课程编号\t课程名称\t课程类别\t总学时\t授课学时\t上机学时\t学分\t开课学期\n");
    readCourseInfos();
    
    while (courseInfos[i] != NULL)
    {
        p = courseInfos[i];
        if ((int)p->courseCode == a) {
            printf("%s\t%s\t%s\t%d\t%d\t%d\t%f\t%d\n", p->courseCode, p->courseName, p->courseType, p->totalPeriod, p->classPeriod, p->experiPeriod, p->creditHour, p->term);
        }
        i ++;
    }
}

void queryInfo() {
    int i;
    printf("信息查询\n");
    printf("\t1.查询学生信息\n");
    printf("\t2.查询课程信息\n");
    printf("\t3.返回主菜单\n");
    printf("\n请选择1-3:");
    scanf("%d", &i);
    switch (i)
    {
        case 1:
            queryStuInfo();
            break;
        case 2:
            queryCourseInfo();
            break;
        case 3:
            break;
    }
}


//信息录入
void inputStuInfoByKeyboard() {
    struct StuCourInfo *p1;
    p1 = (struct StuCourInfo *)malloc(sizeof(struct StuCourInfo));
    printf("学号\t课程编号\n");
    scanf("%d %s", &p1->stuNo, p1->courseCode);
    int count=0;
    while(stuCourInfos[count++] != '\0');
    if (count == 1) {
        stuCourInfos[0] = p1;
    } else {
        stuCourInfos[count-1] = p1;
    }

    storeStuInfos(p1);
    
    int i;
    printf("\t1.继续录入\n");
    printf("\t2.返回主菜单\n");
    printf("\n请选择1-2:");
    scanf("%d", &i);
    switch (i) {
        case 1:
            inputStuInfoByKeyboard();
            break;
        case 2:
            break;
    }
}

void inputStuInfoByFile() {
//    /users/durofei/desktop/coursesystem/coursesystem/temp.txt
    FILE *fp;
    char filepath[200];

    printf("请输入您要读取的路径:\n");
    getchar();

    scanf("%s", filepath);
    if ((fp = fopen(filepath, "r")) == NULL)
    {
        printf("找不到 %s 文件!\n", filepath);
        exit(0);
    }
    int i=0,j;
    
    while(!feof(fp))                     //读取一组数据后指针指向下一组数据，并且判断是否指向最后一行
    {
        struct StuCourInfo *temp = (struct StuCourInfo *)malloc(sizeof(struct StuCourInfo));
        fscanf(fp,"%d\t%s",&temp->stuNo,temp->courseCode);
        if (temp->stuNo == 0) {
            return;
        }
        
        stuCourInfos[i] = temp;
        i++;
    }
    j = i;
    for (int i = 0; i < j; i ++) {
        struct StuCourInfo *p0 = stuCourInfos[i];
        printf("\n%d\t%s\n",p0->stuNo,p0->courseCode);
        storeStuInfos(p0);
    }
    fclose(fp);
}

void inputStuInfo() {
    int i;
    printf("录入学生信息\n");
    printf("\t1.从键盘录入\n");
    printf("\t2.从文件录入\n");
    printf("\t3.返回主菜单\n");
    printf("\n请选择1-3:");
    scanf("%d", &i);
    switch (i)
    {
        case 1:
            inputStuInfoByKeyboard();
            break;
        case 2:
            inputStuInfoByFile();
            break;
        case 3:
            break;
    }
}

void inputCourseInfoByKeyboard() {
    struct CourseInfo *p1;
    p1 = (struct CourseInfo *)malloc(sizeof(struct CourseInfo));
    printf("课程编号\t课程名称\t课程类别\t总学时\t授课学时\t上机学时\t学分\t开课学期\n");
    scanf("%s\t%s\t%s\t%d\t%d\t%d\t%f\t%d", p1->courseCode, p1->courseName, p1->courseType, &p1->totalPeriod, &p1->classPeriod, &p1->experiPeriod, &p1->creditHour, &p1->term);
    
    int count=0;
    while(courseInfos[count++] != '\0');
    if (count == 1) {
        courseInfos[0] = p1;
    } else {
        courseInfos[count-1] = p1;
    }
    
     storeCourseInfos(p1);
    
    int i;
    printf("\t1.继续录入\n");
    printf("\t2.返回主菜单\n");
    printf("\n请选择1-2:");
    scanf("%d", &i);
    switch (i)
    {
        case 1:
            inputCourseInfoByKeyboard();
            break;
        case 2:
            break;
    }
    
}

void inputCourseInfoByFile() {
    FILE *fp;
    char filepath[200];
    
    printf("请输入您要读取的路径:\n");
    getchar();
    
    scanf("%s", filepath);
    if ((fp = fopen(filepath, "r")) == NULL)
    {
        printf("找不到 %s 文件!\n", filepath);
        exit(0);
    }
    int i=0,j;
    
    while(!feof(fp))                     //读取一组数据后指针指向下一组数据，并且判断是否指向最后一行
    {
        struct CourseInfo *temp = (struct CourseInfo *)malloc(sizeof(struct CourseInfo));
        fscanf(fp,"%s\t%s\t%s\t%d\t%d\t%d\t%f\t%d", temp->courseCode, temp->courseName, temp->courseType, &temp->totalPeriod, &temp->classPeriod, &temp->experiPeriod, &temp->creditHour, &temp->term);
        if (strlen(temp->courseCode) == 0) {
            return;
        }
        
        courseInfos[i] = temp;
        i++;
    }
    j = i;
    for (int i = 0; i < j; i ++) {
        struct CourseInfo *p0 = courseInfos[i];
        printf("\n%s\t%s\t%s\t%d\t%d\t%d\t%f\t%d\n", p0->courseCode, p0->courseName, p0->courseType, p0->totalPeriod, p0->classPeriod, p0->experiPeriod, p0->creditHour, p0->term);
        storeCourseInfos(p0);
    }
    fclose(fp);
}

void inputCourseInfo() {
    int i;
    printf("录入课程信息\n");
    printf("\t1.从键盘录入\n");
    printf("\t2.从文件录入\n");
    printf("\t3.返回主菜单\n");
    printf("\n请选择1-3:");
    scanf("%d", &i);
    switch (i)
    {
        case 1:
            inputCourseInfoByKeyboard();
            break;
        case 2:
            inputCourseInfoByFile();
            break;
        case 3:
            break;
    }
}

void inputInfo() {
    int i;
    printf("信息输入\n");
    printf("\t1.录入学生信息\n");
    printf("\t2.录入课程信息\n");
    printf("\t3.返回主菜单\n");
    printf("\n请选择1-3:");
    scanf("%d", &i);
    switch (i)
    {
        case 1:
            inputStuInfo();
            break;
        case 2:
            inputCourseInfo();
            break;
        case 3:
            break;
    }
}

//主函数
int main(int argc, const char * argv[]) {
    // insert code here...
    char m;
    int i;
start:
    printf("\n************************************************\n");
    printf("\n");
    printf("菜单:\n");
    printf("\t1.信息录入\n");
    printf("\t2.信息查询\n");
    printf("\t3.信息浏览\n");
    printf("\t4.退出系统");
    printf("\n请输入1-4:\n");
    
    if (scanf("%d", &i))
    {
        if (i < 1 || i > 4)
        {
            printf("请重新输入:\n");
            goto start;
        }
    } else {
        if (scanf("%c", &m))
        {
            printf("输入错误，请重新输入:\n");
            goto start;
        }
    }
    
    switch (i)
    {
        case 1:
            system("clear");
            inputInfo();
            goto start;
            break;
        case 2:
            system("clear");
            queryInfo();
            goto start;
            break;
        case 3:
            system("clear");
            scanInfo();
            goto start;
            break;
        case 4:
        {
            system("clear");
            printf("\n谢谢使用！");
        }
    }
    return 0;
}


