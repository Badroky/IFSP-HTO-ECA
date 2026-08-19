#include <iostream>
#include <iomanip>
#include <cstdio>

using namespace std;

enum t_formato { F24, F12 };

class Relogio {
    private:
        int _h;
        int _m;
        int _s;
        t_formato _f;

        void _norm_relogio(){
            _m = _m + _s / 60;
            _s = _s % 60;      
            _h = _h + _m/60;  
            _m = _m % 60;      
            _h = _h % 24;
        }

    public:

        relogio(){
            ini();
        }

        void ini(int h=0, int m=0, int s=0, t_formato f=F24){
            _h = h;
            _m = m;
            _s = s;
            _f = f;
            _norm_relogio();
        }
        
        void set_formato(t_formato f){
           _f = f;
        }
        
        void print() {
            if(_f == F24){
                printf("%02d:%02d:%02d\n",_h,_m,_s);
            }
            else{
                int h = _h % 12;
                if (h==0) h = 12;
                printf("%02d:%02d:%02d %s\n",h,_m,_s, _h<12? "AM":"PM");
            }
        }
};

int main() {
    Relogio reloginho;

    reloginho.print();
    reloginho.ini();
    reloginho.print();
    reloginho.ini(100, 100, 100, F24);
    reloginho.print();
    relogiobonito.set(reloginho);
    relogiobonito.print();
}

