#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

class examen {
protected:
    int codExamen;
    static int total;
    string materie;
    int zi, luna, an;
    float notaScris;
public:
    //constructor fara parametrii
    examen():materie("0"),zi(0),luna(0),an(0),notaScris(0) {codExamen=total++;}
    //constructor cu parametrii
    examen(const string &materie, int zi, int luna, int an, float notaScris) : materie(materie), zi(zi), luna(luna), an(an), notaScris(notaScris) {codExamen=total++;}
    //copy constructor
    examen (const examen &obj): codExamen(obj.codExamen), materie(obj.materie), zi(obj.zi), luna(obj.luna),an(obj.an), notaScris(obj.notaScris) {}
    //destructor
    virtual ~examen(){};
    //operator =
    examen&  operator= (const examen&  obj){
        this->codExamen=obj.codExamen;
        this->materie=obj.materie;
        this->zi=obj.zi;
        this->luna=obj.luna;
        this->an=obj.an;
        this->notaScris=obj.notaScris;
        return *this;
    }
    //operator ">>"
    friend std::istream& operator>> (std::istream& in, examen& obj){
        return obj.citire(in);
    }
    //citire
    virtual std::istream& citire(std::istream& in){
        while(true) {
            try {
                cout<<"Introduceti materia:";
                in >> materie;
                //urmataoarul if l-am preluat de aici https://stackoverflow.com/questions/9642292/function-to-check-if-string-contains-a-number
                if (materie.find('0') != std::string::npos || materie.find('1') != std::string::npos || materie.find('2') != std::string::npos || materie.find('3') != std::string::npos
                    || materie.find('4') != std::string::npos || materie.find('5') != std::string::npos || materie.find('6') != std::string::npos || materie.find('7') != std::string::npos
                    || materie.find('8') != std::string::npos || materie.find('9') != std::string::npos)
                    throw materie;
                else
                    break;
            }
            catch (string s) {
                cout << "Materia nu trebuie sa contina cifre, ci litere"<<endl;
            }
        }
        while(true) {
            try {
                cout<<"Introduceti ziua:";
                in >> zi;
                if (zi>31)
                    throw zi;
                else
                    break;
            }
            catch (int s) {
                cout << "Ziua nu trebuie sa fie mai mare ca 31"<<endl;
            }
        }
        while(true) {
            try {
                cout<<"Introduceti luna:";
                in >> luna;
                if (luna>12)
                    throw luna;
                else
                    break;
            }
            catch (int s) {
                cout << "Luna nu trebuie sa fie mai mare ca 12"<<endl;
            }
        }
        while(true) {
            try {
                cout<<"Introduceti anul:";
                in >> an;
                if (an<0)
                    throw an;
                else
                    break;
            }
            catch (int s) {
                cout << "Anul nu trebuie sa fie negativ"<<endl;
            }
        }
        while(true) {
            try {
                cout<<"Introduceti nota de la scris:";
                in >> notaScris;
                if (notaScris<0)
                    throw notaScris;
                else
                    break;
            }
            catch (float s) {
                cout << "Nota trebuie sa fie >=0"<<endl;
            }
        }
        return in;
    }
    //operator "<<"
    friend std::ostream& operator<< (std::ostream&out, const examen& obj){
        return obj.afisare(out);
    }
    //afisare
    virtual std::ostream& afisare(std::ostream &out) const{
        out<<"Cod examen="<<codExamen<<" Materie="<<materie<<" Zi/Luna/An="<<zi<<"/"<<luna<<"/"<<an<<" Nota scris="<<notaScris<<endl;
        return out;
    }
    int nota_scris(){
        return notaScris;
    }
    static int get_total(){
        return total;
    }
};
int examen::total=0;

class partial : public examen{
private:
    float notaOral;
public:
    //constructor fara parametrii
    partial() : examen(), notaOral(0) {}
    //constructor cu parametrii
    partial(const string &materie, int zi, int luna, int an, float notaScris, float notaOral) : examen(materie, zi,luna, an,notaScris),
                                                                                                notaOral(notaOral) {}
    //copy constructor
    partial(const partial &obj) : examen(obj), notaOral(obj.notaOral) {}
    //destructor
    virtual ~partial() {}
    // operator =
    partial&  operator= (const partial&  obj) {
        this->examen::operator=(obj);
        this->notaOral=obj.notaOral;
        return *this;
    }
    //citire
    std::istream& citire(std::istream& in){
        this -> examen::citire(in);
        while(true) {
            try {
                cout<<"Introduceti nota de la oral:";
                in >> notaOral;
                if (notaOral<0)
                    throw notaOral;
                else
                    break;
            }
            catch (float s) {
                cout << "Nota trebuie sa fie >=0"<<endl;
            }
        }
        return in;
    }
    //afisare
    virtual std::ostream& afisare(std::ostream &out) const{
        out<<"Cod examen="<<codExamen<<" Materie="<<materie<<" Zi/Luna/An="<<zi<<"/"<<luna<<"/"<<an<<" Nota scris="<<notaScris<<" Nota oral="<<notaOral<<endl;
        return out;
    }
};

