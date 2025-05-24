// each customer input and handled 1 by 1, can exist anytime
#include<bits/stdc++.h>
using namespace std;

int sales=0, purch=0, loan=0, repay=0, profit=0;
vector<tuple<int,int,double,double>> product; // id, quantity, cp, sp
vector<string> translog;

double getsp(int, vector<tuple<int,int,double,double>>&);
double getcp(int, vector<tuple<int,int,double,double>>&);
int getst(int, vector<tuple<int,int,double,double>>&);
void updst(int, int, vector<tuple<int,int,double,double>>&);
void setup_user();
void pre_setup();
void proc_cust(int);
void printsum();

int main(){\
    char ch;
    cout<<"Do you want to setup products yourself? (y/n): ";
    cin>>ch;
    if(ch=='y'||ch=='Y') setup_user();
    else pre_setup();
    int custid=1;
    while(true){
        cout<<"\nDo you want to enter a new customer? (y/n): ";
        cin>>ch;
        if(ch=='n'||ch=='N') break;
        proc_cust(custid++);
    }
    printsum();
}

double getsp(int pid, vector<tuple<int,int,double,double>> &product){
    for(auto &p : product){
        if(get<0>(p)==pid){
            return get<3>(p);
        }
    }
    return -1;
}

double getcp(int pid, vector<tuple<int,int,double,double>> &product){
    for(auto &p : product){
        if(get<0>(p)==pid){
            return get<2>(p);
        }
    }
    return -1;
}

int getst(int pid, vector<tuple<int,int,double,double>> &product){
    for(auto &p : product){
        if(get<0>(p)==pid){
            return get<1>(p);
        }
    }
    return -1;
}

void updst(int pid, int newb, vector<tuple<int,int,double,double>> &product){
    for(auto &p : product){
        if(get<0>(p)==pid){
            get<1>(p)=newb;
            return;
        }
    }
}

void setup_user(){
    int p,k; 
    double cp,sp;
    cout<<"Enter number of products: ";
    cin>>p;
    for(int i=0;i<p;i++){
        cout<<"Enter quantity of prod "<<i+1<<": ";
        cin>>k;
        cout<<"Enter cost price of prod "<<i+1<<": ";
        cin>>cp;
        cout<<"Enter selling price of prod "<<i+1<<": ";
        cin>>sp;
        product.push_back(make_tuple(i+1,k,cp,sp));
    }
}

void pre_setup() {
    // Preset 10 products: product_id, quantity, cost_price, selling_price
    product.push_back({1, 100, 40.0, 60.0});
    product.push_back({2, 150, 30.0, 50.0});
    product.push_back({3, 200, 25.0, 40.0});
    product.push_back({4, 80,  60.0, 90.0});
    product.push_back({5, 120, 20.0, 35.0});
    product.push_back({6, 90,  55.0, 75.0});
    product.push_back({7, 50,  70.0, 100.0});
    product.push_back({8, 300, 10.0, 20.0});
    product.push_back({9, 110, 45.0, 65.0});
    product.push_back({10, 180, 15.0, 25.0});

    cout << "\n--- Available Products ---\n";
    cout << left << setw(12) << "Product ID"
         << setw(12) << "Quantity"
         << setw(15) << "Price" << "\n";

    for (auto &p : product) {
        cout << left << setw(12) << get<0>(p)
             << setw(12) << get<1>(p)
             << setw(15) << get<3>(p) << "\n";
    }
}


