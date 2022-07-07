#include <bits/stdc++.h>
using namespace std;

// ! worst TC :- O(MN)
vector<int> naiveSearch(string pat, string txt)
{
    vector<int> result;
    int M = pat.length();
    int N = txt.length();

    /* A loop to slide pat[] one by one */
    for (int i = 0; i <= N - M; i++)
    {
        int j;

        /* For current index i, check for pattern match */
        for (j = 0; j < M; j++)
            if (txt[i + j] != pat[j])
                break;

        if (j == M) // if pat[0...M-1] = txt[i, i+1, ...i+M-1]
            result.push_back(i);
    }
    return result;
}

// Driver Code
int main()
{
    string pat = "AABA";
    string txt = "AABAACAADAABAAABAA";
    vector<int> resultIndices;

    resultIndices = naiveSearch(pat, txt);

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
