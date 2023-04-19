#include <iostream>

bool checkPrime(int numberToCheck)
{

}

// Method to iterate the loop from l to r
// If the current number is prime, sum the value
int primeSum(int l)
{
    int sum = 0;
    for (int i = 1; i <= l; i++) {

        bool isPrime = true;
        if(i == 1) {
            isPrime = false;
        }
        for (int j = 2; j*j <= i; j++) {
            if (i % j == 0) {
                isPrime = false;
                break;
            }
            else isPrime = true;
        }
        if (isPrime) {

            // Sum the prime number
            sum = sum + i;
        }
    }
    return sum;
}

int main() {
    int a = primeSum(23);
    std::cout << a << std::endl;
    return 0;
}