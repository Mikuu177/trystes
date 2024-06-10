#include <stdio.h>
#include <windows.h>
#include <time.h>
#include <string.h>
#define N 100
#define REPORT_PASSWORD "password123"
#define PAGE_SIZE 10 // 每页显示10个记录

struct employee
{
    int num;
    char name[10];
    char sex;
    int age;
    char xueli[30];
    int wage;
    int xiao;
    int yu;
    char addr[30];
    long int tel;
} em[100];

void menu();
void input();
void save(int);
void display(int page);
void del();
void add();
void search();
void search_num();
void search_xueli();
void search_tel();
void modify();
void generate_report();
void login();
void paginate(int total_records);
void report_lost();
int load();

char current_user[20];
int is_admin = 0;

void menu()
{
    printf(" ******************菜单管理****************\n");
    printf("------------------------\n");
    printf("------------------------\n");
    printf(" 1.新会员登记");
    printf(" 2统计功能\n");
    printf(" 3.会员消费结算");
    printf(" 4.会员退卡\n");
    printf(" 5.会员卡续费");
    printf(" 6会员信息修改\n");
    printf(" 7.会员卡挂失");
    printf(" 8.退出\n");
    printf(" 9.会员报表\n");
    printf(" *************欢迎使用会员卡计费系统************\n");
    printf("------------------------\n");
    printf("------------------------\n");
    printf("\n");
    printf("\n");
}

void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void login()
{
    char username[20], password[20];
    printf("请输入用户名: ");
    scanf("%s", username);
    clear_input_buffer();
    printf("请输入密码: ");
    scanf("%s", password);
    clear_input_buffer();

    if (strcmp(username, "admin") == 0 && strcmp(password, "admin123") == 0)
    {
        is_admin = 1;
        strcpy(current_user, "admin");
        printf("管理员登录成功！\n");
    }
    else if (strcmp(username, "user") == 0 && strcmp(password, "user123") == 0)
    {
        is_admin = 0;
        strcpy(current_user, "user");
        printf("用户登录成功！\n");
    }
    else
    {
        printf("用户名或密码错误！\n");
        exit(0);
    }
}

int main()
{
    int n, flag;
    char a;

    login();
    menu();

    while (1)
    {
        printf("请选择你需要操作的步骤(1--9):\n");
        scanf("%d", &n);
        clear_input_buffer();
        if (n >= 1 && n <= 9)
        {
            flag = 1;
        }
        else
        {
            flag = 0;
            printf("您输入有误?请重新选择!");
        }

        if (flag == 1)
        {
            switch (n)
            {
            case 1:
                printf(" ◆◆◆新会员登记◆◆◆\n");
                printf("\n");
                input();
                break;
            case 2:
                printf(" ◆◆◆统计功能◆◆◆\n");
                printf("\n");
                paginate(load());
                break;
            case 3:
                printf(" ◆◆◆会员消费结算◆◆◆\n");
                printf("\n");
                search();
                break;
            case 4:
                printf(" ◆◆◆会员退卡◆◆◆\n");
                printf("\n");
                del();
                break;
            case 5:
                printf(" ◆◆◆会员卡续费◆◆◆\n");
                printf("\n");
                add();
                break;
            case 6:
                printf(" ◆◆◆会员信息修改◆◆◆\n");
                printf("\n");
                modify();
                break;
            case 7:
                printf(" ◆◆◆会员卡挂失◆◆◆\n");
                printf("\n");
                report_lost();
                break;
            case 8:
                exit(0);
                break;
            case 9:
                if (is_admin)
                {
                    printf(" ◆◆◆ 生成报表 ◆◆◆(仅限管理员)\n");
                    printf("\n");
                    generate_report();
                }
                else
                {
                    printf("权限不足，无法生成报表。\n");
                }
                break;
            default:
                break;
            }
            clear_input_buffer();
            printf("\n");
            printf("是否继续进行(y or n):\n");
            scanf("%c", &a);
            clear_input_buffer();
            if (a == 'y')
            {
                flag = 1;
                system("cls");
                menu();
            }
            else
                exit(0);
        }
    }
}

