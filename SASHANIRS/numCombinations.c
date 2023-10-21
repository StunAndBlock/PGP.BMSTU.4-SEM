#include "combinations.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


unsigned char keycontrol(unsigned int keycode, winEnv *env) {
  switch (keycode) {
  case K_ESC:
    return 0;
    break;
  case ALT:
    break;
  default:
    break;
  }
}


void arrangeForm(winEnv *env,Cb* comb){
  /* FORM N1 */
  XDrawString(env->dpy, env->forms[0].win, env->gc_C,env->forms[0].C.x,env->forms[0].C.y, comb->C, 1);
  XDrawString(env->dpy, env->forms[0].win, env->gc_Num,env->forms[0].brace_1.x,env->forms[0].brace_1.y, comb->brace_1, 1);
  XDrawString(env->dpy, env->forms[0].win, env->gc_Num,env->forms[0].n.x,env->forms[0].n.y, comb->n_str, comb->n_len);
  XDrawString(env->dpy, env->forms[0].win, env->gc_Num,env->forms[0].comma.x,env->forms[0].comma.y, comb->comma, 1);
  XDrawString(env->dpy, env->forms[0].win, env->gc_Num,env->forms[0].m.x,env->forms[0].m.y, comb->m_str, comb->m_len);
  XDrawString(env->dpy, env->forms[0].win, env->gc_Num,env->forms[0].brace_2.x,env->forms[0].brace_2.y, comb->brace_2, 1);
  /* FORM N1 _END */
  /* FORM N2 */
  XDrawString(env->dpy, env->forms[1].win, env->gc_C,env->forms[1].C.x,env->forms[1].C.y, comb->C, 1);
  XDrawString(env->dpy, env->forms[1].win, env->gc_Num,env->forms[1].m.x,env->forms[1].m.y, comb->m_str, comb->m_len);
  XDrawString(env->dpy, env->forms[1].win, env->gc_Num,env->forms[1].n.x,env->forms[1].n.y, comb->n_str, comb->n_len);
  /* FROM N2 _END */
  /* FORM N3 */
  XDrawString(env->dpy, env->forms[2].win, env->gc_Num,env->forms[2].m.x,env->forms[2].m.y, comb->m_str, comb->m_len);
  XDrawString(env->dpy, env->forms[2].win, env->gc_Num,env->forms[2].n.x,env->forms[2].n.y, comb->n_str, comb->n_len);
  XDrawString(env->dpy, env->forms[2].win, env->gc_C,env->forms[2].brace_1.x,env->forms[2].brace_1.y, comb->brace_1, 1);
  XDrawString(env->dpy, env->forms[2].win, env->gc_C,env->forms[2].brace_2.x,env->forms[2].brace_2.y, comb->brace_2, 1);
  /* FROM N3 _END */
  /* FORM N4 */
  XDrawString(env->dpy, env->forms[3].win, env->gc_C,env->forms[3].equally.x,env->forms[3].equally.y, comb->equally, 1);
  /* FROM N4 _END */
  /* FORM N5 */
  XDrawString(env->dpy, env->forms[4].win, env->gc_C,env->forms[4].result.x,env->forms[4].result.y, comb->result_str, comb->result_len);
  /* FROM N5 _END */
}

