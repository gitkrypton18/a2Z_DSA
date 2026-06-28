class Solution {
public:
    string intToRoman(int num) {
        // Store values and their corresponding symbols in descending order
        int values[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
        string symbols[] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
        
        string result = "";
        
        // Iterate through the available Roman symbols
        for (int i = 0; i < 13; i++) {
            // While the current value can be subtracted from num
            while (num >= values[i]) {
                result += symbols[i]; // Append the symbol
                num -= values[i];     // Decrease the number
            }
        }
        
        return result;
    }
};