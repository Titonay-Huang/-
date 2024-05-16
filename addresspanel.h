#include <cstdio>
#include <string.h>
#define ERROR -1
#define OK 1
#define MAX_LENGTH 50
#define MAX_USERS 1000

typedef struct people
                                                                                                                                                                                                                                                                                                                 {
    char number[MAX_LENGTH];
    char name[MAX_LENGTH];
    char category[MAX_LENGTH];
    char phone[MAX_LENGTH];
    char qq[MAX_LENGTH];
    char email[MAX_LENGTH];
    char places[MAX_LENGTH];
    struct people *next;
}Address;

int i=0, Number[MAX_USERS];

Address *S=new Address;

void GetNumber0()
{
    FILE *fp;
    char temp[MAX_LENGTH];
    int a;

    fp = fopen("number", "r");
    while(fgets(temp, MAX_LENGTH, fp)!=NULL)
    {
        temp[strlen(temp)-1] = '\0';
        sscanf(temp, "%d", &a);
        Number[a] = 1;
    }
    fclose(fp);

    i=0;
    while(Number[i]!=0) i++;
}

int EnterStruct(Address *P, Address *p)  //默认是按名字顺序排列
{
    Address *q, *e;
    q=new Address;
    q=P->next; e=P;

    if(P->next==NULL) P->next = p;
    else
    {
        while(q!=NULL)
        {
            if(strcmp(p->name, q->name)<0) break;
            e=q;
            q=q->next;
        }
        if(q==NULL) e->next=p;
        else
        {
            p->next = q;
            e->next=p;
        }
    }

    return OK;
}

int LoadStruct(Address *P)
{
    int flag=0;
    if(P->next==NULL)
    {
        printf("\n        < 目前暂未保存任何联系人信息 >\n");
        return ERROR;
    }
    Address *p;
    p=P->next;
    printf("        ----------------------------------\n");
    while(p!=NULL)
    {
        printf("\n");
        printf("        编号：%s\n", p->number);
        printf("        姓名：%s\n", p->name);
        printf("        标签：%s\n", p->category);
        printf("        手机号码：%s\n", p->phone);
        printf("        QQ号码：%s\n", p->qq);
        printf("        邮箱地址：%s\n", p->email);
        printf("        家庭住址：%s\n", p->places);
        printf("\n");
        flag++;
        p=p->next;
    }
    printf("        ----------------------------------\n");
    printf("        共有(符合条件） %d 个联系人信息，按名字顺序排序", flag);
    return OK;
}

int OutputNode(Address *p)
{
    printf("\n");
    printf("        编号：%s\n", p->number);
    printf("        姓名：%s\n", p->name);
    printf("        标签：%s\n", p->category);
    printf("        手机号码：%s\n", p->phone);
    printf("        QQ号码：%s\n", p->qq);
    printf("        邮箱地址：%s\n", p->email);
    printf("        家庭住址：%s\n", p->places);
    printf("\n");
    return OK;
}

int LoadName(Address *P)
{
    int flag=0;
    if(P->next==NULL)
    {
        printf("\n        < 目前暂未保存任何联系人信息 >\n");
        return ERROR;
    }
    printf("        名单如下：\n");
    Address *p;
    p=P->next;
    printf("        ----------------------------------\n");
    while(p!=NULL)
    {
        printf("        * %s *\n", p->name);
        flag++;
        p=p->next;
    }
    printf("        ----------------------------------\n");
    printf("        共有(符合条件） %d 个联系人信息，按名字顺序排序", flag);
    return OK;
}

int RefreshStruct(Address *P)
{
     Address *p;

     FILE *fp, *fpnumber;
     char temp[MAX_LENGTH];
     fp = fopen("number", "r");
     if(fp==NULL)
     {
         fclose(fp);
         return ERROR;
     }
     while(fgets(temp, MAX_LENGTH, fp)!=NULL)
     {
         p=new Address;
         temp[strlen(temp)-1] = '\0';
         fpnumber = fopen(temp, "r");
         if(fpnumber==NULL)
         {
             fclose(fpnumber);
             break;
         }
         fgets(temp, MAX_LENGTH, fpnumber);
         temp[strlen(temp)-1] = '\0';
         strcpy(p->number, temp);

         fgets(temp, MAX_LENGTH, fpnumber);
         temp[strlen(temp)-1] = '\0';
         strcpy(p->name, temp);

         fgets(temp, MAX_LENGTH, fpnumber);
         temp[strlen(temp)-1] = '\0';
         strcpy(p->category, temp);

         fgets(temp, MAX_LENGTH, fpnumber);
         temp[strlen(temp)-1] = '\0';
         strcpy(p->phone, temp);

         fgets(temp, MAX_LENGTH, fpnumber);
         temp[strlen(temp)-1] = '\0';
         strcpy(p->qq, temp);

         fgets(temp, MAX_LENGTH, fpnumber);
         temp[strlen(temp)-1] = '\0';
         strcpy(p->email, temp);

         fgets(temp, MAX_LENGTH, fpnumber);
         temp[strlen(temp)-1] = '\0';
         strcpy(p->places, temp);

         p->next = NULL;

         fclose(fpnumber);
         EnterStruct(P, p);
     }
     fclose(fp);
     return OK;
}