void input()
{
    int i, m;
    printf("请输入需要创建信息的会员人数(1--100):\n");
    scanf("%d", &m);
    clear_input_buffer();
    for (i = 0; i < m; i++)
    {
        printf("卡号?");
        srand((int)time(0));
        em[i].num = rand() % 100 + 20000000;
        if (em[i].num != em[i - 1].num)
            printf("%8d ", em[i].num);
        printf("\n");
        printf("请输入姓名: ");
        scanf("%s", em[i].name);
        clear_input_buffer();
        printf("请输入性别(f--女m--男): ");
        scanf("%c", &em[i].sex);
        clear_input_buffer();
        printf("请输入年龄: ");
        scanf("%d", &em[i].age);
        clear_input_buffer();
        printf("请输入学历: ");
        scanf("%s", em[i].xueli);
        clear_input_buffer();
        printf("请输入缴费金额: ");
        scanf("%d", &em[i].wage);
        clear_input_buffer();
        printf("请输入住址: ");
        scanf("%s", em[i].addr);
        clear_input_buffer();
        printf("请输入电话: ");
        scanf("%ld", &em[i].tel);
        clear_input_buffer();
        printf("\n");
    }
    printf("\n创建完毕!\n");
    save(m);
}

void save(int m)
{
    int i;
    FILE *fp;
    if ((fp = fopen("employee_list", "wb")) == NULL)
    {
        printf("cannot open file\n");
        exit(0);
    }
    for (i = 0; i < m; i++)
        if (fwrite(&em[i], sizeof(struct employee), 1, fp) != 1)
            printf("file write error\n");
    fclose(fp);
}

int load()
{
    FILE *fp;
    int i = 0;
    if ((fp = fopen("employee_list", "rb")) == NULL)
    {
        printf("cannot open file\n");
        exit(0);
    }
    else
    {
        do
        {
            fread(&em[i], sizeof(struct employee), 1, fp);
            i++;
        } while (feof(fp) == 0);
    }
    fclose(fp);
    return (i - 1);
}

void display(int page)
{
    int i;
    int m = load();
    int start = (page - 1) * PAGE_SIZE;
    int end = start + PAGE_SIZE;

    if (start >= m)
    {
        printf("没有更多记录。\n");
        return;
    }

    printf("\n卡号\t姓名\t性别\t年龄\t学历\t缴费金额\t消费金额\t住址\t电话\n");
    for (i = start; i < m && i < end; i++)
        printf("\n %d\t%s\t%c\t%d\t%s\t%d\t%s\t%ld\n", em[i].num, em[i].name, em[i].sex, em[i].age, em[i].xueli, em[i].wage, em[i].xiao, em[i].addr, em[i].tel);
}

void paginate(int total_records)
{
    int total_pages = (total_records + PAGE_SIZE - 1) / PAGE_SIZE;
    int current_page = 1;
    char choice;

    while (1)
    {
        display(current_page);
        printf("\n页数: %d/%d\n", current_page, total_pages);
        printf("上一页(p), 下一页(n), 返回主菜单(m): ");
        clear_input_buffer();
        scanf("%c", &choice);
        clear_input_buffer();

        if (choice == 'p' && current_page > 1)
        {
            current_page--;
        }
        else if (choice == 'n' && current_page < total_pages)
        {
            current_page++;
        }
        else if (choice == 'm')
        {
            break;
        }
        else
        {
            printf("无效输入。\n");
        }
    }
}

