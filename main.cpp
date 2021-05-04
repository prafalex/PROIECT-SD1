#include <iostream>
#include <fstream>
using namespace std;

ifstream in("date.in");
ofstream out("date.out");
struct nod_arbore
{
    int info;
    nod_arbore* fiu_stang;
    nod_arbore* fiu_drept;
};

struct arbore
{
    int nrElemente;
    nod_arbore* radacina;
    arbore()
    {
        radacina=NULL;
        nrElemente=0;
    }
    void insert_element(int x)
    {
        nrElemente++;
        nod_arbore* nou = new nod_arbore;
        nou->info = x;
        nou->fiu_stang=NULL;
        nou->fiu_drept=NULL;

        if (radacina==NULL)
        {
            radacina=nou;
            return;
        }

        nod_arbore* pointer_prev = NULL;
        nod_arbore* pointer = radacina;
        int directie = 0;

        while(pointer!=NULL)
        {
            pointer_prev=pointer;
            if (x<=pointer->info)
            {
                pointer=pointer->fiu_stang;
                directie = -1;
            }
            else
            {
                pointer=pointer->fiu_drept;
                directie = 1;
            }
        }

        if (directie <0)
            pointer_prev->fiu_stang=nou;
        else
            pointer_prev->fiu_drept=nou;
    }

    void delete_element(int x)
    {
        nod_arbore* pointer_prev =NULL;
        nod_arbore* pointer =radacina;
        int directie=0;
        while (pointer!=NULL && pointer->info!=x)
        {
            pointer_prev=pointer;
            if (x<= pointer->info)
            {
                pointer=pointer->fiu_stang;
                directie= -1;
            }
            else
            {
                pointer= pointer->fiu_drept;
                directie =1;
            }
        }

        if (pointer==NULL)
        {
            out<<"nu exista "<<x<<endl;
            return;
        }
        nrElemente--;
        //pointer indica nodul care trebuie sters
        //cazul in care nodul de sters nu are fii
        if (pointer->fiu_stang==NULL && pointer->fiu_drept==NULL)
        {
            out<<"nu are fii "<<x<<endl;
            if (pointer == radacina)
            {
                out<<"este radacina "<<x<<endl;
                radacina=NULL;
                delete pointer;
                return;
            }
            if (directie<0)
                pointer_prev->fiu_stang=NULL;
            else
                pointer_prev->fiu_drept=NULL;
            delete pointer;
            return;
        }
        //cazul in care nodul de sters are doar fiu stang
        if (pointer->fiu_stang!=NULL && pointer->fiu_drept==NULL)
        {
            out<<"are doar fiu stang "<<x<<endl;
            if (pointer == radacina)
            {
                out<<"este radacina "<<x<<endl;
                radacina=pointer->fiu_stang;
                delete pointer;
                return;
            }
            if (directie<0)
                pointer_prev->fiu_stang=pointer->fiu_stang;
            else
                pointer_prev->fiu_drept=pointer->fiu_stang;
            delete pointer;
            return;
        }
        //cazul in care nodul de sters are doar fiu drept
        if (pointer->fiu_stang==NULL && pointer->fiu_drept!=NULL)
        {
            out<<"are doar fiu stang "<<x<<endl;
            if (pointer == radacina)
            {
                out<<"este radacina "<<x<<endl;
                radacina=pointer->fiu_drept;
                delete pointer;
                return;
            }
            if (directie<0)
                pointer_prev->fiu_stang=pointer->fiu_drept;
            else
                pointer_prev->fiu_drept=pointer->fiu_drept;
            delete pointer;
            return;
        }
        //cazul in care nodul de sters are ambii fii
        out<<"are ambii fii "<<x<<endl;
        nod_arbore* pointer2=pointer->fiu_stang;
        while (pointer2->fiu_drept!=NULL)
            pointer2=pointer2->fiu_drept;

        int valoare = pointer2->info;
        out<<"nodul "<<valoare<<" il poate inlocui pe "<<x<<endl;
        delete_element(valoare);//doar daca sunt toate cheile distincte
        //am garantia ca valoare va fi sters ori cu stergerea-fara-fii
        //ori cu stergerea doar-fiu-stang; sigur nu are fiu drept

        pointer->info=valoare;
    }

    void SRD()
    {
        out<<"SRD: ";
        SRD(radacina);
        out<<endl;
    }
    void SRD(nod_arbore* pointer)
    {
        if (pointer!=NULL)
        {
            SRD(pointer->fiu_stang);
            out<<pointer->info<<" ";
            SRD(pointer->fiu_drept);
        }
    }
    void RSD()
    {
        out<<"RSD: ";
        RSD(radacina);
        out<<endl;
    }
    void RSD(nod_arbore* pointer)
    {
        if (pointer!=NULL)
        {
            out<<pointer->info<<" ";
            RSD(pointer->fiu_stang);
            RSD(pointer->fiu_drept);
        }
    }
    //de aici incep eu

