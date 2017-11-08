with(plots) ;

GAM := 2 ;

integ:=evalf(int(exp(-1/((t*(1-t))^GAM)), t=0..1))/255 ;

PHI := z-> evalf(int(exp(-1/((t*(1-t))^GAM)),t=0..z)/integ):
plotsetup(     ps,
               plotoutput=`fct.eps`,
              plotoptions=`width=4cm,height=4cm,noborder,portrait,leftmargin=1cm,bottommargin=1cm`
);
#interface(plotdevice=x11) ;

plot([z,PHI(z),z=0..1],numpoints=100) ;



plotsetup(     ps,
               plotoutput=`Dfct.eps`,
              plotoptions=`width=4cm,height=4cm,noborder,portrait,leftmargin=1cm,bottommargin=1cm`
);
#interface(plotdevice=x11) ;

DPHI := z -> D(PHI)(z) ;

plot([z,DPHI(z),z=0..1],numpoints=100) ;

plotsetup(     ps,
               plotoutput=`DDfct.eps`,
              plotoptions=`width=4cm,height=4cm,noborder,portrait,leftmargin=1cm,bottommargin=1cm`
);
#interface(plotdevice=x11) ;
DDPHI := z -> D(DPHI)(z) ;
plot([z,DDPHI(z),z=0..1],numpoints=100) ;

quit ;