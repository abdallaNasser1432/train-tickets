
#include <iostream>
#include <fstream>
#include <string>

using namespace std;
int flag=0;
char check;
int choose;

class Passenger {
public:
    int trainId;
    int coachNumber;
    int seat;
    string fromStation;
    string toStation;
    string date;
    double startTime;
    double arrivalTime;
    string passengerName ;

};


void write(Passenger &p);
void searchBySeat(ifstream &f,Passenger &p);
void searchByName(ifstream &f,Passenger &p);
void passengerInTrain(ifstream &f,Passenger &p);
void passengerInCoach(ifstream &f,Passenger &p);
void count1(ifstream &f,Passenger &p);
void count2(ifstream &f,Passenger &p);
void deleteTicket(ifstream &f,Passenger &p);
void deleteAllTicket(ifstream &f,Passenger &p);
void updateSeats(ifstream &f,Passenger &p);


int main()
{

    Passenger p;
    ifstream f;
    cout<<"if you want write  a ticket press y if you don't press n :\n";
    cin>>check;

    if (check=='y')
        write(p);

    cout<<"if you want do any operations press y,if you don't enter n :\n ";
    cin>>check;

    if (check=='y'){
        do {
            cout<<"-if you want search by name press 0\n "
                  "-if you want search by seats press 1\n "
                  "-if you want know all passenger in train press 2\n "
                  "-if you want know all passenger in coach press 3\n "
                  "-if you want cancelled any ticket press 4\n "
                  "-if you want cancelled all ticket in the train press 5\n "
                  "-if you want know number of passenger in train and check if it's full or not press 6\n "
                  "-if you want know number of passenger in coach and check if it's full or not press 7\n"
                  "-if you want change your seat press 8\n ";
            cout<<"enter a number :";
            cin>>choose;
            switch (choose) {
                case 0:
                    searchByName(f,p);
                    break;
                case 1:
                    searchBySeat(f,p);
                    break;
                case 2:
                    passengerInTrain(f,p);
                    break;
                case 3:
                    passengerInCoach(f,p);
                    break;
                case 4:
                    deleteTicket(f,p);
                    break;
                case 5:
                    deleteAllTicket(f,p);
                    break;
                case 6:
                    count1(f,p);
                    break;
                case 7:
                    count2(f,p);
                    break;
                case 8:
                    updateSeats(f,p);
                    break;
                default:
                    cout<<"you entered wrong number \n";
                    break;

            }
            cout<<"if you want do another operations press y,if you don't enter n :\n ";
            cin>>check;
        } while (check=='y');
    }

    return 0;
}

void write(Passenger &p){
    ofstream f("RAILWAY SYSTEM.txt",ios::app);
    ifstream f2;
    Passenger p2;
    do {
        cout<<"please enter  the passenger name in these form firstName-lastName:\n";
        cin>>p.passengerName;

        cout<<"please enter the from-station :\n";
        cin>>p.fromStation;

        cout<<"we have only 3 travel \n"
              "-if you want go to alexandria press 1\n"
              "-if you want go to luxor press 2\n"
              "-if you want go to suez press 3\n";
        do {

            cout<<"enter a number :";
            cin>>choose;
            switch (choose) {
                case 1:
                    p.toStation="alexandria";
                    p.trainId=1;
                    break;
                case 2:
                    p.toStation="luxor";
                    p.trainId=2;
                    break;
                case 3:
                    p.toStation="suez";
                    p.trainId=3;
                    break;
                default:
                    cout<<"you entered a wrong number ,please try again\n";
                    break;
            }
        } while (choose<1||choose>3);


        cout<<"please enter startTime :\n";
        cin>>p.startTime;

        if (p.trainId==1)
            p.arrivalTime=p.startTime+4;
        else if (p.trainId==2)
            p.arrivalTime=p.startTime+8;
        else
            p.arrivalTime=p.startTime+2;
        do
        {
            cout<<"please enter coach number :\n";
            cin>>p.coachNumber;
            if (p.coachNumber>4)
                cout<<"sorry,the train has only 4 coaches \n";
        } while (p.coachNumber>4);
        f.close();
        f2.open("RAILWAY SYSTEM.txt",ios::in);

        do
        {
            f2.seekg(0);
            cout<<"please enter seat number :\n";
            cin>>p.seat;
            flag=0;
            while (f2>>p2.passengerName&&f2>>p2.fromStation&&f2>>p2.toStation&&f2>>p2.trainId&&f2>>
                   p2.startTime&&f2>>p2.arrivalTime&&f2>>p2.coachNumber&&f2>>p2.seat&&f2>>p2.date)
            {
                if ((p.trainId==p2.trainId)&&(p.coachNumber==p2.coachNumber)&&(p.seat==p2.seat)&&
                    (p.startTime==p2.startTime)){
                    flag=1;
                    break;
                }
            }
            if (p.seat>10)
                cout<<"sorry, the coach has only 10 seats \n";
            if (flag==1)
                cout<<"sorry, the seat is already taken \n";
        } while (p.seat>10||flag==1);
        cout<<"please enter the date in these form --/--/---- :\n";
        cin>>p.date;
        f2.close();
        f.open("RAILWAY SYSTEM.txt",ios::app);
        f<<p.passengerName<<" "<<p.fromStation<<" "<<p.toStation<<" "<<p.trainId<<
         " "<<p.startTime<<" "<<p.arrivalTime<<" "<<p.coachNumber<<" "<<p.seat<<" "<<p.date<<endl;
        cout<<"if you want to enter another ticket enter y ,if you don't enter n :\n";
        cin>>check;
    }while (check=='y');

    f.close();
}

