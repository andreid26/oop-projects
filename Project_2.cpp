#include <iostream>
#include <stdlib.h>
using namespace std;

class Contract{
protected:
    int nrContract;
    int an;
    string beneficiar;
    string furnizor;
    float valoare;
    static int numar_contracte;
public:
    Contract(int, int, string, string, float);
    virtual~Contract();
    Contract(const Contract&);
    int get_nrcontract() const;
    void set_nrcontract(int);
    int get_an() const;
    void set_an(int);
    string get_beneficiar() const;
    void set_beneficiar(string);
    string get_furnizor() const;
    void set_furnizor(string);
    float get_valoare() const;
    void set_valoare(float);
    virtual int get_valoare_incasata() const = 0;
    static int numarContracte(){
        return numar_contracte;
    }
    virtual void citire(istream&);
    virtual void afisare(ostream&);
    Contract& operator=(const Contract&);
    friend istream& operator>>(istream&, Contract&);
    friend ostream& operator<<(ostream&, Contract&);
};

int Contract::numar_contracte;

Contract::Contract(int nrContract=0, int an=0, string beneficiar="", string furnizor="", float valoare=0){
    numar_contracte++;
    this->nrContract = nrContract;
    this->an = an;
    this->beneficiar = beneficiar;
    this->furnizor = furnizor;
    this->valoare = valoare;
}

Contract::~Contract(){
    nrContract = 0;
    an = 0;
    beneficiar = "";
    furnizor = "";
    valoare = 0;
}

Contract::Contract(const Contract &cpy){
    this->nrContract = cpy.nrContract;
    this->an = cpy.an;
    this->beneficiar = cpy.beneficiar;
    this->furnizor = cpy.furnizor;
    this->valoare = cpy.valoare;
}

int Contract::get_nrcontract() const{
    return nrContract;
}

void Contract::set_nrcontract(int nrContract){
    this->nrContract = nrContract;
}

int Contract::get_an() const{
    return an;
}

void Contract::set_an(int an){
    this->an = an;
}

string Contract::get_beneficiar() const{
    return beneficiar;
}

void Contract::set_beneficiar(string beneficiar){
    this->beneficiar = beneficiar;
}

string Contract::get_furnizor() const{
    return furnizor;
}

void Contract::set_furnizor(string furnizor){
    this->furnizor = furnizor;
}


float Contract::get_valoare() const{
    return valoare;
}

void Contract::set_valoare(float valoare){
    this->valoare = valoare;
}

void Contract::citire(istream &in){
    string b,f;
    cout<<"Numar contract: ";in>>nrContract;
    cout<<"Anul: ";in>>an;
    cout<<"Beneficiar: ";
    in.get();
    getline(in, b);
    beneficiar = b;
    cout<<"Furnizor: ";
    getline(in,f);
    furnizor = f;
    cout<<"Valoare: ";in>>valoare;
}

void Contract::afisare(ostream &out){
    out<<"Numar contract: "<<nrContract<<"\n";
    out<<"Anul: "<<an<<"\n";
    out<<"Beneficiar: "<<beneficiar<<"\n";
    out<<"Furnizor: "<<furnizor<<"\n";
    out<<"Valoare: "<<valoare<<"\n";
}

istream& operator>>(istream& in, Contract& c){
    c.citire(in);
    return in;
}

ostream& operator<<(ostream &out, Contract& c){
    c.afisare(out);
    return out;
}

Contract& Contract::operator=(const Contract& cpy){
    this->nrContract = cpy.nrContract;
    this->an = cpy.an;
    this->beneficiar = cpy.beneficiar;
    this->furnizor = cpy.furnizor;
    this->valoare = cpy.valoare;
    return *this;
}

class ContractInchiriere: public Contract{
private:
    int perioada;
public:
    ContractInchiriere(int, int, string, string, float, int);
    ~ContractInchiriere();
    ContractInchiriere(const ContractInchiriere&);
    int get_perioada() const;
    void set_perioada(int);
    int get_valoare_incasata() const;
    void citire(istream&);
    void afisare(ostream&);
    ContractInchiriere& operator=(const ContractInchiriere&);
    friend istream& operator>>(istream&, ContractInchiriere&);
    friend ostream& operator<<(ostream&, ContractInchiriere&);
};

