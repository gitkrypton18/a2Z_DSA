class Solution {
public:
    int mySqrt(int x) {
        long n=0;
        long y=x;
        for (long i = 1; i<=y; i++) {
            if (i *i > y) {
                n=i-1;
                break;
            }
            else if(i*i==y){
                n=i;
                break;
            }
        }
        return n;
    }
};