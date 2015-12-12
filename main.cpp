#include <iostream>
#include <math.h>
#include <stdlib.h>
using namespace std;

class Nodo{
public:
    char dato;
    Nodo *izquierda;
    Nodo *derecha;

    Nodo (Nodo *ramaizquierda = NULL,char valor=NULL, Nodo *ramaderecha = NULL){
        this->dato=valor;
        this->izquierda=ramaizquierda;
        this->derecha=ramaderecha;
    }

    friend class Arbolbinario;
    friend class ArbolBusqueda;
};

class Arbolbinario{
private:
    Nodo *raiz;
public:
    Arbolbinario(Nodo *r=NULL)  {
        this->raiz=r;
    }

    void Praiz(Nodo *r){
        raiz=r;
    }

    Nodo* Oraiz(){
        return raiz;
    }

    bool esVacio(){
        return (raiz==NULL);
    }

    Nodo * hijoizquierda(){
        if(raiz)
            return raiz->izquierda;
        else
            throw " arbol iquierdo vacio";
    }

    Nodo * hijoderecha(){
        if(raiz)
            return raiz->derecha;
        else
            throw " arbol derecho vacio";
    }

    Nodo* nuevoArbol(Nodo* ramaizq, char valor, Nodo* ramader){
        return new Nodo(ramaizq,valor,ramader);
    }

    void preorden(Nodo *r){
        if(r!=NULL){
            cout<<r->dato<<" ";
            preorden(r->izquierda);
            preorden(r->derecha);
        }
    }

    void inorden(Nodo *r){
        if(r!=NULL){
            inorden(r->izquierda);
            cout<<r->dato<<" ";
            inorden(r->derecha);
        }
    }

    void postorden(Nodo *r){
        if(r!=NULL){
            postorden(r->izquierda);
            postorden(r->derecha);
            cout<<r->dato<<" ";
        }
    }

   void vaciar(Nodo *r)
    {
        if(r!=NULL)
        {
            vaciar(r->izquierda);
            vaciar(r->derecha);
            cout<<"Nodo borrado.\n";
            delete r;
        }
    }

//de forma volcada
   Nodo* copiaarbol(Nodo*raiz){
        Nodo *raizcopia;
        if (raiz==NULL)
            raizcopia=NULL;
        else{
            Nodo *copiaizq, *copiader;
            copiaizq=copiaarbol(raiz->izquierda);
            copiader=copiaarbol(raiz->derecha);
            raizcopia=new Nodo(copiaizq, raiz->dato,copiader);
        }
        return raizcopia;
    }

    int altura(Nodo *raiz){
        if(raiz==NULL)
            return 0;
        else{
            int alturaiz = altura(raiz->izquierda);
            int alturadr = altura(raiz->derecha);
            if(alturaiz > alturadr)
                return alturaiz+1;
            else
                return alturadr+1;
        }
    }


    int numnodos(Nodo *raiz){
        if(raiz==NULL)
            return 0;
        else
            return 1+numnodos(raiz->izquierda) + numnodos(raiz->derecha);
    }


    bool arbollleno(Nodo *raiz){
        if(raiz==NULL)
            return true;
        else
            if(altura(raiz->izquierda)!=altura(raiz->derecha))
            return false;

            return arbollleno(raiz->izquierda) && arbollleno(raiz->derecha);

    }

     Nodo* buscar(Nodo *raizsub, char buscado){
        if(raizsub==NULL)
            return NULL;
        else if(buscado==raizsub->dato)
            return raizsub;
        else if(buscado < raizsub->dato)
            return buscar(raizsub->izquierda,buscado);
        else
            return buscar(raizsub->derecha,buscado);
    }

    Nodo* insertar(Nodo* raizsub, char dato){
        if(raizsub==NULL)
            raizsub=new Nodo(NULL,dato,NULL);
        else if(dato < raizsub->dato){
            Nodo *izq;
            izq = insertar(raizsub->izquierda,dato);
            raizsub->izquierda=izq;
        }else if (dato > raizsub->dato){
            Nodo *der;
            der = insertar(raizsub->derecha,dato);
            raizsub->derecha=der;
        }else
            throw "Nodo duplicado"; //cuando se repite el valor
        return raiz=raizsub;
    }

     Nodo* eliminar(Nodo *raizsub, char dato){
      if(raizsub==NULL)
        throw "No se ha encontrado el nodo en la clave";
      else if (dato < raizsub->dato){
        Nodo *izq;
        izq = eliminar(raizsub->izquierda,dato);
        raizsub->izquierda=izq;
      }
      else if (dato > raizsub->dato){
        Nodo *der;
        der = eliminar(raizsub->derecha,dato);
        raizsub->derecha=der;
      }
      else{
        Nodo *q;
        q=raizsub;  //nodo a eliminar
        if(q->izquierda==NULL)
            raizsub=q->derecha;
        else if(q->derecha==NULL)
            raizsub=q->izquierda;
        else{
            q=reemplazar(q);
        }
        q=NULL;
      }
      return raizsub;
    }

    /////////////////////////////evaluar cuando son numeros
    void evaluarnum(){   int num;
        num=evaluarnum(raiz);
        cout<<num<<endl;
    }

