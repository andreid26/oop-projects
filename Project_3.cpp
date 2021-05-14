#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <set>
#include <utility>
using namespace std;

class Locuinta{
protected:
    string nume_client;
    int suprafata_utila;
    int discount;
    int pret_mp;
    const int id_locuinta;
    static int numar_locuinte;
public:
    Locuinta(string, int, int, int);
    virtual ~Locuinta();
    Locuinta(const Locuinta&);
    void set_nume_client(string);
    string get_nume_client() const;
    void set_suprafata_utila(int);
    int get_suprafara_utila() const;
    void set_discount(int);
    int get_discount() const;
    void set_pret_mp(int);
    int get_pret_mp() const;
    static int get_numar_locuinte(){
        return numar_locuinte;
    };
    virtual float get_chirie() const = 0;
    virtual void citire(istream&);
    virtual void afisare(ostream&);
    Locuinta& operator=(const Locuinta&);
    friend istream& operator>>(istream&, Locuinta&);
    friend ostream& operator<<(ostream&, Locuinta&);
};

int Locuinta::numar_locuinte;

Locuinta::Locuinta(string nume_client = "", int suprafata_utila = 0, int discount = 0, int pret_mp = 0):id_locuinta(numar_locuinte++){
    this->nume_client = nume_client;
    try{
        if(suprafata_utila < 0) throw 1;
        if(discount < 0 || discount > 10) throw 3.141;
        if(pret_mp < 0) throw 'a';
    }
    catch(int x){
        cout<<"Eroare in constructor, suprafata utila nu poate fi negativa\n";
        exit(EXIT_FAILURE);
    }
    catch(float x){
        cout<<"Eroare in constructor, discount-ul trebuie sa fie intre 0 si 10\n";
        exit(EXIT_FAILURE);
    }
    catch(char x){
        cout<<"Eroare in constructor, pretul pe metru patrat nu poate fi negativ\n";
        exit(EXIT_FAILURE);
    }
    this->suprafata_utila = suprafata_utila;
    this->discount = discount;
    this->pret_mp = pret_mp;
}

Locuinta::~Locuinta(){
    numar_locuinte--;
    nume_client = "";
    suprafata_utila = 0;
    discount = 0;
    pret_mp = 0;
}

Locuinta::Locuinta(const Locuinta& locuinta_cpy):id_locuinta(locuinta_cpy.id_locuinta){
    this->nume_client = locuinta_cpy.nume_client;
    this->suprafata_utila = locuinta_cpy.suprafata_utila;
    this->discount = locuinta_cpy.discount;
    this->pret_mp = locuinta_cpy.pret_mp;
}

void Locuinta::set_nume_client(string nume_client){
    this->nume_client = nume_client;
}

string Locuinta::get_nume_client() const{
    return nume_client;
}

void Locuinta::set_suprafata_utila(int suprafata_utila){
    this->suprafata_utila = suprafata_utila;
}

int Locuinta::get_suprafara_utila() const {
    return suprafata_utila;
}

void Locuinta::set_discount(int discount){
    this->discount = discount;
}

int Locuinta::get_discount() const {
    return discount;
}

void Locuinta::set_pret_mp(int pret_mp){
    this->pret_mp = pret_mp;
}

int Locuinta::get_pret_mp() const{
    return pret_mp;
}

void Locuinta::citire(istream& in){
    int suprafata, disc, pretMp;
    cout<<"Suprafata utila: ";in>>suprafata;
    cout<<"Nume client: ";
    in.get();
    getline(in, nume_client);
    cout<<"Discount: ";in>>disc;
    cout<<"Pretul pe metru patrat: ";in>>pretMp;
    try{
        if(suprafata < 0) throw 1;
        if(disc < 0 || disc > 10) throw 3.141;
        if(pretMp < 0) throw 'a';
    }
    catch(int x){
        cout<<"Eroare in citire, suprafata utila nu poate fi negativa\n";
        exit(EXIT_FAILURE);
    }
    catch(float x){
        cout<<"Eroare in citire, discount-ul trebuie sa fie intre 0 si 10\n";
        exit(EXIT_FAILURE);
    }
    catch(char x){
        cout<<"Eroare in citire, pretul pe metru patrat nu poate fi negativ\n";
        exit(EXIT_FAILURE);
    }
    suprafata_utila = suprafata;
    discount = disc;
    pret_mp = pretMp;
}

void Locuinta::afisare(ostream& out){
    out<<"Nume client: "<<nume_client<<"\n";
    out<<"Suprafata utila: "<<suprafata_utila<<"\n";
    out<<"Discount: "<<discount<<"%\n";
    out<<"Pretul pe metru patrat: "<<pret_mp<<"\n";
}