int EnterAddress()
{
    FILE *fp;
    Address *p;
    p=new Address;
    char temp[MAX_LENGTH];

    if(Number[MAX_USERS-1]==1)
    {
        printf("通讯录已满，无法增加\n");
        return ERROR;
    }
    else
    {
        memset(Number, 0, sizeof(Number));
        GetNumber0();

        sprintf(temp, "%d", i);
        fp = fopen("number", "a+");
        fputs(temp, fp); fputc('\n', fp);
        fclose(fp);

        fp = fopen(temp, "w");

        fputs(temp, fp);
        fputc('\n', fp);

        printf("        请输入要添加的联系人的名字：");
        scanf("%s", p->name);
        getchar();
        fputs(p->name, fp);
        fputc('\n', fp);

        printf("        请输入要添加的联系人的分类(如家人，朋友，工作，客服, 自定义）：");
        scanf("%s", p->category);
        getchar();
        fputs(p->category, fp);
        fputc('\n', fp);

        printf("        请输入联系人手机号码（若无则填无）：");
        scanf("%s", p->phone);
        getchar();
        fputs(p->phone, fp);
        fputc('\n', fp);

        printf("        请输入联系人qq号码（若无则填无）：");
        scanf("%s", p->qq);
        getchar();
        fputs(p->qq, fp);
        fputc('\n', fp);

        printf("        请输入联系人邮箱地址（若无则填无）：");
        scanf("%s", p->email);
        getchar();
        fputs(p->email, fp);
        fputc('\n', fp);

        printf("        请输入联系人家庭住址（若无则填无）：");
        scanf("%s", p->places);
        getchar();
        fputs(p->places, fp);
        fputc('\n', fp);

        p->next = NULL;
        EnterStruct(S, p);

        fclose(fp);

        Number[i] = 1;
        printf("\n        < 添加成功 >\n");
    }
}

int VerifyName(char comp[], char getstr[])
{
    int i, j;
    i=j=0;
    if(comp[i]<0 && getstr[j]<0)
    {
        while(i<strlen(comp) && j<strlen(getstr))
        {
            if(comp[i]==getstr[j] && comp[i+1]==getstr[j+1]) {i+=2; j+=2;}
            else j+=2;
            if(i==strlen(comp) && j<=strlen(getstr)) return OK;
            else if(i<strlen(comp) && j==strlen(getstr)) return ERROR;
        }
    }

    else if(comp[i]>0 && getstr[j]>0)
    {
        while(i<strlen(comp) && j<strlen(getstr))
        {
            if(comp[i]==getstr[j]) {i++; j++;}
            else j++;
            if(i==strlen(comp) && j<strlen(getstr) || i==strlen(comp) && j==strlen(getstr)) return OK;
            else if(i<strlen(comp) && j==strlen(getstr)) return ERROR;
        }
    }
}

int VerifyPhone(char comp[], char getstr[])
{
    int i=0, j=0;
    while(i<strlen(comp) && j<strlen(getstr))
    {
        if(comp[i]==getstr[j]) {i++; j++;}
        else return ERROR;
        if(i==strlen(comp) && j<strlen(getstr) || i==strlen(comp) && j==strlen(getstr)) return OK;
        else if(i<strlen(comp) && j==strlen(getstr)) return ERROR;
    }
}

int ElasticAddress(Address *P, char input[])
{
    int flag=0;
    Address *p;
    p=P->next;
    printf("        ----------------------------------\n");
    while(p!=NULL)
    {
        if(VerifyName(input, p->name)==1)
        {
           OutputNode(p);
            flag++;
        }
        p=p->next;
    }
    printf("        ----------------------------------\n");
    printf("        共有(符合条件） %d 个联系人信息，按名字顺序排序", flag);
    if(flag==0)
    {
        printf("\n        < 找不到对应的联系人 >\n");
        return ERROR;
    }
    return OK;
}

int PhoneSearch(Address *P, char input[])
{
    int flag=0;
    Address *p;
    p=P->next;
    printf("        ----------------------------------\n");
    while(p!=NULL)
    {
        if(VerifyPhone(input, p->phone)==1)
        {
           OutputNode(p);
            flag++;
        }
        p=p->next;
    }
    printf("        ----------------------------------\n");
    printf("        共有(符合条件） %d 个联系人信息，按名字顺序排序", flag);
    if(flag==0)
    {
        printf("\n        < 找不到对应的联系人 >\n");
        return ERROR;
    }
    return OK;
}

