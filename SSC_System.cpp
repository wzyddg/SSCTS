//学号：1352878
//姓名：王泽宇
//文件名：Main.cpp
//此文件包含程序的所有代码

#include<fstream>
#include<iostream>
#include<map>
#include<cstdlib>
#include<string>
#include<vector>
#include<cstring>
#define MAPV map<string , Ccustomer* >
#define MAPC map<string , Ccard>
#define MAPG map<string , Ccommodity>
#define GOODCODE "GOOD_"
#define VIPCODE "VIP_"
#define CARDCODE "CARD_"
#define ORDERLENGTH 256
using namespace std;

bool checkformat(string a ,string b)    //figure out if the code of
{                                       //VIP/commodity/card is of right format
    a.resize(b.size(),'c');
    return a==b;
}

class Ccommodity            //the class contains information of commodity
{
public:
    Ccommodity()
    {
        Code="Unknown";
        Name="Unknown";
        ProdErea="Unknown";
        Quantity=0;
        BasicPrice=0;
    }
    void print()
    {
        cout<<Name<<"  "<<ProdErea;
        cout<<"  "<<Quantity;
        cout<<"  "<<BasicPrice<<endl;
    }
    string& CODE(){return Code;}
    string& NAME(){return Name;}
    string& PE(){return ProdErea;}
    int& QU(){return Quantity;};
    long double& BP(){return BasicPrice;}
private:
    string Code;
    string Name;
    string ProdErea;
    int Quantity;
    long double BasicPrice;
};

void realact(MAPG & goods ,int & num, istream& is=cin)      //one of the function
{                                                           //that "import" needs

    string code;
    while(is>>code)     //leave try temply
    {
        if(!checkformat(code, GOODCODE ))
            throw 666;
        goods[code];
        if(goods[code].CODE()!="Unknown")
            throw 3.14;
        goods[code].CODE()=code;
        is>>goods[code].NAME();
        is>>goods[code].PE();
        is>>goods[code].BP();
        num++;
    }
}

class Ccustomer         //the basic class of VIP or normal customer
{
public:
    Ccustomer()
    {
        Code="Unknown";
        Name="Unknown";
        Rank="Unknown";
        PhoneNumber="Unknown";
        Gender="Unknown";
        Score=0;
    }

    Ccustomer(string code1,string name1,string rank1,string phonenumber1,string gender1,float score1)
    {
        Code=code1;
        Name=name1;
        Rank=rank1;
        PhoneNumber=phonenumber1;
        Gender=gender1;
        Score=score1;
    }

    int print()
    {
        cout<<Name<<"  "<<Gender<<"  "<<Rank<<" VIP"<<endl;
        cout<<"Phone: "<<PhoneNumber<<"  Score: ";
        cout<<Score<<endl;
    }

    string realrank()
    {
        if(Rank=="Golden")
            return "Golden";
        else if(Rank=="Silver")
        {
            if(Score>=50000)
                return "Golden";
            else return "Silver";
        }
        else
        {
            if(Score>=50000)
                return "Golden";
            else if(Score>=10000)
                return "Silver";
            else
                return "Ordinary";
        }
    }

    long double totalprice(MAPG & shplst)
    {
        long double total=0;
        MAPG::iterator through=shplst.begin();
        for(;through!=shplst.end();through++)
        {
            total+= through->second.QU() * through->second.BP();
        }
        return total;
    }

    virtual long double getscore(MAPG & shplst)=0;
    virtual long double getprice(MAPG & shplst)=0;

    string& CODE(){return Code;}
    string& NAME(){return Name;}
    string& GD(){return Gender;}
    string& PN(){return PhoneNumber;}
    string& RANK(){return Rank;}
    long double& S(){return Score;}
protected:
    string Code;
    string Name;
    string Gender;
    string PhoneNumber;
    string Rank;
    long double Score;
};

class Gvip : public Ccustomer       //class for golden vip
{
public:
    Gvip()
    {
        Rank="Golden";
    }

    long double getscore(MAPG & shplst)
    {
        long double  score=0;
        long double  tmp=getprice(shplst);
        if(tmp<=1000)
            return 1.5*tmp;
        else if(tmp<=5000)
        {
            score=1500+1.8*(tmp-1000);
            return score;
        }
        else
        {
            score=1500+7200+2*(tmp-5000);
            return score;
        }
    }