istream& operator>>(istream& in, Locuinta& loc){
    loc.citire(in);
    return in;
}

ostream& operator<<(ostream& out, Locuinta& loc){
    loc.afisare(out);
    return out;
}

Locuinta& Locuinta::operator=(const Locuinta& loc){
    this->nume_client = loc.nume_client;
    this->suprafata_utila = loc.suprafata_utila;
    this->discount = loc.discount;
    this->pret_mp = loc.pret_mp;
    return *this;
}

class Apartament: public Locuinta{
private:
    int etaj;
public:
    Apartament(string, int, int, int, int);
    ~Apartament();
    Apartament(const Apartament&);
    void set_etaj(int);
    int get_etaj() const;
    float get_chirie() const;
    void citire(istream&);
    void afisare(ostream&);
    Apartament& operator=(const Apartament&);
    friend istream& operator>>(istream&, Apartament&);
    friend ostream& operator<<(ostream&, Apartament&);
};

Apartament::Apartament(string nume_client = "", int suprafata_utila = 0, int discount = 0, int pret_mp = 0, int etaj = 0):Locuinta(nume_client, suprafata_utila, discount, pret_mp){
    try{
        if(etaj < 0) throw 1;
    }
    catch(int x){
        cout<<"Eroare in constructor, etajul nu poate fi mai mic decat 1\n";
        exit(EXIT_FAILURE);
    }
    this->etaj = etaj;
}

Apartament::~Apartament(){
    etaj = 0;
}

Apartament::Apartament(const Apartament& ap):Locuinta(ap){
    this->etaj = ap.etaj;
}

void Apartament::set_etaj(int etaj){
    this->etaj = etaj;
}

int Apartament::get_etaj() const{
    return etaj;
}

float Apartament::get_chirie() const {
    if(discount > 0){
        return (pret_mp*suprafata_utila)-((discount/(float)100)*(pret_mp * suprafata_utila));
    }
    return pret_mp * suprafata_utila;
}

void Apartament::citire(istream& in){
    Locuinta::citire(in);
    int et;
    cout<<"Etaj: ";in>>et;
    try{
        if(et < 0) throw 1;
    }
    catch(int x){
        cout<<"Eroare in citire, etajul nu poate fi mai mic decat 1\n";
        exit(EXIT_FAILURE);
    }
    etaj = et;
}

void Apartament::afisare(ostream& out){
    Locuinta::afisare(out);
    out<<"Etaj: "<<etaj<<"\n";
    out<<"Pret chirie: "<<this->get_chirie()<<"\n";
}

istream& operator>>(istream& in, Apartament& ap){
    ap.citire(in);
    return in;
}

ostream& operator<<(ostream& out, Apartament& ap){
    ap.afisare(out);
    return out;
}

Apartament& Apartament::operator=(const Apartament& ap){
    Locuinta::operator=(ap);
    this->etaj = ap.etaj;
    return *this;
}

class Casa: public Locuinta{
private:
    int mp_curte;
    int numar_etaje;
    int pret_mp_curte;
    int *suprafata_utila_etaj;
public:
    Casa(string, int, int, int, int, int, int);
    ~Casa();
    Casa(const Casa&);
    void set_mp_curte(int);
    int get_mp_curte() const;
    void set_numar_etaje(int);
    int get_numar_etaje() const;
    void set_pret_mp_curte(int);
    int get_pret_mp_curte() const;
    void get_suprafata_utila_etaje() const;
    void set_suprafata_utila_etaje();
    float get_chirie() const;
    void citire(istream&);
    void afisare(ostream&);
    Casa& operator=(const Casa&);
    friend istream& operator>>(istream&, Casa&);
    friend ostream& operator<<(ostream&, Casa&);
};

Casa::Casa(string nume_client = "", int suprafata_utila = 0, int discount = 0, int pret_mp = 0, int mp_curte = 0, int numar_etaje = 0, int pret_mp_curte = 0):Locuinta(nume_client, suprafata_utila, discount,pret_mp){
    try{
        if(mp_curte < 0) throw 1;
        if(numar_etaje < 0) throw 3.141;
        if(pret_mp_curte < 0) throw 'a';
    }
    catch(int x){
        cout<<"Eroare in constructor, suprafata curtii nu poate fi negativa\n";
        exit(EXIT_FAILURE);
    }
    catch(float x){
        cout<<"Eroare in constructor, numarul de etaje nu poate fi mai mic decat 0\n";
        exit(EXIT_FAILURE);
    }
    catch(char x){
        cout<<"Eroare in constructor, pretul pe metru patrat de curte nu poate fi negativ\n";
        exit(EXIT_FAILURE);
    }
    this->mp_curte = mp_curte;
    this->numar_etaje = numar_etaje;
    this->pret_mp_curte = pret_mp_curte;
    suprafata_utila_etaj = new int[numar_etaje];
    for(int i=0;i<numar_etaje;i++){
        cout<<"Suprafata utila etaj "<<i<<": ";cin>>suprafata_utila_etaj[i];
    }
}