class examenFinal : public examen{
private:
    float puncte;
public:
    //constructor fara parametrii
    examenFinal() : examen(), puncte(0) {}
    //constructor cu parametrii
    examenFinal(const string &materie, int zi, int luna, int an, float notaScris, float puncte) : examen(materie, zi,luna, an,notaScris),
                                                                                                  puncte(puncte) {}
    //copy constructor
    examenFinal(const examenFinal &obj) : examen(obj), puncte(obj.puncte) {}
    //destructor
    virtual ~examenFinal() {}
    // operator =
    examenFinal&  operator= (const examenFinal&  obj) {
        this->examen::operator=(obj);
        this->puncte=obj.puncte;
        return *this;
    }
    //citire
    virtual std::istream& citire(std::istream& in){
        this -> examen::citire(in);
        while(true) {
            try {
                cout<<"Introduceti numarul de puncte obtinute la oral:";
                in >> puncte;
                if (puncte<0)
                    throw puncte;
                else
                    break;
            }
            catch (float s) {
                cout << "Numarul de puncte trebuie sa fie >=0"<<endl;
            }
        }
        return in;
    }
    //afisare
    virtual std::ostream& afisare(std::ostream &out) const{
        out<<"Cod examen="<<codExamen<<" Materie="<<materie<<" Zi/Luna/An="<<zi<<"/"<<luna<<"/"<<an<<" Nota scris="<<notaScris<<" Puncte examen final="<<puncte<<endl;
        return out;
    }
};

class quiz : public examen{
private:
    float itemiCorecti;
public:
    //constructor fara parametrii
    quiz() : examen(), itemiCorecti(0) {}
    //constructor cu parametrii
    quiz(const string &materie, int zi, int luna, int an, float notaScris, float itemiCorecti) : examen(materie, zi,luna, an,notaScris),
                                                                                                 itemiCorecti(itemiCorecti) {}
    //copy constructor
    quiz(const quiz &obj) : examen(obj), itemiCorecti(obj.itemiCorecti) {}
    //destructor
    virtual ~quiz() {}
    // operator =
    quiz&  operator= (const quiz&  obj) {
        this->examen::operator=(obj);
        this->itemiCorecti=obj.itemiCorecti;
        return *this;
    }
    //citire
    virtual std::istream& citire(std::istream& in){
        this -> examen::citire(in);
        while(true) {
            try {
                cout<<"Introduceti numarul de itemi corecti de la quiz:";
                in >> itemiCorecti;
                if (itemiCorecti<0)
                    throw itemiCorecti;
                else
                    break;
            }
            catch (float s) {
                cout << "Numarul de itemi corecti trebuie sa fie >=0"<<endl;
            }
        }
        return in;
    }
    //afisare
    virtual std::ostream& afisare(std::ostream &out) const{
        out<<"Cod examen="<<codExamen<<" Materie="<<materie<<" Zi/Luna/An="<<zi<<"/"<<luna<<"/"<<an<<" Nota scris="<<notaScris<<" Itemi corecti="<<itemiCorecti<<endl;
        return out;
    }
};

template<class T>
class catalogIndividual {
private:
    unordered_map<int,vector<T>> examene;
public:
    //constructor fara parametrii
    catalogIndividual(){}
    //constructor cu parametrii
    catalogIndividual(const vector<T> examene) : examene(examene){}
    //copy constructor
    catalogIndividual(const catalogIndividual &obj): examene(obj.examene) {}
    //destructor
    virtual ~catalogIndividual() {}
    // operator =
    catalogIndividual&  operator= (const catalogIndividual&  obj){
        this->examene=obj.examene;
        return *this;
    }
    //operator ">>"
    friend std::istream& operator>> (std::istream& in, catalogIndividual& obj){
        return obj.citire(in);
    }
    //citire
    virtual std::istream& citire(std::istream& in){
        return in;
    }
    //operator "<<"
    friend std::ostream& operator<< (std::ostream&out, const catalogIndividual& obj){
        return obj.afisare(out);
    }
    //afisare
    virtual std::ostream& afisare(std::ostream &out) const{
        for(auto e : examene){
            for(auto x: e.second)
                cout<<x;
        }
        return out;
    }
    void add_examen(int nr_matricol, T ob_examen) {

        if (examene.count(nr_matricol) == 0) {
            examene[nr_matricol] = vector<T>();
        }
        examene[nr_matricol].push_back(ob_examen);
    }


