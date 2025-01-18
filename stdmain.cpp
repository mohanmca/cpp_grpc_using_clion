#include <iostream>
#include <ostream>
#include <unistd.h>
#include <sys/utsname.h>
#include <vector>

class Employee
{
public:
    Employee(): m_age(0), m_name("NoName")
    {
    };

    Employee(int age, std::string name): m_age(age), m_name(name)
    {
    }

    friend std::ostream& operator<<(std::ostream& os, const Employee& obj)
    {
        return os
            << "m_age: " << obj.m_age
            << " m_name: " << obj.m_name;
    };

private:
    int m_age;
    std::string m_name;
};


int main()
{
    Employee employees[10];
    std::vector<Employee> employeesVector;

    //** create vector and add 10 employees and generate code in next line
    for (int i = 0; i < 10; i++)
    {
        employees[i] = Employee(i, "Name" + std::to_string(i));
        employeesVector.emplace_back(employees[i]);
    }

    for (const auto& employee : employeesVector)
    {
        std::cout << employee << std::endl;
    }


    return 0;
}


