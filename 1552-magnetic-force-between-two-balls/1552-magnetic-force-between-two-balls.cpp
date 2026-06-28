class Solution {
public:
// just like aggresive cows 
    bool canWePlace(vector<int>& arr,int dist,int cow){
        int cnt_cow=1, last_cow=arr[0];
        int n=arr.size();
        for(int i=1;i<n;i++){
            if(arr[i]-last_cow >= dist){
                cnt_cow++;
                last_cow=arr[i];
            }
        }
        if(cnt_cow>=cow) return true;
        else return false;
    }
    int maxDistance(vector<int>& position, int m) {
        int n=position.size();
        sort(position.begin(),position.end());
        int low=0,high=position[n-1]-position[0];
        while(low<=high){
            int mid=(low+high)/2;
            if(canWePlace(position,mid,m)==true) low=mid+1;
            else high=mid-1;

        }
        return high;
    }
};