#include <bits/stdc++.h>
#define int long long
#define task "Divisions_Fermat."

using namespace std;

// Phép nhân Ấn Độ (a * b) % mod. Sử dụng để tránh tràn số khi thực hiện phép nhân.
long long indian_multiplication(long long a, long long b, long long mod){
    if (b == 0)		return 0LL;
    long long half = indian_multiplication(a, b / 2LL, mod) % mod;
    if (b & 1)	return (half + half + a) % mod;
    else		return (half + half) % mod;
}

// Tính (a^b) % mod. Sử dụng kết hợp với phép nhân Ấn Độ để tránh tràn số khi thực hiện phép nhân.
long long modular_exponentiation(long long a, long long b, long long mod){
    if (b == 0)	return 1LL;
    long long half = modular_exponentiation(a, b / 2LL, mod) % mod;
    long long product = indian_multiplication(half, half, mod);
    if (b & 1)	return indian_multiplication(product, a, mod);
    else		return product;
}

// Thực hiện kiểm tra Fermat với k = 50 lần.
bool fermat_checking(long long n, int k = 50){
    // Xủ lý trước một số trường hợp để tăng tính chính xác.
    // Cần tránh trước trường hợp n = 4, do trường hợp này kiểm tra Fermat bị sai.
    if (n < 4)						return n == 2 || n == 3;
    if (n != 2 && n % 2 == 0)    	return false;
    for (int i = 1; i <= k; ++i){
        long long a = 2 + rand() % (n - 3);
        if (modular_exponentiation(a, n - 1, n) != 1)
            return false;
    }
    return true;
}


// Sàng lọc số nguyên tố.
vector < int > eratosthenes_sieve(int max_value)
{
    vector < bool > is_prime(max_value + 1, true);
    is_prime[0] = is_prime[1] = false;

    for (int i = 2; i * i <= max_value; ++i)
        if (is_prime[i])
            for (int j = i * i; j <= max_value; j += i)
                is_prime[j] = false;

    vector < int > primes;
    for (int i = 2; i <= max_value; ++i)
        if (is_prime[i])
            primes.push_back(i);

    return primes;
}

void solution(int n)
{
    // Sàng lọc các số nguyên tố từ 1 tới 10^6 (bằng với n^(1/3) trong trường hợp lớn nhất).
    vector < int > primes = eratosthenes_sieve(1000000);

    // Tính F(x) với x bao gồm tất cả các thừa số nguyên tố nhỏ hơn hoặc bằng n^(1/3). Lưu luôn F(x) vào res.
    long long res = 1;
    for (int p: primes)
    {
        if (p * p * p > n)
    		break;

        int cnt = 0;
        while (n % p == 0)
        {
            n /= p;
            ++cnt;
        }

        res *= (cnt + 1);
    }

    // Tính F(y) với y bao gồm tất cả các thừa số nguyên tố lớn hơn n^(1/3). Chắc chắn y chỉ có thể ở một trong ba
    // trường hợp: là số nguyên tố, là bình phương một số nguyên tố hoặc là tích của hai số nguyên tố phân biệt.
    if (fermat_checking(n))
        res *= 2LL;
    else
    {
        int squaroot = sqrt(n);
        if (squaroot * squaroot == n && fermat_checking(squaroot))
            res *= 3;
        else if (n != 1)
            res *= 4;
    }

    cout << res;
}

main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    int n;
    cin >> n;

    solution(n);

    return 0;
}