Casa::~Casa(){
    mp_curte = 0;
    numar_etaje = 0;
    pret_mp_curte = 0;
    delete[] suprafata_utila_etaj;
}

Casa::Casa(const Casa& c):Locuinta(c){
    this->mp_curte = c.mp_curte;
    this->numar_etaje = c.numar_etaje;
    this->pret_mp_curte = c.pret_mp_curte;
    delete[] suprafata_utila_etaj;
    suprafata_utila_etaj = new int[numar_etaje];
    for(int i=0;i<numar_etaje;i++){
        suprafata_utila_etaj[i] = c.suprafata_utila_etaj[i];
    }
}

void Casa::set_mp_curte(int mp_curte){
    this->mp_curte = mp_curte;
}

int Casa::get_mp_curte() const {
    return mp_curte;
}

void Casa::set_numar_etaje(int numar_etaje){
    this->numar_etaje = numar_etaje;
    delete[] suprafata_utila_etaj;
    suprafata_utila_etaj = new int[numar_etaje];
    for(int i=0;i<numar_etaje;i++){
        cout<<"Suprafata utila etaj "<<i<<": ";cin>>suprafata_utila_etaj[i];
    }
}

int Casa::get_numar_etaje() const {
    return numar_etaje;
}

void Casa::set_pret_mp_curte(int pret_mp_curte){
    this->pret_mp_curte = pret_mp_curte;
}

int Casa::get_pret_mp_curte() const {
    return pret_mp_curte;
}

void Casa::get_suprafata_utila_etaje() const{
    for(int i=0;i<numar_etaje;i++){
        cout<<"Etaj "<<i<<": "<<suprafata_utila_etaj[i]<<" - suprafata utila\n";
    }
}

void Casa::set_suprafata_utila_etaje(){
    for(int i=0;i<numar_etaje;i++){
        cout<<"Suprafata utila etaj "<<i<<": ";cin>>suprafata_utila_etaj[i];
    }
}

float Casa::get_chirie() const {
    if(discount > 0){
        return ((pret_mp*suprafata_utila)-((discount/(float)100)*(pret_mp * suprafata_utila))) + (pret_mp_curte*mp_curte);
    }
    return (pret_mp * suprafata_utila) + (pret_mp_curte*mp_curte);
}

void Casa::citire(istream& in){
    Locuinta::citire(in);
    int mpCurte, nrEtaje, pretMpCurte;
    cout<<"Metri patrati curte: ";in>>mpCurte;
    cout<<"Pret metru patrat de curte: ";in>>pretMpCurte;
    cout<<"Numar etaje: ";in>>nrEtaje;
    try{
        if(mpCurte < 0) throw 1;
        if(nrEtaje < 0) throw 3.141;
        if(pretMpCurte < 0) throw 'a';
    }
    catch(int x){
        cout<<"Eroare in citire, suprafata curtii nu poate fi negativa\n";
        exit(EXIT_FAILURE);
    }
    catch(float x){
        cout<<"Eroare in citire, numarul de etaje nu poate fi mai mic decat 0\n";
        exit(EXIT_FAILURE);
    }
    catch(char x){
        cout<<"Eroare in citire, pretul pe metru patrat de curte nu poate fi negativ\n";
        exit(EXIT_FAILURE);
    }
    mp_curte = mpCurte;
    numar_etaje = nrEtaje;
    pret_mp_curte = pretMpCurte;
    suprafata_utila_etaj = new int[numar_etaje];
    for(int i=0;i<numar_etaje;i++){
        cout<<"Suprafata utila etaj "<<i<<": ";in>>suprafata_utila_etaj[i];
    }
}

void Casa::afisare(ostream& out){
    Locuinta::afisare(out);
    out<<"Metri patrati curte: "<<mp_curte<<"\n";
    out<<"Pret metru patrat curte: "<<pret_mp_curte<<"\n";
    out<<"Numar etaje: "<<numar_etaje<<"\n";
    for(int i=0;i<numar_etaje;i++){
        out<<"Suprafata utila etaj "<<i<<": "<<suprafata_utila_etaj[i]<<"\n";
    }
    out<<"Pret chirie: "<<this->get_chirie()<<"\n";
}

