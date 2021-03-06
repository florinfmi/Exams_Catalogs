/*La facultatea Y studenții intra în sesiune. In regulament e prevăzut ca ei sa aibă un anumit numar de examene. Fiecare examen are un numar, 
incrementat automat, denumirea materiei data și nota la scris. Partialul conține și nota la oral, iar examenul final conține extra-puncte pe un proiect. 
Dacă partialul nu e luat, atunci se reface la examenul final, altfel, se păstrează nota. Cei care vor să-mi mareasca nota, pe loc, mai dau un quiz,
 continant un numar de itemi de tip grila.

Cerinta suplimentara: 
- Sa se construiasca clasa template CatalogIndividual care sa conțină informații despre examenele date de un student. Clasa conține nr matricol al 
studentului (incrementat automat la adaugarea unei noi file), nr_examene și un vector de pointeri la obiecte de tip Examen,
alocat dinamic. Sa se supraincarce operatorul += pentru inserarea unei fise de observație a unui examen în lista, indiferent de tipul acestuia.
- Sa se construiasca o specializare pentru tipul unsigned care sa conțină și sa afiseze doar media la examenele finale. 
*/
#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <typeinfo>
using namespace std;

template<class T>
class CatalogIndividual;
template<>
class CatalogIndividual<unsigned>;


class Examen
{
protected:
	static int numar;
	string denumire;
	float nota_scris;
public:
	Examen();
	Examen(string, float);
	Examen(const Examen&);
	friend ifstream& operator >>(ifstream&, Examen&);
	friend istream& operator >>(istream&, Examen&);
	Examen& operator =(const Examen&);
	virtual void afis();
	~Examen() {};
};
int Examen::numar = 0;
Examen::Examen()
{
	numar++;
	denumire = "";
	nota_scris = 0;

}
Examen::Examen(string d, float ns)
{
	numar++;
	denumire = d;
	nota_scris = ns;
}

Examen::Examen(const Examen& ob)
{
	numar++;
	denumire = ob.denumire;
	nota_scris = ob.nota_scris;
}
ifstream& operator >>(ifstream& in, Examen& ob)
{
	in >> ob.denumire;
	in >> ob.nota_scris;
	return in;
}

istream& operator >>(istream& in, Examen& ob)
{
	cout << "Denumire materie:"; in >> ob.denumire;
	cout << "\nNota scris:"; in >> ob.nota_scris;
	cout << endl;
	return in;
}
Examen& Examen::operator =(const Examen& ob)
{
	if (this != &ob)
	{
		numar = ob.numar;
		denumire = ob.denumire;
		nota_scris = ob.nota_scris;
	}
	return *this;
}

void Examen::afis()
{
	cout << "La materia " << denumire << " studentul cu numarul matricol " << numar;
	cout << " a obtinut la proba scrisa nota " << nota_scris << ".\n";
}




class Partial :public Examen
{
	friend class Examen_final;
private:
	float nota_oral;
public:
	Partial() : Examen() { nota_oral = 0; }
	Partial(float no, string d, float ns) :Examen(d, ns)
	{
		nota_oral = no;
	}
	Partial(const Partial& ob) :Examen(ob)
	{
		nota_oral = ob.nota_oral;
	}
	Partial& operator =(const Partial&);
	friend istream& operator >>(istream&, Partial&);
	void afis();
	~Partial() {};
};
Partial& Partial::operator =(const Partial& ob)
{
	if (this != &ob)
	{
		nota_oral = ob.nota_oral;
		this->Examen::operator =(ob);
	}
	return *this;
}
istream& operator >>(istream& in, Partial& ob)
{
	cout << "Nota oral:";
	in >> ob.nota_oral;
	operator>>(in, static_cast<Examen&>(ob));
	return in;
}
void Partial::afis()
{
	cout << "La materia " << denumire << " studentul cu numarul matricol " << numar;
	cout << " a obtinut notele " << nota_scris << " la scris,respectiv ";
	cout << nota_oral << " la oral.";
	cout << endl;
}




class Examen_final : public Examen
{
	friend class Partial;
private:
	float extra_puncte;
public:
	Examen_final() :Examen() { extra_puncte = 0; }
	Examen_final(float e, string d, float ns) :Examen(d, ns)
	{
		extra_puncte = e;
	}
	Examen_final(const Examen_final& ob) :Examen(ob)
	{
		extra_puncte = ob.extra_puncte;
	}
	Examen_final& operator =(const Examen_final&);
	friend istream& operator >>(istream&, Examen_final&);
	void afis();
	~Examen_final() {};

