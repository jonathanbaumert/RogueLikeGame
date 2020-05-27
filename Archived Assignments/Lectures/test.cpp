#include <iostream>
using namespace std;
const char * name(){
    static const char * n = "BOB";
    cout<<n<<endl;
    return n;
}

main(int argc, char * argv[]){
    cout<<(name()="Kevin")<<endl;
}