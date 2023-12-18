#include "./g_configurations.h"
#include "./l_calculations-definitions.h"
#include "./g_environment-class.h"

void calculateTraces(Envi* p){
    int r = HELIX_RADIUS;
    double rad_step = 0;
    int old_r = 0;
    int x = MAIN_WINDOW_WIDTH/2;
    int y = MAIN_WINDOW_HEIGHT/2 - r;
    p->hx[0].pos.x = x;
    p->hx[0].pos.y = y;
    p->hx[0].width = r*2;
    p->hx[0].height = r*2;
    double deg = M_PI;
    for(int j = 0; j<STEPS_PER_ARC; j++){
        p->in_Helix.trajectory[j].x = x + r + r*cos(deg);
        p->in_Helix.trajectory[j].y = y + r + r*sin(deg);
        deg-=RAD_STEP;
    }
    int state = 1;
    for(int i = 0,k = STEPS_PER_ARC; i < HELIX_ARCS; i++,state = -state){
        old_r = r;
        r+=ARC_DELTA;
        if(!(i%2)){
            x = x + 2 * (old_r - r);
        }
        y = MAIN_WINDOW_HEIGHT/2 - r;
        for(int j = 0; j<STEPS_PER_ARC; j++, k++){
            p->in_Helix.trajectory[k].x = x + r + r*cos(deg);
            p->in_Helix.trajectory[k].y = y + r + (-state)*(r*sin(deg));
            deg= deg + state * RAD_STEP;
        }
        p->hx[i+1].pos.x = x;
        p->hx[i+1].pos.y = y;
        p->hx[i+1].width = r*2;
        p->hx[i+1].height = r*2;
    }
    old_r = r;
    r+=ARC_DELTA;
    x = x + 2 * (old_r - r);
    y = MAIN_WINDOW_HEIGHT/2 - r;
        for(int j = 0,k=4*STEPS_PER_ARC+STEPS_PER_ARC ;j<STEPS_PER_ARC/2; j++, k++){
            p->in_Helix.trajectory[k].x = x + r + r*cos(deg);
            p->in_Helix.trajectory[k].y = y + r + (-state)*(r*sin(deg));
            deg= deg + state * RAD_STEP;
        }
    p->hx[HELIX_ARCS+1].pos.x = x;
    p->hx[HELIX_ARCS+1].pos.y = y;
    p->hx[HELIX_ARCS+1].width = r*2;
    p->hx[HELIX_ARCS+1].height = r*2;
}

int limit_exceded(int orb_count){
    if(orb_count==ORB_LIMIT){
        return 1;
    }
    return 0;
}

int is_collision(XRectangle* c){
    double dx = pow((c[0].x-c[1].x),2);
    double dy = pow((c[0].y-c[1].y),2);
    double dist = fabs(sqrt(dx+dy));
    fprintf(stderr,"{dist:} %lf\n", dist);
    if(dist <=HELIX_ORB_RADIUS*2 ){
        return 1;
    } else if ( c[1].x <= 0  || c[1].y <= 0 ){
        return 1;
    } else if (c[1].x + HELIX_ORB_RADIUS*2 >= MAIN_WINDOW_WIDTH  || c[1].y + HELIX_ORB_RADIUS*2 >= MAIN_WINDOW_HEIGHT){
        return 1;
    }
    return 0;
}


XRectangle special_next_trace(XRectangle source, XRectangle dest){
    XRectangle step;
    double rad = atan2(source.y - dest.y,source.x - dest.x);
    step.x = source.x + CUSTOM_STEP * -cos(rad);
    step.y = source.y + CUSTOM_STEP * -sin(rad);
    return step;
}

XRectangle default_next_trace(XRectangle source, double rad){
    XRectangle step;
    step.x = source.x + CUSTOM_STEP * cos(rad);
    step.y = source.y + CUSTOM_STEP * sin(rad);
    return step;
}