void searchByName(ifstream &f,Passenger &p){
    string name;
    f.open("RAILWAY SYSTEM.txt",ios::in);
    cout<<"enter the name you need to search it :\n";
    cin>>name;
    flag=0;
    if (f.is_open()){


        while (f>>p.passengerName&&f>>p.fromStation&&f>>p.toStation&&f>>p.trainId&&f>>
               p.startTime&&f>>p.arrivalTime&&f>>p.coachNumber&&f>>p.seat&&f>>p.date)
        {

            if (name==p.passengerName){
                cout<<"Train  coach   seat  s-time  e-time   f-station    t-station    name \n";
                cout<<"  "<<p.trainId<<"      "<<p.coachNumber<<"      "<<p.seat<<"     "<<p.startTime<<
                    ":00   "<<p.arrivalTime<<":00    "<<p.fromStation<<"     "<<p.toStation<<"  "<<p.passengerName<<"\n";
                flag=1;
                break;
            }
        }
        if (flag==0)
            cout<<"i didn't find this name!\n";
        f.close();
    }
    else
        cout<<"i didn't found these file ";

}

void searchBySeat(ifstream &f,Passenger &p){
    int train,coach,seat;
    f.open("RAILWAY SYSTEM.txt",ios::in);
    cout<<"enter the train id :\n";
    cin>>train;
    cout<<"enter the coach number :\n";
    cin>>coach;
    do {
        cout<<"enter the seat you need to search it :\n";
        cin>>seat;
        if (seat>10)
            cout<<"the coach has only 10 seats,please try again\n";
    } while (seat>10);
    flag=0;
    if (f.is_open()){

        while (f>>p.passengerName&&f>>p.fromStation&&f>>p.toStation&&f>>p.trainId&&f>>
               p.startTime&&f>>p.arrivalTime&&f>>p.coachNumber&&f>>p.seat&&f>>p.date)
        {

            if ((train==p.trainId)&&(coach==p.coachNumber)&&(seat==p.seat)){
                cout<<"Train  coach   seat  s-time  e-time   f-station    t-station    name \n";
                cout<<"  "<<p.trainId<<"      "<<p.coachNumber<<"      "<<p.seat<<"     "<<p.startTime<<
                    ":00   "<<p.arrivalTime<<":00    "<<p.fromStation<<"     "<<p.toStation<<"  "<<p.passengerName<<"\n";
                flag=1;
                break;
            }
        }
        if (flag==0)
            cout<<"no one on these seat\n";
        f.close();
    }
    else
        cout<<"i didn't found these file\n";
}