ContractInchiriere::ContractInchiriere(int nrContract=0, int an=0, string beneficiar="", string furnizor="", float valoare=0, int perioada=0):Contract(nrContract,an,beneficiar,furnizor,valoare){
    this->perioada = perioada;
}

ContractInchiriere::~ContractInchiriere(){
    perioada = 0;
}

ContractInchiriere::ContractInchiriere(const ContractInchiriere &contract):Contract(contract){
    this->perioada = contract.perioada;
}

int ContractInchiriere::get_perioada() const{
    return perioada;
}

void ContractInchiriere::set_perioada(int perioada){
    this->perioada = perioada;
}

int ContractInchiriere::get_valoare_incasata() const{
    return valoare * perioada;
}

void ContractInchiriere::citire(istream& in){
    Contract::citire(in);
    cout<<"Perioada: ";
    in>>perioada;
}

void ContractInchiriere::afisare(ostream& out){
    Contract::afisare(out);
    out<<"Perioada: "<<perioada<<"\n";
}

istream& operator>>(istream &in, ContractInchiriere& contract){
    contract.citire(in);
    return in;
}

ostream& operator<<(ostream& out, ContractInchiriere& contract){
    contract.afisare(out);
    return out;
}

ContractInchiriere& ContractInchiriere::operator=(const ContractInchiriere& contract){
    Contract::operator=(contract);
    this->perioada = contract.perioada;
    return *this;
}

class Dosar{
private:
    Contract **contracte;
    int numar_contracte;
public:
    Dosar();
    Dosar(int);
    ~Dosar();
    Dosar(const Dosar&);
    int get_numarContracte() const;
    void set_numarContracte(int);
    int get_valoare_totala() const;
    void get_valoare_contracte() const;
    void citire(istream&);
    void afisare(ostream&);
    Dosar& operator=(const Dosar&);
    friend istream& operator>>(istream&, Dosar&);
    friend ostream& operator<<(ostream&, Dosar&);
};

Dosar::Dosar(){
    contracte = nullptr;
    numar_contracte = 0;
}

Dosar::Dosar(int numar_contracte){
    this->numar_contracte = numar_contracte;
    contracte = new Contract*[numar_contracte];
}

Dosar::~Dosar(){
    for(int i=0;i<numar_contracte;i++){
        delete contracte[i];
        contracte[i] = nullptr;
    }
    delete[] contracte;
    contracte = nullptr;
    numar_contracte = 0;
}

Dosar::Dosar(const Dosar& dosar){
    if(numar_contracte != 0){
        for(int i=0;i<numar_contracte;i++){
            delete contracte[i];
            contracte[i] = nullptr;
        }
        delete[] contracte;
        contracte = nullptr;
    }
    this->numar_contracte = dosar.numar_contracte;
    contracte = new Contract*[numar_contracte];
    for(int i=0;i<numar_contracte;i++){
        contracte[i] = new ContractInchiriere;
        *contracte[i] = *dosar.contracte[i];
    }
}

int Dosar::get_numarContracte() const{
    return numar_contracte;
}

void Dosar::set_numarContracte(int numar_contracte){
    if(numar_contracte > 0){
        for(int i=0;i<this->numar_contracte;i++){
            delete contracte[i];
            contracte[i] = nullptr;
        }
        delete[] contracte;
        contracte = nullptr;
    }
    this->numar_contracte = numar_contracte;
    contracte = new Contract*[numar_contracte];
}

int Dosar::get_valoare_totala() const{
    int suma = 0;
    for(int i=0;i<numar_contracte;i++){
        suma = suma + contracte[i]->get_valoare_incasata();
    }
    return suma;
}

void Dosar::get_valoare_contracte() const{
    if(numar_contracte > 0){
        for(int i=0;i<numar_contracte;i++){
            cout<<"Contractul cu numarul "<<i+1<<" - "<<contracte[i]->get_valoare_incasata()<<" incasari\n";
        }
    }
    else{
        cout<<"Nu exista contracte in dosar";
    }
}