    catalogIndividual& operator+=(pair<int,T> p){
        if (examene.count(p.first) == 0) {
            examene[p.first] = vector<T>();
        }
        examene[p.first].push_back(p.second);
        return *this;
    }


    void afisare_nota_scris(int nr_matricol){
        for(auto e : examene[nr_matricol])
            e.nota_scris();
    }

    int getNrPartiale(int nr_matricol){
        return examene[nr_matricol].size();
    }

    int getNota(int nr_matricol){
        int s = examene[nr_matricol].size()-1;
        return examene[nr_matricol][s].nota_scris();
    }

};

template<>
class catalogIndividual<quiz> {
private:
    unordered_map<int,vector<quiz>> examene;
public:
    //constructor fara parametrii
    catalogIndividual(){}
    //copy constructor
    catalogIndividual(const catalogIndividual &obj): examene(obj.examene) {}
    //destructor
    virtual ~catalogIndividual() {}
    // operator =
    catalogIndividual&  operator= (const catalogIndividual&  obj){
        this->examene=obj.examene;
        return *this;
    }
    //operator ">>"
    friend std::istream& operator>> (std::istream& in, catalogIndividual& obj){
        return obj.citire(in);
    }
    //citire
    virtual std::istream& citire(std::istream& in){
        return in;
    }
    //operator "<<"
    friend std::ostream& operator<< (std::ostream&out, const catalogIndividual& obj){
        return obj.afisare(out);
    }
    //afisare
    virtual std::ostream& afisare(std::ostream &out) const{
        for(auto e : examene){
            for(auto x: e.second)
                cout<<x;
        }
        return out;
    }
    void add_examen(int nr_matricol, quiz ob_examen) {

        if (examene.count(nr_matricol) == 0) {
            examene[nr_matricol] = vector<quiz>();
        }
        examene[nr_matricol].push_back(ob_examen);
    }

    catalogIndividual& operator+=(pair<int,quiz> p){
        if (examene.count(p.first) == 0) {
            examene[p.first] = vector<quiz>();
        }
        examene[p.first].push_back(p.second);
        return *this;
    }

    void afisare_nota_scris(int nr_matricol){
        for(auto e : examene[nr_matricol])
            e.nota_scris();
    }

    int getNrPartiale(int nr_matricol){
        return examene[nr_matricol].size();
    }

    int getNota(int nr_matricol){
        int s = examene[nr_matricol].size()-1;
        return examene[nr_matricol][s].nota_scris();
    }

    int afisare2quiz(){
        int nr = 0;
        for (auto x : examene)
        {
            if(x.second.size()>=2)
                nr++;
        }
        return nr;
    }

};

class student {
private:
    string nume;
    int nrMatricol;
    static int t;
    int nrExamene;
public:
    //constructor fara parametrii
    student():nume(""){nrExamene=0; nrMatricol=t++;}
    //constructor cu parametrii
    student(const string &nume) : nume(nume) {nrExamene=0; nrMatricol=t++;}
    //copy constructor
    //student(const student&) = delete;
    //destructor
    virtual ~student(){};
    //operator =
    student& operator=(const student&) = delete;
    //operator ">>"
    friend std::istream& operator>> (std::istream& in, student& obj){
        return obj.citire(in);
    }
    //citire
    virtual std::istream& citire(std::istream& in){
        while(true) {
            try {
                cout<<"Introduceti numele:";
                in >> nume;
                if (nume.find('0') != std::string::npos || nume.find('1') != std::string::npos || nume.find('2') != std::string::npos || nume.find('3') != std::string::npos
                    || nume.find('4') != std::string::npos || nume.find('5') != std::string::npos || nume.find('6') != std::string::npos || nume.find('7') != std::string::npos
                    || nume.find('8') != std::string::npos || nume.find('9') != std::string::npos)
                    throw nume;
                else
                    break;
            }
            catch (string s) {
                cout << "Numele nu trebuie sa contina cifre"<<endl;
            }
        }
        return in;
    }
    //operator "<<"
    friend std::ostream& operator<< (std::ostream&out, const student& obj){
        return obj.afisare(out);
    }
    //afisare
    virtual std::ostream& afisare(std::ostream &out) const{
        out<<"Nume: "<<nume<<" Nr matricol: "<<nrMatricol<<" Nr examene: "<<nrExamene<<endl;
        return out;
    }

