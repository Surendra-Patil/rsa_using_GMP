/**************************************\
* Create By $urendr@ पाटील                                  *
* 3 November 2015                       *
* Version 1.0                           *
\***************************************/
           
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <gmp.h>

typedef struct {
    mpz_t n; 
    mpz_t e; 
} public_key;

typedef struct {
    mpz_t n; 
    mpz_t e; 
    mpz_t d; 
    mpz_t p; 
    mpz_t q; 
} private_key;


int main()
{
    int i;
    mpz_t M; mpz_init(M);
    mpz_t C; mpz_init(C);
    mpz_t DC; mpz_init(DC);
    private_key ku;
    public_key kp;
    mpz_init(ku.n); 
    mpz_init(ku.e); 
    mpz_init(ku.d); 
    mpz_init(ku.p); 
    mpz_init(ku.q); 
    mpz_t tmp1; mpz_init(tmp1);
    mpz_t tmp2; mpz_init(tmp2); 
    mpz_t phi; mpz_init(phi);
    mpz_init_set_str (ku.p, "1000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000166047", 10); //set values of p
    mpz_init_set_str (ku.q, "1000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000166291", 10); //set value of q
    mpz_t x;
    mpz_init_set_str (x, "3", 10);
    mpz_t tmp5;
    mpz_init(tmp5);
    mpz_mul(ku.n,ku.p,ku.q);
    mpz_sub_ui(tmp1, ku.p, 1);
    mpz_sub_ui(tmp2, ku.q, 1);
    mpz_mul(phi, tmp1, tmp2);

     int z;
     while(1)
     {
	mpz_gcd(tmp5, x, phi);
		if(mpz_cmp_ui(tmp5,1)==0)
		{
		break;
		}
	mpz_add_ui(x, x, 1);
     }

     mpz_swap(x,ku.e);
     
   if(mpz_invert(ku.d, ku.e, phi) == 0)
    {
        mpz_gcd(tmp1, ku.e, phi);
        printf("gcd(e, phi) = [%s]\n", mpz_get_str(NULL, 16, tmp1));
        printf("Invert failed\n");
    }

	mpz_set(kp.e,ku.e);
	mpz_set(kp.n,ku.n);

    printf("Private Key\n");
    printf("kp.n is [%s]\n", mpz_get_str(NULL, 16, kp.n));
    printf("kp.e is [%s]\n", mpz_get_str(NULL, 16, kp.e));
    
    printf("Public Key\n");
    printf("ku.n is [%s]\n", mpz_get_str(NULL, 16, ku.n));
    printf("ku.e is [%s]\n", mpz_get_str(NULL, 16, ku.e));
    printf("ku.d is [%s]\n", mpz_get_str(NULL, 16, ku.d));
    printf("ku.p is [%s]\n", mpz_get_str(NULL, 16, ku.p));
    printf("ku.q is [%s]\n", mpz_get_str(NULL, 16, ku.q));
    printf("phi is [%s]\n", mpz_get_str(NULL, 16, phi));


    mpz_set_ui(M, 43284738247347238); // Set your message in numbers...
        
    printf("original is [%s]\n", mpz_get_str(NULL, 16, M)); 
    mpz_powm(C, M, kp.e, kp.n);
    printf("encrypted is [%s]\n", mpz_get_str(NULL, 16, C));
  
    mpz_powm(DC, C, ku.d, ku.n); 
    printf("decrypted is [%s]\n", mpz_get_str(NULL, 16, DC));
    return 0;
}
