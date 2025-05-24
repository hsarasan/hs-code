#include <iostream>

[[nodiscard]] bool performImportantOperation(){
    std::cout<<"Performing important operation "<<std::endl;
    return true;
}

int main(){
    performImportantOperation();
}