void convertString(Cb* comb){
comb->n_len= snprintf( NULL, 0, "%d", comb->n );
comb->n_str = (char*)malloc( (comb->n_len + 1)*sizeof(char) );
snprintf(comb->n_str, comb->n_len + 1, "%d", comb->n );

comb->m_len = snprintf( NULL, 0, "%d", comb->m );
comb->m_str = (char*)malloc( (comb->m_len  + 1)*sizeof(char) );
snprintf(comb->m_str, comb->m_len  + 1, "%d", comb->m );

comb->result_len = snprintf( NULL, 0, "%lld", comb->result );
comb->result_str = (char*)malloc( (comb->result_len  + 1)*sizeof(char) );
snprintf(comb->result_str, comb->result_len  + 1, "%lld", comb->result );
comb->C="C";
comb->brace_1="(";
comb->brace_2=")";
comb->comma=",";
comb->equally="=";
}
void configFonts(winEnv *env,Cb* comb){
  XFontStruct *fn;
  XFontStruct *fn_number; /* Font parameters structure */
  char font_pref[]="-bitstream-courier 10 pitch-medium-r-normal--";
  char font_suff[]="-0-0-0-m-0-iso10646-1";
  char fontname_C[] = "-bitstream-courier 10 pitch-medium-r-normal--50-0-0-0-m-0-iso10646-1";
  char* fontname_number;
  size_t x = CELL_SIZE_FORM/2;
    if (x>99){
    x=99;
  }
  size_t max_len = (comb->n_len > comb->m_len) ? comb->n_len : comb->m_len; //max
  double coef=1/sqrt(max_len*10);

  size_t number_font_size = coef * x; 
  size_t length_x = snprintf( NULL, 0, "%ld", x );
  char* x_str = malloc( length_x + 1 );
  snprintf(x_str, length_x + 1, "%ld", x);
  for (size_t i=0;i<length_x;i++){
    fontname_C[45+i]=x_str[i];
  }
  if ((fn = XLoadQueryFont(env->dpy, fontname_C)) == NULL)
    exit(-1);
  XSetFont(env->dpy, env->gc_C, fn->fid);
  free(x_str);
 

  size_t length_number_size = snprintf( NULL, 0, "%ld", number_font_size);
  char* number_font_size_str = malloc( length_number_size + 1 );
  snprintf(number_font_size_str , length_number_size + 1, "%ld", number_font_size);
  fontname_number = strcat(font_pref,number_font_size_str);
  strcat(fontname_number,font_suff);


  if ((fn_number = XLoadQueryFont(env->dpy, fontname_number)) == NULL)
    exit(-1);
  XSetFont(env->dpy, env->gc_Num, fn_number->fid);
  free(number_font_size_str);
  
  fprintf(stderr,"\n\tFONT: %s\n",fontname_number);
  /* FORM N1 */
  env->forms[0].C.width = fn->max_bounds.width;
  env->forms[0].C.height = fn->max_bounds.ascent + fn->max_bounds.descent;
  env->forms[0].C.x = (CELL_SIZE_FORM - fn->max_bounds.width) / 2 - 0.5*(fn_number->max_bounds.width * (comb->n_len+comb->m_len+3));
  env->forms[0].C.y =
      CELL_SIZE_FORM / 2 + (fn->max_bounds.ascent - fn->max_bounds.descent) / 2;

  env->forms[0].brace_1.width = fn_number->max_bounds.width;
  env->forms[0].brace_1.height = fn_number->max_bounds.ascent + fn_number->max_bounds.descent;
  env->forms[0].brace_1.x = env->forms[0].C.x + env->forms[0].C.width;
  env->forms[0].brace_1.y = env->forms[0].C.y ;

  env->forms[0].n.width = fn_number->max_bounds.width;
  env->forms[0].n.height = fn_number->max_bounds.ascent + fn_number->max_bounds.descent;
  env->forms[0].n.x = env->forms[0].brace_1.x + env->forms[0].n.width;
  env->forms[0].n.y =env->forms[0].C.y ;

  env->forms[0].comma.width = fn_number->max_bounds.width;
  env->forms[0].comma.height = fn_number->max_bounds.ascent + fn_number->max_bounds.descent;
  env->forms[0].comma.x = env->forms[0].n.x + env->forms[0].n.width*comb->n_len;
  env->forms[0].comma.y = env->forms[0].C.y ;

  env->forms[0].m.width = fn_number->max_bounds.width;
  env->forms[0].m.height = fn_number->max_bounds.ascent + fn_number->max_bounds.descent;
  env->forms[0].m.x = env->forms[0].comma.x + env->forms[0].m.width;
  env->forms[0].m.y = env->forms[0].C.y ;

  env->forms[0].brace_2.width = fn_number->max_bounds.width;
  env->forms[0].brace_2.height = fn_number->max_bounds.ascent + fn_number->max_bounds.descent;
  env->forms[0].brace_2.x = env->forms[0].m.x + env->forms[0].m.width * comb->m_len;
  env->forms[0].brace_2.y = env->forms[0].C.y ;

  /* FORM N1 _END */
  /* FORM N2*/
  env->forms[1].C.width = fn->max_bounds.width;
  env->forms[1].C.height = fn->max_bounds.ascent + fn->max_bounds.descent;
  env->forms[1].C.x = (CELL_SIZE_FORM - fn->max_bounds.width) / 3;
  env->forms[1].C.y =
      CELL_SIZE_FORM / 2 + (fn->max_bounds.ascent - fn->max_bounds.descent) / 2;

  env->forms[1].m.width = fn_number->max_bounds.width;
  env->forms[1].m.height = fn_number->max_bounds.ascent + fn_number->max_bounds.descent;
  env->forms[1].m.x = env->forms[1].C.x + env->forms[1].C.width;
  env->forms[1].m.y =env->forms[1].C.y - (fn->max_bounds.ascent-fn->max_bounds.descent);

  env->forms[1].n.width = fn_number->max_bounds.width;
  env->forms[1].n.height = fn_number->max_bounds.ascent + fn_number->max_bounds.descent;
  env->forms[1].n.x = env->forms[1].C.x + env->forms[1].C.width;
  env->forms[1].n.y =env->forms[1].C.y + (fn_number->max_bounds.ascent + fn_number->max_bounds.descent)/2;
  /* FORM N2 _END */
  /* FORM N3 */

  env->forms[2].m.width = fn_number->max_bounds.width;
  env->forms[2].m.height = fn_number->max_bounds.ascent + fn_number->max_bounds.descent;
  env->forms[2].m.x = (CELL_SIZE_FORM - env->forms[2].m.width* comb->m_len) / 2;
  env->forms[2].m.y = CELL_SIZE_FORM / 2 + (fn->max_bounds.ascent - fn->max_bounds.descent)/2;

  env->forms[2].n.width = fn_number->max_bounds.width;
  env->forms[2].n.height = fn_number->max_bounds.ascent + fn_number->max_bounds.descent;
  env->forms[2].n.x = (CELL_SIZE_FORM - env->forms[2].n.width* comb->n_len) / 2;
  env->forms[2].n.y =  CELL_SIZE_FORM / 2 ;


  env->forms[2].brace_1.width = fn->max_bounds.width;
  env->forms[2].brace_1.height = fn->max_bounds.ascent + fn->max_bounds.descent;
  env->forms[2].brace_1.x = (CELL_SIZE_FORM - env->forms[2].m.width* max_len) / 2 -env->forms[2].brace_1.width;
  env->forms[2].brace_1.y =
      CELL_SIZE_FORM / 2 + (fn->max_bounds.ascent - fn->max_bounds.descent) / 2;

  env->forms[2].brace_2.width = fn->max_bounds.width;
  env->forms[2].brace_2.height = fn->max_bounds.ascent + fn->max_bounds.descent;
  env->forms[2].brace_2.x = (CELL_SIZE_FORM + env->forms[2].m.width* max_len) / 2 ;
  env->forms[2].brace_2.y =
      CELL_SIZE_FORM / 2 + (fn->max_bounds.ascent - fn->max_bounds.descent) / 2;
  /* FORM N3 _END */
  /* FORM N4 */
  env->forms[3].equally.width = fn->max_bounds.width;
  env->forms[3].equally.height = fn->max_bounds.ascent + fn->max_bounds.descent;
  env->forms[3].equally.x = (CELL_SIZE_FORM - fn->max_bounds.width) / 2;
  env->forms[3].equally.y =
      CELL_SIZE_FORM / 2 + (fn->max_bounds.ascent - fn->max_bounds.descent) / 2;
  /* FORM N4 _END */
  /* FORM N5 */
  env->forms[4].result.width = fn->max_bounds.width;
  env->forms[4].result.height = fn->max_bounds.ascent + fn->max_bounds.descent;
  env->forms[4].result.x = (ceil(comb->result_len/3.0)*CELL_SIZE_FORM - fn->max_bounds.width*comb->result_len) / 2;
  env->forms[4].result.y =
      CELL_SIZE_FORM / 2 + (fn->max_bounds.ascent - fn->max_bounds.descent) / 2;
  /* FORM N5 _END */


  XFreeFont(env->dpy, fn);
  XFreeFont(env->dpy, fn_number);
}