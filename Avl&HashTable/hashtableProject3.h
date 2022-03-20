#ifndef HASHTABLEPROJECT3_H_INCLUDED
#define HASHTABLEPROJECT3_H_INCLUDED
#define MAX 250

typedef struct word_node {

    char word[30];
    char meaning[MAX];
    char synonym[30];
    char antonym[30];

} *Word ;

typedef struct tree {

    Word node ;
    struct tree * Left;
    struct tree * Right;
    int Hight;
} *Tree ;

typedef struct hash // Hash Table Contain the city and two boolean to remark the sells
{
    Word node  ;
    bool del ; // remark the cell deleted
    bool vis ; // remark the cell visited


} Hash;

int get_prime(int x);
Hash * insert_hash( Word  c , int n, Hash* h );


Hash* create_table(int size){ // create new hash table
    int x = get_prime(size*2+1) , i=0; // get the print after 2*n

    Hash* table = ( Hash* )malloc(sizeof(struct hash)*x) ; // create the table
    for(i=0; i<x ; i++ )
    {
        table[i].node = NULL ;
        table[i].vis = 0 ;


    }
    return table ;
}
int get_prime(int x){ // get the prime number after x

    int i = 3, temp = 1 ;
    for( ; x<1e9 ; x+=2 )
    {
        for(i=3 ; i*i<=x ; i+=2)
        {
            if(x%i == 0) // if is not prime
            {
                temp =0 ;
                break ;
            }
        }
        if(temp)
            return x ;
        temp =1 ;
    }
    return x ;
}

int get_key( char *c, int size ){ // hash function

    long long hv = 1, i =0;
    for(i=0 ; i<strlen(c) ; i++){
        hv = ( ( (hv<<2) + ( (long long)c[i]-60) ) ) ; // equation of hash
        }

    return ((hv%size)+size)%size ; // resize the
}

Hash * rehash_table(Hash *table, int n ){ // rehash

    Hash  *new_table = create_table(n) ;
    int i =0 ;
    for(i = 0 ; i<n ; i++)
    {
        if(table[i].vis  && table[i].node != NULL)
        {
            insert_hash(table[i].node, n, new_table) ;

        }
    }
    return new_table ;
}



Hash * insert_hash( Word c , int wsize , Hash* h ){        // n capcity of table

    int tsize = get_prime(2*wsize+1) ; // get the prime
    //printf("%d\n",tsize);
    int key = get_key( c->word, tsize ) , ind = key ; // get the key of hash
    if(get_size(h, tsize) < wsize  ) // check if hash or rehash
    {
        int i = 0 ;
        while( h[ind].vis  ) // quadratic hash
        {
            i++;
           ind = (key+i*i)%tsize;
        }
        h[ind].node = c;
        h[ind].vis = 1 ; // remark the vis

    }
     else
    {
        h = rehash_table(h, tsize) ; // rehash table size
        wsize = tsize ;
        tsize = get_prime(tsize*2+1 ) ; // get prime
        h = insert_hash( c, wsize , h); // insert the element to hash table
    }

    return h;
}


Hash * Delete_Value( Hash * t, int size , char* c ){ // delete city

    int key = get_key( c , size ) ; // find the key
    int i = 0 , ind = key ;
    while( (strcmp(t[ind].node->word,c) != 0 && t[ind].vis)   )
    {
        i++ ;
        ind = (key+i*i)%size ; // quadratic hash
    }
    t[ind].node = NULL;// remark it deleted
    t[ind].vis = 0 ;
    return t ;
}






int Search_Value(Hash *t, int size ,char* c, int flag){ // search about the city

    int st =1 ;
    int key = get_key(c, size ) ;
    int i =0 ,ind = key ;

    while( t[ind].vis ) // if vis
    {
        if(  strcmp(t[ind].node->word ,c) == 0 ) // if not the city
        {
            if(flag)
                return 1;
            st = 0 ;
            printf("\n\tThe index is %d | Word : %s | Meaning : %s | Synonym : %s | Antonym : %s\n", ind ,t[ind].node->word , t[ind].node->meaning , t[ind].node->synonym , t[ind].node->antonym);
        }
        i++ ;
        ind = (key + i*i)%size; // quadratic hash
    }
    if(st)
        return 0 ;
    else
        return 1 ;
}


int get_size(Hash* h, int size ){ // get size of table

    int i =0, n =0 ;
    for(i =0 ; i<size ; i++)
    {
        if(h[i].vis == 1) // if visited count them
            n++;
    }
    return n ;
}

void print_table(Hash *h,int size){ // print the table

    int i =0 ;
    for(i =0 ; i < size ; i++)
    {
        if(h[i].vis){

         // if the cell contain values

            printf("\n\t\t>>>The index %d | Word : %s | Meaning : %s | Synonym : %s | Antonym : %s | vis -> %d", i ,h[i].node->word , h[i].node->meaning , h[i].node->synonym , h[i].node->antonym , h[i].vis);
            printf("\n\t\t___________________________________________________________________________________________\n");
        }
        else
        {
            printf("\n\t\t>>>The index %d | (empty) | vis -> %d    \n",i, h[i].vis );
             printf("\n\t\t___________________________________________________________________________________________\n");

        }
    }
}


void print_hash_file(Hash *h, int size ){ // print the hash in the file

    FILE * fp;
   int i;

   fp = fopen ("Dictionary.txt","w");        // open the file for writing


   for(i = 0 ; i < size ; i++){
        if (h[i].vis)
       fprintf (fp, "%s : %s / %s * %s", h[i].node->word ,  h[i].node->meaning ,  h[i].node->synonym ,  h[i].node->antonym);
       puts("\n");
   }


   fclose (fp);           // close the file
}



void print_hash(Hash  *t, int size ){/ print the hash function

    int i =0 ;
    printf("\n\tHashValue = (HashValue<<2 + (long long)(str[i]-60)) \n") ;


    for(i=0 ; i <size ; i++)
    {
        if(t[i].vis == 1 && t[i].del == 0)
        {
            printf("\t%s :: hash Function is : %d\n", t[i].node->word , get_key( t[i].node->word,size ) );
        }
    }
}


Hash* add_to_table(Tree root, Hash * h, int size  ){ // add city to the table from the tree

    if(root == NULL)
        return h ;
    else
    {
        add_to_table(root->Left, h,size ) ;

        Word temp = root->node ;

        h = insert_hash(temp, size, h) ;

        add_to_table(root->Right, h,size) ;
        return h ;
    }
}

Hash *implement_table( Tree root , int avlsize){ // create table


    Hash* h = create_table(avlsize);
    h = add_to_table(root, h, avlsize ) ;



    return h ;
}






#endif //