void del()
{
    int m = load();
    int i, j, n, t, flag;
    char name[20];
    printf("\n 原来的会员信息:\n");
    paginate(m);
    printf("\n");
    printf("请输入要删除的会员的姓名:\n");
    scanf("%s", name);
    clear_input_buffer();
    for (flag = 1, i = 0; flag && i < m; i++)
    {
        if (strcmp(em[i].name, name) == 0)
        {
            printf("\n已找到此人?原始记录为?\n");
            printf("\n卡号 姓名 性别 年龄 缴费金额 余额\n");
            printf("\n%d\t%s\t%c\t%d\t%d\t%d\n", em[i].num, em[i].name, em[i].sex, em[i].age, em[i].wage, em[i].yu);
            printf("\n确实要删除此人信息请按1,不删除请按0\n");
            scanf("%d", &n);
            clear_input_buffer();
            if (n == 1)
            {
                for (j = i; j < m - 1; j++)
                {
                    strcpy(em[j].name, em[j + 1].name);
                    em[j].num = em[j + 1].num;
                    em[j].sex = em[j + 1].sex;
                    em[j].age = em[j + 1].age;
                    em[j].wage = em[j + 1].wage;
                    em[j].yu = em[j + 1].yu;
                }
                flag = 0;
            }
        }
    }
    if (!flag)
        m = m - 1;
    else
        printf("\n对不起?查无此人!\n");
    printf("\n 浏览删除后的所有会员信息:\n");
    save(m);
    paginate(m);
    printf("\n继续删除请按?不再删除请按\n");
    scanf("%d", &t);
    clear_input_buffer();
    switch (t)
    {
    case 1:
        del();
        break;
    case 0:
        break;
    default:
        break;
    }
}

void add()
{
    FILE *fp;
    int num;
    int t;
    int i;
    int m = load();
    printf("\n 原来的会员信息:\n");
    paginate(m);
    printf("\n");
    fp = fopen("employee_list", "a");
    printf("请输入续费会员卡号:\n");
    scanf("%d", &num);
    clear_input_buffer();
    for (i = 0; i < m; i++)
        if (num == em[i].num)
        {
            printf("\n已找到此人?其记录为?\n");
            printf("\n卡号\t姓名\t缴费金额\t消费金额\n");
            printf("\n%d\t%s\t%d\t%d\t%d\n", em[i].num, em[i].name, em[i].wage, em[i].xiao);
            printf("\n输入续费金额?\n");
            scanf("%d", &t);
            clear_input_buffer();
            em[i].wage = em[i].wage + t;
            printf("\n续后金额?\t%d\n", em[i].wage);
            printf("\n续费成功!\n");
        }
}

void search()
{
    int t, flag;
    do
    {
        printf("\n按卡号查询请按1; 按电话号码查询请按3,进入主函数按4\n");
        scanf("%d", &t);
        clear_input_buffer();
        if (t >= 1 && t <= 4)
        {
            flag = 1;
            break;
        }
        else
        {
            flag = 0;
            printf("您输入有误?请重新选择!");
        }
    } while (flag == 0);
    while (flag == 1)
    {
        switch (t)
        {
        case 1:
            printf("按卡号查询\n");
            search_num();
            break;
        case 3:
            printf("按电话号码查询\n");
            search_tel();
            break;

        case 4:
            main();
            break;
        default:
            break;
        }
    }
}

void search_num()
{
    int num;
    int i, t;
    int m = load();
    printf("请输入要查找的会员卡号(20000001---20000100):\n");
    scanf("%d", &num);
    clear_input_buffer();
    for (i = 0; i < m; i++)
        if (num == em[i].num)
        {
            printf("\n已找到此人?其记录为?\n");
            printf("\n卡号\t      姓名\t性别\t年龄\t缴费金额\t电话\n");
            printf("\n%d\t%s\t%c\t%d\t%d\t%ld\n", em[i].num, em[i].name, em[i].sex, em[i].age, em[i].wage, em[i].tel);
            printf("\n该次消费为;\n");
            scanf("%d", &em[i].xiao);
            clear_input_buffer();
            em[i].yu = em[i].wage - em[i].xiao;
            printf("\n卡号\t      姓名\t性别\t年龄\t缴费金额\t消费金额\t余额\t电话\n");
            printf("\n%d\t%s\t%c\t%d\t%d\t%d\t%d\t%ld\n", em[i].num, em[i].name, em[i].sex, em[i].age, em[i].wage, em[i].xiao, em[i].yu, em[i].tel);
            break;
        }
    if (i == m)
        printf("\n对不起?查无此人\n");
    printf("\n");
    printf("返回查询函数请按1,继续查询卡号请按2\n");
    scanf("%d", &t);
    clear_input_buffer();
    switch (t)
    {
    case 1:
        search();
        break;
    case 2:
        break;
    default:
        break;
    }
}

