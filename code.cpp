#include <bits/stdc++.h> 
#include <string>
#include <iostream>

using namespace std; 
double value1,value2;

template <class T>
class vectorClass { 
    T* arr; 
    int current;
  
public: 
    vectorClass() 
    { 
        arr = new T[1]; 
        current = 0; 
    } 
  
    void push(T data) 
    { 
        arr[current] = data; 
        current++; 
    } 
  
    void pop() 
    { 
        current--; 
    } 
  
    int size() 
    { 
        return current; 
    } 
    
    T top()
    {
    	return arr[current-1];
    }
    
    bool isEmpty()
    {
    	if(current==0)
    	return true;
    	else return false;
    }
};
int precedence(char op){ 
    if(op == '+'||op == '-') 
    return 1; 
    if(op == '*'||op == '/' ||op=='%') 
    return 2; 
    return 0; 
} 

double applyOp(double a, double b, char op){ 
	switch(op){ 
        case '+': return a + b; 
        case '-': return a - b; 
        case '*': return a * b; 
        case '/': {if (b!=0) return a / b;}; 
        case '%': return fmod(a,b);
   }
   return 0;
} 
  
double evaluate(string str){ 
    int i; 
      
    vectorClass<double> values; 
    vectorClass<char> ops; 
      
    for(i = 0; i < str.length(); i++){ 
    
      if(str[i] == '(')
            ops.push(str[i]); 
         
          
     else if(isdigit(str[i]))
     { 
	    int start=i;
            while((i < str.length()) && (isdigit(str[i])||str[i]=='.'))
            i++; 
        int end=i;
	    int string_size=end-start; 
	    string subs=str.substr(start,string_size);
	    double value = stod(subs,NULL);
        values.push(value); 
        i--;
      } 
          
    else if(str[i] == ')') 
        { 
            while(!ops.isEmpty() && ops.top() != '(') 
            { 
                double value2 = values.top();
				values.pop(); 
                double value1 = values.top();
				values.pop(); 
                char op = ops.top();
				ops.pop(); 
			    double ans=applyOp(value1,value2,op);
                values.push(ans); 
            } 
              
            if(!ops.isEmpty()) 
               ops.pop(); 
        } 
          
    else
        { 
            while(!ops.isEmpty() && precedence(ops.top()) >= precedence(str[i]))
			{ 
                value2 = values.top();
				values.pop(); 
                value1 = values.top();
				values.pop(); 
                char op = ops.top();
				ops.pop() ;
                values.push(applyOp(value1,value2,op)); 
            } 
              
            ops.push(str[i]); 
        } 
    } 
      
    while(!ops.isEmpty()){ 
       value2 = values.top();
       values.pop();
       value1 = values.top();
       values.pop();
       char op = ops.top();
       ops.pop();
       values.push(applyOp(value1,value2,op)); 
       } 
      
return values.top(); 
} 
  
int main() { 

string s;
cin>>s;
double ans=evaluate(s);
cout<<fixed<<setprecision(5)<<ans<<endl;
return 0; 
}