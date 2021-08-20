#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX 250        // size of string
typedef int boolean ; // boolean false 0 true 1

typedef struct stack_d // stack for integer using liked list
{
    double val ;
    struct stack_d *next;
}*stack_d ;


struct node              // link list to store the postfix
{
    double valuo ;
    char mood ;
    struct node *next ;

};
typedef struct node* node_eq ;
typedef struct node* head ;


typedef struct equation        // store the equation
{
    char arr[MAX] ;     // equation
    bool valid ;      // if valid or not
    char postfix[MAX] ;     // postfix if valid
    double res ;              // result if valid
    char apology[MAX] ;         // apology if not valid

} equation;

typedef struct pair1     // pair contain two equation
{
    equation first ;
    equation secound ;
    bool valid_p ; // check if tow equation are valid
} pair_eq;



struct node1          // stack for char
{
    char val ;
    struct node1*next1 ;
};
typedef struct node1* stack ;
typedef struct list
{
    pair_eq p ;
    struct list *next ;
}*list;



// method of stack && stack_int && list && pair
stack new_stack()           // create the stack
{
    stack k = (stack)malloc(sizeof(struct node1)) ;
    k->next1 = NULL ;
    return k ;
}
void push(stack h, char ch )          // push to stack
{
    stack st = new_stack() ;
    st->next1 = h->next1 ;
    h->next1 = st ;
    st->val = ch ;
}
void pop(stack h )              // pop from the stack
{
    if(! is_empty(h))
    {
        stack st = h->next1 ;
        h->next1 = st->next1 ;
        free(st);
    }
}
char top(stack h )            // return the top of stack
{
    if(!is_empty(h))
    {

        return h->next1->val ;
    }
    return -1;
}
int is_empty(stack h )           // check if empty
{
    return h->next1 == NULL ;
}

pair_eq make_pair(equation eq1, equation eq2)    // add two equation to the pair
{
    pair_eq p;
    p.first = eq1 ;
    p.secound = eq2 ;
    return p ;
}
list new_list()           // create new list
{
    list p = (list)malloc(sizeof(struct list));
    p->next = NULL ;
    return p ;
}
void add_last_list(list h, pair_eq p )     // add last to the list
{
    list temp  = h ;
    while(temp->next != NULL)
    {
        temp = temp->next ;
    }
    list p1 = new_list() ;

    temp->next = p1 ;
    p1->p = p ;
    p1->next = 0 ;
}
node_eq new_node()        // create the new node
{
    node_eq n = (node_eq)malloc(sizeof(struct node)) ;
    n->next = NULL ;
    return n ;
}
void add_last(head h, double x, char c) // add last to the list
{
    node_eq p = h ;
    while(p->next != NULL)
    {
        p = p->next ;
    }
    node_eq temp = new_node() ;
    temp->valuo = x ;
    temp->mood = c ;
    temp->next = NULL ;
    p->next = temp ;
}

stack_d new_stack_d() // create the stack of integer
{
    stack_d st = (stack_d)malloc(sizeof(struct stack_d));
    st->next = NULL ;
    return st ;
}
void push_d(stack_d h,double x) // push to the stack of integer
{
    stack_d temp = new_stack_d() ;
    temp->val = x ;
    temp->next = h->next ;
    h->next = temp ;
}
void pop_d(stack_d h )         // pop from the stack of integer
{
    if(! is_empty_d(h))
    {
        stack_d e = h->next ;
        h->next = e->next ;
        free(e);
    }
}

boolean is_empty_d(stack_d h)     // check if is empty stack
{
    return h->next == NULL ;
}
double top_d(stack_d h )            // return the top of the stack
{
    return h->next->val ;
}

char close_b(char ch );
head re_str(char *arr);
int prec(char f, char l );
int valuo_ch(char ch );
void infix_postfix(char *temp,char *arr) ;
head to_node(char *arr1);
double evaluate(char *arr) ;
double calc(double l, double f, char ch );

double str_d(char *arr);
bool op(char ch );
int left_pre(char ch );
int right_pre(char ch );
char * con(char * a , char * b );
void  apo( char * arr , char *s );

