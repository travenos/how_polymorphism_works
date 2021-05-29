#include <iostream>
#include <memory>
#include <cassert>

struct A
{
    A(int x, int y) noexcept;

    virtual ~A() noexcept;

    virtual void printX() const noexcept = 0;
    virtual void printY() const noexcept = 0;

    int m_x;
    int m_y;
};

A::A(int x, int y) noexcept:
    m_x{x}
  , m_y{y}
{
    std::cout << "A constructor: " << "x = " << m_x << " y = " << m_y << std::endl;
}

A::~A() noexcept
{
    std::cout << "A destructor: " << "x = " << m_x << " y = " << m_y << std::endl;
}

//____________________________________________
struct B : A
{
    B() noexcept;
    ~B() noexcept override;

    void printX() const noexcept override;
    void printY() const noexcept override;
};

B::B() noexcept :
    A{1, 2}
{
    std::cout << "B constructor" << std::endl;
}

B::~B() noexcept
{
    std::cout << "B destructor" << std::endl;
}

void B::printX() const noexcept
{
    std::cout << "Print x from B: " << m_x << std::endl;
}

void B::printY() const noexcept
{
    std::cout << "Print y from B: " << m_y << std::endl;
}

//____________________________________________
struct C : A
{
    C() noexcept;
    ~C() noexcept override;

    void printX() const noexcept override;
    void printY() const noexcept override;
};

C::C() noexcept :
    A{3, 4}
{
    std::cout << "C constructor" << std::endl;
}

C::~C() noexcept
{
    std::cout << "C destructor" << std::endl;
}

void C::printX() const noexcept
{
    std::cout << "Print x from C: " << m_x << std::endl;
}

void C::printY() const noexcept
{
    std::cout << "Print y from C: " << m_y << std::endl;
}

//____________________________________________
int main()
{
    {
        std::unique_ptr<A> pA{new B};
        pA->printX();
        pA->printY();
    }
    {
        std::unique_ptr<A> pA{new C};
        pA->printX();
        pA->printY();
    }
    return 0;
}