    long double getprice(MAPG & shplst)
    {
        long double price=0;
        MAPG::iterator through=shplst.begin();
        for(;through!=shplst.end();through++)
        {
            if(through->second.BP()<=10)
                price+= through->second.QU() * through->second.BP();
            else if(through->second.BP()<=20)
                price+= 0.95 * through->second.QU() * through->second.BP();
            else
                price+= 0.9 * through->second.QU() * through->second.BP();
        }
        return price;
    }
};

class Svip : public Ccustomer       //class for silver vip
{
public:
    Svip()
    {
        Rank="Silver";
    }

    long double getscore(MAPG & shplst)
    {
        long double  score=0;
        long double  tmp=getprice(shplst);
        if(tmp<=2000)
            return 1.2*tmp;
        else if(tmp<=5000)
        {
            score=2400+1.5*(tmp-2000);
            return score;
        }
        else
        {
            score=2400+4500+1.8*(tmp-5000);
            return score;
        }
    }

    long double getprice(MAPG & shplst)
    {
        long double  price=0;
        long double  tmp=totalprice(shplst);
        if(tmp<=1000)
            return 0.95*tmp;
        else if(tmp<=2000)
        {
            price=950+0.9*(tmp-1000);
            return price;
        }
        else
        {
            price=950+900+0.85*(tmp-2000);
            return price;
        }
    }
};

class Ovip : public Ccustomer       //class for ordinary vip
{
public:
    Ovip()
    {
        Rank="Ordinary";
    }

    long double getscore(MAPG & shplst)
    {
        return 0.5*getprice(shplst);
    }

    long double getprice(MAPG & shplst)
    {
        long double  price=0;
        long double  tmp=totalprice(shplst);
        if(tmp<=2000)
            return tmp;
        else if(tmp<=5000)
        {
            price=2000+0.95*(tmp-2000);
            return price;
        }
        else
        {
            price=2000+0.95*3000+0.9*(tmp-5000);
            return price;
        }
    }
};

class Norm : public Ccustomer       //class for normal customer and basic class of vip
{
public:
    Norm()
    {
        Rank="Notatall";
    }

    long double getscore(MAPG & shplst)
    {
        return 0;
    }

    long double getprice(MAPG & shplst)
    {
        return totalprice(shplst);
    }
};

int selectrank(const string & Rank , Ccustomer* & getvip )      //give the pointer a right instance
{
    if(Rank=="Ordinary")
    {
        getvip=new Ovip;
        return 1;
    }
    else if(Rank=="Silver")
    {
        getvip=new Svip;
        return 1;
    }
    else if(Rank=="Golden")
    {
        getvip=new Gvip;
        return 1;
    }else
    throw 666;
}

int correctrank(MAPV& vips)     //the function that give VIP promotion
{
    MAPV::iterator itmapv=vips.begin();
    for(Ccustomer* tmp=NULL;itmapv!=vips.end();itmapv++)
    {
        tmp=itmapv->second;
        if(itmapv->second->RANK()!=itmapv->second->realrank())
        {
            try
            {
                selectrank(itmapv->second->realrank() , itmapv->second );
                itmapv->second->CODE()=tmp->CODE();
                itmapv->second->NAME()=tmp->NAME();
                itmapv->second->GD()=tmp->GD();
                itmapv->second->PN()=tmp->PN();
                itmapv->second->S()=tmp->S();
                delete tmp;
            }
            catch(int err)
            {
                cout<<"this never gonna happen~, haha!"<<endl;
            }
        }
    }
}

void realact(MAPV & vips ,int & num, istream& is=cin)      //one of the function
{                                                          //that "import" needs
    string code;
    string Rank;
    while(is>>code)
    {
        is>>Rank;
        if(!checkformat(code, VIPCODE ))
            throw 666;
        if(vips[code]!=NULL)
            throw 3.14;
        selectrank(Rank,vips[code]);
        vips[code]->CODE()=code;
        vips[code]->RANK()=Rank;
        is>>vips[code]->NAME();
        is>>vips[code]->GD();
        is>>vips[code]->PN();
        is>>vips[code]->S();
        num++;
    }
}