int main()
{

    FILE *in, *out ;        // pointer of file to read && write
    int max = 0, y = 0, i = 0, o = 0, j= 0;
    list head1 = new_list() ;
    char x[50] ;
    int state = 1 ;
    do
    {
        printf("\n\n\t\t__________________________Project 2 - Data Structure_______________________________\n") ;
        printf("\n\t\t____________________________Mohammad Qashoo 1183336_______________________________\n") ;
        printf("\n\t\t 1) Read from file\n");
        printf("\n\t\t 2) Print all Equation \n");
        printf("\n\t\t 3) Print valid Equation with it's Postfix \n");
        printf("\n\t\t 4) Print valid Equation with it's Evaluation \n");
        printf("\n\t\t 5) Print Invalid Equation \n");
        printf("\n\t\t 6) Print all Equation in the file (output.txt) \n");
        printf("\n\t\t 7) Exit.\n\n\t\t ->") ;
        gets(x);
        if(x[0]>='1' && x[0]<='8' && strlen(x) == 1){
            //
            switch(x[0])
            {
            case '1' :
                clear_screan() ;
                //int x = Read_File(in,head1);
                if(!(y=Read_File(in, head1))){
                clear_screan() ;
                printf("\n\t\tError the file dose not exist.\n");
                }
                else{
                    printf("\n\t\The file has been reading successfully .\n\n\n");
                }
                end_screan(0) ;
            break ;
            case '2' :
                clear_screan() ;
                print_all(head1);
                end_screan(0) ;
            break ;
             case '3' :
                clear_screan() ;
                print_valid(head1);
                end_screan(0) ;
            break ;
            case '4' :
                clear_screan() ;
               print_valid_Evaluate(head1);
                end_screan(0) ;
            break ;
             case '5' :
                clear_screan() ;
               print_invalid(head1);
                end_screan(0) ;
            break ;
            case '6' :
                clear_screan() ;
               print_in_file(out,head1);
                end_screan(0) ;
            break ;
            case '7' :
                exit(0);
            break ;
            }
        }
        else
        {
            clear_screan() ;
            printf("\n\t\tThe number isn't in list try again.\n");
        }
    }
    while(state );
    return 0 ;

}


void clear_screan() // clear screen
{
    system("cls");
    printf("\n\t\t_______________________________________________________________________________\n\n");

}


void end_screan(int b)  // wait the user
{
    char g[256];
    printf("\n\n\n\t\t Press Enter to back to the menu ... ");
    if(b)
        gets(g);
    gets(g);
    system("cls");
    printf("\n\t\t_______________________________________________________________________________\n\n");

}


boolean check_str(char *arr)         // check if the equation are valid and trim the equation
{
    int i = strlen(arr)-1 ;
    int y, o = 1 ;
    if(arr[0] == '=')
    {
        return 0 ;
    }
    for(y =0 ; y < i ; y++)
    {
        if(arr[y] == '=')
        {
            o =0 ;
        }
        if(arr[y] == ' ')
        {
            int r = y ;
            for(; r<i ; r++ )
            {
                arr[r] = arr[r+1] ;
            }
            arr[r]='\0';
            y-- ;
        }
    }

    if(o)
        return 0 ;
    return 1 ;
}

void print_invalid(list h){

     list p = h->next;
    int c = 1;
    while(p!=NULL){
            if(strcmp(p->p.secound.arr,"NULL")==0){   // if the second part of eq = nothing

                    if(!p->p.first.valid){
                       apo(p->p.first.arr,p->p.first.apology);   // get the justification
                        printf("EQ %d >> %s | not valid >> %s \n",c,p->p.first.arr,p->p.first.apology);

                        c++ ;
                    }


            }
            else if ( !p->p.first.valid || !p->p.secound.valid){
                     if( (!p->p.first.valid && !p->p.secound.valid)){

                            apo(p->p.first.arr,p->p.first.apology);
                            apo(p->p.secound.arr,p->p.secound.apology);
                            printf("EQ %d >> %s = %s | not valid >> in the First part %s and in the second part %s \n",c,p->p.first.arr,p->p.secound.arr,p->p.first.apology,p->p.secound.apology);
                              c++ ;

                        }

                    if(!p->p.first.valid){
                                apo(p->p.first.arr,p->p.first.apology);
                                printf("EQ %d >> %s = %s | not valid >> in the first part %s \n",c,p->p.first.arr,p->p.secound.arr,p->p.first.apology);
                                c++ ;

                        }
                    else if (!p->p.secound.valid){
                                    apo(p->p.first.arr,p->p.secound.apology);
                                    printf("EQ %d >> %s = %s | not valid >> in the second part %s \n",c,p->p.first.arr,p->p.secound.arr,p->p.secound.apology);
                                    c++ ;

                            }

                    }

                    p=p->next;


            }



    }


