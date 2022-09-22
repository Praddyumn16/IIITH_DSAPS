#include <iostream>
#include <string>
using namespace std;

string add(string a, string b){
    
    if(a.size() > b.size()){
        string temp = b;
        b = a;
        a = temp;
    }

    string res = "";
    int l1 = a.size() , l2 = b.size();
    string temp1 = "" , temp2 = "";

    for(int i = l1 - 1 ; i >= 0 ; i--)
        temp1 += a[i];

    for(int i = l2 - 1 ; i >= 0 ; i--)
        temp2 += b[i];
    
    a = temp1 , b = temp2;
    int carry = 0;

    for(int i = 0 ; i < l1 ; i++){
        int sum = a[i] - '0';
        sum += b[i] - '0';
        sum += carry;
        res.push_back(sum%10 + '0');
        carry = sum/10; 
    }

    for(int i = l1 ; i < l2 ; i++){
        int sum = b[i] - '0';
        sum += carry;
        res.push_back(sum%10 + '0');
        carry = sum/10; 
    }

    if(carry != 0)
        res.push_back(carry + '0');

    string temp = "";
    for(int i = res.size() - 1 ; i >= 0 ; i--)
        temp.push_back(res[i]);
    
    res = temp;
    
    return res;
}


bool check(string a, string b){ // function to check if a is smaller than b or not
    int l1 = a.size() , l2 = b.size();
    if(l1 < l2)
        return true;
    if(l1 > l2)
        return false;
    
    for(int i = 0 ; i < l1 ; i++){
        if(a[i] < b[i])
            return true;
        else if(a[i] > b[i])
            return false;
    }
    return false;
    
}


string subtract(string a, string b){
    
    if(check(a , b)){
        string temp = a;
        a = b;
        b = temp;
    }

    string res = "";
    int l1 = a.size() , l2 = b.size();

    string temp1 = "" , temp2 = "";

    for(int i = l1 - 1 ; i >= 0 ; i--)
        temp1 += a[i];

    for(int i = l2 - 1 ; i >= 0 ; i--)
        temp2 += b[i];
    
    a = temp1 , b = temp2;
    int carry = 0;

    for(int i = 0 ; i < l2 ; i++){
        int curr = (a[i] - '0') - (b[i] - '0') - carry;
        if(curr < 0){
            curr += 10;
            carry = 1;
        }
        else
            carry = 0;
        
        res.push_back(curr + '0');
    }

    for (int i = l2; i < l1; i++) {
        int curr = (a[i] - '0') - carry;
        if (curr < 0) {
            curr += 10;
            carry = 1;
        }
        else
            carry = 0;
        res.push_back(curr + '0');
    }

    string temp = "";
    for(int i = res.size() - 1 ; i >= 0 ; i--)
        temp += res[i];
    
    res = temp;
    res.erase(0 , res.find_first_not_of('0'));

    return res;
}


string multiply_single(string a, int b){

    int arr[a.size() + 1] = {-1};
    int carry = 0;

    for(int i = 0 ; i < a.size() ; i++){
        int curr = ((a[a.size() - 1 - i] - '0') * b) + carry;
        carry = curr/10;
        arr[i] = curr%10;
    }

    arr[a.size()] = carry;

    string res = "";
    for(int i = a.size() ; i >= 0 ; i--)
        res += to_string(arr[i]);
    
    return res;
}


string multiply(string a, string b){
    
    if(check(a , b)){
        string temp = a;
        a = b;
        b = temp;
    }
    int l1 = a.size() , l2 = b.size(); // a is the bigger number
    string temp2 = "";

    for(int i = l2 - 1 ; i >= 0 ; i--)
        temp2 += b[i];
    
    b = temp2;

    string res = "";

    for(int i = 0 ; i < l2 ; i++){
        int x = b[i] - '0';
        string mul = multiply_single(a , x);
        string zero(i , '0');
        mul += zero;
        res = add(res , mul);
    }

    res.erase(0 , res.find_first_not_of('0'));
    return res;

}


