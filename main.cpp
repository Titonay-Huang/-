#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "functions.h"
#include "AddressList.h"

int main()
{
    int status=0, t;
    FILE *fp;
    char input[20], temp[20];
    while(1)
    {
        if(status==0)
        {
            printf("\n");
            printf("************************************************\n");
            printf("*                                              *\n");
            printf("*  请先登录通讯录管理系统，若无账户请先注册    *\n");
            printf("*    1、注册                      2、登录      *\n");
            printf("*    3、退出                                   *\n");
            printf("*                                              *\n");
            printf("************************************************\n");
            printf("    请输入您需要的功能编号：");
            scanf("%d", &t);
            getchar();
            if(t==1)
            {
                printf("    请先输入管理员密码，以获得账号注册权限：");
                scanf("%s", input);
                getchar();
                if(root_Verify(input)!=1) continue;
                get_Flag_all();
                Register();
            }
            else if(t==2)
            {
                if(Signin()!=-1)
                {
                    printf("    用户存在，请输入密码：");
                    scanf("%s", input);
                    getchar();
                    putchar('\n');
                    if(passwd_Verify(input))
                    {
                        printf("    密码正确，登陆成功！\n    欢迎进入通讯录系统！\n");
                        status = 1;
                    }
                    else
                    {
                        printf("    密码错误！\n");
                    }
                }
                else
                {
                    printf("    用户不存在！\n");
                }
            }
            else if(t==3)
            {
                exit(0);
            }
            else
            {
                printf("    输入无效！不存在此命令！ ");
            }
        }
        else
        {
            printf("\n");
            printf("************************************************\n");
            printf("*                                              *\n");
            printf("*  用户 %-20s 你好，请选择功能：*\n", user);
            printf("*    1、查找联系人          2、删除联系人      *\n");
            printf("*    3、列出所有联系人列表  4、增加联系人      *\n");
            printf("*    5、修改联系人信息      6、列出联系人类别  *\n");
            printf("*    7、退出登录                               *\n");
            printf("*                                              *\n");
            printf("************************************************\n");
            printf("    请输入您需要的功能编号：");
            scanf("%d", &t);
            getchar();
            switch(t)
            {
                case 1 :
                    printf("    请输入你要查看的联系人的名字：");
                    scanf("%s", input);
                    ElasticSearch(input);
                    break;
                case 2 :
                    DelAddress();
                    break;
                case 3 :LoadAddress();break;
                case 4 :EnterAddress(); break;
                case 5 :
                    printf("    请输入要修改的联系人名字：");
                    scanf("%s", input);
                    if(ModifyAddress(input)!=-1)
                    {
                        printf("    联系人信息修改成功！\n");
                    }
                    else
                    {
                        printf("    联系人不存在，修改信息失败！");
                    }
                    break;
                case 6 :
                    flag = 0;
                    printf("    请输入你要查看的标签列表（家人，朋友，工作，客服）：");
                    scanf("%s", input);
                    getchar();
                    fp = fopen(input, "r");
                    if(fp!=NULL){
                        printf("    标签内联系人如下：\n\n");
                        while(fgets(temp, 20, fp)!=NULL)
                        {
                            temp[strlen(temp)-1] = '\0';
                            printf("    * %s *\n", temp);
                            flag++;
                        }
                    }
                    else printf("\n    此标签不存在！\n");
                    if(flag==0 && fp!=NULL){
                        printf("    此标签内联系人为空！\n");
                    }
                    fclose(fp);
                    break;
                case 7 :status=0; printf("\n    退出登录成功\n");break;
            }
        }
    }
    return 0;
}