    int evaluarnum(Nodo *raiz){
        int x,y;
        string ch;
        char car;
        int num;

        if(raiz!=NULL){
            ch=raiz->dato;
            car=ch[0];
            num=atoi(ch.c_str());

            if(num>0)
               return num;
            else{
                x=evaluarnum(raiz->izquierda);
                y=evaluarnum(raiz->derecha);

                switch (car){
                    case '+': return x+y;
                    break;
                    case '-': return x-y;
                    break;
                    case '*':return x*y;
                    break;
                    case '/': if(y!=0)
                    return x/y;
                    else
                        throw "Error: division por 0";
                    break;
                    case '^': return pow(x,y);
                }
            }
        }
    }

    /////////////////////////////evaluar cuando son letras
    double evaluarletra(Arbolbinario b, double operandos[]){
        double x,y;
        char ch;
        Nodo *raiz;
        raiz=b.Oraiz();
        if(raiz!=NULL){
            ch=raiz->dato;
            if(ch>='A' && ch <='Z')
                return operandos[ch - 'A'];
            else{
                x=evaluarletra(raiz->izquierda,operandos);
                y=evaluarletra(raiz->derecha,operandos);
                switch (ch){
                    case '+': return x+y;
                    break;
                    case '-': return x-y;
                    break;
                    case '*':return x*y;
                    break;
                    case '/': if(y!=0)
                    return x/y;
                    else
                        throw "Error: division por 0";
                    break;
                    case '^': return pow(x,y);
                }
            }
        }
    }


private:
    Nodo* buscariterativo (char buscado){
        char dato;
        bool encontrado = false;
        Nodo *raizsub = raiz;
        dato=buscado;
        while(!encontrado && raizsub != NULL){
            if (dato==raizsub->dato)
                encontrado=true;
            else if (dato<raizsub->dato)
                raizsub = raizsub->izquierda;
            else
                raizsub = raizsub->derecha;
        }
        return raizsub;
    }


    Nodo* reemplazar(Nodo* actual){
      Nodo *a, *p;
      p=actual;
      a=actual->izquierda;
      while (a->derecha!=NULL){
          p=a;
          a=a->derecha;
      }
      //copia en actual el valor del nodo apuntado por a
      actual->dato=a->dato;
      if(p==actual) // si a es el hijo izquierdo de actual
        p->izquierda=a->izquierda; //enlaza subarbol izquierdo
      else
        p->derecha=a->derecha; //enlaza subarbol derecho

      return a;
    }

};



int main(){
    Arbolbinario a1, a2, a3, a4, a, b;
    Nodo *n1, *n2,*n3,*n4;
    n1 = a1.nuevoArbol(NULL,'B', NULL);
    n2 = a2.nuevoArbol(NULL, 'C', NULL);
    n3 = a3.nuevoArbol(n1,'+',n2);

    n1 = a1.nuevoArbol(NULL,'D', NULL);
    n2 = a2.nuevoArbol(NULL, 'R', NULL);
    n4 = a4.nuevoArbol(n1,'+',n2);
    n1 = a1.nuevoArbol(n3,'+',n4);
    a.Praiz(n1);
   cout<<"Altura: "<<endl;
   cout<<a.altura(n1)<<endl;

   cout<<"\nNumero de Nodos: "<<endl;
   cout<<a.numnodos(n1)<<endl;

   cout<<"\nPreorden: "<<endl;
   a.preorden(a.Oraiz());

   cout<<"\n\nInorden: "<<endl;
   a.inorden(a.Oraiz());

   cout<<"\n\nPostorden: "<<endl;
   a.postorden(a.Oraiz());

   cout<<"\n\nCopia de arbol B: "<<endl;
   b=a.copiaarbol(a.Oraiz());
   b.preorden(b.Oraiz());

   cout<<"\n\nVaciar arbol B: "<<endl;
   b.vaciar(b.Oraiz());

   cout<<"\nArbol de Expresion: \n";
   double operando[26];
   for(int i=0; i<=26;i++)
   {operando[i]=i;}
   cout<<a.evaluarletra(a,operando);

    cout<<"\n\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>ARBOL DE BUSQUEDA "<<endl;
    Arbolbinario c;
    Nodo *n5;

    c.insertar(c.Oraiz(),'8');
    c.insertar(c.Oraiz(),'3');
    c.insertar(c.Oraiz(),'1');
    c.insertar(c.Oraiz(),'2');
    c.insertar(c.Oraiz(),'9');
    c.insertar(c.Oraiz(),'5');
    c.insertar(c.Oraiz(),'4');

    cout<<"Recorrido Preorden: "<<endl;
    c.preorden(c.Oraiz());
    cout<<endl;

    cout<<"\nInsertar nuevo valor: 7"<<endl;
    c.insertar(c.Oraiz(),'7');
    c.preorden(c.Oraiz());
    cout<<endl;

    cout<<"\nBuscar Valor: 3"<<endl;
    n5=c.buscar(c.Oraiz(),'3');
    if(n5==NULL)
        cout<<"NO se encontro el nodo con el valor"<<endl;
    else
        cout<<"SI se encontro el nodo con el valor: "<<n5->dato<<endl;

    cout<<"\nEliminar valor: 5"<<endl;
    c.eliminar(c.Oraiz(),'5');
    c.preorden(c.Oraiz());
    cout<<endl;

    //cout << "Hello world!" << endl;
    return 0;
}
