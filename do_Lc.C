#include "Booster_Eff_Lc.h"

int main(){

for(int i=0;i<4;i++)
    
{
    
 

MakeD0AccEff(0,i);
MakeD0AccEff(1,i);
MakeD0AccEff(2,i);
MakeD0AccEff(3,i);
MakeD0AccEff(4,i);
    

doDsEffMergingBunches(0);
doDsEffMergingBunches(1);
doDsEffMergingBunches(2);
doDsEffMergingBunches(3);
doDsEffMergingBunches(4);
    
wEff(i);
    
   }
    
    return 0;
}
