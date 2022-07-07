#include <bits/stdc++.h>
using namespace std;

vector<int> badCharHeuristic(string str, int size)
{
    vector<int> result(256, -1);
    for (int i = 0; i < size; i++)
        result[str[i]] = i;
    return result;
}

// ! TC :- O(M*N)
// ! SC :- O(M)
vector<int> Boyer_Moore_search(string pat, string text)
{
    vector<int> result;
    int M = pat.length();
    int N = text.length();
    // create bad match table
    vector<int> badChar = badCharHeuristic(pat, M);
    // shift of pattern with respect to text
    int s = 0;
    while (s <= N - M)
    {
        int j = M - 1;
        // start matching from right of pattern
        while (j >= 0 && pat[j] == text[s + j])
            j--;
        if (j < 0)
        {
            result.push_back(s);
            if (s + M >= N)
                s += 1; // break out of loop
            else
                s += M - badChar[text[s + M]]; // shift the pattern
        }
        else
            s += max(1, j - badChar[text[s + j]]); // shift the pattern
    }
    return result;
}

int main()
{
    string txt = "abcxabcdabxabcdabcdabcy";
    string pat = "abcdab";
    vector<int> resultIndices;

    resultIndices = Boyer_Moore_search(pat, txt);

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
