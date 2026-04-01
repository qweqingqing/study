#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;




int main(){
    int n;//物品数量
    int V;//背包容量
    cin>>n>>V;
    vector<int> v(n+1),w(n+1);
    for (int i = 1; i <= n; i++) 
        cin >> v[i] >> w[i]; 
    vector<vector<int>> dp(n+1,vector<int>(V+1));

    for(int i=1;i<=n;i++){
        dp[i]=dp[i-1];
        for(int j=v[i];j<=V;j++){
            dp[i][j]=max(dp[i][j],dp[i-1][j-v[i]]+w[i]);

        }

    }
    cout<<dp[n][V]<<endl;
}