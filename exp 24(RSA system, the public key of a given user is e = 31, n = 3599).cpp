#include <stdio.h>
int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}
int modInverse(int a, int m) {
    int m0 = m, t, q;
    int x0 = 0, x1 = 1;
    if (m == 1)
        return 0;
    while (a > 1) {
        q = a / m;
        t = m;
        m = a % m;
        a = t;
        t = x0;
        x0 = x1 - q * x0;
        x1 = t;
    }
    if (x1 < 0)
        x1 += m0;
    return x1;
}
int main() {
    int n = 3599;
    int e = 31;
    int p, q;
    for (p = 2; p < n; p++) {
        if (n % p == 0) {
            q = n / p;
            if (p * q == n) {
                break;
            }
        }
    }
    printf("Factors of %d are p = %d and q = %d\n", n, p, q);
    int phi = (p - 1) * (q - 1);
    printf("phi(%d) = %d\n", n, phi);
    int d = modInverse(e, phi);
    if (d != -1) {
        printf("The private key d is: %d\n", d);
    } else {
        printf("Modular inverse does not exist.\n");
    }
    return 0;
}

