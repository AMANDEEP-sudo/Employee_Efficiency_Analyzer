#include <iostream>
#include "Admin.h"
#include "Utils.h"

using namespace std;

int main() {
    // Create Admin object which is the main controller
    Admin admin;
    
    // Run the main application loop
    admin.run();
    
    return 0;
}