class Ccard     //the class contains information of shopping cards
{
public:
    Ccard()
    {
        Code="Unknown";
        Balance=0;
    }
    string& CODE(){return Code;}
    long double& B(){return Balance;}

private:
    string Code;
    long double Balance;
};

void realact(MAPC & cards ,int & num, istream& is=cin )      //one of the function
{                                                            //that "import" needs
    string code;
    while(is>>code)
    {
        if(!checkformat(code, CARDCODE ))
            throw 666;
        cards[code];
        if(cards[code].CODE() != "Unknown" )
            throw 3.14 ;
        cards[code].CODE()=code;
        is>>cards[code].B();
        num++;
    }
}

template<typename T>
int import(map<string , T > & items , istream& is=cin)      //template function ,used to import data from file
{
    int num=0;

    try
    {
        realact(items,num,is);
    }
    catch(int err1)
    {
        throw err1;
    }
    catch(double err2)
    {
        throw err2;
    }
    cout<<"Import successfully! "<<num<<" items imported."<<endl<<endl;
    return 1;
}

int atoi(char *k)     //get an integer from a c_style-string
{
    int c=0;
    int x=0;
    while(k[c]<'1'||k[c]>'9')
        c++;    //c is on the first position of number
    for(x=c;k[x]>='0'&&k[x]<='9';x++)
        k[x-c]=k[x];
    //x-c numbers
    k[x-c]='\0';
    c=x-c;   //strlen
    x=0;
    //now flip
    for(char tmp=0;x<c/2;x++)
        {
            tmp=k[x];
            k[x]=k[c-x-1];
            k[c-x-1]=tmp;
        }
    //flip successfully
    x=0;
    c=0;
    int y=0,z=0;
    for(;k[c]>='0'&&k[c]<='9';c++)
    {
        y=c;
        z=1;
        for(;y>0;y--)
            z=z*10;
        x=x+(k[c]-'0')*z;
    }
    return x;
}

int StrEdit(string& ord , char* k)      //get commodity's name and number
{                                       //1 as default
    int y=0;
    int num=0;
    for(;k[y]!=0&&k[y]!=' ';y++);
    ord=k;
    ord.resize(y);  //get the code
    if(strlen(k)==ord.size())
    {
    	num=1;
    	return num;
    }
    else
    {
    	for(;k[y]!=0;y++)
    	{
    		if(k[y]>='0'&&k[y]<='9')
    		{
    			num=atoi(k+y);
    			return num;
    		}else;
    	}
    	return 1;
    }
}

Ccustomer * settle( MAPV & vips , MAPG & goods , MAPG & shplst )//accept goods map and vip map's reference ,return vip pointer
{
    Ccustomer *ThisCust;
    string ord;
    cout<<"\nDo you want to shop as a VIP? Input your VIP code or 'no'."<<endl;
    while(cin>>ord)
    {
        if(ord=="no")
        {
            ThisCust=new Norm;
            cout<<"\nOK, you will shop as a normal customer."<<endl;
            break;
        }
        else if(vips.find(ord)==vips.end())
        {
            cout<<"\nWrong VIP code, try again."<<endl;
        }
        else
        {
            ThisCust=vips[ord];
            cout<<"\nOK, you will shop as a "<<ThisCust->RANK()<<" VIP."<<endl;
            ThisCust->print();
            break;
        }
    }

        //customer type got , or a none-VIP customer

    cout<<"\nNow start inputting the codes of goods and its number"<<endl;
    cout<<"separated with space, input 'stop' to stop inputting."<<endl;
    char k[ORDERLENGTH]={0};
    gets(k);
    while(1)
    {
        gets(k);
        ord=k;
        if(strlen(k)>=ORDERLENGTH)
        {
            cout<<"\nThe order is too long, input a new one."<<endl;
            continue;
        }else;
        if(ord=="stop")
        {
            if(!shplst.size())
            {
                cout<<"\nPlease select at least one commodity."<<endl;
                continue;
            }else
            {
                cout<<"\nInputting finished, "<<shplst.size()<<" items selected."<<endl<<endl;
                break;
            }
        }else
        {
            int num;
            num=StrEdit(ord,k);
            if(num<0)
            {
                cout<<"\nWrong order, try again."<<endl;
                continue;
            }else;
            if(goods.find(ord)==goods.end())
            {
                cout<<"\nWrong commodity code, try again."<<endl;
                continue;
            }
            else
            {
                shplst[ord];
                if(!shplst[ord].QU())
                    shplst[ord]=goods[ord];
                else;
                shplst[ord].QU()+=num;
                shplst[ord].print();
            }
        }
    }
    return ThisCust;
   //select done

}

