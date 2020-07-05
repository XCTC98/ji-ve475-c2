#include <iostream>
#include <fstream>
#include <stdio.h>
#include <gmp.h>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <string.h>
#include<cmath>
using namespace std;

#define LENGTH_KEY 1671
void GenerateKey(){

    int i=1;
    srand((int)time(0));
    int a;
    int b;
    for(i=0;i<LENGTH_KEY;i++)
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

void encrypt(const char * message, string Key){
    //read key
    srand((int)time(0));
    ifstream keyfile;
    keyfile.open(Key);
    string key;
    keyfile >> key;
    int length_m=strlen(message);


    int length_um=max(3*length_m,501);

    int* usedmap=new int[length_um];
    int index_m=0;
    int index_k=0;


    //cout<<index_m<<" "<<length_m<<" "<<index_k<<" "<<key.length()<<endl;
    int index=length_um/2;
    while(index_m<length_m && index_k<key.length())
    {

    	//17 is coprime to 501
    	index=(index+17*(int)key.at(index_k))%(length_um);
    	index_k++;

    	while(usedmap[index]!=0)
    	{
    		if(index_k>=key.length())
    		{
    			//不能用这个key了,但我希望的是，不要有人搞了个1600+的key都摆不定的东西出来
				for(int i=length_um-1;i>=0;i--)
				{
					if(usedmap[i]==0)
					{
						index=i;
						break;
					}
				 }
			}
			else
			{
				//首次卡住后用19跳步
				index=(index+19*(int)key.at(index_k))%length_um;
            	index_k++;
			}
		}

        //cout<<index<<endl;
		usedmap[index]=message[index_m];
		index_m++;
	}

    index=length_um/2;
    while(index_m<length_m)
    {
    	while(usedmap[index]!=0)
    	{
    		index=(index-1+length_um)%(length_um);
		}
		usedmap[index]=message[index_m];
		index_m++;
	}


    index_k=index_k/2;
    index=2*length_um/3;
    for(int i=0;i<length_um;i++)
    {
    	//用非法解密填补不足（1-37）
		 if(usedmap[i]!=0)
		 {
		 	continue;
		 }
		 else
		 {
		 	usedmap[i]=(rand()%37)+1;
		 }
	}



    //encryption
    int ii=0;
    mpz_t m;
    mpz_t c;
    mpz_t e;
    mpz_t n;
    mpz_init(m);
    mpz_init(c);
    mpz_init(e);
    mpz_init(n);

    mpz_set_ui(e, 1);
    mpz_set_ui(n, 0);

    for(ii=0;ii<length_um;ii++)
    {
    	mpz_set_ui(m,usedmap[ii]);
    	mpz_mul(c,m,e);
    	mpz_add(n,n,c);
    	mpz_mul_ui(e,e,197);
	}

    gmp_printf("%Zd \n", n);
    mpz_clear(m);
    mpz_clear(c);
    mpz_clear(e);
    mpz_clear(n);

    delete [] usedmap;
}

void decrypt(const char * message, string Key){
    //read key
    ifstream keyfile;
    keyfile.open(Key);
    string key;
    keyfile >> key;


    //decryption
    mpz_t m;
    mpz_t e;
    mpz_t d;
    mpz_t n;
    mpz_init(m);
    mpz_init(e);
    mpz_init(d);
    mpz_init(n);


    mpz_set_str(n, message, 10);


    int length_um=0;

    mpz_set_ui(e, 1);

    while(mpz_cmp(n, e)>0)
    {
    	length_um++;
    	mpz_mul_ui(e,e,197);//Now e=197^length_um
	}

	// Here we get the length of usedmap

    int length_m=length_um/3;//如果是501的情况，那么就可以提前截断
	char* decrypt=new char[length_m+1];
    int* usedmap=new int[length_um];

    int index=length_um/2;

    int index_k=0;

    int index_m=0;

    int ii=0;

    while( index_k<key.length())
    {

    	index=(index+17*(int)key.at(index_k))%(length_um);
    	index_k++;

    	while(usedmap[index]!=0)
    	{
    		if(index_k>=key.length())
    		{

				for(int i=length_um-1;i>=0;i--)
				{
					if(usedmap[i]==0)
					{
						index=i;
						break;
					}
				 }
			}
			else
			{
				//首次卡住后用19跳步
				index=(index+19*(int)key.at(index_k))%length_um;
            	index_k++;
			}
		}


		//cout<<index<<endl;

    mpz_ui_pow_ui(e, 197,index+1);

    mpz_fdiv_qr(d, m,n,e);//考虑m

	 mpz_tdiv_q_ui(e, e, 197);

	 mpz_fdiv_q(d, m, e);



	 if(mpz_cmp_si(d,38)<0)
	 {
	 	break;
	 }
	 else
	 {
	 	decrypt[ii++]=mpz_get_ui(d);
	 	usedmap[index]=1;//不需要确定数据，标志即可
	 }


	}

    index=length_um/2;

    while(decrypt[ii-1]>38)
    {
    	//这里代表key没了

    	while(usedmap[index]!=0)
    	{
    		index=(index-1+length_um)%(length_um);
		}
		 mpz_ui_pow_ui(e, 197,index+1);

    mpz_fdiv_qr(d, m,n,e);//考虑m

	 mpz_tdiv_q_ui(e, e, 197);

	 mpz_fdiv_q(d, m, e);



	 if(mpz_cmp_si(d,38)<0)
	 {
	 	break;
	 }
	 else
	 {
	 	decrypt[ii++]=mpz_get_ui(d);
	 	usedmap[index]=1;//不需要确定数据，标志即可
	 }
	}








    decrypt[ii]='\0';



    cout<<decrypt<<endl;



    delete []decrypt;
    delete []usedmap;


    mpz_clear(m);
    mpz_clear(e);
    mpz_clear(d);
    mpz_clear(n);
}

int main(int argu, char * argv[]) {
    if (argu == 2) GenerateKey();
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
    return 0;
}




