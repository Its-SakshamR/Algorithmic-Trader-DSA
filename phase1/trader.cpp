#include "receiver.h"
#include <vector>
#include <string>
using namespace std;

int check_string(string f, vector<pair<string,vector<int>>> stocks){
    for(int i=0; i<stocks.size(); i++){
        if(f == stocks[i].first){return i;}
    }
    return -1;
}

vector<pair<string,vector<int>>> sum_stocks(vector<pair<string,vector<int>>>stocks1 ,int m ,int n){
    for(int i=0; i<stocks1.size();i++){
        stocks1[i].second[m]+=stocks1[i].second[n];
    }
    return stocks1;
}

vector<int> check_sum(vector<pair<string,vector<int>>>stocks1, vector<int>stk_price1, int last, vector<int>collection){
    collection.push_back(last);
    if(last==0){
        for(int i=0; i<stocks1.size(); i++){
            if(stocks1[i].second[0]!=0){
                //cout<<"check_sum_0";
                return{};}
        }
        collection.push_back(stk_price1[0]);
        //cout<<"check_sum_1";
        return collection;
    }

    int x=0;
    for(int i=0; i<stocks1.size(); i++){
            if(stocks1[i].second[last]!=0){x=1;}
        }
    if(x==0){collection.push_back(stk_price1[last]);
        //cout<<"check_sum_2";
        return collection;}

    vector<int>stk_price,collection1,collection2={};
    for(int i=last-1; i>=0; i--){
        stk_price=stk_price1;
        collection1=collection;
        stk_price[i]+=stk_price[last];
        collection1=check_sum(sum_stocks(stocks1,i,last),stk_price,i,collection);
        if(!collection1.empty()){
            if(collection2.empty()||collection1.back()>collection2.back()){
            collection2= check_sum(sum_stocks(stocks1,i,last),stk_price,i,collection);}
        }
    }
    //cout<<"check_sum_3";
    return collection2;
}

vector<int> arbitrage(vector<pair<string,vector<int>>>stocks1, vector<int>stk_price1, int last, vector<int>collection){
    return check_sum(stocks1,stk_price1,last,collection);
}

int check_string(string f, vector<string> stocks){
    int n=stocks.size();
    for(int i=0; i<n; i++){
        if(f == stocks[i]){return i;}
    }
    return -1;
}

void part_1(string message){
    string message_copy = message;

        vector<string> Inputs;          // To save the message into different strings that are accumulated in a vector
        int pos1 = 0;
        int pos2 = message_copy.find('#');
        while(true){
            if(pos2 == -1){
                break;
            }
            Inputs.push_back(message_copy.substr(pos1, pos2+1-pos1));
            pos1 = pos2 + 2;
            pos2 = message_copy.find('#',pos1);
        }
        //cout<<"pikachu"<<endl;

        vector<string> Stocks;
        vector<int> curr_pr;                // These 2 vectors will help in remembering the latest price;
        vector<string> Outputs;             // To save outputs

        int pos3;
        string curr_in;
        while(!Inputs.empty()){
            curr_in = Inputs[0];

            pos1 = curr_in.find(' ');
            pos2 = curr_in.find(' ',pos1+1);
            pos3 = curr_in.find('#');

            string stock_name = curr_in.substr(0,pos1);
            int stock_price = stoi(curr_in.substr(pos1+1, pos2));

            bool found = false;
            int n = 0;

            for (const std::string& element : Stocks) {
                if (element == stock_name) {
                    found = true;
                    break;
                }
                n++;
            }

            if(!found){
                Stocks.push_back(stock_name);
                curr_pr.push_back(stock_price);
                if(curr_in[pos3-1] == 's') curr_in[pos3-1] = 'b';
                else curr_in[pos3-1] = 's';
                Outputs.push_back(curr_in.substr(0,curr_in.length()-1));
            }

            else{
                if(curr_in[pos3-1] == 's'){
                    if(stock_price < curr_pr[n]){
                        curr_in[pos3-1] = 'b';
                        curr_pr[n] = stock_price;
                        Outputs.push_back(curr_in.substr(0,curr_in.length()-1));
                    }
                    else{
                        Outputs.push_back("No Trade");
                    }
                }

                else{
                    if(stock_price > curr_pr[n]){
                        curr_in[pos3-1] = 's';
                        curr_pr[n] = stock_price;
                        Outputs.push_back(curr_in.substr(0,curr_in.length()-1));
                    }
                    else{
                        Outputs.push_back("No Trade");
                    }
                }
            }

            Inputs.erase(Inputs.begin());
        }

        while(!Outputs.empty()){
            cout<<Outputs[0]<<endl;
            Outputs.erase(Outputs.begin());
        }
}