int pay(Ccustomer* ThisCust,MAPG& shplst,MAPC& cards)       //pay and level up
{
    long double Score=ThisCust->getscore(shplst);
    long double Price=ThisCust->getprice(shplst);
    long double Pricesave=Price;
    vector< pair<string,long double> > ways;
    string how;
    cout<<Price<<" to pay."<<endl;
    cout<<"Input 'CA' to pay by cash, 'SC' by shopping card, 'BC' by bank card."<<endl;
    cout<<"It will stop automatically when you paid off the bill."<<endl;
    while(Price>0)
    {
        long double ldtmp=0;
        cin>>how;
        if(how=="CA")
        {
            long double get=0;
            long double pay=0;
            cout<<"Input the number you hand in and the number you want to pay off by cash."<<endl;
            cin>>get>>pay;
            while(get<0||pay<0)
            {
                cout<<"Negative number is not allowed, please change one."<<endl;
                cin>>get>>pay;
            }
            while(pay>get)
            {
                cout<<"Wrong numbers, try again."<<endl;
                cin>>get>>pay;
            }
            if(pay>Price)
                pay=Price;
            else;
            ldtmp=pay;
            how="Cash ";
            cout<<"Cash accepted."<<endl;
            cout<<"You get "<<get-pay<<" for change."<<endl;
        }
        //。如以银行卡支付，用户应录入银行卡号、姓名、消费数额等信息。如以
        //超市购物卡支付，用户应录入购物卡编号与消费数额，系统须检查相应的购物卡数
        //据记录以判断余额是否充足，并更新数据记录（实现扣款操作）
        else if(how=="SC")
        {
            cout<<"Input you shopping card code"<<endl;
            cout<<"and the number you want to pay off by shopping card."<<endl;
            string ScCode;
            long double ldnum=0;
            cin>>ScCode;
            cin>>ldnum;
            while(ldnum<0)
            {
                cout<<"Negative number is not allowed, please change one."<<endl;
                cin>>ldnum;
            }
            if(ldnum>Price)
                ldnum=Price;
            else;
            while(cards.find(ScCode)==cards.end())
            {
                cout<<"The card does not exist, change a card code."<<endl;
                cin>>ScCode;
            }
            if(cards[ScCode].B()<ldnum)
            {
                if(cards[ScCode].B()==0)
                {
                    cout<<"This card has no money left, try another way."<<endl;
                    continue;
                }
                else
                {
                    cout<<"This card does not have enough money, Input 'Use' to use it up,"<<endl;
                    cout<<"others to change a way."<<endl;
                    string AskAgain;
                    cin.sync();
                    cin.clear();
                    cin>>AskAgain;
                    if(AskAgain=="Use")
                        ldnum=cards[ScCode].B();
                    else
                    {
                        cout<<"ShoppingCard paying abandoned."<<endl;
                        continue;
                    }
                }

            }else;
            ldtmp=ldnum;
            how="ShoppingCard "+ScCode;
            cards[ScCode].B()-=ldnum;
            cout<<"ShoppingCard accepted."<<endl;
        }
        else if(how=="BC")
        {
            string BcCode;
            string BcName;
            long double ldnum=0;
            cout<<"Input you bank card code and name."<<endl;
            cin>>BcCode>>BcName;
            cin.sync();
            cin.clear();
            cout<<"Input the number you want to pay off by bank card."<<endl;
            cin>>ldnum;
            while(ldnum<0)
            {
                cout<<"Negative number is not allowed, please change one."<<endl;
                cin>>ldnum;
            }
            if(ldnum>Price)
                ldnum=Price;
            else;
            ldtmp=ldnum;
            how="BankCard "+BcCode+" "+BcName+" ";
            cout<<"BankCard accepted."<<endl;
        }
        else
        {
            cout<<"Wrong order, try again."<<endl;
            cin.sync();
            cin.clear();
            continue;
        }
        Price-=ldtmp;
        pair<string,long double> step(how,ldtmp);
        ways.push_back(step);
    }
    cout<<"\nCongratulations! you have paid off the bill.\n"<<endl;
    ofstream ofile;
    string adfile=ThisCust->NAME()+".txt";
    ofile.open(adfile.c_str(),ios::app);
    for(MAPG::iterator itmapg=shplst.begin();itmapg!=shplst.end();itmapg++)
    {
        cout<<itmapg->second.CODE()<<" ";
        cout<<itmapg->second.NAME()<<" ";
        cout<<itmapg->second.PE()<<" ";
        cout<<itmapg->second.QU()<<endl;
        ofile<<itmapg->second.CODE()<<" ";
        ofile<<itmapg->second.NAME()<<" ";
        ofile<<itmapg->second.PE()<<" ";
        ofile<<itmapg->second.QU()<<endl;
    }
    cout<<"Total Price: "<<Pricesave<<endl;
    ofile<<"Total Price: "<<Pricesave<<endl;
    for(vector< pair<string,long double> >::iterator itvec=ways.begin();itvec!=ways.end();itvec++)
    {
        cout<<itvec->first<<" ";
        cout<<itvec->second<<endl;
        ofile<<itvec->first<<" ";
        ofile<<itvec->second<<endl;
    }
    //score now
    if(ThisCust->RANK()=="Notatall")
        1;  //nothing to be done
    else
    {
        cout<<"get score "<<Score<<endl;
        ofile<<"get score "<<Score<<endl;
        ThisCust->S()+=Score;
        if(ThisCust->realrank()!=ThisCust->RANK())
            cout<<"Congratulations! You've level up to "<<ThisCust->realrank()<<" VIP!"<<endl;
    }
    cout<<endl;
    ofile<<endl<<endl;
    ofile.close();
    return 0;
}