void search_by_xueli()
{
    char xueli[30];
    int i, m = load();

    printf("请输入要查找的学历: \n");
    scanf("%s", xueli);
    clear_input_buffer();

    for (i = 0; i < m; i++)
    {
        if (strcmp(em[i].xueli, xueli) == 0)
        {
            printf("\n找到会员:\n");
            // 打印会员信息
            printf("卡号\t姓名\t性别\t年龄\t学历\t缴费金额\t消费金额\t住址\t电话\n");
            printf("%d\t%s\t%c\t%d\t%s\t%d\t%d\t%s\t%ld\n",
                   em[i].num, em[i].name, em[i].sex, em[i].age,
                   em[i].xueli, em[i].wage, em[i].xiao, em[i].addr, em[i].tel);
            return;
        }
    }
    printf("\n没有找到相应学历的会员。\n");
}

void search_tel()
{
    long int tel;
    int i, t;
    int m = load();
    printf("请输入要查找的电话号码:\n");
    scanf("%ld", &tel);
    clear_input_buffer();
    for (i = 0; i < m; i++)
        if (tel == em[i].tel)
        {
            printf("\n已找到此人?其记录为?\n");
            printf("\n卡号\t      姓名\t性别\t年龄\t缴费金额\t电话\n");
            printf("\n%d\t%s\t%c\t%d\t%d\t%ld\n", em[i].num, em[i].name, em[i].sex, em[i].age,
                   em[i].wage, em[i].tel);
            printf("\n该次消费为;\n");
            scanf("%d", &em[i].xiao);
            clear_input_buffer();
            em[i].yu = em[i].wage - em[i].xiao;
            printf("\n卡号\t      姓名\t性别\t年龄\t缴费金额\t消费金额\t余额\t电话\n");
            printf("\n%d\t%s\t%c\t%d\t%d\t%d\t%d\t%s\t%ld\n", em[i].num, em[i].name, em[i].sex, em[i].age, em[i].wage, em[i].xiao, em[i].yu, em[i].tel);
            break;
        }
    if (i == m)
        printf("\n对不起?查无此人\n");
    printf("\n");
    printf("返回查询函数请按,继续查询电话号码请按\n");
    scanf("%d", &t);
    clear_input_buffer();
    switch (t)
    {
    case 1:
        search();
        break;
    case 2:
        break;
    default:
        break;
    }
}

void generate_report()
{
    char input_password[20];
    int is_correct = 0;

    printf("请输入报表查看密码: ");
    scanf("%s", input_password);
    clear_input_buffer();
    if (strcmp(input_password, REPORT_PASSWORD) == 0)
    {
        is_correct = 1;
        int i, m = load();
        int total_members = m;
        int total_wage = 0;

        printf("\n生成会员报表:\n");
        printf("总会员数: %d\n", total_members);

        for (i = 0; i < m; i++)
        {
            total_wage += em[i].wage;
        }

        printf("总缴费金额: %d\n", total_wage);
    }
    else
    {
        printf("密码错误！\n");
    }
    if (is_correct)
    {
        // 报表显示逻辑
        printf("\n生成会员报表:\n");
        printf("总会员数: %d\n", load());
        // 可以添加更多的报表信息
        printf("=================================================\n");
    }
    else
    {
        // 密码错误，返回菜单
        printf("\n返回菜单，请按任意键继续...\n");
        getchar();
        menu(); // 调用 menu 函数返回主菜单
    }
}