void Dosar::citire(istream& in){
    for(int i=0;i<numar_contracte;i++){
        contracte[i] = new ContractInchiriere;
        in>>*contracte[i];
        cout<<"\n";
    }
}

void Dosar::afisare(ostream& out){
    for(int i=0;i<numar_contracte;i++){
        out<<*contracte[i];
        cout<<"\n";
    }
}

istream& operator>>(istream& in, Dosar& d){
    d.citire(in);
    return in;
}

ostream& operator<<(ostream& out, Dosar& d){
    d.afisare(out);
    return out;
}

Dosar& Dosar::operator=(const Dosar& d){
    if(this->numar_contracte != 0){
        for(int i=0;i<numar_contracte;i++){
            delete contracte[i];
            contracte[i] = nullptr;
        }
        delete[] contracte;
        contracte = nullptr;
    }
    this->numar_contracte = d.numar_contracte;
    contracte = new Contract*[numar_contracte];
    for(int i=0;i<numar_contracte;i++){
        contracte[i] = new ContractInchiriere;
        *contracte[i] = *d.contracte[i];
    }
    return *this;
}

void display_menu(Dosar* dosare, int numar_dosare){
    cout<<"=============================================================================\n";
    cout<<"\n";
    for(int i=0;i<numar_dosare;i++){
        cout<<"Dosarul numarul "<<i+1<<": "<<dosare[i].get_numarContracte()<<" contracte - "<<dosare[i].get_valoare_totala()<<" incasari.\n";
    }
    cout<<"\n=============================================================================\n";
    cout<<"\n";
    cout<<"1. Citire/Modificare contracte\n";
    cout<<"2. Vizualizare contracte\n";
    cout<<"3. Valoare incasata pentru fiecare contract\n";
    cout<<"4. Valoare totala\n";
    cout<<"5. Exit\n";
}

void menu(){

    int optiune;
    int numar_dosare;

    cout<<"Numarul de dosare: ";
    cin>>numar_dosare;
    Dosar *dosare = new Dosar[numar_dosare];
    system("cls");

    do{
        int id,numar_contracte;
        display_menu(dosare, numar_dosare);
        cout<<"\nActiune: ";
        cin>>optiune;

        switch(optiune){
            case 1:
            {
                cout<<"Numar dosar: ";cin>>id;
                if(id<1 || id>numar_dosare){
                    cout<<"\n\nNumar dosar invalid.\n\n";
                }
                else{
                    cout<<"Numar contracte: ";cin>>numar_contracte;
                    cout<<"\n";
                    dosare[id-1].set_numarContracte(numar_contracte);
                    cin>>dosare[id-1];
                }
                system("cls");
                break;
            }
            case 2:
            {
                cout<<"Numar dosar: ";cin>>id;
                if(id<1 || id>numar_dosare){
                    cout<<"\n\nNumar dosar invalid.\n\n";
                }
                else{
                    cout<<"\n=============== Vizualizare contracte pentru dosarul "<<id<<" ===============\n\n";
                    if(dosare[id-1].get_numarContracte() > 0){
                        cout<<dosare[id-1];
                    }
                    else{
                        cout<<"Nu exista contracte in dosar\n\n\n";
                    }
                }
                system("pause");
                system("cls");
                break;
            }
            case 3:
            {
                cout<<"Numar dosar: ";cin>>id;
                if(id<1 || id>numar_dosare){
                    cout<<"\n\nNumar dosar invalid.\n\n";
                }
                else{
                    cout<<"\n";
                    dosare[id-1].get_valoare_contracte();
                    cout<<"\n";
                }
                system("pause");
                system("cls");
                break;
            }
            case 4:
            {
                int suma = 0;
                for(int i=0;i<numar_dosare;i++){
                    suma = suma + dosare[i].get_valoare_totala();
                }
                cout<<"Suma totala a tuturor dosarelor: "<<suma<<".\n";
                system("pause");
                system("cls");
                break;
            }
            case 5:
            {
                delete[] dosare;
                system("cls");
                break;
            }
            default:
            {
                cout<<"Selectie invalida\n";
                system("pause");
                system("cls");
                break;
            }
        }

    }while(optiune != 5);
}

int main(){
    menu();
    return 0;
}
