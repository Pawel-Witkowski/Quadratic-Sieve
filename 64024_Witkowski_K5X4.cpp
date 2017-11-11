#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <tchar.h>
#include <math.h>
#include <vector>
using namespace std;
typedef long long int int2;
void convert(int2 n, vector<int> &cont);
int2 pot_mod(int2 a, int2 n, int2 mod);
int2 pot(int2 a, int2 n);
void SitoErastotenesa(int2 p, vector<int2> &Primes);
int2 SitoKwadratowe(int2 N, vector<vector<int2>> &TF);

int main() {
	int2 N,FunctionValue,Multiplication=1,Trywialny_Dzielnik;
	vector < vector <int2>> TF;
	vector <int2> P_Gladkie;
	cout << "Podaj N dla ktorego ma zostac przeprowadzony algorytm sita kwadratowego." << endl;
	cin >> N;
	cout << "b zostalo wyznaczone wzorem b=2*a\nP zostalo wyznaczone wzorem exp(sqrt((1/2)*log(N)*log(log(N)))" << endl << endl;
	Trywialny_Dzielnik=SitoKwadratowe(N, TF);
	if (Trywialny_Dzielnik == 0){
		cout << endl << "P Gladkie: " << endl;
		for (int i = 0; i < TF.size(); i++) {
			FunctionValue = pot(TF[i][0], 2) - N;
			Multiplication = 1;
			for (int j = 1; j < TF[i].size(); j++) {
				Multiplication *= TF[i][j];
			}
			if ((FunctionValue!=1)&&(Multiplication == FunctionValue))  {
				cout << "F(" << TF[i][0] << ")\t" << FunctionValue << "\t\tbaza rozkladu = ";
				int l = 1;
				for (int k = 2; k <= TF[i].size(); k++) {
					if ((k == TF[i].size()) || (TF[i][k] != TF[i][k - 1])) {
						if (l==1) cout << TF[i][k - 1] << " ";
						else cout << TF[i][k - 1] << "^" << l << " ";
						l = 1;
					}
					else l++;
				}
				cout << endl;
			}

		}
	}
	else cout << "Podana liczba: " << N << " ma trywialny dzielnik rowny " << Trywialny_Dzielnik << "." << endl;



	system("PAUSE");
	return 0;
}
void convert(int2 n, vector<int> &cont) {
	int2 reszta = n % 2;
	if (n > 1) convert((int2)(n / 2), cont);
	cont.push_back(reszta);
}
int2 pot_mod(int2 a, int2 n, int2 mod) {
	int2 value = 1;
	int2 temp = a;
	vector<int>cont;
	convert(n, cont);
	for (int i = cont.size() - 1; i >= 0; i--) {
		if (cont[i] != 0)
			value *= temp;
		temp *= temp;
		value %= mod;

	}
	return value;
}
int2 pot(int2 a, int2 n) {
	int2 value = 1;
	int2 temp = a;
	vector<int>cont;
	convert(n, cont);
	for (int i = cont.size() - 1; i >= 0; i--) {
		if (cont[i] != 0)
			value *= temp;
		temp *= temp;
	}
	return value;
}
void SitoErastotenesa(int2 p, vector<int2> &Primes) {
	int2 *TemporaryTab = new int2[p];
	int j;
	for (int i = 1; i <= p; i++) {
		TemporaryTab[i] = i;
	}
	for (int i = 2; i*i <= p; i++) {
		if (TemporaryTab[i] != 0) {
			j = i + i;
			while (j <= p) {
				TemporaryTab[j] = 0;
				j += i;
			}
		}
	}
	for (int i = 2; i <= p; i++) if (TemporaryTab[i] != 0) Primes.push_back(TemporaryTab[i]);
}
int2 SitoKwadratowe(int2 N, vector<vector<int2>> &TF) {
	int2 LowerBorder = (int2)sqrt((long double)N) + 1;
	int2 UpperBorder =  2 * LowerBorder;
	int2 PrimeBorder;
	int2 ValueMod;
	int2 FirstRoot=1, SecondRoot=1;
	bool First = false, Second = false, Exists = true;
	int2 value;
	int2 Mod;
	vector <int2> PrimeNumbers;
	long double power = log(N)*log(log(N));
	power /= 2;
	power = sqrt(power);
	PrimeBorder = (int2)exp(power) + 1;
	SitoErastotenesa(PrimeBorder, PrimeNumbers);
	cout << "b: " << UpperBorder << endl << "P: " << PrimeBorder << endl << endl;
	//for (int i = 0; i < PrimeNumbers.size(); i++) cout << PrimeNumbers[i] << " ";
	for (int i = 0; i < LowerBorder + 1; i++) {
		vector<int2> temp;
		temp.push_back(LowerBorder + i);
		TF.push_back(temp);
	}
	for (int i = 0; i < PrimeNumbers.size(); i++) {
		Mod = PrimeNumbers[i];
		ValueMod = N % Mod;
		if (ValueMod == 0) return Mod;
		int2 x = -1, y = 2, z = 0;
		First = false;
		Second = false;
		Exists = true;
		if (PrimeNumbers[i] == 2) {
			do {
				value = ValueMod + z*Mod;
				z++;
				if ((value >= LowerBorder) && (value <= UpperBorder)) TF[value - LowerBorder].push_back(PrimeNumbers[i]);
			} while (value <= UpperBorder);
		}
		else {

			do {
				x++;
				power = pot_mod(x, 2, Mod);
				if ((power == ValueMod) && (First == true)) {
					Second = true;
					SecondRoot = x;
				}
				if ((power == ValueMod) && (First == false)) {
					First = true;
					FirstRoot = x;				
				}				
				if ((x%Mod == (Mod - 1)) && (First == false) && (Second == false)) {
					Exists = false;
				}
			} while ((Exists) && (!(First&&Second)));

			if (Exists) {
				z = 0;
				do {
					value = FirstRoot + z*Mod;
					z++;
					if ((value >= LowerBorder) && (value <= UpperBorder)) TF[value - LowerBorder].push_back(PrimeNumbers[i]);
				} while (value <= UpperBorder);
				z = 0;
				if (FirstRoot!=SecondRoot){ 
					do {
						value = SecondRoot + z*Mod;
						z++;
						if ((value >= LowerBorder) && (value <= UpperBorder)) TF[value - LowerBorder].push_back(PrimeNumbers[i]);
					} while (value <= UpperBorder);
				}
			}
		}
		y = 2;
		if (Exists) {
			Mod = pot(PrimeNumbers[i], y);			
			bool stop = false;
			while (!stop) {
				ValueMod = N%Mod;
				First = false;
				Second = false;
				x = -1;
				stop = true;
				do {				
					x++;
					power = pot_mod(x, 2, Mod);
					if ((power == ValueMod) && (First == true)) {
						Second = true;
						SecondRoot = x;
					}
					if ((power == ValueMod) && (First == false)) {
						First = true;
						FirstRoot = x;					
					}
					if ((x%Mod == (Mod - 1)) && (First == false) && (Second == false)) {
						Exists = false;
					}
				} while ((Exists) && (!(First && Second)));
				if (Exists) {
					
					z = 0;
					do {
						value = FirstRoot + z*Mod;
						z++;
						if ((value >= LowerBorder) && (value <= UpperBorder)) {
							TF[value - LowerBorder].push_back(PrimeNumbers[i]);
							stop = false;
						}
					} while (value <= UpperBorder);
					z = 0;
					if (FirstRoot != SecondRoot) {
							do {
							value = SecondRoot + z*Mod;
							z++;
							if ((value >= LowerBorder) && (value <= UpperBorder)) TF[value - LowerBorder].push_back(PrimeNumbers[i]);
						} while (value <= UpperBorder);
					}
				}
				y++;
				Mod = pot(PrimeNumbers[i], y);
			}
		}
	}
	return 0;
}