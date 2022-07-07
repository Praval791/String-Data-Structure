#include <bits/stdc++.h>
using namespace std;

// * Create a hash of pattern then try to match with the hash of the window(same size of pattern).
// * Here we use rolling hash function
// * hash(s) = s[0] + s[1] * p + s[2] * p² + ··· + s[n − 1] * p⁽ⁿ⁻¹⁾

long long createHash(string str, int size, int prime)
{
    long long hash = 0;
    for (int i = 0; i < size; i++)
        hash += str[i] * pow(prime, i);
    return hash;
}

// ! TC :- O(M+N)
// ! SC :- O(M)
vector<int> RK_Search(string pat, string text, int prime = 101)
{
    vector<int> result;
    int M = pat.length();
    int N = text.length();
    long long highestPowerOfPrime = pow(prime, M - 1);
    long long patternHash = createHash(pat, M, prime);
    long long textHash = createHash(text, M, prime);

    for (int i = 0; i < N - M; i++)
    {
        if (patternHash == textHash)
        {
            // Check for character one by one
            int j;
            for (j = 0; j < M; j++)
            {
                if (text[i + j] != pat[j])
                    break;
            }
            if (j == M)
                result.push_back(i);
        }
        if (i < N - M)
            textHash = ((textHash - text[i]) / prime) + (text[i + M] * highestPowerOfPrime);
    }
    return result;
}

int main()
{
    string txt = "abcxabcdabxabcdabcdabcy";
    string pat = "abcdab";
    vector<int> resultIndices;

    resultIndices = RK_Search(pat, txt);

    if (resultIndices.size() == 0)
        cout << "\nPattern not found";
    else
    {
        if (resultIndices.size() == 1)
            cout << "\nPattern found at index " << resultIndices[0];
        else
        {
            cout << "\nPattern found at indices";
            for (int index : resultIndices)
                cout << " " << index;
        }
    }
    cout << "\n";

    return 0;
}