void passengerInTrain(ifstream &f,Passenger &p){
    int train;
    f.open("RAILWAY SYSTEM.txt",ios::in);
    cout<<"enter the train id :\n";
    cin>>train;
    int x=0;
    flag=0;
    if (f.is_open()){

        while (f>>p.passengerName&&f>>p.fromStation&&f>>p.toStation&&f>>p.trainId&&f>>
               p.startTime&&f>>p.arrivalTime&&f>>p.coachNumber&&f>>p.seat&&f>>p.date)
        {

            if (train==p.trainId){
                if (x==0){
                    cout<<"coach   seat  s-time  e-time   f-station    t-station    name \n";
                    x=1;
                }
                cout<<"  "<<p.coachNumber<<"      "<<p.seat<<"     "<<p.startTime<<
                    ":00   "<<p.arrivalTime<<":00    "<<p.fromStation<<"     "<<p.toStation<<"  "<<p.passengerName<<"\n";
                flag=1;
            }
        }
        if (flag==0)
            cout<<"no one on the train\n";
        f.close();
    }
    else
        cout<<"i didn't found these file\n";
}

void passengerInCoach(ifstream &f,Passenger &p){
    int train,coach;
    f.open("RAILWAY SYSTEM.txt",ios::in);
    cout<<"enter the train id :\n";
    cin>>train;
    do
    {
        cout<<"enter coach number :\n";
        cin>>coach;
        if (coach>4)
            cout<<"sorry,the train has only 4 coaches \n";
    } while (coach>4);
    int x=0;
    flag=0;
    if (f.is_open()){

        while (f>>p.passengerName&&f>>p.fromStation&&f>>p.toStation&&f>>p.trainId&&f>>
               p.startTime&&f>>p.arrivalTime&&f>>p.coachNumber&&f>>p.seat&&f>>p.date)
        {

            if ((train==p.trainId)&&(coach==p.coachNumber)){
                if (x==0){
                    cout<<"coach   seat  s-time  e-time       name \n";
                    x=1;
                }
                cout<<"  "<<p.coachNumber<<"      "<<p.seat<<"     "<<p.startTime<<
                    ":00   "<<p.arrivalTime<<":00    "<<p.passengerName<<"\n";
                flag=1;
            }
        }
        if (flag==0)
            cout<<"no one on these coach \n";
        f.close();
    }
    else
        cout<<"i didn't found these file\n";
}

void count1(ifstream &f,Passenger &p){
    int train;
    int count=0;
    f.open("RAILWAY SYSTEM.txt",ios::in);
    cout<<"enter the train id :\n";
    cin>>train;
    if (f.is_open()){


        while (f>>p.passengerName&&f>>p.fromStation&&f>>p.toStation&&f>>p.trainId&&f>>
               p.startTime&&f>>p.arrivalTime&&f>>p.coachNumber&&f>>p.seat&&f>>p.date)
        {
            if (train==p.trainId)
                count++;
        }

        if (count==0)
            cout<<"the train is empty!\n";
        else if (count==40)
            cout<<"the train is full\n";
        else
            cout<<count<<endl;

        f.close();

    }
    else
        cout<<"i didn't found these file\n";

}

void count2(ifstream &f,Passenger &p){
    int train,coach;
    int count=0;
    f.open("RAILWAY SYSTEM.txt",ios::in);
    cout<<"enter the train id :\n";
    cin>>train;
    cout<<"enter coach number :\n";
    cin>>coach;
    if (f.is_open()){


        while (f>>p.passengerName&&f>>p.fromStation&&f>>p.toStation&&f>>p.trainId&&f>>
               p.startTime&&f>>p.arrivalTime&&f>>p.coachNumber&&f>>p.seat&&f>>p.date)
        {
            if (train==p.trainId&&coach==p.coachNumber)
                count++;
        }

        if (count==0)
            cout<<"the coach is empty!\n";
        else if (count==10)
            cout<<"the coach is full\n";
        else
            cout<<count<<endl;
        f.close();

    }
    else
        cout<<"i didn't found these file\n";
}

void deleteTicket(ifstream &f,Passenger &p){
    string name;
    f.open("RAILWAY SYSTEM.txt",ios::in);
    ofstream temp("temp.txt",ios::out);
    cout<<"enter the name of ticket  you need to delete it :\n";
    cin>>name;
    flag=0;
    if (f.is_open()){


        while (f>>p.passengerName&&f>>p.fromStation&&f>>p.toStation&&f>>p.trainId&&f>>
               p.startTime&&f>>p.arrivalTime&&f>>p.coachNumber&&f>>p.seat&&f>>p.date)
        {

            if (name!=p.passengerName){
                temp<<p.passengerName<<" "<<p.fromStation<<" "<<p.toStation<<" "<<p.trainId<<
                    " "<<p.startTime<<" "<<p.arrivalTime<<" "<<p.coachNumber<<" "<<p.seat<<" "<<p.date<<endl;
            }
            else{
                flag=1;
                cout<<"Done\n";
            }

        }
        if (flag==0)
            cout<<"i didn't find this name!\n";
        f.close();
        temp.close();
        remove("RAILWAY SYSTEM.txt");
        rename("temp.txt","RAILWAY SYSTEM.txt");
    }
    else
        cout<<"i didn't found these file ";
}

