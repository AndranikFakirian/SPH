#include <iostream>
struct particle
{
    std::string color;
    double x, y, vx, vy, dvx, dvy, ro0, ro, dro, p, m, Wk;
};
struct ppair
{
    particle pparticle;
    double dk;
};
#include <vector>
class Particles
{
private:
    std::vector <particle> p; //Vector of particles
public:
    static long int N; //Number of particles
    static double h; //Kernel radius
    Particles (std::string c, double vx, double vy, double m, long int Num, double h); //Constructs vector with Num particles (if Num+N>maxNumOfParticles => with maxNumOfParticles-N) coordinates and velocities of which is artificially fluctuated
    Particles (std::string c, double vx, double vy, double m, long int Num); //Constructor if h is already known
    std::vector <particle> getParticles();
};
long int Particles::N=0;
double Particles::h=0;
std::vector <particle> Particles::getParticles ()
{
    return p;
}
#include <stdlib.h>
#include <time.h>
int randomize(int max, int min) //Returns value [min; max]^Z
{
    srand(time(NULL));
    return min+rand()%(max-min+1);
}

double randomize() //Returns value [0; 1]
{
    double d=0;
    for (int i=0; i<7; i++)
    {
        d*=10;
        d+=randomize(9, 0);
    }
    if (d==9999999)
        return 1;
    else
    {
        for (int i=0; i<7; i++)
        {
            d=d/10;
        }
        return d;
    }
}
#include <cmath>
double dist(particle p1, particle p2)
{
    double dr=std::pow(p1.x-p2.x, 2)+std::pow(p1.y-p2.y, 2);
    return pow(dr,0.5);
}
double Ker(particle p1, particle p2, double h)  //Kernel function //Speed - O(1)
{
    double r=dist(p1, p2);
    double e=r/h;
    double k=0.7*M_PI*h*h;
    if ((e>=2)||(e==0))
    {
        return 0;
    }
    else if (e<=1)
    {
        return std::pow(2-e,3)/(4*k);
    }
    else if (e>0)
    {
        return (1-1.5*std::pow(e, 2)+0.75*std::pow(e, 3))/k;
    }
}
double ro(std::vector <particle> liq, unsigned int ind, double h) //Computing densities of particles //Speed - O(n)
{
    double val=0;
    for (unsigned int i=0; i<liq.size(); i++)
    {
        val+=(liq[i].m*Ker(liq[ind],liq[i], h));
    }
    return val;
}
const double E_WX=1938;
const double E_WY=1156;
const unsigned E_p_length=70;
const unsigned E_p_heigth=90;
const double E_height=950.0;
const double E_indent=50.0;
const double E_width=3.0;
const double E_rad=4.0;
const double E_length=E_p_length*(E_rad+1)*2;
Particles::Particles(std::string c, double vx, double vy, double m, long int Num, double h) //Speed - O(N), memory - O(N)
{
    this->h=h;
    long tempNum=N+Num;
    long tNum=0;
    if (tempNum>E_p_heigth*E_p_length)
        tNum=E_p_heigth*E_p_length-N;
    else
        tNum=tempNum;
    p.resize(tNum);
    double x0=(E_WX-E_length)/2+1+E_rad;
    double y0=E_height+E_indent-1-E_rad;
    for (long i=0; i<tNum; i++)
    {
        particle pa;
        N++;
        pa.color=c;
        pa.vx=vx;
        pa.vy=vy;
        pa.m=m;
        pa.y=y0-(1+E_rad)*2*((N-1)/E_p_length);
        pa.x=x0+(1+E_rad)*2*(N-1-((N-1)/E_p_length)*E_p_length);
        p[i]=pa;
    }
    double ro0=0;
    for (long i=0; i<tNum; i++)
    {
        ro0+=ro(p, i, h);
    }
    ro0=ro0/Num;
    for (long i=0; i<tNum; i++)
    {
        p[i].ro0=ro0;
    }
    for (long i=0; i<tNum; i++)
    {
        double cos, sin, rad, fluc;
        rad=randomize();
        cos=randomize();
        if (randomize(0, 1)==1)
            cos*=-1;
        sin=std::sqrt(1-cos*cos);
        if (randomize(0, 1)==1)
            sin*=-1;
        p[i].x+=cos*rad;
        p[i].y+=sin*rad;
        fluc=randomize();
        if (randomize(0, 1)==1)
            fluc*=-1;
        p[i].vx+=p[i].vx/10*fluc;
        fluc=randomize();
        if (randomize(0, 1)==1)
            fluc*=-1;
        p[i].vy+=p[i].vy/10*fluc;
    }
}
Particles::Particles (std::string c, double vx, double vy, double m, long int Num) //Asymptotics are analogic
{
    Particles(c, vx, vy, m, Num, this->h);
}
class Liquid
{
private:
    std::vector <particle> liq; //Vector of particles
    std::vector <std::vector<ppair>> DK; //Table of derivatives of the kernel function for each pair of particles in the distance range (0; h)
    double h;
    double alpha; //Pulse reduction coefficient after reflection from the walls and bottom
    double k; //Pressure coefficient
    double g; //Acceleration of free fall
    double dt; //Time change
public:
    Liquid (std::vector <Particles>& P, double alpha, double k, double g, double dt);
    double DerKer (particle p1, particle p2, double h); //Derivative of Kernel function
    void fillDK();
    void Solve(); //Computing of movement
    void Starting(); //Computing of some initial values
    void Visualize(); //Visualizer
    double derRo(unsigned int ind); //Density derivative
    double derE(unsigned int ind); //Derivative of specific kinetic energy
    double derVx(unsigned int ind); //Derivatives of velocity projections on the axises
    double derVy(unsigned int ind);
    double press(unsigned int ind); //Computing pressure
    void reflector(unsigned int ind); //Reflects particles from the walls and bottom
};
Liquid::Liquid (std::vector <Particles>& P, double alpha, double k, double g, double dt): alpha(alpha), k(k), g(g), dt(dt) //Speed - O(N), memory - O(N)
{
    this->h=P[0].h;
    liq.resize(P[0].N);
    long pointer=0;
    for (long i=0; i<P.size(); i++)
    {
        for (long j=0; j<P[i].getParticles().size(); j++)
        {
            liq[pointer]=P[i].getParticles()[j];
            pointer++;
        }
    }
}
double Liquid::DerKer(particle p1, particle p2, double h) //Speed - O(1)
{
    double r=dist(p1, p2);
    double e=r/h;
    double k=2.8*M_PI*h*h*h;
    if ((e>=2)||(e==0))
    {
        return 0;
    }
    else if (e<=1)
    {
        return -3*std::pow(2-e,3)/k;
    }
    else if (e>0)
    {
        return (-12*e+9*std::pow(e, 2))/k;
    }
}
double scalar(double x1, double y1, double x2, double y2)
{
    return x1*x2+y1*y2;
}
void Liquid::fillDK() //Speed - O(n^2), memory - O(n)
{
    long i=0;
    DK.resize(liq.size());
    for (const auto &it : liq)
    {
        DK[i].resize(liq.size());
        long j=0;
        for (const auto &it1 : liq)
        {
            double dk=DerKer(it, it1, h);
            if (dk!=0)
            {
                ppair p;
                p.pparticle=it1;
                p.dk=dk;
                DK[i][j]=p;
                j++;
            }
        }
        DK[i].resize(j);
        i++;
    }
}
#include <iterator>
double Liquid::derRo(unsigned int ind) //Speed - O(1)
{
    double val=0;
    for (std::vector <ppair>::iterator ppai=DK[ind].begin(); ppai!=DK[ind].end(); ++ppai)
    {
        val+=(ppai->pparticle.m*liq[ind].ro*ppai->dk/ppai->pparticle.ro*scalar(liq[ind].vx-ppai->pparticle.vx, liq[ind].vy-ppai->pparticle.vy, liq[ind].x-ppai->pparticle.x, liq[ind].y-ppai->pparticle.y)/dist(liq[ind], ppai->pparticle));
    }
    return -1*val;
}
double Liquid::derE(unsigned int ind) //Speed - O(1)
{
    double val=0;
    for (std::vector <ppair>::iterator ppai=DK[ind].begin(); ppai!=DK[ind].end(); ++ppai)
    {
        val+=(ppai->pparticle.m*(ppai->pparticle.p+liq[ind].p)*ppai->dk/2/ppai->pparticle.ro/liq[ind].ro*scalar(liq[ind].vx-ppai->pparticle.vx, liq[ind].vy-ppai->pparticle.vy, liq[ind].x-ppai->pparticle.x, liq[ind].y-ppai->pparticle.y)/dist(liq[ind], ppai->pparticle));
    }
    return -1*val;
}
double Liquid::derVx(unsigned int ind) //Speed - O(1)
{
    double val=0;
    for (std::vector <ppair>::iterator ppai=DK[ind].begin(); ppai!=DK[ind].end(); ++ppai)
    {
        val+=(ppai->pparticle.m*(ppai->pparticle.p+liq[ind].p)*ppai->dk/ppai->pparticle.ro/liq[ind].ro*(liq[ind].x-ppai->pparticle.x)/dist(liq[ind], ppai->pparticle));
    }
    return val;
}
double Liquid::derVy(unsigned int ind) //Speed - O(1)
{
    double val=0;
    for (std::vector <ppair>::iterator ppai=DK[ind].begin(); ppai!=DK[ind].end(); ++ppai)
    {
        val+=(ppai->pparticle.m*(ppai->pparticle.p+liq[ind].p)*ppai->dk/ppai->pparticle.ro/liq[ind].ro*(liq[ind].y-ppai->pparticle.y)/dist(liq[ind], ppai->pparticle));
    }
    return val;
}
double Liquid::press(unsigned int ind) //Speed - O(1)
{
    return k*(std::pow(liq[ind].ro/liq[ind].ro0, 7)-1);
}
void Liquid::reflector(unsigned int ind)
{
    double xmin=(E_WX-E_length)/2+E_rad;
    double xmax=(E_WX+E_length)/2-E_rad;
    double ymin=E_height+E_indent-E_rad;
    if (liq[ind].x<xmin)
    {
        liq[ind].x=xmin+alpha*(xmin-liq[ind].x);
        liq[ind].vx*=-alpha;
    }
    if (liq[ind].x>xmax)
    {
        liq[ind].x=xmax+alpha*(xmax-liq[ind].x);
        liq[ind].vx*=-alpha;
    }
    if (liq[ind].y<ymin)
    {
        liq[ind].y=ymin+alpha*(ymin-liq[ind].y);
        liq[ind].vy*=-alpha;
    }
}
void Liquid::Starting() //Speed - O(N)
{
    for (long i=0; i<liq.size(); i++)
    {
        liq[i].ro=ro(liq, i, h);
        liq[i].p=press(i);
    }
}
void Liquid::Solve() //Speed - O(N)
{
    fillDK();
    for (unsigned i=0; i<liq.size(); i++)
    {
        liq[i].dro=derRo(i)*dt;
        liq[i].dvx=derVx(i)*dt;
        liq[i].dvy=(derVy(i)+g)*dt;
    }
    for (unsigned i=0; i<liq.size(); i++)
    {
        liq[i].ro+=liq[i].dro;
        liq[i].vx+=liq[i].dvx;
        liq[i].vy+=liq[i].dvy;
        liq[i].p=press(i);
        liq[i].x+=liq[i].vx*dt;
        liq[i].y+=liq[i].vy*dt;
    }
}
#include <SFML/Graphics.hpp>
void Liquid::Visualize()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(E_WX, E_WY), "SPH", sf::Style::Fullscreen, settings);
    window.setFramerateLimit(60);
    sf::RectangleShape bg(sf::Vector2f(E_WX, E_WY));
    bg.setPosition(0, 0);
    sf::RectangleShape wall1(sf::Vector2f(E_width, E_height));
    wall1.setPosition((E_WX-E_length)/2-E_width, E_indent);
    wall1.setFillColor(sf::Color::Black);
    sf::RectangleShape wall2(sf::Vector2f(E_width, E_height));
    wall2.setPosition((E_WX+E_length)/2, E_indent);
    wall2.setFillColor(sf::Color::Black);
    sf::RectangleShape bottom(sf::Vector2f(E_length+2*E_width, E_width));
    bottom.setPosition((E_WX-E_length)/2-E_width, E_height+E_indent);
    bottom.setFillColor(sf::Color::Black);
    std::vector <sf::CircleShape> fluid;
    fluid.resize(liq.size());
    for (unsigned i=0; i<liq.size(); i++)
    {
        sf::Color c;
        if (liq[i].color=="red")
            c=sf::Color::Red;
        if (liq[i].color=="blue")
            c=sf::Color::Blue;
        if (liq[i].color=="green")
            c=sf::Color::Green;
        fluid[i].setFillColor(c);
        fluid[i].setRadius(E_rad);
        fluid[i].setOrigin(E_rad, E_rad);
        fluid[i].setPosition(liq[i].x, liq[i].y);
    }
    Starting();
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            for (int i=0; i<10; i++)
            {
                Solve();
                for (unsigned j=0; j<liq.size(); j++)
                {
                    fluid[j].setPosition(liq[j].x, liq[j].y);
                }
            }
            window.clear();
            window.draw(bg);
            window.draw(wall1);
            window.draw(wall2);
            window.draw(bottom);
            for (std::vector <sf::CircleShape>::iterator it=fluid.begin(); it!=fluid.end(); ++it)
            {
                window.draw((*it));
            }
            window.display();
        }
    }
}
