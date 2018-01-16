/*@Author
 * Student Name: Onat ŞAHİN
 * Student ID: sahino15
 * Student No: 150150129
 * Date : 24.12.2016
*/

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <cmath>
#include <cstdio>
#include <fstream>
#include "data.h"

using namespace std;

bool isOperator(char* str);
bool isNumber(char* str);

int main(int argc, char** argv){
    char ex[101]={0}, postfix[30][20]={0}, prefix[30][20]={0}, resultstr[20], toans[20], infcheck[20], infcheck2[20];
    int i,j,k,index,parcount,postindex=0, pinf, pninf;
    int arglims[10], argindex=0, argtrav=0;
    bool found, inf, ninf, error;
    bool file = false;
    long int second, first, result, temp;
    double log1, log2;
    ifstream inputfile;

    Stack s;
    s.create();

    Queue q;
    q.create();


    if(argc == 2){ //Checking if opened in batch mode and getting input
        //cout << argv[1];
        inputfile.open(argv[1], ios::in);
        inputfile.getline(ex, 100);

        for(int i=0; i<101; i++){
            if(ex[i] == '\r')
                ex[i] = '\0';
        }
        file = true;
    }

    else{ // Console mode input
        cout << ">> ";
        cin.getline(ex,100);
    }

    while( strcmp(ex, "exit") != 0 ){ //Splitting the expression
        error = false;
        for(i=0, j=0, k=0; ex[i]!='\0'; i++){

            if(ex[i] == ' '){
                j++;
                k=0;
            }
            else{
                prefix[j][k] = ex[i];
                k++;
            }
        }

        if(isNumber(prefix[0])){ //Some syntax error checks
            cout << "Syntax Error: Prefix exp must start with an operation" << endl;
            error = true;

        }

        if(!error){
            for(int i=0; prefix[i][0] != '\0'; i++){
                if(strcmp(prefix[i], "ans") == 0){
                    if(q.isempty()){
                        cout << "Syntax Error: ans used in first expression" << endl;
                        error = true;
                        break;
                    }
                    else
                        strcpy(prefix[i], q.lookback());
                }
            }
        }

        if(error){ // Geting new input if there is a syntax error

            for(int i=0; i<30; i++){
                for(int j=0; j<10; j++){
                    prefix[i][j] = '\0';
                }
            }

            if(file){

                if(!inputfile.eof()){
                    inputfile.getline(ex, 100);

                    for(int i=0; i<101; i++){
                        if(ex[i] == '\r')
                        ex[i] = '\0';
                    }
                }
                else break;
            }
            else{
                cout << endl << ">> ";
                cin.getline(ex,100);
                continue;
            }
        }


        for(int i=0; i<50 && prefix[i][0] != '\0'; i++){ //Postfix conversion. I assumed that if the user wants an operation inside
            parcount = 0;                                //another operation, they enter it using parantheses.
            if(isOperator(prefix[i])){
                s.push(prefix[i]);
                s.head->arglim = 0;

                if( strcmp(prefix[i], "sqrt")==0 || strcmp(prefix[i], "abs" )==0)
                    s.head->arglim = 1;

                else if( strcmp(prefix[i], "sub")==0 || strcmp(prefix[i], "div" )==0)
                    s.head->arglim = 2;

                else{
                    found = false;
                    index = i+1;
                    while(!found){
                        if(index == 50 || prefix[index][0] == '\0')
                            break;
                        if( isNumber(prefix[index]) ){
                            if(parcount == 0)
                                s.head->arglim++;
                        }

                        else if( prefix[index][0] == '(' )
                            parcount++;

                        else if( prefix[index][0] == ')' ){
                            if(parcount == 0){
                                found = true;
                            }
                            else{
                                parcount--;
                                if(parcount == 0)
                                    s.head->arglim++;
                            }

                        }

                        index++;
                    }

                }

            }

            else if( prefix[i][0] == ')' ){
                if(s.head){

                    s.head->arg++;

                    if(s.head->arg == s.head->arglim){
                        arglims[argindex] = s.head->arglim;
                        argindex++;
                        strcpy( postfix[postindex], s.pop() );
                        postindex++;
                    }
                }
                else{ // Empty stack means syntax error(User entered more operands than the operation takes)
                    cout << "Syntax Error" << endl;
                    error = true;
                    break;
                }
            }

            else if( isNumber(prefix[i]) ){
                strcpy( postfix[postindex], prefix[i] );
                postindex++;

                if(s.head){
                    s.head->arg++;

                    if(s.head->arg == s.head->arglim){
                        arglims[argindex] = s.head->arglim;
                        argindex++;
                        strcpy( postfix[postindex], s.pop() );
                        postindex++;
                    }
                }
                else{
                    cout << "Syntax Error" << endl;
                    error = true;
                    break;
                }
            }

        }

        if(error){ // Getting new input if error
            for(int i=0; i<30; i++){
                for(int j=0; j<10; j++){
                    prefix[i][j] = '\0';
                    postfix[i][j] = '\0';
                }
            }

            if(file){

                if(!inputfile.eof()){
                    inputfile.getline(ex, 100);

                    for(int i=0; i<101; i++){
                        if(ex[i] == '\r')
                        ex[i] = '\0';
                    }
                }
                else break;
            }

            else{
                cout << endl << ">> ";
                cin.getline(ex,100);
                continue;
            }
        }


        if(!file){ // Printing the postfix
            cout << "Postfix: ";
            for(int i=0; postfix[i][0] != '\0'; i++){
                cout << postfix[i] << " ";
            }
            cout << endl;
        }


        for(int i=0; postfix[i][0] != '\0'; i++){ // Evaluating the postfix expression
            if(isNumber(postfix[i]))
                s.push(postfix[i]);

            else if(isOperator(postfix[i])){

                inf = false;

                if( strcmp(postfix[i], "sum") == 0 ){
                    ninf = false;
                    result = 0;

                    for(int j=0; j<arglims[argtrav]; j++){

                        strcpy(infcheck, s.pop());

                        if( strcmp(infcheck, "inf") == 0 ){
                            if(ninf){
                                cout << "Error: inf-inf situation" << endl;
                                error = true;
                                break;
                            }
                            else{
                                strcpy(resultstr, "inf");
                                inf = true;
                            }

                        }
                        else if( strcmp(infcheck, "-inf") == 0 ){
                            if(inf){
                                cout << "Error: inf-inf situation" << endl;
                                error = true;
                                break;
                            }
                            else{
                                strcpy(resultstr, "-inf");
                                ninf = true;
                            }

                        }
                        else{
                            if(inf || ninf)
                                continue;
                            else{
                                result += atol(infcheck);
                            }
                        }
                    }

                    if(!inf && !ninf)
                        sprintf(resultstr, "%ld", result);

                    s.push(resultstr);
                    argtrav++;
                }

                else if( strcmp(postfix[i], "product") == 0 ){
                    result = 1;
                    pinf = 0;
                    pninf = 0;

                    for(int j=0; j<arglims[argtrav]; j++){

                        strcpy(infcheck, s.pop());

                        if( strcmp(infcheck, "inf") == 0 ){        
                            pinf++;
                        }
                        else if( strcmp(infcheck, "-inf") == 0 ){
                            pninf++;
                        }
                        else
                            result *= atol(infcheck);
                    }
                    if(pinf == 0 && pninf == 0)
                        sprintf(resultstr, "%ld", result);

                    else {
                        if(result == 0){
                            cout << "Error: 0 times infinity situation" << endl;
                            error = true;
                            break;
                        }
                        else if(pninf % 2 == 0){
                            if(result > 0)
                                strcpy(resultstr, "inf");

                            else if(result < 0)
                                strcpy(resultstr, "-inf");

                            inf = true;
                        }
                        else if(pninf % 2 == 1){
                            if(result > 0){
                                strcpy(resultstr, "-inf");
                                inf = true;
                            }
                            else if(result < 0){
                                strcpy(resultstr, "inf");
                                inf = true;
                            }
                        }
                    }

                    if(!inf)
                        sprintf(resultstr, "%ld", result);

                    s.push(resultstr);
                    argtrav++;

                }

                else if( strcmp(postfix[i], "min") == 0 ){

                    do{
                        strcpy(infcheck, s.pop());
                    }while(strcmp(infcheck, "inf") == 0);

                    if(strcmp(infcheck, "-inf") == 0){
                        strcpy(resultstr, "-inf");
                        inf = true;
                    }

                    else
                        result = atol(infcheck);

                    if(!inf){
                        for(int j=0; j<arglims[argtrav]-1; j++){

                            strcpy(infcheck, s.pop());

                            if(strcmp(infcheck, "-inf") == 0){
                                strcpy(resultstr, "-inf");
                                inf = true;
                                break;
                            }
                            else if(strcmp(infcheck, "inf") == 0)
                                continue;
                            else{
                                temp = atol(infcheck);

                                if( temp < result )
                                    result = temp;
                            }

                        }

                    }

                    if(!inf)
                        sprintf(resultstr, "%ld", result);

                    s.push(resultstr);
                    argtrav++;
                }

                else if( strcmp(postfix[i], "max") == 0 ){

                    do{
                        strcpy(infcheck, s.pop());
                    }while(strcmp(infcheck, "-inf") == 0);

                    if(strcmp(infcheck, "inf") == 0){
                        strcpy(resultstr, "inf");
                        inf = true;
                    }

                    else
                        result = atol(infcheck);

                    if(!inf){
                        for(int j=0; j<arglims[argtrav]-1; j++){

                            strcpy(infcheck, s.pop());

                            if(strcmp(infcheck, "inf") == 0){
                                strcpy(resultstr, "inf");
                                inf = true;
                                break;
                            }
                            else if(strcmp(infcheck, "-inf") == 0)
                                continue;
                            else{
                                temp = atol(infcheck);

                                if( temp > result )
                                    result = temp;
                            }

                        }

                    }
                    if(!inf)
                        sprintf(resultstr, "%ld", result);

                    s.push(resultstr);
                    argtrav++;
                }

                else if( strcmp(postfix[i], "exp")==0 ){

                    result = 0;

                    if(arglims[argtrav] == 1){

                        strcpy(infcheck, s.pop());
                        if(strcmp(infcheck, "inf") == 0){
                            strcpy(resultstr, "inf");
                            inf = true;
                        }
                        else if(strcmp(infcheck, "-inf") == 0){
                            result = 0;
                        }
                        else
                            result = (long int) floor( pow( 2.71, (double) atol( infcheck ) ) );
                    }

                    else if(arglims[argtrav] == 2){

                        strcpy(infcheck2, s.pop());
                        strcpy(infcheck, s.pop());

                        if(strcmp(infcheck, "inf")==0){
                            if(strcmp(infcheck2, "inf")==0 || strcmp(infcheck2, "-inf")==0){
                                cout << "Error: inf^inf situation" << endl;
                                error = true;
                                break;
                            }
                            else if(atol(infcheck2) == 0){
                                cout << "Error: inf^0 situation" << endl;
                                error = true;
                                break;
                            }

                            else{
                                strcpy(resultstr, "inf");
                                inf = true;
                            }
                        }

                        else if(strcmp(infcheck, "-inf")==0){
                            if(strcmp(infcheck2, "inf")==0 || strcmp(infcheck2, "-inf")==0){
                                cout << "Error: inf^inf situation" << endl;
                                error = true;
                                break;
                            }
                            else if(atol(infcheck2) == 0){
                                cout << "Error: inf^0 situation" << endl;
                                error = true;
                                break;
                            }
                            else if(atol(infcheck2) % 2 == 0){
                                strcpy(resultstr, "inf");
                                inf = true;
                            }
                            else if(atol(infcheck2) % 2 == 1){
                                strcpy(resultstr, "-inf");
                                inf = true;
                            }
                        }

                        else if(strcmp(infcheck2, "inf")==0 || strcmp(infcheck2, "-inf")==0){
                            if(atol(infcheck) == 1 || atol(infcheck) < 0 ){
                                cout << "Error: 1^inf or negative^inf situation" << endl;
                                error = true;
                                break;
                            }
                            else if(atol(infcheck) == 0){
                                if(strcmp(infcheck2, "inf")==0){
                                    result = 0;
                                }
                                else if(strcmp(infcheck2, "-inf")==0){
                                    strcpy(resultstr, "inf");
                                    inf = true;
                                }
                            }
                            else{
                                if(strcmp(infcheck2, "inf")==0){
                                    strcpy(resultstr, "inf");
                                    inf = true;
                                }
                                else if(strcmp(infcheck2, "-inf")==0){
                                    result = 0;
                                }
                            }
                        }
                        else{
                            second = (double) atol( infcheck2 );
                            first = (double) atol( infcheck );
                            result = (long int) pow(first, second);
                        }

                    }
                    if(!inf)
                        sprintf(resultstr, "%ld", result);

                    s.push(resultstr);
                    argtrav++;
                }

                else if( strcmp(postfix[i], "log")==0 ){

                    if(arglims[argtrav] == 1){
                        strcpy(infcheck, s.pop());
                        if( strcmp(infcheck, "inf") == 0){
                            strcpy(resultstr, "inf");
                            inf = true;
                        }
                        else if( atol(infcheck) < 1 || strcmp(infcheck, "-inf") == 0){
                            cout << "Error: Negative operand for log" << endl;
                            error = true;
                            break;
                        }
                        else
                            result = (long int) log( (double) atol(s.pop()) );
                    }

                    else if(arglims[argtrav] == 2){
                        strcpy(infcheck2, s.pop());
                        strcpy(infcheck, s.pop());

                        if( strcmp(infcheck2, "inf") == 0){

                            if(strcmp(infcheck, "inf") == 0 || strcmp(infcheck, "-inf") == 0){
                                cout << "Error: log inf inf situation" << endl;
                                error = true;
                                break;
                            }
                            else{
                                strcpy(resultstr, "inf");
                                inf = true;
                            }
                        }
                        else if( atol(infcheck2) < 1 || strcmp(infcheck2, "-inf") == 0){
                            cout << "Error: Negative operand for log" << endl;
                            error = true;
                            break;
                        }
                        else if(strcmp(infcheck, "inf") == 0 || strcmp(infcheck, "-inf") == 0 || atol(infcheck) <= 1){
                            cout << "Error: Invalid base for log" << endl;
                            error = true;
                            break;
                        }

                        else{
                            log2 = log( (double) atol(infcheck2) );
                            log1 = log( (double) atol(infcheck) );
                            result = (long int) floor(log2 / log1);
                        }
                    }

                    if(!inf)
                        sprintf(resultstr, "%ld", result);

                    s.push(resultstr);
                    argtrav++;
                }

                else if( strcmp(postfix[i], "mod")==0 ){
                    if(arglims[argtrav] == 1){
                        strcpy(infcheck, s.pop());

                        if( strcmp(infcheck, "inf") == 0 || strcmp(infcheck, "-inf") == 0){
                            cout << "Error: inf operand in mod" << endl;
                            error = true;
                            break;
                        }
                        else
                            result = atol(infcheck) % 10;
                    }
                    else if(arglims[argtrav] == 2){
                        strcpy(infcheck2, s.pop());
                        strcpy(infcheck, s.pop());

                        if(strcmp(infcheck, "inf")==0 || strcmp(infcheck, "-inf")==0 || strcmp(infcheck2, "inf")==0 || strcmp(infcheck2, "-inf")==0){
                            cout << "Error: inf operand in mod" << endl;
                            error = true;
                            break;
                        }
                        else if(atol(infcheck) <= 0){
                            cout << "Error: mod of base 0 or negative" << endl;
                            error = true;
                            break;
                        }
                        else{
                            second = atol(infcheck2);
                            first = atol(infcheck);
                            result = second % first;
                        }
                    }
                    if(!inf)
                        sprintf(resultstr, "%ld", result);

                    s.push(resultstr);
                    argtrav++;
                }

                else if( strcmp(postfix[i], "sqrt")==0 ){
                    strcpy(infcheck, s.pop());

                    if(strcmp(infcheck, "inf")==0){
                        strcpy(resultstr, "inf");
                        inf = true;
                    }
                    else if(strcmp(infcheck, "-inf")==0 || atol(infcheck) < 0){
                        cout << "Error: negative inside root" <<  endl;
                        error = true;
                        break;
                    }

                    else
                        result = (long int) floor( sqrt( atol( infcheck ) ) );

                    if(!inf)
                        sprintf(resultstr, "%ld", result);

                    s.push(resultstr);
                    argtrav++;
                }

                else if( strcmp(postfix[i], "abs")==0 ){
                    strcpy(infcheck, s.pop());

                    if(strcmp(infcheck, "inf")==0 || strcmp(infcheck, "-inf")==0){
                        strcpy(resultstr, "inf");
                        inf = true;
                    }

                    else
                        result = labs( atol(infcheck) );

                    if(!inf)
                        sprintf(resultstr, "%ld", result);
                    s.push(resultstr);
                    argtrav++;
                }

                else if( strcmp(postfix[i], "div")==0 ){
                    strcpy(infcheck2, s.pop());
                    strcpy(infcheck, s.pop());

                    if((strcmp(infcheck, "inf")==0 || strcmp(infcheck, "-inf")==0) && (strcmp(infcheck2, "inf")==0 || strcmp(infcheck2, "-inf")==0)){
                        cout << "Error: inf/inf situation" << endl;
                        error = true;
                        break;
                    }
                    else if(strcmp(infcheck2, "inf")==0 || strcmp(infcheck2, "-inf")==0)
                        result = 0;
                    else if(strcmp(infcheck, "inf")==0){
                        strcpy(resultstr, "inf");
                        inf = true;
                    }
                    else if(strcmp(infcheck, "-inf")==0){
                        strcpy(resultstr, "-inf");
                        inf = true;
                    }

                    else{
                        second = atol(infcheck2);
                        first = atol(infcheck);

                        result = floor(first / second);
                    }

                    if(!inf)
                        sprintf(resultstr, "%ld", result);

                    s.push(resultstr);
                    argtrav++;
                }

                else if( strcmp(postfix[i], "sub")==0 ){
                    strcpy(infcheck2, s.pop());
                    strcpy(infcheck, s.pop());

                    if((strcmp(infcheck, "inf")==0 && strcmp(infcheck2, "inf")==0) || (strcmp(infcheck, "-inf")==0 && strcmp(infcheck2, "-inf")==0)){
                        cout << "Error: inf-inf situation" << endl;
                        error = true;
                        break;
                    }
                    else if(strcmp(infcheck, "inf")==0){
                        strcpy(resultstr, "inf");
                        inf = true;
                    }
                    else if(strcmp(infcheck, "-inf")==0){
                        strcpy(resultstr, "-inf");
                        inf = true;
                    }
                    else if(strcmp(infcheck2, "inf")==0){
                        strcpy(resultstr, "-inf");
                        inf = true;
                    }
                    else if(strcmp(infcheck2, "-inf")==0){
                        strcpy(resultstr, "inf");
                        inf = true;
                    }
                    else{
                        second = atol(infcheck2);
                        first = atol(infcheck);

                        result = first - second;
                    }
                    if(!inf)
                        sprintf(resultstr, "%ld", result);

                    s.push(resultstr);
                    argtrav++;
                }
            }
        }

        if(!error){ //If the stack has more than 1 node which is the solution, this means there is a syntax error
            if(s.head->next){
                cout << "Syntax Error" << endl;
                error = true;

                while(!s.isempty())
                    s.pop();
            }
        }

        if(!error){ // Printing the result and adding it to the queue for ans

            if(!file)
                cout << "Result: " << s.head->data << endl;

            strcpy(toans, s.pop());

            q.enqueue(toans);
        }

        for(int i=0; i<30; i++){
            for(int j=0; j<10; j++){
                prefix[i][j] = '\0';
                postfix[i][j] = '\0';
            }
        }

        argindex = 0;
        argtrav = 0;
        postindex = 0;

        if(file){

            if(!inputfile.eof()){
                inputfile.getline(ex, 100);

                for(int i=0; i<101; i++){
                    if(ex[i] == '\r')
                        ex[i] = '\0';
                }
            }
            else break;
        }

        else{
            cout << endl << ">> ";
            cin.getline(ex,100);
        }

    }

    cout << "Answer Queue: ";
    while(!q.isempty()){
        cout << q.dequeue();
        if(!q.isempty())
            cout << " -> ";
    }

    cout << endl;

    s.close();
    q.close();

    return 0;
}

bool isOperator(char* str){
    return !((str[0] >= '0' && str[0] <= '9') || str[0] == '-' || strcmp(str, "ans")==0 || strcmp(str, "inf")==0 || str[0] == ')' || str[0] == '(');
}

bool isNumber(char *str){
    return ((str[0] >= '0' && str[0] <= '9') || str[0] == '-' || strcmp(str, "ans")==0 || strcmp(str, "inf")==0 );
}

