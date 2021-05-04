#include <iostream>
#include <fstream>
using namespace std;

ifstream in("date.in");
ofstream out("date.out");
struct nod_arbore
{
    int info;
    int nr_ap=1;
    nod_arbore* fiu_stang;
    nod_arbore* fiu_drept;
};
//functie creare un nou nod
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
            if(pointer->info==x){
                pointer->nr_ap++;
                return;
            }
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
            out<<pointer->info<<"("<<pointer->nr_ap<<")"<<" ";
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
            out<<pointer->info<<"("<<pointer->nr_ap<<")"<<" ";
            RSD(pointer->fiu_stang);
            RSD(pointer->fiu_drept);
        }
    }
    //de aici incep eu

    int minim()
    {
        nod_arbore * pointer =radacina;
        while(pointer->fiu_stang!=NULL)
            pointer=pointer->fiu_stang;
        return pointer->info;
    }
    int maxim()
    {
        nod_arbore * pointer =radacina;
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
        int c=cardinal2(radacina);
        if(k>c)
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

    nod_arbore *minN(nod_arbore *n)
    {
        nod_arbore * act=n;
        while(act && act->fiu_stang!=NULL)
            act=act->fiu_stang;

        return act;
    }

    nod_arbore* sterge(nod_arbore * rad,int x)
    {
        if(rad==NULL)
            return rad;

        //gasire nod

        if(x<rad->info)
            rad->fiu_stang=sterge(rad->fiu_stang,x);
        else if(x>rad->info)
            rad->fiu_drept=sterge(rad->fiu_drept,x);
        else
        {
            //daca nr de ap este>1 stergem din nr de ap
            if(rad->nr_ap>1)
            {
                (rad->nr_ap)--;
                return rad;
            }
            //daca nu stergem nodul
            // nod cu un fiu sau fara fii
            if(rad->fiu_stang==NULL)
            {
                nod_arbore * tmp= rad->fiu_drept;
                free(rad);
                return tmp;
            }
            else if(rad->fiu_drept=NULL)
            {
                nod_arbore * tmp= rad->fiu_stang;
                free(rad);
                return tmp;
            }

            //daca avem 2 copii
            nod_arbore *tmp=minN(rad->fiu_drept);
            // succesorul inorder in pozitia nodului ce urmeaza sa fie sters
            rad->info=tmp->info;
            //stergem succesorul inorder
            rad->fiu_drept= sterge(rad->fiu_drept,tmp->info);
        }
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
    //arb.insert_element(1);
    while(in>>a)
    {
        arb.insert_element(a);
    }

    arb.SRD();
    arb.RSD();

    arb.sterge(arb.radacina,7);
    //arb.sterge(arb.radacina,10);

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

