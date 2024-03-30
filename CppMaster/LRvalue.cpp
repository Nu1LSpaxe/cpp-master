#include <iostream>

int x = 42;

// Define a function that returns a reference to an integer
int& foo() {
    return x; // Returning a reference to the integer x
}

int main() {
    // Call the foo function and assign the returned reference to a reference variable
    int& result = foo();

    // Now, result is a reference to the integer x
    std::cout << "Value of x: " << result << std::endl;
    std::cout << "Address of x: " << &result << std::endl;

    // Modify the value of x through the reference result
    result = 100;

    // Check the value of x
    std::cout << "New value of x: " << x << std::endl;
    std::cout << "Address of result: " << &result << std::endl;

    system("pause");
    return 0;
}