void modify()
{
    int num;
    char name[10];
    char sex;
    int age;
    char xueli[30];
    int wage;
    char addr[30];
    long int tel;
    int b, c, i, n, t, flag;
    int m = load();
    printf("\n 原来的会员信息:\n");
    paginate(m);
    printf("\n");
    printf("请输入要修改的会员的姓名:\n");
    scanf("%s", name);
    clear_input_buffer();
    for (flag = 1, i = 0; flag && i < m; i++)
    {
        if (strcmp(em[i].name, name) == 0)
        {
            printf("\n已找到此人?原始记录为?\n");
            printf("\n卡号\t        姓名\t性别\t年龄\t学历\t缴费金额\t住址\t电话\n");
            printf("\n%d\t%s\t%c\t%d\t%s\t%d\t%s\t%ld\n", em[i].num, em[i].name, em[i].sex, em[i].age, em[i].xueli, em[i].wage, em[i].addr, em[i].tel);
            printf("\n确实要修改此人信息请按; 不修改请按\n");
            scanf("%d", &n);
            clear_input_buffer();
            if (n == 1)
            {
                printf("\n需要进行修改的选项\n 1.卡号2.姓名3.性别4.年龄5.学历6.缴费金额7.住址8.电话\n");
                printf("请输入你想修改的那一项序号:\n");
                scanf("%d", &c);
                clear_input_buffer();
                if (c > 8 || c < 1)
                    printf("\n选择错误?请重新选择!\n");
            }
            flag = 0;
        }
    }
    if (flag == 1)
        printf("\n对不起?查无此人!\n");
    do
    {
        switch (c)
        {
        case 1:
            printf("卡号改为: ");
            scanf("%d", &num);
            clear_input_buffer();
            em[i - 1].num = num;
            break;
        case 2:
            printf("姓名改为: ");
            scanf("%s", name);
            clear_input_buffer();
            strcpy(em[i - 1].name, name);
            break;
        case 3:
            printf("性别改为: ");
            getchar();
            scanf("%c", &sex);
            clear_input_buffer();
            em[i - 1].sex = sex;
            break;
        case 4:
            printf("年龄改为: ");
            scanf("%d", &age);
            clear_input_buffer();
            em[i - 1].age = age;
            break;
        case 5:
            printf("学历改为: ");
            scanf("%s", xueli);
            clear_input_buffer();
            strcpy(em[i - 1].xueli, xueli);
            break;
        case 6:
            printf("缴费金额改为: ");
            scanf("%d", &wage);
            clear_input_buffer();
            em[i - 1].wage = wage;
            break;
        case 7:
            printf("住址改为: ");
            scanf("%s", addr);
            clear_input_buffer();
            strcpy(em[i - 1].addr, addr);
            break;
        case 8:
            printf("电话改为: ");
            scanf("%ld", &tel);
            clear_input_buffer();
            em[i - 1].tel = tel;
            break;
        }
        printf("\n");
        printf("\n是否确定所修改的信息?\n 是请按; 不,重新修改请按: \n");
        scanf("%d", &b);
        clear_input_buffer();
    } while (b == 2);
    printf("\n浏览修改后的所有会员信息:\n");
    printf("\n");
    save(m);
    paginate(m);
    printf("\n继续修改请按?不再修改请按\n");
    scanf("%d", &t);
    clear_input_buffer();
    switch (t)
    {
    case 1:
        modify();
        break;
    case 0:
        break;
    default:
        break;
    }
    getchar();
}

void report_lost()
{
    int num, i, flag, t;
    int m = load();
    printf("\n 原来的会员信息:\n");
    paginate(m);
    printf("\n请输入要挂失的会员卡号:\n");
    clear_input_buffer();
    scanf("%d", &num);
    clear_input_buffer();
    for (flag = 1, i = 0; flag && i < m; i++)
    {
        if (em[i].num == num)
        {
            printf("\n已找到此人?原始记录为?\n");
            printf("\n卡号\t姓名\t性别\t年龄\t学历\t缴费金额\t住址\t电话\n");
            printf("\n%d\t%s\t%c\t%d\t%s\t%d\t%s\t%ld\n", em[i].num, em[i].name, em[i].sex, em[i].age, em[i].xueli, em[i].wage, em[i].addr, em[i].tel);
            printf("\n确实要挂失此会员卡请按1,不挂失请按0\n");
            clear_input_buffer();
            scanf("%d", &t);
            clear_input_buffer();
            if (t == 1)
            {
                em[i].num = -1; // 设置为无效卡号表示挂失
                flag = 0;
                printf("\n会员卡已挂失!\n");
            }
        }
    }
    if (flag == 1)
        printf("\n对不起?查无此人!\n");
    save(m);
}