istream& operator>>(istream& in, Casa& c){
    c.citire(in);
    return in;
}

ostream& operator<<(ostream& out, Casa& c){
    c.afisare(out);
    return out;
}

Casa& Casa::operator=(const Casa& c){
    Locuinta::operator=(c);
    this->mp_curte = c.mp_curte;
    this->numar_etaje = c.numar_etaje;
    this->pret_mp_curte = c.pret_mp_curte;
    delete[] suprafata_utila_etaj;
    suprafata_utila_etaj = new int[numar_etaje];
    for(int i=0;i<numar_etaje;i++){
        suprafata_utila_etaj[i] = c.suprafata_utila_etaj[i];
    }
}

template <class t> class Gestiune{
private:
    t *v;
    int numar_obiecte;
public:
    Gestiune(t *p = NULL, int numar_obiecte=0){
        this->numar_obiecte = numar_obiecte;
        v = new t[numar_obiecte];
        for(int i=0;i<numar_obiecte;i++){
            v[i] = p[i];
        }
    }
    ~Gestiune(){
        delete[] v;
        numar_obiecte = 0;
    }
    Gestiune(Gestiune &a){
        numar_obiecte = a.numar_obiecte;
        v = new t[numar_obiecte];
        for(int i=0;i<numar_obiecte;i++){
            v[i] = a.v[i];
        }
    }

    int get_numar_obiecte() {
        return numar_obiecte;
    }

    t get_obiecte(int i){
        try{
            if(i>numar_obiecte) throw 1;
        }
        catch(int x){
            cout<<"Nu exista obiectul cu indexul "<<i<<"\n";
            exit(EXIT_FAILURE);
        }
        return v[i];
    }

    void operator+=(t& newObj){
        t* p = new t[numar_obiecte+1];
        for(int i=0;i<numar_obiecte;i++){
            p[i] = v[i];
        }
        p[numar_obiecte] = newObj;
        delete[] v;
        numar_obiecte++;
        v = new t[numar_obiecte];
        for(int i=0;i<numar_obiecte;i++){
            v[i] = p[i];
        }
        delete[] p;
    }

    friend istream& operator>>(istream& in, Gestiune <t> &g){
        cout<<"Introduceti numarul de locuinte: ";
        in>>g.numar_obiecte;
        try{
            if(g.numar_obiecte < 0) throw 1;
        }
        catch(int x){
            cout<<"\nNumarul de locuinte trebuie sa fie un numar pozitiv\n";
            exit(EXIT_FAILURE);
        }
        g.v = new t[g.numar_obiecte];
        cout<<"=====================================================================\n";
        cout<<"Introduceti locuintele: \n\n";
        for(int i=0;i<g.numar_obiecte;i++){
            in>>g.v[i];
            cout<<"---------------------------------------------------------------\n";
        }
        cout<<"\n\n";
        return in;
    }

    friend ostream& operator<<(ostream& out, Gestiune <t> &g){
        out<<"Gestiune - "<<g.numar_obiecte<<" locuinte:\n";
        cout<<"=================================================================\n\n";
        for(int i=0;i<g.numar_obiecte;i++){
            out<<g.v[i];
            out<<"---------------------------------------------------------------\n";
        }
        return out;
    }
};

template <> class Gestiune <Casa>{
private:
    Casa *v;
    int numar_case;
public:
    Gestiune(Casa *p = NULL, int numar_case = 0){
        this->numar_case = numar_case;
        v = new Casa[numar_case];
        for(int i=0;i<numar_case;i++){
            v[i] = p[i];
        }
    }

    ~Gestiune(){
        delete[] v;
        numar_case = 0;
    }

    Gestiune(Gestiune &a){
        numar_case = a.numar_case;
        v = new Casa[numar_case];
        for(int i=0;i<numar_case;i++){
            v[i] = a.v[i];
        }
    }

    int get_numar_case(){
        return numar_case;
    }

    Casa get_casa_id(int i){
        try{
            if(i > numar_case) throw 1;
        }
        catch(int x){
            cout<<"Nu exista o casa cu indexul "<<i<<"\n";
            exit(EXIT_FAILURE);
        }
        return v[i];
    }

    friend istream& operator>>(istream&in, Gestiune <Casa> &g){
        cout<<"Introduceti numarul de case: ";
        in>>g.numar_case;
        try{
            if(g.numar_case < 0) throw 1;
        }
        catch(int x){
            cout<<"\nNumarul de case trebuie sa fie un numar pozitiv\n";
            exit(EXIT_FAILURE);
        }
        g.v = new Casa[g.numar_case];
        cout<<"=====================================================================\n";
        cout<<"Introduceti casele:\n\n";
        for(int i=0;i<g.numar_case;i++){
            in>>g.v[i];
            cout<<"---------------------------------------------------------------\n";
        }
        cout<<"\n\n";
        return in;
    }

    friend ostream& operator<<(ostream& out, Gestiune <Casa> &g){
        float total = 0;
        out<<"Gestiune - "<<g.numar_case<<" case:\n";
        out<<"=================================================================\n\n";
        for(int i=0;i<g.numar_case;i++){
            out<<g.v[i];
            total = total + g.v[i].get_chirie();
            out<<"---------------------------------------------------------------\n";
        }
        out<<"\nTOTAL OBTINUT DE AGENTIE: "<<total<<"\n";
        return out;
    }

};

