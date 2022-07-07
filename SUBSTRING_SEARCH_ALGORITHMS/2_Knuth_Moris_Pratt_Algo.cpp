#include <bits/stdc++.h>
using namespace std;

// * The KMP matching algorithm uses degenerating property (pattern having same sub-patterns appearing more than once in the pattern) of the pattern

// * LPS :- [longest prefix which is same as some suffix]
// * stores the length of the prefix(beginning) of pattern that is matching at any other position in the pattern
// * pat = a a b c a a b a b c a
// * LPS = 0 1 0 0 1 2 3 1 0 0 1

// ! TC :- O(N)
vector<int> longest_proper_suffix(string pat)
{
    int M = pat.length();
    vector<int> result(M);
    int index = 0;
    for (int i = 1; i < M;)
    {
        if (pat[index] == pat[i])
        {
            result[i] = index + 1;
            index++;
            i++;
        }
        else
        {
            if (index != 0)
                index = result[index - 1];
            else
                result[i] = 0, i++;
        }
    }

    return result;
}

// ! TC :- O(M+N)
// ! SC :- O(M)
vector<int> KMP_search(string pat, string text)
{
    vector<int> result;
    int M = pat.length();
    int N = text.length();
    vector<int> lps;
    lps = longest_proper_suffix(pat);
    int i = 0;
    int j = 0;
    while (i < N)
    {
        if (pat[j] == text[i])
            i++, j++;
        if (j == M)
            result.push_back(i - j), j = lps[j - 1];
        else if (i < N && pat[j] != text[i])
        {
            if (j != 0)
                j = lps[j - 1];
            else
                i++;
        }
    }
    return result;
}

int main()
{
    string txt = "abcxabcdabxabcdabcdabcy";
    string pat = "abcdab";
    vector<int> resultIndices;

    resultIndices = KMP_search(pat, txt);

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