int ModifyAddress(Address *P)
{
    FILE *fp;
    Address *p;
    char temp[MAX_LENGTH];
    printf("\n\n        请正确输入联系人所对应的编号以确认修改：");
    scanf("%s", temp);
    getchar();

    fp = fopen(temp, "w");
    p=P->next;

    while(p!=NULL)
    {
        if(strcmp(p->number, temp)==0) break;
        p=p->next;
    }

    fputs(temp, fp);
    fputc('\n', fp);

    printf("        请重新输入联系人的名字：");
    scanf("%s", temp);
    getchar();
    strcpy(p->name, temp);
    fputs(temp, fp);
    fputc('\n', fp);

    printf("        请重新输入联系人分类：");
    scanf("%s", temp);
    getchar();
    strcpy(p->category, temp);
    fputs(temp, fp);
    fputc('\n', fp);

    printf("        请重新输入11位手机号码（若无则填无）：");
    scanf("%s", temp);
    getchar();
    strcpy(p->phone, temp);
    fputs(temp, fp);
    fputc('\n', fp);

    printf("        请重新输入qq号码（若无则填无）：");
    scanf("%s", temp);
    getchar();
    strcpy(p->qq, temp);
    fputs(temp, fp);
    fputc('\n', fp);

    printf("        请重新输入邮箱地址（若无则填无）：");
    scanf("%s", temp);
    getchar();
    strcpy(p->email, temp);
    fputs(temp, fp);
    fputc('\n', fp);

    printf("        请重新输入家庭住址（若无则填无）：");
    scanf("%s", temp);
    getchar();
    strcpy(p->places, temp);
    fputs(temp, fp);
    fputc('\n', fp);

    fclose(fp);

    return OK;
}

int Delfilestr(FILE *file, char delstr[])
{
    FILE *fp;
    fp = fopen("channel", "w");
    char getstr[MAX_LENGTH];
    while(fgets(getstr, MAX_LENGTH, file) != NULL)
    {
        getstr[strlen(getstr)-1] = '\0';
        if(strcmp(getstr, delstr)!=0)
        {
             fputs(getstr, fp);
             fputc('\n', fp);
        }
        memset(getstr,'\0',sizeof(getstr));
    }
    fclose(fp);

    return OK;
}

int DelAddress(Address *P)
{
    FILE *fp;
    Address *p, *e;
    char temp[MAX_LENGTH];
    printf("\n\n        请再次输入联系人所对应的编号以确认删除：");
    scanf("%s", temp);
    getchar();

    e=P; p=P->next;
    while(p!=NULL)
    {
        if(strcmp(p->number, temp)==0) break;
        e=p;
        p=p->next;
    }
    e->next = p->next;

    if(remove(temp)!=0)
    {
        printf("\n        < 删除失败 >\n");
        return ERROR;
    }

    fp = fopen("number", "r");
    Delfilestr(fp, temp);
    fclose(fp);

    if(remove("number")!=0)
    {
        printf("\n        < 删除失败 >\n");
        return ERROR;
    }
    rename("channel", "number");

    printf("\n        < 删除成功 >\n");

    return OK;
}

int CheckNewCategory(char test[])
{
    FILE *fp;
    char temp[MAX_LENGTH];
    fp = fopen("channel", "a+");
    while(fgets(temp, MAX_LENGTH, fp)!=NULL)
    {
        temp[strlen(temp)-1] = '\0';
        if(strcmp(temp, test)==0)
        {
            fclose(fp);
            return ERROR;
        }
    }
    fputs(test, fp);
    fputc('\n', fp);
    fclose(fp);
    return OK;
}

int RefreshCategory(Address *P)
{
    Address *p;

    p=P->next;
    while(p!=NULL)
    {
        CheckNewCategory( p->category);
        p=p->next;
    }
    remove("category");
    rename("channel", "category");
    return OK;
}

int CategoryMenu(Address *P)
{
    FILE *fp;
    Address *p;
    int flag=0;
    char temp[MAX_LENGTH];
    p=P->next;
    printf("        存在的分类如下：\n\n");
    fp=fopen("category", "r");
    while(fgets(temp, MAX_LENGTH, fp)!=NULL)
    {
        temp[strlen(temp)-1] = '\0';
        printf("        * %s *\n", temp);
        flag++;
    }
    printf("        共有 %d 种分类\n\n", flag);
    fclose(fp);
    printf("        请输入你要查看的分类：");
    scanf("%s", temp);
    getchar();
    flag=0;
    printf("        ----------------------------------\n");
    while(p!=NULL)
    {
        if(strcmp(temp, p->category)==0)
        {
            OutputNode(p);
            flag++;
        }
        p=p->next;
    }
    printf("        ----------------------------------\n");
    printf("        共有(符合条件） %d 个联系人信息，按名字顺序排序", flag);
    return OK;
}
