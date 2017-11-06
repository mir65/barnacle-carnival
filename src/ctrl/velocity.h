/* Initializes the velocity controller. */

void ctrl_velocity_init();
{
 
double sp,pv,reset,o0
    
    
error:=sp-pv;
if reset then
old:=0.0;

else
old:=old;
outKP:=kp*error;
outKD:=kd*(error-i0_old)/sample_time;
i0_old:=error;
end_if;
 
if error*sample_time*ki+old+outKP+outKD>limit_upper then
o0:=limit_upper;
old:=limit_upper;

else
if error*sample_time*ki+old+outKP+outKD<limit_lower then
o0:=limit_lower;
old:=limit_lower;

else
o0 := error*sample_time*ki+old+outKP+outKD;
old:=o0-outKP-outKD;
end_if;
end_if;
    
  
  
  
  
}