void print_in_file(FILE * out , list h ){  // to print the equation in the file

    out = fopen("output.txt","w") ;
    list p = h->next;

    int c = 1;
    while(p!=NULL){
            if(strcmp(p->p.secound.arr,"NULL")==0){   // if the second part of eq = nothing

                    if(p->p.first.valid){
                        fprintf(out,"EQ %d >> %s | valid | Postfix >> [ %s ] | Result >> [ %.2lf ] \n",c,p->p.first.arr,p->p.first.postfix,p->p.first.res);
                        c++ ;
                    }
                    else{

                        apo(p->p.first.arr,p->p.first.apology);   // get the justification
                        fprintf(out,"EQ %d >> %s | not valid >> %s \n",c,p->p.first.arr,p->p.first.apology);
                        c++ ;
                    }
            }
            else{
                     if( (p->p.first.valid && p->p.secound.valid)){
                         if(p->p.first.res == p->p.secound.res){
                            fprintf(out,"EQ %d >> %s = %s | valid and the result is true | Postfix >> [ %s ] = [ %s ] | Result >> [ %.2lf ] = [ %.2lf ] \n",c,p->p.first.arr,p->p.secound.arr,p->p.first.postfix,p->p.secound.postfix,p->p.first.res,p->p.secound.res);

                             c++ ;
                         }
                         else{
                               fprintf(out,"EQ %d >> %s = %s | valid and the result is false | Postfix >> [ %s ] != [ %s ] | Result >> [ %.2lf ] != [ %.2lf ] \n",c,p->p.first.arr,p->p.secound.arr,p->p.first.postfix,p->p.secound.postfix,p->p.first.res,p->p.secound.res);
                             c++ ;
                         }
                    }
                    else{
                            if(p->p.first.valid){
                                apo(p->p.secound.arr,p->p.secound.apology);
                                fprintf(out,"EQ %d >> %s = %s | not valid >> in the second part %s \n",c,p->p.first.arr,p->p.secound.arr,p->p.secound.apology);
                                c++ ;
                            }
                            else{
                                    apo(p->p.first.arr,p->p.first.apology);
                                    fprintf(out,"EQ %d >> %s = %s | not valid >> in the first part %s \n",c,p->p.first.arr,p->p.secound.arr,p->p.first.apology);
                                    c++ ;
                            }
                    }

            }
             p=p->next;
    }
    printf("\n\t\tThe operation is completed successfully");
    fclose(out);
}

void print_valid_Evaluate(list h ){

    list p = h->next ;
    int c = 1;

    while(p!=NULL){
            if(strcmp(p->p.secound.arr,"NULL")==0){   // if the second part of eq = nothing

                    if(p->p.first.valid){
                        printf("EQ %d >>  %s  | Result >>   [ %.2lf ]  \n",c,p->p.first.arr,p->p.first.res);

                        c++ ;
                        }
                }

            else {
                    if((p->p.first.valid && p->p.secound.valid)){
                         if(p->p.first.res == p->p.secound.res){

                             printf("EQ %d >>  %s = %s  | Result >> [ %.2lf ] = [ %.2lf ] >> The result is true \n",c,p->p.first.arr,p->p.secound.arr ,p->p.first.res , p->p.secound.res );

                             c++ ;
                         }
                         else{
                             printf("EQ %d >> [ %s = %s ] | Result >> [ %.2lf ] != [ %.2lf ] >> The result is false \n",c,p->p.first.arr,p->p.secound.arr ,p->p.first.res , p->p.secound.res );

                             c++ ;
                         }


                    }

            }

             p=p->next;

    }

}

void print_valid(list h ){

    list p = h->next ;
    int c = 1;

    while(p!=NULL){
            if(strcmp(p->p.secound.arr,"NULL")==0){   // if the second part of eq = nothing

                    if(p->p.first.valid){
                        printf("EQ %d >>  %s  | postfix >>  %s  \n",c,p->p.first.arr,p->p.first.postfix);

                        c++ ;
                        }
                }

            else {
                    if((p->p.first.valid && p->p.secound.valid)){
                         if(p->p.first.res == p->p.secound.res){

                             printf("EQ %d >>  %s = %s  | postfix >> [ %s ] = [ %s ] and the result is true \n",c,p->p.first.arr,p->p.secound.arr ,p->p.first.postfix , p->p.secound.postfix );

                             c++ ;
                         }
                         else{
                             printf("EQ %d >> [ %s = %s ] | postfix >> [ %s ] = [ %s ] and the result is false \n",c,p->p.first.arr,p->p.secound.arr ,p->p.first.postfix , p->p.secound.postfix );

                             c++ ;
                         }


                    }

            }

             p=p->next;

    }

}

