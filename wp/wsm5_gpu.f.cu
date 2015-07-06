#define REWORK_FALL
#define REWORK_PART2
// wsm5_gpu.cu gets preprocessed by spt.pl, which handles the _def_ directives before it is compiled

#ifndef PREPASS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "cublas.h"
#endif

#define IDEBUG ((DEBUG_I)-2)
#define JDEBUG ((DEBUG_J)-2)
#define KDEBUG (DEBUG_K)

// this is an M4 include









//SPTSTART

#include "spt.h"

#include "util.h"

# define float float



__global__ void wsm5_gpu ( 
                    float *th, float *pii                   //_def_ arg ikj:th,pii
                   ,float *q                                //_def_ arg ikj:q
                   ,float *qc,float *qi,float *qr,float *qs //_def_ arg ikj:qc,qi,qr,qs
                   ,float *den, float *p, float *delz       //_def_ arg ikj:den,p,delz
#ifdef DEBUGAL_ARRAY
,float *debuggal                           //_def_ arg ikj:debuggal
#endif
                   ,float *rain,float *rainncv              //_def_ arg ij:rain,rainncv
                   ,float *sr                               //_def_ arg ij:sr
                   ,float *snow,float *snowncv              //_def_ arg ij:snow,snowncv
                   ,float delt
,float* retvals
                   ,int ids, int ide,  int jds, int jde,  int kds, int kde          
                   ,int ims, int ime,  int jms, int jme,  int kms, int kme          
                   ,int ips, int ipe,  int jps, int jpe,  int kps, int kpe          
                         )
{

   float xlf, xmi, acrfac, vt2i, vt2s, supice, diameter ;
   float roqi0, xni0, qimax, value, source, factor, xlwork2 ;
   float t_k, q_k, qr_k, qc_k, qs_k, qi_k, qs1_k, qs2_k, cpm_k, xl_k, xni_k, w1_k, w2_k, w3_k  ;

#define hsub   xls
#define hvap   xlv0
#define cvap   cpv
     float ttp ;
     float dldt ;
     float xa ;
     float xb ;
     float dldti ;
     float xai ;
     float xbi ;

#if (FLOAT_4 == 4)
   Float4 qs1[MKX] ; 
#else
   float qs1[MKX] ; 
#endif
#if (FLOAT_4 == 4)
   Float4 qs2[MKX] ; 
#else
   float qs2[MKX] ; 
#endif
#if (FLOAT_4 == 4)
   Float4 rh1[MKX] ; 
#else
   float rh1[MKX] ; 
#endif
#if (FLOAT_4 == 4)
   Float4 rh2[MKX] ; 
#else
   float rh2[MKX] ; 
#endif
     //_def_ local k:qs1,qs2,rh1,rh2

#ifdef DEBUGAL_ARRAY
  debuggal[P3(ti,0,tj)] = 999.00 ;
#endif

if ( ig < ide-ids+1 && jg < jde-jds+1 ) {


   int k ;

#include "wsm5_constants.h"

#if (FLOAT_4 == 4)
   Float4 t[MKX] ; 
#else
   float t[MKX] ; 
#endif
   //_def_ local k:t
#if (FLOAT_4 == 4)
   Float4 cpm[MKX] ; 
#else
   float cpm[MKX] ; 
#endif
#if (FLOAT_4 == 4)
   Float4 xl[MKX] ; 
#else
   float xl[MKX] ; 
#endif
   //_def_ local k:cpm,xl

   for ( k = kps-1 ; k <= kpe-1 ; k++ ) {
     t[k] = th[P3(ti,k,tj)] * pii[P3(ti,k,tj)] ;
   }

   for( k=kps-1 ;k<=kpe-1;k++) { 
                                if ( qc[P3(ti,k,tj)] < 0. ) { qc[P3(ti,k,tj)] = 0. ; } 
                                if ( qi[P3(ti,k,tj)] < 0. ) { qi[P3(ti,k,tj)] = 0. ; } 
                                if ( qr[P3(ti,k,tj)] < 0. ) { qr[P3(ti,k,tj)] = 0. ; } 
                                if ( qs[P3(ti,k,tj)] < 0. ) { qs[P3(ti,k,tj)] = 0. ; } 
                               }

// 564 !----------------------------------------------------------------
// 565 !     latent heat for phase changes and heat capacity. neglect the
// 566 !     changes during microphysical process calculation
// 567 !     emanuel(1994)

#define CPMCAL(x) (cpd*(1.-max(x,qmin))+max(x,qmin)*cpv)
#define XLCAL(x)  (xlv0-xlv1*((x)-t0c))

   for ( k = kps-1 ; k <= kpe-1 ; k++ ) {
     cpm[k] = CPMCAL(q[P3(ti,k,tj)]) ;
     xl[k] = XLCAL(t[k]) ;
   }

// 576 !----------------------------------------------------------------
// 577 !     compute the minor time steps.

   float dtcldcr = 120. ;
   int loops = delt/dtcldcr+.5 ;

   loops = MAX(loops,1) ;
   float dtcld = delt/loops ;
   if ( delt <= dtcldcr) dtcld = delt ;

   int loop ;


   for ( loop = 1 ; loop <= loops ; loop++ ) {
// 585 !----------------------------------------------------------------
// 586 !     initialize the large scale variables
     int mstep = 1 ;

     ttp=t0c+0.01 ;
     dldt=cvap-cliq ;
     xa=-dldt/rv ;
     xb=xa+hvap/(rv*ttp) ;
     dldti=cvap-cice ;
     xai=-dldti/rv ;
     xbi=xai+hsub/(rv*ttp) ;


     float tr, ltr, tt, pp, qq ;

     for ( k = kps-1 ; k <= kpe-1 ; k++ ) {

       pp = p[P3(ti,k,tj)] ;
       tt = t[k] ;
       tr = ttp/tt ;
       ltr = log(tr) ;

       qq=psat*exp(ltr*(xa)+xb*(1.-tr)) ;
       qq=ep2*qq/(pp-qq) ;
       qs1[k] = MAX(qq,qmin) ;
       rh1[k] = MAX( q[P3(ti,k,tj)]/qs1[k],qmin) ;

       if( tt < ttp ) {
         qq=psat*exp(ltr*(xai)+xbi*(1.-tr)) ;
       } else {
         qq=psat*exp(ltr*(xa)+xb*(1.-tr)) ;
       }
       qq = ep2 * qq / (pp - qq) ;
       qs2[k] = MAX(qq,qmin) ;
       rh2[k] = MAX(q[P3(ti,k,tj)]/qs2[k],qmin) ;

     }

float prevp_reg ;
float psdep_reg ;
float praut_reg ;
float psaut_reg ;
float pracw_reg ;
float psaci_reg ;
float psacw_reg ;
float pigen_reg ;
float pidep_reg ;
float pcond_reg ;
float psmlt_reg ;
float psevp_reg ;
     //_def_ register 0:prevp,psdep,praut,psaut,pracw,psaci,psacw,pigen,pidep,pcond,psmlt,psevp
#if (FLOAT_4 == 4)
   Float4 xni[MKX] ; 
#else
   float xni[MKX] ; 
#endif
     //_def_ local k:xni

     for ( k = kps-1 ; k <= kpe-1 ; k++ ) {
          xni[k] = 1.e3 ;
      }

//     diffus(x,y) = 8.794e-5 * exp(log(x)*(1.81)) / y        ! 8.794e-5*x**1.81/y
//     viscos(x,y) = 1.496e-6 * (x*sqrt(x)) /(x+120.)/y  ! 1.496e-6*x**1.5/(x+120.)/y
//     xka(x,y) = 1.414e3*viscos(x,y)*y
//     diffac(a,b,c,d,e) = d*a*a/(xka(c,d)*rv*c*c)+1./(e*diffus(c,b))
//     venfac(a,b,c) = exp(log((viscos(b,c)/diffus(b,a)))*((.3333333)))    &
//                    /sqrt(viscos(b,c))*sqrt(sqrt(den0/c))

#define DIFFUS(x,y) (8.794e-5 * exp(log(x)*(1.81)) / (y))
#define VISCOS(x,y) (1.496e-6 * ((x)*sqrt(x)) /((x)+120.)/(y))
#define XKA(x,y) (1.414e3*VISCOS((x),(y))*(y))
#define DIFFAC(a,b,c,d,e) ((d)*(a)*(a)/(XKA((c),(d))*rv*(c)*(c))+1./((e)*DIFFUS((c),(b))))
#define VENFAC(a,b,c) (exp(log((VISCOS((b),(c))/DIFFUS((b),(a))))*((.3333333)))*rsqrt(VISCOS((b),(c)))*sqrt(sqrt(den0/(c))))
#define CONDEN(a,b,c,d,e) ((MAX((b),qmin)-(c))/(1.+(d)*(d)/(rv*(e))*(c)/((a)*(a))))

#define LAMDAR(x,y) sqrt(sqrt(pidn0r/((x)*(y))))
#define LAMDAS(x,y,z) sqrt(sqrt(pidn0s*(z)/((x)*(y))))

// calculate mstep for this colum

#if (FLOAT_4 == 4)
   Float4 rsloper[MKX] ; 
#else
   float rsloper[MKX] ; 
#endif
#if (FLOAT_4 == 4)
   Float4 rslopebr[MKX] ; 
#else
   float rslopebr[MKX] ; 
#endif
#if (FLOAT_4 == 4)
   Float4 rslope2r[MKX] ; 
#else
   float rslope2r[MKX] ; 
#endif
#if (FLOAT_4 == 4)
   Float4 rslope3r[MKX] ; 
#else
   float rslope3r[MKX] ; 
#endif
     //_def_ local k:rsloper,rslopebr,rslope2r,rslope3r
#if (FLOAT_4 == 4)
   Float4 rslopes[MKX] ; 
#else
   float rslopes[MKX] ; 
#endif
#if (FLOAT_4 == 4)
   Float4 rslopebs[MKX] ; 
#else
   float rslopebs[MKX] ; 
#endif
#if (FLOAT_4 == 4)
   Float4 rslope2s[MKX] ; 
#else
   float rslope2s[MKX] ; 
#endif
#if (FLOAT_4 == 4)
   Float4 rslope3s[MKX] ; 
#else
   float rslope3s[MKX] ; 
#endif
     //_def_ local k:rslopes,rslopebs,rslope2s,rslope3s
#if (FLOAT_4 == 4)
   Float4 denfac[MKX] ; 
#else
   float denfac[MKX] ; 
#endif
     //_def_ local k:denfac
#if (FLOAT_4 == 4)
   Float4 n0sfac[MKX] ; 
#else
   float n0sfac[MKX] ; 
#endif
     //_def_ local k:n0sfac
#if (FLOAT_4 == 4)
   Float4 w1[MKX] ; 
#else
   float w1[MKX] ; 
#endif
#if (FLOAT_4 == 4)
   Float4 w2[MKX] ; 
#else
   float w2[MKX] ; 
#endif
#if (FLOAT_4 == 4)
   Float4 w3[MKX] ; 
#else
   float w3[MKX] ; 
#endif
     //_def_ local k:w1,w2,w3


     float w ; 
     float rmstep ;
     int numdt ;
     for ( k = kps-1 ; k <= kpe-1 ; k++ ) {
       float supcol = t0c - t[k] ;
       n0sfac[k] = MAX(MIN(exp(alpha*supcol),n0smax/n0s),1.) ;
       if ( qr[P3(ti,k,tj)] <= qcrmin ) {
         rsloper[k]  = rslopermax ;
         rslopebr[k] = rsloperbmax ;
         rslope2r[k] = rsloper2max ;
         rslope3r[k] = rsloper3max ;
       } else {
         rsloper[k]  = 1./LAMDAR(qr[P3(ti,k,tj)],den[P3(ti,k,tj)]) ;
         rslopebr[k] = exp(log(rsloper[k])*bvtr) ;
         rslope2r[k] = rsloper[k] * rsloper[k] ; 
         rslope3r[k] = rslope2r[k] * rsloper[k] ; 
       }
       if ( qs[P3(ti,k,tj)] <= qcrmin ) {
         rslopes[k]  = rslopesmax ;
         rslopebs[k] = rslopesbmax ;
         rslope2s[k] = rslopes2max ;
         rslope3s[k] = rslopes3max ;
       } else {
         rslopes[k] = 1./LAMDAS(qs[P3(ti,k,tj)],den[P3(ti,k,tj)],n0sfac[k]) ;
         rslopebs[k] = exp(log(rslopes[k])*bvts) ;
         rslope2s[k] = rslopes[k] * rslopes[k] ; 
         rslope3s[k] = rslope2s[k] * rslopes[k] ; 
       }
       denfac[k] = sqrt(den0/den[P3(ti,k,tj)]) ;
       w1[k] = pvtr*rslopebr[k]*denfac[k]/delz[P3(ti,k,tj)] ;
       w2[k] = pvts*rslopebs[k]*denfac[k]/delz[P3(ti,k,tj)] ;

       w = MAX(w1[k],w2[k]) ;
       numdt = MAX((int)trunc(w*dtcld+.5+.5),1) ;
       if ( numdt >= mstep ) mstep = numdt ;
//-------------------------------------------------------------
// Ni: ice crystal number concentration   [HDC 5c]
//-------------------------------------------------------------
       float temp = (den[P3(ti,k,tj)]*MAX(qi[P3(ti,k,tj)],qmin)) ;
       temp = sqrt(sqrt(temp*temp*temp)) ;
#ifdef DEBUGDEBUG
       xni[k] = 1.e3 ;
#else
       xni[k] = MIN(MAX(5.38e7*temp,1.e3),1.e6) ;
#endif
     }
     rmstep = 1./mstep ;
   
     int n ;
     float dtcldden, coeres, rdelz ;


     float den_k, falk1_k, falk1_kp1, fall1_k, fall1_kp1, delz_k, delz_kp1 ;
     float        falk2_k, falk2_kp1, fall2_k, fall2_kp1                   ;

     for ( n = 1 ; n <= mstep ; n++ ) {
       k = kpe - 1 ;
       den_k = den[P3(ti,k,tj)] ;
       falk1_kp1 = den_k*qr[P3(ti,k,tj)]*w1[k]*rmstep ;
       fall1_kp1 = falk1_kp1 ;
       falk2_kp1 = den_k*qs[P3(ti,k,tj)]*w2[k]*rmstep ;
       fall2_kp1 = falk2_kp1 ;
       dtcldden = dtcld/den_k ;
       qr[P3(ti,k,tj)] = MAX(qr[P3(ti,k,tj)]-falk1_kp1*dtcldden,0.0) ;
       qs[P3(ti,k,tj)] = MAX(qs[P3(ti,k,tj)]-falk2_kp1*dtcldden,0.0) ;
       delz_kp1 = delz[P3(ti,k,tj)] ;
       for ( k = kpe-2 ; k >= kps-1 ; k-- ) {
         den_k = den[P3(ti,k,tj)] ;
         falk1_k = den_k*qr[P3(ti,k,tj)]*w1[k]*rmstep ;
         fall1_k = falk1_k ;
         falk2_k = den_k*qs[P3(ti,k,tj)]*w2[k]*rmstep ;
         fall2_k = falk2_k ;
         dtcldden = dtcld/den_k ;
         delz_k = delz[P3(ti,k,tj)] ;
         rdelz = 1./delz_k ;
         qr[P3(ti,k,tj)] = MAX(qr[P3(ti,k,tj)]- (falk1_k-falk1_kp1*delz_kp1*rdelz)* dtcldden,0.) ;
         qs[P3(ti,k,tj)] = MAX(qs[P3(ti,k,tj)]- (falk2_k-falk2_kp1*delz_kp1*rdelz)* dtcldden,0.) ;
         delz_kp1 = delz_k ;
         falk1_kp1 = falk1_k ;
         fall1_kp1 = fall1_k ;
         falk2_kp1 = falk2_k ;
         fall2_kp1 = fall2_k ;
       }

       for ( k = kpe-1 ; k >= kps-1 ; k-- ) {
         if ( t[k] > t0c && qs[P3(ti,k,tj)] > 0.) {
           xlf = xlf0 ;
           w3[k] = VENFAC(p[P3(ti,k,tj)],t[k],den[P3(ti,k,tj)]) ;
           coeres = rslope2s[k]*sqrt(rslopes[k]*rslopebs[2]) ;
           psmlt_reg = XKA(t[k],den[P3(ti,k,tj)])/xlf*(t0c-t[k])*pi/2.
                     *n0sfac[k]*(precs1*rslope2s[k]+precs2
                     *w3[k]*coeres) ;
           psmlt_reg = MIN(MAX(psmlt_reg*dtcld*rmstep,-qs[P3(ti,k,tj)]*rmstep),0.) ;
           qs[P3(ti,k,tj)] += psmlt_reg ;
           qr[P3(ti,k,tj)] -= psmlt_reg ;
           t[k] += xlf/CPMCAL(q[P3(ti,k,tj)])*psmlt_reg ;
         }
       }
     }

//---------------------------------------------------------------
// Vice [ms-1] : fallout of ice crystal [HDC 5a]
//---------------------------------------------------------------
     mstep = 1 ;
     numdt = 1 ;
     for ( k = kpe-1 ; k >= kps-1 ; k-- ) {
       if (qi[P3(ti,k,tj)] <= 0.) {
         w2[k] = 0. ;
       } else {
         xmi = den[P3(ti,k,tj)]*qi[P3(ti,k,tj)]/xni[k] ;
         diameter  = MAX(MIN(dicon * sqrt(xmi),dimax), 1.e-25) ;
         w1[k] = 1.49e4*exp(log(diameter)*(1.31)) ;
         w2[k] = w1[k]/delz[P3(ti,k,tj)] ;
       }
       numdt = MAX( (int) trunc(w2[k]*dtcld+.5+.5),1) ;
       if(numdt > mstep) mstep = numdt ;
     }
     rmstep = 1./mstep ;

     float falkc_k, falkc_kp1, fallc_k, fallc_kp1 ;
     for ( n = 1 ; n <= mstep ; n++ ) {
       k = kpe - 1 ;
       den_k = den[P3(ti,k,tj)] ;
       falkc_kp1 = den_k*qi[P3(ti,k,tj)]*w2[k]*rmstep ;
       fallc_kp1 = fallc_kp1+falkc_kp1 ;
       qi[P3(ti,k,tj)] = MAX(qi[P3(ti,k,tj)]-falkc_kp1*dtcld/den_k,0.) ;
       delz_kp1 = delz[P3(ti,k,tj)] ;
       for ( k = kpe-2 ; k >= kps-1 ; k-- ) {
         den_k = den[P3(ti,k,tj)] ;
         falkc_k = den_k*qi[P3(ti,k,tj)]*w2[k]*rmstep ;
         fallc_k = fallc_k+falkc_k ;
         delz_k = delz[P3(ti,k,tj)] ;
         qi[P3(ti,k,tj)] = MAX(qi[P3(ti,k,tj)]-(falkc_k-falkc_kp1
                 *delz_kp1/delz_k)*dtcld/den_k,0.) ;
         delz_kp1 = delz_k ;
         falkc_kp1 = falkc_k ;
         fallc_kp1 = fallc_k ;
       }
     }
     float fallsum = fall1_k+fall2_k+fallc_k ;
     float fallsum_qsi = fall2_k+fallc_k ;

     rainncv[P2(ti,tj)] = 0. ;
     if(fallsum > 0.) {
       rainncv[P2(ti,tj)] = fallsum*delz[P3(ti,1,tj)]/denr*dtcld*1000. ;
       rain[P2(ti,tj)] = fallsum*delz[P3(ti,1,tj)]/denr*dtcld*1000. + rain[P2(ti,tj)] ;
     }
     snowncv[P2(ti,tj)] = 0. ;
     if(fallsum_qsi > 0.) {
       snowncv[P2(ti,tj)] = fallsum_qsi*delz[P3(ti,0,tj)]/denr*dtcld*1000. ;
       snow[P2(ti,tj)] = fallsum_qsi*delz[P3(ti,0,tj)]/denr*dtcld*1000. + snow[P2(ti,tj)] ;
     }
     sr[P2(ti,tj)] = 0. ;
     if ( fallsum > 0. ) sr[P2(ti,tj)] = fallsum_qsi*delz[P3(ti,0,tj)]/denr*dtcld*1000./(rainncv[P2(ti,tj)]+1.e-12) ;

//---------------------------------------------------------------
// pimlt: instantaneous melting of cloud ice [HL A47] [RH83 A28]
//       (T>T0: I->C)
//---------------------------------------------------------------


     for ( k = kps-1 ; k <= kpe-1 ; k++ ) {

       //  note -- many of these are turned into scalars of form name_reg by _def_ above
       //  so that they will be stored in registers
       prevp_reg = 0. ;
       psdep_reg = 0. ;
       praut_reg = 0. ;
       psaut_reg = 0. ;
       pracw_reg = 0. ;
       psaci_reg = 0. ;
       psacw_reg = 0. ;
       pigen_reg = 0. ;
       pidep_reg = 0. ;
       pcond_reg = 0. ;
       psevp_reg = 0. ;

       q_k =  q[P3(ti,k,tj)] ;
       t_k = t[k] ;
       qr_k =  qr[P3(ti,k,tj)] ;
       qc_k = qc[P3(ti,k,tj)] ;
       qs_k = qs[P3(ti,k,tj)] ;
       qi_k = qi[P3(ti,k,tj)] ;
       qs1_k = qs1[k] ;
       qs2_k = qs2[k] ;
       cpm_k = cpm[k] ;
       xl_k = xl[k] ;
      
       float supcol = t0c-t_k ;
       xlf = xls-xl_k ;
       if( supcol < 0. ) xlf = xlf0 ;
       if( supcol < 0 && qi_k > 0. ) {
         qc_k = qc_k + qi_k ;
         t_k = t_k - xlf/cpm_k*qi_k ;
         qi_k = 0. ;
       }
//---------------------------------------------------------------
// pihmf: homogeneous freezing of cloud water below -40c [HL A45]
//        (T<-40C: C->I)
//---------------------------------------------------------------
       if( supcol > 40. && qc_k > 0. ) {
         qi_k = qi_k + qc_k ;
         t_k = t_k + xlf/cpm_k*qc_k ;
         qc_k = 0. ;
       }
//---------------------------------------------------------------
// pihtf: heterogeneous freezing of cloud water [HL A44]
//        (T0>T>-40C: C->I)
//---------------------------------------------------------------
       if ( supcol > 0. && qc_k > 0.) {
         float pfrzdtc = MIN(pfrz1*(exp(pfrz2*supcol)-1.)
           *den[P3(ti,k,tj)]/denr/xncr*qc_k*qc_k*dtcld,qc_k) ;
         qi_k = qi_k + pfrzdtc ;
         t_k = t_k + xlf/cpm_k*pfrzdtc ;
         qc_k = qc_k-pfrzdtc ;
       }
//---------------------------------------------------------------
// psfrz: freezing of rain water [HL A20] [LFO 45]
//        (T<T0, R->S)
//---------------------------------------------------------------
       if( supcol > 0. && qr_k > 0. ) {
         float temp = rsloper[k] ;
         temp = temp*temp*temp*temp*temp*temp*temp ;
         float pfrzdtr = MIN(20.*(pi*pi)*pfrz1*n0r*denr/den[P3(ti,k,tj)]
               *(exp(pfrz2*supcol)-1.)*temp*dtcld,
               qr_k) ;
         qs_k = qs_k + pfrzdtr ;
         t_k = t_k + xlf/cpm_k*pfrzdtr ;
         qr_k = qr_k-pfrzdtr ;
       }

//----------------------------------------------------------------
//     rsloper: reverse of the slope parameter of the rain(m)
//     xka:    thermal conductivity of air(jm-1s-1k-1)
//     work1:  the thermodynamic term in the denominator associated with
//             heat conduction and vapor diffusion
//             (ry88, y93, h85)
//     work2: parameter associated with the ventilation effects(y93)

       n0sfac[k] = MAX(MIN(exp(alpha*supcol),n0smax/n0s),1.) ;
       if ( qr_k <= qcrmin ) {
         rsloper[k]  = rslopermax ;
         rslopebr[k] = rsloperbmax ;
         rslope2r[k] = rsloper2max ;
         rslope3r[k] = rsloper3max ;
       } else {
         rsloper[k] = 1./(sqrt(sqrt(pidn0r/((qr_k)*(den[P3(ti,k,tj)]))))) ;
         rslopebr[k] = exp(log(rsloper[k])*bvtr) ;
         rslope2r[k] = rsloper[k] * rsloper[k] ;
         rslope3r[k] = rslope2r[k] * rsloper[k] ;
       }
       if ( qs_k <= qcrmin ) {
         rslopes[k]  = rslopesmax ;
         rslopebs[k] = rslopesbmax ;
         rslope2s[k] = rslopes2max ;
         rslope3s[k] = rslopes3max ;
       } else {
         rslopes[k] = 1./(sqrt(sqrt(pidn0s*(n0sfac[k])/((qs_k)*(den[P3(ti,k,tj)]))))) ;
         rslopebs[k] = exp(log(rslopes[k])*bvts) ;
         rslope2s[k] = rslopes[k] * rslopes[k] ;
         rslope3s[k] = rslope2s[k] * rslopes[k] ;
       }

       w1_k = DIFFAC(xl_k,p[P3(ti,k,tj)],t_k,den[P3(ti,k,tj)],qs1_k) ;
       w2_k = DIFFAC(xls,p[P3(ti,k,tj)],t_k,den[P3(ti,k,tj)],qs2_k) ;
       w3_k = VENFAC(p[P3(ti,k,tj)],t_k,den[P3(ti,k,tj)]) ;

//
//===============================================================
//
// warm rain processes
//
// - follows the processes in RH83 and LFO except for autoconcersion
//
//===============================================================
//
      float supsat = MAX(q_k,qmin)-qs1_k ;
      float satdt = supsat/dtcld ;
//---------------------------------------------------------------
// praut: auto conversion rate from cloud to rain [HDC 16]
//        (C->R)
//---------------------------------------------------------------
      if(qc_k > qc0) {
        praut_reg = qck1*exp(log(qc_k)*((7./3.))) ;
        praut_reg = MIN(praut_reg,qc_k/dtcld) ;
      }
//---------------------------------------------------------------
// pracw: accretion of cloud water by rain [HL A40] [LFO 51]
//        (C->R)
//---------------------------------------------------------------
      if(qr_k > qcrmin && qc_k > qmin) {
        pracw_reg = MIN(pacrr*rslope3r[k]*rslopebr[k]
                   *qc_k*denfac[k],qc_k/dtcld) ;
      }
//---------------------------------------------------------------
// prevp: evaporation/condensation rate of rain [HDC 14]
//        (V->R or R->V)
//---------------------------------------------------------------
      if(qr_k > 0.) {
        coeres = rslope2r[k]*sqrt(rsloper[k]*rslopebr[k]) ;
        prevp_reg = (rh1[k]-1.)*(precr1*rslope2r[k]
                     +precr2*w3_k*coeres)/w1_k ;
        if(prevp_reg < 0.) {
          prevp_reg = MAX(prevp_reg,-qr_k/dtcld) ;
          prevp_reg = MAX(prevp_reg,satdt/2) ;
        } else {
          prevp_reg = MIN(prevp_reg,satdt/2) ;
        }
      }

//
//===============================================================
//
// cold rain processes
//
// - follows the revised ice microphysics processes in HDC
// - the processes same as in RH83 and RH84  and LFO behave
//   following ice crystal hapits defined in HDC, inclduing
//   intercept parameter for snow (n0s), ice crystal number
//   concentration (ni), ice nuclei number concentration
//   (n0i), ice diameter (d)
//
//===============================================================
//
          float rdtcld = 1./dtcld ;
          supsat = MAX(q_k,qmin)-qs2_k ;
          satdt = supsat/dtcld ;
          int ifsat = 0 ;
//-------------------------------------------------------------
// Ni: ice crystal number concentraiton   [HDC 5c]
//-------------------------------------------------------------
          float temp = (den[P3(ti,k,tj)]*MAX(qi_k,qmin)) ;
          temp = sqrt(sqrt(temp*temp*temp)) ;
          xni[k] = MIN(MAX(5.38e7*temp,1.e3),1.e6) ;
          float eacrs = exp(0.07*(-supcol)) ;
//-------------------------------------------------------------
// psacw: Accretion of cloud water by snow  [HL A7] [LFO 24]
//        (T<T0: C->S, and T>=T0: C->R)
//-------------------------------------------------------------
          if(qs_k > qcrmin && qc_k > qmin) {
            psacw_reg = MIN(pacrc*n0sfac[k]*rslope3s[k] 
                         *rslopebs[k]*qc_k*denfac[k]
                         ,qc_k*rdtcld) ;
          }
//
          if(supcol > 0) {
            if(qs_k > qcrmin && qi_k > qmin) {
              xmi = den[P3(ti,k,tj)]*qi_k/xni[k] ;
              diameter  = MIN(dicon * sqrt(xmi),dimax) ;
              vt2i = 1.49e4*pow(diameter,(float)1.31) ;
              vt2s = pvts*rslopebs[k]*denfac[k] ;
//-------------------------------------------------------------
// psaci: Accretion of cloud ice by rain [HDC 10]
//        (T<T0: I->S)
//-------------------------------------------------------------
              acrfac = 2.*rslope3s[k]+2.*diameter*rslope2s[k]
                      +diameter*diameter*rslopes[k] ;
              psaci_reg = pi*qi_k*eacrs*n0s*n0sfac[k]
                           *abs(vt2s-vt2i)*acrfac*.25 ;
            }
//-------------------------------------------------------------
// pidep: Deposition/Sublimation rate of ice [HDC 9]
//       (T<T0: V->I or I->V)
//-------------------------------------------------------------
            if(qi_k > 0 && ifsat != 1) {
              xmi = den[P3(ti,k,tj)]*qi_k/xni[k] ;
              diameter = dicon * sqrt(xmi) ;
              pidep_reg = 4.*diameter*xni[k]*(rh2[k]-1.)/w2_k ;
              supice = satdt-prevp_reg ;
              if(pidep_reg < 0.) {
                pidep_reg = MAX(MAX(pidep_reg,satdt*.5),supice) ;
                pidep_reg = MAX(pidep_reg,-qi_k*rdtcld) ;
              } else {
                pidep_reg = MIN(MIN(pidep_reg,satdt*.5),supice) ;
              }
              if(abs(prevp_reg+pidep_reg) >= abs(satdt)) ifsat = 1 ;
            }
//-------------------------------------------------------------
// psdep: deposition/sublimation rate of snow [HDC 14]
//        (V->S or S->V)
//-------------------------------------------------------------
            if( qs_k > 0. && ifsat != 1) {
              coeres = rslope2s[k]*sqrt(rslopes[k]*rslopebs[k]) ;
              psdep_reg = (rh2[k]-1.)*n0sfac[k]
                           *(precs1*rslope2s[k]+precs2
                           *w3_k*coeres)/w2_k ;
              supice = satdt-prevp_reg-pidep_reg ;
              if(psdep_reg < 0.) {
                psdep_reg = MAX(psdep_reg,-qs_k*rdtcld) ;
                psdep_reg = MAX(MAX(psdep_reg,satdt*.5),supice) ;
              } else {
                psdep_reg = MIN(MIN(psdep_reg,satdt*.5),supice) ;
              }
              if(abs(prevp_reg+pidep_reg+psdep_reg) >= abs(satdt))
                ifsat = 1 ;
            }
//-------------------------------------------------------------
// pigen: generation(nucleation) of ice from vapor [HL A50] [HDC 7-8]
//       (T<T0: V->I)
//-------------------------------------------------------------
            if(supsat > 0 && ifsat != 1) {
              supice = satdt-prevp_reg-pidep_reg-psdep_reg ; 
              xni0 = 1.e3*exp(0.1*supcol) ;
              roqi0 = 4.92e-11*exp(log(xni0)*(1.33));
              pigen_reg = MAX(0.,(roqi0/den[P3(ti,k,tj)]-MAX(qi_k,0.))
                         *rdtcld) ;
              pigen_reg = MIN(MIN(pigen_reg,satdt),supice) ;
            }
//
//-------------------------------------------------------------
// psaut: conversion(aggregation) of ice to snow [HDC 12]
//       (T<T0: I->S)
//-------------------------------------------------------------
            if(qi_k > 0.) {
              qimax = roqimax/den[P3(ti,k,tj)] ;
              psaut_reg = MAX(0.,(qi_k-qimax)*rdtcld) ;
            }
          }
//-------------------------------------------------------------
// psevp: Evaporation of melting snow [HL A35] [RH83 A27]
//       (T>T0: S->V)
//-------------------------------------------------------------
          if(supcol < 0.) {
            if(qs_k > 0. && rh1[k] < 1.) {
              psevp_reg = psdep_reg*w2_k/w1_k ;
            }  // asked Jimy about this, 11.6.07, JM
            psevp_reg = MIN(MAX(psevp_reg,-qs_k*rdtcld),0.) ;
          }


//
//
//----------------------------------------------------------------
//     check mass conservation of generation terms and feedback to the
//     large scale
//
          if(t_k<=t0c) {
//
//     cloud water
//
            value = MAX(qmin,qc_k) ;
            source = (praut_reg+pracw_reg+psacw_reg)*dtcld ;
            if (source > value) {
              factor = value/source ;
              praut_reg = praut_reg*factor ;
              pracw_reg = pracw_reg*factor ;
              psacw_reg = psacw_reg*factor ;
            }
//
//     cloud ice
//
            value = MAX(qmin,qi_k) ;
            source = (psaut_reg+psaci_reg-pigen_reg-pidep_reg)*dtcld ;
            if (source > value) {
              factor = value/source ;
              psaut_reg = psaut_reg*factor ;
              psaci_reg = psaci_reg*factor ;
              pigen_reg = pigen_reg*factor ;
              pidep_reg = pidep_reg*factor ;
            }

//
//     rain (added for WRFV3.0.1)
//
            value = MAX(qmin,qr_k) ;
            source = (-praut_reg+pracw_reg-prevp_reg)*dtcld ;
            if (source > value) {
              factor = value/source ;
              praut_reg = praut_reg*factor ;
              pracw_reg = pracw_reg*factor ;
              prevp_reg = prevp_reg*factor ;
            }
//
//     snow (added for WRFV3.0.1)
//
            value = MAX(qmin,qs_k) ;
            source = (-psdep_reg+psaut_reg-psaci_reg-psacw_reg)*dtcld ;
            if (source > value) {
              factor = value/source ;
              psdep_reg = psdep_reg*factor ;
              psaut_reg = psaut_reg*factor ;
              psaci_reg = psaci_reg*factor ;
              psacw_reg = psacw_reg*factor ;
            }
//     (end added for WRFV3.0.1)

//
            w3_k=-(prevp_reg+psdep_reg+pigen_reg+pidep_reg) ;
//     update
            q_k = q_k+w3_k*dtcld ;
            qc_k = MAX(qc_k-(praut_reg+pracw_reg+psacw_reg)*dtcld,0.) ;
            qr_k = MAX(qr_k+(praut_reg+pracw_reg+prevp_reg)*dtcld,0.) ;
            qi_k = MAX(qi_k-(psaut_reg+psaci_reg-pigen_reg-pidep_reg)*dtcld,0.) ;
            qs_k = MAX(qs_k+(psdep_reg+psaut_reg+psaci_reg+psacw_reg)*dtcld,0.) ;
            xlf = xls-xl_k ;
            xlwork2 = -xls*(psdep_reg+pidep_reg+pigen_reg)-xl_k*prevp_reg-xlf*psacw_reg ;
            t_k = t_k-xlwork2/cpm_k*dtcld ;
          } else {
//
//     cloud water
//
            value = MAX(qmin,qc_k) ;
            source=(praut_reg+pracw_reg+psacw_reg)*dtcld ;
            if (source > value) {
              factor = value/source ;
              praut_reg = praut_reg*factor ;
              pracw_reg = pracw_reg*factor ;
              psacw_reg = psacw_reg*factor ;
            }
//
//     rain (added for WRFV3.0.1)
//
            value = MAX(qmin,qr_k) ;
            source = (-praut_reg-pracw_reg-prevp_reg-psacw_reg)*dtcld ;
            if (source > value) {
              factor = value/source ;
              praut_reg = praut_reg*factor ;
              pracw_reg = pracw_reg*factor ;
              prevp_reg = prevp_reg*factor ;
              psacw_reg = psacw_reg*factor ;
            }
//     (end added for WRFV3.0.1)
//
//     snow
//
            value = MAX(qcrmin,qs_k) ;
            source=(-psevp_reg)*dtcld ;
            if (source > value) {
              factor = value/source ;
              psevp_reg = psevp_reg*factor ;
            }
            w3_k=-(prevp_reg+psevp_reg) ;
//     update
            q_k = q_k+w3_k*dtcld ;
            qc_k = MAX(qc_k-(praut_reg+pracw_reg+psacw_reg)*dtcld,0.) ;
            qr_k = MAX(qr_k+(praut_reg+pracw_reg+prevp_reg +psacw_reg)*dtcld,0.) ;
            qs_k = MAX(qs_k+psevp_reg*dtcld,0.) ;
            xlf = xls-xl_k ;
            xlwork2 = -xl_k*(prevp_reg+psevp_reg) ;
            t_k = t_k-xlwork2/cpm_k*dtcld ;
          }
//
// Inline expansion for fpvs
          cvap = cpv ;
          ttp=t0c+0.01 ;
          dldt=cvap-cliq ;
          xa=-dldt/rv ;
          xb=xa+hvap/(rv*ttp) ;
          dldti=cvap-cice ;
          xai=-dldti/rv ;
          xbi=xai+hsub/(rv*ttp) ;
          tr=ttp/t_k ;
          qs1_k=psat*exp(log(tr)*(xa))*exp(xb*(1.-tr)) ;
          qs1_k = ep2 * qs1_k / (p[P3(ti,k,tj)] - qs1_k) ;
          qs1_k = MAX(qs1_k,qmin) ;
//
//----------------------------------------------------------------
//  pcond: condensational/evaporational rate of cloud water [HL A46] [RH83 A6]
//     if there exists additional water vapor condensated/if
//     evaporation of cloud water is not enough to remove subsaturation
//
          w1_k = ((MAX(q_k,qmin)-(qs1_k)) /
            (1.+(xl_k)*(xl_k)/(rv*(cpm_k))*(qs1_k)/((t_k)*(t_k)))) ;
          // w3_k = qc_k+w1_k ;   NOT USED
          pcond_reg = MIN(MAX(w1_k/dtcld,0.),MAX(q_k,0.)/dtcld) ;
          if(qc_k > 0. && w1_k < 0.) {
            pcond_reg = MAX(w1_k,-qc_k)/dtcld ;
          }
          q_k = q_k-pcond_reg*dtcld ;
          qc_k = MAX(qc_k+pcond_reg*dtcld,0.) ;
          t_k = t_k+pcond_reg*xl_k/cpm_k*dtcld ;
//
//
//----------------------------------------------------------------
//     padding for small values
//
          if(qc_k <= qmin) qc_k = 0.0 ;
          if(qi_k <= qmin) qi_k = 0.0 ;

          q[P3(ti,k,tj)] = q_k ;
          t[k] = t_k ;
          qr[P3(ti,k,tj)] = qr_k ;
          qc[P3(ti,k,tj)] = qc_k ;
          qs[P3(ti,k,tj)] = qs_k ;
          qi[P3(ti,k,tj)] = qi_k ;
          qs1[k] = qs1_k ;

     }
   }
   for ( k = kps-1 ; k <= kpe-1 ; k++ ) {
          th[P3(ti,k,tj)] = t[k] / pii[P3(ti,k,tj)] ;
   }
 } // guard 
}


