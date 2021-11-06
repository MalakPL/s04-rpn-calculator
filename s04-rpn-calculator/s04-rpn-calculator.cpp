/*
	Poprawny output: https://github.com/user943-24/Podstawy-Programowania/blob/main/src/s04-rpn-calculator-oo.txt
*/

#include <iostream>
#include <vector>
#include <stack>
#include <string>
#include <map>

using std::string;
using std::vector;
using std::stack;
using std::logic_error;
using std::map;
using std::cout;
using std::cerr;
using std::stod;
using std::endl;

const char* InvalidONPExceptionMessage = "Niepoprawne wyrazenie ONP";
const char* DivideByZeroExceptionMessage = "Dzielenie przez 0";

/* Globalny Stos */
stack<double> Stos;

#pragma region Operatory
void Add()
{
	/* Sprawdzenie poprawności stosu */
	if (Stos.size() < 2) { throw logic_error{ InvalidONPExceptionMessage }; }

	double A, B;
	B = Stos.top(); Stos.pop();
	A = Stos.top(); Stos.pop();
	Stos.push(A + B);
}

void Sub()
{
	/* Sprawdzenie poprawności stosu */
	if (Stos.size() < 2) { throw logic_error{ InvalidONPExceptionMessage }; }

	double A, B;
	B = Stos.top(); Stos.pop();
	A = Stos.top(); Stos.pop();
	Stos.push(A - B);
}

void Mul()
{
	/* Sprawdzenie poprawności stosu */
	if (Stos.size() < 2) { throw logic_error{ InvalidONPExceptionMessage }; }

	double A, B;
	B = Stos.top(); Stos.pop();
	A = Stos.top(); Stos.pop();
	Stos.push(A * B);
}

void Div()
{
	/* Sprawdzenie poprawności stosu */
	if (Stos.size() < 2) { throw logic_error{ InvalidONPExceptionMessage }; }

	double A, B;
	B = Stos.top(); Stos.pop();
	A = Stos.top(); Stos.pop();
	if (A == 0) throw logic_error{ DivideByZeroExceptionMessage };
	Stos.push(A / B);
}

void Pow()
{
	/* Sprawdzenie poprawności stosu */
	if (Stos.size() < 2) { throw logic_error{ InvalidONPExceptionMessage }; }

	double A, B;
	B = Stos.top(); Stos.pop();
	A = Stos.top(); Stos.pop();
	Stos.push(pow(A, B));
}

void DivInt()
{
	/* Sprawdzenie poprawności stosu */
	if (Stos.size() < 2) { throw logic_error{ InvalidONPExceptionMessage }; }

	double A, B;
	B = Stos.top(); Stos.pop();
	A = Stos.top(); Stos.pop();
	Stos.push(floor(A / B));
}

void Mod()
{
	/* Sprawdzenie poprawności stosu */
	if (Stos.size() < 2) { throw logic_error{ InvalidONPExceptionMessage }; }

	double A, B;
	B = Stos.top(); Stos.pop();
	A = Stos.top(); Stos.pop();

	if (B == 0) throw logic_error{ DivideByZeroExceptionMessage };
	Stos.push(floor((int)A % (int)B));
}

void Sqrt()
{
	/* Sprawdzenie poprawności stosu */
	if (Stos.size() < 1) { throw logic_error{ InvalidONPExceptionMessage }; }

	double A;
	A = Stos.top(); Stos.pop();
	Stos.push(sqrt(A));
}

void Print()
{
	/* Sprawdzenie poprawności stosu */
	if (Stos.size() < 1) { throw logic_error{ InvalidONPExceptionMessage }; }

	cout << Stos.top() << endl;
}

bool isPrime(int N)
{
	if (N < 2) { return false; }
	if (N == 2) { return true; }
	if (N % 2 == 0) { return false; }
	double sq = sqrt(N);
	for (int i = 3; i <= sq; i += 2)
	{
		if (N % i == 0) { return false; }
	}

	return true;
	/*
	Lub warunek 2^p mod p == 2, gdzie p to liczba pierwsza. Szybsza metoda, jednak potrzebuje więcej pamięci. Można użyć szybkiego potęgowania modularnego do optymalizacji.
	2^p (np. Poziomy w Trójkącie Pascala)-> https://upload.wikimedia.org/wikipedia/commons/thumb/0/05/Pascal4.png/330px-Pascal4.png
	*/
}

void MyFunc()
{
	if (Stos.size() < 1) { throw logic_error{ InvalidONPExceptionMessage }; }

	double A;
	A = Stos.top(); Stos.pop();

	Stos.push(isPrime((int)A) ? (int)A : 0);
}
#pragma endregion

/* Mapowanie znaków jako funkcje */
map<string, void (*)()> Opeartory {
	{ "+", Add },
	{ "-", Sub },
	{ "*", Mul },
	{ "/", Div },
	{ "**", Pow },
	{ "//", DivInt },
	{ "%", Mod },
	{ "sqrt", Sqrt },
	{ "p", Print },
	{ "prime", MyFunc }, /* Zgodnie z Panem Markiem, własna funkcja, jeżeli liczba na stosie jest pierwsza to ją zwraca, w innym wypadku zwraca 0 */
};

auto main(int argc, const char* argv[]) -> int
{
	try
	{
		vector<string> ONP(argv + 1, argv + argc); /* Argumenty. Omijamy pierwszy, ktory jest sciezka do pliku wykonalnego */

		/* Zgodnie z zadaniem wykorzystałem range-based for */
		for (const string Element : ONP)
		{
			if (Opeartory.find(Element) != Opeartory.end()) /* Jeżeli jest opreatorem */
			{
				Opeartory[Element]();
			}
			else /* Jeżeli nie jest operatorem */
			{
				Stos.push(stod(Element));
			}
		}

		/* Sprawdzenie poprawności stosu */
		if (Stos.size() != 1) { throw logic_error{ InvalidONPExceptionMessage }; }

		return 0;
	}
	catch (logic_error ex)
	{
		cerr << ex.what() << endl;
		return 1;
	}
}

