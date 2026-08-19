#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <math.h>

using namespace std;

typedef enum {
	A_IGUAL_B = -1,
	A_MENOR_B,
	A_MAIOR_B
} tEnumRel;

typedef enum {
	F24, F12
} tFormato;

typedef struct {
	int h;
	int m;
	int s;
	tFormato f;
} tRelogio;


class Relogio {
    private:
        int _h;
	    int _m;
	    int _s;
	    tFormato _f;
    public:
        void ini(){
            _h = 0;
            _m = 0;
            _s = 0;
            _f = F24;
        }
        void print() {
        	if(_f == F24) {
        		printf("%02d:%02d:%02d\n", _h, _m, _s);
        	} else {
        		int h = _h % 12;
        		if(h==0) h = 12;
        		printf("%02d:%02d:%02d %s\n", h, _m, _s, _h<12? "AM":"PM");
        	}
        }
};



int clockRelogio(tRelogio* r) {
	if((r->s)++ >= 59) {
		r->s = 0;
		if((r->m)++ >= 59) {
			r->m = 0;
			//*h = (*h+1) % 24;

			if((r->h)++>=23) {
				r->h = 0;
				return 1;
			}
		}
	}
	return 0;
}

void printRelogio(tRelogio r) {
	if(r.f == F24) {
		printf("%02d:%02d:%02d\n", r.h, r.m, r.s);
	} else {
		int h = r.h % 12;
		if(h==0) h = 12;
		printf("%02d:%02d:%02d %s\n", h, r.m, r.s, r.h<12? "AM":"PM");
	}
}


tRelogio setNormRelogio(tRelogio* r, tRelogio rt ) {
	*r=rt;
	return rt;
}


tRelogio normRelogio(tRelogio r) {
	r.m = r.m + r.s / 60;  //calcula minutos excedentes
	r.s = r.s % 60;       //normaliza os segundos
	r.h = r.h + r.m/60;    //calcula horas excedentes
	r.m = r.m % 60;       //normaliza os minutos
	//r.h = r.h % 24;       //normaliza a hora
	return r;
}

tRelogio normHoraRelogio(tRelogio r) {
    r.h = r.h % 24;
    return r;
}


int setRelogio(tRelogio* r, tRelogio tr) {
	*r = normRelogio(tr);
	return tr.h > 23 || tr.m > 59|| tr.s > 59;
}

tEnumRel comparaRelogio(tRelogio r1, tRelogio r2) {
	if(r1.h != r2.h) {
	    if(r1.h > r2.h)
	        return A_MAIOR_B;
	   else
	        return A_MENOR_B;
	}
    if(r1.m != r2.m) {
        if(r1.m > r2.m)
            return A_MAIOR_B;
        else
            return A_MENOR_B;
    }
    if(r1.s != r2.s) {
        if(r1.s > r2.s)
            return A_MAIOR_B;
        else
            return A_MENOR_B;
    }
    return A_IGUAL_B;
}


tRelogio somaRelogio(tRelogio r1, tRelogio r2) {
    r1.h += r2.h;
    r1.m += r2.m;
    r1.s += r2.s;
    return normRelogio(r1);
}


/*
tRelogio somaNRelogios(int count, ...) {

}
*/
int paraSegundos(tRelogio r) {
    return r.s + r.m * 60 + r.h*3600;
}

float paraMinutos(tRelogio r) {
    return r.m + r.s/60.0 + r.h*60;
}

float paraHoras(tRelogio r) {
    return r.h + r.s/3600.0 + r.m/60.;
}

tRelogio segundosPara(int s) {
    tRelogio x = {.s = s};
    return normRelogio(x);
}


tRelogio minutosPara(float m) {
    tRelogio x = {.m = m};
    return normRelogio(x);
}


tRelogio horasPara(float h) {
    tRelogio x = {.h = h};
    return normRelogio(x);
}

tRelogio togleFRelogio(tRelogio r) {
    if(r.f == F24){
        r.f = F12;
    } else {
        r.f = F24;
    }
    return r;
}

tRelogio setFRelogio(tRelogio* r, tFormato f) {
    r->f = f;
    return *r;
}

int main()
{
    Relogio reloginho;
    
    reloginho.print();
    reloginho.ini();
    reloginho.print();
    
    /*
	tRelogio x = {.h =22, .m=30, .s=36, .f=F12};
	tRelogio y = {.h =22, .m=30, .s=10, .f=F12};
	printRelogio(x);
	printRelogio(togleFRelogio(x));
	printRelogio(y);
	printRelogio(setFRelogio(&y, F24));
	printRelogio(y);
	*/
	
	
}