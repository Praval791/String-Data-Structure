#include <bits/stdc++.h>
using namespace std;

// * The Z array = stores longest substring starting at index i which is also prefix a of the string of pattern.
// * pat = a b c a b a b c d a
// * zAr = 0 0 0 2 0 3 0 0 0 1

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
    cout << z_array[15];
    for (int i = M + 1; i < totalLength; i++)
        if (z_array[i] == M)
            result.push_back(i - M - 1);

    return result;
}

int main()
{
    string txt = "abcxabcdabxabcdabcdabcy";
    string pat = "abcdab";
    vector<int> resultIndices;

    resultIndices = Z_search(pat, txt);

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
