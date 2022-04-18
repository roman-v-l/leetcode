#include <vector>
#include <iostream>

using namespace std;

class Solution
{
  struct VecRange
  {
    VecRange(int l, int r, vector<int> &v) : _l(l), _r(r), _v(v) {}

    int _l;
    int _r;
    vector<int> &_v;
  };

  struct CurMedian
  {
    int _ind = 0;
    bool _is_first = true;
  };

public:
  inline double getMedian(vector<int> &v)
  {
    if (v.size() % 2 == 1)
      return v[v.size() / 2];

    return ((double)v[v.size() / 2 - 1] + v[v.size() / 2]) / 2.0;
  }

  inline size_t GetUpperInd(int val, vector<int> &v, int l, int r)
  {
    while (l < r)
    {
      size_t m = (l + r) / 2;

      if (val == v[m])
      {
        r = m;
        break;
      }

      if (val > v[m])
        l = m + 1;
      else
        r = m;
    }

    return r;
  }

  double findMedianSortedArrays(vector<int> &nums1, vector<int> &nums2)
  {
    if (nums1.size() == 0)
      return getMedian(nums2);

    if (nums2.size() == 0)
      return getMedian(nums1);

    size_t total_len = nums1.size() + nums2.size();

    VecRange vr1(0, nums1.size() - 1, nums1);
    VecRange vr2(0, nums2.size() - 1, nums2);

    CurMedian cur;
    cur._ind = nums1.size() / 2;

    int ind2 = GetUpperInd(nums1[cur._ind], nums2, 0, nums2.size());
    size_t left = cur._ind + 1 + ind2;
    int diff = total_len - 2 * left;

    while (abs(diff) > 1)
    {
      cout << "diff = " << diff << " vr1.l = " << vr1._l << " vr1.r = " << vr1._r << " vr2.l = " << vr2._l << " vr2.r = " << vr2._r << endl;
      cout << "cur._ind = " << cur._ind << " cur._is_first = " << cur._is_first << " ind2 = " << ind2 << endl;

      // adjust ranges
      VecRange &cur_vr1 = (cur._is_first) ? vr1 : vr2;
      VecRange &cur_vr2 = (!cur._is_first) ? vr1 : vr2;
      if (diff > 0)
      {
        cur_vr1._l = cur._ind + 1;
        cur_vr2._l = ind2;
      }
      else
      {
        cur_vr1._r = cur._ind;
        cur_vr2._r = ind2 - 1;
      }

      int shift = diff / 2;
      ind2 += shift;
      ind2 = diff > 0 ? ind2 - 1 : ind2;

      if (ind2 >= cur_vr2._l && ind2 <= cur_vr2._r)
      {
        cur._ind = ind2;
        cur._is_first = !cur._is_first;

        if (cur_vr1._r >= cur_vr1._l)
          ind2 = GetUpperInd(cur_vr2._v[cur._ind], cur_vr1._v, cur_vr1._l, cur_vr1._r + 1);
        else
          ind2 = -1;
      }
      else
      {
        cur._ind += shift;

        if (cur_vr2._r >= cur_vr2._l)
          ind2 = GetUpperInd(cur_vr1._v[cur._ind], cur_vr2._v, cur_vr2._l, cur_vr2._r + 1);
        else
          ind2 = -1;
      }

      if (ind2 >= 0)
      {
        left = cur._ind + 1 + ind2;
        diff = total_len - 2 * left;
      }
      else
      {
        // exit on next iteration
        diff -= 2 * shift;
      }
    }

    cout << "Result:" << endl;
    cout << "diff = " << diff << " vr1.l = " << vr1._l << " vr1.r = " << vr1._r << " vr2.l = " << vr2._l << " vr2.r = " << vr2._r << endl;
    cout << "cur._ind = " << cur._ind << " cur._is_first = " << cur._is_first << " ind2 = " << ind2 << endl;

    if (diff == -1)
      return cur._is_first ? nums1[cur._ind] : nums2[cur._ind];

    VecRange &cur_vr1 = (cur._is_first) ? vr1 : vr2;
    VecRange &cur_vr2 = (!cur._is_first) ? vr1 : vr2;

    if (diff == 0)
    {
      int l = cur_vr1._v[cur._ind];
      int r = cur._ind < cur_vr1._v.size() - 1 ? cur_vr1._v[cur._ind + 1] : cur_vr2._v[ind2];
      if (ind2 >= cur_vr2._l && ind2 <= cur_vr2._r)
        r = min(r, cur_vr2._v[ind2]);

      return ((double)l + r) / 2.0;
    }

    if (diff == 1)
    {
      int m = cur._ind < cur_vr1._v.size() - 1 ? cur_vr1._v[cur._ind + 1] : cur_vr2._v[ind2];
      if (ind2 >= cur_vr2._l && ind2 <= cur_vr2._r)
        m = min(m, cur_vr2._v[ind2]);

      return m;
    }

    return 0;

    /*    size_t ind1 = nums1.size() / 2;
        bool is_nums1 = true;
        size_t ind2 = GetUpperInd(nums1[ind1], nums2);
        size_t left = ind1 + ind2;
        int diff = total_len - 2 * left;

        auto searchInd = [this](size_t &ind1, vector<int> &nums1, size_t &ind2, vector<int> &nums2, int shift, bool &is_nums1)
        {
          if (ind1 + shift >= 0 && ind1 + shift < nums1.size())
          {
            ind1 += shift;

            if (shift > 0)
              --ind1;

            ind2 = GetUpperInd(nums1[ind1], nums2);
            is_nums1 = !is_nums1;
          }
          else
          {
            ind2 += shift;
            ind2 = GetUpperInd(nums2[ind2], nums1);
          }
        };

        while (abs(diff) > 1)
        {
          cout << "diff = " << diff << " ind1 = " << ind1 << " ind2 = " << ind2 << " is_nums1 = " << is_nums1 << "\n";

          int shift = diff / 2;

          if (is_nums1)
            searchInd(ind2, nums2, ind1, nums1, shift, is_nums1);
          else
            searchInd(ind1, nums1, ind2, nums2, shift, is_nums1);

          left = ind1 + ind2;
          diff = total_len - 2 * left;
          cout << "diff = " << diff << " ind1 = " << ind1 << " ind2 = " << ind2 << " is_nums1 = " << is_nums1 << "\n";
        }

        cout << "ind1 = " << ind1 << " ind2 = " << ind2 << " is_nums1 = " << is_nums1 << "\n";

        if (total_len % 2 == 1)
          return is_nums1 ? nums1[ind1] : nums2[ind2];

        return 0;*/
  }

