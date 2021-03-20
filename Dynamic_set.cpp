#include <iostream>
#include <stdlib.h>
using namespace std;

class Node{
private:
    int value;
    Node *next;
public:
    Node();
    Node(int value, Node *next);
    Node(Node &cpy);
    int get_value(){return value;}
    Node* get_next(){return next;}
    friend class Dynamic_set;
};

Node::Node(){
    this->value = NULL;
    this->next = NULL;
}

Node::Node(int value=0, Node *next = NULL){
    this->value = value;
    this->next = next;
}

Node::Node(Node &cpy){
    this->value = cpy.value;
    this->next = cpy.next;
}

class Dynamic_set{
private:
    int num_elements;
    Node *first;
public:
    Dynamic_set();
    Dynamic_set(int);
    ~Dynamic_set();
    Dynamic_set(Dynamic_set&);
    int get_length();
    void add(int);
    void make_set();
    void print(ostream &out);
    void read(istream &in);
    friend ostream& operator<<(ostream &out, Dynamic_set &);
    friend istream& operator>>(istream &in, Dynamic_set &);
    friend Dynamic_set& operator+(Dynamic_set&, Dynamic_set&);
    friend Dynamic_set& operator*(Dynamic_set&, Dynamic_set&);
    friend Dynamic_set& operator-(Dynamic_set&, Dynamic_set&);
};

Dynamic_set::Dynamic_set(){
    this->num_elements = 0;
    this->first = NULL;
}

Dynamic_set::Dynamic_set(int first_value){
    Node *newNode = new Node(first_value, NULL);
    first = newNode;
    num_elements=1;
}

Dynamic_set::~Dynamic_set(){
    Node *current = first;
    Node *aux;
    while(current != NULL){
        aux = current;
        current = current->next;
        delete aux;
    }
    this->first = NULL;
    this->num_elements = 0;
}

Dynamic_set::Dynamic_set(Dynamic_set &cpy){
    if(cpy.first == NULL){
        this->first = NULL;
        this->num_elements = 0;
    }
    else{
        first = new Node(*cpy.first);
        Node *p = cpy.first -> next;
        Node *q = first;
        while(p){
            q->next = new Node(*p);
            p = p->next;
            q = q->next;
        }
        this->num_elements = cpy.num_elements;
    }
}

/*void Dynamic_set::add(int val){
    if(first == NULL){
        Node *newNode = new Node(val, NULL);
        first = newNode;
        num_elements++;
    }
    else{
        bool element_in_set = false;
        Node *current = first;
        while(current != NULL){
            if(current->value == val){
                element_in_set = true;
            }
            current = current->next;
        }
        if(element_in_set == false){
            Node *newNode = new Node(val, NULL);
            current = first;
            while(current->next != NULL){
                current = current->next;
            }
            current->next = newNode;
            num_elements++;
        }
    }
}*/

void Dynamic_set::add(int val){
    if(first == NULL){
        Node *newNode = new Node(val, NULL);
        first = newNode;
        num_elements++;
    }
    else{
        Node *newNode = new Node(val, NULL);
        Node *current = first;
        while(current->next != NULL){
            current = current->next;
        }
        current->next = newNode;
        num_elements++;
    }
}

void Dynamic_set::make_set(){
   Node *current = first;
   while(current != NULL){
        Node *p = current;
        if(p != NULL){
            while(p!=NULL){
                if(p->next != NULL && p->next->value == current->value){
                    Node *q = p->next;
                    p->next = q->next;
                    delete q;
                    num_elements--;
                }
                p=p->next;
            }
        }
        current=current->next;
   }
}

void Dynamic_set::print(ostream& out){
    if(first == NULL){
        out<<"No elements";
    }
    else{
        Node *current = first;
        out<<"{";
        while(current != NULL){
            out<<current->value;
            if(current->next != NULL){
                out<<", ";
            }
            current=current->next;
        }
        out<<"}";
    }
    out<<"\n";
}

void Dynamic_set::read(istream& in){
    int num_of_elements, element;
    cout<<"Number of elements: ";
    in>>num_of_elements;
    for(int i=1;i<=num_of_elements;i++){
        cout<<"Element "<<i<<": ";
        in>>element;
        this->add(element);
        this->make_set();
    }
}