void print_all(list h ){   // 2

    list p = h->next;
    int c = 1;
    while(p!=NULL){
            if(strcmp(p->p.secound.arr,"NULL")==0){   // if the second part of eq = nothing

                    if(p->p.first.valid){
                        printf("EQ %d >> %s | valid \n",c,p->p.first.arr);

                        c++ ;
                    }
                    else{
                        apo(p->p.first.arr,p->p.first.apology);   // get the justification
                        printf("EQ %d >> %s | not valid >> %s \n",c,p->p.first.arr,p->p.first.apology);

                        c++ ;

                    }

            }
            else{
                     if( (p->p.first.valid && p->p.secound.valid)){
                         if(p->p.first.res == p->p.secound.res){

                             printf("EQ %d >> %s = %s | valid and the result is true \n",c,p->p.first.arr,p->p.secound.arr);

                             c++ ;
                         }
                         else{
                             printf("EQ %d >> %s = %s | valid and the result is false \n",c,p->p.first.arr,p->p.secound.arr);

                             c++ ;
                         }


                    }
                    else{
                            if(p->p.first.valid){
                                apo(p->p.secound.arr,p->p.secound.apology);
                                printf("EQ %d >> %s = %s | not valid >> in the second part %s \n",c,p->p.first.arr,p->p.secound.arr,p->p.secound.apology);

                                c++ ;

                            }
                            else{
                                    apo(p->p.first.arr,p->p.first.apology);
                                    printf("EQ %d >> %s = %s | not valid >> in the first part %s \n",c,p->p.first.arr,p->p.secound.arr,p->p.first.apology);
                                    c++ ;
                            }
                    }
            }
             p=p->next;
    }

}


int Read_File(FILE *in,list head1){

    int max ;
    char path[MAX] ;
    printf("\n\t\tEnter the name of the file >> "); // get the name of the file
    gets(path);
    in = fopen(path,"r") ;
    if(in == NULL)
    {
        return 0 ;
    }
    else
    {
        Read_Eq(in,head1);           // read the equation and store them into list
        calc_equation(head1);         // get all operation of every Eq

        return 1 ;
    }


}

void calc_equation(list head1) // calculate the equation
{
    list p = head1->next ;
    while(p != NULL)
    {
        p->p.first.valid = valid(p->p.first.arr) ; // check if the first equation are valid

        p->p.secound.valid = valid(p->p.secound.arr) ; // check the secound equation are valid

        if( p->p.first.valid &&  p->p.secound.valid)     // if two equation are valid
        {
            p->p.valid_p = 1 ;
            p->p.first.valid = 1 ;
            p->p.secound.valid = 1 ;
            char e[MAX] ="" ;
            infix_postfix(e, p->p.first.arr ); // convert from infix to prefix
            strcpy(p->p.first.postfix, e) ;
            double result = evaluate(p->p.first.postfix) ; // convert from infix to prefix
            p->p.first.res = result ;
            //
            char e1[MAX] = "" ;
            infix_postfix(e1, p->p.secound.arr ); // convert from infix to prefix
            strcpy( p->p.secound.postfix, e1 ) ;
            double ruselt2 = evaluate(p->p.secound.postfix) ; // convert from infix to prefix
            p->p.secound.res = ruselt2 ;

        }
        else               // if one of them are invalid
        {
            p->p.valid_p = 0 ;

            if(p->p.first.valid)
            {
                char e[MAX] ="" ;
                infix_postfix(e, p->p.first.arr ); // convert from infix to prefix
                strcpy(p->p.first.postfix, e) ;
                double ruslt =  evaluate(p->p.first.postfix) ; // convert from infix to prefix
                p->p.first.res = ruslt ;
            }
            else
            {
                p->p.first.valid = 0 ;

            }

            if(p->p.secound.valid)
            {
                char e[MAX] ="" ;
                infix_postfix(e, p->p.secound.arr ); // convert from infix to prefix
                strcpy(p->p.secound.postfix, e) ;
                double ruslt =  evaluate(p->p.secound.postfix) ; // convert from infix to prefix
                p->p.secound.res = ruslt ;
            }
            else
            {
                p->p.secound.valid = 0 ;
            }
        }
        p = p->next;
    }
}


