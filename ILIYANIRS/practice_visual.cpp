#include "practice.h"

Environment::Environment(const std::string & str):Graph(str){
  dpy = XOpenDisplay(NULL);
  scr = DefaultScreen(dpy);
  depth = DefaultDepth(dpy, scr);
  XGCValues values;
  const char* font_name="-bitstream-courier 10 pitch-medium-r-normal--20-0-0-0-m-0-iso10646-1";
  if((fn=XLoadQueryFont(dpy,font_name))==NULL){
    exit(-1);
  }
  values.foreground = BlackPixel(dpy,scr);
  values.line_width = LINE_WIDTH;
  values.font=fn->fid;
  gc_black = XCreateGC(dpy, DefaultRootWindow(dpy),(GCForeground | GCLineWidth | GCFont),&values);
  
  
  values.foreground=WhitePixel(dpy,scr);
  gc_white = XCreateGC(dpy, DefaultRootWindow(dpy),(GCForeground | GCFont),&values);
  values.foreground=0xFF0000;
  gc_red = XCreateGC(dpy, DefaultRootWindow(dpy),(GCForeground | GCLineWidth ),&values);

  XSetWindowAttributes attr; /* created Window attributes */
  XSizeHints hint;
  attr.override_redirect = False;
  attr.background_pixel = WhitePixel(dpy, scr);
  attr.event_mask = (ExposureMask | KeyPressMask);
  main_win = XCreateWindow(dpy, DefaultRootWindow(dpy), 0, 0, WIN_WIDTH,
          WIN_HEIGHT, 0, depth, InputOutput, CopyFromParent,
          (CWOverrideRedirect | CWBackPixel | CWEventMask), &attr);
  
  attr.background_pixel = WhitePixel(dpy, scr);
  option_field_win = XCreateWindow(dpy, main_win, 0, 0, OPTION_FIELD_WIDTH,
          OPTION_FILED_HEIGHT, 1, depth, InputOutput, CopyFromParent,
          (CWOverrideRedirect | CWBackPixel | CWEventMask), &attr);
  attr.event_mask = (ExposureMask | ButtonPressMask);
  draw_button_win = XCreateWindow(dpy, option_field_win, -1, -1, BUTTON_WIDTH,
          BUTTON_HEIGHT, 1, depth, InputOutput, CopyFromParent,
          (CWOverrideRedirect | CWBackPixel | CWEventMask), &attr);
  attr.event_mask = (ExposureMask);
  draw_field_win = XCreateWindow(dpy, main_win, OPTION_FIELD_WIDTH+1, 0, DRAW_FIELD_WIDTH,
          DRAW_FIELD_HEIGHT, 1, depth, InputOutput, CopyFromParent,
          (CWOverrideRedirect | CWBackPixel | CWEventMask), &attr);
  hint.flags = (PMinSize | PMaxSize | PPosition);
  hint.min_width = WIN_WIDTH;
  hint.min_height = WIN_HEIGHT;
  hint.x = 300;
  hint.y = 300;
  XSetNormalHints(dpy, main_win, &hint);
  XMapWindow(dpy, main_win);
  XMapSubwindows(dpy, main_win);     
  XMapSubwindows(dpy, option_field_win);           
}

void Environment::dispatch(size_t num_of_vertices){
  unsigned char flag = 1;
  char e = 0;
  XEvent event;

  while (flag) {
    XNextEvent(dpy, &event);
    switch (event.type) {
      break;
    case ButtonPress:
      drawTree(num_of_vertices);
      break;
    case KeyPress:
      if(event.xkey.keycode==9){
        flag=0;
      }
    default:
      drawGraph(num_of_vertices);
      break;
    }
  }
  
}

