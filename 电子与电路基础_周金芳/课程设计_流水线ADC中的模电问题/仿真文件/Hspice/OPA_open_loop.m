x=loadsig('OPA_open_loop.sw0');
y=loadsig('OPA_open_loop.ac0');
plotsig(x,'v_3','VOLTS');
plotsig(y,'vdb_3;vp_3','logx');