bool Check_Str(char *arr)         // check if the equation are valid and trim the equation
{
    int i = strlen(arr)-1 ;
    int y, o = 1 ;
    if(arr[0] == '=')
    {
        return 0 ;
    }
    for(y =0 ; y < i ; y++)
    {
        if(arr[y] == '=')
        {
            o =0 ;
        }
        if(arr[y] == ' ')
        {
            int r = y ;
            for(; r<i ; r++ )
            {
                arr[r] = arr[r+1] ;
            }
            arr[r]='\0';
            y-- ;
        }
    }

    if(o)
        return 0 ;
    return 1 ;
}


void Read_Eq(FILE *file, list h) // read the equation from the file
{
    char line[MAX], *temp ;
    pair_eq p ;
    while(fgets(line, MAX, file) != NULL)
    {
        if(check_str(line) == 1 )
        {
            equation eq1, eq2 ;
            temp = strtok(line, "=");            // split the tow equation
            strcpy( eq1.arr, temp );
            temp = strtok(NULL, "\n");
            strcpy( eq2.arr, temp );
            p = make_pair(eq1, eq2);                  // store them to the pair
            add_last_list(h, p);                        // add the pair to the list

        }
        else{
            equation eq1, eq2;
            temp = strtok(line, "\n");            // split the tow equation
            strcpy( eq1.arr, temp );
            strcpy( eq2.arr,"NULL");
            p = make_pair(eq1, eq2);                  // store them to the pair
            add_last_list(h, p);                        // add the pair to the list


        }

    }

    fclose(file);

}


void infix_postfix(char *temp,char *arr) // convert from infix to prefix
{
    head h = new_node() ;           // create new node
    stack s = new_stack() ;            //create the stack
    h = re_str(arr);                     // add the equation to the linked list
    node_eq p =h->next ;
    while(p != NULL)
    {
        if(p->mood == '[' || p->mood == '{') // convert the [ & { to (
        {
            p->mood ='(' ;
        }
        if(p->mood == ']' || p->mood == '}') // convert the ] & } t )
        {
            p->mood =')' ;
        }

        if( p->mood == 'n' ) // if number append to the array
        {
            append_int(temp, p->valuo);
            append(temp, ',');
        }
        else
        {
            if(is_empty(s) || p->mood == '(')  // if '(' push
            {
                push(s, p->mood) ;
            }
            else
            {
                if( p->mood == ')' || prec(top(s), p->mood ))  // if ')' pop to reach the '('
                {
                    if(p->mood ==')')
                    {
                        while(top(s) != '(')
                        {
                            append(temp, top(s)) ;
                            append(temp, ',');
                            pop(s);
                        }
                        pop(s);
                    }
                    else
                    {
                        append(temp, top(s) );          // if operation
                        append(temp, ',');
                        pop(s);
                        while( prec(top(s), p->mood ) && !is_empty(s)) // check the proc the operation
                        {
                            append(temp, top(s));
                            append(temp, ',');
                            pop(s);
                        }
                        push(s,p->mood);
                    }
                }
                else
                {
                    push(s,p->mood);
                }
            }
        }
        p = p->next ;
    }
    while(!is_empty(s))      // is there is element in to stack put them in the array
    {
        append(temp, top(s));
        append(temp, ',');
        pop(s);
    }
    free_all_node(h) ;     // free all node in the linked list
}


int prec(char f, char l )
{
    if(f == '(' || f ==')' || l == '(' || l ==')')
        return 0  ;
    if(valuo_ch(f) >= valuo_ch(l))
        return 1 ;

    return 0 ;

}

int valuo_ch(char ch ) // value of all operation
{
    switch(ch)
    {
    case '+' :
        return 1 ;
    case '-' :
        return 1 ;
    case '*' :
        return 2 ;
    case '/' :
        return 2 ;
    case '%' :
        return 2 ;
    case '^' :
        return 3 ;
    }

}