	float getNotaScris()
	{
		return nota_scris;
	}
};
Examen_final& Examen_final::operator =(const Examen_final& ob)
{
	if (this != &ob)
	{
		extra_puncte = ob.extra_puncte;
		this->Examen::operator =(ob);
	}
	return *this;
}
istream& operator >>(istream& in, Examen_final& ob)
{
	cout << "Extra puncte:";
	in >> ob.extra_puncte;
	operator>>(in, static_cast<Examen&>(ob));
	return in;
}
void Examen_final::afis()
{
	cout << "Studentul cu numarul matricol" << numar << " are la materia " << denumire << " " << extra_puncte;
	cout<< " puncte extra si a obtinuta nota "<<nota_scris << " la scris." << endl;
}




template<class T>
class CatalogIndividual
{
	int index;
	static int NrMatricol;
	int NrExamene;
	T* *v;
public:

	CatalogIndividual<T>();
	CatalogIndividual<T>(int, int,T**);
	
	void citire();
	void afisare();

	CatalogIndividual<T> operator +=(T*);
};
template<class T>
int CatalogIndividual<T>::NrMatricol = 0;

template<class T>
CatalogIndividual<T>::CatalogIndividual()
{
	index = 0; NrExamene = 0;
	v = NULL;
}
template<class T>
CatalogIndividual<T>::CatalogIndividual(int i, int ne,T* *v)
{
	index = i;
	NrExamene = ne;
	v = v;
}
template<class T>
void CatalogIndividual<T>::citire()
{
	NrMatricol++;
	cout << "Nr Examene:";
	cin >> NrExamene;
	cout << endl;
	vector<Examen*> x(NrExamene);

	for(int i=0;i<NrExamene;i++)
	{
		int op; cout << "Introduceti tipul examenului,1=Partial,2=Final,3=Examen.";
		cin >> op;
		/*switch (op)
		{
		case 1: { x[i] = new Partial;
			cin >> *dynamic_cast<Partial*>(x[i]);
			cout << endl; break; }
		case 2: { x[i] = new Examen_final;
			cin >> *dynamic_cast<Examen_final*>(x[i]);
			cout << endl; break; }
		case 3: { x[i] = new Examen;
			cin >> *x[i];
			cout << endl; break; }
		}*/
		switch (op)
		{
		case 1: { x[i] = new Partial;
		cout << endl; break; }
		case 2: { x[i] = new Examen_final;
		cout << endl; break; }
		case 3: { x[i] = new Examen;
		cout << endl; break; }
		}
		cin >> *x[i];
		*this += x[i];
		i++;
	}
}
template<class T>
void CatalogIndividual<T>::afisare()
{
	Examen_final f;
	Partial p;

	for (int i = 0; i < NrExamene; i++)
	{
		cout << endl;
		if (typeid(*v[i]) == typeid(f))
			dynamic_cast<Examen_final*>(v[i])->afis();
		else if (typeid(*v[i]) == typeid(p))
		{
			dynamic_cast<Partial*>(v[i])->afis();
		}
		else
			v[i]->afis();
	}
}
template<class T>
CatalogIndividual<T> CatalogIndividual<T>::operator+=(T* ob)
{
	Examen_final f;
	Partial p;

	if (typeid(*ob) == typeid(f))
	{
		v[index] = new Examen_final;
		(*dynamic_cast<Examen_final*>(v[index])) = (*dynamic_cast<Examen_final*>(ob));
	}
	else if (typeid(*ob) == typeid(p))
	      {
		     v[index] = new Partial;
		     *dynamic_cast<Partial*>(v[index]) = *dynamic_cast<Partial*>(ob);
	      }
	      else
	       {
	        	v[index] = new Examen;
		        *v[index] = *ob;
	       }
	     
	index++;
	return *this;
}



template<>
class CatalogIndividual<unsigned>
{
private:
	int NrExamene;
	Examen_final *f;
public:
	void citire()
	{
		cin >> NrExamene;
		f = new Examen_final[NrExamene];
		for (int i = 0; i < NrExamene; i++)
			cin >> f[i];
	}
	void MedieExFinal()
	{

		float s = 0; int imp = 0;
		for(int i=0;i<NrExamene;i++)
			{
				s = s + f[i].getNotaScris();
				imp++;
			}
		s = s / imp;
		cout << s;
	}
};

int main()
{
	
	CatalogIndividual<Examen> A;
	A.citire();
	A.afisare();
	return 0;
}