string exponent(string a , long long int b){
    
    string res = a;
    
    for(int i = 1 ; i < b ; i++)
        res = multiply(res , a);
    
    res.erase(0 , res.find_first_not_of('0'));
    return res;

}


string factorial(string a){

    string res = a;
    int start = stoi(a) -1;

    for(int i = start ; i >= 2 ; i--){
        if(i > 9)
            res = multiply(res , to_string(i));
        else
            res = multiply_single(res , i);
    }

    res.erase(0 , res.find_first_not_of('0'));
    return res;
}

string modulo(string num2, string num1){ // calculating num2 % num1

    while(check(num1 , num2)){
        
        string temp = "";
        int i = 0;
        while(check(temp , num1))
            temp += num2[i++];
        
        string curr = num1;
        
        for(int j = 2 ; j <= 10 ; j++){
            curr = multiply_single(num1 , j);
            if(!check(curr , temp))
                break;
        }

        string div = "";

        if(curr == temp){
            for(int j = i ; j < num2.size() ; j++)
                div += num2[j];
        }
        else{
            curr = subtract(curr , num1);
            div += subtract(temp , curr);
            for(int j = i ; j < num2.size() ; j++)
                div += num2[j];
        }
        num2 = div;
    }

    return (num2 != "" ? num2 : "0");
}

string gcd(string a, string b){ 
    
    if(b == "0")
        return a;
    if(a == "0")
        return b;
    if(a == b)
        return a;
    
    if(check(a , b))
        return gcd(a , modulo(b , a));
    else
        return gcd(b , modulo(a , b));
}


string evaluate_exp(string exp){
    
    string operand[exp.size()];
    char op[3000];

    int top1 = -1 , top2 = -1;
    string temp = "";

    for(auto a : exp){
        if((a - '0' >= 0) && (a -'0' <= 9))
            temp += a;
        else{
            if(a == '*'){
                if(top2 == -1 || op[top2] != '*'){
                    op[++top2] = '*';
                    operand[++top1] = temp;
                    temp = "";
                }
                else{
                    string curr = multiply(operand[top1] , temp);
                    operand[top1] = curr;
                    temp = "";
                }
            }
            else{
                if(top2 == -1 || op[top2] != '*'){
                    op[++top2] = a;
                    operand[++top1] = temp;
                    temp = "";
                }
                else{
                    string curr = multiply(operand[top1] , temp);
                    operand[top1] = curr;
                    op[top2] = a;
                    temp = "";
                }
            }
        }
    }

    while(top2 != -1){

        if(op[top2] == '*')
            temp = multiply(operand[top1--] , temp);
        else if(op[top2] == '+')
            temp = add(operand[top1--] , temp);
        else    
            temp = subtract(operand[top1--] , temp);
        top2--;
    }

    return temp;
}

int main(){

    cout << "Enter a choice between from 1 to 4" << endl;
    int n;
    cin >> n;
    
    switch(n){
        case 1:
            // addition, subtraction and multiplication
            {
                cout << "Enter the expression" << endl;
                string exp;
                cin >> exp ;
                cout << evaluate_exp(exp) << endl;
            }
            break;
        case 2:
            // exponentiation
            {   
                cout << "Enter number and power" << endl;
                string num;
                long long int power;
                cin >> num >> power;
                cout << exponent(num , power) << endl;
            }
            break;
        case 3:
            // gcd(a , b)
            {
                cout << "Enter two numbers to find their gcd" << endl;
                string a , b;
                cin >> a >> b;
                cout << gcd(a , b) << endl;
            }
            break;
        case 4:
            // factorial
            {   
                cout << "Enter number to take factorial" << endl;
                string num;
                cin >> num;
                cout << factorial(num) << endl;
            }
            break;
        default:
            cout << "Enter a valid choice" << endl;
            break;
    }
    return 0;
}