head re_str(char *arr) // store the equation to the linked list
{
    int i = strlen(arr);
    int y, j = 0, state = 0 ;
    char temp[MAX][MAX] = {} ;               // array to put the split equation
    head h = new_node() ;             // create the header for the list
    for( y =0 ; y<= i ; y++)
    {
        if( (arr[y] >= '0' && arr[y]<= '9') || arr[y] == '.') // if operand append to the array
        {
            state = 1 ;
            append(temp[j],arr[y] );
        }
        else          // operation increment and add to array
        {
            if(state)
                j++ ;
            state =0 ;
            temp[j++][0] = arr[y] ;
        }
    }
    double  res = 1 ;
    double q = 1;
    for(y = 0 ; y < j-1 ; y++)         //add the split equation to the link list
    {
        if((temp[y][0] == '-' && op(temp[y-1][0])) || ( temp[y][0] == '-' && right_pre(temp[y-1][0]))) // (- || +-  continue this is sign
        {
            continue ;
        }
        if( (temp[y][0]=='+' && op(temp[y-1][0])) || (temp[y][0] == '+' && right_pre(temp[y-1][0])) ) // (+ || (+ continue this sign
        {
            continue ;
        }
        // --( || -+(
        if( (right_pre(temp[y][0]) && temp[y-1][0] == '-' && temp[y-2][0] == '-') || right_pre(temp[y][0]) && temp[y-1][0] == '-' && temp[y-2][0] == '+')
        {
            q = -1 ;
        }
        if(temp[0][0]== '-' && y == 0) // start with minus
        {
            res = -1 ; // to make the result minus
        }
        else
        {
            if(temp[y][0] >='0' && temp[y][0]<='9')      // if operand
            {

                res *= str_d(temp[y]);
                if( (temp[y-1][0] == '-' && right_pre(temp[y-2][0])) || (temp[y-1][0] =='-' && op(temp[y-2][0]))) // ( - 8 its sign || *-9 sign
                {
                    res*=-1;
                }
                res *= q ;
                if(left_pre(temp[y+1][0]))
                {
                    q = 1 ;   // if --(
                }

                add_last( h, res, 'n'); // add the number to the list
                res = 1;
            }
            else // if operand add to the new node
            {
                add_last( h, 0, temp[y][0]);
            }
        }
    }
    return h ;
}


bool op(char ch ) // operation
{
    switch(ch)
    {
    case '-' :
        return 1;
    case '+' :
        return 1;
    case '*' :
        return 1;
    case '/' :
        return 1;
    case '^' :
        return 1;
    case '%' :
        return 1;

    }
    return 0 ;
}

void append(char* arr, char ch ) // append the char
{
    int i = strlen(arr) ;
    arr[i] = ch ;
    arr[i+1] = '\0' ;
}

void append_int(char*arr, double x ) // append the number
{
    int i = strlen(arr) ;
    char temp[MAX] ;
    sprintf(temp, "%0.2lf", x);
    int y = strlen(temp), o = 0;
    while(y != 0  )
    {
        arr[i++] = temp[o++] ;
        y-- ;
    }
    arr[i+1] = '\0';
}



double evaluate(char *arr) // evaluate the equation
{

    head h = to_node(arr) ;        // make the postfix link list and split it
    double res =  0 ;
    stack_d st = new_stack_d() ; // new stack integer
    node_eq p = h->next ;
    while( p != NULL )              // for all the element
    {

        if(p->mood == 'n' && p->valuo != 0) // if number push
        {
            push_d(st,p->valuo) ;
        }
        else if(p->mood != ',')      // if operation pop pop evaluate push
        {
            double l = top_d(st) ;
            pop_d(st) ;
            double f = top_d(st) ;
            pop_d(st) ;
            res = calc(l, f, p->mood);
            if(res == 100000007)
            {
                return res;
            }
            push_d(st, res) ;
        }
        p= p->next ;
    }
    res = top_d(st) ;         // the result in the top off stack
    free_all_node(h) ;     // free all the node in the link list
    return res ;
}

double calc(double l, double f, char ch ) // calculate the operation
{
    switch(ch)
    {
    case '+':
        return (f+l) ;
        break ;
    case '-':
        return (f-l);
        break;
    case '*':
        return (f*l)  ;
        break ;
    case '/':
        if(l != 0)
        {
            return f/l ;
        }
        else
        {
            return 100000007 ;
        }
        break ;
    case '%':
        return ((int)f%(int)l) ;
        break ;
    case '^' :
        return (pow(f,l)) ;
        break ;
    }
    return -1 ;
}


head to_node(char *arr1) // split the postfix to link list
{
    double res = 0 ;
    char arr[MAX] ;
    strcpy(arr, arr1) ;
    head h = new_node() ; // create new node
    char *token ;
    token = strtok(arr, ",");
    while(token != NULL)             // split the postfix
    {
        if(token[0]>='0' && token[0]<='9' || (token[0]=='-'&&token[1]>='0'&&token[1]<='9')) // if is operand add to node
        {
            res = str_d(token);
            add_last(h, res, 'n');
        }
        else
        {
            add_last( h, 0, token[0]) ; // if its operand add to node
        }
        token = strtok(NULL, ",");
    }
    return h ;
}



double str_d(char *arr) // convert from string to double
{
    double res ;
    res = atof(arr) ;
    return res ;
}


bool equal(char *s, char *s2) // function compare the string
{
    int i = 0;
    while (i != strlen(s))
    {
        if (s[i] != s2[i])
            return 0;
        else
            i++;
    }
    return 1;
}