int Dynamic_set::get_length(){
    return this->num_elements;
}

ostream& operator<<(ostream &out, Dynamic_set& sett){
    sett.print(out);
    return out;
}

istream& operator>>(istream &in, Dynamic_set& sett){
    sett.read(in);
    return in;
}

Dynamic_set& operator+(Dynamic_set& set_1, Dynamic_set &set_2){
    Dynamic_set *sett = new Dynamic_set(set_1);
    Node *current = set_2.first;
    while(current != NULL){
        Node *p = set_1.first;
        bool is_ok = true;
        while(p!=NULL){
            if(current->get_value() == p->get_value()) is_ok = false;
            p = p->get_next();
        }
        if(is_ok){
            sett->add(current->get_value());
        }
        current = current->get_next();
    }
    return *sett;
}

Dynamic_set& operator*(Dynamic_set& set_1, Dynamic_set& set_2){
    Dynamic_set *sett = new Dynamic_set();
    Node *current = set_1.first;
    while(current != NULL){
        Node *p = set_2.first;
        bool is_ok = false;
        while(p!=NULL){
            if(current->get_value() == p->get_value()) is_ok = true;
            p = p->get_next();
        }
        if(is_ok){
            sett->add(current->get_value());
        }
        current = current->get_next();
    }
    return *sett;
}

Dynamic_set& operator-(Dynamic_set& set_1, Dynamic_set& set_2){
    Dynamic_set *sett = new Dynamic_set();
    Node *current = set_1.first;
    while(current != NULL){
        Node *p = set_2.first;
        bool is_ok = true;
        while(p!=NULL){
            if(p->get_value() == current->get_value()) is_ok = false;
            p = p->get_next();
        }
        if(is_ok){
            sett->add(current->get_value());
        }
        current=current->get_next();
    }
    return *sett;
}

///MENU

void display_menu(Dynamic_set* sets, int number_of_sets){
    for(int i=0;i<number_of_sets;i++){
        cout<<"SET["<<i<<"]: ";
        cout<<sets[i];
    }
    cout<<"\n=============================================================================\n";
    cout<<"\n";
    cout<<"1. Add element to a set\n";
    cout<<"2. Sets union\n";
    cout<<"3. Sets intersection\n";
    cout<<"4. Sets difference\n";
    cout<<"5. Exit\n";
}

void menu(){

    int option = 0;
    int number,number_of_sets;

    cout<<"Number of sets: ";
    cin>>number_of_sets;
    Dynamic_set *sets = new Dynamic_set[number_of_sets];
    system("cls");

    do{
        display_menu(sets,number_of_sets);
        cout<<"\n";
        cout<<"Action number: ";
        cin>>option;

        int set_id, element, set_id_1, set_id_2;

        switch(option){
            case 1:
                cout<<"Set ID: ";cin>>set_id;
                cout<<"Element: ";cin>>element;
                sets[set_id].add(element);
                sets[set_id].make_set();
                system("cls");
                break;
            case 2:
                cout<<"First set ID: ";cin>>set_id_1;
                cout<<"Second set ID: ";cin>>set_id_2;
                cout<<"\nSET["<<set_id_1<<"]+SET["<<set_id_2<<"] = "<<sets[set_id_1]+sets[set_id_2]<<"\n";
                system("pause");
                system("cls");
                break;
            case 3:
                cout<<"First set ID: ";cin>>set_id_1;
                cout<<"Second set ID: ";cin>>set_id_2;
                cout<<"\nSET["<<set_id_1<<"]*SET["<<set_id_2<<"] = "<<sets[set_id_1]*sets[set_id_2]<<"\n";
                system("pause");
                system("cls");
                break;
            case 4:
                cout<<"First set ID: ";cin>>set_id_1;
                cout<<"Second set ID: ";cin>>set_id_2;
                cout<<"\nSET["<<set_id_1<<"]-SET["<<set_id_2<<"] = "<<sets[set_id_1]-sets[set_id_2]<<"\n";
                system("pause");
                system("cls");
                break;
            case 5:
                system("cls");
                break;
            default:
                cout<<"Invalid selection\n";
                system("pause");
                system("cls");
                break;
        }
    }while(option != 5);
}

int main(){

    menu();
    return 0;
}
