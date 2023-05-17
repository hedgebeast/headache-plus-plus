#include <iostream>
#include <string>
#include <cmath>

using namespace std;

/* Done by: Leon Cai
 * 
*/

double Pi1(int nTerm) {
    return nTerm == 0 ? 4 : 4*pow(-1, nTerm)/(2*nTerm+1) + Pi1(nTerm-1);
}

double Pi2(int nTerm){
    int k = 1;
    double sum_n_terms = 0;
    
    while (k <= nTerm){
        sum_n_terms += pow(-1, k-1)/((2*k)*(2*k + 1)*(2*k + 2));
        
        k++;
    }
    return 3 + 4*sum_n_terms;
}

double Pi3(int nTerm) {
    double x1 = 1.0/5;
    double x2 = 1.0/239;
    int k = 0;
    double arctan_x1 = 0;
    double arctan_x2 = 0;
    
    do {
        arctan_x1 += pow(-1, k)*pow(x1, 2*k + 1)/(2*k + 1);    
        arctan_x2 += pow(-1, k)*pow(x2, 2*k + 1)/(2*k + 1); 
    
        k++;
//        cout << "Current k value is: " << k << endl;
    } while (k <= nTerm);
        
    return 4*(4*arctan_x1 - arctan_x2);
}

int main() {
    
    int n;
    const double PI = 3.141592653589793238463;
    double pi_1, pi_2, pi_3;
    
    cout << "Please enter the number of terms you want to use for approximation: ";
    cin >> n;
    cout << "The number of terms you have entered = " << n << endl;
    cout << endl;
    
    if (n <= 0) {
        throw invalid_argument("Number of terms must be POSITIVE!");
    } 
    
    pi_1 = Pi1(n);
    pi_2 = Pi2(n);
    pi_3 = Pi3(n);
    
    cout << "Pi1 approximation is: " << pi_1 << endl;
    cout << "Error of Pi1 approximation against the PI constant is: " << PI - pi_1 << endl;
    cout << endl;
    
    cout << "Pi2 approximation is: " << pi_2 << endl;
    cout << "Error of Pi2 approximation against the PI constant is: " << PI - pi_2 << endl;
    cout << endl;
    
    cout << "Pi3 approximation is: " << pi_3 << endl;
    cout << "Error of Pi3 approximation against the PI constant is: " << PI - pi_3 << endl;
    
    return 0;
}