void part_2(string message){
    string message_copy = message;

        vector<string> Inputs;          // To save the message into different strings that are accumulated in a vector
        int k = 0 , pos1 = 0;
        int pos2 = message_copy.find('#');
        while(true){
            if(pos2 == -1){
                break;
            }
            Inputs.push_back(message_copy.substr(pos1, pos2+1-pos1));
            k++;
            pos1 = pos2 + 2;
            pos2 = message_copy.find('#',pos1);
        }

        // vector<string> Stocks;
        // vector<int> curr_pr;                // These 2 vectors will help in remembering the latest price;
        // vector<string> Outputs;             // To save outputs

        string curr_in;
        vector<vector<pair<string,int>>>stock_name;
        vector<pair<string,vector<int>>>stocks;
        vector<int> stk_price;
        vector<int> buysell;
        vector<pair<string,int>>n;
        string s;
        char a;
        int x;
        for(int i=0; i<k; i++){
            curr_in = Inputs[i];
            n.clear();

            pos1=curr_in.find('#');
            a=curr_in[pos1-1];
            x = 1;
            if (a == 's')x=-1;
            buysell.push_back(x);
            pos2 =0;
            pos1=curr_in.find(' ');

            while(curr_in.find(' ',pos1+1) != -1)   //checking if space after stock value
            {
            s = curr_in.substr(pos2,pos1-pos2);     //pos2 stores position of space before stock name + 1 and pos1 after stock name

            if(check_string(s,stocks) == -1){
                vector<int> b;
                for(int j=0;j<=stock_name.size();j++){
                    b.push_back(0);
                }
                stocks.push_back(make_pair(s,b));}               //stocks will contain all the different stocks

            pos2 = curr_in.find(' ',pos1+1)+1;
            int y = x*stoi(curr_in.substr(pos1+1, pos2-pos1-1));
            n.push_back(make_pair(s,y));
            pos1 = curr_in.find(' ',pos2+1);
            }
            stock_name.push_back(n);
            stk_price.push_back(x*stoi(curr_in.substr(pos2, pos1-pos2)));

            //stocks stores the value of a stock in subsequent lines

            for(int m=0; m<stocks.size(); m++){
                stocks[m].second.push_back(0);
            for(int j=0; j<stock_name[i].size(); j++){
                if(stock_name[i][j].first==stocks[m].first){
                stocks[m].second[i]=stock_name[i][j].second;}
                }
            }
        }

        int last=0;                                               //i-number of no trades for each iteration
        vector<pair<string,vector<int>>>stocks1;
        vector<int>stk_price1;
        vector<int>collection;
        for(int i=0; i<k; i++){
            stocks1=stocks;
            stk_price1=stk_price;
            collection.clear();
            collection=arbitrage(stocks1,stk_price1,last,collection);
            if(collection.empty()){
                cout<<"No Trade"<<endl;
                last++;
                continue;
            }
            for(int m=0;m<collection.size()-1;m++){
                for(int j=0;j<stocks.size();j++){                      //clear part
                    stocks[j].second.erase(stocks[j].second.begin()+collection[m]);
                }                                                      //clear part
                for(int j=0;j<stock_name[collection[m]].size();j++){
                    cout<<stock_name[collection[m]][j].first<<" ";
                    cout<<buysell[collection[m]]*stock_name[collection[m]][j].second<<" ";
                }
                cout<<stk_price[collection[m]]<<" ";
                if(buysell[collection[m]]==1){cout<<"s"<<'#'<<endl;}
                else{cout<<"b"<<'#'<<endl;}
                stock_name[collection[m]].clear();                                   //clear part
                stock_name.erase(stock_name.begin()+collection[m]);
                stk_price.erase(stk_price.begin()+collection[m]);
                buysell.erase(buysell.begin()+collection[m]);            //clear part
            }
            cout<<collection.back()<<endl;
            last=last-collection.size()+2;
            }
        // for(int i=0;i< stocks.size();i++){
        // cout<<stocks[i].first<<endl;
        // for(int m=0; m<stocks.size(); m++){
        //     cout<<stocks[i].second[m]<<endl;}
    //}
}

int main(int argc, char* argv[]) {

    Receiver rcv;
    sleep(5);
    string message = rcv.readIML();
    string message_copy = message;


    if(strcmp(argv[1],"1") == 0){
        part_1(message);
    }
    if(strcmp(argv[1],"2")==0){
        part_2(message);
    }
    return 0;
}