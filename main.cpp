#include<stdio.h>
#include<conio.h>
#include<fstream.h>
#include<string.h>


class cust
{
	private:
		long int bn;
		long int bd;
		char cn[20];
		char ca[30];
		long int ccn;
		int dc[8];
		int dp[8];
		int ba;
	
	public:
		void get(int *c,int *p)
		{
			cout<<"Enter Bill Numnber:";cin>>bn;
			cout<<"Enter Bill Date:";cin>>bd;
			cout<<"Enter Customer Name:";cin>>cn;
			cout<<"Enter Customer Address:";cin>>ca;
			cout<<"Enter Credit Card Number:";cin>>ccn;
			for(int i=0;i<8;i++,p++,c++)
			{
				dc[i]=*c;
				dp[i]=*p;
			}
		}

		void show()
		{
			cout<<bn<<"\t"<<bd<<"\t"<<cn<<"\t"<<ca<<"\t"<<endl;
			cout<<"\n--------------------------------------------\n"<<endl;
			ba=0;
			for(int i=0;i<8;i++)
			{
				cout<<(i+1)<<"\t"<<dc[i]<<"\t\t"<<dp[i]<<endl;
			   ba=ba+dp[i];
			}
			cout<<"\n--------------------------------------------\n"<<endl;
			cout<<"Total Bill : "<<ba<<endl;
		}
};


class dish
{
	private:
		int dc;
		char dn[20];
		int dp;

	public:
		void get()
		{
			cout<<"Enter Dish Code:";cin>>dc;
			cout<<"Enter Dish Name:";cin>>dn;
			cout<<"Enter Dish Price:";cin>>dp;
		}

		void show()
		{
			cout<<dc<<"\t\t"<<dn<<endl;
		}
		
		int dishcode()
		{
			return dc;
		}
		
		int dpr()
		{
			return dp;
		}
};


main()
{
	int ch;
	int dscd[8],dp[8];
	cust cm;
	dish ds;
	fstream  fcm,fds;
	do
	{
		clrscr();
		cout<<
			"1.Enter New Dish\n"
			"2.Enter and append customer details\n"
			"3.Display all dishes\n"
			"4.Display Customer Information\n"
			"5.Exit\nEnter Your Choice:";
			cin>>ch;
		switch(ch)
		{
			case 1:
				fds.open("dish.b",ios::app|ios::out);
				ds.get();
				fds.write((char*)&ds,sizeof(ds));
				fds.close();
				break;
			case 2:
				fcm.open("cust.b",ios::app|ios::out);
				fds.open("dish.b",ios::in);
				int f=0;
				char ch;
				for(int i=0;i<8;i++)
				{
					f=0;
					cout<<"Enter Dish Code :";
					cin>>dscd[i];
					fds.read((char*)&ds,sizeof(ds));
					while(!fds.eof())
					{
						if(dscd[i]==ds.dishcode())
						{
							f=1;
							break;
						}
						fds.read((char*)&ds,sizeof(ds));
					}
					if(f==0)
						cout<<"Dish Not Found :Try Again"<<endl;
					else
						dp[i]=ds.dpr();
					fds.seekg(0);
				}
				cm.get(dscd,dp);
				fcm.write((char*)&cm,sizeof(cm));
				cm.show();
				fds.close();
				fcm.close();
				break;
			case 3:
				fds.open("dish.b",ios::in);
				cout<<"Dish Code"<<"\t"<<"Dish Name"<<endl;
				fds.read((char*)&ds,sizeof(ds));
				while(!fds.eof())
				{
					ds.show();
					fds.read((char*)&ds,sizeof(ds));
				}
				fds.close();
				break;
			case 4:
				fcm.open("cust.b",ios::in);
				cout<<"Bill No"<<"\t"<<"Bill Dt"<<"\t\t"<<"Name"<<"\t"<<"Address"<<"\t"<<"\t"<<"Dish Code"<<"\t"<<"Bill"<<endl;
				fcm.read((char*)&cm,sizeof(cm));
				while(!fcm.eof())
				{
					cm.show();
					fcm.read((char*)&cm,sizeof(cm));
				}
				fcm.close();
				break;
			case 5:
				cout<<"Thank you";
				break;
			default:
				cout<<"Invalid Input"
		}
		cout<<"\n\nPress any key to continue.......\n\n";
		getch();
	}
	while(ch!=5);
	getch();
}
