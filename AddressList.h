#include <cstdio>
#include <string.h>
#define ERROR -1
#define OK 1

char name[20];
char category[10];
char phone[11];
char qq[10];
char email[20];
char places[50];

int SearchAddress(char input[])
{
    printf("\n");
    FILE *fp;
    fp = fopen(input, "r");
    fgets(name, 20, fp);
    printf("        姓名：%s\n", name);
    fgets(category, 20, fp);
    printf("        标签：%s\n", category);
    fgets(phone, 20, fp);
    printf("        手机号码：%s\n", phone);
    fgets(qq, 20, fp);
    printf("        QQ号码：%s\n", qq);
    fgets(email, 20, fp);
    printf("        邮箱地址：%s\n", email);
    fgets(places, 50, fp);
    printf("        家庭住址：%s\n", places);
    fclose(fp);
    printf("\n");
    return OK;
}

int VerifyName(char name[], char getstr[])
{
    int i, j;
    i=j=0;
    while(i<strlen(name)-1 && j<strlen(getstr)-1)
    {
        if(name[i]==getstr[j])
        {
            i++; j++;
        }
        else j++;

        if(i==strlen(name)-1 && j<strlen(getstr)-1)
        {
            return OK;
        }
        else if(i<strlen(name)-1 && j==strlen(getstr)-1)
        {
            return ERROR;
        }
    }
}

int ElasticSearch(char input[])
{
    FILE *fp;
    fp = fopen("name.txt", "r");
    while(fgets(name, 20, fp)!=NULL)
    {
        if(VerifyName(input, name)==1)
        {
            SearchAddress(name);
        }
        printf("\n");
    }
    return OK;
}

int EnterAddress()
{
    FILE *fp;

    printf("        请输入要添加的联系人的类别标签(家人，朋友，工作，客服, 自定义）：");
    scanf("%s", category);
    getchar();
    printf("        请输入联系人的名字：");
    scanf("%s", name);
    getchar();
    if(strlen(name)==0)
    {
        printf("        联系人的名字是最基础的信息！");
        return ERROR;
    }

    fp = fopen("name.txt", "a+");
    if(fp==NULL) return ERROR;
    fputs(name, fp);
    fputc('\n', fp);
    fclose(fp);

    fp = fopen(category, "a+");
    if(fp==NULL) return ERROR;
    fputs(name, fp);
    fputc('\n', fp);
    fclose(fp);

    printf("        请输入11位手机号码（若无则填无）：");
    scanf("%s", phone);
    getchar();

    printf("        请输入qq号码（若无则填无）：");
    scanf("%s", qq);
    getchar();
    printf("        请输入邮箱地址（若无则填无）：");
    scanf("%s", email);
    getchar();
    printf("        请输入家庭住址（若无则填无）：");
    scanf("%s", places);
    getchar();


    fp = fopen(name, "a+");
    if(fp==NULL) return ERROR;

    fputs(name, fp);
    fputc('\n', fp);
    fputs(category, fp);
    fputc('\n', fp);
    fputs(phone, fp);
    fputc('\n', fp);
    fputs(qq, fp);
    fputc('\n', fp);
    fputs(email, fp);
    fputc('\n', fp);
    fputs(places, fp);
    fputc('\n', fp);
    fclose(fp);

    printf("\n        创建联系人成功！\n");
    return OK;
}

int ModifyAddress(char input[])
{
    FILE *fp;

    printf("        请重新输入联系人标签：");
    scanf("%s", category);
    getchar();
    printf("        请重新输入11位手机号码（若无则填无）：");
    scanf("%s", phone);
    getchar();

    printf("        请重新输入qq号码（若无则填无）：");
    scanf("%s", qq);
    getchar();
    printf("        请重新输入邮箱地址（若无则填无）：");
    scanf("%s", email);
    getchar();
    printf("        请重新输入家庭住址（若无则填无）：");
    scanf("%s", places);
    getchar();

    fp = fopen(input, "w");
    if(fp==NULL) return ERROR;
    fputs(input, fp);
    fputc('\n', fp);
    fputs(category, fp);
    fputc('\n', fp);
    fputs(phone, fp);
    fputc('\n', fp);
    fputs(qq, fp);
    fputc('\n', fp);
    fputs(email, fp);
    fputc('\n', fp);
    fputs(places, fp);
    fputc('\n', fp);
    fclose(fp);

    return OK;
}

int LoadAddress()
{
    FILE *fp;
    int Flag;
    Flag = 0;
    printf("\n");
    fp = fopen("name.txt", "r");
    if(fp==NULL)
    {
        printf("        此系统通讯录信息为空！\n");
        return 0;
    }
    while(fgets(name, 20, fp)!=NULL)
    {
        name[strlen(name)-1] = '\0';
        printf("        * %s *\n", name);
        Flag++;
    }
    if(Flag==0) printf("        此系统通讯录信息为空！\n");
    fclose(fp);
    return OK;
}
int Delfilestr(FILE *file, char delstr[])
{
    FILE *fp;
    fp = fopen("channel.txt", "w");
    if(fp == NULL) return ERROR;
    char getstr[20];
    while(fgets(getstr, 20, file) != NULL)
    {
        getstr[strlen(getstr)-1] = '\0';
        if(strcmp(getstr, delstr)!=0)
        {
             fputs(getstr, fp);
             fputc('\n', fp);
        }
    }
    fclose(fp);
}

int DelAddress()
{
    FILE *fp, *fpname, *fpcategory;
    int i;
    printf("        请输入你所要删除联系人的名字：");
    scanf("%s", name);
    fp = fopen(name, "r");
    fpname = fopen("name.txt", "r");

    if(fp==NULL || fpname==NULL)
    {
        printf("\n        此联系人的信息不存在！\n");
        return ERROR;
    }
    Delfilestr(fpname, name);
    fclose(fpname);
    remove("name.txt");
    rename("channel.txt", "name.txt");


    for(i=1; i<=2; i++)
        fgets(category, 20, fp);
    category[strlen(category)-1] = '\0';
    fpcategory = fopen(category, "r");
    if(fpcategory==NULL) return ERROR;
    Delfilestr(fpcategory, name);
    fclose(fpcategory);
    remove(category);
    rename("channel.txt", category);

    fclose(fp);
    remove(name);

    printf("\n        联系人删除成功！\n");
    return OK;
}


