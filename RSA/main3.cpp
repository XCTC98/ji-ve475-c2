#include <iostream>
#include <fstream>
#include <stdio.h>
//#include <gmp.h>
#include <cmath>
#include <ctime>
#include <cstdlib>

using namespace std;

void GenerateKey(){
    
    int i=1;
    srand((int)time(0));
    int a;
    int b;
    for(i=0;i<1671;i++)
    {
	
    b=rand() % 70;
    if(b<26) a=(rand() % (90-65+1))+ 65; 
    else if (b<38) a=(rand() % (57-48+1))+ 48; 
    else if (b<64)a=(rand() % (122-97+1))+ 97; 
    else 
    {
    	int mark=rand()%7;
    	if(mark==0) a=',';
		else if(mark==1) a='.';
		else if(mark==2) a=';';
		else if(mark==3) a='?';
		else if(mark==4) a='!';
		else if(mark==5) a='(';	
		else a=')';
		}
    cout<<(char)a;
	}
    
}
/*
void encrypt(const char * message, string key){
    //read key
    ifstream keyfile;
    keyfile.open(key);
    string p0, q0, n0, phi0, e0, d0;
    keyfile >> p0 >> q0 >> n0 >> phi0 >> e0 >> d0;
    int  
    //encryption
    mpz_t m;
    mpz_t c;
    mpz_t e;
    mpz_t n;
    mpz_init(m);
    mpz_init(c);
    mpz_init(e);
    mpz_init(n);
    mpz_set_str(m, message, 10);
    mpz_set_str(e, e1, 10);
    mpz_set_str(n, n1, 10);
    mpz_powm(c, m ,e, n);
    gmp_printf("%Zd \n", c);
    mpz_clear(m);
    mpz_clear(c);
    mpz_clear(e);
    mpz_clear(n);
}

void decrypt(const char * message, string key){
    //read key
    ifstream keyfile;
    keyfile.open(key);
    string p0, q0, n0, phi0, e0, d0;
    keyfile >> p0 >> q0 >> n0 >> phi0 >> e0 >> d0;
    const char* d1 = d0.c_str();
    const char* n1 = n0.c_str();
    //encryption
    mpz_t m;
    mpz_t c;
    mpz_t d;
    mpz_t n;
    mpz_init(m);
    mpz_init(c);
    mpz_init(d);
    mpz_init(n);
    mpz_set_str(c, message, 10);
    mpz_set_str(d, d1, 10);
    mpz_set_str(n, n1, 10);
    mpz_powm_sec(m, c, d, n);
    if (mpz_cmp_ui(m, 0) == 0) cout << "really zero?" << endl;
    gmp_printf("%Zd \n", m);
    mpz_clear(m);
    mpz_clear(c);
    mpz_clear(d);
    mpz_clear(n);
}
*/
int main(int argu, char * argv[]) {
    /*if (argu == 2) GenerateKey();
    else if (argu == 3 && argv[1][2] == 'e') encrypt(argv[2], "keyfile.txt");
    else if (argu == 3 && argv[1][2] == 'd') {
        //test if is using the default key to decript the ciphertext
        ifstream cipher;
        cipher.open("ciphertext.txt");
        string ciphertext0;
        const char* ciphertext1 = ciphertext0.c_str();
        mpz_t ciphertext;
        mpz_init(ciphertext);
        mpz_set_str(ciphertext, ciphertext1, 10);
        mpz_t text;
        mpz_init(text);
        mpz_set_str(text, argv[2], 10);
        if (mpz_cmp(text, ciphertext) == 0) {
            mpz_clear(text);
            mpz_clear(ciphertext);
            cout << "cheater: it is forbidden to decrypt the challenge ciphertext" << endl;
            return 0;
        }
        decrypt(argv[2], "keyfile.txt");
        mpz_clear(text);
        mpz_clear(ciphertext);
    }
    else if (argu == 5 && argv[1][2] == 'e') encrypt(argv[2], argv[4]);
    else if (argu == 5 && argv[1][2] == 'd') decrypt(argv[2], argv[4]);
    return 0;*/
    GenerateKey();
}



