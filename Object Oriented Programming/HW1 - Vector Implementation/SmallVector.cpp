//Name: Onat ŞAHİN  No:150150129
#include "SmallVector.h"
#include <cstring>
#include <iostream>
#include <cstdlib>

using namespace std;

SmallVector::SmallVector(){
    staticSize = 0;
    dynamicSize = 0;
    tempSize = 0;
    dynamicBuffer = NULL;
    tempBuffer = NULL;
    capacity = STATIC_CAP;
    dyncapacity = 0;
}

SmallVector::SmallVector(int arr[], int arrsize){
    staticSize = 0;
    dynamicSize = 0;
    dynamicBuffer = NULL;
    tempBuffer = NULL;
    capacity = STATIC_CAP;
    dyncapacity = 0;

    if(arrsize <= STATIC_CAP){
        memcpy(staticBuffer, arr, arrsize * intsz);
        staticSize = arrsize;
    }
    else if(arrsize > STATIC_CAP){
        memcpy(staticBuffer, arr, STATIC_CAP * intsz);
        staticSize = STATIC_CAP;
        extendCap(arrsize - staticSize);

        for(int i=0; i<dyncapacity; i++){
            dynamicBuffer[i] = arr[i+STATIC_CAP];
            dynamicSize++;
        }
    }

}

SmallVector::SmallVector(const SmallVector& objectIn){
    staticSize = objectIn.staticSize;
    dynamicSize = objectIn.dynamicSize;
    dyncapacity = objectIn.dyncapacity;
    capacity = objectIn.capacity;
    tempBuffer = NULL;

    memcpy(staticBuffer, objectIn.staticBuffer, STATIC_CAP * intsz);

    if(objectIn.dynamicBuffer){
        dynamicBuffer = new int[objectIn.dynamicSize];
        memcpy(dynamicBuffer, objectIn.dynamicBuffer, dynamicSize * intsz);
    }
    else{
        dynamicBuffer = NULL;
    }
}

SmallVector::~SmallVector(){
    if(dynamicBuffer)
        delete[] dynamicBuffer;
}

SmallVector& SmallVector::operator=(const SmallVector& toCopy){
    if(dynamicBuffer)
        delete[] dynamicBuffer;

    staticSize = toCopy.staticSize;
    dynamicSize = toCopy.dynamicSize;
    capacity = toCopy.capacity;
    dyncapacity = toCopy.dyncapacity;

    memcpy(staticBuffer, toCopy.staticBuffer, staticSize * intsz);

    if(dyncapacity != 0){
        dynamicBuffer = new int[dyncapacity];
        memcpy(dynamicBuffer, toCopy.dynamicBuffer, dynamicSize * intsz);
    }

    return *this;
}

int& SmallVector::operator[](int index){
    if(index >= 0){
        if(index > getSize() - 1){
            if(dynamicBuffer)
                return dynamicBuffer[dynamicSize-1];
            else
                return staticBuffer[staticSize - 1];
        }

        else if(index > STATIC_CAP - 1)
            return dynamicBuffer[index - STATIC_CAP];

        else
            return staticBuffer[index];

    }
    else{
        if(abs(index) > getSize() - 1)
            return staticBuffer[0];

        else if(index + getSize() > STATIC_CAP - 1)
            return dynamicBuffer[index + getSize() - STATIC_CAP];

        else if(index + getSize() <= STATIC_CAP - 1)
            return staticBuffer[index + getSize()];
    }

}

const int& SmallVector::operator[](int index) const {
    if(index >= 0){
        if(index > getSize() - 1){
            if(dynamicBuffer)
                return dynamicBuffer[dynamicSize-1];
            else
                return staticBuffer[staticSize - 1];
        }

        else if(index > STATIC_CAP - 1)
            return dynamicBuffer[index - STATIC_CAP];

        else
            return staticBuffer[index];

    }
    else{
        if(abs(index) > getSize() - 1)
            return staticBuffer[0];

        else if(index + getSize() > STATIC_CAP - 1)
            return dynamicBuffer[index + getSize() - STATIC_CAP];

        else if(index + getSize() <= STATIC_CAP - 1)
            return staticBuffer[index + getSize()];
    }

}

SmallVector SmallVector::operator+(const SmallVector& toadd) const{
    int size1 = this->getSize();
    int size2 = toadd.getSize();
    int tsize = size1 + size2;
    int *temp = new int[tsize];

    for(int i=0; i<size1; i++){
        temp[i] = (*this)[i];
    }
    for(int i=0; i<size2; i++){
        temp[i+size1] = toadd[i];
    }

    SmallVector sum(temp, tsize);
    delete[] temp;
    return sum;
}