void appendchar(char* s, char c) {
        int len = strlen(s);
        s[len] = c;
        s[len+1] = '\0';
}


void free_all_node(head  h ) // free all node
{
    if(h == NULL)
    {
        return ;
    }
    free_all_node(h->next);
    free(h);
}

boolean valid( char * arr) // check  if the equation valid or invalid
{



    stack st = new_stack() ; // create new stack to check the ([{ }])
    boolean b = 0 ;
    int i = strlen(arr) ;
    int y = 0 ;
    for(y =0 ; y < i ; y++){

        if(right_pre(arr[y])) // if right push
        {
            push(st,arr[y]);
        }
        if(left_pre(arr[y]))          // if left check if valid
        {
            if( close_b(arr[y]) == top(st) )
            {
                pop(st);
            }
            else
            {

                return 0;
            }
        }
        if((arr[y] == '(' && arr[y+1]==')') || (arr[y] == '[' && arr[y+1]==']')){ // () {} []


            return 0 ;
        }
        if((arr[y] == ')' && arr[y+1]=='(') || (arr[y] == ']' && arr[y+1]=='[')){ // }{ )( ][


            return 0 ;
        }
        if(arr[y] =='-' && arr[y+1]== '-' && arr[y+2] == '-'){ // ---


            return 0 ;
        }
        if(arr[y] =='+' && arr[y+1]== '+' && arr[y+2] == '+'){ // +++


            return 0 ;
        }
        if((arr[y]>='a' && arr[y]<='z') || (arr[y]>= 'A' && arr[y]<= 'Z')){ // if words


            return 0 ;
        }
    }

    if(arr[0] == '*'  || arr[0] == '/' || arr[0] == '^' || arr[0]=='%' ){ // is stat with invalid


        return 0 ;
    }

    if(arr[i-1] == '*' || arr[i-1]=='-' || arr[i-1]=='+' || arr[i-1] == '/' || arr[i-1] == '^' || arr[i-1]=='%' ){// end with operation


        return 0 ;
    }
    if(arr[0] == '-' && arr[1] == '-'){   // start whit --


            return 0 ;

    }


    if(arr[0] == '+' && arr[1] == '+'){ // start with ++



        return 0 ;
    }
    for(y =0 ; y < i ; y++){

        if(arr[y] == '/' && arr[y+1]== '0'){     // if divide by zero



            return 0 ;
        }
        if(op(arr[y])){                               // if operation

            if(!((arr[y+1]>='0' && arr[y+1]<='9') || ( arr[y+1] == '+'|| arr[y+1] == '-' || right_pre(arr[y+1])))){ // check if not the posible valid


                return 0 ;
            }
            if( right_pre(arr[y-1]) && op(arr[y+1])){


                return 0 ;   // (-+ two op
            }
            if(op(arr[y-1]) && op(arr[y+1])){


                return 0 ;   // -+- three op
            }

        }

        if(right_pre(arr[y])){ // 4(

            if( ( arr[y+1] == '*' || arr[y+1] == '/' || arr[y+1] =='^' ||  arr[y+1] =='%')){



                return 0 ;
            }
            if((arr[y-1 ] >= '0' && arr[y-1 ]<='9') ){



                return 0 ;
            }
        }
        if(left_pre(arr[y])){ // )9

            if((arr[y+1]>= '0' && arr[y+1 ]<= '9')){



                return 0 ;
            }
        }

    }
    if(is_empty(st)){
        return 1 ;

    } // if stack not empty in valid ({ {)) >> )
    else
        return 0 ;




}


