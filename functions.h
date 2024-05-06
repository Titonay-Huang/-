#include <cstdio>
#include <string.h>
#define ERROR -1
#define OK 1
#define MAX_USERS 100

int flag=0;
char user[20];

int get_Flag_all()
{
    flag=0;
    FILE *fp;
    char name[20];
    fp = fopen("login.txt", "r");
    while(fgets(name, sizeof(name), fp) != NULL)
        flag++;
    return flag;
}

int Signin()
{
    FILE *fp;
    char name[50], input[50];
    printf("    请输入用户名：");
    scanf("%s", input);
    getchar();
    fp = fopen("login.txt", "r");
    while(1)
    {
        if(fgets(name, sizeof(name), fp) == NULL) return ERROR;
        if(!name) return ERROR;
        name[strlen(name)-1] = '\0';
        if(strcmp(input, name)==0)
        {
            strcpy(user, name);
            return flag;
        }
        memset(name,'\0',sizeof(name));
        flag++;
    }
    fclose(fp);
}

int Register()    //注意后期要查看是否重复名字
{
    FILE *fp;
    char name[20], passwd[20], passwd2[20];
    fp = fopen("login.txt", "a+");
    if(fp==NULL) return 0;
    printf("    请输入你要注册的用户名：");
    scanf("%s", name);
    getchar();
    while(1)
    {
        printf("    请设立密码：");
        scanf("%s", passwd);
        getchar();
        printf("    请再次输入密码：");
        scanf("%s", passwd2);
        getchar();
        if(strcmp(passwd2, passwd)==0)
        {
            fputs(name, fp);
            fputc('\n', fp);
            fclose(fp);
            break;
        }
    }
    fp = fopen("passwd.txt", "a+");
    fputs(passwd, fp);
    fputc('\n', fp);
    fclose(fp);
    printf("    添加成功！\n");
    return 1;
}

int passwd_Verify(char passwd[])
{
    FILE *fp;
    int i;
    char verify[20];
    fp = fopen("passwd.txt", "r");
    for(i=0; i<=flag; i++)
    {
        fgets(verify, 20, fp);
    }
    verify[strlen(verify)-1] = '\0';
    if(strcmp(verify, passwd)==0) return 1;
    else return 0;
}

root_Verify(char passwd[])
{
    if(strcmp(passwd, "5201314")==0)
    {
        printf("    验证成功！\n");
        return OK;
    }
    else
    {
        printf("    验证失败！\n");
        return ERROR;
    }
}