void Environment::drawGraph(size_t num_of_vertices){
  //XDrawPoints(dpy,main_win,gc_black,vertices.points,num_of_vertices,CoordModeOrigin);
  XDrawString(dpy,draw_button_win,gc_black,
  (BUTTON_WIDTH-fn->max_bounds.width*4)/2,
  (BUTTON_HEIGHT/2 + (fn->max_bounds.ascent - fn->max_bounds.descent) / 2),
  "draw",
  4);
  XDrawArcs(dpy,draw_field_win,gc_black,vertices.external_arcs,num_of_vertices);
  XFillArcs(dpy,draw_field_win,gc_black,vertices.external_arcs,num_of_vertices);
  
  std::vector<size_t> * adjacency = this->get_adjacency_matrix();
  for(size_t i = 0; i<num_of_vertices;i++){
    for(size_t j = 0;j<adjacency[i].size();j++){
      XDrawLine(dpy,draw_field_win,gc_black,vertices.points[i].x,vertices.points[i].y,
        vertices.points[adjacency[i][j]].x,vertices.points[adjacency[i][j]].y);
    }
  }
  XFillArcs(dpy,draw_field_win,gc_white,vertices.blank_arcs,num_of_vertices);
  XFillArcs(dpy,draw_field_win,gc_black,vertices.internal_arcs,num_of_vertices);
  for(size_t i = 0;i<num_of_vertices;i++){
    XDrawString(dpy,draw_field_win,gc_white,
    vertices.points[i].x-fn->max_bounds.width*vertices.vertices_numbers_str_arr[i].length()/2,
    vertices.points[i].y+(fn->max_bounds.ascent - fn->max_bounds.descent) / 2,
    vertices.vertices_numbers_str_arr[i].c_str(),vertices.vertices_numbers_str_arr[i].length());
  }
  
}

void Environment::drawTree(size_t num_of_vertices){
  std::vector<std::vector<size_t>> _tree= this->get_tree();
  std::vector<size_t> drawn;
  std::vector<XArc> external_arcs;
  std::vector<XArc> internal_arcs;
  std::vector<XArc> blank_arcs;
  XArc temp;
  for(size_t i = 0; i<_tree.size();i++){
    XDrawLine(dpy,draw_field_win,gc_red,
      vertices.points[_tree[i][0]].x,vertices.points[_tree[i][0]].y,
      vertices.points[_tree[i][1]].x,vertices.points[_tree[i][1]].y);
    if(!(std::count(drawn.begin(),drawn.end(),_tree[i][0]))){
      external_arcs.push_back(vertices.external_arcs[_tree[i][0]]);
      internal_arcs.push_back(vertices.internal_arcs[_tree[i][0]]);
      blank_arcs.push_back(vertices.blank_arcs[_tree[i][0]]);
    } else {
      drawn.push_back(_tree[i][0]);
    }
    if(!(std::count(drawn.begin(),drawn.end(),_tree[i][1]))){
      external_arcs.push_back(vertices.external_arcs[_tree[i][1]]);
      internal_arcs.push_back(vertices.internal_arcs[_tree[i][1]]);
      blank_arcs.push_back(vertices.blank_arcs[_tree[i][1]]);
    } else {
    drawn.push_back(_tree[i][1]);
    }
  }
  drawn.clear();
  XArc* ea = &external_arcs[0];
  XArc* ia = &internal_arcs[0];
  XArc* ba = &blank_arcs[0];
  XDrawArcs(dpy,draw_field_win,gc_red,ea,external_arcs.size());
  XFillArcs(dpy,draw_field_win,gc_red,ea,external_arcs.size());
  XFillArcs(dpy,draw_field_win,gc_white,ba,blank_arcs.size());
  XFillArcs(dpy,draw_field_win,gc_red,ia,internal_arcs.size());
  for(size_t i = 0;i<num_of_vertices;i++){
    XDrawString(dpy,draw_field_win,gc_white,
    vertices.points[i].x-fn->max_bounds.width*vertices.vertices_numbers_str_arr[i].length()/2,
    vertices.points[i].y+(fn->max_bounds.ascent - fn->max_bounds.descent) / 2,
    vertices.vertices_numbers_str_arr[i].c_str(),vertices.vertices_numbers_str_arr[i].length());
  }
}
	