  double test(vector<int> &nums1, vector<int> &nums2)
  {
    vector<int> nums;

    size_t i = 0;
    size_t j = 0;

    while (i < nums1.size() || j < nums2.size())
    {
      if (i < nums1.size() && j < nums2.size())
      {
        if (nums1[i] < nums2[j])
          nums.push_back(nums1[i++]);
        else
          nums.push_back(nums2[j++]);
      }
      else if (i < nums1.size())
      {
        nums.push_back(nums1[i++]);
      }
      else
      {
        nums.push_back(nums2[j++]);
      }
    }

    return getMedian(nums);
  }
};

#include <random>

int main()
{
  Solution s;

  vector<int> nums1; // = {2, 3, 6, 7};
  vector<int> nums2; // = {1, 8};

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> distrib(0, 2);

  int val1 = 0;
  int val2 = 0;
  for (int i = 0; i < 1000; ++i)
  {
    val1 += distrib(gen);
    nums1.push_back(val1);
    val2 += distrib(gen);
    nums2.push_back(val2);
  }

  cout << "Size of nums1: " << nums1.size() << endl;
  cout << "Size of nums2: " << nums2.size() << endl;

  // cout << s.GetUpperInd(2, nums1) << endl;
  cout << "findMedianSortedArrays returns: " << s.findMedianSortedArrays(nums1, nums2) << endl;
  cout << "test returns: " << s.test(nums1, nums2) << endl;
}