//Name: Onat ŞAHİN  No:150150129
#ifndef SMALLVECTOR_H
#define SMALLVECTOR_H

#define STATIC_CAP 32 //Macro definitions of values which are used a lot
#define intsz sizeof(int)

class SmallVector{
    private:          //Buffers, size and capacity variables and functions used to extend and shrink dynamic buffer are all private
        int staticBuffer[STATIC_CAP];
        int *dynamicBuffer, *tempBuffer;
        int staticSize, dynamicSize, tempSize, capacity, dyncapacity;
        void extendCap(int);
        void shrinkCap();

    public:
        SmallVector();                                  //Constructor
        SmallVector(int arr[],int);                     //Overloaded constructor with array
        SmallVector(const SmallVector&);
        ~SmallVector();                                 //Destructor
        int& operator[](int);
        const int& operator[](int) const;
        SmallVector& operator=(const SmallVector&);
        SmallVector operator+(const SmallVector&) const;
        SmallVector operator*(const int) const;
        void push_back(int);
        void push_back(int arr[],int);
        int pop_back();
        SmallVector reverse();

        int getSize(){   //getSize() and getCapacity() functions are inline because it improves the performance since these functions are short
             return staticSize + dynamicSize;
        }
        int getSize() const{
            return staticSize + dynamicSize;
        }
        int getCapacity(){
            return STATIC_CAP + dyncapacity;
        }
        int getCapacity() const{
            return STATIC_CAP + dyncapacity;
        }

};



#endif // SMALLVECTOR_H
