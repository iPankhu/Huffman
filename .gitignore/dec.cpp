#include <iostream>
#include <string>
#include <fstream>
#include "huffdec.h"

using namespace std;

int main(int argc, char const *argv[]) {

   if ( argc != 3 ){
    cout<<"Usage: "<<argv[0]<<" encoded.bin code_table.txt"<<endl;
    return 0;
    }

    std::ifstream f (argv[1],ios::binary | ios::in);
    if ( !f.is_open() ){
      std::cout<<"Error: File cannot be opened \n";
      return 0;
    }

    ifstream ct(argv[2], ios::in);
    if ( !ct.is_open() ){
      std::cout<<"Error: File cannot be opened\n";
      return 0;
    }

    Decode D = Decode();
    int a;
    string b;
    cout << "Decoded tree is being built" << endl;
    while (ct >> a >> b) {
        D.leafadd(a, b);
    }



    cout << "Binary file is being decoded" << endl;
    ofstream onfile ("decoded.txt",std::ios::out);

    char c;
    string res;
    while (f.get(c)) {
        for (int i = 7; i >= 0; i--) {
            int d = (c >> i) & 1;
            res.append(to_string(d));
            if (D.getnow(res) != -1) {

                onfile << D.getnow(res) << endl;
                res = "";
            }
        }

    }

    onfile.close();
    f.close();
    ct.close();
    return 0;
}