int data_update(MAPV& vips,string& VIPsAddress)     //update VIP to disk
{
    cout<<"Input 'new' to write in a new file for VIPS, others to overwrite the old file."<<endl;
    string order;
    ofstream ofile;
    cin>>order;
    if(order=="new")
    {
        cout<<"Input the name of new file.(only with numbers, letters, '.' and '_')"<<endl;
        cin>>order;
        ofile.open(order.c_str());
        while(!ofile)
        {
            cout<<"Wrong name, try again.(only with numbers, letters, '.' and '_')"<<endl;
            cin>>order;
            ofile.open(order.c_str());
        }
        VIPsAddress=order;
    }
    else
    {
        ofile.open(VIPsAddress.c_str());
    }
    for(MAPV::iterator itmapv=vips.begin();itmapv!=vips.end();itmapv++)
    {
        ofile<<itmapv->second->CODE()<<" ";
        ofile<<itmapv->second->RANK()<<" ";
        ofile<<itmapv->second->NAME()<<" ";
        ofile<<itmapv->second->GD()<<" ";
        ofile<<itmapv->second->PN()<<" ";
        ofile<<itmapv->second->S()<<endl;
    }
    ofile.close();
    cout<<"VIPs file updated successfully!"<<endl;
    return 0;
}

int data_update(MAPC& cards,string CardsAddress)    //update cards to disk
{
    cout<<"Input 'new' to write in a new file for Cards, others to overwrite the old file."<<endl;
    string order;
    ofstream ofile;
    cin>>order;
    if(order=="new")
    {
        cout<<"Input the name of new file.(only with numbers, letters, '.' and '_')"<<endl;
        cin>>order;
        ofile.open(order.c_str());
        while(!ofile)
        {
            cout<<"Wrong name, try again.(only with numbers, letters, '.' and '_')"<<endl;
            cin>>order;
            ofile.open(order.c_str());
        }
        CardsAddress=order;
    }
    else
    {
        ofile.open(CardsAddress.c_str());
    }
    for(MAPC::iterator itmapc=cards.begin();itmapc!=cards.end();itmapc++)
    {
        ofile<<itmapc->second.CODE()<<" ";
        ofile<<itmapc->second.B()<<endl;
    }
    ofile.close();
    cout<<"Shopping Cards file updated successfully!"<<endl;
    return 0;
}

