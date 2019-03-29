#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include<utility>
#include<cmath>
#include<queue>

typedef std::vector<std::vector<std::pair<int,int> > > pPath;

struct koor{
    int x,y; //baris x, kolom y
    int prior;
    int f(koor b){
        return pow(x-b.x,2)+pow(y-b.y,2);
    }
};

int find(int n,std::string s,char c){
    bool ada=false;
    int i=0;
    while ((i<n) && (!ada)){
        if (s[i]==c){
            ada=true;
        }
        else{
            i++;
        }
    }
    return ada? i:n;
}

void inputFile(int &m,int &n,std::vector<std::string> &peta,koor &a,koor &b,pPath &parent){
    std::string file;
    std::cout<<"\nMasukkan directive file: ";
    std::cin>>file;
    std::ifstream inp (file);
    
    int find1,find2;
    std::string s;
    inp>>m>>n;
    for (int i=0;i<m;i++){
        std::vector<std::pair<int,int> > temp;
        for (int j=0;j<n;j++){
            temp.push_back(std::make_pair(i,j));
        }
        parent.push_back(temp);
    }
    for (int i=0;i<m;i++){
        inp>>s;
        peta.push_back(s);
        find1=find(n,s,'1');
        find2=find(n,s,'2');
        if (find1!=n){
            a.x=i;
            a.y=find1;
        }
        else if (find2!=n){
            b.x=i;
            b.y=find2;
        }
    }
    inp.close();
}

void inputManual(int &m,int &n,std::vector<std::string> &peta,koor &a,koor &b,pPath &parent){
    int find1,find2;
    std::string s;
    std::cin>>m>>n;
    for (int i=0;i<m;i++){
        std::vector<std::pair<int,int> > temp;
        for (int j=0;j<n;j++){
            temp.push_back(std::make_pair(i,j));
        }
        parent.push_back(temp);
    }
    for (int i=0;i<m;i++){
        std::cin>>s;
        peta.push_back(s);
        find1=find(n,s,'1');
        find2=find(n,s,'2');
        if (find1!=n){
            a.x=i;
            a.y=find1;
        }
        else if (find2!=n){
            b.x=i;
            b.y=find2;
        }
    }
}

void outputFile(int &m,int &n,std::vector<std::string> &peta,koor &a,koor &b,pPath &parent) {
    std::ofstream out ("/Users/mirzaalarsyad/Desktop/mirza/mirza/output.txt");
    int x,y,temp;
    x=parent[b.x][b.y].first;
    y=parent[b.x][b.y].second;
    while ((x!=a.x)||(y!=a.y)){
        peta[x][y]= '!';
        temp=x;
        x=parent[x][y].first;
        y=parent[temp][y].second;
    }
    for (int i=0;i<m;i++){
        for (int j=0;j<n;j++){
            out<<peta[i][j];
        }
        out<<'\n';
    }
}
bool isValid(koor a,std::pair<int,int> p,int m,int n,int &x,int &y){
    if ((a.x+p.first>=0)&&(a.x+p.first<m)&&
        (a.y+p.second>=0)&&(a.y+p.second<n)){
        x=a.x+p.first;
        y=a.y+p.second;
        return true;
    }
    return false;
}

void aStar(int &m,int &n,std::vector<std::string> &peta,koor &awal,koor &akhir,pPath &parent){
    auto banding=[](const koor &a,const koor &b){
        return a.prior>b.prior;
    };
    std::priority_queue<koor,std::vector<koor>,decltype(banding)> q(banding);
    awal.prior=awal.f(akhir);
    akhir.prior=akhir.f(akhir);
    
    std::vector<std::vector<bool> > sudah;
    for (int i=0;i<m;i++){
        std::vector<bool> t;
        for (int j=0;j<n;j++){
            t.push_back(false);
        }
        sudah.push_back(t);
    }
    
    std::pair<int,int> w[4]={ {0,1},{1,0},{0,-1},{-1,0}};
    koor now,temp;
    q.push(awal);
    int x,y;
    bool temu=false;
    while ((!q.empty()) && (!temu)){
        now=q.top();
        q.pop();
        std::cout<<now.x<<' '<<now.y<<'\n';
        if ((now.x==akhir.x) && (now.y==akhir.y)){
            temu=true;
        }
        else{
            for (int i=0;i<4;i++){
                if (isValid(now,w[i],m,n,x,y)){
                    if ((!sudah[x][y]) && (peta[x][y]!='x')){
                        sudah[x][y]=true;
                        parent[x][y]=std::make_pair(now.x,now.y);
                        temp.x=x;
                        temp.y=y;
                        temp.prior=temp.f(akhir);
                        q.push(temp);
                    }
                }
            }
        }
    }
}


int main(){
    int m,n,opt;
    std::vector<std::string> peta;
    pPath parent;
    koor awal,akhir;
    
    std::cout<<"=======================\n";
    std::cout<<"     Implementasi A*   \n";
    std::cout<<"=======================\n";
    do{
        std::cout<<'\n';
        std::cout<<"Pilih menu:\n";
        std::cout<<"1. File Input\n";
        std::cout<<"2. Manual Input\n";
        std::cout<<"Masukkan pilihan: ";
        std::cin>>opt;
        if (opt==1){
            inputFile(m,n,peta,awal,akhir,parent);
        }
        else if (opt==2){
            inputManual(m,n,peta,awal,akhir,parent);
        }
        else{
            std::cout<<"Input Anda salah\n";
        }
    } while ((opt!=1)&&(opt!=2));
    
    aStar(m,n,peta,awal,akhir,parent);
    outputFile(m,n,peta,awal,akhir,parent);
    /*
     Looping untuk menampilkan path robot ke layar terminal
     
     for (int i=0;i<m;i++){
        for (int j=0;j<n;j++){
            std::cout<<peta[i][j];
        }
        std::cout<<'\n';
    }
     std::cout<<awal.x<<' '<<awal.y<<'\n'; {koordinat awal dari robot}
     std::cout<<akhir.x<<' '<<akhir.y<<'\n'; {koordinat akhir dari robot}
     */
    
}

