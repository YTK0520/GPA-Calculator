//
//  main.cpp
//  GPA Calculator
//
//  Created by yvonne90520 on 2021/8/30.
//

#include <iostream>
#include <string>
#include <fstream>

using namespace std;
struct _Course{
    string CourseName;
    int CourseCredit;
    int CourseScore;
    int CourseGpa;
};
typedef struct _Course Course;

class GpaCalculator
{
public:
    void login(string sname){
        int m=0,i,c=0;
        
        fstream file;
        file.open("book", ios::in);
        file>>m;
        for(i=0;i<m;i++){
            file>>Name[i]>>Credit[i]>>Gpa[i];
        }
        file.close();
        
        for(i=0;i<m;i++){
            if(sname==Name[i]){
                cout<<"GPA Cal: Welcome "<<sname<<"!"<<endl;
                c=1;
            }
        }
        if(c==0){
            cout<<"GPA Cal: Welcome first time user "<<sname<<"!"<<endl;
        }
    }
    
    void logout(string sname, int a, int b){
        int m=0,i,c=0;
        double avg=(double)a/b;
        
        fstream file;
        file.open("book", ios::in);
        file>>m;
        for(i=0;i<m;i++){
            file>>Name[i]>>Credit[i]>>Gpa[i];
        }
        file.close();
        
        for(i=0;i<m;i++){
            if(sname==Name[i]){
                Credit[i]=b;
                Gpa[i]=avg;
                file.open("book", ios::out);
                file<<m<<endl;
                for(i=0;i<m;i++){
                    file<<Name[i]<<" "<<Credit[i]<<" "<<setprecision(3)<<fixed<<Gpa[i]<<endl;
                    c=1;
                }
                file.close();
            }
        }
        if(c==0){
            Credit[m]=b;
            Gpa[m]=avg;
            Name[m]=sname;
            file.open("book", ios::out);
            file<<m+1<<endl;
            for(i=0;i<m+1;i++){
                file<<Name[i]<<" "<<Credit[i]<<" "<<Gpa[i]<<endl;
            }
            file.close();
        }
    }
private:
    string Name[100];
    int Credit[100];
    double Gpa[100];
};
int main(int argc, const char * argv[]) {
    char op;
    int n=0,i,m=0;
    int sumGpa=0, sumCredit=0, sg=0, sc=0;
    double avg;
    string sname1;
    GpaCalculator s1;
    Course c[100];
    fstream file;
    
    cout<<"=== GPA Calculator ==="<<endl;
    cout<<"Student name: ";
    cin>>sname1;
    file.open(sname1, ios::in);
    file>>n;
    for(i=0;i<n;i++){
        file>>c[i].CourseName>>c[i].CourseCredit>>c[i].CourseScore>>c[i].CourseGpa;
    }
    file.close();
    
    s1.login(sname1);
    
    while(1){
        cout<<"GPA Cal: Hello "<<sname1<<", please choose an option:"<<endl;
        cout<<"i: input data"<<endl;
        cout<<"l: list data"<<endl;
        cout<<"s: save data"<<endl;
        cout<<"r: read data"<<endl;
        cout<<"q: quit GPA Calculator"<<endl;
        cin>>op;
        switch(op)
        {
            case 'i':
                cout<<"Course Name: ";
                cin>>c[n].CourseName;
                cout<<"Course Credit: ";
                cin>>c[n].CourseCredit;
                cout<<"Course Score: ";
                cin>>c[n].CourseScore;
                if(c[n].CourseScore>80){
                    c[n].CourseGpa=4;
                }
                else if(80>=c[n].CourseScore && c[n].CourseScore>70){
                    c[n].CourseGpa=3;
                }
                else if(70>=c[n].CourseScore && c[n].CourseScore>60){
                    c[n].CourseGpa=2;
                }
                else if(60>=c[n].CourseScore && c[n].CourseScore>50){
                    c[n].CourseGpa=1;
                }
                else {
                    c[n].CourseGpa=0;
                }
                n++;
                m++;
                break;
            case'l':
                for(i=0;i<m;i++){
                    cout<<i+1<<". "<<c[n-m+i].CourseName<<endl;
                    cout<<"Course Credit: "<<c[n-m+i].CourseCredit<<endl;
                    cout<<"Course Score: "<<c[n-m+i].CourseScore<<endl;
                    cout<<"Course GPA: "<<c[n-m+i].CourseGpa<<endl;
                    cout<<"===================="<<endl;
                }
                break;
            case 's':
                file.open(sname1, ios::out);
                file<<n<<endl;
                for(i=0;i<n;i++){
                    file<<c[i].CourseName<<" "<<c[i].CourseCredit<<" "<<c[i].CourseScore<<" "<<c[i].CourseGpa<<endl;
                }
                file.close();
                break;
            case 'r':
                
                file.open(sname1, ios::in);
                file>>n;
                for(i=0;i<n;i++){
                    file>>c[i].CourseName>>c[i].CourseCredit>>c[i].CourseScore>>c[i].CourseGpa;
                    sumCredit+=c[i].CourseCredit;
                    sumGpa+=c[i].CourseGpa*c[i].CourseCredit;
                }
                file.close();
                
                avg=(double)sumGpa/sumCredit;
                cout<<"Total: "<<n<<" courses"<<endl;
                for(i=0;i<n;i++){
                    cout<<i+1<<". "<<c[i].CourseName<<endl;
                    cout<<"Course Credit: "<<c[i].CourseCredit<<endl;
                    cout<<"Course Score: "<<c[i].CourseScore<<endl;
                    cout<<"Course GPA: "<<c[i].CourseGpa<<endl;
                    cout<<"===================="<<endl;
                }
                cout<<"Total Credits: "<<sumCredit<<endl;
                cout<<"Average GPA: "<<setprecision(3)<<fixed<<avg<<endl;
                break;
            case 'q':
                
                file.open(sname1, ios::in);
                file>>n;
                for(i=0;i<n;i++){
                    file>>c[i].CourseName>>c[i].CourseCredit>>c[i].CourseScore>>c[i].CourseGpa;
                    sc+=c[i].CourseCredit;
                    sg+=c[i].CourseGpa*c[i].CourseCredit;
                }
                file.close();
                
                s1.logout(sname1, sg, sc);
                
                return 0;
                break;
        }
        getchar();
        system("clear");
    }
    return 0;
}