    int get_nr_matricol()const{
        return nrMatricol;
    }

    string get_nume() const{
        return nume;
    }
    void incrementare(){
        nrExamene++;
    }
    void PromovatPicat(catalogIndividual <examen> e, catalogIndividual <partial> p, catalogIndividual <examenFinal> eF, catalogIndividual <quiz> q, int ex_necesare){
        int nr_partiale = p.getNrPartiale(nrMatricol);
        if(nrExamene>=ex_necesare) {
            if (nr_partiale == 1 || nr_partiale == 2)
                if (p.getNota(nrMatricol) >= 5) {
                    double x=(p.getNota(nrMatricol) + e.getNota(nrMatricol))/2 + eF.getNota(nrMatricol) + q.getNota(nrMatricol);                    if (x >= 5)
                        cout << "Promovat cu nota: " << x << endl;
                    else
                        cout << "Picat :(" << endl;
                } else if (nr_partiale > 2)
                    cout << "Ai picat primele 2 partiale, nu mai ai dreptul la al treile. Ai picat :(" << endl;
                else if (nr_partiale == 0)
                    cout << "Trebuie sa sustii partialul" << endl;
        }
        else
            cout<<"Trebuie sa sustii minim "<<ex_necesare<<" examene! Ai picat :(";
    }
};
int student::t=100;

int main() {
    vector <student> studenti;

    catalogIndividual<examen> examene;
    catalogIndividual<partial> partiale;
    catalogIndividual<examenFinal> exameneFinale;
    catalogIndividual<quiz> quizuri;

    int nr_studenti = 0;
    cout<<"Introduceti nr de studenti\n";
    cin>>nr_studenti;

    int ex_necesare = 0;
    cout<<"Introduceti nr de examene necesar\n";
    cin>>ex_necesare;

    for(int i = 0; i<nr_studenti; i++) {

        student s;
        cin >> s;
        studenti.push_back(s);
        int nr_mat_temporar = s.get_nr_matricol();

        int nr_ex = 0;
        cout<<"Cate examene adaugati?";
        cin>>nr_ex;

        for(int j=0;j<nr_ex;j++) {
            examen temporar;
            cin >> temporar;
            pair<int, examen> pair1;
            pair1.first = nr_mat_temporar;
            pair1.second = temporar;
            examene += pair1;
            s.incrementare();
        }

        int nr_par = 0;
        cout<<"Cate partiale adaugati?";
        cin>>nr_par;

        for(int j=0;j<nr_par;j++) {
            pair<int, partial> pair2;
            partial temp;
            cin >> temp;
            pair2.first = nr_mat_temporar;
            pair2.second = temp;
            partiale += pair2;
            s.incrementare();
        }

        int nr_quiz = 0;
        cout<<"Cate quiz-uri adaugati?";
        cin>>nr_quiz;

        for(int j=0;j<nr_quiz;j++) {
            pair<int, quiz> pair3;
            quiz q_temp;
            cin >> q_temp;
            pair3.first = nr_mat_temporar;
            pair3.second = q_temp;
            quizuri += pair3;
            s.incrementare();
        }

        cout<<"Introduceti examenul final\n";

        pair <int,examenFinal> pair4;
        examenFinal e_final;
        cin >> e_final;
        pair4.first = nr_mat_temporar;
        pair4.second = e_final;
        exameneFinale+=pair4;
        s.incrementare();

        cout<<"Studentul "<<s.get_nume()<<" a sustinut:\n";
        cout<<"Examene:\n";
        cout<<examene;
        cout<<"Partiale:\n";
        cout<<partiale;
        cout<<"Quiz-uri:\n";
        cout<<quizuri;
        cout<<"Examene finale:\n";
        cout<<exameneFinale;

        s.PromovatPicat(examene, partiale, exameneFinale, quizuri, ex_necesare);
    }
    cout<<"Numarul studentilor care au sustinut cel putin 2 quiz-uri:\n";
    cout<<quizuri.afisare2quiz();
}