void apo( char * arr , char * s) // check  if the equation valid or invalid
{

    stack st = new_stack() ; // create new stack to check the ([{ }])
    boolean b = 0 ;
    int i = strlen(arr) ;
    int y = 0 ;
    for(y =0 ; y < i ; y++){

        if(right_pre(arr[y])) // if right push
        {
            push(st,arr[y]);
        }
        if(left_pre(arr[y]))          // if left check if valid
        {
            if( close_b(arr[y]) == top(st) )
            {
                pop(st);
            }
            else
            {

                strcpy(s,"The '");
                appendchar(s,top(st));
                strcat(s,"' is not closed");
                strcpy(s,s);
                return;


            }
        }
        if((arr[y] == '(' && arr[y+1]==')') || (arr[y] == '[' && arr[y+1]==']')){ // () {} []

            strcpy(s,"There is no operation between '");
            appendchar(s,arr[y]);
            strcat(s,"' and '");
            appendchar(s,arr[y+1]);
            strcat(s,"'");
            strcpy(s,s);
            return;


        }
        if((arr[y] == ')' && arr[y+1]=='(') || (arr[y] == ']' && arr[y+1]=='[')){ // }{ )( ][

            strcpy(s,"Multiple Bracktes with wrong sequentially ");
            return;

        }
        if(arr[y] =='-' && arr[y+1]== '-' && arr[y+2] == '-'){ // ---

            strcpy(s,"The Equation is contain 3 operator sequentially ");
            return;

        }
        if(arr[y] =='+' && arr[y+1]== '+' && arr[y+2] == '+'){ // +++

             strcpy(s,"The Equation is contain 3 operator seq ");
             return;

        }
        if((arr[y]>='a' && arr[y]<='z') || (arr[y]>= 'A' && arr[y]<= 'Z')){ // if words

             strcpy(s,"The Equation is contain a words ");
             return;

        }
    }

    if(arr[0] == '*'  || arr[0] == '/' || arr[0] == '^' || arr[0]=='%' ){ // is stat with invalid

         strcpy(s,"The Equation is start with operation ");
         return;
    }

    if(arr[i-1] == '*' || arr[i-1]=='-' || arr[i-1]=='+' || arr[i-1] == '/' || arr[i-1] == '^' || arr[i-1]=='%' ){// end with operation

        strcpy(s,"The Equation is end with operation ");
        return;

    }
    if(arr[0] == '-' && arr[1] == '-'){   // start whit --

            strcpy(s,"The Equation is start with two operation ");
            return;


    }


    if(arr[0] == '+' && arr[1] == '+'){ // start with ++

         strcpy(s,"The Equation is start with two operation ");
         return;


    }
    for(y =0 ; y < i ; y++){

        if(arr[y] == '/' && arr[y+1]== '0'){     // if divide by zero

            strcpy(s,"There is a divide by zero >> ");
                appendchar(s,arr[y]);
                appendchar(s,arr[y+1]);
                strcpy(s,s);
                return;


        }
        if(op(arr[y])){                               // if operation

            if(!((arr[y+1]>='0' && arr[y+1]<='9') || ( arr[y+1] == '+'|| arr[y+1] == '-' || right_pre(arr[y+1])))){ // check if not the posible valid

                 strcpy(s,"There is a divide by zero >> ");
                 return;

            }
            if( right_pre(arr[y-1]) && op(arr[y+1])){

                strcpy(s,"There is a divide by zero >> ");    // (-+ two op
                return;

            }
            if(op(arr[y-1]) && op(arr[y+1])){

                 strcpy(s,"There is a divide by zero >> ");   // -+- three op
                 return;

            }

        }

        if(right_pre(arr[y])){ // 4(

            if( ( arr[y+1] == '*' || arr[y+1] == '/' || arr[y+1] =='^' ||  arr[y+1] =='%')){


            strcpy(s,"There is no value between '");
            appendchar(s,arr[y]);
            strcat(s,"' and '");
            appendchar(s,arr[y+1]);
            strcat(s,"'");
            strcpy(s,s);
            return;


            }
            if((arr[y-1 ] >= '0' && arr[y-1 ]<='9') ){

                strcpy(s,"There is no operator between '");
                appendchar(s,arr[y-1]);
                strcat(s,"' and '");
                appendchar(s,arr[y]);
                strcat(s,"'");
                strcpy(s,s);
                return;


            }
        }
        if(left_pre(arr[y])){ // )9

            if((arr[y+1]>= '0' && arr[y+1 ]<= '9')){

                strcpy(s,"There is no operator between '");
                appendchar(s,arr[y]);
                strcat(s,"' and '");
                appendchar(s,arr[y+1]);
                strcat(s,"'");
                strcpy(s,s);
                return;


            }
        }

    }

      if(!is_empty(st)){
        strcpy(s,"The '");
        appendchar(s,top(st));
        strcat(s,"' is not closed");
        strcpy(s,s);
        return;


    } // if stack not empty in valid ({ {)) >> )





}



int left_pre(char lp ){
    switch(lp)
    {
    case ')':
        return 1 ;
    case ']':
        return 1 ;
    }
    return 0 ;
}



int right_pre(char rp ){
    switch(rp)
    {
    case '(':
        return 1 ;
    case '[':
        return 1 ;
    }
    return 0 ;
}



char close_b(char cb )
{
    if(cb == ']')
        return '[' ;
    if(cb == ')')
        return '(' ;
}
