int main()
{
    MAPV vips;          //a map that contains vips
    MAPC cards;         //a map that contains cards
    MAPG goods;         //a map that contains goods
    cout<<"        ************************************************"<<endl;
    cout<<"        *            Supermarket Shopping and          *"<<endl;
    cout<<"        *            Checkout Terminal System          *"<<endl;
    cout<<"        *                  Version 1.4                 *"<<endl;
    cout<<"        *              All Rights Reserved             *"<<endl;
    cout<<"        *           By   Wang Zeyu   1352878           *"<<endl;
    cout<<"        *                   May 2014                   *"<<endl;
    cout<<"        ************************************************"<<endl;

    string FileAddress;
    string CardsAddress;
    string VIPsAddress;
    ifstream ifile;

    //open the goods file
    cout<<"Input the address of file about goods."<<endl;
    GDERR:
    ifile.close();
    cin>>FileAddress;
    ifile.open(FileAddress.c_str());
    while(!ifile)
    {
        cerr<<"wrong address,input another address."<<endl;
        cin>>FileAddress;
        ifile.open(FileAddress.c_str());
    }//file opened
    try
    {
        import(goods,ifile);     //information about goods imported
    }
    catch(int err1)
    {
        cout<<"the file is of wrong format, please change one."<<endl;
        goto GDERR;
    }
    catch(double err2)
    {
        cout<<"there are some same items in the file, please change one."<<endl;
        goto GDERR;
    }
    ifile.close();

    //open the cards file
    cout<<"Input the address of file about shopping cards."<<endl;
    CDERR:
    ifile.close();
    cin>>FileAddress;
    ifile.open(FileAddress.c_str());
    while(!ifile)
    {
        cerr<<"wrong address,input another address."<<endl;
        cin>>FileAddress;
        ifile.open(FileAddress.c_str());
    }//file opened
    try
    {
        import(cards,ifile);     //information about cards imported
    }
    catch(int err1)
    {
        cout<<"the file is of wrong format, please change one."<<endl;
        goto CDERR;
    }
    catch(double err2)
    {
        cout<<"there are some same items in the file, please change one."<<endl;
        goto CDERR;
    }
    CardsAddress=FileAddress;
    ifile.close();


    //open the VIPs file
    cout<<"Input the address of file about VIPs."<<endl;
    VIPERR:
    ifile.close();
    cin>>FileAddress;
    ifile.open(FileAddress.c_str());
    while(!ifile)
    {
        cerr<<"wrong address,input another address."<<endl;
        cin>>FileAddress;
        ifile.open(FileAddress.c_str());
    }//file opened
    try
    {
        import(vips,ifile);     //information about vips imported
    }
    catch(int err1)
    {
        cout<<"the file is of wrong format, please change one."<<endl;
        goto VIPERR;
    }
    catch(double err2)
    {
        cout<<"there are some same items in the file, please change one."<<endl;
        goto VIPERR;
    }
    VIPsAddress=FileAddress;
    ifile.close();
    correctrank(vips);      //make sure every VIP get promoted



    string order;

    //functional part
    while(1)
    {
        cout<<"Input 'quit' to quit, input 'start' to start settling."<<endl;
        while(cin>>order)
        {
            if(order=="quit")
            {
                cout<<"Bye!"<<endl;
                system("pause");
                exit(0);
            }
            else if(order=="start")
                    break;
                else
                    cout<<"Unknown order, try again."<<endl;
        }

        MAPG shplst;        //a shopping list ,something like a subset of MAPG goods
        Ccustomer * ThisCust=NULL;
        ThisCust=settle(vips,goods,shplst);     //settle is done ,get the pointer
        //all clear                             //to the certain VIP

        pay(ThisCust,shplst,cards);             //pay the bill now ,and
        correctrank(vips);                      //get his score and promotion
        if(ThisCust->RANK()=="Notatall")
            delete ThisCust;
        else;
        cout<<"The transaction has ended,"<<endl;
        cout<<"do you want to update the data on hard disk?(yes/no)"<<endl;
        cin.sync();
        cin.clear();
        cin>>order;
        if(order=="yes")
        {
            data_update(vips,VIPsAddress);      //update the file on disk
            data_update(cards,CardsAddress);    //update the file on disk
        }
        else;
        shplst.clear();
        cout<<"\n\n"<<endl;
    }
}
