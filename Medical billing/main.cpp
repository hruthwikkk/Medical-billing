#include<iostream>
#include<conio.h>
#include<process.h>
#include<fstream>
#include<windows.h>
#include<conio.h>
#include<time.h>
#include<fstream>
#include<cstring>
#include<string.h>
#include<cstdio>
#include<cstdlib>
#include<iomanip>
void expand(int);
using namespace std;
int k=7,r=0,flag=0;
time_t my_time = time(NULL);
char password[20]="1234";
COORD coord = {0, 0};

void gotoxy(int x, int y)
{
    COORD co;
    co.X = x;
    co.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), co);
}
struct customer
{
    string ph_no;
    string pas;
    char mail_id[100];
    char cust_name[100];
    char address[100];
}Cust;
class product
{
    int pno;
    char name[50];
    float price,qty,tax,dis;
    public:
void create_product()
{
    cout<<"\nPlease Enter The Product No. of The Product ";
    cin>>pno;
    cin.get();
    cout<<"\n\nPlease Enter The Name of The Product(mention dosage too) ";
    gets(name);
    cout<<"\nPlease Enter The Price of The Product ";
    cin>>price;
    cout<<"\nPlease Enter The Discount (%) ";
    cin>>dis;
}

void show_product()
{
    cout<<"\nThe Product No. of The Product : "<<pno;
    cout<<"\nThe Name of The Product : ";
    puts(name);
    cout<<"\nThe Price of The Product : "<<price;
    cout<<"\nDiscount : "<<dis;
}

int retpno()
    {return pno;}

float retprice()
    {return price;}

char* retname()
    {return name;}

int retdis()
    {return dis;}

};
fstream fp;
product pr;
void write_product()
{
        fp.open("Shop.txt",ios::out|ios::app);
        pr.create_product();
        fp.write((char*)&pr,sizeof(product));
        fp.close();
        cout<<"\n\nThe Product Has Been Created ";
        getch();
}
void display_all()
{
        cout<<"\n\n\n\t\tDISPLAY ALL RECORD !!!\n\n";
        fp.open("Shop.txt",ios::in);
        while(fp.read((char*)&pr,sizeof(product)))
        {
            pr.show_product();
            cout<<"\n\n=================================\n";
            getch();
        }
        fp.close();
        getch();
}
void display_sp(int n)
{
        int flag=0;
        fp.open("Shop.txt",ios::in);
        while(fp.read((char*)&pr,sizeof(product)))
        {
            if(pr.retpno()==n)
            {
                system("cls");
                pr.show_product();
                flag=1;
            }
        }
        fp.close();
        if(flag==0)
        cout<<"\n\nrecord not exist";
getch();
}
void modify_product()
{
        int no,found=0;
        system("cls");
        cout<<"\n\n\tTo Modify ";
        cout<<"\n\n\tPlease Enter The Product No. of The Product";
        cin>>no;
        fp.open("Shop.txt",ios::in|ios::out);
        while(fp.read((char*)&pr,sizeof(product)) && found==0)
        {
            if(pr.retpno()==no)
            {
                pr.show_product();
                cout<<"\nPlease Enter The New Details of Product"<<endl;
                pr.create_product();
                int pos=-1*sizeof(pr);
                fp.seekp(pos,ios::cur);
                fp.write((char*)&pr,sizeof(product));
                cout<<"\n\n\t Record Updated";
                found=1;
            }
        }
        fp.close();
        if(found==0)
        cout<<"\n\n Record Not Found ";
        getch();
}
void delete_product()
{
    int no;
    system("cls");
    cout<<"\n\n\n\tDelete Record";
    cout<<"\n\nPlease Enter The product no. of The Product You Want To Delete";
    cin>>no;
    fp.open("Shop.txt",ios::in|ios::out);
    fstream fp2;
    fp2.open("Temp.txt",ios::out);
    fp.seekg(0,ios::beg);
    while(fp.read((char*)&pr,sizeof(product)))
    {
        if(pr.retpno()!=no)
        {
            fp2.write((char*)&pr,sizeof(product));
        }
    }
    fp2.close();
    fp.close();
    remove("Shop.txt");
    rename("Temp.txt","Shop.txt");
    cout<<"\n\n\tRecord Deleted ..";
    getch();
}
void menu()
{
    system("cls");
    fp.open("Shop.txt",ios::in);
    if(!fp)
    {
        cout<<"ERROR!!! FILE COULD NOT BE OPEN\n\n\n Go To Admin Menu to create File";
        cout<<"\n\n\n Program is closing ....";
        getch();
        exit(0);
    }

    cout<<"\n\n\t\tProduct MENU\n\n";
    cout<<"===================================================\n";
    cout<<"P.NO.\t\tNAME\t\t\t\tPRICE\n";
    cout<<"===================================================\n";

    while(fp.read((char*)&pr,sizeof(product)))
    {
        cout<<pr.retpno()<<"\t\t"<<pr.retname()<<"\t\t"<<pr.retprice()<<endl;
    }
    fp.close();
}

