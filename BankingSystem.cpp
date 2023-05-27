#include<iostream>
#include<fstream>
#include<cstring>
#include<ctime>
#include<string.h>
#include<conio.h>
#include<stdio.h>
using namespace std;

class Account
{
    private:
    long int accno;
    float accbalance;
    char name[50];
    char acctype;
    int password;


    public:
    void New_Account();
    void Display_Account();
    void Update_Account();
    void Deposit(int x);
    void Withdraw(int y);
   /*  void show_Balance();
    void Account_type();
 */



    void Storedata();
    void Viewdata();
    void Search_accdetails(long int,int);
    void Delete_Account(long int,int);
    void Deposit_Amount(long int, int,int);
    void Withdraw_Amount(long int,int,int);
    void Update_Account_Details(long int,int);
    
};

//FUNCTION TO CREATE NEW ACCOUNT
void Account::New_Account()
{
    cout<<"Enter Account Holder's Namer: "<<endl;
    cin.ignore();
    cin.getline(name,30);
    cout<<"Enter accout type(Enter 'S' for savings or 'C' for current account)"<<endl;
    cin>>acctype;
    cout<<"Enter the initial amout to be deposited"<<endl;
    cin>>accbalance;
    cout<<"Create a 4 digit Password"<<endl;
    cin>>password;
    cout<<"Account created successfully"<<endl;
    srand(time(0));  // Initialize random number generator.
    cout<<"Your account number is : "<<endl;
      accno=(rand() % 9999999999) + 1000000000;
      cout<<accno;


}



//FUNCTION TO DISPLAY ACCOUNT DETAILS

    void Account::Display_Account() 
{
	cout<<"\nAccount No. : "<<accno;
	cout<<"\nAccount Holder Name : ";
	cout<<name;
	cout<<"\nType of Account : "<<acctype;
	cout<<"\nBalance amount : "<<accbalance;
}




//FUNCTION TO CALCULATE ACC BALANCE AFTER DEPOSIT

void Account::Deposit(int x)
{
    accbalance=accbalance+x;

}




//FUNCTION TO CALCULATE ACC BALANCE AFTER WITHDRAW

void Account::Withdraw(int y)
{
    accbalance=accbalance-y;
}





//FUNCTION TO UPDATE ACCOUNT DETAILS

void Account::Update_Account()
{
	// cout<<"Account No. : "<<accno<<endl;
	cout<<"Update Account Holder Name : "<<endl;
	cin.ignore();
	cin.getline(name,30);
	cout<<"Update Type of Account : "<<endl;
	cin>>acctype;
    cout<<"\nUpdate Password";
    cin>>password;
	/* cout<<"Update Balance amount : "<<endl;
	cin>>accbalance; */
}





//FUNCTIONS OF FILE HANDLING






//FUNCTION TO STORE USERS DATA INTO A FILE

void Account::Storedata()
{
    ofstream fout;
        fout.open("file1.dat",ios::app | ios::binary);
        fout.write((char*)this,sizeof(*this));      //address of caller object
        fout.close();
 
}





//FUNCTION TO VIEW STORED DATA IN A FILE

void Account :: Viewdata()
    {

        ifstream fin;
        fin.open("file1.dat",ios::in | ios::binary);
        if(!fin)
        cout<<"File not found";
        else
        {
            fin.read((char*)this,sizeof(*this));
            while(!fin.eof())  //function to check end of file
            {
                Display_Account();   //caller object of showBookdata is same as caller obj of viewBookdata
                fin.read((char*)this,sizeof(*this));
            }
            fin.close();
        }


    }






    //FUNCTION TO SEARCH A PARTICULAR USER'S DATA FROMA FILE

    void Account::Search_accdetails(long int accnum,int pword)
    {

       

    ifstream fin;
    fin.open("file1.dat",ios::in | ios::binary);
    if(!fin)
    cout<<"File not found";
    else
    {
        fin.read((char*)this,sizeof(*this));
        while(!fin.eof())
            {
                if(accno==accnum && password==pword)                          //if two strings are same it returns 0, !0=1 if(1) statement is true
                {
                     Display_Account();
                }
                 fin.read((char*)this,sizeof(*this));
            }
            fin.close();

    }


}
    





    //FUNCTION TO DELETE A USERS DATA FROM FILE

    void Account::Delete_Account(long int accnum,int pword)
{
    ifstream fin;
    ofstream fout;
    fin.open("file1.dat",ios::in | ios::binary);
    if(!fin)
    cout<<"File not found";
    else
    {
        fout.open("tempfile.dat",ios::out | ios::binary);
        fin.read((char*)this,sizeof(*this));
        while(!fin.eof())
        {
            if(accno!=accnum && password!=pword)          
            
                fout.write((char*)this,sizeof(*this));
                 fin.read((char*)this,sizeof(*this));

        }
        fin.close();
        fout.close();
        remove("file1.dat"); 
        rename("tempfile.dat","file1.dat"); 


    }


}






    //FUNCTION TO UPDATE ACC BALANCE AFTER DEPOSIT IN THE FILE

