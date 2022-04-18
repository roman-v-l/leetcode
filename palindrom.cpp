#include <string>
#include <iostream>

using namespace std;

    string longestPalindrome(string s) {
        if (s.length() == 1)
            return s;
        
        unsigned short* even_inds = new unsigned short[s.length()];
        for (int i = 0; i < s.length(); ++i)
            even_inds[i] = 0;
        
        unsigned short* odd_inds = new unsigned short[s.length()];
        for (int i = 0; i < s.length(); ++i)
            odd_inds[i] = 1;
        
        int longest_len = 1;
        int longest_ind = 0;

        bool improved_odd = true;
        bool improved_even = true;
        for (int cur_len = 2; cur_len <= s.length() && (improved_odd || improved_even); ++cur_len)
        {
            if (cur_len % 2 == 0 && improved_even)
            {
                improved_even = false;
                // even palindrom case
                for (int i = 1; i < s.length() - cur_len + 2; ++i)
                {
                    if (even_inds[i] == cur_len - 2 && s[i - 1] == s[i + cur_len - 2])
                    {
                        even_inds[i - 1] = cur_len;
                        improved_even = true;
                        
                        if (longest_len < cur_len)
                        {
                            longest_len = cur_len;
                            longest_ind = i - 1;
                        }
                    }
                }
            }
            else if (cur_len % 2 == 1 && improved_odd)
            {
                improved_odd = false;
                // odd palindrom case
                for (int i = 1; i < s.length() - cur_len + 2; ++i)
                {
                    if (odd_inds[i] == cur_len - 2 && s[i - 1] == s[i + cur_len - 2])
                    {
                        odd_inds[i - 1] = cur_len;
                        improved_odd = true;
                        
                        if (longest_len < cur_len)
                        {
                            longest_len = cur_len;
                            longest_ind = i - 1;
                        }
                    }
                }
            }
        }
        
        return s.substr(longest_ind, longest_len);
    }

int main()
{
    std::cout << "For string babad: " << longestPalindrome("babad") << std::endl;
    return 0;
}

