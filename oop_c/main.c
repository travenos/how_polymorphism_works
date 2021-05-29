#include <stdio.h>
#include <stdlib.h>

static const int DESTRUCT_POS = 0;
static const int PRINT_X_POS = 1;
static const int PRINT_Y_POS = 2;

typedef void(*FuncPtr)(void);

typedef struct A
{
    FuncPtr* m_vtable;
    int m_x;
    int m_y;
} A;

_Noreturn void pureVirtualFunctionHandler()
{
    fprintf(stderr, "Pure virtual function call\n");
    fflush(stderr);
    abort();
}

void destruct(A* this)
{
    void (*destructor)(A*) = (void (*)(A*))this->m_vtable[DESTRUCT_POS];
    (*destructor)(this);
}

void printX(const A* this)
{
    void (*printXFunc)(const A*) = (void (*)(const A*))this->m_vtable[PRINT_X_POS];
    (*printXFunc)(this);
}

void printY(const A* this)
{
    void (*printYFunc)(const A*) = (void (*)(const A*))this->m_vtable[PRINT_Y_POS];
    (*printYFunc)(this);
}

//____________________________________________
void constructA(A* this, int x, int y);
void destructA(A* this);

FuncPtr VTABLE_A[] = {(FuncPtr)&destructA,
                      (FuncPtr)&pureVirtualFunctionHandler,
                      (FuncPtr)&pureVirtualFunctionHandler};

void constructA(A* this, int x, int y)
{
    this->m_vtable = VTABLE_A;
    this->m_x = x;
    this->m_y = y;
    printf("A constructor: x = %d y = %d\n", this->m_x, this->m_y);
    fflush(stdout);
}

void destructA(A* this)
{
    printf("A destructor: x = %d y = %d\n", this->m_x, this->m_y);
    fflush(stdout);
}

//____________________________________________
void constructB(A* this);
void destructB(A* this);
void printXB(const A* this);
void printYB(const A* this);

FuncPtr VTABLE_B[] = {(FuncPtr)&destructB,
                      (FuncPtr)&printXB,
                      (FuncPtr)&printYB};

void constructB(A* this)
{
    constructA(this, 1, 2);
    this->m_vtable = VTABLE_B;
    printf("B constructor\n");
    fflush(stdout);
}

void destructB(A* this)
{
    printf("B destructor\n");
    fflush(stdout);
    this->m_vtable = VTABLE_A;
    destructA(this);
}

void printXB(const A* this)
{
    printf("Print x from B: %d\n", this->m_x);
    fflush(stdout);
}

void printYB(const A* this)
{
    printf("Print y from B: %d\n", this->m_y);
    fflush(stdout);
}

//____________________________________________
void constructC(A* this);
void destructC(A* this);
void printXC(const A* this);
void printYC(const A* this);

FuncPtr VTABLE_C[] = {(FuncPtr)&destructC,
                      (FuncPtr)&printXC,
                      (FuncPtr)&printYC};

void constructC(A* this)
{
    constructA(this, 3, 4);
    this->m_vtable = VTABLE_C;
    printf("C constructor\n");
    fflush(stdout);
}

void destructC(A* this)
{
    printf("C destructor\n");
    fflush(stdout);
    this->m_vtable = VTABLE_A;
    destructA(this);
}

void printXC(const A* this)
{
    printf("Print x from C: %d\n", this->m_x);
    fflush(stdout);
}

void printYC(const A* this)
{
    printf("Print y from C: %d\n", this->m_y);
    fflush(stdout);
}

int main()
{
    {
        A* pA = malloc(sizeof(A));
        constructB(pA);
        printX(pA);
        printY(pA);
        destruct(pA);
        free(pA);
    }
    {
        A* pA = malloc(sizeof(A));
        constructC(pA);
        printX(pA);
        printY(pA);
        destruct(pA);
        free(pA);
    }
    return 0;
}
