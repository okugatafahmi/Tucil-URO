#include<iostream>
#include<vector>
#include<string>
#include<fstream>

struct koor{
	int x,y; //baris x, kolom y
	
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

void inputFile(){
	std::cout<<"Hello\n";
}

void inputManual(int &m,int &n,std::vector<std::string> peta,koor a,koor b){
	int find1,find2;
	std::string s;
	std::cin>>m>>n;
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
	for (int i=0;i<m;i++){
		for (int j=0;j<n;j++){
			std::cout<<peta[i][j];
		}
		std::cout<<'\n';
	}
}



int main(){
	int m,n,opt;
	std::vector<std::string> peta;
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
			inputFile();
		}
		else if (opt==2){
			inputManual(m,n,peta,awal,akhir);
		}
		else{
			std::cout<<"Input Anda salah\n";
		}
	} while ((opt!=1)&&(opt!=2));
	
	aStar(m,n,peta,awal,akhir);
	
}