void menu_output(){
    cout<<"---------------------------- GESTIONARE PROPRIETATI IMOBILIARE ----------------------------\n";
    cout<<"===========================================================================================\n\n";
    cout<<"1. Citeste informatii despre N proprietati\n";
    cout<<"2. Afiseaza informatiile despre cele N proprietati\n";
    cout<<"3. Gestiune - TEMPLATE (Apartament)\n";
    cout<<"4. Gestiune - TEMPLATE (Casa - specializare)\n";
    cout<<"5. Contorizare proprietati\n";
    cout<<"0. Iesire\n";
}

void menu(){
    int optiune = 0;
    int numar_obiecte = 0;
    set<pair<Locuinta*, string>> proprietati;
    do{
        menu_output();
        cout<<"\nIntroduceti numarul actiunii: ";
        cin>>optiune;
        if(optiune == 1){
            cout<<"\nIntroduceti numarul de proprietati: ";
            cin>>numar_obiecte;
            if(numar_obiecte>0){
                for(int i=0;i<numar_obiecte;i++){
                    string tip;
                    cout<<"\n\nIntroduceti tipul proprietatii (apartament/casa): ";
                    cin>>tip;
                    try{
                        if(tip == "apartament"){
                            Apartament *ap = new Apartament;
                            cin>>*ap;
                            proprietati.insert(make_pair(&*ap, "Apartament"));
                        }
                        else{
                            if(tip == "casa"){
                                Casa *c = new Casa;
                                cin>>*c;
                                proprietati.insert(make_pair(&*c, "Casa"));
                            }
                            else throw 1;
                        }
                    }
                    catch (bad_alloc var){
                        cout << "Allocation Failure\n";
                        exit(EXIT_FAILURE);
                    }
                    catch(int x){
                        cout<<"Nu ati introdus o proprietate valida. Incercati apartament/casa.\n";
                    }
                }
            }
            else{
                cout<<"Numarul de proprietati trebuie sa fie un numar pozitiv\n";
            }
        }
        if(optiune == 2){
            set<pair<Locuinta*, string>>::iterator i;
            cout<<"---------------------------------------------------------------\n";
            for(i=proprietati.begin(); i!=proprietati.end();i++){
                cout<<"---------------------- "<<(*i).second<<" ----------------------\n";
                cout<<*((*i).first)<<"\n";
            }
        }
        if(optiune == 3){
            Gestiune <Apartament> x;
            cin>>x;
            cout<<x;
        }
        if(optiune == 4){
            Gestiune <Casa> x;
            cin>>x;
            cout<<x;
        }
        if(optiune == 5){
            int num_ap=0, num_case=0;
            if(numar_obiecte > 0){
                set<pair<Locuinta*, string>>::iterator i;
                for(i=proprietati.begin(); i!=proprietati.end();i++){
                    Apartament *ap = dynamic_cast<Apartament*>((*i).first);
                    Casa *c = dynamic_cast<Casa*>((*i).first);

                    if(ap) num_ap++;
                    if(c) num_case++;
                }
                cout<<"\n\n--- Numarul de apartamente: "<<num_ap<<"\n";
                cout<<"--- Numarul de case: "<<num_case<<"\n";
            }
            else cout<<"\n\nNu s-au adaugat aparamente/case. Reveniti la optiunea 1\n";
        }
        if(optiune == 0){
            cout<<"\n\nEXIT\n\n";
        }
        if(optiune < 0 || optiune > 5){
            cout<<"\nSelectie invalida\n";
        }
        cout<<"\n";
        system("pause");
        system("cls");
    }while(optiune != 0);
}

int main(){
    menu();
    return 0;
}