void deleteAllTicket(ifstream &f,Passenger &p){
    int trainId;
    f.open("RAILWAY SYSTEM.txt",ios::in);
    ofstream temp("temp.txt",ios::out);
    cout<<"enter the number of train  :\n";
    cin>>trainId;
    flag=0;
    if (f.is_open()){


        while (f>>p.passengerName&&f>>p.fromStation&&f>>p.toStation&&f>>p.trainId&&f>>
               p.startTime&&f>>p.arrivalTime&&f>>p.coachNumber&&f>>p.seat&&f>>p.date)
        {

            if (trainId!=p.trainId){
                temp<<p.passengerName<<" "<<p.fromStation<<" "<<p.toStation<<" "<<p.trainId<<
                    " "<<p.startTime<<" "<<p.arrivalTime<<" "<<p.coachNumber<<" "<<p.seat<<" "<<p.date<<endl;
            }
            else{
                flag=1;
                cout<<"Done\n";
            }
        }
        if (flag==0)
            cout<<"no one on the train \n";
        f.close();
        temp.close();
        remove("RAILWAY SYSTEM.txt");
        rename("temp.txt","RAILWAY SYSTEM.txt");
    }
    else
        cout<<"i didn't found these file ";
}

void updateSeats(ifstream &f,Passenger &p){
    int trainId,coach,seat1,seat2;
    bool found= false;
    f.open("RAILWAY SYSTEM.txt",ios::in);
    ofstream temp("temp.txt",ios::out);
    cout<<"enter the train id :\n";
    cin>>trainId;
    cout<<"enter number of the coach :\n";
    cin>>coach;
    cout<<"enter your current seat :\n";
    cin>>seat1;
    do {

        cout << "enter the seat you want :\n";
        cin >> seat2;
        flag = 0;
        f.seekg(0,ios::beg);
        if (f.is_open()) {


            while (f>>p.passengerName&&f>>p.fromStation&&f>>p.toStation&&f>>p.trainId&&f>>
                   p.startTime&&f>>p.arrivalTime&&f>>p.coachNumber&&f>>p.seat&&f>>p.date)
            {
                if (seat2 == p.seat&&trainId==p.trainId&&coach==p.coachNumber) {
                    flag = 1;
                    cout<<"sorry, these seat is reserved\n";
                    break;
                }
            }
        }
        else
            cout << "i didn't found these file \n";

    } while (flag==1);

    f.close();
    f.open("RAILWAY SYSTEM.txt",ios::in);
    flag=0;
    if (f.is_open()) {
        while (f>>p.passengerName&&f>>p.fromStation&&f>>p.toStation&&f>>p.trainId&&f>>
               p.startTime&&f>>p.arrivalTime&&f>>p.coachNumber&&f>>p.seat&&f>>p.date)
        {

            if (seat1==p.seat&&trainId==p.trainId&&coach==p.coachNumber){
                flag=1;
                p.seat=seat2;
                temp<<p.passengerName<<" "<<p.fromStation<<" "<<p.toStation<<" "<<p.trainId<<
                    " "<<p.startTime<<" "<<p.arrivalTime<<" "<<p.coachNumber<<" "<<p.seat<<" "<<p.date<<endl;
            }
            else{
                temp<<p.passengerName<<" "<<p.fromStation<<" "<<p.toStation<<" "<<p.trainId<<
                    " "<<p.startTime<<" "<<p.arrivalTime<<" "<<p.coachNumber<<" "<<p.seat<<" "<<p.date<<endl;
            }

        }
        if (flag==0)
            cout<<"i didn't find your seat\n";
        f.close();
        temp.close();
        remove("RAILWAY SYSTEM.txt");
        rename("temp.txt","RAILWAY SYSTEM.txt");
    }
    else
        cout << "i didn't found these file \n";

}