    int minim()
    {
        nod_arbore* pointer =radacina;
        while(pointer->fiu_stang!=NULL)
            pointer=pointer->fiu_stang;
        return pointer->info;
    }
    int maxim()
    {
        nod_arbore* pointer =radacina;
        while(pointer->fiu_drept!=NULL)
            pointer=pointer->fiu_drept;
        return pointer->info;
    }
    int succesor(int x)
    {
        //caut noddul
        int s=radacina->info;
        nod_arbore* pointer_prev =NULL;
        nod_arbore* pointer =radacina;
        while(pointer!=NULL && pointer->info!=x)
        {
            pointer_prev=pointer;
            if (x<= pointer->info)
            {
                s=pointer->info;
                pointer=pointer->fiu_stang;

            }
            else
            {
                pointer= pointer->fiu_drept;

            }
        }

        if (pointer==NULL)
        {
            out<<"nu exista "<<x<<endl;
            return -1;
        }
        //pointer are nodul

        if(pointer->fiu_drept==NULL)
            if(s>x)
                return s;

            else
            {
                out<<"nu exista";
                return -1;
            }
        else
        {
            pointer=pointer->fiu_drept;
            while(pointer->fiu_stang!=NULL)
                pointer=pointer->fiu_stang;
        }

        //return (pointer->info<s)? pointer->info:s;
        return pointer->info;
    }
    int predecesor(int x)
    {
        //caut noddul
        int s=radacina->info;
        nod_arbore* pointer_prev =NULL;
        nod_arbore* pointer =radacina;
        while(pointer!=NULL && pointer->info!=x)
        {
            pointer_prev=pointer;
            if (x<= pointer->info)
            {

                pointer=pointer->fiu_stang;

            }
            else
            {
                s=pointer->info;
                pointer= pointer->fiu_drept;

            }
        }

        if (pointer==NULL)
        {
            out<<"nu exista "<<x<<endl;
            return -1;
        }
        //pointer are nodul

        if(pointer->fiu_stang==NULL)
            if(s<x)
            {
                return s;
            }

            else
            {
                out<<"nu exista";
                return -1;
            }
        else
        {
            pointer=pointer->fiu_stang;
            while(pointer->fiu_drept!=NULL)
                pointer=pointer->fiu_drept;
        }

        return pointer->info;
        //return (pointer->info<s)? pointer->info:s;

    }
    bool este_in(int x)
    {
        nod_arbore* pointer =radacina;
        while(pointer!=NULL && pointer->info!=x)
        {
            if (x<= pointer->info)
            {

                pointer=pointer->fiu_stang;

            }
            else
            {
                pointer= pointer->fiu_drept;

            }
        }
        if (pointer==NULL)
        {
            return 0;
        }
        return 1;
    }
    int cardinal()
    {
        return nrElemente;
    }
    int cardinal2(nod_arbore *n)
    {
        int ct=1;
        if(n==NULL)
            return 0;
        else
        {
            ct+=cardinal2(n->fiu_stang);
            ct+=cardinal2(n->fiu_drept);
            return ct;
        }
    }
    void k_element(nod_arbore* n, int k,int &ct )
    {
        if (n == NULL)
            return;
        if(k>nrElemente)
        {
            out<<"Elementul de pe pozitia "<<k<<" nu exista.\n";
            return;
        }
        if (ct <= k)
        {
            k_element(n->fiu_stang, k,ct);

            ct++;
            if (ct == k)
            {
                out <<"Elementul cautat : "<< n->info<<".\n";
                return;
            }
            k_element(n->fiu_drept, k,ct);
        }

    }
    void k_element(nod_arbore* n, int k)
    {
        int ct=0;
        return k_element(n,k,ct);
    }
};

int main()
{
    arbore arb;
    if(!in)
    {
        out<<"eroare deschidere fisier";
    }
    int a;
    while(in>>a)
    {
        arb.insert_element(a);
    }

    arb.SRD();
    arb.RSD();

    //arb.delete_element(6);

    arb.SRD();
    arb.RSD();
    out<<"\n-----------------\n";
    out<<"min:"<<arb.minim();
    out<<endl;
    out<<"max:"<<arb.maxim();
    out<<"\n-----------------\n";
    int n=5;
    out<<"Succesorul lui "<<n<<": "<<arb.succesor(n)<<endl;
    /*for(int i=1;i<=9;i++)
        out<<"Succesorul lui "<<i<<": "<<arb.succesor(i)<<endl;*/
    out<<"Predecesorul lui "<<n<<": "<<arb.predecesor(n)<<endl;
    /*for(int i=1;i<=9;i++)
        out<<"Predecesorul lui "<<i<<": "<<arb.predecesor(i)<<endl;*/

    out<<"\n-----------------\n";


    out<<"\n-----------------\n";
    out<<"Cardinal: "<<arb.cardinal();
    out<<"\n-----------------\n";
    /*for(int i=1;i<=20;i++)
        out<<"Apare "<<i<<" in arbore: "<<arb.este_in(i)<<endl;*/
    int cnt=0;
    arb.k_element(arb.radacina,2);
    arb.k_element(arb.radacina,4);
    arb.k_element(arb.radacina,14);

    return 0;
}

