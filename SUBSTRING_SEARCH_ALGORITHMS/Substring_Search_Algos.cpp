#include <bits/stdc++.h>
using namespace std;

class Substring_Search_Algos
{
    // ! TC :- O(M)
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
    vector<int> z_array_util(string str)
    {
        int M = str.length();
        vector<int> result(M);
        // Both end of that window or z-box, that matches with prefix of str
        int left = 0, right = 0, k;
        for (int i = 1; i < M; ++i)
        {
            // if i > right means we have to make a new z-box
            if (i > right)
            {
                left = i;
                right = i;
                while (right < M && str[right - left] == str[right])
                    ++right;
                result[i] = right - left;
                --right;
            }
            // else if i lies in z box then try to copy the previously calculated result if possible
            else
            {
                // k is the index that's result we can copy to the ith position
                // as the first time we try to copy then the i always be 1 greater then left because in previous pass we calculate left = i and in this pass we increase i's value by one so this we get k as 1 . Now why we don't need k = 0 as the first time because the z-box is already check for 0th element that's is why this increases i's right bound . If we get next element as well in the z-box then now i will increase i's value by 1 and left is stays the same so now i - left will be the also increases by 1 .
                // Thus we mark the location that's result we can copy to the ith position.
                k = i - left;
                // simply copy the previous result if result[k] doesn't touch the right bound
                if (result[k] < right - i + 1)
                    result[i] = result[k];
                else
                {
                    // set left bound to i then do the comparisons
                    left = i;
                    while (right < M && str[right - left] == str[right])
                        ++right;
                    result[i] = right - left;
                    --right;
                }
            }
        }
        return result;
    }

    // ! TC :- O(M)
    int createHash(string str, int size, int prime, int numberOfChars)
    {
        // Strong hash p :- Prime number, d :- number of characters
        // hash(s) =  (s[0] % p + (s[1] * d) % p + (s[2] * d²) % p + ....) % p
        int hash = 0;
        for (int i = 0; i < size; i++)
            hash = (hash * numberOfChars + str[i]) % prime;
        return hash;
    }

    vector<int> badCharHeuristic(string str, int size)
    {
        vector<int> result(256, -1);
        for (int i = 0; i < size; i++)
            result[str[i]] = i;
        return result;
    }

public:
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

    // ! TC :- O(M+N)
    // ! SC :- O(M)
    vector<int> Z_search(string pat, string text)
    {
        vector<int> result;
        int M = pat.length();
        int N = text.length();
        // ! '$' must not contain either in pat or text
        vector<int> z_array = z_array_util(pat + '$' + text);
        int totalLength = M + N + 1;

        for (int i = M + 1; i < totalLength; i++)
            if (z_array[i] == M)
                result.push_back(i - M - 1);

        return result;
    }

    // ! worst TC :- O(MN) {due to collisions}
    vector<int> RK_Search(string pat, string text, int prime = 5381)
    {
        vector<int> result;
        int M = pat.length();
        int N = text.length();

        // total number of characters
        int d = 256;

        // require to calculate next hash (more specifically when adding hash of leading character)
        // h = pow(d, m-1) % Prime
        int h = 1;
        for (int i = 1; i <= M - 1; i++)
            h = (h * d) % prime;

        // hash value for pattern and text
        int patternHash = createHash(pat, M, prime, d);
        int textHash = createHash(text, M, prime, d);

        for (int i = 0; i <= N - M; i++)
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
            {
                textHash = (d * (textHash - text[i] * h) + text[i + M]) % prime;
                if (textHash < 0)
                    textHash += prime;
            }
        }
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
};

int main()
{
    string txt = "abcxabcdabxabcdabcdabcy";
    string pat = "abcdab";
    Substring_Search_Algos algos;
    vector<int> resultIndices;

    resultIndices = algos.Z_search(pat, txt);

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
