class Solution {
public:
    void swapGreat(vector<int>& arr1, vector<int>& arr2,
                   int ind1, int ind2) {

        if (arr1[ind1] > arr2[ind2]) {
            swap(arr1[ind1], arr2[ind2]);
        }
    }

    void merge(vector<int>& nums1, int m,
               vector<int>& nums2, int n) {

        int len = m + n;
        int gap = (len / 2) + (len % 2);

        while (gap > 0) {

            int left = 0;
            int right = left + gap;

            while (right < len) {

                // nums1 & nums2
                if (left < m && right >= m) {
                    swapGreat(nums1, nums2,
                              left, right - m);
                }

                // nums2 & nums2
                else if (left >= m) {
                    swapGreat(nums2, nums2,
                              left - m, right - m);
                }

                // nums1 & nums1
                else {
                    swapGreat(nums1, nums1,
                              left, right);
                }

                left++;
                right++;
            }

            if (gap == 1) break;

            gap = (gap / 2) + (gap % 2);
        }

        // copy nums2 into nums1
        for (int i = m; i < m + n; i++) {
            nums1[i] = nums2[i - m];
        }

        sort(nums1.begin(), nums1.end());
    }
};