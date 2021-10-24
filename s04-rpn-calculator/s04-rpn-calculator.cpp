#include <iostream>
#include <vector>
#include <stack>
#include <string>

using std::string;
using std::vector;
using std::stack;
using std::logic_error;
using std::cout;
using std::cerr;
using std::stod;
using std::endl;

const char* InvalidONPExceptionMessage = "Niepoprawne wyrazenie ONP";
const char* DivideByZeroExceptionMessage = "Dzielenie przez 0";

auto main(int argc, const char* argv[]) -> int
{
	try 
	{
		vector<string> ONP(argv, argv + argc);
		stack<double> Stos;

		double A, B;
		for (int i = 1; i < argc; ++i)
		{
			if (ONP[i] == "+" || 
				ONP[i] == "-" || 
				ONP[i] == "*" || 
				ONP[i] == "/" || 
				ONP[i] == "**" || 
				ONP[i] == "//" || 
				ONP[i] == "%" ||
				ONP[i] == "p")
			{
				if (ONP[i] == "p")
				{
					cout << Stos.top() << endl;
					continue;
				}

				if (Stos.size() < 2)
				{
					throw logic_error { InvalidONPExceptionMessage };
				}

				A = Stos.top(); Stos.pop();
				B = Stos.top(); Stos.pop();

				if (ONP[i] == "+") /* Operator dodawania */
				{
					Stos.push(B + A);
				}
				else if (ONP[i] == "-") /* Operator odejmowania */
				{
					Stos.push(B - A);
				}
				else if (ONP[i] == "*") /* Operator mnozenia */
				{
					Stos.push(B * A);
				}
				else if (ONP[i] == "/") /* Operator dzielenia */
				{
					if (A == 0) throw logic_error { DivideByZeroExceptionMessage };
					Stos.push(B / A);
				}
				else if (ONP[i] == "**") /* Operator potegowania */
				{
					Stos.push(pow(B, A));
				}
				else if (ONP[i] == "//") /* Operator dzielenia dla liczb całkowitch */
				{
					Stos.push(floor(B / A));
				}
				else if (ONP[i] == "%") /* Zgodnie z Panem Markiem, dodałem dodatkowy operator modulo */
				{
					if (A == 0) throw logic_error { DivideByZeroExceptionMessage };
					Stos.push(floor((int)B % (int)A));
				}
			}
			else
			{
				Stos.push(stod(ONP[i]));
			}
		}

		if (Stos.size() != 1)
		{
			throw logic_error { InvalidONPExceptionMessage };
		}

		return 0;
	}
	catch (logic_error ex)
	{
		cerr << ex.what() << endl;
		return 1;
	}
}

