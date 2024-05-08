#include <cstdio>
#include <string.h>
#define ERROR -1
#define OK 1
#define MAX_LENGTH 50

int flag=0, a;
char user[MAX_LENGTH], face[MAX_LENGTH];

int get_Flag_all()
{
    flag=0;
    FILE *fp;
    char name[MAX_LENGTH];
    fp = fopen("login", "r");
    while(fgets(name, sizeof(name), fp) != NULL)
        flag++;
    fclose(fp);
    return flag;
}

int repeat_LoginVerify(char input[])
{
    FILE *fp;
    flag=0;
    fp = fopen("login", "r");
    if(fp==NULL) return ERROR;
    while(fgets(user, MAX_LENGTH, fp)!=NULL)
    {
        user[strlen(user)-1] = '\0';
        if(strcmp(user, input)==0)
        {
            flag=1;
            break;
        }
    }
    fclose(fp);
    if(flag==1) return ERROR;
    else return OK;  //已存在则返回-1， 不存在则返回1
}

int repeat_NameVerify(char input[])
{
    FILE *fp;
    flag=0;
    fp = fopen("name", "r");
    if(fp==NULL) return ERROR;
    while(fgets(user, MAX_LENGTH, fp)!=NULL)
    {
        user[strlen(user)-1] = '\0';
        if(strcmp(user, input)==0)
        {
            flag=1;
            break;
        }
    }
    fclose(fp);
    if(flag==1) return ERROR;
    else return OK;  //已存在则返回-1， 不存在则返回1
}

int Register()    //注意后期要查看是否重复名字
{
    FILE *fp;
    char name[MAX_LENGTH], passwd[MAX_LENGTH], passwd2[MAX_LENGTH];
    fp = fopen("login", "a+");
    if(fp==NULL) return 0;
    printf("\n        请输入你要注册的用户名：");
    scanf("%s", name);
    getchar();
    if(repeat_LoginVerify(name)==-1)
    {
        printf("\n        < 用户名已被使用 >\n");
        return ERROR;
    }
    a=3;
    while(a--)
    {
        printf("        请设立密码：");
        scanf("%s", passwd);
        getchar();
        printf("        请再次输入密码：");
        scanf("%s", passwd2);
        getchar();
        if(strcmp(passwd2, passwd)==0)
        {
            fputs(name, fp);
            fputc('\n', fp);
            fclose(fp);
            break;
        }
        else printf("\n        < 密码不一致 >\n\n");
    }
    if(a<0) return ERROR;
    fp = fopen("passwd", "a+");
    fputs(passwd, fp);
    fputc('\n', fp);
    fclose(fp);
    printf("\n        < 添加成功 >\n");
    return OK;
}

int passwd_Verify(char passwd[])
{
    FILE *fp;
    int i;
    char verify[MAX_LENGTH];
    fp = fopen("passwd", "r");
    for(i=0; i<=flag; i++)
    {
        fgets(verify, MAX_LENGTH, fp);
    }
    verify[strlen(verify)-1] = '\0';
    fclose(fp);
    if(strcmp(verify, passwd)==0) return 1;
    else return 0;
}



int root_Verify(char passwd[])
{
    FILE *fp;
    char getpasswd[MAX_LENGTH];
    fp = fopen("rootpasswd", "r");
    if(fp==NULL) return ERROR;
    fgets(getpasswd, MAX_LENGTH, fp);
    getpasswd[strlen(getpasswd)-1] = '\0';
    fclose(fp);
    if(strcmp(passwd, getpasswd)==0)
    {
        printf("\n        < 验证成功 >\n");
        return OK;
    }
    else
    {
        printf("\n        < 验证失败 >\n");
        return ERROR;
    }
}

int root_Power()
{
    char passwd[MAX_LENGTH];
    printf("        请先输入管理员密码，以获得账号注册权限：");
    scanf("%s", passwd);
    getchar();
    a=3;
    while(a--)
    {
        if(root_Verify(passwd)==1)
        {
            get_Flag_all();
            Register();
            return OK;
        }
        else
        {
            printf("\n        请重新输入密码：");
            scanf("%s", passwd);
            getchar();
        }
    }
    return OK;
}

int Signin(char input[])
{
    FILE *fp;
    char name[MAX_LENGTH];
    fp = fopen("login", "r");
    while(1)
    {
        if(fgets(name, sizeof(name), fp) == NULL) return ERROR;
        if(!name) return ERROR;
        name[strlen(name)-1] = '\0';
        if(strcmp(input, name)==0)
        {
            strcpy(face, name);
            return flag;
        }
        memset(name,'\0',sizeof(name));
        flag++;
    }
    fclose(fp);
}


int user_Signin()
{
    a=3;
    printf("        请输入用户名：");
    scanf("%s", user);
    getchar();
    while(a--)
    {

        if(Signin(user)!=-1)
        {
            printf("        用户存在，请输入密码：");
            scanf("%s", user);
            getchar();
            break;
        }
        else
        {
            printf("        用户不存在, 请重新输入：");
            scanf("%s", user);
            getchar();
        }
    }
    if(a<0) return ERROR;
    a=3;
    while(a--)
    {
        if(passwd_Verify(user))
        {
            printf("\n        < 密码正确，登陆成功 >\n        < 欢迎进入通讯录系统 >\n");
            return 1;
        }
        else
        {
            printf("\n        < 密码错误 >\n");
            printf("\n        请重新输入：");
            scanf("%s", user);
            getchar();
        }
    }
    if(a<0) return ERROR;
    return OK;
}

int root_Signin()
{
    char passwd[MAX_LENGTH];
    printf("        请输入管理员账户的密码：");
    scanf("%s", passwd);
    getchar();
    a=3;
    while(a--)
        if(root_Verify(passwd)==1) return OK;
        else
        {
            printf("\n        请重新输入密码：");
            scanf("%s", passwd);
            getchar();
        }
    return ERROR;
}
