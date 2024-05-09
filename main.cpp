#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "functions.h"
#include "AddressList.h"
#define MAX_LENGTH 50

int main()
{
    int status=0, t;
    char input[MAX_LENGTH];
    while(1)
    {
        if(status==0)
        {
            printf("\n");
            printf("    ********************************************************\n");
            printf("    *                                                      *\n");
            printf("    *      请先登录通讯录管理系统，若无账户请先注册        *\n");
            printf("    *        1、注册                      2、登录          *\n");
            printf("    *        3、管理员登陆                4、退出          *\n");
            printf("    *                                                      *\n");
            printf("    *      ##请注意：输入过程中不可以有任何的空格哦##      *\n");
            printf("    *                                                      *\n");
            printf("    ********************************************************\n");
            printf("        请输入您需要的功能编号：");
            scanf("%d", &t);
            getchar();
            switch(t)
            {
                case 1 :
                    root_Power();
                    break;
                case 2 :
                    if(user_Signin()==1) status=1;
                    break;
                case 3 :
                    if()
                    if(root_Signin()==1) status=2;
                    break;
                case 4 :
                    exit(0);
                default:
                    printf("\n        < 暂时无此命令 >\n");
                    break;
            }

        }

        else if(status == 1)
        {
            printf("\n");
            printf("    ********************************************************\n");
            printf("    *                                                      *\n");
            printf("    *     用户 %-20s 你好，请选择功能：                    *\n", user);
            printf("    *       1、查找联系人               2、删除联系人      *\n");
            printf("    *       3、修改联系人信息           4、增加联系人      *\n");
            printf("    *       5、列出所有联系人           6、列出标签种类    *\n");
            printf("    *       7、查看标签内联系人         8、退出登录        *\n");
            printf("    *                                                      *\n");
            printf("    *      ##请注意：输入过程中不可以有任何的空格哦##      *\n");
            printf("    *                                                      *\n");
            printf("    ********************************************************\n");
            printf("        请输入您需要的功能编号：");
            scanf("%d", &t);
            getchar();
            switch(t)
            {
                case 1 :
                    printf("        请输入你要查看的联系人的名字：");
                    scanf("%s", input);
                    ElasticSearch(input);
                    break;
                case 2 :
                    DelAddress();
                    break;
                case 3 :
                    printf("        请输入要修改的联系人名字：");
                    scanf("%s", input);
                    if(ModifyAddress(input)!=-1) printf("\n        < 联系人信息修改成功 >\n");
                    else                         printf("\n        < 联系人不存在，修改信息失败,请输入完整的名字 >\n");
                    break;
                case 4 :
                    EnterAddress();
                    break;
                case 5 :
                    LoadAddress();
                    break;
                case 6 :
                    LoadCategory();
                    break;
                case 7 :
                    CheckCategory();
                    break;
                case 8 :
                    status=0;
                    printf("\n        < 退出登录成功 >\n");
                    break;
                default:
                    printf("\n        < 暂时无此命令 >\n");
                    break;
            }
        }
        else if(status == 2)
        {
            printf("\n");
            printf("    ********************************************************\n");
            printf("    *                                                      *\n");
            printf("    *     管理员模式，请选择所需要的功能：                 *\n");
            printf("    *       1、更改管理员密码       2、增加用户            *\n");
            printf("    *       3、删除用户             4、查看用户列表        *\n");
            printf("    *       5、退出登录                                    *\n");
            printf("    *                                                      *\n");
            printf("    *      ##请注意：输入过程中不可以有任何的空格哦##      *\n");
            printf("    *                                                      *\n");
            printf("    ********************************************************\n");
            printf("        请输入您需要的功能编号：");
            scanf("%d", &t);
            getchar();
            switch(t)
            {
                case 1 :
                    rewriteRootPasswd();
                case 2 :

                case 3 :

                case 4 :
                case 5 :status=0; printf("\n        < 退出登录成功 >\n");break;
            }
        }

    }
    return 0;
}