SmallVector SmallVector::operator*(const int operand) const{
    int initsize = this->getSize();
    int tsize = initsize * operand;
    int *temp = new int[tsize];

    for(int i=0; i<tsize; i++){
        temp[i] = (*this)[i % initsize];
    }

    SmallVector result(temp,tsize);
    delete[] temp;
    return result;
}

void SmallVector::extendCap(int ext){  //This private function takes an integer as an argument and extends the dynamic buffer according to that
    if(dynamicBuffer){
        tempBuffer = new int[dynamicSize];                     //a temporary buffer is created
        tempSize = dynamicSize;
        memcpy(tempBuffer, dynamicBuffer, dynamicSize * intsz); //dynamic buffer is copied to temp buffer
        delete[] dynamicBuffer;                                 //dynamic buffer is deleted

        dyncapacity += ext;                                     //dynamic buffer's capacity is increased by the value sent to function as an argument
        dynamicBuffer = new int[dyncapacity];                   //new space is allocated to dynamic buffer
        memcpy(dynamicBuffer, tempBuffer, tempSize * intsz);    //contents of the temp buffer are copied to the new dynamic buffer
        delete[] tempBuffer;                                    //temp buffer is deleted
        capacity = STATIC_CAP + dyncapacity;                    //capacity is updated
    }
    else{
        dynamicBuffer = new int[ext];                           //if a dynamic buffer does not exist, it is created.
        dyncapacity = ext;
        capacity = STATIC_CAP + dyncapacity;
    }

}

void SmallVector::shrinkCap(){ //this private function shrinks the size of the dynamic buffer by 1

    if(dynamicSize == 1){  //If there is only 1 value in the dynamic buffer, the dynamic buffer is deleted
        delete[] dynamicBuffer;
        dynamicBuffer = NULL;
        dynamicSize = 0;
        dyncapacity = 0;
        capacity = STATIC_CAP;
    }
    else{
        tempBuffer = new int[dynamicSize];                      //A temporary buffer is created
        tempSize = dynamicSize;
        memcpy(tempBuffer, dynamicBuffer, dynamicSize * intsz);  //dynamic buffer is copied to temp buffer
        delete[] dynamicBuffer;                                   //dynamic buffer is deleted

        dynamicSize--;                                            //Size and capacity are updated
        dyncapacity--;
        dynamicBuffer = new int[dynamicSize];                     //A new dynamic buffer is created
        memcpy(dynamicBuffer, tempBuffer, tempSize * intsz);      //contents of the temp buffer are copied to the new dynamic buffer
        delete[] tempBuffer;                                       //temp buffer is deleted

        capacity = STATIC_CAP + dyncapacity;                      //capacity is updated
    }

}

void SmallVector::push_back(int toPush){
    if(staticSize < STATIC_CAP){
        staticBuffer[staticSize] = toPush;
        staticSize++;
    }
    else{
        extendCap(1);
        dynamicBuffer[dynamicSize] = toPush;
        dynamicSize++;
        capacity = STATIC_CAP + dyncapacity;
    }
}

void SmallVector::push_back(int arr[], int size){
    if(staticSize + size <= STATIC_CAP){
        for(int i=0; i<size; i++){
            staticBuffer[staticSize] = arr[i];
            staticSize++;
        }
    }
    else if(staticSize == STATIC_CAP){
        extendCap(size);
        for(int i=0; i<size; i++){
            dynamicBuffer[dynamicSize] = arr[i];
            dynamicSize++;
        }
    }
    else{
        int i=0;
        for(i=0; staticSize != STATIC_CAP; i++){
            staticBuffer[staticSize] = arr[i];
            staticSize++;
        }
        extendCap(size-i);

        while(i<size){
            dynamicBuffer[dynamicSize] = arr[i];
            dynamicSize++;
            i++;
        }
    }
}
int SmallVector::pop_back(){
    int popped;

    if(dynamicBuffer){
        popped = dynamicBuffer[dynamicSize-1];
        shrinkCap();
    }
    else{
        popped = staticBuffer[staticSize-1];
        staticSize--;
    }
    return popped;
}

SmallVector SmallVector::reverse(){
    int size = getSize();
    int *temp = new int[size];
    int j=0;

    for(int i = size-1; i>=0; i--,j++){
        temp[j] = (*this)[i];
    }

    SmallVector reversed(temp, size);
    delete[] temp;
    return reversed;
}
