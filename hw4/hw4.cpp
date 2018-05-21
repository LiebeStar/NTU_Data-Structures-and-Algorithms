

#include <iostream>
#include <cstdio>
#include <string>
#include <unordered_map>
#include <algorithm>

using namespace std;

long long int x = 257, M = 1000000007, LENGTH = 10000;

int main()
{
    string str;
    cin >> str;
    
    int query_num, query;
    scanf("%d", &query_num);
    
    char ch;
    unordered_map<long long int, long long int> substring;
    
    long long int hashValue = 0;
    for(int i=0; i<str.length(); i++){
        hashValue = str[i]-'a'+1;
        substring[hashValue]++;
        
        for(int j=i+1; j<str.length(); j++){
            hashValue = (hashValue*x + (str[j]-'a'+1)) % M;
            substring[hashValue]++;
        }
    }
    
    for (int i=0; i<query_num; i++) {
        scanf("%d", &query);
        
        if(query==1)
        {
            scanf(" %c", &ch);
            
            reverse(str.begin(), str.end());
            str+=ch;
            reverse(str.begin(), str.end());
            
            for(int j=0; j<str.length(); j++){
                if(j==0) hashValue = str[j]-'a'+1;
                else hashValue = (hashValue*x + (str[j]-'a'+1)) % M;
                substring[hashValue]++;
            }
        }
        else if(query==2)
        {
            scanf(" %c", &ch);
            str+=ch;
            
            for(int j=0; j<str.length(); j++){
                hashValue = str[j]-'a'+1;
                for(int k=j+1; k<str.length(); k++){
                    hashValue = (hashValue*x + (str[k]-'a'+1)) % M;
                }
                substring[hashValue]++;
            }
        }
        else
        {
            string tmp;
            cin >> tmp;
            
            if(tmp.length()<LENGTH){
                for(int j=0; j<tmp.length(); j++){
                    if(j==0) hashValue = tmp[j]-'a'+1;
                    else hashValue = (hashValue*x + (tmp[j]-'a'+1)) % M;
                }

                cout << substring[hashValue] << endl;
            }
            else{
                long long int times=0;
                for(int j=0; j<str.length()-tmp.length()+1; j++){
                    string s;
                    for(int k=0; k<tmp.length(); k++){
                        s+=str[j+k];
                    }
                    if(tmp==s) times++;
//                    cout << "tmp:" << tmp << " s:" << s << endl;
                }
                cout << times << endl;
            }
        }
//        cout << "str:" << str << endl;
    }
    return 0;
}










