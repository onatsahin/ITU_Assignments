#include <iostream>
#include <cstring>
#include <cstdio>
#include "stack.h"
#include <stdlib.h>
using namespace std;

Stack s;
int main(){
  s.create();
  char infix[100];
  cout << "Enter the operation in infix format"<<endl;
  cin.getline(infix,100);
  char postfix[100];
  int postindex=0;

  for(int i = 0 ; infix[i] != '\0'; i++ ){
    if( '0' <= infix[i] && infix[i] <= '9' ){//Hi I'm operand.
        postfix[postindex] = infix[i];
        postindex++;
    }
    else{
        if(s.isempty() || infix[i] == '('){
            s.push(infix[i]);
        }
        else if(!s.isempty() && infix[i] != ')'){

            if( !s.isempty() && (infix[i] == '+' || infix[i] == '-') && (s.head->data == '*' || s.head->data == '/' ) ){
                while( !s.isempty() && (infix[i] == '+' || infix[i] == '-') && (s.head->data == '*' || s.head->data == '/' ) ){
                    postfix[postindex] = s.pop();
                    postindex++;
                    s.push(infix[i]);
                }
            }

            else{
                s.push(infix[i]);
            }

        }
        else if(infix[i] == ')'){
            while(s.head->data != '('){
                postfix[postindex] = s.pop();
                postindex++;
            }
            s.pop();
        }
    }
  }
  while(!s.isempty()){
      postfix[postindex] = s.pop();
      postindex++;
  }
  for(int i = 0; i<postindex ; i++){
      cout << postfix[i];
  }
  cout << endl;
  s.close();
  s.create();
  int first,second;
  int sum;
  char a;


  for(int j = 0 ;j < postindex ; j++ ){
      if('0' <= postfix[j] && postfix[j] <= '9' ){
          s.push(postfix[j]);
    }
      else{

          first = s.pop()-'0';
          second = s.pop()-'0';

          if(postfix[j] == '+'){
              sum = first + second;
          }
          if(postfix[j] == '-'){
              sum = second - first;
          }
          if(postfix[j] == '*'){
              sum  = first * second;
          }
          if(postfix[j] == '/'){
              sum = second / first;
          }
          a = sum + '0';
         s.push(a);
      }
  }
  cout << s.pop()<<endl;
  s.close();

  return 0;
}
