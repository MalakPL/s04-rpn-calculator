#include <iostream>
#include <queue>
#include <vector>
#include <stack>
#include <string>

using std::string;
using std::queue;
using std::vector;
using std::stack;
using std::exception;
using std::cout;
using std::stof;
using std::endl;

const char* InvalidONPExceptionMessage = "Niepoprawne wyrazenie ONP";
const char* DivideByZeroExceptionMessage = "Dzielenie przez 0";

auto main(int argc, const char* argv[]) -> int
{
	try 
	{
		vector<string> ONP(argv, argv + argc);
		stack<float> Stos;

		float A, B;
		for (int i = 1; i < argc; ++i)
		{
			if (ONP[i] == "+" || 
				ONP[i] == "-" || 
				ONP[i] == "*" || 
				ONP[i] == "/" || 
				ONP[i] == "**" || 
				ONP[i] == "//" || 
				ONP[i] == "%")
			{
				if (Stos.size() < 2)
				{
					throw exception{ InvalidONPExceptionMessage };
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
					if (A == 0) throw exception{ DivideByZeroExceptionMessage };
					Stos.push(B / A);
				}
				else if (ONP[i] == "**") /* Operator potegowania */
				{
					Stos.push(powf(B, A));
				}
				else if (ONP[i] == "//") /* Operator dzielenia dla liczb całkowitch */
				{
					Stos.push(floor(B / A));
				}
				else if (ONP[i] == "%") /* Zgodnie z Panem Markiem, dodałem dodatkowy operator modulo */
				{
					if (A == 0) throw exception{ DivideByZeroExceptionMessage };
					Stos.push(floor((int)B % (int)A));
				}
			}
			else
			{
				Stos.push(stof(ONP[i]));
			}
		}

		if (Stos.size() != 1)
		{
			throw exception{ InvalidONPExceptionMessage };
		}

		cout << Stos.top() << endl;
		return 0;
	}
	catch (exception ex)
	{
		cout << ex.what() << endl;
		return 1;
	}
}