void place_order(string x)
{
    string y=x+".txt";
    ofstream f4(y.c_str(),ios::app);
    int order_arr[50],quan[50],c=0;
    float amt,damt,total=0;
    char ch='Y';
    menu();
    cout<<"\n============================";
    cout<<"\n PLACE YOUR ORDER";
    cout<<"\n============================\n";
    do
    {
        cout<<"\n\nEnter The Product No. Of The Product : ";
        cin>>order_arr[c];
        cout<<"\nQuantity in number : ";
        cin>>quan[c];
        c++;
        cout<<"\nDo You Want To Order Another Product ? (y for yes/any other keys for no)";
        cin>>ch;
    }while(ch=='y' ||ch=='Y');
    cout<<"\n\nThank You For Placing The Order";
    getch();
    system("cls");
    cout<<"\t\t\tMEDZONE DRUG HOUSE"<<endl;
    cout<<"\n\n********************************INVOICE***************************************\n";
    cout<<"\nDate and Time:"<<ctime(&my_time);
    cout<<"\nno.\tPr Name\t\tQuantity  Price  Amount  Amount after discount\n";
    f4<<"\t\t\tMEDZONE DRUG HOUSE"<<endl;
    f4<<"\n\n********************************INVOICE***************************************\n";
    f4<<"\nDate and Time:"<<ctime(&my_time);
    f4<<"\nno.\tPr Name\t\tQuantity  Price  Amount  Amount after discount\n";
    for(int x=0;x<=c;x++)
    {
        fp.open("Shop.txt",ios::in);
        fp.read((char*)&pr,sizeof(product));
        while(!fp.eof())
        {
            if(pr.retpno()==order_arr[x])
            {
                amt=pr.retprice()*quan[x];
                damt=amt-(amt*pr.retdis()/100);
                cout<<"\n"<<order_arr[x]<<"."<<pr.retname()<<"\t"<<quan[x]<<"\t   "<<pr.retprice()<<"\t  "<<amt<<"\t\t"<<damt;
                f4<<"\n"<<order_arr[x]<<"."<<pr.retname()<<"\t"<<quan[x]<<"\t   "<<pr.retprice()<<"\t  "<<amt<<"\t\t"<<damt;
                total+=damt;
            }
        fp.read((char*)&pr,sizeof(product));
        }
    fp.close();
    }
    cout<<"\n\n\t\t\t\t\tTOTAL = "<<total<<"/-"<<endl<<"\t\t\tIn Words : ";
    f4<<"\n\n\t\t\t\t\tTOTAL = "<<total<<"/-"<<endl;
    f4<<"******************************************************************************";
    expand(total);
    cout<<" only"<<endl;
    cout<<"******************************************************************************\n\t\t\tThank you visit again"<<endl;
    getch();
    return;
}
void seehist(string x)
{
    string y,xxx;
    y=x+".txt";
    ifstream kiran(y.c_str());
    if(!kiran)
    {
        cout<<"No History";
        return;
    }
    while(!kiran.eof())
    {
        getline(kiran,xxx);
        cout<<xxx<<endl;
    }
return;
}
void intro()
{
    system("cls");
    gotoxy(32,4);
    cout<<"MEDICAL BILLING SYSTEM\n";
    gotoxy(45,16);
    cout<<"MADE BY :Hruthwik K(1BM17IS032)\n\t\t\t\t\t\t       B S Prasanna(1BM17IS019)\n\n\n\t\t\t\t\t\t BMS College Of Engineering";
    getch();
}
void admin_menu()
{
        system("cls");
        char ch2;
        cout<<"\n\n\n\tADMIN MENU";
        cout<<"\n\n\t1.CREATE PRODUCT";
        cout<<"\n\n\t2.DISPLAY ALL PRODUCTS";
        cout<<"\n\n\t3.QUERY ";
        cout<<"\n\n\t4.MODIFY PRODUCT";
        cout<<"\n\n\t5.DELETE PRODUCT";
        cout<<"\n\n\t6.VIEW PRODUCT MENU";
        cout<<"\n\n\t7.CHANGE THE PASSWORD";
        cout<<"\n\n\t8.BACK TO MAIN MENU";
        cout<<"\n\n\tPlease Enter Your Choice (1-7) ";
        ch2=getche();
switch(ch2)
        {
        case '1':
            system("cls");
            write_product();
            break;
        case '2':
            display_all();
            break;
        case '3':
            int num;
            system("cls");
            cout<<"\n\n\tPlease Enter The Product No. ";
            cin>>num;
            display_sp(num);
            break;
        case '4':
            modify_product();
            break;
        case '5':
            delete_product();
            break;
        case '6':
            menu();
            getch();
            break;
        case '7':
            system("cls");
            char pass[10];
            ab:
            gotoxy(16,4);
            cout<<"enter your current password: ";
               for(int i=0;i<10;i++)
               {
                    pass[i]=getch();
                    if(pass[i]==13)
                    {
                        pass[i]='\0';
                        break;
                    }
                    else
                    {
                        cout<<"*";
                    }
               }
                if(strcmp(pass,password)==0)
                {
                    cout<<"\n\n\t\tenter the new password: ";
                    for(int i=0;i<10;i++)
                    {
                        password[i]=getch();
                        if(password[i]==13)
                        {
                            password[i]='\0';
                            break;
                        }
                        else
                        {
                            cout<<"*";
                        }
                    }
                    cout<<"\n\n\t\tPassword changed successfully......";
                    getchar();
                    getchar();

                }
                else
                {
                    cout<<"\n\n\tthe password is incorrect!!!";
                    goto ab;
                }

        case '8':
                break;
        default:
            cout<<"\a";admin_menu();
        }
}
void expand(int value)
{
    const char * const ones[20] = {"zero", "one", "two", "three","four","five","six","seven",
    "eight","nine","ten","eleven","twelve","thirteen","fourteen","fifteen","sixteen","seventeen",
    "eighteen","nineteen"};
    const char * const tens[10] = {"", "ten", "twenty", "thirty","forty","fifty","sixty","seventy",
    "eighty","ninety"};

    if(value<0)
    {
        cout<<"minus ";
        expand(-value);
    }
    else if(value>=1000)
    {
        expand(value/1000);
        cout<<" thousand";
        if(value % 1000)
        {
            if(value % 1000 < 100)
            {
                cout << " and";
            }
            cout << " " ;
            expand(value % 1000);
        }
    }
    else if(value >= 100)
    {
        expand(value / 100);
        cout<<" hundred";
        if(value % 100)
        {
            cout << " and ";
            expand (value % 100);
        }
    }
    else if(value >= 20)
    {
        cout << tens[value / 10];
        if(value % 10)
        {
            cout << " ";
            expand(value % 10);
        }
    }
    else
    {
        cout<<ones[value];
    }
    return;
}
int main()
{
char ch,lol;
char pass[10];
int i;
intro();
abcde:
do
{
    system("cls");
    cout<<"\n\n\n\tMAIN MENU";
    cout<<"\n\n\t01. CUSTOMER";
    cout<<"\n\n\t02. ADMINISTRATOR";
    cout<<"\n\n\t03. EXIT";
    cout<<"\n\n\tPlease Select Your Option (1-3) ";
    ch=getche();
    switch(ch)
    {
        case '1':
            system("cls");
            while(1)
            {
                system("cls");
                char choice;
                char srch[20];
                gotoxy(32,4);
                cout<<"\tCUSTOMER MENU\n\n\n";
                cout<<"\t\t\tEnter your choice:\n\n"<<endl;
                cout<<"\t\t\t1.SIGN UP\n\n";
                cout<<"\t\t\t2.LOGIN\n\n";
                cout<<"\t\t\t3.Jump to main\n";
                choice=getch();
                switch(choice)
                {
                    case '1':
                    {
                        system("cls");
                        gotoxy(16,4);
                        string passw ="";
                        char cc;
                        ofstream f1("customer.txt",ios::app);
                        cout<<"Enter your phone number:";
                        cin>>Cust.ph_no;
                        cout<<"\t\tEnter password of your choice:";
                        cc = _getch();
                        while(cc != 13)
                        {
                            passw.push_back(cc);
                            cout << '*';
                            cc = _getch();
                        }
                        cin.get();
                        cout<<"\n\t\tEnter your email id: ";
                        gets(Cust.mail_id);
                        cin.get();
                        cout<<"\t\tEnter your name:";
                        gets(Cust.cust_name);
                        cin.get();
                        cout<<"\t\tEnter your address\n\t\t(Note: Press ENTER only after you fill your address completely):\n";
                        gets(Cust.address);
                        cout<<"\n\t\tSign up successfull  :) \n\n\t\t\tYou can login by enetering your mobile no. and password\n\t\t\t\tPress any key ";
                        getchar();
                        getchar();
                        f1<<"Phone no.:"<<Cust.ph_no<<endl<<"Password:"<<passw<<endl<<"Email id:"<<Cust.mail_id<<endl<<"Name:"<<Cust.cust_name<<endl<<"Address:"<<Cust.address<<endl;
                        f1.close();
                    }
                    break;
                    case '2':
                    {
                        system("cls");
                        gotoxy(15,4);
                        ifstream f2("customer.txt");
                        cout<<"Enter your Mobile no. to Login:  ";
                        cin>>srch;
                        string pes;
                        cout<<endl;
                        int notFound=0;
                        while(!f2.eof())
                        {
                            string x,mm,u,uu;
                            string passwo ="";
                            char ccv;
                            getline(f2,Cust.ph_no);
                            if (!Cust.ph_no.size())
                                break;
                            x = Cust.ph_no.substr(10,10);
                            if(srch == x)
                            {
                                cout<<"\n\n\t\tPassword please......";
                         asdf:  ccv = _getch();
                                while(ccv != 13)
                                {
                                    passwo.push_back(ccv);
                                    cout << '*';
                                    ccv = _getch();
                                }
                                getline(f2,Cust.pas);
                                u = Cust.pas.substr(9,10);

                                while(passwo != u)
                                {
                                    cout<<"\nPassword is incorrect.... \n\tPlease try again";
                                    goto asdf;
                                }
                                    notFound=1;
                                    system("cls");
                                    cout<<Cust.ph_no<<endl;
                                    getline(f2,mm);
                                    cout<<mm<<endl;
                                    getline(f2,mm);
                                    cout<<mm<<endl;
                                    getline(f2,mm);
                                    cout<<mm<<endl;
                                    cout<<"\n\n\n\n\n\n\n\n\n\t\t\t";
                                    cout<<"\n\t\t\tENTER YOUR CHOICE";
                                    cout<<"\n\t\t\t1. ORDER ";
                                    cout<<"\n\t\t\t2. View Your Recent Activities";
                                    cout<<"\n\t\t\t3. Go Back\n\n";
                                    getchar();
                                    lol=getch();
                                    switch(lol)
                                    {
                                    case '1':
                                        place_order(x);
                                        break;
                                    case '2':
                                        seehist(x);
                                        break;
                                    case '3':
                                        break;
                                    default:
                                        cout<<"\nplease Enter no.s only between 1-3";
                                   }
                            }
                            else
                            {
                                getline(f2,mm);getline(f2,mm);getline(f2,mm);getline(f2,mm);
                            }
                        }
                        if(notFound==0)
                        {
                        cout<<"No Record Found"<<endl;
                        }
                        f2.close();
                        cout<<"Press any key";
                        getch();
                        getch();
                    }
                    break;
                    case '3':
                        goto abcde;
                        break;
                }
            }

    case '2':
                abcd:cout<<"\n\tenter the password (10 characters max.): ";
                for(i=0;i<10;i++)
                {
                    pass[i]=getch();
                    if(pass[i]==13)
                    {
                        pass[i]='\0';
                        break;
                    }
                    else
                    {
                        cout<<"*";
                    }
                }
            if(strcmp(pass,password)==0)
            {
                admin_menu();
            }
            else
            {
                cout<<"\n\n\tthe password is incorrect!!!";
                goto abcd;
            }

            break;
    case '3':exit(0);
    default :
        cout<<"\a";
    }
}while(ch!='3');
return 0;
}
