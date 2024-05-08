#include <cstdio>
#include <string.h>
#define ERROR -1
#define OK 1
#define MAX_LENGTH 50

char name[MAX_LENGTH];
char category[MAX_LENGTH];
char phone[MAX_LENGTH];
char qq[MAX_LENGTH];
char email[MAX_LENGTH];
char places[MAX_LENGTH];

int SearchAddress(char input[])
{
    printf("\n");
    FILE *fp;
    fp = fopen(input, "r");
    fgets(name, MAX_LENGTH, fp);
    name[strlen(name)-1] = '\0';
    printf("        姓名：%s\n", name);
    fgets(category, MAX_LENGTH, fp);
    category[strlen(category)-1] = '\0';
    printf("        标签：%s\n", category);
    fgets(phone, MAX_LENGTH, fp);
    phone[strlen(phone)-1] = '\0';
    printf("        手机号码：%s\n", phone);
    fgets(qq, MAX_LENGTH, fp);
    qq[strlen(qq)-1] = '\0';
    printf("        QQ号码：%s\n", qq);
    fgets(email, MAX_LENGTH, fp);
    email[strlen(email)-1] = '\0';
    printf("        邮箱地址：%s\n", email);
    fgets(places, MAX_LENGTH, fp);
    places[strlen(places)-1] = '\0';
    printf("        家庭住址：%s\n", places);
    fclose(fp);
    printf("\n");
    return OK;
}

int VerifyName(char comp[], char getstr[])
{
    int i, j;
    i=j=0;
    while(i<strlen(comp) && j<=strlen(getstr))
    {
        if(comp[i]<0 && getstr[j]<0)
        {
            if(comp[i]==getstr[j] && comp[i+1]==getstr[j+1])
                {i+=2; j+=2;}
        }
        else if(comp[i]>0 && getstr[j]>0)
        {
            if(comp[i]==getstr[j])
            {
                i+=2; j+=2;
            }
        }
        else j+=2;

        if(i==strlen(comp) && j<strlen(getstr) || i==strlen(comp) && j==strlen(getstr)) return OK;
        else if(i<strlen(comp) && j==strlen(getstr)) return ERROR;
    }
}

int ElasticSearch(char input[])
{
    FILE *fp;
    fp = fopen("name.txt", "r");
    while(fgets(name, MAX_LENGTH, fp)!=NULL)
    {
        name[strlen(name)-1] = '\0';
        if(VerifyName(input, name)==1)
        {
            SearchAddress(name);
        }
    }
    return OK;
}

int CheckNewCategory(char test[])
{
    FILE *fp;
    char temp[MAX_LENGTH];
    fp = fopen("category.txt", "r");
    if(fp==NULL) return ERROR;
    while(fgets(temp, MAX_LENGTH, fp)!=NULL)
    {
        temp[strlen(temp)-1] = '\0';
        if(strcmp(temp, test)==0) return ERROR;
    }
    fputs(temp, fp);
    fputc('\n', fp);
    fclose(fp);
    return OK;
}

int EnterAddress()
{
    FILE *fp;

    printf("        请输入要添加的联系人的类别标签(如家人，朋友，工作，客服, 自定义）：");
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

    CheckNewCategory(category);

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

    printf("\n         < 创建联系人成功 >\n");
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
        printf("\n        < 此系统通讯录信息为空 >\n");
        return 0;
    }
    printf("        系统内所有联系人如下：\n\n");
    while(fgets(name, MAX_LENGTH, fp)!=NULL)
    {
        name[strlen(name)-1] = '\0';
        printf("        * %s *\n", name);
        Flag++;
    }
    printf("\n        联系人共有 %d 个", Flag);
    if(Flag==0) printf("        < 此系统通讯录信息为空 >\n");
    fclose(fp);
    return OK;
}
int Delfilestr(FILE *file, char delstr[])
{
    FILE *fp;
    fp = fopen("channel.txt", "w");
    if(fp == NULL) return ERROR;
    char getstr[MAX_LENGTH];
    while(fgets(getstr, MAX_LENGTH, file) != NULL)
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
    char input[MAX_LENGTH];
    int i;
    printf("        请输入你所要删除联系人的名字：");
    scanf("%s", name);
    fp = fopen(name, "r");
    fpname = fopen("name.txt", "r");

    if(fp==NULL || fpname==NULL)
    {
        printf("\n        < 此联系人的信息不存在！请输入全名 >\n");
        return ERROR;
    }

    printf("        请问确定要删除联系人 %s 吗？确定的话请输入 yes 这个完整的单词：", name);
    scanf("%s", input);
    getchar();
    if(strcmp(input, "yes")!=0) {printf("\n        < 取消操作成功 >\n"); return ERROR;}

    Delfilestr(fpname, name);
    fclose(fpname);
    remove("name.txt");
    rename("channel.txt", "name.txt");


    for(i=1; i<=2; i++)
        fgets(category, MAX_LENGTH, fp);
    category[strlen(category)-1] = '\0';
    fpcategory = fopen(category, "r");
    if(fpcategory==NULL) return ERROR;
    Delfilestr(fpcategory, name);
    fclose(fpcategory);
    remove(category);
    rename("channel.txt", category);

    fclose(fp);
    remove(name);

    printf("\n        < 联系人删除成功 >\n");
    return OK;
}

int CheckCategory()
{
    flag = 0;
    FILE *fp;
    char input[MAX_LENGTH], temp[MAX_LENGTH];
    printf("        请输入你要查看的标签列表（如家人，朋友，工作，其他）：");
    scanf("%s", input);
    getchar();
    fp = fopen(input, "r");
    if(fp!=NULL){
        printf("\n        标签内联系人如下：\n\n");
        while(fgets(temp, MAX_LENGTH, fp)!=NULL)
        {
            temp[strlen(temp)-1] = '\0';
            printf("        * %s *\n", temp);
            flag++;
        }
    }
    else printf("\n        < 此标签不存在 >\n");
    if(flag==0 && fp!=NULL){
        printf("        < 此标签内联系人为空 >\n");
    }
    fclose(fp);
    printf("\n        标签内联系人共有 %d 个", flag);
    return OK;
}

int LoadCategory()
{
    char temp[MAX_LENGTH];
    FILE *fp;
    flag=0;
    fp = fopen("category.txt", "r");
    if(fp==NULL)
    {
        printf("\n        < 暂时还没有标签 >\n");
        return ERROR;
    }
    printf("\n        已定义的标签如下：\n\n");
    while(fgets(temp, MAX_LENGTH, fp)!=NULL)
    {
        temp[strlen(temp)-1] = '\0';
        printf("        * %s *\n", temp);
        flag++;
    }
    printf("\n        共有标签 %d 个", flag);
    return OK;
}