void Account::Deposit_Amount(long int accnum,int depamt,int pword)
{
    fstream file;
    file.open("file1.dat",ios::in|ios::out|ios::ate|ios::binary);
    file.seekg(0);  
    file.read((char*)this,sizeof(*this));
    while(!file.eof())
    {
        if(accno==accnum && password==pword)
        {
            Deposit(depamt);
            file.seekp(file.tellp()-sizeof(*this));
            file.write((char*)this,sizeof(*this));
        }
        file.read((char*)this,sizeof(*this));
    }

}







//FUNCTION TO UPDATE ACC BALANCE AFTER WITHDRAW IN THE FILE

void Account::Withdraw_Amount(long int accnum,int withamt,int pword)
{
    fstream file;
    file.open("file1.dat",ios::in|ios::out|ios::ate|ios::binary);
    file.seekg(0);  
    file.read((char*)this,sizeof(*this));
    while(!file.eof())
    {
        if(accno==accnum && password==pword)
        {
            Withdraw(withamt);
            file.seekp(file.tellp()-sizeof(*this));
            file.write((char*)this,sizeof(*this));
        }
        file.read((char*)this,sizeof(*this));
    }

}







    //FUNCTION TO UPDATE ACCOUNT DETAILS OF USER IN THE FILE

void Account::Update_Account_Details(long int accnum,int pword)
{
    fstream file;
    file.open("file1.dat",ios::in|ios::out|ios::ate|ios::binary);
    file.seekg(0);  
    file.read((char*)this,sizeof(*this));
    while(!file.eof())
    {
        if(accno==accnum && password==pword)
        {
            Update_Account();
            file.seekp(file.tellp()-sizeof(*this));
            file.write((char*)this,sizeof(*this));
        }
        file.read((char*)this,sizeof(*this));
    }
}





int menu()
{
    int choice;
    cout<<"\nMAIN MENU";
		cout<<"\n01. Create an account";
        cout<<"\n02. View Your Account deatils";
		cout<<"\n03. Deposit amount";
		cout<<"\n04. Withdraw amount";
		cout<<"\n05. List of all account holders";
		cout<<"\n06. Close and account";
		cout<<"\n07. Update an account";
		cout<<"\n08. EXIT";
		cout<<"\nSelect Your Option (1-8) ";
    cin>>choice;
    return(choice);

}





int main()
{
    Account a1;
      int dep,with,pin;
      long int accnumber;
    while(1)
    {
        system("cls");
  
        switch(menu())
        {


        case 1:
        a1.New_Account();
        a1.Storedata();
        cout<<"\nRecord inserted";
        break;



        case 2:
        cout<<"Enter your account number";
        cin>>accnumber;
        cout<<"\nEnter your 4 digit Password";
        cin>>pin;
        a1.Search_accdetails(accnumber,pin);
        break;



        case 3:
        cout<<"Enter Account number";
        cin>>accnumber;
        cout<<"\nEnter amount to be deposited";
        cin>>dep;
        cout<<"\nEnter your 4 digit Password";
        cin>>pin;
        a1.Deposit_Amount(accnumber,dep,pin);
        cout<<"\n Deposit completed";
        break;



        case 4:
        cout<<"Enter Account number";
        cin>>accnumber;
        cout<<"\nEnter amount to be Withdrawn";
        cin>>with;
        cout<<"\nEnter your 4 digit Password";
        cin>>pin;
        a1.Withdraw_Amount(accnumber,with,pin);
        cout<<"\nWithdrawal Completed";
        break;



        case 5:
        a1.Viewdata();
        break;



        case 6:
        cout<<"Enter your account number";
        cin>>accnumber;
        cout<<"\nEnter your 4 digit Password";
        cin>>pin;
        a1.Delete_Account(accnumber,pin);
        cout<<"\n Your account has been successfully deleted";
        break;



        case 7:
        cout<<"Enter your account number";
        cin>>accnumber;
        cout<<"\nEnter your 4 digit Password";
        cin>>pin;
        a1.Update_Account_Details(accnumber,pin);
        cout<<"\n Your account has been successfully updated";
        break;



        case 8:
        cout<<"Enter any key to exit";
        getch();
        exit(0);
        default:
        cout<<"Invalid choice";
        }

        getch();
    }

    

} 



