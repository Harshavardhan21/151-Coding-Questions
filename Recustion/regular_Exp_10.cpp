//first question: Match entire string
class Solution {
public:
    bool check(string s, int i, string p, int j){
        if(i==s.length()&&j==p.length()){
            return true;
        }
        if(i==s.length() || j==p.length()){
            return false;
        }
        if(s[i]==p[j]){
            return check(s,i+1,p,j+1);
        }else{
            if(p[j]=='.'){
                return check(s,i+1,p,j+1);
            }else if(p[j]=='*'){
                return check(s,i+1,p,j) || check(s,i+1,p,j+1);
            }else{
                return false;
            }
        }
    }
    bool isMatch(string s, string p) {
        return check(s,0,p,0);
    }
};

//second match partial in pattern
class Solution {
public:
    bool isMatch(string s, string p) {
        return helper(0,s,0,p);
    }
    bool helper(int i , string s , int j , string p){
        if(i>=s.length() && j>=p.length())    // both the strings are exhausted with matching
            return true;
        if(j>=p.length())       // we have exhausted pattern but havent come up with complete match of s
            return false;
        bool matched = (i<s.length() && (s[i] == p[j] || p[j] == '.'));  // first chrs match
        bool notTake = false , take = false ;
        if(j+1<p.length() && p[j+1] == '*'){        // if we have preceeding *
            notTake = helper(i,s,j+2,p);
            take = false;
            if(matched){
                take = helper(i+1,s,j,p);
            }
            return take || notTake;
        }
        if(matched){                // if we dont have preceeding *
            return helper(i+1,s,j+1,p);
        }
        return false;
        
    }
};

//Memoization
class Solution {
public:
    bool isMatch(string s, string p) {
        vector<vector<int>>dp(s.length()+1,vector<int>(p.length()+1,-1));
        return helper(0,s,0,p,dp);
    }
    bool helper(int i , string s , int j , string p,vector<vector<int>>&dp){
        if(i>=s.length() && j>=p.length())    // both the strings are exhausted with matching
            return true;
        if(j>=p.length())       // we have exhausted pattern but havent come up with complete match of s
            return false;
        if(i<s.length()&&dp[i][j]!=-1){
            return dp[i][j];
        }
        bool matched = (i<s.length() && (s[i] == p[j] || p[j] == '.'));  // first chrs match
        bool notTake = false , take = false ;
        if(j+1<p.length() && p[j+1] == '*'){        // if we have preceeding *
            notTake = helper(i,s,j+2,p,dp);
            take = false;
            if(matched){
                take = helper(i+1,s,j,p,dp);
            }
            return dp[i][j]=take || notTake;
        }
        if(matched){                // if we dont have preceeding *
            return dp[i][j]=helper(i+1,s,j+1,p,dp);
        }
        return dp[i][j]=false;
        
    }
};
==========================================
class Solution {
public:
    bool check(string& s, int i, string p, int j,vector<vector<int>>&memo){
        if(memo[i][j]!=-1){
            return memo[i][j];
        }
        if(i>=s.length() && j>=p.length()){
            return memo[i][j]=true;
        }
        if(i>=s.length()&&j<p.length()&&p[j]=='*'){
            return memo[i][j]=check(s,i,p,j+1,memo);
        }
        if(i==s.length() || j==p.length()){
            return memo[i][j]=false;
        }
        if(p[j]=='*'){
            return memo[i][j]=check(s,i+1,p,j,memo) || check(s,i,p,j+1,memo);
        }
        if(s[i]==p[j]){
            return memo[i][j]=check(s,i+1,p,j+1,memo);
        }
        if(p[j]=='?'){
            return memo[i][j]=check(s,i+1,p,j+1,memo);
        }
        
        return memo[i][j]=false;
        
    }
    bool isMatch(string s, string p) {
        vector<vector<int>>memo(s.length()+1,vector<int>(p.length()+1,-1));
        return check(s,0,p,0,memo);
    }
};