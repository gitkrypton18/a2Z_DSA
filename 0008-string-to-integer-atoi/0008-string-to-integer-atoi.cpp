class Solution {
public:
    int myAtoi(string s) {
        int i = 0, n = s.size();

        // Skip leading spaces
        while (i < n && s[i] == ' ')
            i++;

        // Handle sign
        int sign = 1;
        if (i < n && (s[i] == '+' || s[i] == '-')) {
            if (s[i] == '-') sign = -1;
            i++;
        }

        long long num = 0;

        // Process digits
        while (i < n && isdigit(s[i])) {
            num = num * 10 + (s[i] - '0');

            // Overflow check
            if (sign * num > INT_MAX)
                return INT_MAX;

            if (sign * num < INT_MIN)
                return INT_MIN;

            i++;
        }

        return sign * num;
    }
};