void proc_cust(int id){
    double bud;
    cout<<"Enter budget for customer:";
    cin>>bud;
    int m;
    cout<<"Enter number of queries of customer: ";
    cin>>m;
    vector<tuple<int,int,double>> fquery; // id, quantity, payoff val
    bool anyq=false;
    for(int j=0;j<m;j++){
        int pid,quant;
        double pay;
        cout<<"Enter product id for Query "<<j+1<<" of Customer: ";
        cin>>pid;
        cout<<"Enter quantity corresp to prod for Query "<<j+1<<" of Customer: ";
        cin>>quant;
        cout<<"Enter payoff value for Query "<<j+1<<" of Customer: ";
        cin>>pay;
        double sp= getsp(pid, product);
        if(sp == -1){
            cout << "*************Query " << j+1 << ": Invalid product ID " << pid << ". Query discarded.*************\n";
            continue;
        }
        double cost=sp*quant;
        if(cost > bud){
            cout << "*************Query " << j+1 << ": Cost (" << cost << ") exceeds customer's budget (" << bud << "). Query discarded.*************\n";
            continue;
        }
        if(cost<=bud) {
            fquery.push_back(make_tuple(pid,quant,pay));
            anyq=true;
        }
    }
    if(!anyq){
        cout << "*************No queries fulfilled for Customer " << id << ".*************\n";
        return;
    }
    sort(fquery.begin(),fquery.end(),[&](auto &a, auto &b){
        double ca=getsp(get<0>(a), product) * get<1>(a);
        double cb=getsp(get<0>(b), product) * get<1>(b);
        return (get<2>(a) / ca) > (get<2>(b) / cb);
    });
    double leftb= bud;
    int sal=0;
    bool anys=false;
    for(auto &q: fquery){
        int pid=get<0>(q);
        int quant=get<1>(q);
        double pay=get<2>(q);
        double sp=getsp(pid,product);
        double cp=getcp(pid,product);
        double cost= sp*quant;
        if(cost <= leftb){
            int stock= getst(pid, product);
            if(stock == -1){
                cout << "*************Skipping query for Product " << pid << ": Invalid product ID.*************\n";
                continue;
            }
            if(stock>=quant){
                updst(pid,stock-quant,product);
            }
            else{
                int need=quant-stock;
                double restco= need*cp;
                purch+=restco;
                if(restco<=profit){
                    cout << "*************Restocking " << need << " of Product " << pid << " using available profit (" << profit << ").*************\n";
                    translog.push_back("Restocking through profit of product " + to_string(pid) + ", bought " + to_string(need) + " quantity of Product ");
                    updst(pid,0,product);
                }
                else{
                    double shortf=restco-profit;
                    cout << "*************Restocking " << need << " of Product " << pid << " using loan for shortfall (" << shortf << ").*************\n";
                    translog.push_back("Restocking through loan of product " + to_string(pid) + ", bought " + to_string(need) + " quantity of Product and loan- "+ to_string(shortf));
                    loan+=shortf;
                    repay+=(shortf*1.1);
                    updst(pid,0,product);
                }
            }
            leftb-=cost;
            sales+=cost;
            sal+=(quant*(sp-cp));
            translog.push_back("Customer " + to_string(id) + " bought " + to_string(quant) + " quantity of Product " + to_string(pid));
            anys=true;
            cout << "*************Fulfilling query: Sold " << quant << " of Product " << pid << " from stock.*************\n";
        }
        else{
            cout << "*************Skipping query for Product " << pid << ": Not enough budget left (needed " << cost << ", left " << leftb << ").*************\n";
            continue;
        }
    }
    if(!anys){
        cout << "*************No queries could be fulfilled for Customer " << id << ".*************\n";
    }
    profit+=sal;
}

void printsum(){
    profit-=(repay-loan);
    translog.push_back("Loan taken: " + to_string(loan));
    translog.push_back("Loan repaid with interest: " + to_string(repay));
    cout << "\n--- TRANSACTION LOG ---\n";
    for (string s : translog) cout << s << endl;
    cout << "\n--- SUMMARY ---\n";
    cout << "Total Sales: " << sales << endl;
    cout << "Total Purchase Cost: " << purch << endl;
    cout << "Total Loan Taken: " << loan << endl;
    cout << "Total Repayment (with interest): " << repay << endl;
    if(profit>=0) cout << "Net Profit: " << profit<< endl;
    else cout << "Net Loss: " << -1*profit<< endl;
}
